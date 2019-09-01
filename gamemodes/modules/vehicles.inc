forward StworzPojazd(playerid, model, color1, color2, vw, int, Float:posx, Float:posy, Float:posz, Float:angle);
forward DeleteVehicle(uid);
forward LoadVehicle(uid);
forward UnspawnVehicle(uid);
forward ListVehiclesForPlayer(playerid);
forward SaveVehicle(uid, what);
forward EngineStart(playerid);
forward SpeedMeterUP(playerid);
forward IsSportVehicle(vehuid);
forward CanPlayerManageVehicle(playerid,vehid);
forward RecentlyLocked(vehuid);

stock GetDoorState(doorStates, Door:door, DoorState:doorState)
	return (doorStates >>> (8 * door)) & doorState;

public SaveVehicle(uid, what)
{
	new string[512];
	
	if(what == SAVE_VEH_BASIC)
	{
		format(string, sizeof(string), "UPDATE `srv_vehicles` SET `hp` = '%f', `model` = '%d', `color1` = '%d', `color2` = '%d', `visual` = '%d,%d,%d,%d', `fuel` = '%f', `distance` = '%f', `register` = '%s', `block`='%d', `rank`='%d', `tuning`='%d', `registered`='%d', `glass`='%d' WHERE `UID` = '%d' LIMIT 1",
		VehicleInfo[uid][vHP],
		VehicleInfo[uid][vModel],
		VehicleInfo[uid][vColor1],
		VehicleInfo[uid][vColor2],
		VehicleInfo[uid][vVisual][0],
		VehicleInfo[uid][vVisual][1],
		VehicleInfo[uid][vVisual][2],
		VehicleInfo[uid][vVisual][3],
		VehicleInfo[uid][vFuel],
		VehicleInfo[uid][vDistance],
		VehicleInfo[uid][vRegister],
		VehicleInfo[uid][vBlokada],
		VehicleInfo[uid][vRank],
		VehicleInfo[uid][vTuning],
		VehicleInfo[uid][vRegistered],
		VehicleInfo[uid][vGlass],
		
		uid);
	}
	else if(what == SAVE_VEH_POS)
	{
		format(string, sizeof(string), "UPDATE `srv_vehicles` SET `posx` = '%f', `posy` = '%f', `posz` = '%f', `vw` = '%d', `interior` = '%d', `angle` = '%f' WHERE `UID` = '%d' LIMIT 1",
		VehicleInfo[uid][vposx],
		VehicleInfo[uid][vposy],
		VehicleInfo[uid][vposz],
		VehicleInfo[uid][vVW],
		VehicleInfo[uid][vInt],
		VehicleInfo[uid][vAngle],
		
		uid);
	}
	else if(what == SAVE_VEH_OWNER)
	{
		format(string, sizeof(string), "UPDATE `srv_vehicles` SET `ownertyp` = '%d', `owner` = '%d' WHERE `UID` = '%d' LIMIT 1",
		VehicleInfo[uid][vOwnerTyp],
		VehicleInfo[uid][vOwner],
		
		uid);	
	}
	mysql_query(string);
	return 1;
}

public StworzPojazd(playerid, model, color1, color2, vw, int, Float:posx, Float:posy, Float:posz, Float:angle)
{
	new uid;
	
	ForeachEx(i, MAX_VEHICLES)
	{
		if(VehicleInfo[i][vUID] == 0 && i != 0)
		{
			uid = i;
			break;
		}
	}
	if(!uid)
		return msg_error(playerid, "Osi¹gniêto maksymaln¹ iloœc pojazdów na serwerze.");
	if(uid+1 >_VEH_COUNT)
		_VEH_COUNT=uid+1;
	
	new register[8];
	format(register, sizeof(register), ".");
	
	mysql_query_format("INSERT INTO `srv_vehicles` (`UID`, `model`, `hp`, `visual`, `color1`, `color2`, `ownertyp`, `owner`, `posx`, `posy`, `posz`, `angle`, `vw`, `interior`, `fuel`, `register`, `radio_url`, `description`) VALUES ('%d', '%d', '%d', '0,0,0,0', '%d', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '.', '.', '.')", uid, model, GetVehicleMaxHP(model), color1, color2, OWNER_PLAYER, CharacterInfo[playerid][pUID], posx, posy, posz, angle, vw, int, GetVehicleMaxFuel(model));
	
	VehicleInfo[uid][vUID] = uid;
	VehicleInfo[uid][vModel] = model;
	VehicleInfo[uid][vColor1] = color1;
	VehicleInfo[uid][vColor2] = color2;
	VehicleInfo[uid][vHP] = GetVehicleMaxHP(model);
	VehicleInfo[uid][vVisual][0] = 
	VehicleInfo[uid][vVisual][1] = 
	VehicleInfo[uid][vVisual][2] = 
	VehicleInfo[uid][vVisual][3] = 0;
	VehicleInfo[uid][vOwner] = CharacterInfo[playerid][pUID];
	VehicleInfo[uid][vOwnerTyp] = OWNER_PLAYER;
	VehicleInfo[uid][vposx] = posx;
	VehicleInfo[uid][vposy] = posy;
	VehicleInfo[uid][vposz] = posz;
	VehicleInfo[uid][vAngle] = angle;
	VehicleInfo[uid][vVW] = vw;
	VehicleInfo[uid][vInt] = int;
	VehicleInfo[uid][vRegister] = register;
	VehicleInfo[uid][vRadio] = 
	VehicleInfo[uid][vBlokada] = 0;
	VehicleInfo[uid][vFuel] = GetVehicleMaxFuel(model);
	VehicleInfo[uid][vDistance] = 
	VehicleInfo[uid][vTuning] = 
	VehicleInfo[uid][vRank] = 0;
	VehicleInfo[uid][vDesc] = false;
	VehicleInfo[uid][vPolice] = 
	VehicleInfo[uid][vRegistered] = 0;
	VehicleInfo[uid][vHB][0] = 
	VehicleInfo[uid][vHB][1] = 
	VehicleInfo[uid][vHB][2] = 
	VehicleInfo[uid][vHB][3] = 0;
	VehicleInfo[uid][vGlass] = 
	VehicleInfo[uid][vHandBrake] = 
	VehicleInfo[uid][vRecentlyLocked] = false;
	
	LoadVehicle(uid);
	
	return uid;
}

