<?php
class public_msrp_admin_chars extends ipsCommand
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

		$count = $this->DB->query('SELECT COUNT(*) as max FROM `srv_characters`');
		$count = $this->DB->fetch($count);

		$st=$this->request['st'];
		$perpage=100;

		/* Parsowanie paginacji */
		$pagination = $this->registry->getClass('output')->generatePagination( array(
			'totalItems'		=> $count['max'],
			'itemsPerPage'		=> $perpage,
			'currentStartValue'	=> $st,
			'baseUrl'			=> "app=msrp&module=admin&section=chars",
		)
	);

	$this->DB->query(sprintf('SELECT * FROM `srv_characters` ORDER by `player_uid` ASC LIMIT %d,%d',$st,$perpage));
	$this->DB->execute();

	while($row = $this->DB->fetch())
	{
		$row['nickname'] = str_replace("_", " ", $row['nickname']);
		$row['cash']= $functions->formatDollars($row['cash']);
		$row['credit']= $functions->formatDollars($row['credit']);


		$chars[] = $row;
	}

	$template = $this->registry->output->getTemplate('msrp')->msrp_admin_chars($pagination, $chars);
	$this->registry->getClass('output')->addContent($template);
	$this->registry->output->setTitle('Lista postaci');
	$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin' );
	$this->registry->output->addNavigation( 'Lista postaci', 'app=msrp&module=admin&section=chars' );
	$this->registry->getClass('output')->sendOutput();
}

}
?>
