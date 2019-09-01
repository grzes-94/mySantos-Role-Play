<?php
class public_msrp_admin_doors extends ipsCommand
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

					$count = $this->DB->query('SELECT COUNT(*) as max FROM srv_doors ORDER BY uid ASC');
					$count = $this->DB->fetch($count);

					$pagination = $this->registry->getClass('output')->generatePagination( array(
																				'totalItems'		=> $count['max'],
																				'itemsPerPage'		=> 100,
																				'baseUrl'			=> "app=msrp&module=admin&section=doors",
																				)
																		);

		$this->DB->query(sprintf('SELECT * FROM `srv_doors` LIMIT %d,100',$this->request['st']));
		$this->DB->execute();

		while($row = $this->DB->fetch())
		{
			switch($row['ownertyp'])
			{
				case 0: $row['ownertyp'] = 'Nieznany'; break;
				case 1:	$row['ownertyp'] = 'Gracz'; break;
				case 2:	$row['ownertyp'] = 'Grupa'; break;
				case 3:	$row['ownertyp'] = 'Dom'; break;
				case 4: $row['ownertyp'] = 'Dom na sell'; break;
				case 5: $row['ownertyp'] = 'Salon'; break;
				case 6: $row['ownertyp'] = 'Bankomat'; break;
				case 7: $row['ownertyp'] = 'Areszt'; break;
				case 8: $row['ownertyp'] = 'Ciucholand'; break;
				case 9: $row['ownertyp'] = 'Praca'; break;
				case 10: $row['ownertyp'] = 'Area'; break;
				case 11: $row['ownertyp'] = 'Door'; break;
				case 12: $row['ownertyp'] = 'Admin'; break;
				case 13: $row['ownertyp'] = 'Trup'; break;
				default: $row['ownertyp'] = 'Nieznany'; break;
			}

			$doors[] = $row;
		}


		$template = $this->registry->output->getTemplate('msrp')->msrp_admin_doors($doors, $pagination);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('Lista drzwi');
		$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin' );
		$this->registry->output->addNavigation( 'Lista drzwi', 'app=msrp&module=admin&section=doors' );
		$this->registry->getClass('output')->sendOutput();
	}

}
?>
