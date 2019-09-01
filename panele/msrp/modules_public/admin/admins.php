<?php
class public_msrp_admin_admins extends ipsCommand
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

		$query = $this->DB->query('SELECT c.player_uid, c.global_id, c.nickname, c.admin, c.hours, c.minutes, c.online_today, c.last_online, m.members_display_name, m.member_group_id FROM srv_characters c, members m WHERE `admin`>0 AND c.global_id=m.member_id ORDER BY `admin` DESC, `last_online` DESC ');
    $this->DB->execute();

		while($row = $query->fetch_assoc())
		{
      $row['nickname'] = str_replace("_", " ", $row['nickname']);
			$row['onlinetoday'] = floor($row['online_today']/3600)." h ".floor(($row['online_today']%3600)/60)." min";
      switch($row['admin'])
      {
        case 1:
          $row['admgroup']='<span style="color:#001BEB">Opiekun</span>';
          break;
        case 2:
          $row['admgroup']='<span style="color:#8B00B0">GameMaster I</span>';
          break;
        case 3:
          $row['admgroup']='<span style="color:#8B00B0">GameMaster II</span>';
          break;
        case 4:
          $row['admgroup']='<span style="color:#8B00B0">GameMaster III</span>';
          break;
        case 5:
          $row['admgroup']='<span style="color:#B00000">Administrator</span>';
          break;
        case 6:
          $row['admgroup']='<span style="color:#FF0000">Head Admin</span>';
          break;
        defautl:
          $row['admgroup']='Błąd '.$row['admin'];
      }
			$q2=$this->DB->query('SELECT SUM(`online_today`) as time FROM `srv_characters` WHERE `global_id`='.$row['global_id'].' AND `player_uid` !='.$row['player_uid']);
			$res=$q2->fetch_assoc();
			$row['otherTime']=floor($res['time']/3600)." h ".floor(($res['time']%3600)/60)." min";

			$admins[] = $row;
		}


		$q3 = "SELECT DISTINCT `player_uid` AS puid,  `global_id`,
		(SELECT online FROM `panel_admins_online` WHERE `player_uid` = puid AND `date` > (NOW()- INTERVAL 23 HOUR) LIMIT 1) as d1,

		(SELECT online FROM `panel_admins_online` WHERE `player_uid` = puid AND `date` BETWEEN (NOW() - INTERVAL 2 DAY) AND (NOW() - INTERVAL 1 DAY) LIMIT 1) as d2,

		(SELECT online FROM `panel_admins_online` WHERE `player_uid` = puid AND `date` BETWEEN (NOW() - INTERVAL 3 DAY) AND (NOW() - INTERVAL 2 DAY) LIMIT 1) as d3,

		(SELECT online FROM `panel_admins_online` WHERE `player_uid` = puid AND `date` BETWEEN (NOW() - INTERVAL 4 DAY) AND (NOW() - INTERVAL 3 DAY) LIMIT 1) as d4,

		(SELECT online FROM `panel_admins_online` WHERE `player_uid` = puid AND `date` BETWEEN (NOW() - INTERVAL 5 DAY) AND (NOW() - INTERVAL 4 DAY) LIMIT 1) as d5,

		(SELECT online FROM `panel_admins_online` WHERE `player_uid` = puid AND `date` BETWEEN (NOW() - INTERVAL 6 DAY) AND (NOW() - INTERVAL 5 DAY) LIMIT 1) as d6,

		(SELECT online FROM `panel_admins_online` WHERE `player_uid` = puid AND `date` BETWEEN (NOW() - INTERVAL 7 DAY) AND (NOW() - INTERVAL 6 DAY) LIMIT 1) as d7

		FROM panel_admins_online WHERE `player_uid` IN (SELECT `player_uid` FROM `srv_characters` WHERE `admin`> 0 ) ORDER BY puid";

		$this->DB->allow_sub_select=1;
		$query=$this->DB->query($q3);
		$this->DB->allow_sub_select=0;
		while($row = $query->fetch_assoc())
		{
			$row['d1'] = floor($row['d1']/3600)." h ".floor(($row['d1']%3600)/60)." min";
			$row['d2'] = floor($row['d2']/3600)." h ".floor(($row['d2']%3600)/60)." min";
			$row['d3'] = floor($row['d3']/3600)." h ".floor(($row['d3']%3600)/60)." min";
			$row['d4'] = floor($row['d4']/3600)." h ".floor(($row['d4']%3600)/60)." min";
			$row['d5'] = floor($row['d5']/3600)." h ".floor(($row['d5']%3600)/60)." min";
			$row['d6'] = floor($row['d6']/3600)." h ".floor(($row['d6']%3600)/60)." min";
			$row['d7'] = floor($row['d7']/3600)." h ".floor(($row['d1']%3600)/60)." min";
			$logs[] = $row;
		}


		$template = $this->registry->output->getTemplate('msrp')->msrp_admin_admins($admins,$logs);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('Administratorzy');
		$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin' );
		$this->registry->output->addNavigation( 'Administratorzy', 'app=msrp&module=admin&section=admins' );
		$this->registry->getClass('output')->sendOutput();
	}

}
