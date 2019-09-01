<?php
class public_msrp_admin_bans extends ipsCommand
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


		$count = $this->DB->query('SELECT COUNT(*) as max FROM `srv_bans`');
		$count = $this->DB->fetch($count);



		/* Parsowanie paginacji */
		$pagination = $this->registry->getClass('output')->generatePagination( array(
																		'totalItems'		=> $count['max'],
																		'itemsPerPage'		=> 100,
																		'baseUrl'			=> "app=msrp&module=admin&section=bans",
																		)
																);

		$this->DB->query(sprintf('SELECT * FROM `srv_bans` ORDER by ban_id DESC LIMIT %d,100',$this->request['st']));
		$this->DB->execute();

		while($row = $this->DB->fetch())
		{
			$penalty[] = $row;
		}

		$template = $this->registry->output->getTemplate('msrp')->msrp_admin_bans($penalty,$pagination);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('Panel administratora');
		$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin' );
		$this->registry->output->addNavigation( 'Bany', 'app=msrp&module=admin&section=bans' );
		$this->registry->getClass('output')->sendOutput();
	}

}
?>
