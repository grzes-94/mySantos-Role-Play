<?php
class public_msrp_ajax_newapp extends ipsAjaxCommand
{

	public function doExecute( ipsRegistry $registry ) 
	{		
		if(!empty($_POST['save']))
		{
			if($this->request['char'] == 0)
			{
				$this->registry->output->showError('Postać nie została wybrana!',0);
			}
			
			$cookie = $this->request['char'];
			IPSText::getTextClass('bbcode')->parse_html		= 1;
			IPSText::getTextClass('bbcode')->parse_nl2br	= 0;
			IPSText::getTextClass('bbcode')->parse_smilies	= 1;
			IPSText::getTextClass('bbcode')->parse_bbcode	= 0;
			IPSText::getTextClass('bbcode')->parsing_section		= 'msrp_ajax_newapp';
			IPSText::getTextClass('bbcode')->parsing_mgroup			= $this->memberData['member_group_id'];
			IPSText::getTextClass('bbcode')->parsing_mgroup_others	= $this->memberData['mgroup_others'];
			
			$description1 = $this->DB->addSlashes(IPSText::getTextClass('bbcode')->preDbParse( $this->request['saveApplication1'] ));
			$description2 = $this->DB->addSlashes(IPSText::getTextClass('bbcode')->preDbParse( $this->request['saveApplication2'] ));
			$description3 = $this->DB->addSlashes(IPSText::getTextClass('bbcode')->preDbParse( $this->request['saveApplication3'] ));
			$description4 = $this->DB->addSlashes(IPSText::getTextClass('bbcode')->preDbParse( $this->request['saveApplication4'] ));
			$description5 = $this->DB->addSlashes(IPSText::getTextClass('bbcode')->preDbParse( $this->request['saveApplication5'] ));

			$q1 = $_COOKIE['Quest1'];
			$q2 = $_COOKIE['Quest2'];
			$q3 = $_COOKIE['Quest3'];
			$q4 = $_COOKIE['Quest4'];
			$q5 = $_COOKIE['Quest5'];
			
			$this->DB->query('SELECT `kolejka` FROM `msrp_applications` WHERE `kolejka` > 0');
			$this->DB->execute();
			$num = $this->DB->getTotalRows();
			$num++;
			$this->DB->query(sprintf('INSERT INTO msrp_applications (pid,owner_app,q1,q2,q3,q4,q5,a1,a2,a3,a4,a5,dateline,status,kolejka) VALUES(%d,%d,%d,%d,%d,%d,%d,\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',%d,%d,%d)',
				$cookie,
				$this->memberData['member_id'],
				$q1,
				$q2,
				$q3,
				$q4,
				$q5,
				$description1,
				$description2,
				$description3,
				$description4,
				$description5,
				IPS_UNIX_TIME_NOW,
				1,
				$num
				
			));
			$this->DB->execute();

			setcookie("CharacterID", 0);
			setcookie("Quest1", 0);
			setcookie("Quest2", 0);
			setcookie("Quest3", 0);
			setcookie("Quest4", 0);
			setcookie("Quest5", 0);
			
			$this->registry->output->silentRedirect('index.php?&app=msrp&module=character&section=list');
		}
		
		$this->DB->query('SELECT * FROM `fc_characters` WHERE `global_uid` = '.intval($this->memberData['member_id']).'  AND `block` = 1024 LIMIT 10');
		$this->DB->execute();
		
		while($row = $this->DB->fetch())
		{
			$row['name'] = str_replace("_", " ", $row['name']);
			$chars[] = $row;
		}
		
		$this->DB->query('SELECT * FROM `msrp_questions` ORDER BY rand() LIMIT 5');
		$this->DB->execute();

			while($row = $this->DB->fetch())
			{
				$i++;
				$editor = '<textarea style="margin: 0px; width: 699px; height: 91px;" name="saveApplication'.$i.'" required></textarea>';
				$pytanie = $row['question'];
				$ret .= "<fieldset class='submit'><strong>Pytanie $i:</strong> $pytanie</fieldset>$editor";
				setcookie("Quest$i", $row['uid']);
			}
		
		$this->returnHtml($this->registry->output->getTemplate('msrp')->msrp_ajax_newapp($chars, $ret));
	}
}
?>