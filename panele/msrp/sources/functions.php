<?php
class functions
{
	protected $registry;
	protected $DB;
	protected $settings;
	protected $request;
	protected $memberData;
	public $playersOnline = 5;

	public function __construct( ipsRegistry $registry )
	{
		$this->registry		=  $registry;
		$this->DB			=  $this->registry->DB();
		$this->settings		=& $this->registry->fetchSettings();
		$this->request		=& $this->registry->fetchRequest();
		$this->memberData	=& $this->registry->member()->fetchMemberData();
	}
	public function formatDollars($dollars)
	{
	    $formatted = number_format(sprintf('%d', preg_replace("/[^0-9.]/", "", $dollars)), 0);
	    return $dollars < 0 ? "({$formatted})" : "{$formatted}";
	}

	public function IsGruopAdmin( $groupid , $gm = false)
	{
		if($gm)
		{
			if($groupid == 4 || $groupid == 7 || $groupid == 8 || $groupid==11)
				return true;
		}
		else
		{
			return ($groupid == 4 || $groupid == 7);
		}
	}
	public function GetCharacterName($id,$link=false)
	{
		$this->DB->query('SELECT `nickname` FROM `srv_characters` WHERE `player_uid` ='.$id);
		$name=$this->DB->fetch();
		if(!$link)
			return str_replace("_", " ", $name['nickname']);
		else
		{
				$nick=str_replace("_", " ", $name['nickname']);
				return '<a href="index.php?&app=msrp&module=character&section=showchar&uid='.$id.'">'.$nick.'</a>';
		}
	}
	public function GetGroupName($uid,$link=false)
	{
		$this->DB->query('SELECT `name` FROM `srv_groups` WHERE `UID` ='.$uid);
		$name=$this->DB->fetch();
		if(!$link)
			return $name['name'];

		return '<a href="index.php?&app=msrp&module=admin&section=groupinfo&uid='.$uid.'">'. $name['name'].'</a>';
	}
	public function GetMemberName($uid)
	{
		$this->DB->query('SELECT `member_group_id`, `members_display_name` FROM `members` WHERE `member_id` ='.$uid);
		$name=$this->DB->fetch();
		$name = IPSMember::makeNameFormatted( $name['members_display_name'],$name['member_group_id'] );
		$name = '<a href="index.php?showuser='.$uid.'">'.$name.'</a>';
		return $name;
	}
	public function GetOnlinePlayersNumber()
	{
		$this->DB->query('SELECT COUNT(*) as `online` FROM `srv_characters` WHERE `logged`=1');
		$row=$this->DB->fetch();
		return intval($row['online']);

	}
	public function isMemberPremium($memberid)
	{
		$tmie = time();
		$this->DB->query("SELECT `member_group_id`, `mgroup_others` FROM `members` WHERE `member_id` = $memberid ");
		$res=$this->DB->fetch();
		return ( $res['member_group_id'] == 9 || in_array(9, explode(',', $res['mgroup_others'])) );
	}
	public function getGroupType($group)
	{
		$grouptype = array(
						'0'	=>	'--',
						'1'	=>	'Government',
						'2'	=>	'Police Department',
						'3'	=>	'Medyczna',
						'4'	=>	'Radio',
						'5'	=>	'FBI',
						'6'	=>	'Wojsko',
						'7'	=>	'Gang',
						'8'	=>	'Mafia',
						'9'	=>	'Szajka zmotoryzowana',
						'10'	=>	'Sklep',
						'11'	=>	'Warsztat',
						'12'	=>	'Taxi',
						'13'	=>	'Ochrona',
						'14'	=>	'Komis samochodowy',
						'15'	=>	'Logistyka',
						'16'	=>	'Bank',
						'17'	=>	'Siłownia',
						'18'	=>	'Restauracja',
						'19'	=>	'Stacja benzynowa',
						'20'	=>	'Syndykat',
						'21'	=>	'Kasyno',
						'22'	=>	'Kartel' );

		return $grouptype[ $group ];
	}

