<?php
class public_msrp_group_choosegroup extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
		if(!$this->memberData['member_id'])
		{
			$this->registry->output->showError('Nie jesteś zalogowany, zrób to aby otrzymać dostęp do tej części forum.',0);
		}

			$this->DB->query('SELECT `global_id` FROM `srv_characters` WHERE `player_uid` = '.strval($this->request['character']).'');
			$this->DB->execute();
			$char = $this->DB->fetch();

		if($char['global_id'] != $this->memberData['member_id'])
		{
			$this->registry->output->showError('Nie jesteś zalogowany, zrób to aby otrzymać dostęp do tej części forum.',0);
		}

			$this->DB->query('SELECT * FROM `srv_groups_members` WHERE `player_uid` = '.strval($this->request['character']).' ORDER BY `group_uid`');
			$this->DB->execute();

			while($row = $this->DB->fetch())
			{
				$groups[] = $row;
			}

		if(isset($this->request['choose_group']))
		{
			if(!$this->request['choice'])
			{
				$this->registry->output->showError('Forumlarz został źle pobrany, pobierz go ponownie.',0);
			}
			else
			{
				if(is_numeric($this->request['choice']))
				{
					$this->registry->output->silentRedirect( $this->registry->output->buildUrl('app=msrp&module=group&section=dashboard&group='.$this->request['choice'].'&character='.$this->request['character'].'') );
				}
				else
				{
					$this->registry->output->showError('Forumlarz został źle pobrany, pobierz go ponownie.',0);
				}
			}
		}

		$template = $this->registry->output->getTemplate('msrp')->msrp_group_choose($groups);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('Wybór grupy');
		$this->registry->output->addNavigation( 'Panel Grupy', 'app=msrp&module=group' );
		$this->registry->output->addNavigation( 'Wybór grupy', 'app=msrp&module=group' );
		$this->registry->getClass('output')->sendOutput();
	}


}
?>
