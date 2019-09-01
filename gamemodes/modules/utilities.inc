forward CreateFuelStation(owner,Float:x,Float:y,Float:z);
forward DeleteFuelStation(uid);
forward AddStationFuel(stationid,value);
forward GetPlayerStationID(playerid);
forward GetIntoBus(playerid,puid,from,to,dist);

forward LeaveBus2(playerid,to);
forward GetPlayerBusStop(playerid);
forward LeaveBus(playerid,puid,to,price);

public CreateFuelStation(owner,Float:x,Float:y,Float:z)
{
	new uid=0;
	for(new i = 1;i<MAX_STATIONS;i++)
	{
		if(!StationInfo[i][sUID])
		{
			uid=i;
			break;
		}
	}
	if(!uid) return 0;

	StationInfo[uid][sUID]=uid;
	StationInfo[uid][sOwner]=owner;
	StationInfo[uid][sFuel]=0;
	StationInfo[uid][sPosX]=x;
	StationInfo[uid][sPosY]=y;
	StationInfo[uid][sPosZ]=z;
	StationInfo[uid][sFuelCost]=SettingInfo[sFuelCost];

	mysql_query_format("INSERT INTO `srv_fuel_stations` VALUES ('%d', '%d', '%d', '%f', '%f', '%f', '%d')",
		uid,owner,0,x,y,z,StationInfo[uid][sFuelCost]);

	return uid;
}
public DeleteFuelStation(uid)
{
	if(uid<1 || uid >= MAX_STATIONS)
		return 0;

	mysql_query_format("DELETE FROM `srv_fuel_stations` WHERE `uid`='%d'",uid);

	StationInfo[uid][sUID]=0;
	StationInfo[uid][sOwner]=0;
	StationInfo[uid][sFuel]=0;
	StationInfo[uid][sPosX]=0.0;
	StationInfo[uid][sPosY]=0.0;
	StationInfo[uid][sPosZ]=0.0;

	return 1;
}
public AddStationFuel(stationid,value)
{
	StationInfo[stationid][sFuel]+=value;
	if(StationInfo[stationid][sFuel]<0)
		StationInfo[stationid][sFuel]=0;

	new query[128];
	format(query,sizeof(query),"UPDATE `srv_fuel_stations` SET `fuel`='%d' WHERE `uid`='%d'",StationInfo[stationid][sFuel],stationid);
	mysql_query(query);

	return 1;
}
public GetPlayerStationID(playerid)
{
	for(new i=1; i<MAX_STATIONS; i++)
	{
		if(IsPlayerInRangeOfPoint(playerid, 30.0, StationInfo[i][sPosX], StationInfo[i][sPosY], StationInfo[i][sPosZ]))
			return i;
	}
	return 0;
}
public GetPlayerBusStop(playerid)
{
	if(GetPlayerVirtualWorld(playerid))
		return 0;
	new Float:x,Float:y,Float:z;
	GetPlayerPos(playerid,x,y,z);
	for(new i=1;i<MAX_BUS_STOPS;i++)
	{
		if(BusInfo[i][bUID])
		{
			if(IsPlayerInRangeOfPoint(playerid, 5.0, BusInfo[i][bPosX], BusInfo[i][bPosY],BusInfo[i][bPosZ]))
				return i;
		}
	}
	return 0;
}
public GetIntoBus(playerid,puid,from,to,dist)
{
	if(CharacterInfo[playerid][pUID]!=puid)
		return 1;
	if(!IsPlayerInRangeOfPoint(playerid, 15.0, BusInfo[from][bPosX],  BusInfo[from][bPosY],  BusInfo[from][bPosZ]))
		return Tip(playerid,5,"Oddaliles sie od przystanku, autobus odjechal.");
	cmd_me(playerid,"wsiada do autobusu.");
	new price;
	SetSpawnInfo(playerid, 0, CharacterInfo[playerid][pSkin], BusInfo[to][bPosX],BusInfo[to][bPosY],BusInfo[to][bPosZ], BusInfo[to][bAngle], -1, -1, -1, -1, -1, -1);	
	
	if(CharacterInfo[playerid][pHours]>5) price = dist*4;
	SetPlayerVirtualWorld(playerid, 255);
	
	CharacterInfo[playerid][pACLastJustification] = gettime();
	
	SetPVarInt(playerid,"pBus",from);
	SetPlayerCameraPos(playerid, BusInfo[from][bPosX],  BusInfo[from][bPosY],  BusInfo[from][bPosZ]+30.0);
	SetPlayerCameraLookAt(playerid, BusInfo[to][bPosX],  BusInfo[to][bPosY],  BusInfo[to][bPosZ], CAMERA_CUT);
	TogglePlayerSpectating(playerid, true);
	SetSpawnInfo(playerid, 0, CharacterInfo[playerid][pSkin], BusInfo[to][bPosX],BusInfo[to][bPosY],BusInfo[to][bPosZ], BusInfo[to][bAngle], -1, -1, -1, -1, -1, -1);	
	InterpolateCameraPos(playerid, BusInfo[from][bPosX],  BusInfo[from][bPosY],  BusInfo[from][bPosZ]+30.0,  BusInfo[to][bPosX],BusInfo[to][bPosY],BusInfo[to][bPosZ]+30.0, dist*4000, CAMERA_MOVE);
	if(!(CharacterInfo[playerid][pStatus] & STATUS_BUS ))
		CharacterInfo[playerid][pStatus] += STATUS_BUS;

	SetTimerEx("LeaveBus", dist*4000, false, "iiii",playerid,CharacterInfo[playerid][pUID],to,price);

	return 1;
}
public LeaveBus(playerid,puid,to,price)
{
	if(CharacterInfo[playerid][pUID] != puid)
		return 1;
	SetSpawnInfo(playerid, 0, CharacterInfo[playerid][pSkin], BusInfo[to][bPosX],BusInfo[to][bPosY],BusInfo[to][bPosZ], BusInfo[to][bAngle], -1, -1, -1, -1, -1, -1);	
	CharacterInfo[playerid][pACLastJustification] = gettime();
	
	TogglePlayerSpectating(playerid, false);
	SetPlayerVirtualWorld(playerid, 0);
	SetPlayerInterior(playerid, 0);

	DeletePVar(playerid, "pBus");
	GivePlayerCash(playerid,-price);
	
	cmd_me(playerid,"wysiada z autobusu.");

	
	SetTimerEx("LeaveBus2",1000,false,"ii",playerid,to);

	return 1;
}
public LeaveBus2(playerid,to)
{
	if(CharacterInfo[playerid][pStatus] & STATUS_BUS )
		CharacterInfo[playerid][pStatus] -= STATUS_BUS;
	SetSpawnInfo(playerid, 0, CharacterInfo[playerid][pSkin], SettingInfo[sSpawnX], SettingInfo[sSpawnY], SettingInfo[sSpawnZ], SettingInfo[sSpawnAngle], -1, -1, -1, -1, -1, -1);
	//SetPlayerPos(playerid,BusInfo[to][bPosX],BusInfo[to][bPosY],BusInfo[to][bPosZ]);
	CharacterInfo[playerid][pACLastJustification] = gettime();
	
	return 1;

}

stock EndJob(playerid)
{
	DeletePVar(playerid,"pJob");
	DisablePlayerCheckpoint(playerid);
	SetPlayerSpecialAction(playerid, 0);
	RemovePlayerAttachedObject(playerid, SLOT_JOB);
	CharacterInfo[playerid][pJobPhase] = 0;
	return 1;
}

stock IsSkinValid(id)
{
	return (id > 0 && id <=311) || (id > 20000 && id < 30000);
}