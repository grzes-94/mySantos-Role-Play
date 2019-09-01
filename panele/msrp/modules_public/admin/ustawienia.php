<?php
class public_msrp_admin_settings extends ipsCommand
{
	public function doExecute( ipsRegistry $registry ) 
	{
		if($this->memberData['member_group_id'] != 4 &&  $this->memberData['member_group_id'] == 7)
		{
			$this->registry->output->silentRedirect('index.php');
		}
		
		$count = $this->DB->query('SELECT COUNT(*) as max FROM `srv_settings`');
		$count = $this->DB->fetch($count);
		


		/* Parsowanie paginacji */
		$pagination = $this->registry->getClass('output')->generatePagination( array( 
																		'totalItems'		=> $count['max'],
																		'itemsPerPage'		=> 110000000,
																		'baseUrl'			=> "app=msrp&module=admin&section=ustawienia",
																		)
																);
		
		$this->DB->query(sprintf('SELECT * FROM `srv_settings`',$this->request['st']));	
		$this->DB->execute();	

		while($row = $this->DB->fetch())
		{                    
			$penalty[] = $row;
		}
		
		$template = $this->registry->output->getTemplate('msrp')->msrp_admin_settings($ustawienia);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('ACP');
		$this->registry->output->addNavigation( 'ACP', 'app=msrp&module=admin&section=ustawienia' );
		$this->registry->getClass('output')->sendOutput();
	}
	
}
?>