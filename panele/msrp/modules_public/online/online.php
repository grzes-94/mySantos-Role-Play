<?php
class public_msrp_online_online extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{

			$this->DB->query('SELECT global_id, nickname, hours,minutes, hide FROM `srv_characters` WHERE `logged` = 1 ORDER BY admin DESC, player_uid');
			$this->DB->execute();

		while($row = $this->DB->fetch())
		{
			//$row['hours'] = floor($row['online'] / 3600);
			//$row['minutes'] = floor(($row['online'] - floor($row['online'] / 3600) * 3600) / 60);
			$row['nickname'] = str_replace("_", " ", $row['nickname']);
			$online[] = $row;
		}

		$template = $this->registry->output->getTemplate('msrp')->msrp_online($online);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('Gracze online');
		$this->registry->output->addNavigation( 'Panel Gry', 'app=msrp' );
		$this->registry->output->addNavigation( 'Gracze online', 'app=msrp&module=online&section=online' );
		$this->registry->getClass('output')->sendOutput();
	}

}
?>
