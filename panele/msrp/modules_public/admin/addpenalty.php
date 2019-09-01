<?php
class public_msrp_admin_addpenalty extends ipsCommand
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


		if(! $functions->IsGruopAdmin($this->memberData['member_group_id'],true))
		{
			$this->registry->output->silentRedirect('index.php');
		}
		if(!isset($this->request['uid']))
		{
			$this->registry->output->showError("Wystapił błąd podczas pobierania formularza.",0);
		}

		$this->DB->query('SELECT `player_uid`, `global_id`,`nickname`,`block`,`nogun`,`norun`,`nocar`,`noooc`,`logged` FROM `srv_characters` WHERE `player_uid` = '.$this->request['uid']);
		$character = $this->DB->fetch();

		$this->DB->query('SELECT `aj`, `warn`,`curse` FROM `members` WHERE `member_id` = '.$character['global_id']);
		$member= $this->DB->fetch();
		$curse=($member['curse']>IPS_UNIX_TIME_NOW);


		$nick=$functions->getCharacterName($this->request['uid'],true);

		$memberid=$character['global_id'];


		if(empty($character))
		$this->registry->output->showError("Nie znaleziono postaci o podanym UID.",0);

		$this->DB->query( 'SELECT * FROM srv_penalty WHERE player_gid = '.$character['global_id'].' ORDER BY `time` DESC LIMIT 10');
		while( $row = $this->DB->fetch() )
		{
			$row['type'] = $functions->getPenaltyName( $row['type'] );
			$logs[] = $row;
		}


		if(!empty($_POST['addpenalty']))
		{
			$type=$_POST['type'];
			$value=$_POST['value'];
			$reason=$_POST['reason'];

			if(!$type || $type==2 || $type==12 || $type > 13)
			$this->registry->output->showError("Niepoprawny typ kary",0);
			if(strlen($reason) < 1 )
			$this->registry->output->showError("Nie wprowadzono powodu nadania kary",0);



			$this->DB->query("SELECT `logged` FROM `srv_characters` WHERE `player_uid`=".$this->request['uid']);
			$islogged = $this->DB->fetch();
			if($islogged['logged'])
				$this->registry->output->showError("Postać jest online.",0);

			$reason=htmlentities($reason);
			$reason=mysql_escape_string($reason);

			switch($type)
			{
				case 1:
				{
					if($member['warn']>=4)
					$this->registry->output->showError("Wybrany gracz posiada już więcej niż 4 warny.",0);

					if($member['warn']==3 || $curse)
					{
						if($curse)
						$type=14;
						else
						$type=12;

						if(!($character['block'] & 2))
							$this->DB->query("UPDATE `srv_characters` SET `block`=`block`+2 WHERE `player_uid`=".$this->request['uid']);
						$this->DB->query("UPDATE `members` SET `warn`=`warn`+1 WHERE `member_id`=".$memberid);

					}
					else if($member['warn']<3)
					$this->DB->query("UPDATE `members` SET `warn`=`warn`+1 WHERE `member_id`=".$memberid);


					break;
				}
				case 3:
				{
					if(!($character['block'] & 2))
						$this->AddBan($this->request['uid'],$character['global_id']);
					else
					 	$this->registry->output->showError("Wybrany postać posiada już banicję.",0);
						break;
				}
				case 4:
				{
					if(!($character['block'] & 1))
						$this->DB->query("UPDATE `srv_characters` SET `block`=`block`+1 WHERE `player_uid`=".$this->request['uid']);
					else
					 	$this->registry->output->showError("Wybrany postać posiada jest już zablokowana.",0);
						break;
				}
				case 5:
				{
					if($value<1 || $value>50)
					$this->registry->output->showError("Niepoprawna wartość gamescore. Dozwolony zakres 1-50.",0);

					$this->DB->query("UPDATE `members` SET `score`=`score`+$value WHERE `member_id`=".$memberid);
					break;
				}
				case 6:
				{
					if($value<1 || $value>1000)
					$this->registry->output->showError("Niepoprawna wartość. Dozwolony zakres 1-1000.",0);
					if($member['aj'])
						$this->registry->output->showError("Wybrana postac posiada już AdminJaila.",0);

					if($curse)
					{
						$this->AddBan($this->request['uid'],$character['global_id']);
						$type=14;
					}

					$this->DB->query("UPDATE `members` SET `aj`=".($value*60)." WHERE `member_id`=".$memberid);

					break;
				}
				case 7:
				{
					$value=0;
					if($member['warn']<1)
						$this->registry->output->showError("Wybrana postać nie posiada aktywnych ostrzeżeń.",0);

					$this->DB->query("UPDATE `members` SET `warn`=`warn`-1 WHERE `member_id`=".$memberid);

					break;
				}
				case 8:
				case 9:
				case 10:
				case 11:
				{
					if($type==8) $what="norun";
					else if($type==9) $what="nogun";
					else if($type==10) $what="nocar";
					else if($type==11) $what="noooc";
					if($value<1 || $value>1000)
					$this->registry->output->showError("Niepoprawna wartość. Dozwolony zakres 1-1000.",0);
					if($character[$what])
						$this->registry->output->showError("Postac posiada już wybraną karę.",0);

					if($curse && $value>30 && !($character['block'] & 2))
					{
						$this->DB->query("UPDATE `srv_characters` SET `block`=`block`+2 WHERE `player_uid`=".$this->request['uid']);
						$type=14;
					}
					else
						$this->DB->query("UPDATE `srv_characters` SET `$what`=".($value*60)." WHERE `player_uid`=".$this->request['uid']);
					break;
				}
				case 13:
				{
					if($curse)
						$this->registry->output->showError("Gracz posiada już aktywną klątwę.",0);
					if($value<1 || $value>1000)
					$this->registry->output->showError("Niepoprawna wartość. Dozwolony zakres 1-1000.",0);
					$time=IPS_UNIX_TIME_NOW;
					$this->DB->query("UPDATE `members` SET `curse`=".(IPS_UNIX_TIME_NOW+ $value*86400)." WHERE `member_id`=".$memberid);
					break;
				}
				default:
				$value =0;
			}
			$this->DB->query("INSERT INTO `srv_penalty` VALUES (NULL, ".$this->request['uid'].", $memberid, ".$this->memberData['member_id'].", ".IPS_UNIX_TIME_NOW.", $type, $value, \"$reason\" )");
			$this->registry->output->redirectScreen( 'Kara została dodana.', $this->settings['base_url'].'app=msrp&module=admin&section=addpenalty&uid=' .$this->request['uid']);


			//echo "Typ: $type, wartość: $value, powód: $reason";
			//	exit();
		}


		$template = $this->registry->output->getTemplate('msrp')->msrp_admin_addpenalty($character,$member,$nick,$logs);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('Panel kar');
		$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin' );
		$this->registry->output->addNavigation( 'Dodaj karę', 'app=msrp&module=admin&section=addpenalty&uid='.$this->request['uid'].'' );
		$this->registry->getClass('output')->sendOutput();
	}

	private function AddBan($uid,$gid)
	{
		$this->DB->query("UPDATE `srv_characters` SET `block`=`block`|2 WHERE `player_uid`=".$uid);
		$this->DB->query("SELECT `ip` FROM `srv_login_logs` WHERE `character_id`=$uid ORDER BY `time` LIMIT 1");
		$res=$this->DB->fetch();
		$ip=$res['ip'];
		$this->DB->query("INSERT INTO `srv_bans` VALUES (NULL,'$ip','$gid')");
	}


}
