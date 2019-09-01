<?php
class public_msrp_admin_active extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
			$this->DB->query('SELECT * FROM `srv_characters` WHERE `player_uid` = '.$this->request['uid'].'');
			$row = $this->DB->fetch();

			if($this->memberData['member_group_id'] != 4 || $this->memberData['member_group_id'] == 7)
			{
				if($row['global_id'] != $this->memberData['member_id'])
				{
					$this->registry->output->showError('Wybrana postać nie jest przypisana do Twojego konta globalnego.',0);
				}
			}

			if(!($row['block'] & 1) && !($row['block'] & 2))
			{
				$this->registry->output->showError('Wybrana postać nie posiada nałożonej blokady dezaktywacji.',0);
			}

			$row['_nick'] = str_replace("_", " ", $row['nickname']);

			echo '<h3 class="maintitle">Potwierdzenie aktywacji postaci</h3>
			<br />
			<center>Aktywacja postaci została potwierdzona przez system.</center><br /><br />&nbsp&nbsp<b>Postać</b>: '.$row['_nick'].'<br /><br />
			&nbsp&nbsp<b>Uprawnienie:</b> Aktywacja postaci
			<br /><br /><b><center>Dokonaj pełnego potwierdzenia akcji w celu zakończenia procesu aktywacji.</center></b><br />
			<form action="index.php?app=msrp&module=admin&section=active&uid='.$this->request['uid'].'" method="post">
			<center>
			<input class="input_submit" type="submit" name="submit" value="Potwierdzam" />
			<input class="input_submit" type="submit" name="submitno" value="Anuluj" />
			</center>
			<br />
			<form>';

			if(!empty($_POST['submit']))
			{
				$this->DB->query('UPDATE `srv_characters` SET `block` = 0 WHERE `player_uid` = '.$this->request['uid'].'');
				$this->registry->output->silentRedirect('index.php?&app=msrp&module=admin&section=chars');
			}

			if(!empty($_POST['submitno']))
			{
				$this->registry->output->silentRedirect('index.php?&app=msrp&module=admin&section=chars');
			}

	}
}
?>