public DeleteVehicle(uid)
{
	ForeachEx(i,_ITEM_COUNT)
	{
		if((ItemInfo[i][iOwnerTyp] == OWNER_BAGAZNIK || ItemInfo[i][iOwnerTyp] == OWNER_VEHICLE) && ItemInfo[i][iOwner] == uid)
			DeleteItem(i);
	}
	if(VehicleInfo[uid][vDesc3D] != Text3D:INVALID_3DTEXT_ID)
	{
		DestroyDynamic3DTextLabel(VehicleInfo[uid][vDesc3D]);
		VehicleInfo[uid][vDesc3D] = Text3D:INVALID_3DTEXT_ID;
	}
	
	new query[128];
	format(query,sizeof(query),"DELETE FROM `srv_vehicles` WHERE `UID` = '%d' LIMIT 1", uid);
	mysql_query(query);
	
	VehicleInfo[uid][vUID] = 
	VehicleInfo[uid][vModel] = 
	VehicleInfo[uid][vColor1] = 
	VehicleInfo[uid][vColor2] = 0;
	VehicleInfo[uid][vHP] = 0.0;
	VehicleInfo[uid][vVisual][0] = 
	VehicleInfo[uid][vVisual][1] = 
	VehicleInfo[uid][vVisual][2] = 
	VehicleInfo[uid][vVisual][3] = 0;
	VehicleInfo[uid][vOwner] = 
	VehicleInfo[uid][vOwnerTyp] = 0;
	VehicleInfo[uid][vposx] = 
	VehicleInfo[uid][vposy] = 
	VehicleInfo[uid][vposz] = 
	VehicleInfo[uid][vAngle] = 0;
	VehicleInfo[uid][vVW] = 
	VehicleInfo[uid][vInt] = 0;
	VehicleInfo[uid][vRegister] = 
	VehicleInfo[uid][vRadio] = 
	VehicleInfo[uid][vBlokada] = 0;
	VehicleInfo[uid][vFuel] = 0.0;
	VehicleInfo[uid][vDistance] = 
	VehicleInfo[uid][vTuning] = 
	VehicleInfo[uid][vRank] = 0;
	VehicleInfo[uid][vDesc] = false;
	VehicleInfo[uid][vPolice] = 
	VehicleInfo[uid][vRegistered] = 0;
	VehicleInfo[uid][vHB][0] = 
	VehicleInfo[uid][vHB][1] = 
	VehicleInfo[uid][vHB][2] = 
	VehicleInfo[uid][vHB][3] = 0;
	VehicleInfo[uid][vGlass] = 
	VehicleInfo[uid][vHandBrake] = 
	VehicleInfo[uid][vRecentlyLocked] = false;
	
	return 1;
}


