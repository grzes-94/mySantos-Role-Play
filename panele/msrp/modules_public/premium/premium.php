<?php

class public_msrp_premium_premium extends ipsCommand
{

  public function doExecute(ipsRegistry $registry)
  {
    if(!$this->memberData['member_id'])
    {
      $this->registry->output->showError('Dostęp do tej sekcji modułu wymaga zalogowania.');
    }

    $premium_end=$this->memberData['premium'];
    //PREMIUM SMS
    if(isset($this->request['smsactivate']))
    {
      $userCode = $this->request['smscode'];


      $hotplayID = "VVJiYkFQRXJrNkprRXhtRDYwSkI5NEUyb3pFVDUvRzludXBhUG9YVGU5dz0,";

      $ch = curl_init();
      $url = "https://api.hotpay.pl/check_sms.php?sekret=".$hotplayID."&kod_sms=".$userCode;
      curl_setopt($ch, CURLOPT_URL, $url);
      curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
      $wynik = curl_exec($ch);
      curl_close($ch);

      $codeInfo = json_decode($wynik);


      if($codeInfo->status=="ERROR")
      {
        $success=-1;
      }
      else
      {

        if($codeInfo->aktywacja==1)
        {
          //Pierwsza aktywacja

          $success=1;
          $premium_end = $this->activatePremium($this->memberData['member_id'],30,1);
        }
        else
        {
          //kolejna aktywacja
          $success=-2;
        }


      }
      //$this->registry->output->showError($this->request['code']);
    }
    else if(isset($this->request['skinactivate']))
    {
      $userCode = $this->request['skincode'];


      $hotplayID = "THdMNnU4N3RnNGd2bmcwbjkxa3FxWDI5dFFXcXZqUjhzVFduaW1RTUlVWT0,";

      $ch = curl_init();
      $url = "https://api.hotpay.pl/check_sms.php?sekret=".$hotplayID."&kod_sms=".$userCode;
      curl_setopt($ch, CURLOPT_URL, $url);
      curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
      $wynik = curl_exec($ch);
      curl_close($ch);

      $codeInfo = json_decode($wynik);


      if($codeInfo->status=="ERROR")
      {
        $success=-1;
      }
      else
      {

        if($codeInfo->aktywacja==1)
        {
          //Pierwsza aktywacja

          $success=2;
          $this->DB->query("INSERT INTO `panel_skin_codes` SET `code`='".$userCode."', `member_id` = '".$this->memberData['member_id']."'");
          
          $classToLoad = IPSLib::loadLibrary( IPS_ROOT_PATH . '/sources/classes/member/notifications.php', 'notifications' );
          $notifyLibrary = new $classToLoad( $this->registry );
      
      		$notifyLibrary->setMember( 1 );
          $notifyLibrary->setFrom( $this->memberData );
          $notifyLibrary->setNotificationKey( 'profile_comment' );
          $notifyLibrary->setNotificationText( 'Nowy zakup skina' );
          $notifyLibrary->setNotificationTitle( $this->memberData['members_display_name']." kupił skin przez SMS" );
        		try
           {
                $notifyLibrary->sendNotification();
           }
           catch( Exception $e )
           {
           }
           $notifyLibrary->setMember( 3 );
           try
           {
                $notifyLibrary->sendNotification();
           }
           catch( Exception $e )
           {
           }
        }
        else
        {
          //kolejna aktywacja
          $success=-2;
        }


      }
      //$this->registry->output->showError($this->request['code']);
    }
    else if(isset($this->request['codeactivate'])) //kod @
    {
      $premiumCode = $this->request['code'];
      if(strlen($premiumCode) != 12)
      $success=-1;
      else
      {
        $result = $this->DB->query("SELECT * FROM `panel_premium_codes` WHERE `code`=\"".$premiumCode."\"");
        if(! ($row=$result->fetch_assoc()))
        $success=-1;
        else if($row['used_by'])
        $success=-2;
        else
        {
          $premium_end = $this->activatePremium($this->memberData['member_id'],$row['days'],0);
          $success  = 1;
          $query=sprintf("UPDATE `panel_premium_codes` SET `used_by`=%d, `activation_time`=%d WHERE `code_uid`=%d",$this->memberData['member_id'],IPS_UNIX_TIME_NOW,$row['code_uid']);
          $this->DB->query($query);
        }

      }
    }

    $template = $this->registry->output->getTemplate('msrp')->msrp_premium($success, $premium_end);
    $this->registry->output->addContent($template);
    $this->registry->output->setTitle('Konto premium');
    $this->registry->output->addNavigation('Konto Premium', 'app=msrp&module=premium&section=premium', 'false', 'msrp_premium', 'public');
    $this->registry->output->sendOutput();
  }

  private function activatePremium($memberid, $days,$type)
  {
    $group_premium = 9;
    $group_user = 3;
    $TIME_NOW = IPS_UNIX_TIME_NOW;
    $this->DB->query(sprintf('INSERT INTO `panel_premium_logs` (code_owner, code_date, typ) VALUES (%d, %d, %d)', $this->memberData['member_id'], $TIME_NOW,$type));
    $this->DB->execute();

    $this->DB->query('SELECT premium, member_group_id FROM `members` WHERE member_id = '.$memberid);
    $this->DB->execute();
    $dupa = $this->DB->fetch();

    $premium_time = $dupa['premium'];
    $time= $days * 86400;
    if($premium_time >= $TIME_NOW)
    $premium_time += $time;
    else
    $premium_time= $TIME_NOW + $time;

    $this->DB->query('UPDATE `members` SET premium = '.$premium_time.' WHERE member_id = '.$memberid.' LIMIT 1');
    if($dupa['member_group_id'] == $group_user)
    {
      $this->DB->query("UPDATE `members` SET  `member_group_id` =".$group_premium." WHERE `member_id` = ".$memberid);
    }

    return $premium_time;
  }

}
