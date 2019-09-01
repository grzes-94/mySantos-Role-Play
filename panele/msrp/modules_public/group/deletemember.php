<?php
class public_msrp_group_deletemember extends ipsCommand
{
  public function doExecute( ipsRegistry $registry )
  {

    if(!isset($this->request['group']) || !isset($this->request['memberid']))
    {
      $this->registry->output->showError('Wystapł błąd podczas przesyłania formularza.',0);
    }
    require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/group.php' );
    $this->registry->setClass( 'group', new group( $registry ) );
    $group = $this->registry->getClass( 'group' );

    $groupid=$this->request['group'];
    $information = $group->fetchGroupInformation( intval( $this->request['group'] ) );

    $result = $this->DB->query("SELECT m.permission FROM srv_groups_members m, srv_characters c WHERE m.permission & 128 AND m.group_uid = $groupid AND m.player_uid=c.player_uid AND c.global_id=".$this->memberData['member_id']);
    if(!$result->fetch_assoc())
      $this->registry->output->showError('Nie posiadasz uprawnień do usunięcia tej postaci.',0);

    $this->DB->query('SELECT nickname, global_id FROM `srv_characters` WHERE `player_uid` = '.$this->request['memberid'].'');
    $row = $this->DB->fetch();

    if($row['global_id']==$this->memberData['member_id'])
    {

      echo "<h3 class=\"maintitle\">Potwierdzenie usunięcia pracownika</h3>
      <center>
      <br />Nie możesz zwolnić swojej postaci.<br /><br>
      </center>";
    }
    else
    {



    $membername = str_replace("_", " ", $row['nickname']);
    $memberid = $this->request['memberid'];

    $url='index.php?app=msrp&module=group&section=deletemember&group='.$this->request['group'].'$memberid='.$memberid;

echo<<<EOF
    <h3 class="maintitle">Potwierdzenie usunięcia pracownika</h3>
    <br />
    Czy na pewno chcesz usunąć pracownika $membername?

    <br />
    <center>
    <form method="post" action="#">
    <input type="hidden" value=$memberid name="memberid">
    </div>
    <input class="input_submit" type="submit" name="yes" value="Tak" />

    <form>
    <input class="input_submit" type="submit" name="no" value="Nie" />
    </center>
    <br />
EOF;

  }
  }
}
