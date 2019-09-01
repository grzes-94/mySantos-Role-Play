forward DeleteObject(uid);
forward SaveObject(uid);
forward SaveObjectGate(uid);
forward AddObject(creator_uid,model, ownertype, owner, World, InteriorEx, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz);
forward IsPlayerGateOwner(playerid,gateid);
forward IsObjectOwner(playerid,objectid);
forward GetObjectModelClosest( playerid, model );
forward CopyObject(playerid,object_id);
forward HideObjectTextDraw(playerid);

stock GetObjectIndex( objectid )
{
	for(new i=1; i<_OBJ_COUNT;i++)
		if(ObjectInfo[i][oObject] == objectid)
			return i;
	
	return 0;
}

stock GetObjectID(uid)
{
	ForeachEx(i, _OBJ_COUNT)
		if(ObjectInfo[i][oUID] == uid)
			return i;
	
	return 0;
}

public HideObjectTextDraw(playerid)
{
	PlayerTextDrawHide(playerid, EditObjectText[playerid]);
	return 1;
}
public AddObject(creator_uid, model, ownertype, owner, World, InteriorEx, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	new uid;
	
	ForeachEx(i, MAX_OBJECTS)
	{
		if(ObjectInfo[i][oUID] == 0 && i != 0)
		{
			uid = i;
			break;
		}
	}
	if(uid+1>_OBJ_COUNT)
		_OBJ_COUNT=uid+1;
	
	mysql_query_format("INSERT INTO `srv_objects` VALUES ('%d', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%d', '0', '0', '0', '0', '0', '0', '0', '0', '%d', '%d')", uid, model, x, y, z, rx, ry, rz, World, InteriorEx, owner, ownertype, creator_uid, creator_uid);

	ObjectInfo[uid][oUID] = uid;
	ObjectInfo[uid][oModel] = model;

	ObjectInfo[uid][oX] = x;
	ObjectInfo[uid][oY] = y;
	ObjectInfo[uid][oZ] = z;

	ObjectInfo[uid][oRX] = rx;
	ObjectInfo[uid][oRY] = ry;
	ObjectInfo[uid][oRZ] = rz;

	ObjectInfo[uid][oInt] = InteriorEx;
	ObjectInfo[uid][oVW] = World;

	ObjectInfo[uid][oOwnerType] = ownertype;
	ObjectInfo[uid][oOwner] = owner;
	
	ObjectInfo[uid][oCreator] = creator_uid;
	ObjectInfo[uid][oLastEditor] = creator_uid;

	ObjectInfo[uid][oGateX] = 0.0;
	ObjectInfo[uid][oGateY] = 0.0;
	ObjectInfo[uid][oGateZ] = 0.0;

	ObjectInfo[uid][oGateRX] = 0.0;
	ObjectInfo[uid][oGateRY] = 0.0;
	ObjectInfo[uid][oGateRZ] = 0.0;

	ObjectInfo[uid][oGate] = 0;

	ObjectInfo[uid][oObject] = CreateDynamicObject(ObjectInfo[uid][oModel], ObjectInfo[uid][oX], ObjectInfo[uid][oY], ObjectInfo[uid][oZ], ObjectInfo[uid][oRX], ObjectInfo[uid][oRY], ObjectInfo[uid][oRZ], ObjectInfo[uid][oVW], ObjectInfo[uid][oInt], -1);

	return uid;
}
public SaveObject(uid)
{
	new query[292];
	format(query, sizeof(query), "UPDATE `srv_objects` SET `model` = '%d', `x` = '%f', `y` = '%f', `z` = '%f', `rx` = '%f', `ry` = '%f', `rz` = '%f', `int` = '%d', `vw` = '%d', `ownertype` = '%d', `owner` = '%d', `mmat` = '%d', `lastedit_uid`='%d' WHERE `uid` = '%d'",
	ObjectInfo[uid][oModel],
	ObjectInfo[uid][oX],
	ObjectInfo[uid][oY],
	ObjectInfo[uid][oZ],
	ObjectInfo[uid][oRX],
	ObjectInfo[uid][oRY],
	ObjectInfo[uid][oRZ],
	ObjectInfo[uid][oInt],
	ObjectInfo[uid][oVW],
	ObjectInfo[uid][oOwnerType],
	ObjectInfo[uid][oOwner],
	ObjectInfo[uid][oMMAT],
	ObjectInfo[uid][oLastEditor],
	uid);
	mysql_query(query);
	return 1;
}
public SaveObjectGate(uid)
{
	new query[256];
	format(query, sizeof(query), "UPDATE `srv_objects` SET `gate_x` = '%f', `gate_y` = '%f', `gate_z` = '%f', `gate_rx` = '%f', `gate_ry` = '%f', `gate_rz` = '%f', `gate` = '%d', `lastedit_uid`='%d' WHERE `uid` = '%d'",
	ObjectInfo[uid][oGateX],
	ObjectInfo[uid][oGateY],
	ObjectInfo[uid][oGateZ],
	ObjectInfo[uid][oGateRX],
	ObjectInfo[uid][oGateRY],
	ObjectInfo[uid][oGateRZ],
	ObjectInfo[uid][oGate],
	ObjectInfo[uid][oLastEditor],
	uid);
	mysql_query(query);

	return 1;
}
public DeleteObject(uid)
{
	new query[128];
	format(query,sizeof(query),"DELETE FROM `srv_objects` WHERE `uid` = '%d'", uid);
	mysql_query(query);
	format(query,sizeof(query),"DELETE FROM `srv_mmat_text` WHERE `object_id` = '%d'", uid);
	mysql_query(query);
	format(query,sizeof(query),"DELETE FROM `srv_mmat_texture` WHERE `object_id` = '%d'", uid);
	mysql_query(query);
	
	if(ObjectInfo[uid][oOwnerType] == OWNER_GROUP)
		GroupInfo[ObjectInfo[uid][oOwner]][gObjects]--;
	else if(ObjectInfo[uid][oOwnerType] == OWNER_HOUSE)
	{
		if(!ObjectInfo[uid][oVW])
			DoorsInfo[ObjectInfo[uid][oOwner]][dObj0]--;
		else
			DoorsInfo[ObjectInfo[uid][oOwner]][dObj]--;
	}
	
	ObjectInfo[uid][oUID] = 0;
	ObjectInfo[uid][oModel] = 0;
	ObjectInfo[uid][oX] = 
	ObjectInfo[uid][oY] =
	ObjectInfo[uid][oZ] = 
	ObjectInfo[uid][oRX] = 
	ObjectInfo[uid][oRY] =
	ObjectInfo[uid][oRZ] = 0.0;
	ObjectInfo[uid][oInt] = 
	ObjectInfo[uid][oVW] = 
	ObjectInfo[uid][oOwnerType] = 
	ObjectInfo[uid][oOwner] = 
	ObjectInfo[uid][oMMAT] = 0;

	ObjectInfo[uid][oGateX] = 0.0;
	ObjectInfo[uid][oGateY] = 0.0;
	ObjectInfo[uid][oGateZ] = 0.0;

	ObjectInfo[uid][oGateRX] = 0.0;
	ObjectInfo[uid][oGateRY] = 0.0;
	ObjectInfo[uid][oGateRZ] = 0.0;

	ObjectInfo[uid][oGate] = 0;
	
	ObjectInfo[uid][oCreator] = 0;
	ObjectInfo[uid][oLastEditor] = 0;
	
	if(ObjectInfo[uid][o3dText])
	{
		DestroyDynamic3DTextLabel(ObjectInfo[uid][o3dText]);
		ObjectInfo[uid][o3dText]=Text3D:0;
	}
	DestroyDynamicObject(ObjectInfo[uid][oObject]);
	ObjectInfo[uid][oObject]=0;

	return 1;
}

