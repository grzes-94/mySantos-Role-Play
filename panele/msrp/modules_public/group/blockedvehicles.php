<?php

class public_msrp_group_blockedvehicles extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
		require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/group.php' );
		$this->registry->setClass( 'group', new group( $registry ) );
		$group = $this->registry->getClass( 'group' );

		require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/functions.php' );
		$this->registry->setClass( 'functions', new functions( $registry ) );
		$functions = $this->registry->getClass( 'functions' );

		$group->checkCharacterAndGroup( intval( $this->request['group'] ), intval( $this->request['character'] ), $this->memberData['member_id'] );

		if($this->request['group'] != 2)
		{
			$this->registry->output->showError('Wybrana grupa nie posiada dostępu.',0);
		}
		$admin = $functions->IsGruopAdmin($this->memberData['member_group_id']);

		$result = $this->DB->query('SELECT * FROM `srv_vehicles` WHERE `block`>0');
		while($row = $result->fetch_assoc())
		{
			if($row['ownertyp']==1)
			{
				$this->DB->query("SELECT last_online FROM srv_characters WHERE player_uid=".$row['owner']);
				$res=$this->DB->fetch();
				$row['lastonline']=$res['last_online'];
				$row['owner']=$functions->GetCharacterName($row['owner'],$functions->IsGruopAdmin($this->memberData['member_group_id']));

			}
			elseif ($row['ownertyp']==2)
			{
				$row['owner']=$functions->GetGroupName($row['owner'],$functions->IsGruopAdmin($this->memberData['member_group_id']));
			}
			$row['name']=$functions->getVehicleModelName($row['model']);
			$row['block'] = "$ ".$functions->formatDollars($row['block']);
			$logs[]=$row;
		}

		$this->registry->output->setTitle( 'Pojazdy z blokadą' );
		$this->registry->output->addNavigation( 'Panel Grupy', 'app=msrp&module=group' );
		$this->registry->output->addNavigation( 'Poazdy z blokadą', 'app=msrp&module=group&section=jaillogs&group='. $this->request['group'] .'&character='. $this->request['character'] );
		$this->registry->output->addContent( $this->registry->output->getTemplate( 'msrp' )->msrp_group_blockedvehicles( $logs ) );
		$this->registry->output->sendOutput();
	}


}
