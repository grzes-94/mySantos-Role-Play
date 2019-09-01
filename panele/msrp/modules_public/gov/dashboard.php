<?php
class public_msrp_gov_dashboard extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
    require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/functions.php' );
		$this->registry->setClass( 'functions', new functions( $registry ) );
		$functions = $this->registry->getClass( 'functions' );
    if(!($this->memberData['panel_perm'] & 2))
		{
			$this->registry->output->silentRedirect('index.php');
		}

    if(!empty($_POST['confirm']))
    {
      $query=sprintf("UPDATE `srv_settings` SET `doc_id`=%d , `doc_driver`=%d, `doc_pilot`=%d, `fuel_cost`=%d, `taxes`=%d, `platecharge`=%d, `registercharge`=%d WHERE 1",
          $_POST['docId'],
          $_POST['docDriver'],
          $_POST['docPilot'],
          $_POST['fuel'],
          $_POST['tax'],
          $_POST['carRegister'],
          $_POST['businessRegister']
        );
        $this->DB->query($query);

        	$this->DB->query('INSERT INTO `panel_admin_log` (`owner`, `log`, `date`) VALUES ('.$this->memberData['member_id'].', "Edycja ustawień rządowych.", "'.IPS_UNIX_TIME_NOW.'")');

        $this->registry->output->redirectScreen( 'Ustawienia zapisane.', $this->settings['base_url'] . 'app=msrp&module=gov');
    }
    $query = $this->DB->query("SELECT * FROM `srv_settings`");
    $settings = $query->fetch_assoc();

    $template = $this->registry->output->getTemplate('msrp')->msrp_gov($settings);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('Panel rządowy');
		$this->registry->output->addNavigation( 'Panel rządowy', 'app=msrp&module=gov' );
		$this->registry->output->addNavigation( 'Finanse', 'app=msrp&module=gov&section=dashboard' );
		$this->registry->getClass('output')->sendOutput();
  }
}