public LoadVehicle(uid)
{
	new siren=false;
	if(VehicleInfo[uid][vOwnerTyp]==OWNER_GROUP)
	{
		new groupid=VehicleInfo[uid][vOwner];
		siren = ((GroupInfo[groupid][gType]==GROUP_PD || GroupInfo[groupid][gType]==GROUP_MC || GroupInfo[groupid][gType]==GROUP_FBI) && Siren(uid));
	}
	VehicleInfo[uid][vSAMPID] = CreateVehicle(VehicleInfo[uid][vModel], VehicleInfo[uid][vposx], VehicleInfo[uid][vposy], VehicleInfo[uid][vposz], VehicleInfo[uid][vAngle], VehicleInfo[uid][vColor1], VehicleInfo[uid][vColor2], -1, siren);
	VehicleUIDs[VehicleInfo[uid][vSAMPID]] = uid;

	if(VehicleInfo[uid][vTuning] & TUNING_PAINTJOB)
	{
		if(VehicleInfo[uid][vTuning] & TUNING_PAINTJOB_0)
			ChangeVehiclePaintjob(VehicleInfo[uid][vSAMPID],0);			
		else if(VehicleInfo[uid][vTuning] & TUNING_PAINTJOB_1)
			ChangeVehiclePaintjob(VehicleInfo[uid][vSAMPID],1);
		else if(VehicleInfo[uid][vTuning] & TUNING_PAINTJOB_2)
			ChangeVehiclePaintjob(VehicleInfo[uid][vSAMPID],2);
	}
	
	SetVehicleVirtualWorld(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vVW]);
	LinkVehicleToInterior(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vInt]);
	
	SetVehicleHealth(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vHP]);
	UpdateVehicleDamageStatus(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vVisual][0], VehicleInfo[uid][vVisual][1], VehicleInfo[uid][vVisual][2], VehicleInfo[uid][vVisual][3]);
	
	SetVehicleNumberPlate(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vRegister]);
	
	if(VehicleInfo[uid][vModel] == 509 || VehicleInfo[uid][vModel] == 510 || VehicleInfo[uid][vModel] == 481)
	{
		VehicleInfo[uid][vLocked] = false;
		VehicleInfo[uid][vEngine] = true;
	}
	else if(VehicleInfo[uid][vModel] == 448 || VehicleInfo[uid][vModel] == 461 || VehicleInfo[uid][vModel] == 462 || VehicleInfo[uid][vModel] == 463)
	{
		VehicleInfo[uid][vLocked] = false;
		VehicleInfo[uid][vEngine] = false;
	}
	else if(VehicleInfo[uid][vModel] == 468 || VehicleInfo[uid][vModel] == 471 || VehicleInfo[uid][vModel] == 521 || VehicleInfo[uid][vModel] == 522)
	{
		VehicleInfo[uid][vLocked] = false;
		VehicleInfo[uid][vEngine] = false;
	}
	else if(VehicleInfo[uid][vModel] == 523 || VehicleInfo[uid][vModel] == 581 || VehicleInfo[uid][vModel] == 586 || VehicleInfo[uid][vModel] == 574)
	{
		VehicleInfo[uid][vLocked] = false;
		VehicleInfo[uid][vEngine] = false;
	}
	else
	{
		VehicleInfo[uid][vLocked] = true;
		VehicleInfo[uid][vEngine] = false;
	}
	
	if(VehicleInfo[uid][vTuning] & TUNING_VISUAL)
	{
		new query2[64];
		format(query2,sizeof(query2),"SELECT `component_id` FROM `srv_tuning` WHERE `vehicle`='%d'",uid);
		mysql_query(query2);
		mysql_store_result();
		while(mysql_fetch_row_format(query2, "|") == 1)
			AddVehicleComponent(VehicleInfo[uid][vSAMPID], strval(query2));

		mysql_free_result();
	}
	
	SetVehicleLock(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vLocked]);
	ChangeVehicleEngineStatus(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vEngine]);
	ChangeVehicleLightsStatus(VehicleInfo[uid][vSAMPID], false);
	
	VehicleInfo[uid][vSpawned] = true;
	VehicleInfo[uid][vRecentlyLocked] = false;
	ChangeVehicleColor(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vColor1], VehicleInfo[uid][vColor2]);

	if(VehicleInfo[uid][vDesc])
		VehicleInfo[uid][vDesc3D] = CreateDynamic3DTextLabel(WordWrap(LoadVehDesc(uid), 5), COLOR_VEH_DESC, VehicleInfo[uid][vposx], VehicleInfo[uid][vposy], VehicleInfo[uid][vposz],10.0, INVALID_PLAYER_ID, VehicleInfo[uid][vSAMPID]);
	
	return 1;	
}

public UnspawnVehicle(uid)
{
	SaveVehicle(uid, SAVE_VEH_BASIC);
	
	if(VehicleInfo[uid][vDesc3D] != Text3D:INVALID_3DTEXT_ID)
	{
		DestroyDynamic3DTextLabel(VehicleInfo[uid][vDesc3D]);
		VehicleInfo[uid][vDesc3D] = Text3D:INVALID_3DTEXT_ID;
	}
	if(Kierunki_V[uid][2])
	{
		DestroyObject(Kierunki_V[uid][2]);
		DestroyObject(Kierunki_V[uid][3]);
		DestroyObject(Kierunki_V[uid][5]);
		
		Kierunki_V[uid][2]=0;
	}
	if(Kierunki_V[uid][0])
	{
		DestroyObject(Kierunki_V[uid][0]);
		DestroyObject(Kierunki_V[uid][1]);
		DestroyObject(Kierunki_V[uid][4]);
		
		Kierunki_V[uid][0]=0;
	}
	if(strlen(VehicleInfo[uid][vRadio])>5)
	{
		ForeachPlayer(i)
		{
			if(GetPlayerVehicleID(i)==VehicleInfo[uid][vSAMPID] && !(CharacterInfo[i][pStatus] & STATUS_MP3) )
				StopAudioStreamForPlayer(i);
		}
	}
	DestroyVehicle(VehicleInfo[uid][vSAMPID]);
	if(VehicleInfo[uid][vPolice])
	{
		DestroyDynamicObject(VehicleInfo[uid][vPolice]);
		VehicleInfo[uid][vPolice]=0;
	}
	
	if(VehicleInfo[uid][vHandBrake])
	{
		VehicleInfo[uid][vHandBrake] = false;
		VehicleInfo[uid][vHB][0] = 
		VehicleInfo[uid][vHB][1] = 
		VehicleInfo[uid][vHB][2] = 
		VehicleInfo[uid][vHB][3] = 0;
	}
	
	VehicleUIDs[VehicleInfo[uid][vSAMPID]]=
	VehicleInfo[uid][vSAMPID] = 0;
	
	VehicleInfo[uid][vSpawned] = false;
	VehicleInfo[uid][vRecentlyLocked]=false;
}

