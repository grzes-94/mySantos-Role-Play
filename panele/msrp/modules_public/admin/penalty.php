<?php
class public_msrp_admin_penalty extends ipsCommand
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

		$count = $this->DB->query('SELECT COUNT(*) as max FROM `srv_penalty`');
		$count = $this->DB->fetch($count);

		/* Parsowanie paginacji */
		$pagination = $this->registry->getClass('output')->generatePagination( array(
																		'totalItems'		=> $count['max'],
																		'itemsPerPage'		=> 100,
																		'baseUrl'			=> "app=msrp&module=admin&section=penalty",
																		)
																);

		$this->DB->query(sprintf('SELECT * FROM `srv_penalty` ORDER by time DESC LIMIT %d,%d',$this->request['st'],100));
		$this->DB->execute();

		while($row = $this->DB->fetch())
		{
			$row['type']=$functions->getPenaltyName($row['type']);

			$penalty[] = $row;
		}

		$template = $this->registry->output->getTemplate('msrp')->msrp_admin_penalty($penalty,$pagination);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('Nadane kary');
		$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin' );
		$this->registry->output->addNavigation( 'Nadane kary', 'app=msrp&module=admin&section=penalty' );
		$this->registry->getClass('output')->sendOutput();
	}

}
?>
