<?php
class public_msrp_admin_groups extends ipsCommand
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


	$this->DB->query('SELECT * FROM srv_groups  ORDER by UID ASC');
	$this->DB->execute();

	while($row = $this->DB->fetch())
	{
		$row['cash']=$functions->formatDollars($row['cash'] );
		$row['perm']=$functions->getGroupType($row['type']);

		$groups[] = $row;
	}

	$template = $this->registry->output->getTemplate('msrp')->msrp_admin_groups($groups, $pagination);
	$this->registry->getClass('output')->addContent($template);
	$this->registry->output->setTitle('Lista grup');
	$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin' );
	$this->registry->output->addNavigation( 'Lista grup', 'app=msrp&module=admin&section=groups' );
	$this->registry->getClass('output')->sendOutput();
}

}
?>
