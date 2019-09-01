CMD:mc(playerid,params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new model;
	if(sscanf(params, "d", model))
		return msg_usage(playerid,"U¿yj: /mc [ID obiektu]");
	else
	{
		if(model < 331 || (model > 371 && model < 615) || model > 19999)
			return msg_error(playerid,"Nie mo¿esz utworzyæ obiektu o tym ID.");
		
		for(new i=0; i<26; i++)
			if(model == forbidden[i])
				return msg_error(playerid,"Nie mo¿esz utworzyæ obiektu o tym ID.");
		
		new ownertype, owner;
		
		new doorid = PlayerDoor[playerid]; 
		new vw = GetPlayerVirtualWorld(playerid); 
		new interior = GetPlayerInterior(playerid); 
		new Float:Pos[3],Float:ang; 
		GetPlayerFacingAngle(playerid, ang);
		GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
		
		if(!doorid)
		{
			ForeachEx(i,_DOOR_COUNT)
			{
				if(DoorsInfo[i][dOwnerTyp] == OWNER_GROUP && !DoorsInfo[i][dEnterVW] && IsPlayerPermInGroup(playerid, DoorsInfo[i][dOwner], PERM_OBJECT) && IsPlayerInRangeOfPoint(playerid, 30.0, DoorsInfo[i][dEnterX], DoorsInfo[i][dEnterY], DoorsInfo[i][dEnterZ]))
				{
					ownertype=OWNER_GROUP;
					owner=DoorsInfo[i][dOwner];
					GroupInfo[DoorsInfo[i][dOwner]][gObjects]++;
					break;
				}
			}
			if(!ownertype && CharacterInfo[playerid][pAdmin])
			{
				ownertype=OWNER_ADMIN;
				owner=CharacterInfo[playerid][pUID];
			}
		}
		else if(doorid && DoorsInfo[doorid][dOwnerTyp] == OWNER_GROUP && IsPlayerPermInGroup(playerid, DoorsInfo[doorid][dOwner], PERM_OBJECT))
		{
			ownertype=OWNER_GROUP;
			owner=DoorsInfo[doorid][dOwner];
			GroupInfo[DoorsInfo[doorid][dOwner]][gObjects]++;
		}
		else if(doorid && DoorsInfo[doorid][dOwnerTyp] == OWNER_PLAYER && DoorsInfo[doorid][dOwner] == CharacterInfo[playerid][pUID] && GetPlayerVirtualWorld(playerid) != 0)
		{
			ownertype=OWNER_HOUSE;
			owner=doorid;
			DoorsInfo[doorid][dObj]++;
		}
		else if(doorid && DoorsInfo[DoorsInfo[doorid][dOwner]][dOwnerTyp] == OWNER_PLAYER && DoorsInfo[DoorsInfo[doorid][dOwner]][dOwner] == CharacterInfo[playerid][pUID] && GetPlayerVirtualWorld(playerid) != 0)
		{
			ownertype=OWNER_HOUSE;
			owner=DoorsInfo[doorid][dOwner];
			DoorsInfo[DoorsInfo[doorid][dOwner]][dObj]++;
		}
		else if(CharacterInfo[playerid][pAdmin] > 4)
		{
			ownertype=OWNER_ADMIN;
			owner=CharacterInfo[playerid][pUID];
		}
		else
			return msg_error(playerid,"Nie mo¿esz stworzyæ obiektu w tym miejscu.");

		if(!owner || !ownertype)
			return msg_error(playerid,"Nie posiadasz uprawnieñ do stworzenia obiektu w tym miejscu.");

		new uid = AddObject(CharacterInfo[playerid][pUID], model, ownertype, owner, vw, interior, Pos[0]-5.0*floatsin(ang,degrees), Pos[1]+5.0*floatcos(ang,degrees) , Pos[2], 0.0, 0.0, 0.0);

		PlayerEditObject[playerid] = uid;
		EditDynamicObject(playerid, ObjectInfo[uid][oObject]);
		return 1;
	}
}

