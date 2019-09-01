<?php
class public_msrp_admin_stats extends ipsCommand
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
		$this->DB->allow_sub_select=1;
		$this->DB->query('SELECT
			(SELECT COUNT(*) FROM srv_characters) AS characters,
			(SELECT COUNT(*) FROM srv_vehicles) AS vehicles,
			(SELECT MAX(`UID`) FROM srv_vehicles) AS maxvehicle,
			(SELECT COUNT(*) FROM srv_objects) AS objects,
			(SELECT MAX(`UID`) FROM srv_objects) AS maxobject,
			(SELECT COUNT(*) FROM srv_items) AS items,
			(SELECT MAX(`UID`) FROM srv_items) AS maxitem,
			(SELECT COUNT(*) FROM srv_groups) AS groups,
			(SELECT MAX(`UID`) FROM srv_groups) AS maxgroup,
			(SELECT COUNT(*) FROM srv_doors) AS doors,
			(SELECT MAX(`UID`) FROM srv_doors) AS maxdoor,
			(SELECT COUNT(*) FROM srv_plants) AS plants,
			(SELECT MAX(`UID`) FROM srv_plants) AS maxplant,
			(SELECT COUNT(*) FROM srv_corpse) AS corpse,
			(SELECT MAX(`UID`) FROM srv_corpse) AS maxcorpse,
			(SELECT COUNT(*) FROM srv_corners) AS corners,
			(SELECT MAX(`UID`) FROM srv_corners) AS maxcorner,
			(SELECT COUNT(*) FROM srv_fuel_stations) AS fuel_stations,
			(SELECT MAX(`UID`) FROM srv_fuel_stations) AS maxfuel,
			(SELECT COUNT(*) FROM srv_safekeeps) AS safekeeps,
			(SELECT MAX(`UID`) FROM srv_safekeeps) AS maxsafekeep,
			(SELECT COUNT(*) FROM srv_3dtext) AS 3dtext,
			(SELECT MAX(`UID`) FROM srv_3dtext) AS max3dtext,
			(SELECT COUNT(*) FROM srv_bus) AS bus,
			(SELECT MAX(`UID`) FROM srv_bus) AS maxbus,
			(SELECT COUNT(*) FROM srv_descriptions) AS descriptions,
			(SELECT MAX(`UID`) FROM srv_descriptions) AS maxdescription
			');
			$stats=$this->DB->fetch();


		$this->DB->allow_sub_select=1;
		$template = $this->registry->output->getTemplate('msrp')->msrp_admin_stats($stats);
		$this->registry->getClass('output')->addContent($template);
		$this->registry->output->setTitle('Panel administratora');
		$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin' );
		$this->registry->output->addNavigation( 'Statystyki
		', 'app=msrp&module=admin&section=stats' );
		$this->registry->getClass('output')->sendOutput();
	}

}
?>