public ListVehiclesForPlayer(playerid)
{
	new list[1024];
	VehSpawned[playerid] = 0;
	
	format(list, sizeof(list), "UID\tModel\tHP\tPaliwo");

	ForeachEx(uid, _VEH_COUNT)
	{
		if(VehicleInfo[uid][vUID] && VehicleInfo[uid][vOwnerTyp] == OWNER_PLAYER && VehicleInfo[uid][vOwner] == CharacterInfo[playerid][pUID])
		{
			if(VehicleInfo[uid][vSpawned]) 
			{
					format(list, sizeof(list), "%s\n%d\t{02AD38}%s{ffffff}\t%3.1f\t%3d", list, uid, GetVehicleModelName(VehicleInfo[uid][vModel]), VehicleInfo[uid][vHP]/10,floatround(VehicleInfo[uid][vFuel]));
					VehSpawned[playerid]++;
			}
			else format(list, sizeof(list), "%s\n%d\t{878A87}%s{ffffff}\t%3.1f\t%3d", list, uid, GetVehicleModelName(VehicleInfo[uid][vModel]), VehicleInfo[uid][vHP]/10,floatround(VehicleInfo[uid][vFuel]));
		}
	}
	
	if(strlen(list) > 23) ShowPlayerDialog(playerid, D_LIST_VEH, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » lista pojazdów", list, "Opcje", "Zamknij");
	else Tip(playerid, 3, "Nie posiadasz pojazdow.");
	
	return 1;
}

stock GetVehicleModelName(modelid)
{
	if(modelid < 400)
		return VehicleName[212];
	new tmp = modelid - 400;
	return VehicleName[tmp];
}

stock GetClosestVehicle(playerid)
{
	new Float:prevdist = 5.000, prevcar = INVALID_VEHICLE_ID, Float: dist;
	new poolSize = GetVehiclePoolSize()+1;
	ForeachEx(carid,poolSize)	
	{
		if(GetVehicleModel(carid))
		{
			dist = GetDistanceToVehicle(playerid, carid);
			if ((dist < prevdist) && GetVehicleVirtualWorld(carid)==GetPlayerVirtualWorld(playerid))
			{
				prevdist = dist;
				prevcar = carid;
			}
		}
	}
	
	return prevcar;
}


stock GetDistanceToVehicle(playerid, carid)
{
	new Float:x1, Float:y1, Float:z1,
	Float:x2, Float:y2, Float:z2, Float:dis;
	
	GetPlayerPos(playerid, x1, y1, z1);
	GetVehiclePos(carid, x2, y2, z2);
	
	dis = floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2));
	return floatround(dis);
}

stock ChangeVehicleEngineStatus(vehicleid, bool:toggle)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;
	
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vehicleid, toggle, lights, alarm, doors, bonnet, boot, objective);
	return toggle;
}

stock IsOwnerVehicle(playerid, vehuid, bool: mainOwner = false)
{	
	if(mainOwner)
		return (CharacterInfo[playerid][pAdmin] > 1 || (VehicleInfo[vehuid][vOwnerTyp] == OWNER_PLAYER && VehicleInfo[vehuid][vOwner] == CharacterInfo[playerid][pUID]));
	else
	{
		if(CharacterInfo[playerid][pAdmin] > 1)
			return 1;
		if(VehicleInfo[vehuid][vOwnerTyp] == OWNER_PLAYER && VehicleInfo[vehuid][vOwner] == CharacterInfo[playerid][pUID])
			return 1;
		if(VehicleInfo[vehuid][vOwnerTyp] == OWNER_JOB && VehicleInfo[vehuid][vOwner] == CharacterInfo[playerid][pJob])
			return 1;
		if(VehicleInfo[vehuid][vOwnerTyp] == OWNER_GROUP && IsPlayerPermInGroup(playerid, VehicleInfo[vehuid][vOwner], PERM_VEHICLES))
		{ 
			if(!VehicleInfo[vehuid][vRank] || IsPlayerPermInGroup(playerid, VehicleInfo[vehuid][vOwner], PERM_VEHICLES_MAN))
				return 1;
			else
			{
				for(new i=1;i<MAX_PLAYER_GROUPS;i++)
				{
					if(MemberGroup[playerid][i][GroupID] == VehicleInfo[vehuid][vOwner] && MemberGroup[playerid][i][GroupRank] ==  VehicleInfo[vehuid][vRank])
						return 1;
				}
			}
		}
		ForeachEx(i, _ITEM_COUNT)
		{
			if(ItemInfo[i][iOwnerTyp] == OWNER_PLAYER && ItemInfo[i][iOwner] == CharacterInfo[playerid][pUID] && ItemInfo[i][iType] == ITEM_TYPE_CARKEYS && ItemInfo[i][iValue1] == vehuid)
				return 1;
		}
	}
	return 0;
}
public CanPlayerManageVehicle(playerid,vehid)
{
	if(CharacterInfo[playerid][pAdmin]>3)
		return 1;
	if(VehicleInfo[vehid][vOwnerTyp]==OWNER_PLAYER && VehicleInfo[vehid][vOwner] == CharacterInfo[playerid][pUID])
		return 1;
	if(VehicleInfo[vehid][vOwnerTyp]==OWNER_GROUP && IsPlayerPermInGroup(playerid,VehicleInfo[vehid][vOwner],PERM_VEHICLES_MAN))
		return 1;

	return 0;
}

