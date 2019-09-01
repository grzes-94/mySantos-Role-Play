<?php
class public_msrp_admin_itemlogs extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
		require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/functions.php' );
		$this->registry->setClass( 'functions', new functions( $registry ) );
		$functions = $this->registry->getClass( 'functions' );


		if(! $functions->IsGruopAdmin($this->memberData['member_group_id'],true))
		{
			$this->registry->output->silentRedirect('index.php');
		}

		$count = $this->DB->query('SELECT COUNT(*) as max FROM `srv_items_logs`');
		$count = $this->DB->fetch($count);


		$st=$this->request['st'];
		$perpage=100;

		/* Parsowanie paginacji */
		$pagination = $this->registry->getClass('output')->generatePagination( array(
			'totalItems'		=> $count['max'],
			'itemsPerPage'		=> $perpage,
			'currentStartValue'	=> $st,
			'baseUrl'			=> "app=msrp&module=admin&section=itemlogs",
		)
	 );

	$result =$this->DB->query(sprintf('SELECT l.*, i.name FROM `srv_items_logs` l LEFT JOIN `srv_items` i ON l.itemid = i.UID ORDER by `time` DESC LIMIT %d,%d',$st,$perpage));

	while($row = $result->fetch_assoc())
	{
    $row['from']=$functions->GetCharacterName($row['from_uid'],true)."<br />".$functions->GetMemberName($row['from_gid']);
    $row['to']=$functions->GetCharacterName($row['to_uid'],true)."<br />".$functions->GetMemberName($row['to_gid']);
		$row['value']= $functions->formatDollars($row['price']);
		$logs[] = $row;
	}

	$template = $this->registry->output->getTemplate('msrp')->msrp_admin_itemlogs($pagination, $logs);
	$this->registry->getClass('output')->addContent($template);
	$this->registry->output->setTitle('Logi przedmiotów');
	$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin' );
	$this->registry->output->addNavigation( 'Logi przedmiotów', 'app=msrp&module=admin&section=vehlogs' );
	$this->registry->getClass('output')->sendOutput();
  }

}
