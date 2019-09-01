<?php
class public_msrp_salon_salon extends ipsCommand
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

    $count = $this->DB->query('SELECT COUNT(*) as max FROM `srv_salon_vehicles`');
    $count = $this->DB->fetch($count);


    $this->DB->query('SELECT * FROM `srv_salon_vehicles` ORDER by category, price');
    $this->DB->execute();

    while($row = $this->DB->fetch())
    {
      switch($row['category'])
      {
        case 0: $row['category'] = 'Jednoślady'; break;
        case 1: $row['category'] = 'Trzydrzwiowe'; break;
        case 2: $row['category'] = 'Pięciodrzwiowe'; break;
        case 3: $row['category'] = 'Offroad'; break;
        case 4: $row['category'] = 'Dostawcze'; break;
        case 5: $row['category'] = 'Sportowe'; break;
        default: $row['category'] = 'Blad systemu'; break;
      }
      $row['price'] = $functions->formatDollars(  $row['price']);
      $veh[] = $row;
    }

    $template = $this->registry->output->getTemplate('msrp')->msrp_salon($veh);
    $this->registry->getClass('output')->addContent($template);
    $this->registry->output->setTitle('Pojazdy w salonie');
    $this->registry->output->addNavigation( 'Panel Gry', 'app=msrp&module=character' );
    $this->registry->output->addNavigation( 'Cennik pojazdów', 'app=msrp&module=salon' );
    $this->registry->getClass('output')->sendOutput();
  }

}
