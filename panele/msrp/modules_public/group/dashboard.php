<?php

class public_msrp_group_dashboard extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
		require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/group.php' );
		$this->registry->setClass( 'group', new group( $registry ) );
		$group = $this->registry->getClass( 'group' );

		require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/functions.php' );
		$this->registry->setClass( 'functions', new functions( $registry ) );
		$functions = $this->registry->getClass( 'functions' );

		$group->checkCharacterAndGroup( intval( $this->request['group'] ), intval( $this->request['character'] ), $this->memberData['member_id'] );
		$information = $group->fetchGroupInformation( intval( $this->request['group'] ) );

		$information['cash']= $functions->formatDollars(	$information['cash'] );
		$information['salary_account']= $functions->formatDollars(	$information['salary_account'] );

		$kind=$information['type'];
		if($kind >=10 && $kind!=20)
			$information['isbusiness']=true;
			else
			$information['isbusiness']=false;


			$admin=$functions->IsGruopAdmin($this->memberData['member_group_id'],true);

			$query =  $this->DB->query('SELECT * FROM `srv_vehicles` WHERE `ownertyp` =  2 AND `owner` = ' . $this->request['group'] . '');
			while( $row = $query->fetch_assoc() )
			{
				$row['modelname'] = $functions->getVehicleModelName($row['model']);
				if($row['last_driver'])
					$row['last_driver']=$functions->GetCharacterName($row['last_driver'],$admin);
				else
					$row['last_driver']="--";

				$vehicles[] = $row;
			}

		$this->registry->output->setTitle( 'Zarządzanie grupami' );
		$this->registry->output->addNavigation( 'Panel Grupy', 'app=msrp&module=group' );
		$this->registry->output->addNavigation( $information['name'] .' (UID: '. $information['UID'] .')', 'app=msrp&module=group&section=dashboard&group='. $this->request['group'] .'&character='. $this->request['character'] );
		$this->registry->output->addContent( $this->registry->output->getTemplate( 'msrp' )->msrp_group_dashboard( $information, $vehicles ) );
		$this->registry->output->sendOutput();
	}

}
