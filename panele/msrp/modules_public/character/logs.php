<?php
class public_msrp_character_logs extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
		if(!$this->memberData['member_id'])
		{
			$this->registry->output->showError('Niestety, nie jesteś zalogowany dlatego dostęp do tej części forum został zablokowany.',0);
		}
		$count = $this->DB->query('SELECT COUNT(*) as max FROM `srv_login_logs` WHERE `character_id`='.$this->memberData['member_id']);
		$count = $this->DB->fetch($count);
		$st=$this->request['st'];
		$perpage=50;

		/* Parsowanie paginacji */
		$pagination = $this->registry->getClass('output')->generatePagination( array(
			'totalItems'		=> $count['max'],
			'itemsPerPage'		=> $perpage,
			'currentStartValue'	=> $st,
			'baseUrl'			=> "app=msrp&module=character&section=logs",
		)
	);

	$this->DB->query(sprintf('SELECT l.*, p.nickname FROM srv_login_logs l, srv_characters p WHERE l.character_id = p.player_uid AND p.global_id = %d ORDER BY time DESC LIMIT %d,%d',$this->memberData['member_id'],$st,$perpage));
	$this->DB->execute();

	while($row = $this->DB->fetch())
	{
		$row['nickname'] = str_replace("_", " ", $row['nickname']);
		$logs[] = $row;
	}

	$template = $this->registry->output->getTemplate('msrp')->msrp_logs($pagination,$logs);
	$this->registry->getClass('output')->addContent($template);
	$this->registry->output->setTitle('Logi logowań');
	$this->registry->output->addNavigation( 'Panel Gry', 'app=msrp' );
	$this->registry->output->addNavigation( 'Logi logowań', 'app=msrp&module=character&section=logs' );
	$this->registry->getClass('output')->sendOutput();
}

}
?>
