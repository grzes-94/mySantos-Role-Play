forward StworzDrzwi(playerid, ownertyp, owner, name[31]);
forward DeleteDoor(uid);
forward SaveDoors(uid, what);
forward PlayerEnterDoor(playerid, uid);
forward PlayerExitDoor(playerid, uid);
forward IsDoorOwner(playerid, uid);
forward PlayerNearDoorType(playerid, type, Float:range);
forward IsDoorMember(playerid, uid);
forward HaveHome(playerid);

public StworzDrzwi(playerid, ownertyp, owner, name[31])
{
	new pickupid;
	new Float:PosX, Float:PosY, Float:PosZ, Float:Angle;
	
	if(ownertyp == OWNER_HOUSE_BUY)
		pickupid = 1273;
	else
		pickupid = 1239;
	
	GetPlayerPos(playerid, PosX, PosY, PosZ);
	GetPlayerFacingAngle(playerid, Angle);
	
	new uid;
	
	ForeachEx(i, MAX_DOORS)
	{
		if(DoorsInfo[i][dUID] == 0 && i != 0)
		{
			uid = i;
			break;
		}
	}
	if(uid+1>_DOOR_COUNT)
		_DOOR_COUNT=uid+1;
	
	mysql_real_escape_string(name,name);
	new query[512];
	format(query, sizeof(query), "INSERT INTO `srv_doors` VALUES ('%d', '%s', '%d', '%d', '%f', '%f', '%f', '%f', '%d', '%d', '%f', '%f', '%f', '%f', '%d', '%d', '1', '%d', '0', '', '0', '0', '0', '0')", uid, name, ownertyp, owner, PosX, PosY, PosZ, Angle, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), PosX, PosY, PosZ, Angle, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), pickupid);
	mysql_query(query);
	
	DoorsInfo[uid][dUID] = uid;
	DoorsInfo[uid][dName] = name;
	DoorsInfo[uid][dOwnerTyp] = ownertyp;
	DoorsInfo[uid][dOwner] = owner;
	DoorsInfo[uid][dEnterX] = PosX;
	DoorsInfo[uid][dEnterY] = PosY;
	DoorsInfo[uid][dEnterZ] = PosZ;
	DoorsInfo[uid][dEnterAngle] = Angle;
	DoorsInfo[uid][dEnterInt] = GetPlayerInterior(playerid);
	DoorsInfo[uid][dEnterVW] = GetPlayerVirtualWorld(playerid);
	DoorsInfo[uid][dExitX] = PosX;
	DoorsInfo[uid][dExitY] = PosY;
	DoorsInfo[uid][dExitZ] = PosZ;
	DoorsInfo[uid][dExitAngle] = Angle;
	DoorsInfo[uid][dExitInt] = GetPlayerInterior(playerid);
	DoorsInfo[uid][dExitVW] = GetPlayerVirtualWorld(playerid);
	DoorsInfo[uid][dLock] = 1;
	DoorsInfo[uid][dPickupID] = pickupid;
	DoorsInfo[uid][dGarage] = 
	DoorsInfo[uid][dIconID] = 
	DoorsInfo[uid][dPriceForEntry] = 
	DoorsInfo[uid][dTime] = 
	DoorsInfo[uid][dWeather] = 0;

	DoorsInfo[uid][dPickup] = CreateDynamicPickup(DoorsInfo[uid][dPickupID], 1, DoorsInfo[uid][dEnterX], DoorsInfo[uid][dEnterY], DoorsInfo[uid][dEnterZ], DoorsInfo[uid][dEnterVW], DoorsInfo[uid][dEnterInt]);
	
	return uid;
}
public DeleteDoor(uid)
{

	new query[64];
	format(query, sizeof(query), "DELETE FROM `srv_doors` WHERE `UID`='%d' LIMIT 1", uid);
	mysql_query(query);
	
	DestroyDynamicPickup(DoorsInfo[uid][dPickup]);
	
	DoorsInfo[uid][dUID] = 
	DoorsInfo[uid][dName] = 
	DoorsInfo[uid][dOwnerTyp] = 
	DoorsInfo[uid][dOwner] = 0;
	DoorsInfo[uid][dEnterX] = 
	DoorsInfo[uid][dEnterY] = 
	DoorsInfo[uid][dEnterZ] = 
	DoorsInfo[uid][dEnterAngle] = 0.0;
	DoorsInfo[uid][dEnterInt] = 
	DoorsInfo[uid][dEnterVW] = 0;
	DoorsInfo[uid][dExitX] = 
	DoorsInfo[uid][dExitY] = 
	DoorsInfo[uid][dExitZ] = 
	DoorsInfo[uid][dExitAngle] = 0.0;
	DoorsInfo[uid][dExitInt] = 
	DoorsInfo[uid][dExitVW] = 
	DoorsInfo[uid][dLock] = 
	DoorsInfo[uid][dPickupID] = 
	DoorsInfo[uid][dPickup] = 
	DoorsInfo[uid][dGarage] = 
	DoorsInfo[uid][dIconID] = 
	DoorsInfo[uid][dPriceForEntry] = 0;
}

