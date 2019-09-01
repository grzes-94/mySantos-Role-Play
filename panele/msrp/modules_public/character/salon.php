<?php
class public_msrp_public_saloncennik extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
		if(!$this->memberData['member_id'])
		{
			$this->registry->output->showError('Niestety, nie jesteś zalogowany dlatego dostęp do tej części forum został zablokowany.',0);
		}

		$count = $this->DB->query('SELECT COUNT(*) as max FROM `srv_salon_vehicles`');
		$count = $this->DB->fetch($count);


		if(isset($this->request['submit']))
		{

			$this->DB->query('UPDATE `srv_salon_vehicles` SET `price` = '.$_POST['price'].' WHERE `model` = '.$_POST['model'].'');


			$this->registry->output->silentRedirect(
				$this->registry->output->buildUrl('/index.php?app=msrp&module=admin&section=salon','publicWithApp')
			);
		}

		$this->DB->query(sprintf('SELECT * FROM `srv_salon_vehicles` ORDER by category, price',$this->request['st']));
		$this->DB->execute();

		while($row = $this->DB->fetch())
		{
			switch($row['category'])
			{
                case 0: $row['category'] = 'Jednoslady'; break;
		case 1: $row['category'] = 'Trzydrzwiowe'; break;
		case 2: $row['category'] = 'Pieciodrzwiowe'; break;
		case 3: $row['category'] = 'Offroad'; break;
		case 4: $row['category'] = 'Sportowe'; break;
		default: $row['category'] = 'Blad systemu'; break;
			}
			$veh[] = $row;
		}

		$template = $this->registry->output->getTemplate('msrp')->msrp_salon($veh);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('Cennik');
		$this->registry->output->addNavigation( 'Panel Gry', 'app=msrp' );
		$this->registry->output->addNavigation( 'Cennik', 'app=msrp&modules=character&section=salon' );
		$this->registry->getClass('output')->sendOutput();
}
}
?>
