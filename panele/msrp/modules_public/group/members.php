<?php

class public_msrp_group_members extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
		require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/group.php' );
		$this->registry->setClass( 'group', new group( $registry ) );
		$group = $this->registry->getClass( 'group' );

		$group->checkCharacterAndGroup( intval( $this->request['group'] ), intval( $this->request['character'] ), $this->memberData['member_id'] );
		$information = $group->fetchGroupInformation( intval( $this->request['group'] ) );

		$members = $this->fetchMembers( $this->request['group'] );

		if(isset( $this->request['updateMembers'] ))
		{
			$this->UpdateMembers( $group );
		}

		if(isset( $this->request['add'] ))
		{
			$this->addMember( $this->request['char_name'], $this->request['group'] );
		}

		$this->registry->output->setTitle( 'Zarządzanie pracownikami' );
		$this->registry->output->addNavigation( 'Panel Grupy', 'app=msrp&module=group' );
		$this->registry->output->addNavigation( ''. $information['name'] .' (UID: '. $information['UID'] .')', 'app=msrp&module=group&section=members&group='. $this->request['group'] .'&character='. $this->request['character'] );
		$this->registry->output->addContent( $this->registry->output->getTemplate( 'msrp' )->msrp_group_members( $information, $members, $ranks ) );
		$this->registry->output->sendOutput();
	}



	protected function UpdateMembers( $group )
	{
		$group->checkCharacterAndGroup( intval( $this->request['group'] ), intval( $this->request['character'] ), $this->memberData['member_id'] );

		foreach($this->request['member'] as $member=>$newData)
		{
			$this->DB->query('UPDATE `srv_groups_members` SET  `skin` = "' . ($newData['skin']) . '" WHERE `player_uid` = ' . intval($member) . ' AND `group_uid` = ' . $this->request['group'] . '');
		}

		$this->registry->output->redirectScreen( 'Ustawienia zostały zapisane.', $this->settings['base_url'] . 'app=msrp&module=group&section=members&group=' . $this->request['group'] . '&character=' . $this->request['character'] . '' );
	}

	protected function fetchMembers( $group )
	{
		$this->DB->query('SELECT g.member_id, g.members_seo_name, g.members_display_name, g.member_group_id, c.global_id, c.nickname,c.block,c.last_online, m.* FROM srv_characters c, srv_groups_members m, members g WHERE c.global_id = g.member_id AND c.player_uid = m.player_uid AND m.group_uid = ' . $group . ' ORDER BY m.time DESC');

		while( $row = $this->DB->fetch() )
		{
			$row['nickname'] = str_replace("_", " ", $row['nickname']);

			if($row['block'] & 2)
				$row['status'] = '<font color="red"><b>Ban</b></font>';
			else if($row['block'] & 1)
				$row['status'] = '<font color="grey"><b>Blokada Postaci</b></font>';
			else if($row['block'] & 4)
					$row['status'] = '<font color="grey"><b>Character Kill</b></font>';
			else
					$row['status'] = '<font color="green"><b>Aktywna</b></font>';

			$row['group_hours'] = floor(($row['time'] / 60) / 60);
			$row['group_minutes'] = floor($row['time'] / 60 % 60);

			$members[] = $row;
		}

		return $members;
	}

}
