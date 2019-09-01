<?php

class public_msrp_group_legalweapons extends ipsCommand
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

		$result = $this->DB->query('SELECT w.*, i.name FROM `srv_legal_weapons` w LEFT JOIN `srv_items` i ON i.UID = w.`weapuid` ORDER BY w.`time` DESC ');
		while($row = $result->fetch_assoc())
		{
			$row['player_uid'] = $functions->GetCharacterName($row['player_uid'], $admin);
			$row['player_gid'] = $functions->GetMemberName($row['player_gid']);
			$row['seller_uid'] = $functions->GetCharacterName($row['seller_uid'], $admin);
			$logs[]=$row;
		}

		$this->registry->output->setTitle( 'Broń' );
		$this->registry->output->addNavigation( 'Panel Grupy', 'app=msrp&module=group' );
		$this->registry->output->addNavigation( 'Wydana broń', 'app=msrp&module=group&section=jaillogs&group='. $this->request['group'] .'&character='. $this->request['character'] );
		$this->registry->output->addContent( $this->registry->output->getTemplate( 'msrp' )->msrp_group_legal_weapons( $logs ) );
		$this->registry->output->sendOutput();
	}


}
