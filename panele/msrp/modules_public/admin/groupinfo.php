<?php
class public_msrp_admin_groupinfo extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
		require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/functions.php' );
		$this->registry->setClass( 'functions', new functions( $registry ) );
		$functions = $this->registry->getClass( 'functions' );

		require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/group.php' );
		$this->registry->setClass( 'group', new group( $registry ) );
		$group = $this->registry->getClass( 'group' );


		if(! $functions->IsGruopAdmin($this->memberData['member_group_id'],true))
		{
			$this->registry->output->silentRedirect('index.php');
		}

		if(is_null($this->request['uid']))
		{
			$this->registry->output->showError('Wystąpił bład podczas pobierana formularza.',0);
		}


		$this->DB->query('SELECT * FROM srv_groups WHERE `UID`='.$this->request['uid']);
		$this->DB->execute();
		$groupinfo=$this->DB->fetch();

		$groupinfo['nickname']=str_replace("_", " ", $groupinfo['nickname']);
		$groupinfo['cash']-$functions->formatDollars($groupinfo['cash']);
		$groupinfo['type']=$group->getGroupType($groupinfo['type']);

		$this->DB->query('SELECT g.*, m.member_group_id, m.members_display_name,c.global_id,c.nickname FROM srv_groups_members g,members m, srv_characters c WHERE g.player_uid = c.player_uid AND c.global_id = m.member_id AND g.group_uid ='.$this->request['uid'].' ORDER BY g.permission DESC');
		$this->DB->execute();
		while($m=$this->DB->fetch())
		{
			$m['nickname']=str_replace("_", " ", $m['nickname']);

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



		$template = $this->registry->output->getTemplate('msrp')->msrp_admin_groupinfo($groupinfo, $members, $vehicles, $items);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('Informacje o groupie');
		$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin' );
		$this->registry->output->addNavigation( 'Informacje o grupie', 'app=msrp&module=admin&section=groupinfo&uid='.$this->request['uid'].'' );
		$this->registry->getClass('output')->sendOutput();
	}
}
?>
