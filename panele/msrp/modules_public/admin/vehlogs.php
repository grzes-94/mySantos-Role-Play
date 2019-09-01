<?php
class public_msrp_admin_vehlogs extends ipsCommand
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

		$count = $this->DB->query('SELECT COUNT(*) as max FROM `srv_veh_logs`');
		$count = $this->DB->fetch($count);


		$st=$this->request['st'];
		$perpage=100;

		/* Parsowanie paginacji */
		$pagination = $this->registry->getClass('output')->generatePagination( array(
			'totalItems'		=> $count['max'],
			'itemsPerPage'		=> $perpage,
			'currentStartValue'	=> $st,
			'baseUrl'			=> "app=msrp&module=admin&section=vehlogs",
		)
	 );

	$query = $this->DB->query(sprintf('SELECT * FROM `srv_veh_logs` ORDER by `time` DESC LIMIT %d,%d',$st,$perpage));

	while($row = $query->fetch_assoc())
	{

			switch($row['type'])
			{
				case 1:
				{
					$row['from'] = $functions->GetCharacterName($row['from_uid'],true)."<br />".$functions->GetMemberName($row['from_gid']);

					$row['to']= $functions->GetCharacterName($row['to_uid'],true)."<br />".$functions->GetMemberName($row['to_gid']);
					break;
				}
				case 2:
				{
					$from=$functions->GetGroupName($row['from_gid']);
					$row['from']='<a href="index.php?app=msrp&module=admin&section=groupinfo&uid='.$row['from_gid'].'">'.$from.'</a>';
					$row['to']= $functions->GetCharacterName($row['to_uid'],true)."<br />".$functions->GetMemberName($row['to_gid']);
					break;
				}
				case 3:
				{
					$to=$this->registry->getClass('functions')->GetGroupName($row['to_gid']);
					$row['to']='<a href="index.php?app=msrp&module=admin&section=groupinfo&uid='.$row['to_gid'].'">'.$to.'</a>';

					$nick = $this->registry->getClass('functions')->GetMemberName($row['from_gid']);
					$from =$this->registry->getClass('functions')->GetCharacterName($row['from_uid']);
					$row['from']='<a href="index.php?app=msrp&module=character&section=showchar&uid='.$row['from_uid'].'">'.$from.'</a><br />'.$nick;
					break;
				}
			}

		$row['value']= $functions->formatDollars($row['value']);
		$row['modelname']=$functions->GetVehicleModelName($row['model']);
		$logs[] = $row;
	}

	$template = $this->registry->output->getTemplate('msrp')->msrp_admin_vehlogs($pagination, $logs);
	$this->registry->getClass('output')->addContent($template);
	$this->registry->output->setTitle('Logi pojazdów');
	$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin' );
	$this->registry->output->addNavigation( 'Logi pojazdów', 'app=msrp&module=admin&section=vehlogs' );
	$this->registry->getClass('output')->sendOutput();
  }

}
