<?php
class public_msrp_character_showchar extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
		require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/functions.php' );
		$this->registry->setClass( 'functions', new functions( $registry ) );
		$functions = $this->registry->getClass( 'functions' );
	    if(!$this->memberData['member_id'])
		{
			$this->registry->output->showError('Niestety, nie jesteś zalogowany dlatego dostęp do tej części forum został zablokowany.',0);
		}


		/* Postacie */
		$this->DB->query("SELECT c.*, m.premium, m.warn,m.curse,m.aj FROM srv_characters c LEFT JOIN members m ON m.member_id=c.global_id WHERE `player_uid` = ".$this->request['uid']." LIMIT 1");
		$row = $this->DB->fetch();

		if(!$functions->IsGruopAdmin($this->memberData['member_group_id'],true) && $this->memberData['member_id']!=$row['global_id'])
		{
			$this->registry->output->showError('Nie posiadasz uprawnień do podglądu tej postaci.',0);
		}

		if($row['block'] & 2)
			$row['status'] = '<font color="red"><b>Ban</b></font>';
		else if($row['block'] & 1)
			$row['status'] = '<font color="grey"><b>Blokada Postaci</b></font>';
		else if($row['block'] & 4)
				$row['status'] = '<font color="grey"><b>Character Kill</b></font>';
		else
				$row['status'] = '<font color="green"><b>Aktywna</b></font>';

		$row['nickname'] = str_replace("_", " ", $row['nickname']);

		$row['cash']=$functions->formatDollars($row['cash']);
		$row['credit']=$functions->formatDollars($row['credit']);
		$row['onlineToday'] = floor($row['online_today']/3600)." h ".round(($row['online_today']%3600)/60)." min";

		if(!$row['logged'])
			$row['ingame']='<span class="ipsBadge ipsBadge_grey" >Offline</span>';
		else
			$row['ingame']='<span class="ipsBadge ipsBadge_green">Online</span>';

		if($row['premium'] < time() && $row['premium']>=0)
			$row['ispremium'] = '<span class="ipsBadge ipsBadge_grey" >Konto standard</span>';
		else
			$row['ispremium'] = '<span class="ipsBadge" style="background:#FFBB00">Konto premium</span>';







        /* Przedmioty */

		$this->DB->query('SELECT * FROM `srv_items` WHERE `owner` = '.$this->request['uid'].' AND `ownertyp` = 1 ORDER by `uid` DESC');
		$this->DB->execute();

		while($item = $this->DB->fetch())
		{
			$item['type'] = $functions->getItemTypeName($item['type']);

			$items[] = $item;
		}
		/* Pojazdy */

		$this->DB->query('SELECT * FROM `srv_vehicles` WHERE `owner` = '.$this->request['uid'].' AND `ownertyp` = 1 ORDER by `uid` ASC LIMIT 20');
		$this->DB->execute();

		while($veh = $this->DB->fetch())
		{
			$veh['distance'] 	= sprintf("%01.2f", $veh['distance']);
			$veh['HP'] 			= sprintf("%01.2f", $veh['HP']);
			$veh['modelname'] = $functions->getVehicleModelName( $veh['model']);
			$vehs[] = $veh;
		}

		/* Drzwi */

		$this->DB->query('SELECT * FROM `srv_doors` WHERE (`ownertyp` = 3 OR  `ownertyp` = 1) AND `owner` = '.$this->request['uid'].' ORDER by `uid` DESC LIMIT 20');
		$this->DB->execute();

		while($door = $this->DB->fetch())
		{
			$doors[] = $door;
		}

		$this->DB->query('SELECT m.*, g.name FROM srv_groups_members m, srv_groups g WHERE m.group_uid = g.UID AND m.player_uid='.$this->request['uid'].'');
		$this->DB->execute();

		while($group = $this->DB->fetch())
		{
			$groups[]=$group;
		}

		$template = $this->registry->output->getTemplate('msrp')->msrp_showchar($row, $logs, $vehs, $chars, $doors, $items, $groups);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('Postać '.str_replace("_", " ", $row['nickname']).'');
		$this->registry->output->addNavigation( 'Panel Gry', 'app=msrp' );
		$this->registry->output->addNavigation( 'Postać '.str_replace("_", " ", $row['nickname']).'', 'app=msrp&modules=character&section=showchar&uid='.$this->request['uid'].'' );
		$this->registry->getClass('output')->sendOutput();
	}

}
?>
