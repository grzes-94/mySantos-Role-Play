<?php

class profile_player extends profile_plugin_parent
{
	/**
	* Return HTML block
	*
	* @access	public
	* @param	array		Member information
	* @return	string		HTML block
	*/
	public function return_html_block( $member = array() )
	{
		$characters = $this->fetchCharacters( $member['member_id'] );
		$premium = $this->isMemberPremium($member['member_id']);
		$logs = $this->fetchLogs( $member['member_id'] );

		return $this->registry->getClass( 'output' )->getTemplate( 'msrp' )->profileCard( $characters, $logs, $member, $premium );
	}

	protected function fetchCharacters( $member )
	{
		$this->DB->query( 'SELECT * FROM `srv_characters` WHERE `global_id` = '. $member );

		while( $row = $this->DB->fetch() )
		{
			$row['nickname'] = str_replace( '_', ' ', $row['nickname'] );
			$characters[] = $row;
		}

		return $characters;
	}

	protected function fetchLogs( $member )
	{
		$this->DB->query( 'SELECT * FROM srv_penalty
			WHERE player_gid = '. $member .' ORDER BY time DESC LIMIT 100');

			while( $row = $this->DB->fetch() )
			{
				$row['type'] = $this->getPenaltyName( $row['type'] );
				$logs[] = $row;
			}

			return $logs;
	}
		protected function isMemberPremium($memberid)
		{
			$tmie = time();
			$this->DB->query("SELECT `member_group_id`, `mgroup_others` FROM `members` WHERE `member_id` = $memberid ");
			$res=$this->DB->fetch();
			return ( $res['member_group_id'] == 9 || in_array(9, explode(',', $res['mgroup_others'])) );
		}
		protected function getPenaltyName( $type )
		{
			switch( $type )
			{
				case 1:	return 'Warn';
				case 2:	return 'Kick';
				case 3:	return 'Ban';
				case 4:	return 'Blokada postaci';
				case 5:	return 'GameScore';
				case 6: return'Admin Jail';
				case 7: return 'UnWarn';
				case 8:	return'Blokada biegania';
				case 9:	return 'Blokada broni';
				case 10: return 'Blokada prowadzenia';
				case 11: return 'Blokada OOC';
				case 12:	return 'Ban 4/4';
				case 13: return "Klątwa";
				case 14: return "Ban (klątwa)";
			}
			return "Błąd";
		}
	}
