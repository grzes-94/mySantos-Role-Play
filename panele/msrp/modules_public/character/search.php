<?php
class public_msrp_character_search extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
		require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/functions.php' );
		$this->registry->setClass( 'functions', new functions( $registry ) );
		$functions = $this->registry->getClass( 'functions' );


    if(!empty($this->request['nick']))
    {
      $nick = $this->request['nick'];
      if(strlen($nick)<3)
        $this->registry->output->showError('Wprowadzona nazwa postaci jest za krótka. Minimum 3 znaki.',0);
      if(!preg_match('/^[A-Za-z_]+$/',$nick))
        $this->registry->output->showError('Wprowadzona nazwa postaci zawiera niedozwolone znaki.',0);
      $query = $this->DB->query("SELECT * FROM `srv_characters` WHERE `hide`=0 AND `nickname` LIKE '%$nick%'");
      while($row = $query->fetch_assoc())
      {
        $row['nickname']=$functions->GetCharacterName($row['player_uid'],false);
        $row['ooc']=$functions->GetMemberName($row['global_id']);
        if($row['block'] & 2)
    			$row['status'] = '<font color="red"><b>Ban</b></font>';
    		else if($row['block'] & 1)
    			$row['status'] = '<font color="grey"><b>Blokada Postaci</b></font>';
    		else if($row['block'] & 4)
    				$row['status'] = '<font color="grey"><b>Character Kill</b></font>';
    		else
    				$row['status'] = '<font color="green"><b>Aktywna</b></font>';
        $chars[] = $row;
      }
    }


	$template = $this->registry->output->getTemplate('msrp')->msrp_char_searchchar($chars);
	$this->registry->getClass('output')->addContent($template);
	$this->registry->output->setTitle('Wyszukiwanie postaci');
	$this->registry->output->addNavigation( 'Panel administratora', 'app=panel&module=admin' );
	$this->registry->output->addNavigation( 'Szukaj postaci', 'app=panel&module=admin&section=searchar' );
	$this->registry->getClass('output')->sendOutput();
}


}
?>