public SaveDoors(uid, what)
{
	new string[512];
	
	if(what == SAVE_DOORS_BASIC)
	{
		format(string, sizeof(string), "UPDATE `srv_doors` SET `name` = '%s', `ownertyp` = '%d', `owner` = '%d', `lock` = '%d', `pickupid` = '%d', `garage` = '%d', `radio_url` = '%s', `icon_id` = '%d', `priceforentry` = '%d' WHERE `UID` = '%d' LIMIT 1",
		DoorsInfo[uid][dName],
		DoorsInfo[uid][dOwnerTyp],
		DoorsInfo[uid][dOwner],
		DoorsInfo[uid][dLock],
		DoorsInfo[uid][dPickupID],
		DoorsInfo[uid][dGarage],
		DoorsInfo[uid][dRadio],
		DoorsInfo[uid][dIconID],
		DoorsInfo[uid][dPriceForEntry],
		
		uid);
		
		mysql_query(string);
	}
	else if(what == SAVE_DOORS_POS)
	{
		format(string, sizeof(string), "UPDATE `srv_doors` SET `enterx` = '%f', `entery` = '%f', `enterz` = '%f', `enterangle` = '%f', `enterint` = '%d', `entervw` = '%d', `exitx` = '%f', `exity` = '%f', `exitz` = '%f', `exitangle` = '%f', `exitint` = '%d', `exitvw` = '%d' WHERE `UID` = '%d' LIMIT 1",
		DoorsInfo[uid][dEnterX],
		DoorsInfo[uid][dEnterY],
		DoorsInfo[uid][dEnterZ],
		DoorsInfo[uid][dEnterAngle],
		DoorsInfo[uid][dEnterInt],
		DoorsInfo[uid][dEnterVW],
		DoorsInfo[uid][dExitX],
		DoorsInfo[uid][dExitY],
		DoorsInfo[uid][dExitZ],
		DoorsInfo[uid][dExitAngle],
		DoorsInfo[uid][dExitInt],
		DoorsInfo[uid][dExitVW],
		
		uid);
		
		mysql_query(string);
	}
	
	return 1;
}

stock GetPickupUID(pickup)
{
	new uid = 0;
	ForeachEx(i, _DOOR_COUNT)
		if(DoorsInfo[i][dPickup] == pickup)
			uid = i;
	
	return uid;
}

public PlayerEnterDoor(playerid, uid)
{
	if(DoorsInfo[uid][dPriceForEntry])
	{
		if(CharacterInfo[playerid][pCash] < DoorsInfo[uid][dPriceForEntry])
			return msg_error(playerid, "Nie posiadasz odpowiedniej kwoty przy sobie aby wejœæ do œrodka.");
		else
		{
			GivePlayerCash(playerid, -DoorsInfo[uid][dPriceForEntry]);
			GiveGroupCash(DoorsInfo[uid][dOwner], DoorsInfo[uid][dPriceForEntry]);
		}
	}
	if(CharacterInfo[playerid][pGymType])
		OnPlayerGymTrainStopped(playerid);
	
	CharacterInfo[playerid][pDoorEnter] = true;
	
	CharacterInfo[playerid][pACLastJustification] = gettime();
	
	SetPlayerVirtualWorld(playerid, DoorsInfo[uid][dExitVW]);
	SetPlayerInterior(playerid, DoorsInfo[uid][dExitInt]);
	SetPlayerPos(playerid, DoorsInfo[uid][dExitX], DoorsInfo[uid][dExitY], DoorsInfo[uid][dExitZ]);
	SetPlayerFacingAngle(playerid, DoorsInfo[uid][dExitAngle]);
	PlayerTextDrawHide(playerid, DoorsTD[playerid]);
	PlayerDoor[playerid] = uid;
	
	if(!(CharacterInfo[playerid][pTog] & TOG_FREEZE))
	{
		TogglePlayerControllable(playerid, 0);
		SetTimerEx("UnfreezePlayer", 2000, false, "i", playerid);
	}
	
	if(DoorsInfo[uid][dTime] && DoorsInfo[uid][dExitVW])
		SetPlayerTime(playerid, DoorsInfo[uid][dTime], 0);
	else
		SetPlayerTime(playerid, SERVER_TIME, 0);
	
	if(DoorsInfo[uid][dWeather] && DoorsInfo[uid][dExitVW])
		SetPlayerWeather(playerid, DoorsInfo[uid][dWeather]);
	else
		SetPlayerWeather(playerid, SERVER_WEATHER);
	
	if(DoorsInfo[uid][dRadio] && !(CharacterInfo[playerid][pStatus] & STATUS_MP3))
	{
		StopAudioStreamForPlayer(playerid);
		PlayAudioStreamForPlayer(playerid,DoorsInfo[uid][dRadio]);
	}
	
	if(GetPVarInt(playerid,"pJob"))
		EndJob(playerid);
	
	CharacterInfo[playerid][pDoorEnter] = false;
	
	return 1;
}