stock SetVehicleLock(vehicleid, bool: toggle)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;
	
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vehicleid, engine, lights, alarm, toggle, bonnet, boot, objective);
	return toggle;
}

stock GetVehicleLightsStatus(vehicleid)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	return lights;
}

stock ChangeVehicleLightsStatus(vehicleid, bool: toggle)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;
	
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vehicleid, engine, toggle, alarm, doors, bonnet, boot, objective);
	return toggle;
}

stock GetVehicleBonnetStatus(vehicleid)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	return bonnet;
}

stock ChangeVehicleBonnetStatus(vehicleid, bool: toggle)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;
	
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, toggle, boot, objective);
	return toggle;
}

stock GetVehicleBootStatus(vehicleid)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	return boot;
}

stock ChangeVehicleBootStatus(vehicleid, bool: toggle)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;
	
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, toggle, objective);
	return toggle;
}

public EngineStart(playerid)
{
	if(GetPVarInt(playerid, "pRepairMechanic"))
		return 1;
	new vehid = GetPlayerVehicleID(playerid);
	new vehuid = GetVehicleUID(vehid);
	if(vehuid<0) return 1;
	
	if(VehicleInfo[vehuid][vDistance] > 10000.0 && random(30) == 14)
	{
		cmd_do(playerid, "Silnik nie odpali³ z powodu sporego przebiegu.");
	}
	else
	{
		VehicleInfo[vehuid][vEngine] = true;
		
		ChangeVehicleEngineStatus(vehid, VehicleInfo[vehuid][vEngine]);
		new string[256];
		VehicleInfo[vehuid][vLastDriver] = CharacterInfo[playerid][pUID];
		format(string,sizeof(string),"UPDATE `srv_vehicles` SET `last_driver`='%d' WHERE `UID`='%d'",VehicleInfo[vehuid][vLastDriver],vehuid);
		mysql_query(string);
		
		format(string, sizeof(string), "Silnik uruchomiony (%s).", GetVehicleModelName(VehicleInfo[vehuid][vModel]));
		cmd_do(playerid, string);
	}
	
	return 1;
}

public SpeedMeterUP(playerid)
{
	if(Logged[playerid] && GetPlayerVehicleID(playerid) && !(CharacterInfo[playerid][pTog] & TOG_SPEEDOMETER))
	{
		static vehid, vehuid, Float:vehhp, speed, modelid;
		vehid = GetPlayerVehicleID(playerid);
		vehuid = GetVehicleUID(vehid);
		speed = VehicleSpeed(vehid);
        modelid = GetVehicleModel(vehid);
		
		GetVehicleHealth(vehid, vehhp);
		
		new string[128];
		
		format(string, sizeof(string), "%d", speed);
		PlayerTextDrawSetString(playerid, Speedometer[playerid][6], string);
		
		format(string, sizeof(string), "%.0fKM", VehicleInfo[vehuid][vDistance]);
		PlayerTextDrawSetString(playerid, Speedometer[playerid][7], string);
		
		format(string, sizeof(string), "%d/%dL", floatround(VehicleInfo[vehuid][vFuel]), GetVehicleMaxFuel(modelid));
		PlayerTextDrawSetString(playerid, Speedometer[playerid][8], string);
		
		format(string, sizeof(string), "%.1f%", vehhp/10);
		PlayerTextDrawSetString(playerid, Speedometer[playerid][9], string);
		
		for(new x = 0; x < 10; x++)
			PlayerTextDrawShow(playerid, Speedometer[playerid][x]);
		
		if(VehicleInfo[vehuid][vModel]==597 && speed > 192)
		{
			static keys, updown, leftright;
			GetPlayerKeys(playerid, keys, updown, leftright);

			static Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2,Float:a,Float:factor;
			GetVehicleZAngle(vehid, a);
			if((keys & KEY_SPRINT  && a>VehicleInfo[vehuid][vAngle] && floatabs(a-VehicleInfo[vehuid][vAngle]) < 10.0) || (a<=VehicleInfo[vehuid][vAngle] && floatabs(VehicleInfo[vehuid][vAngle]-a) < 10.0))
			{
				VehicleInfo[vehuid][vAngle] = a;
				GetVehicleVelocity(vehid, x1, y1, z1);
				GetVehiclePos(vehid, x2, y2, z2);
				if(speed < 200.0) factor= 1.05;
				else if(speed < 210.0) factor = 1.1;
				else if(speed < 220.0) factor = 1.15;
				else factor = 1.2;
				a = 360.0-a;
				x1 = (floatsin(a, degrees) * (factor) + floatcos(a, degrees) * 0 + x2) - x2;
				y1 = (floatcos(a, degrees) * (factor) + floatsin(a, degrees) * 0 + y2) - y2;
				SetVehicleVelocity(vehid, x1, y1, z1);
			}
			else
				VehicleInfo[vehuid][vAngle] = a;
		}
		
		SetTimerEx("SpeedMeterUP", 750, false, "i", playerid);
	} else {
		for(new x = 0; x < 10; x++)
			PlayerTextDrawHide(playerid, Speedometer[playerid][x]);
	}
	
	return 1;
}

