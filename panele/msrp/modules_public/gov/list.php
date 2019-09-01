<?php
class public_msrp_gov_list extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
    if(!($this->memberData['panel_perm'] & 2))
		{
			$this->registry->output->silentRedirect('index.php');
		}
    require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/functions.php' );
		$this->registry->setClass( 'functions', new functions( $registry ) );
		$functions = $this->registry->getClass( 'functions' );

    $query = $this->DB->query("SELECT * FROM `srv_groups` WHERE `registered`=1");
    while($row=$query->fetch_assoc())
    {
      $row['typename']= $functions->getGroupType($row['type']);
      $row['cash']=$functions->formatDollars($row['cash'] );
      $row['grant']=$functions->formatDollars($row['grant'] );
      $row['salary_account']=$functions->formatDollars($row['salary_account'] );
      $row['leadernick']=$functions->GetCharacterName($row['leader']);

      $groups[] = $row;
    }

    $template = $this->registry->output->getTemplate('msrp')->msrp_gov_list($groups);
    $this->registry->getClass('output')->addContent($template);
    $this->registry->output->setTitle('Lista grup');
    $this->registry->output->addNavigation( 'Panel rządowy', 'app=msrp&module=gov' );
    $this->registry->output->addNavigation( 'Lista grup', 'app=msrp&module=gov&section=list' );
    $this->registry->getClass('output')->sendOutput();
  }
}
