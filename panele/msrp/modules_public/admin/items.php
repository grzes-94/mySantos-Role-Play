<?php
class public_msrp_admin_items extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
		require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/functions.php' );
		$this->registry->setClass( 'functions', new functions( $registry ) );
		$functions = $this->registry->getClass( 'functions' );



		if(! $functions->IsGruopAdmin($this->memberData['member_group_id'],true))
		{
			$this->registry->output->silentRedirect('index.php');
		}
    isset($_POST['type']) ? $type=$_POST['type'] : $type='.+';
    isset($_POST['ownertyp']) ? $ownertyp=$_POST['ownertyp'] : $ownertyp='.+';

		$this->DB->query('SELECT * FROM `srv_items` WHERE `type` REGEXP \'^'.$type.'$\' ');
    $this->DB->execute();

		while($row = $this->DB->fetch())
		{
      $row['typename']=$functions->getWeaponName($row['value1']);
      switch($row['ownertyp'])
      {
        case 0: $row['ownertypename']= "Przedmiot odłożony"; break;
        case 1: $row['ownertypename']="Gracz"; break;
        case 2: $row['ownertypename']="Magazyn"; break;
        case 11: $row['ownertypename']= "Drzwi (schowek)"; break;
        case 15: $row['ownertypename']= "Drzwi (schowek)"; break;
        case 20: $row['ownertypename']="Pojazd"; break;
        case 21: $row['ownertypename']="Pojazd (bagażnik)"; break;
        default: $row['ownertypename']="INNY : ".$row['ownertyp'];
      }
			$row['ownername'];
      $items[] = $row;
		}
		foreach($items as $gun)
		{
			$gun['ownername']=$this->GetWeaponOwner($gun['owner'],$gun['ownertype']);
		}

		$template = $this->registry->output->getTemplate('msrp')->msrp_admin_items($items);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('Lista broni');
		$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin' );
		$this->registry->output->addNavigation( 'Lista broni', 'app=msrp&module=admin&section=guns' );
		$this->registry->getClass('output')->sendOutput();
	}

  public function GetWeaponOwner( $owner, $ownertype )
  {
    switch($ownertype)
    {
      case 0: //przedmiot odłożony
      {
        $this->DB->query('SELECT posx,posy,posz,world FROM `srv_items` WHERE `UID` = '.$owner);
        $item = $this->DB->fetch();
        $owner =  $item['posx'].' '.$item['posy'].' '.$item['posz'].' '.$item['world'];
        return $owner;
      }
      case 1: //gracz
      {
        $this->DB->query('SELECT nickname FROM `srv_characters` WHERE `player_uid` = '.$owner);
        $player = $this->DB->fetch();
        $player['nickname'] = str_replace("_", " ", $player['nickname']);
        $owner =  '<a href ="index.php?&app=msrp&module=admin&section=editchar&uid='.$owner.'">'.$player['nickname'].'</a>';
        return $owner;
      }
      case 2: //grupa - magazyn
      {
        $this->DB->query('SELECT name FROM `srv_groups` WHERE `UID` = '.$owner);
        $group = $this->DB->fetch();
        return $group['name'];
      }
      case 11:
      {
        $this->DB->query('SELECT name FROM `srv_doors` WHERE `UID` = '.$owner);
        $door = $this->DB->fetch();
        $owner =  $owner.': '.$door['name'];
        return $owner;
      }
      case 15:
      {
        $this->DB->query('SELECT name FROM `srv_doors` WHERE `UID` = '.$owner);
        $door = $this->DB->fetch();
        $owner =  $owner.': '.$door['name'];
        return $owner;
      }

      case 20:
      {
        $this->DB->query('SELECT model,ownertyp,owner FROM `srv_vehicles` WHERE `UID` = '.$owner);
        $veh = $this->DB->fetch();
        $model=$functions->getVehicleModelName($veh['model']);
        if($veh['ownertyp']==1)
        {
            $this->DB->query('SELECT nickname FROM `srv_characters` WHERE `player_uid` = '.$veh['owner']);
            $player = $this->DB->fetch();
            $player['nickname'] = str_replace("_", " ", $player['nickname']);

            $owner =  $owner.': '.$model.' <a href ="index.php?&app=msrp&module=admin&section=editchar&uid='.$owner.'">'.$player['nickname'].'</a>';
            return $owner;

        }
        else if($veh['ownertyp']==2)
        {
          $this->DB->query('SELECT name FROM `srv_groups` WHERE `UID` = '.$veh['owner']);
          $group = $this->DB->fetch();
          $owner = $owner.': '.$model.' '.$group['name'];
          return $owner;
        }
        return "INNY ".$owner;
      }
      case 21:
      {
        $this->DB->query('SELECT model,ownertyp,owner FROM `srv_vehicles` WHERE `UID` = '.$owner);
        $veh = $this->DB->fetch();
        $model=$functions->getVehicleModelName($veh['model']);
        if($veh['ownertyp']==1)
        {
            $this->DB->query('SELECT nickname FROM `srv_characters` WHERE `player_uid` = '.$veh['owner']);
            $player = $this->DB->fetch();
            $player['nickname'] = str_replace("_", " ", $player['nickname']);

            $owner =  $owner.': '.$model.' <a href ="index.php?&app=msrp&module=admin&section=editchar&uid='.$owner.'">'.$player['nickname'].'</a>';
            return $owner;

        }
        else if($veh['ownertyp']==2)
        {
          $this->DB->query('SELECT name FROM `srv_groups` WHERE `UID` = '.$veh['owner']);
          $group = $this->DB->fetch();
          $owner = $owner.': '.$model.' '.$group['name'];
          return $owner;
        }
        return "INNY ".$owner;
      }
    }

  }

}