stock VehicleSpeed(vehid)
{
	static Float:X,Float:Y,Float:Z;
	GetVehicleVelocity(vehid, X, Y, Z);
	return floatround(floatsqroot(floatabs(X*X) + floatabs(Y*Y) + floatabs(Z*Z)) * 200.0);
}

stock GetVehicleMaxFuel(model)
{
	switch(model)
	{
		case 400: return 70;
		case 401: return 50;
		case 402: return 60;
		case 403: return 400;
		case 404: return 50;
		case 405: return 50;
		case 406: return 100;
		case 407: return 200;
		case 408: return 100;
		case 409: return 100;
		case 410: return 50;
		case 411: return 80;
		case 412: return 50;
		case 413: return 80;
		case 414: return 80;
		case 415: return 70;
		case 416: return 100;
		case 417: return 250;
		case 418: return 80;
		case 419: return 70;
		case 420: return 80;
		case 421: return 80;
		case 422: return 80;
		case 423: return 90;
		case 424: return 30;
		case 425: return 250;
		case 426: return 70;
		case 427: return 120;
		case 428: return 120;
		case 429: return 60;
		case 430: return 200;
		case 431: return 100;
		case 432: return 500;
		case 433: return 100;
		case 434: return 40;
		case 436: return 60;
		case 437: return 100;
		case 438: return 60;
		case 439: return 60;
		case 440: return 80;
		case 442: return 60;
		case 443: return 150;
		case 444: return 80;
		case 445: return 50;
		case 446: return 100;
		case 447: return 200;
		case 448: return 20;
		case 449: return 100;
		case 451: return 80;
		case 452: return 200;
		case 453: return 200;
		case 454: return 200;
		case 455: return 200;
		case 456: return 80;
		case 457: return 20;
		case 458: return 70;
		case 459: return 80;
		case 460: return 200;
		case 461: return 50;
		case 462: return 30;
		case 463: return 60;
		case 466: return 60;
		case 467: return 60;
		case 468: return 50;
		case 469: return 200;
		case 470: return 100;
		case 471: return 50;
		case 472: return 150;
		case 473: return 150;
		case 474: return 70;
		case 475: return 70;
		case 476: return 200;
		case 477: return 70;
		case 478: return 60;
		case 479: return 60;
		case 480: return 60;
		case 482: return 80;
		case 483: return 80;
		case 484: return 200;
		case 485: return 50;
		case 486: return 150;
		case 487: return 200;
		case 488: return 200;
		case 489: return 90;
		case 490: return 100;
		case 491: return 60;
		case 492: return 50;
		case 493: return 200;
		case 494: return 100;
		case 495: return 80;
		case 496: return 60;
		case 497: return 200;
		case 498: return 90;
		case 499: return 90;
		case 500: return 70;
		case 502: return 90;
		case 503: return 90;
		case 504: return 90;
		case 505: return 90;
		case 506: return 70;
		case 507: return 70;
		case 508: return 100;
		case 511: return 200;
		case 512: return 200;
		case 513: return 150;
		case 514: return 200;
		case 515: return 200;
		case 516: return 60;
		case 517: return 60;
		case 518: return 60;
		case 519: return 300;
		case 520: return 300;
		case 521: return 60;
		case 522: return 60;
		case 523: return 80;
		case 524: return 100;
		case 525: return 70;
		case 526: return 60;
		case 527: return 60;
		case 528: return 80;
		case 529: return 60;
		case 530: return 20;
		case 531: return 40;
		case 532: return 100;
		case 533: return 60;
		case 534: return 70;
		case 535: return 80;
		case 536: return 70;
		case 537: return 300;
		case 538: return 300;
		case 539: return 50;
		case 540: return 60;
		case 541: return 70;
		case 542: return 50;
		case 543: return 60;
		case 544: return 100;
		case 545: return 70;
		case 546: return 60;
		case 547: return 60;
		case 548: return 250;
		case 549: return 70;
		case 550: return 60;
		case 551: return 60;
		case 552: return 60;
		case 553: return 300;
		case 554: return 90;
		case 555: return 60;
		case 556: return 100;
		case 557: return 100;
		case 558: return 60;
		case 559: return 60;
		case 560: return 70;
		case 561: return 70;
		case 562: return 60;
		case 563: return 200;
		case 565: return 50;
		case 566: return 60;
		case 567: return 60;
		case 568: return 50;
		case 571: return 10;
		case 572: return 10;
		case 573: return 150;
		case 574: return 50;
		case 575: return 70;
		case 576: return 75;
		case 577: return 500;
		case 578: return 150;
		case 579: return 80;
		case 580: return 80;
		case 581: return 60;
		case 582: return 80;
		case 583: return 20;
		case 585: return 60;
		case 586: return 25;
		case 587: return 60;
		case 588: return 70;
		case 589: return 60;
		case 593: return 200;
		case 595: return 200;
		case 596: return 90;
		case 597: return 90;
		case 598: return 90;
		case 599: return 100;
		case 600: return 60;
		case 601: return 150;
		case 602: return 60;
		case 603: return 60;
		case 604: return 90;
		case 605: return 60;
		case 609: return 100;
		default: return 0;
	}
	return 0;
}

