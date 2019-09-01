<?php
class public_msrp_admin_vehicles extends ipsCommand
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

		$count = $this->DB->query('SELECT COUNT(*) as max FROM `srv_vehicles`');
		$count = $this->DB->fetch($count);
		$st = $this->request['st'];
		$perpage = 50;

		/* Parsowanie paginacji */
		$pagination = $this->registry->getClass('output')->generatePagination( array(
			'totalItems'		=> $count['max'],
			'itemsPerPage'		=> $perpage,
			'currentStartValue'	=> $st,
			'baseUrl'			=> "app=msrp&module=admin&section=vehicles",
		)
	);
	$this->DB->query(sprintf('SELECT * FROM `srv_vehicles` ORDER by `UID` ASC LIMIT %d,%d',$st,$perpage));
	$this->DB->execute();


	while($row = $this->DB->fetch())
	{
		switch($row['ownertyp'])
		{
			case 0: $row['ownertyp'] = 'Nieznany'; break;
			case 1:	$row['ownertyp'] = 'Gracz'; break;
			case 2:	$row['ownertyp'] = 'Grupa'; break;
			case 9: $row['ownertyp'] = 'Praca dorywcza'; break;
			default: $row['ownertyp'] = 'Nieznany'; break;
		}
		$row['model']= $functions->GetVehicleModelName($row['model']);

		$vehicles[] = $row;
	}

	$template = $this->registry->output->getTemplate('msrp')->msrp_admin_vehicles($pagination, $vehicles);
	$this->registry->getClass('output')->addContent($template);
	$this->registry->output->setTitle('Lista pojazdów');
	$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin' );
	$this->registry->output->addNavigation( 'Lista pojazdów', 'app=msrp&module=admin&section=vehicles' );
	$this->registry->getClass('output')->sendOutput();
}

}
?>