public PlayerExitDoor(playerid, uid)
{
	if(!(CharacterInfo[playerid][pTog] & TOG_FREEZE))
	{
		TogglePlayerControllable(playerid, 0);
		SetTimerEx("UnfreezePlayer", 2000, false, "i", playerid);
	}
	if(CharacterInfo[playerid][pGymType])
		OnPlayerGymTrainStopped(playerid);
	
	CharacterInfo[playerid][pDoorEnter] = true;
	
	CharacterInfo[playerid][pACLastJustification] = gettime();
	
	SetPlayerVirtualWorld(playerid, DoorsInfo[uid][dEnterVW]);
	SetPlayerInterior(playerid, DoorsInfo[uid][dEnterInt]);
	SetPlayerPos(playerid, DoorsInfo[uid][dEnterX], DoorsInfo[uid][dEnterY], DoorsInfo[uid][dEnterZ]);
	SetPlayerFacingAngle(playerid, DoorsInfo[uid][dEnterAngle]);
	PlayerDoor[playerid] = 0;
	
	if(!IsPlayerInAnyVehicle(playerid) && !(CharacterInfo[playerid][pStatus] & STATUS_MP3))
		StopAudioStreamForPlayer(playerid);
	if(CharacterInfo[playerid][pGymPass] && DoorsInfo[uid][dExitVW]==0)
		CharacterInfo[playerid][pGymPass]=0;
	else if(GetPVarInt(playerid,"pJob"))
		EndJob(playerid);
	
	if(DoorsInfo[uid][dTime] && DoorsInfo[uid][dEnterVW])
		SetPlayerTime(playerid, DoorsInfo[uid][dTime], 0);
	else
		SetPlayerTime(playerid, SERVER_TIME, 0);
	
	if(DoorsInfo[uid][dWeather] && DoorsInfo[uid][dEnterVW])
		SetPlayerWeather(playerid, DoorsInfo[uid][dWeather]);
	else
		SetPlayerWeather(playerid, SERVER_WEATHER);
	
	CharacterInfo[playerid][pDoorEnter] = false;
	
	return 1;
}

public IsDoorOwner(playerid, uid)
{
	if(CharacterInfo[playerid][pAdmin] || 
		(DoorsInfo[uid][dOwnerTyp] == OWNER_PLAYER && CharacterInfo[playerid][pUID] == DoorsInfo[uid][dOwner]) || 
		IsDoorMember(playerid, uid) || 
		(DoorsInfo[uid][dOwnerTyp] == OWNER_HOUSE && (CharacterInfo[playerid][pUID] == DoorsInfo[DoorsInfo[uid][dOwner]][dOwner] || IsDoorMember(playerid, DoorsInfo[uid][dOwner]))) || 
		(DoorsInfo[uid][dOwnerTyp] == OWNER_GROUP && IsPlayerPermInGroup(playerid, DoorsInfo[uid][dOwner], PERM_DOOR)))
		return true;
	
	return false;
}

stock GetClosestDoor(playerid)
{
	ForeachEx(i, _DOOR_COUNT)
		if(DoorsInfo[i][dUID])
			if(IsPlayerInRangeOfPoint(playerid, 1.0, DoorsInfo[i][dEnterX], DoorsInfo[i][dEnterY], DoorsInfo[i][dEnterZ]) && GetPlayerVirtualWorld(playerid) == DoorsInfo[i][dEnterVW] || IsPlayerInRangeOfPoint(playerid, 1.0, DoorsInfo[i][dExitX], DoorsInfo[i][dExitY], DoorsInfo[i][dExitZ]) && GetPlayerVirtualWorld(playerid) == DoorsInfo[i][dExitVW])
				return i;
	
	return 0;
}

public PlayerNearDoorType(playerid, type, Float:range)
{
	ForeachEx(i, _DOOR_COUNT)
		if(IsPlayerInRangeOfPoint(playerid, range, DoorsInfo[i][dEnterX], DoorsInfo[i][dEnterY], DoorsInfo[i][dEnterZ]) && GetPlayerVirtualWorld(playerid) == DoorsInfo[i][dEnterVW] && DoorsInfo[i][dOwnerTyp] == type)
			return true;
	
	return false;
}

public IsDoorMember(playerid, uid)
{
	new query[128];
	format(query, sizeof(query), "SELECT * FROM `srv_doors_members` WHERE `UID` = '%d' AND `player_uid` = '%d'", uid, CharacterInfo[playerid][pUID]);
	mysql_query(query);
	
	mysql_store_result();
	
	if(mysql_num_rows())
	{
		mysql_free_result();
		return true;
	}
	else
	{
		mysql_free_result();
		return false;
	}
}

public HaveHome(playerid)
{
	ForeachEx(i, _DOOR_COUNT)
		if(DoorsInfo[i][dOwnerTyp] == OWNER_PLAYER && DoorsInfo[i][dOwner] == CharacterInfo[playerid][pUID])
				return true;
	
	new query[128];
	format(query, sizeof(query), "SELECT * FROM `srv_doors_members` WHERE `player_uid`='%d'", CharacterInfo[playerid][pUID]);
	mysql_query(query);
	mysql_store_result();
	if(mysql_num_rows())
	{
		mysql_free_result();
		return true;
	}

	return false;
}