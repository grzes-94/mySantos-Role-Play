<?php
class public_msrp_admin_editchar extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{

		if(!$this->memberData['member_id'])
		{
			$this->registry->output->showError('Niestety, nie jesteś zalogowany dlatego dostęp do tej części forum został zablokowany.',0);
		}
		require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/functions.php' );
		$this->registry->setClass( 'functions', new functions( $registry ) );
		$functions = $this->registry->getClass( 'functions' );


		if(! $functions->IsGruopAdmin($this->memberData['member_group_id']))
		{
			$this->registry->output->showError("Nie posiadasz uprawnień do edycji postaci. Twój krawat jest za mały.",0);
		}
		/* Postacie */
		if(isset($this->request['uid']))
		{
				$this->DB->query('SELECT c.*, m.warn FROM `srv_characters` c LEFT JOIN `members` m ON c.`global_id`=m.`member_id` WHERE c.`player_uid` = '.$this->request['uid']);
				$row = $this->DB->fetch();
		}
		else
			$this->registry->output->showError("Wystapił błąd podczas pobierania formularza.",0);




		//BUTTON
		if(!empty($_POST['updateChar']))
		{
			$row['nickname']= str_replace("_", " ", $row['nickname']);
			$this->DB->query('INSERT INTO `panel_admin_log` (`owner`, `log`, `date`) VALUES ('.$this->memberData['member_id'].', "Edytował postać '.$row['nickname'].'['.$row['player_uid'].'] pomyślnie.", "'.IPS_UNIX_TIME_NOW.'")');
			$this->DB->execute();

			$block=$_POST['block'];
			$blockval=0;
			foreach($block as $x)
			{
				$blockval += $x;
			}
			if($this->memberData['panel_perm'] & 1 && $this->memberData['member_group_id'] == 4)
				$this->DB->query('UPDATE `srv_characters` SET `nickname` = "'.$_POST['nickname'].'", `admin` = '.$_POST['admin'].', `age` = '.$_POST['age'].', `hours` = '.$_POST['hours'].', `credit`= '.$_POST['credit'].', `sex` = '.$_POST['sex'].', `cash` = '.$_POST['cash'].', `skin` = '.$_POST['skin'].', `hp` = '.$_POST['hp'].', `glod` = '.$_POST['glod'].', `nocar` = '.$_POST['nocar'].', `nogun` = '.$_POST['nogun'].', `noooc` = '.$_POST['noooc'].', `nogun` = '.$_POST['nogun'].', `block` = '.$blockval.' WHERE `player_uid` = '.$this->request['uid'].'');
			else if($this->memberData['member_group_id'] == 7 || $this->memberData['member_group_id'] == 4)
				$this->DB->query('UPDATE `srv_characters` SET  `age` = '.$_POST['age'].', `sex` = '.$_POST['sex'].', `skin` = '.$_POST['skin'].', `hp` = '.$_POST['hp'].', `glod` = '.$_POST['glod'].', `nocar` = '.$_POST['nocar'].', `nogun` = '.$_POST['nogun'].', `noooc` = '.$_POST['noooc'].', `nogun` = '.$_POST['nogun'].',  `block` = '.$blockval.' WHERE `player_uid` = '.$this->request['uid'].'');
			else {
				$this->registry->output->showError('Nie posiadasz uprawnień do edycji postaci.',0);
			}

			$this->registry->output->silentRedirect('index.php?&app=msrp&module=character&section=showchar&uid='.$this->request['uid']);
		}

		if($this->request['uid'] != $row['player_uid'])
		{
			$this->registry->output->showError('A ty kurwa czego tu?',0);
		}


		/* Przedmioty */

		$this->DB->query('SELECT * FROM `srv_items` WHERE `owner` = '.$this->request['uid'].' AND `ownertyp` = 1 ORDER by `uid`');
		$this->DB->execute();

		while($item = $this->DB->fetch())
		{
			$item['type']= $functions->getItemTypeName($item['type']);
			$items[] = $item;
		}
		/* Pojazdy */

		$this->DB->query('SELECT * FROM `srv_vehicles` WHERE `owner` = '.$this->request['uid'].' AND `ownertyp` = 1 ORDER by `uid` DESC LIMIT 20');
		$this->DB->execute();

		while($veh = $this->DB->fetch())
		{
			$veh['distance'] 	= sprintf("%01.2f", $veh['distance']);
			$veh['HP'] 			= sprintf("%01.2f", $veh['HP']);
			$vehs[] = $veh;
		}

		/* Drzwi */

		$this->DB->query('SELECT * FROM `srv_doors` WHERE `ownertyp` = 1 AND `owner` = '.$this->request['uid'].' ORDER by `uid` DESC LIMIT 20');
		$this->DB->execute();

		while($door = $this->DB->fetch())
		{
			$doors[] = $door;
		}

		/* Logi */

		$this->DB->query('SELECT * FROM `srv_login_logs` WHERE `character_id` = '.$this->request['uid'].' ORDER by `time` DESC LIMIT 30');
		$this->DB->execute();

		while($log = $this->DB->fetch())
		{
			$logs[] = $log;
		}

		$template = $this->registry->output->getTemplate('msrp')->msrp_admin_editchar($row, $logs, $vehs, $chars, $doors, $items);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('Postać '.str_replace("_", " ", $row['nickname']).'');
		$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin' );
		$this->registry->output->addNavigation( 'Postać '.str_replace("_", " ", $row['nickname']).'', 'app=msrp&module=admin&section=editchar&uid='.$this->request['uid'].'' );
		$this->registry->getClass('output')->sendOutput();
	}

}
?>
