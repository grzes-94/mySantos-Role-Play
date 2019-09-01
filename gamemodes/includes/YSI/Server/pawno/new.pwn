#include <YSI>

//#define FILTERSCRIPT

#if defined FILTERSCRIPT

Script_OnFilterScriptInit()
{
	print("\n--------------------------------------");
	print(" Blank Filterscript by your name here");
	print("--------------------------------------\n");
	return 1;
}

Script_OnFilterScriptExit()
{
	return 1;
}

#else

main()
{
	print("\n--------------------------------");
	print(" YSI Gamemode by your name here");
	print("--------------------------------\n");
}

#endif

Text_RegisterTag(connect);

Script_OnGameModeInit()
{
	// Don't use these lines if it's a filterscript
	SetGameModeText("Blank Script");
	AddPlayerClass(0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0);
	// Put your command declarations below
	ycmd("mycommand");
	// Put your command declarations above
	Langs_AddLanguage("EN", "English");
	Langs_AddFile("standard_text");
	return LoadScript();
}

Command_(mycommand)
{
	// Your code here
	return 1;
}

Script_OnGameModeExit()
{
	return 1;
}

Script_OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
	return 1;
}

Script_OnPlayerRequestSpawn(playerid)
{
	return 1;
}

Script_OnPlayerConnect(playerid)
{
	SendClientMessage2Format(playerid, 0xFF0000AA, "YSI_GREETING", ReturnPlayerName(playerid), playerid);
	return 1;
}

Script_OnPlayerDisconnect(playerid, reason)
{
	return 1;
}

Script_OnPlayerSpawn(playerid)
{
	return 1;
}

Script_OnPlayerDeath(playerid, killerid, reason)
{
	return 1;
}

Script_OnVehicleSpawn(vehicleid)
{
	return 1;
}

Script_OnVehicleDeath(vehicleid, killerid)
{
	return 1;
}

Script_OnPlayerText(playerid, text[])
{
	return 1;
}

Script_OnPlayerPrivmsg(playerid, recieverid, text[])
{
	return 1;
}

Script_OnPlayerCommandText(playerid, cmdtext[])
{
	return 0;
}

Script_OnPlayerInfoChange(playerid)
{
	return 1;
}

Script_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	return 1;
}

Script_OnPlayerExitVehicle(playerid, vehicleid)
{
	return 1;
}

Script_OnPlayerStateChange(playerid, newstate, oldstate)
{
	return 1;
}

Script_OnPlayerEnterCheckpoint(playerid)
{
	return 1;
}

Script_OnPlayerLeaveCheckpoint(playerid)
{
	return 1;
}

Script_OnPlayerEnterRaceCheckpoint(playerid)
{
	return 1;
}

Script_OnPlayerLeaveRaceCheckpoint(playerid)
{
	return 1;
}

Script_OnRconCommand(cmd[])
{
	return 1;
}

Script_OnObjectMoved(objectid)
{
	return 1;
}

Script_OnPlayerObjectMoved(playerid, objectid)
{
	return 1;
}

Script_OnPlayerPickUpPickup(playerid, pickupid)
{
	return 1;
}

Script_OnPlayerSelectedMenuRow(playerid, row)
{
	return 1;
}

Script_OnPlayerExitedMenu(playerid)
{
	return 1;
}

Script_OnVehicleMod(vehicleid, componentid)
{
	return 1;
}

Script_OnVehiclePaintjob(vehicleid, paintjobid)
{
	return 1;
}

Script_OnVehicleRespray(vehicleid, color1, color2)
{
	return 1;
}

Script_OnPlayerLogin(playerid, data[])
{
	return 1;
}

Script_OnPlayerLogout(playerid)
{
	return 1;
}
