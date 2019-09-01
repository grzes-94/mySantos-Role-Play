<?php
class public_msrp_admin_global extends ipsCommand
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

		$count = $this->DB->query('SELECT COUNT(*) as max FROM `members`');
		$count = $this->DB->fetch($count);

		/* Parsowanie paginacji */
		$pagination = $this->registry->getClass('output')->generatePagination( array(
																		'totalItems'		=> $count['max'],
																		'itemsPerPage'		=> 100,
																		'baseUrl'			=> "app=msrp&module=admin&section=global",
																		)
																);

		$this->DB->query(sprintf('SELECT * FROM `members` ORDER by `member_id` ASC LIMIT %d,100',$this->request['st']));
		$this->DB->execute();

		while($row = $this->DB->fetch())
		{
			$members[] = $row;
		}

		$template = $this->registry->output->getTemplate('msrp')->msrp_admin_global($members, $pagination);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('Konta globalne');
		$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin' );
		$this->registry->output->addNavigation( 'Konta globalne', 'app=msrp&module=admin&section=global' );
		$this->registry->getClass('output')->sendOutput();
	}

}
?>
