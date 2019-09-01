<?php
class public_msrp_character_list extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
		if(!$this->memberData['member_id'])
		{
			$this->registry->output->showError('Niestety, nie jesteś zalogowany dlatego dostęp do tej części forum został zablokowany.',0);
		}
		if(($this->memberData['member_group_id']) < 3)
		{
			$this->registry->output->showError('Niestety, nie jesteś zalogowany dlatego dostęp do tej części forum został zablokowany.',0);
		}
			require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/functions.php' );
			$this->registry->setClass( 'functions', new functions( $registry ) );
			$functions = $this->registry->getClass( 'functions' );
			$this->DB->query('SELECT * FROM `srv_characters` WHERE `global_id` = '.$this->memberData['member_id'].'');
			$this->DB->execute();

		while($row = $this->DB->fetch())
		{
			$row['nickname'] = str_replace("_", " ", $row['nickname']);

			$row['cash']=$functions->formatDollars($row['cash']);
			$row['credit']=$functions->formatDollars($row['credit']);


			if($row['block'] & 2)
				$row['status'] = '<font color="red"><b>Ban</b></font>';
			else if($row['block'] & 1)
				$row['status'] = '<font color="grey"><b>Blokada Postaci</b></font>';
			else if($row['block'] & 4)
					$row['status'] = '<font color="grey"><b>Character Kill</b></font>';
			else
					$row['status'] = '<font color="green"><b>Aktywna</b></font>';
					$chars[] = $row;
		}


		//Ukrywanie postaci w profilu
		if(isset($this->request['hideChar']))
		{
			$this->DB->query('SELECT `global_id`, `hide`, `player_uid` FROM `srv_characters` WHERE `player_uid` = '.$this->request['uid'].'');
			$row = $this->DB->fetch();

			if($this->memberData['member_group_id'] != 4 && $this->memberData['member_group_id'] != 7)
			{
				if($row['global_id'] != $this->memberData['member_id'])
				{
					$this->registry->output->showError('Wybrana postać nie jest przypisana do Twojego konta globalnego.',0);
				}
				if(!$functions->isMemberPremium($this->memberData['member_id']))
				{
					$this->registry->output->showError('Opcja ukrycia postaci jest dostępna dla posiadaczy Konta Premium.',0);
					exit();
				}

			}

			if($row['hide']==1)
				$hide = 0;
			else
				$hide  = 1;


			$this->DB->query('UPDATE `srv_characters` SET `hide` = '.$hide.'  WHERE `player_uid` = '.$row['player_uid'].'');
			$this->registry->output->silentRedirect('index.php?app=msrp&module=character');
		}

		$template = $this->registry->output->getTemplate('msrp')->msrp_character($chars, $charss, $app);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('Lista Twoich postaci');
		$this->registry->output->addNavigation( 'Panel Gry', 'app=msrp' );
		$this->registry->output->addNavigation( 'Lista Twoich postaci', 'app=msrp&module=character' );
		$this->registry->getClass('output')->sendOutput();
	}
}
?>
