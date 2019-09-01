<?php

class public_msrp_group_jaillogs extends ipsCommand
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


		$result = $this->DB->query('SELECT * FROM `srv_jail_logs` WHERE `groupid`='.$this->request['group'].' ORDER BY `time` DESC');
		while($row = $result->fetch_assoc())
		{
			if($row['type']==1)
				$row['type']="Przetrzymanie (".$row['value']." h)";
			else
				$row['type']="Wypuszczenie z celi";

			$row['from']=$functions->GetCharacterName($row['from_uid'])."<br />".$functions->GetMemberName($row['from_gid']);
			$row['to']=$functions->GetCharacterName($row['to_uid']);


			$logs[]=$row;
		}

		$this->registry->output->setTitle( 'Logi przetrzymania' );
		$this->registry->output->addNavigation( 'Panel Grupy', 'app=msrp&module=group' );
		$this->registry->output->addNavigation( 'Logi przetrzymania', 'app=msrp&module=group&section=jaillogs&group='. $this->request['group'] .'&character='. $this->request['character'] );
		$this->registry->output->addContent( $this->registry->output->getTemplate( 'msrp' )->msrp_group_jaillogs( $logs ) );
		$this->registry->output->sendOutput();
	}


}