	public function getWeaponName( $weapon )
	{
		switch($weapon)
		{
			case 1: return "Kastet";
			case 2: return "Kij golfowy";
			case 3: return "Pałka";
			case 4: return "Nóż";
			case 5: return "Baseball";
			case 6: return "Łopata";
			case 7: return "Kij bilardowy";
			case 8: return "Katana";
			case 9: return "Piła łańcuchowa";
			case 10: return "Podwójny dildos";
			case 11: return "Dildo";
			case 12: return "Wibrator";
			case 13: return "Wibrator";
			case 14: return "Kwiatki";
			case 15: return "Laska";
			case 16: return "Granat";
			case 17: return "Gaz";
			case 18: return "Mołotow";
			case 22: return "9mm";
			case 23: return "9mm tłumik";
			case 24: return "Deagle";
			case 25: return "Shotgun";
			case 26: return "Sawnoff Shotgun";
			case 27: return "Combat Shotgun";
			case 28: return "Uzi";
			case 29: return "MP5";
			case 30: return "AK-47";
			case 31: return "M4";
			case 32: return "Tec-9";
			case 33: return "Country Rifle";
			case 34: return "Snajperka";
			case 35: return "RPG";
			case 36: return "Wyrzutnia namierzająca";
			case 37: return "Miotacz ognia";
			case 38: return "Minigun";
			case 39: return "C4";
			case 40: return "Detonator";
			case 41: return "C4";
			case 42: return "Gaśnica";
			case 43: return "Aparat";
			case 44: return "Noktowizor";
			case 45: return "Termowizja";
			case 46: return "Spadochron";
			default: return "Nieznany:".$weapon;
		}
	}
	public function getPenaltyName( $type )
	{
		switch( $type )
		{
			case 1:	return 'Warn';
			case 2:	return 'Kick';
			case 3:	return 'Ban';
			case 4:	return 'Blokada postaci';
			case 5:	return 'GameScore';
			case 6: return'Admin Jail';
			case 7: return 'UnWarn';
			case 8:	return'Blokada biegania';
			case 9:	return 'Blokada broni';
			case 10: return 'Blokada prowadzenia';
			case 11: return 'Blokada OOC';
			case 12:	return 'Ban 4/4';
			case 13: return "Klątwa";
			case 14: return "Ban (klątwa)";
		}
		return "Błąd";
	}
	public function getItemTypeName($type)
	{
		switch($type)
		{
			case 0: return 'Nieokreślony';
			case 1: return 'Broń';
			case 2: return 'Telefon';
			case 3: return 'Maska';
			case 4: return 'Jedzenie';
			case 5: return 'Kostka';
			case 6: return 'Karty';
			case 7: return 'Lek';
			case 8: return 'Kamizelka';
			case 9: return 'Zegarek';
			case 10: return 'Paliwo';
			case 11: return 'Papierosy';
			case 12: return 'Piwo';
			case 13: return 'Nasiona';
			case 14: return 'Marihuana';
			case 15: return 'Kokaina';
			case 16: return 'Heroina';
			case 17: return 'LSD';
			case 18: return 'Radio';
			case 19: return 'Megafon';
			case 20: return 'Sterydy';
			case 21: return 'Boombox';
			case 22: return 'Amunicja';
			case 23: return 'Tuning';
			case 24: return 'Tłumik 9mm';
			case 25: return 'Kluczyk do pojazdu';
			case 26: return 'Przedmiot doczepiany';
			case 27: return 'Zestaw naprawczy';
			case 28: return 'Klucz do skrytki';

			default: return 'NIEZNANY';
		}
	}
	public function getVehicleModelName( $modelid )
	{
		switch($modelid)
		{
			case 579: return 'Huntley';
			case 400: return 'Landstalker';
			case 404: return 'Perrenial';
			case 489: return 'Rancher';
			case 505: return 'Rancher';
			case 479: return 'Regina';
			case 442: return 'Romero';
			case 458: return 'Solair';
			case 602: return 'Alpha';
			case 496: return 'Blista';
			case 401: return 'Bravura';
			case 518: return 'Buccaneer';
			case 527: return 'Cadrona';
			case 589: return 'Club';
			case 419: return 'Esperanto';
			case 533: return 'Feltzer';
			case 526: return 'Fortune';
			case 474: return 'Hermes';
			case 545: return 'Hustler';
			case 517: return 'Majestic';
			case 410: return 'Manana';
			case 600: return 'Picador';
			case 436: return 'Previon';
			case 580: return 'Stafford';
			case 439: return 'Stallion';
			case 549: return 'Tampa';
			case 491: return 'Virgo';
			case 445: return 'Admiral';
			case 507: return 'Elegant';
			case 585: return 'Emperor';
			case 587: return 'Euros';
			case 466: return 'Glendale';
			case 492: return 'Greenwood';
			case 546: return 'Intruder';
			case 551: return 'Merit';
			case 516: return 'Nebula';
			case 467: return 'Oceanic';
			case 426: return 'Premier';
			case 547: return 'Primo';
			case 405: return 'Sentinel';
			case 409: return 'Stretch';
			case 550: return 'Sunrise';
			case 566: return 'Tahoma';
			case 540: return 'Vincent';
			case 421: return 'Washington';
			case 529: return 'Willard';
			case 402: return 'Buffalo';
			case 542: return 'Clover';
			case 603: return 'Phoenix';
			case 475: return 'Sabre';
			case 562: return 'Elegy';
			case 565: return 'Flash';
			case 559: return 'Jester';
			case 561: return 'Stratum';
			case 560: return 'Sultan';
			case 558: return 'Uranus';
			case 429: return 'Banshee';
			case 541: return 'Bullet';
			case 415: return 'Cheetah';
			case 480: return 'Comet';
			case 434: return 'Hotknife';
			case 494: return 'Hotring';
			case 502: return 'Hotring A';
			case 503: return 'Hotring B';
			case 411: return 'Infernus';
			case 506: return 'Super GT';
			case 451: return 'Turismo';
			case 555: return 'Windsor';
			case 477: return 'ZR-350';
			case 435: return 'Artict1 (Semi Trailer)';
			case 450: return 'Artict2 (Semi Trailer)';
			case 591: return 'Artict3 (Semi Trailer)';
			case 584: return 'Xoomer (Gas Tanker Trailer)';
			case 499: return 'Benson';
			case 498: return 'Boxville';
			case 609: return 'Boxville (Black for Robbery)';
			case 524: return 'Cement Truck';
			case 532: return 'Combine Harvestor';
			case 578: return 'DFT-30';
			case 486: return 'Dozer';
			case 406: return 'Dumper';
			case 573: return 'Dune';
			case 455: return 'Flatbed';
			case 588: return 'Hotdog';
			case 403: return 'Linerunner';
			case 423: return 'Mr Woopee';
			case 414: return 'Mule';
			case 443: return 'Packer';
			case 515: return 'Roadtrain';
			case 514: return 'Tanker';
			case 531: return 'Tractor';
			case 610: return 'Farm Trailer';
			case 456: return 'Yankee';
			case 459: return 'Topfun (RC Van)';
			case 422: return 'Bobcat';
			case 482: return 'Burrito';
			case 530: return 'Forklift';
			case 418: return 'Moonbeam';
			case 572: return 'Mower';
			case 582: return 'Newsvan';
			case 413: return 'Pony';
			case 440: return 'Rumpo';
			case 543: return 'Sadler';
			case 583: return 'Tug';
			case 478: return 'Walton';
			case 554: return 'Yosemite';
			case 536: return 'Blade';
			case 575: return 'Broadway';
			case 534: return 'Remington';
			case 567: return 'Savanna';
			case 535: return 'Slamvan';
			case 576: return 'Tornado';
			case 412: return 'Voodoo';
			case 568: return 'Bandito';
			case 424: return 'BF Injection';
			case 504: return 'Bloodring Banger';
			case 457: return 'Caddy';
			case 483: return 'Camper';
			case 508: return 'Journey';
			case 571: return 'Kart';
			case 500: return 'Mesa';
			case 444: return 'Monster';
			case 556: return 'Monstera';
			case 557: return 'Monsterb';
			case 471: return 'Quad';
			case 495: return 'Sandking';
			case 539: return 'Vortex';
			case 481: return 'Bmx';
			case 509: return 'Bike';
			case 510: return 'Mountain Bike';
			case 581: return 'BF-400';
			case 462: return 'Faggio';
			case 521: return 'FCR-900';
			case 463: return 'Freeway';
			case 522: return 'NRG-500';
			case 461: return 'PCJ-600';
			case 448: return 'Pizzaboy';
			case 468: return 'Sanchez';
			case 586: return 'Wayfarer';
			case 606: return 'Bagboxa (Baggage Trailer)';
			case 607: return 'Bagboxb (Baggage Trailer)';
			case 485: return 'Baggage';
			case 431: return 'Bus';
			case 438: return 'Cabbie';
			case 437: return 'Coach';
			case 574: return 'Sweeper';
			case 611: return 'Sweeper Trailer';
			case 420: return 'Taxi';
			case 525: return 'Towtruck';
			case 408: return 'Trashmaster';
			case 608: return 'Tug Stairs (Stairs Trailer)';
			case 552: return 'Utility Van';
			case 416: return 'Ambulance';
			case 433: return 'Barracks';
			case 427: return 'Enforcer';
			case 490: return 'FBI Rancher';
			case 528: return 'FBI Truck';
			case 407: return 'Fire Truck';
			case 544: return 'Fire Truck A';
			case 523: return 'HPV-1000 (Police Bike)';
			case 470: return 'Patriot';
			case 596: return 'Police Los Santos';
			case 597: return 'Police San Fierro';
			case 598: return 'Police Las Venturas';
			case 599: return 'Police Ranger';
			case 432: return 'Rhino';
			case 428: return 'Securicar';
			case 601: return 'Swat Tank';
			case 592: return 'Andromada';
			case 577: return 'AT-400';
			case 511: return 'Beagle';
			case 548: return 'Cargobob';
			case 512: return 'Cropduster';
			case 593: return 'Dodo';
			case 425: return 'Hunter';
			case 417: return 'Leviathon';
			case 487: return 'Maverick';
			case 553: return 'Nevada';
			case 488: return 'News Maverick';
			case 497: return 'Police Maverick';
			case 563: return 'Raindance';
			case 476: return 'Rustler';
			case 447: return 'Seasparrow';
			case 519: return 'Shamal';
			case 460: return 'Skimmer';
			case 469: return 'Sparrow';
			case 513: return 'Stunt Plane';
			case 520: return 'Hydra';
			case 472: return 'Coastguard';
			case 473: return 'Dingy';
			case 493: return 'Jetmax';
			case 595: return 'Launch';
			case 484: return 'Marquis';
			case 430: return 'Predator';
			case 453: return 'Reefer';
			case 452: return 'Speeder';
			case 446: return 'Squallo';
			case 454: return 'Tropic';
			case 441: return 'RC Bandit';
			case 464: return 'RC Baron';
			case 594: return 'RC Cam';
			case 465: return 'RC Goblin';
			case 501: return 'RC Goblin';
			case 564: return 'RC Tigerv';
			case 604: return 'Glendale';
			case 605: return 'Sadler';
			default: return 'NIEZNANY';
	}

	}

}
