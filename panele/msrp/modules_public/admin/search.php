<?php
class public_msrp_admin_search extends ipsCommand
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

			echo '<h3 class="maintitle">Wyszukiwanie wszystkich postaci użytkownika</h3>';

			echo '<table class="ipb_table">
					<tbody>
						<tr class="header">
							<th scope="col">Postać</th>
							<th scope="col">Płeć</th>
							<th scope="col">Suma pieniędzy</th>
							<th scope="col">Czas gry</th>
						</tr>';
			$licz = $this->DB->query('SELECT * FROM `srv_characters` WHERE `global_id` = '.$this->request['uid'].'');

			if($this->DB->getTotalRows( $licz ))
			{
				$this->DB->query('SELECT * FROM `srv_characters` WHERE `global_id` = '.$this->request['uid'].'');
				while($row = $this->DB->fetch())
				{
					$cash = $row['cash'] + $row['credit'];

					if($row['sex'] == 0)
					{
						$row['sex'] = 'Kobieta';
					}
					else
					{
						$row['sex'] = 'Mężczyzna';
					}

					$row['_name'] = str_replace("_", " ", $row['nickname']);

					$row['hours'] = floor($row['online'] / 3600);
					$row['minutes'] = floor(($row['online'] - floor($row['online'] / 3600) * 3600) / 60);

					echo '<tr>
							<th>'.$row['_name'].' ('.$row['player_uid'].')</th>
							<th>'.$row['sex'].'</th>
							<th><font color="green"><b>$</b></font> '.$cash.'</th>
							<th><b>'.$row['hours'].'</b>h, <b>'.$row['minutes'].'</b>min</th>
						  </tr>';
				}
			}
			else
			{
				echo '<tr colspan="4"><td>Nie znaleziono żadnej postaci.</td></tr>';
			}

			echo '	</tbody>
				  </table>';

	}
}
?>
