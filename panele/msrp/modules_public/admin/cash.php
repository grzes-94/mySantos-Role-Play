<?php
class public_msrp_admin_cash extends ipsCommand
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

		$result = $this->DB->query('SELECT *,`cash` + `credit` AS `sum` FROM `srv_characters` ORDER by `sum` DESC LIMIT 100');

		while($row = $result->fetch_assoc())
		{
			$row['ooc']=$functions->GetMemberName($row['global_id']);
			$row['ic']=$functions->GetCharacterName($row['player_uid'],true);
			$row['bank']=$functions->formatDollars($row['bank']);
			$row['credit']=$functions->formatDollars($row['credit']);
			$row['sum']=$functions->formatDollars($row['sum']);
			$cash[] = $row;
		}

		$template = $this->registry->output->getTemplate('msrp')->msrp_admin_cash($cash);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('Panel administratora');
		$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin' );
		$this->registry->output->addNavigation( 'Gotówka', 'app=msrp&module=admin&section=cash' );
		$this->registry->getClass('output')->sendOutput();
	}

}
?>
