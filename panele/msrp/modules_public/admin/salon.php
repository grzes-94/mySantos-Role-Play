<?php
class public_msrp_admin_salon extends ipsCommand
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

		$count = $this->DB->query('SELECT COUNT(*) as max FROM `srv_salon_vehicles`');
		$count = $this->DB->fetch($count);


		if(isset($this->request['submit']))
		{

			$this->DB->query('UPDATE `srv_salon_vehicles` SET `price` = '.$_POST['price'].' WHERE `model` = '.$_POST['model'].'');

			$this->registry->output->silentRedirect(
			$this->registry->output->buildUrl('/index.php?app=msrp&module=admin&section=salon','publicWithApp')
		);
	}

	$this->DB->query('SELECT * FROM `srv_salon_vehicles` ORDER by category, price');
	$this->DB->execute();

	while($row = $this->DB->fetch())
	{
		switch($row['category'])
		{
			case 0: $row['category'] = 'Jednoslady'; break;
			case 1: $row['category'] = 'Trzydrzwiowe'; break;
			case 2: $row['category'] = 'Pieciodrzwiowe'; break;
			case 3: $row['category'] = 'Offroad'; break;
			case 4: $row['category'] = 'Dostawcze'; break;
			case 5: $row['category'] = 'Sportowe'; break;
			default: $row['category'] = 'Blad systemu'; break;
		}

		$row['price']=$functions->formatDollars($row['price']);
		$veh[] = $row;
	}

	$template = $this->registry->output->getTemplate('msrp')->msrp_admin_salon($veh);
	$this->registry->getClass('output')->addContent($template);
	$this->registry->output->setTitle('Pojazdy w salonie');
	$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin' );
	$this->registry->output->addNavigation( 'Salon', 'app=msrp&module=admin&section=salon' );
	$this->registry->getClass('output')->sendOutput();
}

}
?>