CMD:msel(playerid, params[])
{	
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new modelid;
	if(sscanf(params, "d", modelid))
		SelectObject(playerid);
	else
	{
		//new searchid = GetObjectModelClosest(playerid, modelid);
		
		if(modelid <= 0 || modelid >= MAX_OBJECTS)
			return msg_error(playerid,"Wprowadzony format modelu jest nieprawid³owy.");
		if(!IsPlayerInRangeOfPoint(playerid,30.0,ObjectInfo[modelid][oX],ObjectInfo[modelid][oY],ObjectInfo[modelid][oZ]))
			return msg_error(playerid,"Nie znajdujesz siê w pobli¿u obiektu o podanym ID.");
		if(!IsObjectOwner(playerid,modelid))			
			return msg_error(playerid,"Nie posiadasz uprawnien do edycji tego obiektu.");
		
		PlayerEditObject[playerid] = modelid;
		EditDynamicObject(playerid, ObjectInfo[modelid][oObject]);
	}
	
	return 1;
}

CMD:msave(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!PlayerEditObject[playerid])
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Aktualnie nie edytujesz ¿adnego obiektu.\nU¿yj komendy: /msel do edycji obiektu.", "Zamknij", "");
		return 1;
	}
	
	new objectid = PlayerEditObject[playerid];

	GetDynamicObjectPos(ObjectInfo[objectid][oObject], ObjectInfo[objectid][oX], ObjectInfo[objectid][oY], ObjectInfo[objectid][oZ]);
	GetDynamicObjectRot(ObjectInfo[objectid][oObject], ObjectInfo[objectid][oRX], ObjectInfo[objectid][oRY], ObjectInfo[objectid][oRZ]);
	SetPVarInt(playerid,"Msave",1);

	SaveObject(objectid);
	CancelEdit(playerid);
	PlayerTextDrawHide(playerid, EditObjectText[playerid]);

	//SetTimerEx("HideObjectTextDraw", 150, false, "%d", playerid);
	
	return 1;
}

CMD:mdel(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!PlayerEditObject[playerid])
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Aktualnie nie edytujesz ¿adnego obiektu.\nU¿yj komendy: /msel do edycji obiektu.", "Zamknij", "");
		return 1;
	}
	
	// Pobieranie ID obiektu
	new objectid = PlayerEditObject[playerid];
	
	new query[128];
	format(query, sizeof(query), "DELETE FROM `srv_mmat_text` WHERE `object_id`='%d' LIMIT 1", objectid);
	mysql_query(query);
	
	format(query, sizeof(query), "DELETE FROM `srv_mmat_texture` WHERE `object_id`='%d' LIMIT 1",objectid);
	mysql_query(query);
   	
	// Usuwanie obiektu
	DeleteObject(objectid);
	
	// Zerowanie zmiennych
	CancelEdit(playerid);
	PlayerTextDrawHide(playerid, EditObjectText[playerid]);
	PlayerEditObject[playerid] = 0;
	
	return 1;
}
CMD:md(playerid,params[]) return cmd_mdel(playerid,params);

CMD:mx(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	
	new Float: pos_x;
	if(!PlayerEditObject[playerid])
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Aktualnie nie edytujesz ¿adnego obiektu.\nU¿yj komendy: /msel do edycji obiektu.", "Zamknij", "");
		return 1;
	}
	if(sscanf(params, "f", pos_x))
		return msg_usage(playerid,"U¿yj: /mx [pozycja X]");
	else
	{
		// Pobieranie ID obiektu
		new objectid = PlayerEditObject[playerid];
		new Float:Pos[3];
		
		// Pobieranie i ustawianie obiektu
		GetDynamicObjectRot(ObjectInfo[objectid][oObject], Pos[0], Pos[1], Pos[2]);
		SetDynamicObjectRot(ObjectInfo[objectid][oObject], pos_x, Pos[1], Pos[2]);
		ObjectInfo[objectid][oRX]=pos_x;
		SaveObject(objectid);
		
		// Informowanie gracza
		//Infobox(playerid, 5, "Pozycja obiektu ~g~~h~X ~w~~h~zostala zmieniona.");
		EditDynamicObject(playerid, ObjectInfo[objectid][oObject]);
	}
	
	return 1;
}
CMD:mrx(playerid, params[]) return cmd_mx(playerid, params);
CMD:rx(playerid, params[]) return cmd_mx(playerid, params);

