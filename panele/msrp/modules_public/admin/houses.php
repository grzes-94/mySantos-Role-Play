<?php
class public_msrp_admin_houses extends ipsCommand
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
    $count = $this->DB->query('SELECT COUNT(*) as max FROM srv_doors WHERE `ownertyp`=1');
    $count = $this->DB->fetch($count);

    $pagination = $this->registry->getClass('output')->generatePagination( array(
                                  'totalItems'		=> $count['max'],
                                  'itemsPerPage'		=> 50,
                                  'baseUrl'			=> "app=msrp&module=admin&section=houses",
                                  )
                              );

		$query = $this->DB->query(sprintf('SELECT * FROM `srv_doors` WHERE `ownertyp`=1 LIMIT %d,50',$this->request['st']));

		while($row = $query->fetch_assoc())
		{
      $q = $this->DB->query(sprintf('SELECT `last_online`,`block` FROM `srv_characters` WHERE `player_uid`=%d',$row['owner']));
      $online = $q->fetch_assoc();
      $row['last_online'] = $online['last_online'];
			if($online['block'] & 2)
				$row['status'] = '<font color="red"><b>Ban</b></font>';
			else if($online['block'] & 1)
				$row['status'] = '<font color="grey"><b>Blokada Postaci</b></font>';
			else if($online['block'] & 4)
					$row['status'] = '<font color="grey"><b>Character Kill</b></font>';
			else
					$row['status'] = '<font color="green"><b>Aktywna</b></font>';

      $row['owner'] = $functions->GetCharacterName($row['owner'],true);

			$doors[] = $row;
		}



		$template = $this->registry->output->getTemplate('msrp')->msrp_admin_houses($doors, $pagination);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('Lista domów');
		$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin' );
		$this->registry->output->addNavigation( 'Lista domów', 'app=msrp&module=admin&section=houses' );
		$this->registry->getClass('output')->sendOutput();
	}

}
?>
