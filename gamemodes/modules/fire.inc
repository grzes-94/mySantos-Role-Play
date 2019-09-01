#define Labels
#define MaxFire 100
forward f_OnPlayerUpdate(playerid);
#define Holding(%0) \
        ((newkeys & (%0)) == (%0))

new FireObj[MaxFire], Float:FirePos[MaxFire][3], FireHealth[MaxFire], FireHealthMax[MaxFire];

#if defined Labels
new Text3D:FireText[MaxFire];
#endif

stock AddFire(Float:x, Float:y, Float:z, vw, int, Health, obj)
{
	new uid;
	
	ForeachEx(i, MaxFire)
	{
		if(!IsValidFire(i) && i != 0)
		{
			uid = i;
			break;
		}
	}
	
	if(!uid)
		return 0;
	
	switch(obj)
	{
		case 3461:
			FireObj[uid] = CreateDynamicObject(3461, x, y, z-2.61, 0.0, 0.0, 0.0, vw, int);
		case 18688:
			FireObj[uid] = CreateDynamicObject(18688, x, y, z-2.61, 0.0, 0.0, 0.0, vw, int);
		case 18689:
			FireObj[uid] = CreateDynamicObject(18689, x, y, z-2.61, 0.0, 0.0, 0.0, vw, int);
		case 18690:
			FireObj[uid] = CreateDynamicObject(18690, x, y, z-2.61, 0.0, 0.0, 0.0, vw, int);
		case 18691:
			FireObj[uid] = CreateDynamicObject(18691, x, y, z-2.61, 0.0, 0.0, 0.0, vw, int);
		default:
			return 0;
	}
	
	FirePos[uid][0] = x, FirePos[uid][1] = y, FirePos[uid][2] = z;
	FireHealth[uid] = Health;
	FireHealthMax[uid] = Health;
	
	#if defined Labels
		new string[128];
		format(string, sizeof(string), "Ogien [%d/%d]", FireHealth[uid], FireHealthMax[uid]);
		FireText[uid] = Create3DTextLabel(string, COLOR_RED, x, y, z, 40, vw, 0);
	#endif
	
	return uid;
}

stock DeleteFire(uid)
{
	DestroyDynamicObject(FireObj[uid]);
	FirePos[uid][0] = 0, FirePos[uid][1] = 0, FirePos[uid][2] = 0;
	
	#if defined Labels
		Delete3DTextLabel(FireText[uid]);
	#endif
}

stock DeleteAllFire()
{
	ForeachEx(i, MaxFires)
	{
		if(IsValidFire(i))
		{
			DestroyDynamicObject(FireObj[i]);
			FirePos[i][0] = 0, FirePos[i][1] = 0, FirePos[i][2] = 0;
			#if defined Labels
				Delete3DTextLabel(FireText[i]);
			#endif
		}
	}
}

stock IsValidFire(ID)
{
	if(!(FirePos[ID][0] == 0 && FirePos[ID][1] == 0 && FirePos[ID][2] == 0)) return true;
	else return false;
}

stock GetClosestFire(playerid)
{
	ForeachEx(i, MaxFire)
		if(IsValidFire(i) && IsPlayerInRangeOfPoint(playerid, 3.0, FirePos[i][0],  FirePos[i][1],  FirePos[i][2]))
			return i;
	
	return 0;
}

public f_OnPlayerUpdate(playerid)
{
	new newkeys, l, u;
	GetPlayerKeys(playerid, newkeys, l, u);
	
	if(Holding(KEY_FIRE) && GetPlayerWeapon(playerid) == 42)
	{
		ForeachEx(i, MaxFire)
		{
			if(IsValidFire(i) && PlayerFaces(playerid, FirePos[i][0], FirePos[i][1], FirePos[i][2], 1) && IsPlayerInRangeOfPoint(playerid, 3.0, FirePos[i][0], FirePos[i][1], FirePos[i][2]))
			{
				FireHealth[i] -= 3;
				
				#if defined Labels
					new string[128];
					format(string, sizeof(string), "Ogien [%d/%d]", FireHealth[i], FireHealthMax[i]);
					Update3DTextLabelText(FireText[i], COLOR_RED, string);
				#endif
				
				if(FireHealth[i] <= 0)
					DeleteFire(i);
			}
		}
	}
	else if(Holding(KEY_FIRE) && IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && VehicleInfo[GetVehicleUID(GetPlayerVehicleID(playerid))][vModel] == 407)
	{
		ForeachEx(i, MaxFire)
		{
			if(IsValidFire(i) && IsPlayerInRangeOfPoint(playerid, 40.0, FirePos[i][0], FirePos[i][1], FirePos[i][2]) && PlayerFaces(playerid, FirePos[i][0], FirePos[i][1], FirePos[i][2]-1.5, 3))
			{
				FireHealth[i] -= 5;
				
				#if defined Labels
					new string[128];
					format(string, sizeof(string), "Ogien [%d/%d]", FireHealth[i], FireHealthMax[i]);
					Update3DTextLabelText(FireText[i], COLOR_RED, string);
				#endif
				
				if(FireHealth[i] <= 0)
					DeleteFire(i);
			}
		}
	}
	
	return 1;
}
 
Float:DistanceCameraTargetToLocation(Float:CamX, Float:CamY, Float:CamZ, Float:ObjX, Float:ObjY, Float:ObjZ, Float:FrX, Float:FrY, Float:FrZ)
{
	new Float:TGTDistance;
	TGTDistance = floatsqroot((CamX - ObjX) * (CamX - ObjX) + (CamY - ObjY) * (CamY - ObjY) + (CamZ - ObjZ) * (CamZ - ObjZ));
	new Float:tmpX, Float:tmpY, Float:tmpZ;
	tmpX = FrX * TGTDistance + CamX;
	tmpY = FrY * TGTDistance + CamY;
	tmpZ = FrZ * TGTDistance + CamZ;
	return floatsqroot((tmpX - ObjX) * (tmpX - ObjX) + (tmpY - ObjY) * (tmpY - ObjY) + (tmpZ - ObjZ) * (tmpZ - ObjZ));
}

stock PlayerFaces(playerid, Float:x, Float:y, Float:z, Float:radius)
{
	new Float:cx, Float:cy, Float:cz, Float:fx, Float:fy, Float:fz;
	GetPlayerCameraPos(playerid, cx, cy, cz);
	GetPlayerCameraFrontVector(playerid, fx, fy, fz);
	return (radius >= DistanceCameraTargetToLocation(cx, cy, cz, x, y, z, fx, fy, fz));
}