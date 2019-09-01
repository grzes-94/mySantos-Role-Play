<?php
class public_msrp_admin_editcar extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
		if($this->memberData['member_group_id'] != 4)
		{
			$this->registry->output->silentRedirect('index.php');
		}

		$this->DB->query('SELECT * FROM `srv_salon_vehicles` WHERE `model` = '.$this->request['uid'].'');
		$row = $this->DB->fetch();

		//BUTTON
		if(!empty($_POST['update']))
		{
			$this->DB->query('INSERT INTO `panel_admin_log` (`owner`, `log`, `date`) VALUES ('.$this->memberData['member_id'].', "Edytowal pojazd '.$row['name'].' pomyślnie.", "'.IPS_UNIX_TIME_NOW.'")');
			$this->DB->execute();

			$this->DB->query('UPDATE `srv_salon_vehicles` SET `category` = '.$_POST['category'].', `name` = "'.$_POST['name'].'", `price` = '.$_POST['price'].' WHERE `model` = '.$this->request['uid'].'');
			$this->registry->output->silentRedirect('index.php?&app=msrp&module=admin&section=salon');
		}

		if($row['category'] == 0)
		{
			$sex0 = 'selected="selected"';
		}
		else if($row['category'] == 1)
		{
			$sex1 = 'selected="selected"';
		}
		else if($row['category'] == 2)
		{
			$sex2 = 'selected="selected"';
		}
		else if($row['category'] == 3)
		{
			$sex3 = 'selected="selected"';
		}
		else if($row['category'] == 4)
		{
			$sex4 = 'selected="selected"';
		}
		else if($row['category'] == 5)
		{
			$sex5 = 'selected="selected"';
		}
		else
		{
			$sex6 = 'selected="selected"';
		}

		echo '<h3 class="maintitle">Edycja pojazdu  '.$row['name'].'</h3>
		<form method="post" action="index.php?app=msrp&module=admin&section=editcar&uid='.$this->request['uid'].'">
		<fieldset class="ipsSettings_section">
		<div>
		<ul>

		<li class="custom">
		<label for="field_1" class="ipsSettings_fieldtitle">Nazwa</label>
		<input type="text" size="20" class="input_text" name="name" value="'.$row['name'].'">


		</li>

		<li class="custom">
		<label for="field_3" class="ipsSettings_fieldtitle">Płeć</label>
		<select class="input_select" name="category">
		<option value="0" '.$sex0.'>Jednoslady</option>
		<option value="1" '.$sex1.'>Trzydrzwiowe</option>
		<option value="2" '.$sex2.'>Piecodrzwiowe</option>
		<option value="3" '.$sex3.'>Offroad</option>
		<option value="4" '.$sex4.'>Dostawcze</option>
		<option value="5" '.$sex5.'>Sportowe</option>
		<option value="-1" '.$sex6.'>Wycofany.</option>
		</select>




		<li class="custom">
		<label for="field_2" class="ipsSettings_fieldtitle">Cena</label>
		<input type="text" size="5" class="input_text" name="price" value="'.$row['price'].'">


		</li>


		</li>


		</ul>
		</div>
		</fieldset>
		<fieldset class="submit">
		<input type="submit" class="input_submit" name="update" value="Zapisz">
		</fieldset>
		</form>';

	}
}
?>
