<?php
class public_msrp_admin_cashlogs extends ipsCommand
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

		$this->DB->query('SELECT COUNT(*) AS max FROM `srv_cash_logs`');
		$count = $this->DB->fetch();

		$st=intval($this->request['st']);
		$perpage=100;

		/* Parsowanie paginacji */
		$pagination = $this->registry->getClass('output')->generatePagination( array(
			'totalItems'		=> $count['max'],
			'itemsPerPage'		=> $perpage,
			'currentStartValue'	=> $st,
			'baseUrl'			=> "app=msrp&module=admin&section=cashlogs",
		)
	);

	$this->DB->query(sprintf('SELECT * FROM `srv_cash_logs` ORDER by `time` DESC LIMIT %d,%d',$st,$perpage));
	$this->DB->execute();

	while($row = $this->DB->fetch())
	{
		$row['value']= $functions->formatDollars($row['value']);
		$logs[] = $row;
	}

	$template = $this->registry->output->getTemplate('msrp')->msrp_admin_cashlogs($pagination, $logs);
	$this->registry->getClass('output')->addContent($template);
	$this->registry->output->setTitle('Logi gotówki');
	$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin' );
	$this->registry->output->addNavigation( 'Logi gotówki', 'app=msrp&module=admin&section=cashlogs' );
	$this->registry->getClass('output')->sendOutput();
  }

}
