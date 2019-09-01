<?php

class public_msrp_group_logs extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
		require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/group.php' );
		$this->registry->setClass( 'group', new group( $registry ) );
		$group = $this->registry->getClass( 'group' );

		$group->checkCharacterAndGroup( intval( $this->request['group'] ), intval( $this->request['character'] ), $this->memberData['member_id'] );
		$information = $group->fetchGroupInformation( intval( $this->request['group'] ) );

		$group = $this->request['group'];

		$count = $this->DB->query('SELECT COUNT(*) as max FROM `srv_group_offer_logs` WHERE `groupid`='.$group);
		$count = $this->DB->fetch($count);

		$st=intval($this->request['st']);
		$perpage=100;

		/* Parsowanie paginacji */
		$pagination = $this->registry->getClass('output')->generatePagination( array(
			'totalItems'		=> $count['max'],
			'itemsPerPage'		=> $perpage,
			'currentStartValue'	=> $st,
			'baseUrl'			=> 'app=msrp&module=group&section=logs&group='. $this->request['group'] .'&character='. $this->request['character'],
		)
	);

		$this->DB->query('SELECT g.member_id, g.members_seo_name, g.members_display_name, g.member_group_id, c.global_id, c.nickname, l.* FROM srv_characters c, srv_group_offer_logs l, members g WHERE c.global_id = g.member_id AND c.player_uid = l.player_uid AND l.groupid = ' . $group . ' ORDER BY l.time DESC LIMIT '.$st.','.$perpage);

		while( $row = $this->DB->fetch() )
		{
			$row['nickname'] = str_replace("_", " ", $row['nickname']);


			$members[] = $row;
		}

		$this->registry->output->setTitle( 'Logi grupy' );
		$this->registry->output->addNavigation( 'Panel Grupy', 'app=msrp&module=group' );
		$this->registry->output->addNavigation( ''. $information['name'] .' (UID: '. $information['UID'] .')', 'app=msrp&module=group&section=logs&group='. $this->request['group'] .'&character='. $this->request['character'] );
		$this->registry->output->addContent( $this->registry->output->getTemplate( 'msrp' )->msrp_group_logs( $information, $members, $pagination ) );
		$this->registry->output->sendOutput();
	}


	public function fetchLogs( $group )
	{


		return $members;
	}

}
