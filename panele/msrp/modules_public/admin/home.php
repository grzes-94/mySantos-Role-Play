<?php
class public_msrp_admin_home extends ipsCommand
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

			$this->DB->query('SELECT * FROM `panel_panel_log` ORDER by `uid` DESC LIMIT 10');
			$this->DB->execute();

		while($row = $this->DB->fetch())
		{
			$log[] = $row;
		}

			$this->DB->query('SELECT * FROM `panel_admin_log` ORDER by `uid` DESC LIMIT 50');
			$this->DB->execute();

		while($row = $this->DB->fetch())
		{
			$logs[] = $row;
		}

		$template = $this->registry->output->getTemplate('msrp')->msrp_admin_home($log, $logs);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('Panel administratora');
		$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin&section=home' );
		$this->registry->getClass('output')->sendOutput();
	}

}
?>