CMD:my(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	
	new Float: pos_y;
	if(!PlayerEditObject[playerid])
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Aktualnie nie edytujesz ¿adnego obiektu.\nU¿yj komendy: /msel do edycji obiektu.", "Zamknij", "");
		return 1;
	}
	if(sscanf(params, "f", pos_y))
		return msg_usage(playerid,"U¿yj: /my [pozycja Y]");
	else
	{
		// Pobieranie ID obiektu
		new objectid = PlayerEditObject[playerid];
		new Float:Pos[3];
		
		// Pobieranie i ustawianie obiektu
		GetDynamicObjectRot(ObjectInfo[objectid][oObject], Pos[0], Pos[1], Pos[2]);
		SetDynamicObjectRot(ObjectInfo[objectid][oObject], Pos[0], pos_y, Pos[2]);
		ObjectInfo[objectid][oRY]=pos_y;
		SaveObject(objectid);
		
		// Informowanie gracza
		//Infobox(playerid, 5, "Pozycja obiektu ~g~~h~Y ~w~~h~zostala zmieniona.");
		EditDynamicObject(playerid, ObjectInfo[objectid][oObject]);
	}
	
	return 1;
}
CMD:mry(playerid, params[]) return cmd_my(playerid, params);
CMD:ry(playerid, params[]) return cmd_my(playerid, params);

CMD:mz(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new Float: pos_z;
	if(!PlayerEditObject[playerid])
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Aktualnie nie edytujesz ¿adnego obiektu.\nU¿yj komendy: /msel do edycji obiektu.", "Zamknij", "");
		return 1;
	}
	if(sscanf(params, "f", pos_z))
		return msg_usage(playerid,"U¿yj: /mz [pozycja Z]");
	else
	{
		// Pobieranie ID obiektu
		new objectid = PlayerEditObject[playerid];
		new Float:Pos[3];
		
		// Pobieranie i ustawianie obiektu
		GetDynamicObjectRot(ObjectInfo[objectid][oObject], Pos[0], Pos[1], Pos[2]);
		SetDynamicObjectRot(ObjectInfo[objectid][oObject], Pos[0], Pos[1], pos_z);
		ObjectInfo[objectid][oRZ]=pos_z;
		SaveObject(objectid);
		
		// Informowanie gracza
		//Infobox(playerid, 5, "Pozycja obiektu ~g~~h~Z ~w~~h~zostala zmieniona.");
		EditDynamicObject(playerid, ObjectInfo[objectid][oObject]);
	}
	
	return 1;
}
CMD:mrz(playerid, params[]) return cmd_mz(playerid, params);
CMD:rz(playerid, params[]) return cmd_mz(playerid, params);