stock GetVehicleMaxHP(model)
{
	switch(model)
	{
		case 427,428: return 2500;
		case 489: return 1600;
		case 490: return 3500;
		case 599: return 2000;
		case 601: return 10000;
		case 403,514: return 2000;
		case 515: return 2250;

		default: return 1000;
	}
	return 1000;
}

public IsSportVehicle(vehuid)
{
	if(VehicleInfo[vehuid][vModel] == 402 || VehicleInfo[vehuid][vModel] == 411 || VehicleInfo[vehuid][vModel] == 415 || VehicleInfo[vehuid][vModel] == 429 || VehicleInfo[vehuid][vModel] == 451) return true;
	else if(VehicleInfo[vehuid][vModel] == 477 || VehicleInfo[vehuid][vModel] == 480 || VehicleInfo[vehuid][vModel] == 506 || VehicleInfo[vehuid][vModel] == 541 || VehicleInfo[vehuid][vModel] == 555) return true;
	else if(VehicleInfo[vehuid][vModel] == 558 || VehicleInfo[vehuid][vModel] == 559 || VehicleInfo[vehuid][vModel] == 560 || VehicleInfo[vehuid][vModel] == 562 || VehicleInfo[vehuid][vModel] == 565) return true;
	else if(VehicleInfo[vehuid][vModel] == 587 || VehicleInfo[vehuid][vModel] == 602 || VehicleInfo[vehuid][vModel] == 603) return true;
	
	return false;
}

stock SetVehicleIndicator(vehuid, leftindicator=0, rightindicator=0)
{
	if(!leftindicator & !rightindicator) return false;
	new Float:_vX[2], Float:_vY[2], Float:_vZ[2];
	if(rightindicator)
	{
		if(IsTrailerAttachedToVehicle(VehicleInfo[vehuid][vSAMPID]))
		{
			new trailer = GetVehicleModel(GetVehicleTrailer(VehicleInfo[vehuid][vSAMPID]));
			GetVehicleModelInfo(trailer, VEHICLE_MODEL_INFO_SIZE, _vX[0], _vY[0], _vZ[0]);
			Kierunki_V[vehuid][4] = CreateObject(19294, 0, 0, 0, 0, 0, 0);
			AttachObjectToVehicle(Kierunki_V[vehuid][4], GetVehicleTrailer(VehicleInfo[vehuid][vSAMPID]),  _vX[0]/2.4, -_vY[0]/3.35, -1.0,0, 0, 0);
		}
		
		GetVehicleModelInfo(GetVehicleModel(VehicleInfo[vehuid][vSAMPID]), VEHICLE_MODEL_INFO_SIZE, _vX[0], _vY[0], _vZ[0]);
		Kierunki_V[vehuid][0] = CreateObject(19294, 0, 0, 0, 0, 0, 0);
		AttachObjectToVehicle(Kierunki_V[vehuid][0], VehicleInfo[vehuid][vSAMPID],  _vX[0]/2.23, _vY[0]/2.23, 0.1, 0, 0, 0);
		Kierunki_V[vehuid][1] = CreateObject(19294, 0, 0, 0, 0, 0, 0);
		AttachObjectToVehicle(Kierunki_V[vehuid][1], VehicleInfo[vehuid][vSAMPID],  _vX[0]/2.23, -_vY[0]/2.23, 0.1,0, 0, 0);
	}
	if(leftindicator)
	{
		if(IsTrailerAttachedToVehicle(VehicleInfo[vehuid][vSAMPID]))
		{
			new trailer = GetVehicleModel(GetVehicleTrailer(VehicleInfo[vehuid][vSAMPID]));
			GetVehicleModelInfo(trailer, VEHICLE_MODEL_INFO_SIZE, _vX[0], _vY[0], _vZ[0]);
			Kierunki_V[vehuid][5] = CreateObject(19294, 0, 0, 0, 0, 0, 0);
			AttachObjectToVehicle(Kierunki_V[vehuid][5], GetVehicleTrailer(VehicleInfo[vehuid][vSAMPID]),  -_vX[0]/2.4, -_vY[0]/3.35, -1.0, 0, 0, 0);
		}
		
		GetVehicleModelInfo(GetVehicleModel(VehicleInfo[vehuid][vSAMPID]), VEHICLE_MODEL_INFO_SIZE, _vX[0], _vY[0], _vZ[0]);
		Kierunki_V[vehuid][2] = CreateObject(19294, 0, 0, 0, 0, 0, 0);
		AttachObjectToVehicle(Kierunki_V[vehuid][2], VehicleInfo[vehuid][vSAMPID],  -_vX[0]/2.23, _vY[0]/2.23, 0.1, 0, 0, 0);
		Kierunki_V[vehuid][3] = CreateObject(19294, 0, 0, 0, 0, 0, 0);
		AttachObjectToVehicle(Kierunki_V[vehuid][3], VehicleInfo[vehuid][vSAMPID],  -_vX[0]/2.23, -_vY[0]/2.23, 0.1, 0, 0, 0);
	}
	return 1;
}

