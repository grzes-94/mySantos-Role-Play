<?php

class public_msrp_admin_jaillogs extends ipsCommand
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


		$result = $this->DB->query('SELECT * FROM `srv_jail_logs` ORDER BY `time` DESC');
		while($row = $result->fetch_assoc())
		{
			if($row['type']==1)
				$row['type']="Przetrzymanie (".$row['value']." h)";
			else
				$row['type']="Wypuszczenie z celi";

			$row['from']=$functions->GetCharacterName($row['from_uid'],true)."<br />".$functions->GetMemberName($row['from_gid']);
			$row['to']=$functions->GetCharacterName($row['to_uid'],true)."<br />".$functions->GetMemberName($row['to_gid']);
      $row['group']=$functions->GetGroupName($row['groupid'],true);


			$logs[]=$row;
		}

		$this->registry->output->setTitle( 'Logi przetrzymania' );
		$this->registry->output->addNavigation( 'Panel Grupy', 'app=msrp&module=group' );
		$this->registry->output->addNavigation( 'Logi przetrzymania', 'app=msrp&module=group&section=jaillogs&group='. $this->request['group'] .'&character='. $this->request['character'] );
		$this->registry->output->addContent( $this->registry->output->getTemplate( 'msrp' )->msrp_admin_jaillogs( $logs ) );
		$this->registry->output->sendOutput();
	}


}