public IsPlayerGateOwner(playerid, gateid)
{
	if(CharacterInfo[playerid][pAdmin]) return 1;
	if(ObjectInfo[gateid][oOwnerType] == OWNER_PLAYER && ObjectInfo[gateid][oOwner] == CharacterInfo[playerid][pUID]) return 1;
	if(ObjectInfo[gateid][oOwnerType] == OWNER_GROUP)
	{
		new groupid = ObjectInfo[gateid][oOwner];
		if(IsPlayerInGroup(playerid, groupid)) return 1;
	}
	if(ObjectInfo[gateid][oOwnerType] == OWNER_HOUSE && (DoorsInfo[ObjectInfo[gateid][oOwner]][dOwner] == CharacterInfo[playerid][pUID] || IsDoorMember(playerid, ObjectInfo[ObjectInfo[gateid][oOwner]][oOwner]) || IsDoorMember(playerid, ObjectInfo[gateid][oOwner]))) return 1;
/*
	if (ObjectInfo[gateid][oOwnerType] == OWNER_AREA)
	{
		new areaid=GetPlayerArea(playerid);
		if((AreaInfo[areaid][aOwnerType] == OWNER_GROUP && MemberGroup[playerid][1][GroupID] == AreaInfo[areaid][aOwner] )||
			(AreaInfo[areaid][aOwnerType] == OWNER_GROUP && MemberGroup[playerid][2][GroupID] == AreaInfo[areaid][aOwner]) ||
			(AreaInfo[areaid][aOwnerType] == OWNER_GROUP && MemberGroup[playerid][3][GroupID] == AreaInfo[areaid][aOwner] ) )
			return 1;
	}
*/  //odkomentowaæ po dodaniu stref
	//if (ObjectInfo[gateid][oOwnerType] == OWNER_DOOR &&  IsPlayerPermInGroup(playerid,ObjectInfo[gateid][oOwner],PANEL_VEH)) return 1; //do porpawy
	
	return 0;
}
public IsObjectOwner(playerid, objectid)
{
	if(CharacterInfo[playerid][pAdmin]) return 1;
	else if(ObjectInfo[objectid][oOwnerType] == OWNER_PLAYER && ObjectInfo[objectid][oOwner] == CharacterInfo[playerid][pUID]) return 1;
	else if(ObjectInfo[objectid][oOwnerType] == OWNER_GROUP)
	{
		new groupid = ObjectInfo[objectid][oOwner];
		if(IsPlayerPermInGroup(playerid,groupid,PERM_OBJECT))
			return 1;
	}
	else if(ObjectInfo[objectid][oOwnerType] == OWNER_HOUSE)
	{
		new dooruid = PlayerDoor[playerid];
		if(dooruid && DoorsInfo[dooruid][dOwnerTyp] == OWNER_PLAYER)
		{
			if(DoorsInfo[dooruid][dOwner] == CharacterInfo[playerid][pUID])
				return 1;
		}
		else if(dooruid && DoorsInfo[dooruid][dOwnerTyp] == OWNER_HOUSE)
		{
			if(DoorsInfo[DoorsInfo[dooruid][dOwner]][dOwnerTyp] == OWNER_PLAYER && DoorsInfo[DoorsInfo[dooruid][dOwner]][dOwner] == CharacterInfo[playerid][pUID])
				return 1;
		}
	}
	
	return 0;
}
public GetObjectModelClosest( playerid, model )
{
	ForeachEx(i, _OBJ_COUNT)
		if(ObjectInfo[i][oModel] == model)
			if(IsPlayerInRangeOfPoint(playerid, 5.0, ObjectInfo[i][oX], ObjectInfo[i][oY], ObjectInfo[i][oZ]))
				return 1;
	
	return 0;
}

