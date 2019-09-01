<?php
class public_msrp_online_api extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{

			$this->DB->query('SELECT nickname, hide, members_display_name AS ooc FROM `srv_characters` JOIN `members` ON `global_id`=`member_id` WHERE `logged` = 1 ORDER BY admin DESC, player_uid');
			$this->DB->execute();

		while($row = $this->DB->fetch())
		{
			//$row['hours'] = floor($row['online'] / 3600);
			//$row['minutes'] = floor(($row['online'] - floor($row['online'] / 3600) * 3600) / 60);
			
			$row['nickname'] = $row['hide'] == 0 ? str_replace("_", " ", $row['nickname']) : "Potać ukryta";
			$online[] = $row;
		}

			header('Content-Type: application/json');
			echo json_encode($online);

	}

}
?>
