<?php
class public_msrp_admin_faliedlogins extends ipsCommand
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

		$this->DB->query('SELECT COUNT(*) AS max FROM `srv_falied_logins`');
		$count = $this->DB->fetch();

		$st=$this->request['st'];
		$perpage=50;

		/* Parsowanie paginacji */
		$pagination = $this->registry->getClass('output')->generatePagination( array(
			'totalItems'		=> $count['max'],
			'itemsPerPage'		=> $perpage,
			'currentStartValue'	=> $st,
			'baseUrl'			=> "app=msrp&module=admin&section=faliedlogins",
		)
	);

	$query = $this->DB->query(sprintf('SELECT * FROM `srv_falied_logins` ORDER by `time` DESC LIMIT %d,%d',$st,$perpage));

	while($row = $query->fetch_assoc())
	{
		$row['player_uid']= $functions->GetCharacterName($row['player_uid'],true);
		$row['player_gid']= $functions->GetMemberName($row['player_gid']);
		$logs[] = $row;
	}

	$template = $this->registry->output->getTemplate('msrp')->msrp_admin_faliedlogins($pagination, $logs);
	$this->registry->getClass('output')->addContent($template);
	$this->registry->output->setTitle('Nieudane logowania');
	$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin' );
	$this->registry->output->addNavigation( 'Nieudane logowania', 'app=msrp&module=admin&section=faliedlogins' );
	$this->registry->getClass('output')->sendOutput();
  }

}