stock IsAPlane(carid2)
{
	new carid = GetVehicleModel(carid2);
	if(carid == 592 || carid == 577 || carid == 511 || carid == 512 || carid == 593 || carid == 553 || carid == 476 || carid == 519 || carid == 520|| carid == 460 || carid == 513 || carid == 417 || carid == 447 || carid == 469 || carid == 487 || carid == 488 || carid == 497 || carid == 548 || carid == 563 || carid == 520) return 1;
	return 0;
}
 
stock IsABoat(carid)
{
	new modelid = GetVehicleModel(carid);
	if(modelid == 430 || modelid == 446 || modelid == 452 || modelid == 453 || modelid == 454 || modelid == 472 || modelid == 473 || modelid == 484 || modelid == 493 || modelid == 595) return 1;
	return 0;
}

stock IsABike(carid, option=0)
{
	new modelid = GetVehicleModel(carid);
	
	if(!option)
		return (modelid==448 || modelid==461 || modelid==462 || modelid==463 || modelid==468 || modelid==471 || modelid==481 || modelid==509 || modelid==510 || modelid==521 || modelid==522 || modelid==523 || modelid==581 || modelid==586);
	else
		return (modelid==471 || modelid==481 || modelid==509 || modelid==510);
}
stock IsVehicleOccupied(vehid)
{
	ForeachPlayer(i)
	{
		if(GetPlayerVehicleID(i) == vehid)
			return 1;
	}
	return 0;
}
stock decode_lights(lights, &light1, &light2, &light3, &light4)
{
	light1 = lights & 1;
	light2 = lights >> 1 & 1;
	light3 = lights >> 2 & 1;
	light4 = lights >> 3 & 1;
}
 
stock decode_panels(panels, &front_bumper, &rear_bumper)
{
	front_bumper= panels >> 20 & 15;
	rear_bumper = panels >> 24 & 15;
}
 
stock decode_doors(doors, &bonnet, &boot, &driver_door, &passenger_door)
{
	bonnet = doors & 7;
	boot = doors >> 8 & 7;
	driver_door = doors >> 16 & 7;
	passenger_door = doors >> 24 & 7;
}
 
stock decode_tires(tires, &tire1, &tire2, &tire3, &tire4)
{
	tire1 = tires & 1;
	tire2 = tires >> 1 & 1;
	tire3 = tires >> 2 & 1;
	tire4 = tires >> 3 & 1;
}
stock LoadVehRadio(uid)
{
	new query[64],url[128];
	format(query,sizeof(query),"SELECT `radio_url` FROM `srv_vehicles` WHERE `UID` = '%d'",uid);
	mysql_query(query);
	mysql_store_result();
	if(mysql_num_rows())
	{
		mysql_fetch_row_format(url);
	}
	mysql_free_result();
	return url;
}
stock SaveVehRadio(uid,url[])
{
	new query[256];
	format(query, sizeof(query), "UPDATE `srv_vehicles` SET `radio_url`='%s' WHERE `UID` = '%d'", url, uid);
	mysql_query(query);
	return 1;
}
stock LoadVehDesc(uid)
{
	new query[128];
	format(query,sizeof(query),"SELECT `description` FROM `srv_vehicles` WHERE `UID` = '%d'",uid);
	mysql_query(query);
	mysql_store_result();
	mysql_fetch_row_format(query);
	mysql_free_result();
	return query;
}

stock Siren(uid)
{
	ForeachEx(i, sizeof(SyrenaPos))
		if(SyrenaPos[i][VehicleID] == VehicleInfo[uid][vModel]) return SyrenaPos[i][SPU];
	
	return false;
}
stock hasModelEngine(model)
{
	return (model != 481 && model != 509 && model !=510);
}

public RecentlyLocked(vehuid)
{
	if(VehicleInfo[vehuid][vLocked])
		VehicleInfo[vehuid][vRecentlyLocked] = false;
	
	return 1;
}