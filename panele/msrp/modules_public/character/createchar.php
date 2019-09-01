<?php

class public_msrp_character_createchar extends ipsCommand
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
		//-------------------------- WYŁCZONE NA CZAS TESTÓW
		/*
		if(!in_array($this->memberData['member_group_id'],[4,7,8,12])) {
			$this->registry->output->showError('Tworzenie postaci zostało tymczasowo wyłączone.',0);
		}
		*/
		//-------------------------------------------------------
		if( isset( $this->request['createChar'] ) )
		{
			$this->createCharacter( $this->request['firstname'], $this->request['surname'], $this->request['charsex'], $this->request['skin'], $this->reqest['age'] );
		}

		$man = $this->fetchSkins('1');
		$woman = $this->fetchSkins('0');

		$this->registry->output->addNavigation( 'Panel Gry', 'app=msrp' );
		$this->registry->output->addNavigation( 'Tworzenie postaci', 'app=msrp&module=character&section=createchar' );
		$this->registry->output->setTitle('Tworzenie postaci');
		$this->registry->output->addContent( $this->registry->output->getTemplate( 'msrp' )->msrp_createchar( $man, $woman ) );
		$this->registry->output->sendOutput();
	}

	public function createCharacter( $f, $s, $gender, $skin, $age )
	{
		$man = $this->fetchSkins('1');
		$woman = $this->fetchSkins('0');
		$age=intval($this->request['age']);

		if(!preg_match('/^[A-Za-z]+[a-z]$/',$f) || !preg_match('/^[A-Za-z]+[a-z]$/',$s))
		{
			$errors[] = 'Nazwa postaci nie jest prawidłowa. <br />';
		}

		if( strlen( trim( $this->DB->addSlashes( $f ) ) .'_'. trim( $this->DB->addSlashes( $s ) ) ) > 24 )
		{
			$errors[] = 'Nazwa postaci jest zbyt długa, może zawierać maksymalnie 24 znaki<br />';
		}
		//dodane
		if( strlen( trim( $this->DB->addSlashes( $f ) ) ) < 1 )
		{
			$errors[] = 'Nie wpisano imienia postaci.<br />';
		}
		if( strlen( trim( $this->DB->addSlashes( $s ) ) ) < 1 )
		{
			$errors[] = 'Nie wpisano nazwiska postaci. <br /> ';
		}
		if($age>90 ||$age<14)
		{
			$errors[] = 'Podany wiek wykracza poza dozwolony zakres.<br />';
		}
		if($this->request['skin'] = 0)
		{
			$errors[] = 'Nie wybrałeś/aś skina. <br />';
		}


		//koniec
		if( $gender == 0 && ! in_array( $skin,  $woman ) )
		{
			$errors[] = 'Nieprawdiłowy skin. <br />';
		}

		if( $gender == 1 && ! in_array( $skin,  $man ) )
		{
			$errors[] = 'Nieprawdiłowy skin. <br />';
		}
		//Sprawdzanie czy taka posta� istnieje ju� w �wiecie gry
		$this->DB->query("SELECT nickname FROM srv_characters WHERE nickname LIKE '". trim( $this->DB->addSlashes( $f ) ) .'_'. trim( $this->DB->addSlashes( $s ) ) ."'");
		$this->DB->execute();
		if($this->DB->getTotalRows() > 0)
		{
			$existing = $this->DB->fetch();
			$errors[] = 'Postać o padanych danych już istnieje.';
		}

		//blokada przed tworzeniem postaci zanim przegramy 10h (premium 3h)
		$db = ipsRegistry::DB();
		$db->query('SELECT player_uid FROM srv_characters, members WHERE member_id='.$this->memberData['member_id'].' AND global_id=member_id AND (premium<='.IPS_UNIX_TIME_NOW.' AND !(block & 1) AND !(block & 4) AND hours<10) OR member_id='.$this->memberData['member_id'].' AND global_id=member_id AND (!(block & 1) AND !(block & 4) AND hours<3)');
		//$db->query('SELECT `player_uid` FROM `srv_characters` WHERE `global_id`='.$this->memberData['member_id']);


		if($db->getTotalRows() > 0)
		{
			$this->registry->output->showError('Nie można założyć nowej postaci, możliwe powody:<br /><ul class="ipsPad_top bullets"><li><b>Któraś z Twoich postaci może mieć poniżej 10h (konta premium: 3h). <a href="index.php?app=msrp">Wróć do listy postaci.</a></b></li></ul>', 0);
			return;
		}

		if(count( $errors ))
		{
			$this->registry->output->showError( implode( $errors, '<br />' ) );
		}
		else
		{
			$f[0]=strtoupper($f[0]);
			$s[0]=strtoupper($s[0]);
			$name= trim( $this->DB->addSlashes( $f ) ) .'_'.trim( $this->DB->addSlashes( $s ));
			$this->DB->query('INSERT INTO `srv_characters` SET `global_id` = \''. $this->memberData['member_id'] .'\', `nickname` = \''.$name.'\', `age` =\''.$age.'\', `sex` = '. intval( $gender ) .', `skin` = '. intval( $skin ) .', `block` = 0');


			$this->registry->output->redirectScreen( 'Postać została stworzona.', $this->settings['base_url'] . 'app=msrp&module=character&section=list');
		}
	}

	public function fetchSkins( $what )
	{
	  $woman = array( '9', '10', '12', '13', '31', '39', '40', '41', '53', '55', '56', '63', '65', '69', '76', '88', '90', '91', '93', '130', '131', '141', '148', '150', '151', '152', '157', '169', '190', '191', '192', '193', '195', '196', '197', '198', '199', '211', '214', '215', '216', '219', '224', '225', '226', '233', '237', '263' );
		$man = array( '3', '7', '15', '17', '20', '21', '23', '25', '29', '33', '37', '44', '46', '58', '59', '60', '62', '72', '94', '95', '98', '101', '113', '117', '119', '120', '123', '124', '126', '161', '170', '177', '180', '184', '185', '186', '188', '217', '223', '228', '235', '240', '250', '258', '290', '294', '296', '299' );

		switch( $what )
		{
			case 0: return $woman;
			case 1: return $man;
		}
	}

}
