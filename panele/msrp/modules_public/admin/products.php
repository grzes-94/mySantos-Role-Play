<?php
class public_msrp_admin_products extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
		require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/functions.php' );
		$this->registry->setClass( 'functions', new functions( $registry ) );
		$functions = $this->registry->getClass( 'functions' );


		if(! $functions->IsGruopAdmin($this->memberData['member_group_id']))
		{
			$this->registry->output->silentRedirect('index.php');
		}

			echo '<h3 class="maintitle">Lista produktów grupy</h3>';

			echo '<table class="ipb_table">
					<tbody>
						<tr class="header">
							<th scope="col" class="short">Nazwa produktu</th>
							<th scope="col" class="short">Ilość</th>
							<th scope="col" class="short">Cena hurtowa</th>
						</tr>';
			$licz = $this->DB->query('SELECT * FROM `srv_orders_products` WHERE `group_id` = '.$this->request['uid'].'');

			if($this->DB->getTotalRows( $licz ))
			{
				$this->DB->query('SELECT * FROM `srv_orders_products` WHERE `group_id` = '.$this->request['uid'].'');
				while($row = $this->DB->fetch())
				{
					echo '<tr>
							<th class="short"> '.$row['name'].'</th>
							<th class="short">'.$row['value2'].'</th>
							<th class="short"><font color="green"><b>$</b></font> '.$row['price'].'</th>
						  </tr>';
				}
			}
			else
			{
				echo '<tr colspan="4"><td>Nie znaleziono żadnych produktów w magazynie.</td></tr>';
			}

			echo '	</tbody>
				  </table>';

	}
}
?>
