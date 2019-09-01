<?php
class public_msrp_admin_deactivate extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
			$this->DB->query('SELECT * FROM `srv_characters` WHERE `player_uid` = '.$this->request['uid'].'');
			$row = $this->DB->fetch();

			if($this->memberData['member_group_id'] != 4 && $this->memberData['member_group_id'] == 7)
			{
				$this->registry->output->showError('Wybrana postać nie jest przypisana do Twojego konta globalnego.',0);
			}

			if($row['block'] & 1)
			{
				$this->registry->output->showError('Wybrana postać posiada nałożoną już blokadę dezaktywacyjną.',0);
			}

			$row['_name'] = str_replace("_", " ", $row['nickname']);

			echo '<h3 class="maintitle">Potwierdzenie dezaktywacji postaci</h3>
			<br />
			<center>Dezaktywacja postaci została potwierdzona przez system.</center><br /><br />&nbsp&nbsp<b>Postać</b>: '.$row['_name'].'<br /><br />
			&nbsp&nbsp<b>Uprawnienie:</b> Dezaktywacja postaci
			<br /><br /><b><center>Dokonaj pełnego potwierdzenia akcji w celu zakończenia procesu dezaktywacji.</center></b><br />
			<form action="index.php?app=msrp&module=admin&section=deactivate&uid='.$this->request['uid'].'" method="post">
			<center>
			<input class="input_submit" type="submit" name="submit" value="Potwierdzam" />
			<input class="input_submit" type="submit" name="submitno" value="Anuluj" />
			</center>
			<br />
			<form>';

			if(!empty($_POST['submit']))
			{
				$this->DB->query('UPDATE `srv_characters` SET `block` = 1 WHERE `player_uid` = '.$this->request['uid'].'');
				$this->registry->output->silentRedirect('index.php?&app=msrp&module=admin&section=chars');
			}

			if(!empty($_POST['submitno']))
			{
				$this->registry->output->silentRedirect('index.php?&app=msrp&module=admin&section=chars');
			}

	}
}
?>