CMD:mmat(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!PlayerEditObject[playerid])
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Aktualnie nie edytujesz ¿adnego obiektu.\nU¿yj komendy: /msel do edycji obiektu.", "Zamknij", "");
		return 1;
	}
	
	new index, type, comm1[128];
	if(sscanf(params, "ddS()[128]", index, type, comm1))
		return msg_usage(playerid,"U¿yj: /mmat [index (0 - 10)] [0 - tekstura / 1 - napis] [parametry]");
	else
	{
		if(index < 0 || index > 10)
			return msg_error(playerid,"Wprowadzony index jest nieprawid³owy.\nMaksymalny index to 10.");
		if(type != 0 && type != 1)
			return msg_error(playerid,"Parametr typu jest nieprawid³owy.\nMo¿liwy to 0 lub 1.");
		
		if(type) // Napis
		{
			new object = PlayerEditObject[playerid];
			new matsize, fontsize, bold, fontcolor, backcolor, align, fontface[32], text[64];
			
			if(sscanf(comm1, "dddxxds[32]s[64]", matsize, fontsize, bold, fontcolor, backcolor, align, fontface, text))
				return msg_usage(playerid,"U¿yj: /mmat [index (0 - 5)] 1 [matsize] [fontsize] [bold] [fontcolor] [backcolor] [align] [font] [text]");
			else
			{
				for(new i=0;i<strlen(text);i++)
					if(text[i]=='|' || text[i]=='`' || text[i]=='\'' )
						return msg_error(playerid,"Text zawiera niedozwolony znak.");
				new color_font = ShiftRGBAToABGR(fontcolor);
				new color_back = ShiftRGBAToABGR(backcolor);
				
				EscapeMMAT(text);
				
				SetDynamicObjectMaterialText(ObjectInfo[object][oObject], index, text, matsize, fontface, fontsize, bold, color_font, color_back, align);
				
				ObjectInfo[object][oMMAT] = 1;
				
				SaveObject(ObjectInfo[object][oUID]);
				
				mysql_query_format("DELETE FROM `srv_mmat_text` WHERE `index` = '%d' AND `object_id` = '%d'", index, ObjectInfo[object][oUID]);
				mysql_query_format("INSERT INTO `srv_mmat_text` VALUES ('%d', '%d', '%d', '%d', '%d', '%x', '%x', '%d', '%s', '%s')", ObjectInfo[object][oUID], index, matsize, fontsize, bold, color_font, color_back, align, fontface, text);
			}
		}
		else // Tekstura
		{
			new object = PlayerEditObject[playerid];
			new modelid, txdname[32], texturename[32], materialcolor;
			
			if(sscanf(comm1, "xds[32]s[32]", materialcolor, modelid, txdname, texturename))
				return msg_usage(playerid,"U¿yj: /mmat [index (0 - 5)] 0 [materialcolor] [modelid] [txdname] [texturename]");
			else
			{
				SetDynamicObjectMaterial(ObjectInfo[object][oObject], index, modelid, txdname, texturename, ShiftRGBAToABGR(materialcolor));
				
				ObjectInfo[object][oMMAT] = 2;
				
				SaveObject(ObjectInfo[object][oUID]);
				
				mysql_query_format("DELETE FROM `srv_mmat_texture` WHERE `index` = '%d' AND `object_id` = '%d'", index, ObjectInfo[object][oUID]);
				mysql_query_format("INSERT INTO `srv_mmat_texture` VALUES ('%d', '%d', '%x', '%d', '%s', '%s')", ObjectInfo[object][oUID], index, ShiftRGBAToABGR(materialcolor), modelid, txdname, texturename);
			}
		}
	}
	
	return 1;
}

CMD:mclone(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	
	if(!PlayerEditObject[playerid])
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Aktualnie nie edytujesz ¿adnego obiektu.\nU¿yj komendy: /msel do edycji obiektu.", "Zamknij", "");
		return 1;
	}
	
	new object_id = PlayerEditObject[playerid];
	cmd_msave(playerid,"");
	SetTimerEx("CopyObject", 250, false, "ii", playerid, object_id);
	
	return 1;
}
CMD:mcopy(playerid, params[]) return cmd_mclone(playerid, params);

CMD:mgate(playerid, params[])
{
	if(!PlayerEditObject[playerid])
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Aktualnie nie edytujesz ¿adnego obiektu.\nU¿yj komendy: /msel do edycji obiektu.", "Zamknij", "");
		return 1;
	}
	
	// Zakoñczenie edycji bramy
	PlayerEditGate[playerid] = true;
	
	// Zerowanie edycji
	CancelEdit(playerid);
	PlayerTextDrawHide(playerid, EditObjectText[playerid]);
	
	// Informowanie gracza
	//Infobox(playerid, 5, "Brama zostala ~g~~h~pomyslnie ~w~~h~zapisana.");
	return 1;
}
CMD:brama(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	
	new gateid;
	if(IsPlayerInAnyVehicle(playerid))
		gateid = GetObjectGateIndex(playerid, 15.0);
	else
		gateid = GetObjectGateIndex(playerid, 5.0);
	if(!gateid)
		return 1;
	if(!IsPlayerGateOwner(playerid,gateid)) return 1;
	
	if(ObjectInfo[gateid][oGateOpen])
	{
		MoveDynamicObject(ObjectInfo[gateid][oObject], ObjectInfo[gateid][oX], ObjectInfo[gateid][oY], ObjectInfo[gateid][oZ], 2.0, ObjectInfo[gateid][oRX], ObjectInfo[gateid][oRY], ObjectInfo[gateid][oRZ]);
		ObjectInfo[gateid][oGateOpen] = false;
		
		Tip(playerid, 3, "Zamykasz brame.");
	}
	else
	{
		MoveDynamicObject(ObjectInfo[gateid][oObject], ObjectInfo[gateid][oGateX], ObjectInfo[gateid][oGateY], ObjectInfo[gateid][oGateZ], 2.0, ObjectInfo[gateid][oGateRX], ObjectInfo[gateid][oGateRY], ObjectInfo[gateid][oGateRZ]);
		ObjectInfo[gateid][oGateOpen] = true;
		
		Tip(playerid, 3, "Otwierasz brame.");
	}
	
	return 1;
}
CMD:br(playerid, params[]) return cmd_brama(playerid, params);

