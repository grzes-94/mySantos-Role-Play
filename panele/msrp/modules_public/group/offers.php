<?php

class public_msrp_group_doors extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
		require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/group.php' );
		$this->registry->setClass( 'group', new group( $registry ) );
		$group = $this->registry->getClass( 'group' );

		$group->checkCharacterAndGroup( intval( $this->request['group'] ), intval( $this->request['character'] ), $this->memberData['member_id'] );
		$information = $group->fetchGroupInformation( intval( $this->request['group'] ) );

		$doors = $this->fetchDoors( $information['UID'] );

		$this->registry->output->setTitle( 'Zarządzanie drzwiami' );
		$this->registry->output->addNavigation( 'Panel Grupy', 'app=msrp&module=group' );
		$this->registry->output->addNavigation( ''. $information['name'] .' (UID: '. $information['UID'] .')', 'app=msrp&module=group&section=doors&group='. $this->request['group'] .'&character='. $this->request['character'] );
		$this->registry->output->addContent( $this->registry->output->getTemplate( 'msrp' )->msrp_group_doors( $doors ) );
		$this->registry->output->sendOutput();
	}

	protected function fetchDoors( $group )
	{
		$this->DB->query('SELECT * FROM `srv_doors` WHERE `ownertyp` = 2 AND `owner` = ' . $group . '');

		while( $row = $this->DB->fetch() )
		{
			if( $row['block'] )
			{
				$row['_status'] = "<font color='darkred'>Zablokowane</font>";
			}
			else
			{
				if( $row['lock'] )
				{
					$row['_status'] = "<font color='navy'>Zamknięte</font>";
				}
				else
				{
					$row['_status'] = "<font color='green'>Otwarte</font>";
				}
			}

			$doors[] = $row;
		}

		return $doors;
	}
}
