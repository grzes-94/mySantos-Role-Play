<?php
class public_msrp_group_choosechar extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
		if(!$this->memberData['member_id'])
		{
			$this->registry->output->showError('Nie jesteś zalogowany, zrób to aby otrzymać dostęp do tej części forum.',0);
		}

			$this->DB->query('SELECT * FROM `srv_characters` WHERE `global_id` = '.$this->memberData['member_id'].'');
			$this->DB->execute();

			while($row = $this->DB->fetch())
			{
				$row['nickname'] = str_replace("_", " ", $row['nickname']);
				$characters[] = $row;
			}

		if(isset($this->request['choose_char']))
		{
			if(!$this->request['choice'])
			{
				$this->registry->output->showError('Forumlarz został źle pobrany, pobierz go ponownie.',0);
			}
			else
			{
				if(is_numeric($this->request['choice']))
				{
					$this->registry->output->silentRedirect( $this->registry->output->buildUrl('app=msrp&module=group&section=choosegroup&character='.$this->request['choice'].'') );
				}
				else
				{
					$this->registry->output->showError('Forumlarz został źle pobrany, pobierz go ponownie.',0);
				}
			}
		}

		$template = $this->registry->output->getTemplate('msrp')->msrp_char_choose($characters);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('Wybór postaci');
		$this->registry->output->addNavigation( 'Panel Grupy', 'app=msrp&module=group' );
		$this->registry->output->addNavigation( 'Wybór postaci', 'app=msrp&module=group' );
		$this->registry->getClass('output')->sendOutput();
	}


}
?>
