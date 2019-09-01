<?php
class public_msrp_gov_groupinfo extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
		require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/functions.php' );
		$this->registry->setClass( 'functions', new functions( $registry ) );
		$functions = $this->registry->getClass( 'functions' );

		require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/group.php' );
		$this->registry->setClass( 'group', new group( $registry ) );
		$group = $this->registry->getClass( 'group' );


    if(!($this->memberData['panel_perm'] & 2))
		{
			$this->registry->output->silentRedirect('index.php');
		}

		if(is_null($this->request['uid']))
		{
			$this->registry->output->showError('Wystąpił bład podczas przesyłania formularza.',0);
		}


		$this->DB->query('SELECT * FROM srv_groups WHERE `UID`='.$this->request['uid']);
		$this->DB->execute();
		$groupinfo=$this->DB->fetch();

    if($groupinfo['registered']==0)
    {
      $this->registry->output->showError('Brak dostępu do informacji - biznes nie jest zarejestrowany.',0);
    }

		$groupinfo['nickname']=str_replace("_", " ", $groupinfo['nickname']);
		$groupinfo['cash']-$functions->formatDollars($groupinfo['cash']);
		$groupinfo['grant']-$functions->formatDollars($groupinfo['grant']);
		$groupinfo['salary_account']-$functions->formatDollars($groupinfo['salary_account']);
		$groupinfo['type']=$group->getGroupType($groupinfo['type']);


    if(isset($_POST['confirm']))
    {
      $grant=intval($_POST['grant']);
			if($grant >= 0 && $grant <= 2000)
			{
	      $this->DB->query("UPDATE `srv_groups` SET `grant`=$grant WHERE `UID`=".$groupinfo['UID']);
	      $groupinfo['grant']=$grant;
			}
    }

		$this->DB->query('SELECT g.*, m.member_group_id, m.members_display_name,c.global_id,c.nickname,c.last_online,c.block FROM srv_groups_members g,members m, srv_characters c WHERE g.player_uid = c.player_uid AND c.global_id = m.member_id AND g.group_uid ='.$this->request['uid'].' ORDER BY g.permission DESC');
		$this->DB->execute();
		while($m=$this->DB->fetch())
		{
			$m['nickname']=str_replace("_", " ", $m['nickname']);

      if($row['block'] & 2)
  			$m['status'] = '<font color="red"><b>Ban</b></font>';
  		else if($row['block'] & 1)
  			$m['status'] = '<font color="grey"><b>Blokada Postaci</b></font>';
  		else if($row['block'] & 4)
  				$m['status'] = '<font color="grey"><b>Character Kill</b></font>';
  		else
  				$m['status'] = '<font color="green"><b>Aktywna</b></font>';

			$m['time'] = ''.intval($m['time']/3600).' h '.($m['time']%3600/60).' min';
			$members[]= $m;
		}

		$this->DB->query('SELECT * from srv_vehicles WHERE ownertyp=2 AND owner='.$this->request['uid']);
		$this->DB->execute();
		while($v=$this->DB->fetch())
		{
			$v['modelname']=$functions->getVehicleModelName($v['model']);
			$vehicles[]= $v;
		}

		$this->DB->query('SELECT * FROM srv_items WHERE ownertyp=2 AND `owner`='.$this->request['uid']);
		$this->DB->execute();
		while($item=$this->DB->fetch())
		{
			$item['type']=$functions->getItemTypeName($item['type']);
			$items[]=$item;
		}

		$query = $this->DB->query(sprintf('SELECT * FROM srv_cash_logs WHERE (type=2 AND to_uid = %d) OR (type=3 AND from_uid=%d) ORDER BY `time` DESC LIMIT 30',$this->request['uid'],$this->request['uid']));
		$this->DB->execute();
		while($row=$query->fetch_assoc())
		{
			$row['value']=$functions->formatDollars($row['value']);
			if($row['type']==2)
			{
				$row['from']=$functions->GetCharacterName($row['from_uid']);
				$row['to']=$functions->GetGroupName($row['to_uid']);
			}
			else {
				$row['to']=$functions->GetCharacterName($row['to_uid']);
				$row['from']=$functions->GetGroupName($row['from_uid']);
			}
			$cash[]=$row;
		}
		$query = $this->DB->query('SELECT g.member_id, c.global_id, c.nickname, l.* FROM srv_characters c, srv_group_offer_logs l, members g WHERE c.global_id = g.member_id AND c.player_uid = l.player_uid AND l.groupid = ' . $this->request['uid'] . ' ORDER BY l.time DESC LIMIT 50');
		while( $row =$query->fetch_assoc() )
		{
			$row['nickname'] = str_replace("_", " ", $row['nickname']);
			$logs[] = $row;
		}



		$template = $this->registry->output->getTemplate('msrp')->msrp_gov_groupinfo($groupinfo, $members, $vehicles, $items, $cash, $logs);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('Informacje o groupie');
		$this->registry->output->addNavigation( 'Panel rządowy', 'app=msrp&module=gov' );
		$this->registry->output->addNavigation( 'Informacje o grupie', 'app=msrp&module=gov&section=groupinfo&uid='.$this->request['uid'].'' );
		$this->registry->getClass('output')->sendOutput();
	}
}
?>
