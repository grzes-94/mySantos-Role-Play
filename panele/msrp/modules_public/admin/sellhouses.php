<?php
class public_msrp_admin_sellhouses extends ipsCommand
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
    $count = $this->DB->query('SELECT COUNT(*) as max FROM srv_doors WHERE `ownertyp`=4');
    $count = $this->DB->fetch($count);

    $pagination = $this->registry->getClass('output')->generatePagination( array(
                                  'totalItems'		=> $count['max'],
                                  'itemsPerPage'		=> 50,
                                  'baseUrl'			=> "app=msrp&module=admin&section=sellhouses",
                                  )
                              );

		$query = $this->DB->query(sprintf('SELECT * FROM `srv_doors` WHERE `ownertyp`=4 LIMIT %d,50',$this->request['st']));

		while($row = $query->fetch_assoc())
		{

      $row['owner'] = $functions->formatDollars($row['owner']);

			$doors[] = $row;
		}



		$template = $this->registry->output->getTemplate('msrp')->msrp_admin_sellhouses($doors, $pagination);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('Lista domów na psrzedaż');
		$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin' );
		$this->registry->output->addNavigation( 'Lista domów', 'app=msrp&module=admin&section=sellhouses' );
		$this->registry->getClass('output')->sendOutput();
	}

}
?>
