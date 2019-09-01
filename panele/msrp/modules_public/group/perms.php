<?php

class public_msrp_group_perms extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
		require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/group.php' );
		$this->registry->setClass( 'group', new group( $registry ) );
		$group = $this->registry->getClass( 'group' );

		$group->checkCharacterAndGroup( intval( $this->request['group'] ), intval( $this->request['character'] ), $this->memberData['member_id'], false );
		$information = $group->fetchGroupInformation( intval( $this->request['group'] ) );
		$groupid=$this->request['group'];

		if(!empty($_POST['yes']))
	  {
			$memberid=$_POST['memberid'];
	    $this->DB->query('DELETE FROM `srv_groups_members` WHERE `player_uid`='.$memberid." AND `group_uid`=$groupid");
	  }

		$permissions = array(
			128 => '<span data-tooltip="Zarządzanie pracownikami"> P </span>',
			64 => '<span data-tooltip="Zarządzanie finansami"> $ </span>',
			32 => '<span data-tooltip="Zarządzanie pojazdami"> MV </span>',
			16 => '<span data-tooltip="Zarządzanie produktami"> PR </span>',
			8 => '<span data-tooltip="Dostęm do magazynu"> M </span>',
			4 => '<span data-tooltip="Zarządzanie obiektami"> O </span>',
			2 => '<span data-tooltip="Dostęp do drzwi"> D </span>',
			1 => '<span data-tooltip="DOstęp do pojazdów"> V </span>',
		);

		$members = $this->fetchMembers( $this->request['group'] );

		if( isset( $this->request['updatePerms'] ) )
		{
			$this->updatePermissions($groupid);
		}



		$this->registry->output->setTitle( 'Zarządzanie grupami' );
		$this->registry->output->addNavigation( 'Panel Grupy', 'app=msrp&module=group' );
		$this->registry->output->addNavigation( ''. $information['name'] .' (UID: '. $information['UID'] .')', 'app=msrp&module=group&section=ranks&group='. $this->request['group'] .'&character='. $this->request['character'] );
		$this->registry->output->addContent( $this->registry->output->getTemplate( 'msrp' )->msrp_group_perms($members,$permissions,$groupid) );
		$this->registry->output->sendOutput();
	}

	protected function fetchMembers( $group )
	{
		$this->DB->query('SELECT c.global_id, c.nickname, m.* FROM srv_characters c, srv_groups_members m WHERE  c.player_uid = m.player_uid AND c.logged = 0 AND m.group_uid = ' . $group . ' ORDER BY m.permission DESC');

		while( $row = $this->DB->fetch() )
		{
			$row['nickname'] = str_replace("_", " ", $row['nickname']);

			$members[] = $row;
		}

		return $members;
	}
	protected function updatePermissions($groupid)
		{

			foreach( $this->request['rank'] as $id => $value)
			{
				if(! $this->isMemberInGroup($id, $groupid))
				{
					$this->registry->output->showError( 'Wystapił bład podczas przesyłania formularza.' );
					exit();
				}


				$perm= $this->packMemberPermissions( $value['perms'] );

				$q=$this->DB->query("SELECT m.global_id FROM `srv_groups` g, `srv_characters` m WHERE g.`UID`=$groupid AND m.global_id = g.leader");
				$result=$this->DB->fetch();
				$leader=intval($result['global_id']);
				if($this->memberData['member_id'] != $leader)
				{
					$q=$this->DB->query("SELECT `permission` FROM `srv_groups_members` WHERE `id`=$id");
					$result=$this->DB->fetch();
					$memberPerm=intval($result['permission']);
					if($memberPerm & 64 && !($perm & 64))
						$prem +=64;
					else if(!($memberPerm & 64) && $perm & 64)
						$perm -=64;

				}




				$this->DB->query('UPDATE `srv_groups_members` SET `rank` = ' . intval( $value['rank'] ) . ',`rank_name` = "' . $value['rankname'] . '" ,`skin` = ' . intval( $value['skin'] ) . ', `salary` = ' . intval( $value['salary'] ) . ', commission = ' .  intval( $value['commission'] ) .' , `permission`='.$perm.' WHERE `id` = ' . $id . '');
			}

			$this->registry->output->redirectScreen( 'Ustawienia zostały zapisane.', $this->settings['base_url'] . 'app=msrp&module=group&section=perms&group=' . $this->request['group'] . '&character=' . $this->request['character'] . '' );
		}

		protected function packMemberPermissions( $newGlobalPermissionSet )
		{
			$return = 0;

			if( count( $newGlobalPermissionSet ) )
			{
				foreach($newGlobalPermissionSet as $key => $val)
				{
					if($val)
					{
						$return += intval( $key );
					}
					else $return = 0;
				}
			}

			return $return;
		}

		protected function isMemberInGroup($id, $groupid)
		{
			$this->DB->query('SELECT `player_uid` FROM `srv_groups_members` WHERE `id` ='.$id.' AND `group_uid`='.$groupid);
			return ($this->DB->getTotalRows());
		}

}