CMD:mtext(playerid,params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new string[32];
	if(!GetPVarInt(playerid, "PlayerObject3dText"))
	{		
		if(!GetPlayerVirtualWorld(playerid))
		{
			ForeachEx(i,_OBJ_COUNT)
			{
				if(ObjectInfo[i][oObject] && !ObjectInfo[i][oVW] && IsObjectOwner(playerid, i) &&IsPlayerInRangeOfPoint(playerid, 50.0, ObjectInfo[i][oX], ObjectInfo[i][oY], ObjectInfo[i][oZ]) && !ObjectInfo[i][o3dText])
				{
					format(string,sizeof(string),"UID: %d, Model: %d",i,ObjectInfo[i][oModel]);
					ObjectInfo[i][o3dText]=CreateDynamic3DTextLabel(string, COLOR_MTEXT, ObjectInfo[i][oX], ObjectInfo[i][oY], ObjectInfo[i][oZ], 50.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0, 0);
					ObjectInfo[i][o3dTextPlayer]=playerid;
				}
			}
		}
		else
		{
			ForeachEx(i,_OBJ_COUNT)
			{
				if(ObjectInfo[i][oObject] && ObjectInfo[i][oVW] == GetPlayerVirtualWorld(playerid) && IsObjectOwner(playerid, i) && !ObjectInfo[i][o3dText])
				{
					format(string,sizeof(string),"UID: %d, Model: %d",i,ObjectInfo[i][oModel]);
					ObjectInfo[i][o3dText]=CreateDynamic3DTextLabel(string, COLOR_MTEXT, ObjectInfo[i][oX], ObjectInfo[i][oY], ObjectInfo[i][oZ], 50.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0, ObjectInfo[i][oVW]);
					ObjectInfo[i][o3dTextPlayer]=playerid;
				}
			}
		}
		SetPVarInt(playerid, "PlayerObject3dText", 1);
		msg_info(playerid,"W³¹czy³eœ 3dTexty obiektów");
	}
	else
	{
		ForeachEx(i,_OBJ_COUNT)
		{
			if(ObjectInfo[i][o3dTextPlayer]==playerid)
			{
				DestroyDynamic3DTextLabel(ObjectInfo[i][o3dText]);
				ObjectInfo[i][o3dText]=Text3D:0;
				ObjectInfo[i][o3dTextPlayer] = -1;
			}
		}
		DeletePVar(playerid, "PlayerObject3dText");
		msg_info(playerid,"Wy³¹czy³eœ 3dTexty obiektów.");
	}

	return 1;
}
CMD:mowner(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin] < 5 )
		return msg_error(playerid,"Nie posiadasz uprawnien do u¿ycia tej komendy");

	if(!PlayerEditObject[playerid])
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, " Informacja", "Aktualnie nie edytujesz ¿adnego obiektu.\nU¿yj komendy: /msel do edycji obiektu.", "Zamknij", "");
		return 1;
	}
	new ownertype,owner;
	if(sscanf(params, "dd", ownertype,owner))
		return msg_usage(playerid,"U¿yj: /mowner [typ w³aœciciela] [w³aœciiel]\n\nTypy:\n0. Admin\n1. Gracz [UID gracza]\n2. Grupa [UID grupy]\n3. Dom [UID domu]");
	if(ownertype<0 || ownertype>3)
		return msg_error(playerid,"Niew³aœciwy typ w³aœciciela.");
	new objectid = PlayerEditObject[playerid];
	ObjectInfo[objectid][oOwnerType]=ownertype;
	ObjectInfo[objectid][oOwner]=owner;
	
	SaveObject(objectid);

	CancelEdit(playerid);
	PlayerEditObject[playerid] = 0;
	SetTimerEx("HideObjectTextDraw", 150, false, "i", playerid);

	return 1;
}
