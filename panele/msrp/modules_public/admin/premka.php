<?php
class public_msrp_admin_premka extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
		require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/functions.php' );
		$this->registry->setClass( 'functions', new functions( $registry ) );
		$functions = $this->registry->getClass( 'functions' );

		if(! $functions->IsGruopAdmin($this->memberData['member_group_id'],false))
		{
			$this->registry->output->silentRedirect('index.php');
		}
		if(! ($this->memberData['panel_perm'] & 1))
		{
				$this->registry->output->showError('Nie posiadasz uprawnień do zarządzania kontem premium.',0);
    }

    if(!empty($_POST['generate']) && $_POST['days']>0)
    {
      $code = $this->randomKey(12);

      $query=sprintf("INSERT INTO `panel_premium_codes` (`code`,`days`,`created_by`) VALUES (\"%s\", %d, %d)",$code,$_POST['days'],$this->memberData['member_id']);
      $this->DB->query($query);
    }
    unset($_POST['generate']);
    unset($_POST['days']);

    $result = $this->DB->query("SELECT * FROM `panel_premium_codes` ORDER BY `code_uid` DESC LIMIT 20");
    while($row = $result->fetch_assoc())
    {
      $row['created_by']=$functions->GetMemberName($row['created_by']);
      if($row['used_by'])
      {
        $row['used_by']=$functions->GetMemberName($row['used_by']);
      }
      else
        $row['used_by']="-";

      $premium[]=$row;
    }
		$result = $this->DB->query("SELECT * FROM `panel_premium_logs` WHERE `typ`=1 ORDER BY `code_uid` DESC LIMIT 30");
		while($row = $result->fetch_assoc())
    {
      $row['code_owner']=$functions->GetMemberName($row['code_owner']);

      $lastSms[]=$row;
    }
		

	$template = $this->registry->output->getTemplate('msrp')->msrp_admin_premium($premium,$lastSms, $code, []);
	$this->registry->getClass('output')->addContent($template);
	$this->registry->output->setTitle('Kody premium');
	$this->registry->output->addNavigation( 'Panel administratora', 'app=panel&module=admin' );
	$this->registry->output->addNavigation( 'Premium', 'app=panel&module=admin&section=premka' );
	$this->registry->getClass('output')->sendOutput();
}
private function randomKey($length)
{
    $pool = array_merge(range(0,9), range('a', 'z'),range('A', 'Z'));

    for($i=0; $i < $length; $i++) {
        $key .= $pool[mt_rand(0, count($pool) - 1)];
    }
    return $key;
}

}
?>