stock GetObjectGateIndex( playerid, Float:range )
{	
	ForeachEx(i, _OBJ_COUNT)
		if(ObjectInfo[i][oGate])
			if(IsPlayerInRangeOfPoint(playerid, range,ObjectInfo[i][oX], ObjectInfo[i][oY], ObjectInfo[i][oZ]) && ObjectInfo[i][oVW] == GetPlayerVirtualWorld(playerid) || IsPlayerInRangeOfPoint(playerid, range, ObjectInfo[i][oGateX], ObjectInfo[i][oGateY], ObjectInfo[i][oGateZ]) && ObjectInfo[i][oVW] == GetPlayerVirtualWorld(playerid))
					return i;

	return 0;
}

public CopyObject(playerid,object_id)
{
	new Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz;
	GetDynamicObjectPos(ObjectInfo[object_id][oObject], Float:x, Float:y, Float:z);
	GetDynamicObjectRot(ObjectInfo[object_id][oObject], Float:rx, Float:ry, Float:rz);
	
	new index = AddObject(CharacterInfo[playerid][pUID], ObjectInfo[object_id][oModel], ObjectInfo[object_id][oOwnerType], ObjectInfo[object_id][oOwner], ObjectInfo[object_id][oVW], ObjectInfo[object_id][oInt], x,y,z,rx,ry,rz);

	ObjectInfo[index][oMMAT] = ObjectInfo[object_id][oMMAT];
	if(ObjectInfo[index][oMMAT]==2)
	{
		new result[256];
		mysql_query_format("SELECT * FROM `srv_mmat_texture` WHERE `object_id`='%d'",object_id);
   		mysql_store_result();
	
		while(mysql_fetch_row_format(result, "|") == 1)
		{
			new object, index2, materialcolor, modelid, txdname[32], texturename[32];

			sscanf(result,  "p<|>ddxds[32]s[32]",	object,
												index2,
												materialcolor,
												modelid,
												txdname,
												texturename);
		
			SetDynamicObjectMaterial(ObjectInfo[index][oObject], index2, modelid, txdname, texturename, ShiftRGBAToABGR(materialcolor));
			mysql_query_format("INSERT INTO `srv_mmat_texture` VALUES ('%d', '%d', '%x', '%d', '%s', '%s')", ObjectInfo[index][oUID], index2, materialcolor, modelid, txdname, texturename);
		}

	}
	else if(ObjectInfo[index][oMMAT]==1)
	{
		new result[256];
		mysql_query_format("SELECT * FROM `srv_mmat_text` WHERE `object_id`='%d'",object_id);
   		mysql_store_result();
   		while(mysql_fetch_row_format(result, "|") == 1)
		{
	   		new object, index2, matsize, fontsize, bold, fontcolor, backcolor, align, fontface[32], text[64];

			sscanf(result,  "p<|>dddddxxds[32]s[64]",	object,
														index2,
														matsize,
														fontsize,
														bold,
														fontcolor,
														backcolor,
														align,
														fontface,
														text);

			new color_font = ShiftRGBAToABGR(fontcolor);
			new color_back = ShiftRGBAToABGR(backcolor);
				
			SetDynamicObjectMaterialText(ObjectInfo[index][oObject], index2, text, matsize, fontface, fontsize, bold, color_font, color_back, align);
		}
	}
	
	SetPVarInt(playerid,"Mclone",1);
	EditDynamicObject(playerid, ObjectInfo[index][oObject]);
	PlayerEditObject[playerid] = index;
	new tekst[64];
	format(tekst,sizeof(tekst), "Poprawnie skopiowano obiekt %d [UID: %d]", ObjectInfo[object_id][oModel], ObjectInfo[object_id][oUID]);
	SendClientMessage(playerid, COLOR_GREEN,tekst);
	return 1;
}