forward AddGroup(name[32], tag[8], type, leader);
forward SaveGroup(uid, what);
forward SaveMember(playerid, groupid);
forward AddMember(playerid, groupid, perm);
forward DeleteMember(playerid, groupid);
forward DeleteGroup(uid);
forward IsPlayerInGroup(playerid, groupid);
forward IsPlayerInGroupType(playerid, gtype);
forward IsPlayerPermInGroup(playerid, groupid, perm);
forward HaveFreeSlotGroup(playerid);
forward GetPlayerGroupSlot(playerid, groupid);
forward GiveGroupCash(groupid,cash);
forward GiveOfficialGroupCash(gtype,cash);
forward TransportLoad(playerid);
forward FuelLoad(playerid);
forward SellDrugs(playerid);
forward GiveSalary(playerid,groupid);
forward TakeItemFormPlayer(playerid,playerid2);
forward TakeMoneyFormPlayer(playerid,playerid2);

public AddGroup(name[32], tag[8], type, leader)
{
	new uid;
	
	ForeachEx(i, MAX_GROUPS)
	{
		if(GroupInfo[i][gUID] == 0 && i != 0)
		{
			uid = i;
			break;
		}
	}
	mysql_real_escape_string(name,name);
	new query[512];
	format(query, sizeof(query), "INSERT INTO `srv_groups` (`UID`, `name`, `tag`, `type`, `leader`, `spawn_x`, `spawn_y`, `spawn_z`, `spawn_angle`) VALUES ('%d', '%s', '%s', '%d', '%d', '%f', '%f', '%f', '%f')", uid, name, tag, type, leader, SettingInfo[sSpawnX], SettingInfo[sSpawnY], SettingInfo[sSpawnZ], SettingInfo[sSpawnAngle]);
	mysql_query(query);
	
	GroupInfo[uid][gUID] = uid;
	GroupInfo[uid][gName] = name;
	GroupInfo[uid][gTag] = tag;
	GroupInfo[uid][gType] = type;
	GroupInfo[uid][gCash] = 
	GroupInfo[uid][gFlags] = 0;
	GroupInfo[uid][gLeader] = leader;
	GroupInfo[uid][gSpawnX] = SettingInfo[sSpawnX];
	GroupInfo[uid][gSpawnY] = SettingInfo[sSpawnY];
	GroupInfo[uid][gSpawnZ] = SettingInfo[sSpawnZ];
	GroupInfo[uid][gSpawnAngle] = SettingInfo[sSpawnAngle];
	GroupInfo[uid][gSpawnInt] = 
	GroupInfo[uid][gSpawnVW] = 
	GroupInfo[uid][gGrant] = 
	GroupInfo[uid][gSalaryAccount] = 
	GroupInfo[uid][gOOCBlock] = 
	GroupInfo[uid][gObjects] = 
	GroupInfo[uid][gNotice] = 
	GroupInfo[uid][gRegistered] = 0;
	GroupInfo[uid][gColor] = -1;

	if(type==GROUP_TAXI || type==GROUP_WORKSHOP || type==GROUP_GYM)
	{
		format(query,sizeof(query),"INSERT INTO `srv_group_offer_prices`(`groupid`) VALUES ('%d')",uid);
		mysql_query(query);
	}
	
	return uid;
}

public SaveGroup(uid, what)
{
	new string[512];
	
	if(what == SAVE_GROUP_BASIC)
	{
		format(string, sizeof(string), "UPDATE `srv_groups` SET `name` = '%s', `tag` = '%s', `type` = '%d', `cash` = '%d', `leader` = '%d', `color` = '%d', `registered` = '%d', `salary_account`='%d' WHERE `UID` = '%d' LIMIT 1",
		GroupInfo[uid][gName],
		GroupInfo[uid][gTag],
		GroupInfo[uid][gType],
		GroupInfo[uid][gCash],
		GroupInfo[uid][gLeader],
		GroupInfo[uid][gColor],
		GroupInfo[uid][gRegistered],
		GroupInfo[uid][gSalaryAccount],
		
		uid);
		
		mysql_query(string);
	}
	else if(what == SAVE_GROUP_FLAGS)
	{
		format(string, sizeof(string), "UPDATE `srv_groups` SET `flags` = '%d' WHERE `UID` = '%d' LIMIT 1",
		GroupInfo[uid][gFlags],
		
		uid);
		
		mysql_query(string);
	}
	else if(what == SAVE_GROUP_SPAWN)
	{
		format(string, sizeof(string), "UPDATE `srv_groups` SET `spawn_x` = '%f', `spawn_y` = '%f', `spawn_z` = '%f', `spawn_angle` = '%f', `spawn_int` = '%d', `spawn_vw` = '%d' WHERE `UID` = '%d' LIMIT 1",
		GroupInfo[uid][gSpawnX],
		GroupInfo[uid][gSpawnY],
		GroupInfo[uid][gSpawnZ],
		GroupInfo[uid][gSpawnAngle],
		GroupInfo[uid][gSpawnInt],
		GroupInfo[uid][gSpawnVW],
		
		uid);
		
		mysql_query(string);
	}
	
	return 1;
}

public SaveMember(playerid,groupid)
{
	new slot=0;
	for(new i=1; i<MAX_PLAYER_GROUPS;i++)
	{
		if(MemberGroup[playerid][i][GroupID]==groupid)
			slot=i;
	}
	if(!slot) return 0;
	new query[512];
	format(query, sizeof(query), "UPDATE `srv_groups_members` SET `rank_name`='%s', `rank`='%d', `permission`='%d', `skin`='%d', `salary`='%d', `payment`='%d', `time`='%d', `commission`='%d' WHERE `player_uid`='%d' AND `group_uid`='%d' LIMIT 1",
		MemberGroup[playerid][slot][GroupRankName],
		MemberGroup[playerid][slot][GroupRank],
		MemberGroup[playerid][slot][GroupPerm],
		MemberGroup[playerid][slot][GroupSkin],
		MemberGroup[playerid][slot][GroupSalary],
		MemberGroup[playerid][slot][GroupPayment],
		MemberGroup[playerid][slot][GroupTime],
		MemberGroup[playerid][slot][GroupCommission],
		CharacterInfo[playerid][pUID],
		MemberGroup[playerid][slot][GroupID]
		);
	mysql_query(query);
	return 1;
}

public AddMember(playerid, groupid, perm)
{
	new query[128];
	format(query, sizeof(query), "INSERT INTO `srv_groups_members`(`group_uid`, `player_uid`, `permission`) VALUES ('%d', '%d', '%d')", groupid, CharacterInfo[playerid][pUID],perm);
	mysql_query(query);
	
	if(GroupInfo[groupid][gType]==GROUP_GANG)
		for(new i=1; i<MAX_CORNERS; i++)
			if(CornerInfo[i][cOwner]==groupid)
				SetPlayerMapIcon(playerid, CornerInfo[i][cIcon], CornerInfo[i][cPosX], CornerInfo[i][cPosY], CornerInfo[i][cPosZ], 23, 0, MAPICON_LOCAL_CHECKPOINT);
	
	LoadPlayerGroups(playerid);
	return 1;
}

public DeleteMember(playerid, groupid)
{
	new query[128];
	format(query, sizeof(query), "DELETE FROM `srv_groups_members` WHERE `player_uid`='%d' AND `group_uid`='%d' LIMIT 1", CharacterInfo[playerid][pUID], groupid);
	mysql_query(query);
	
	if(GroupInfo[groupid][gType]==GROUP_GANG)
		for(new i=1;i<MAX_CORNERS;i++)
			if(CornerInfo[i][cOwner]==groupid)
				RemovePlayerMapIcon(playerid, CornerInfo[i][cIcon]);
	
	if(DutyGroup[playerid] == groupid)
	{
		if(IsPlayerPremium(playerid)) CharacterInfo[playerid][pNickColor] = COLOR_PREMIUM;
		else CharacterInfo[playerid][pNickColor] = COLOR_USER;
		
		DutyGroup[playerid] = 0;
		DutyGroupTime[playerid] = 0;
	}
	LoadPlayerGroups(playerid);
}

public DeleteGroup(uid)
{
	ForeachPlayer(i)
		for(new g=1; g<4; g++)
			if(MemberGroup[i][g][GroupID] == uid)
				DeleteMember(i, uid);
	
	new query[128];
	
	ForeachEx(i,_VEH_COUNT)
	{
		if(VehicleInfo[i][vOwnerTyp] == OWNER_GROUP && VehicleInfo[i][vOwner] == uid)
		{
			if(VehicleInfo[i][vSpawned]) UnspawnVehicle(i);
			
			DeleteVehicle(i);
		}
	}
	
	ForeachEx(i, _DOOR_COUNT)
	{
		if(DoorsInfo[i][dOwnerTyp] == OWNER_GROUP && DoorsInfo[i][dOwner] == uid)
		{
			DeleteDoor(i);

			format(query,sizeof(query),"DELETE FROM `srv_orders` WHERE `door_uid` = '%d'", i);
			mysql_query(query);
		}
	}
	
	ForeachEx(i, _OBJ_COUNT)
		if(ObjectInfo[i][oOwnerType] == OWNER_GROUP && ObjectInfo[i][oOwner] == uid)
			DeleteObject(i);
	
	ForeachEx(i,_ITEM_COUNT)
		if(ItemInfo[i][iOwnerTyp] == OWNER_GROUP && ItemInfo[i][iOwner] == uid)
			DeleteItem(i);
	
	ForeachEx(i, MAX_STATIONS)
	{
		if(StationInfo[i][sOwner] == uid)
		{
			StationInfo[i][sOwner]=0;
			format(query,sizeof(query),"UPDATE `srv_fuel_stations` SET `owner`='1' WHERE `uid`='%d'",i);
			mysql_query(query);
		}
	}
	ForeachEx(i, MAX_CORNERS)
	{
		if(CornerInfo[i][cOwner]==uid)
		{
			format(query,sizeof(query),"DELETE FROM `srv_corners` WHERE `uid`='%d'",uid);
			mysql_query(query);
			
			CornerInfo[i][cUID]= 
			CornerInfo[i][cOwner] = 0;
			CornerInfo[i][cPosX]= 
			CornerInfo[i][cPosY]= 
			CornerInfo[i][cPosZ]= 0.0;
			CornerInfo[i][cIcon]= -1;
		}
	}
	
	format(query,sizeof(query),"DELETE FROM `srv_groups` WHERE `UID` = '%d' LIMIT 1",uid);
	mysql_query(query);
	format(query,sizeof(query),"DELETE FROM `srv_groups_members` WHERE `group_uid` = '%d'",uid);
	mysql_query(query);
	format(query,sizeof(query),"DELETE FROM `srv_group_offer_logs` WHERE `groupid` = '%d'",uid);
	mysql_query(query);
	format(query,sizeof(query),"DELETE FROM `srv_group_offer_prices` WHERE `groupid`='%d'",uid);
	mysql_query(query);
	
	GroupInfo[uid][gUID] = 
	GroupInfo[uid][gName] = 
	GroupInfo[uid][gTag] = 
	GroupInfo[uid][gType] = 
	GroupInfo[uid][gCash] = 
	GroupInfo[uid][gFlags] = 
	GroupInfo[uid][gLeader] = 0;
	GroupInfo[uid][gSpawnX] = 
	GroupInfo[uid][gSpawnY] = 
	GroupInfo[uid][gSpawnZ] = 
	GroupInfo[uid][gSpawnAngle] = 0.0;
	GroupInfo[uid][gSpawnInt] = 
	GroupInfo[uid][gSpawnVW] = 
	GroupInfo[uid][gColor] = 
	GroupInfo[uid][gObjects] = 
	GroupInfo[uid][gNotice] = 
	GroupInfo[uid][gRegistered] = 
	GroupInfo[uid][gGrant] = 
	GroupInfo[uid][gSalaryAccount] = 
	GroupInfo[uid][gOOCBlock] = 0;
	
	return 1;
}
public IsPlayerInGroup(playerid, groupid)
{
	ForeachEx(i, MAX_PLAYER_GROUPS)
		if(MemberGroup[playerid][i][GroupID]==groupid)
			return true;
	
	return false;
}

public IsPlayerInGroupType(playerid, gtype)
{
	ForeachEx(i, MAX_PLAYER_GROUPS)
		if(GroupInfo[MemberGroup[playerid][i][GroupID]][gType]==gtype)
			return MemberGroup[playerid][i][GroupID];
	
	return 0;
}

public IsPlayerPermInGroup(playerid, groupid, perm)
{
	ForeachEx(i, MAX_PLAYER_GROUPS)
		if((MemberGroup[playerid][i][GroupID]==groupid) && (MemberGroup[playerid][i][GroupPerm] & perm))
			return true;
	
	return false;
}

stock IsPlayerInCriminalGroup(playerid)
{
	new gtype;
	ForeachEx(i, MAX_PLAYER_GROUPS)
	{
		if(MemberGroup[playerid][i][GroupID])
		{
			gtype=GroupInfo[MemberGroup[playerid][i][GroupID]][gType];
			if(gtype==GROUP_GANG || gtype==GROUP_MAFIA || gtype==GROUP_DRIVERS || gtype==GROUP_SYNDICATE || gtype==GROUP_CARTEL)
				return true;
		}
	}
	
	return false;
}

stock IsPlayerInOfficialGroup(playerid)
{
	new gtype;
	ForeachEx(i, MAX_PLAYER_GROUPS)
	{
		if(MemberGroup[playerid][i][GroupID])
		{
			gtype=GroupInfo[MemberGroup[playerid][i][GroupID]][gType];
			if(gtype==GROUP_GOV || gtype==GROUP_PD || gtype==GROUP_MC || gtype==GROUP_NEWS || gtype==GROUP_FBI || gtype==GROUP_MILITARY)
				return true;
		}
	}
	
	return false;
}

stock IsPlayerInBuisnessGroup(playerid)
{
	new gtype;
	ForeachEx(i, MAX_PLAYER_GROUPS)
	{
		if(MemberGroup[playerid][i][GroupID])
		{
			gtype=GroupInfo[MemberGroup[playerid][i][GroupID]][gType];
			if(gtype==GROUP_SHOP || gtype==GROUP_WORKSHOP || gtype==GROUP_TAXI || gtype==GROUP_SECURITY || gtype==GROUP_CARDEALER || gtype==GROUP_LOGISTIC || gtype==GROUP_BANK)
				return true;
			else if(gtype==GROUP_GYM || gtype==GROUP_RESTAURANT || gtype==GROUP_FUELSTATION || gtype==GROUP_KASYNO || gtype==GROUP_KLUB || gtype==GROUP_GUNSHOP)
				return true;
		}
	}
	
	return false;
}

public HaveFreeSlotGroup(playerid)
{
	if(!MemberGroup[playerid][1][GroupID]) return true;
	if(!MemberGroup[playerid][2][GroupID]) return true;
	if(!MemberGroup[playerid][3][GroupID]) return true;
	if(IsPlayerPremium(playerid))
	{
		if(!MemberGroup[playerid][4][GroupID]) return true;
		if(!MemberGroup[playerid][5][GroupID]) return true;
	}
	return false;
}

public GetPlayerGroupSlot(playerid, groupid)
{
	for(new i=1; i< MAX_PLAYER_GROUPS; i++)
		if(MemberGroup[playerid][i][GroupID]==groupid)
			return i;
	
	return 0;
}

stock IsPlayerOnDutyInGroup(playerid, gtype)
{	
	if(GroupInfo[DutyGroup[playerid]][gType] == gtype)
		return true;	
	
	return false;
}

stock IsPlayerOnDutyInCertGroup(playerid, gid)
{
	if(IsPlayerInGroup(playerid, gid) && DutyGroup[playerid] == gid)
		return true;
	
	return false;
}

stock IsPlayerGroupPerm(playerid, perm)
{
	ForeachEx(i, MAX_PLAYER_GROUPS)
		if(GroupInfo[MemberGroup[playerid][i][GroupID]][gFlags] & perm)
			return MemberGroup[playerid][i][GroupID];
	
	return false;
}

stock GetGroupColor(uid)
{
	return GroupInfo[uid][gColor];
}

public GiveGroupCash(groupid,cash)
{
	GroupInfo[groupid][gCash] += cash;
	new query[128];
	format(query,sizeof(query),"UPDATE `srv_groups` SET `cash` = '%d' WHERE `UID` = '%d'",GroupInfo[groupid][gCash], groupid);
	mysql_query(query);
	return 1;
}

public GiveOfficialGroupCash(gtype,cash)
{
	if(gtype < 1 || gtype > 4)
		return 0;
	ForeachEx(i,MAX_GROUPS)
		if(GroupInfo[i][gType] == gtype)
			 return GiveGroupCash(i,cash);
	
	return 0;
}

public TransportLoad(playerid)
{
	PlayerPlaySound(playerid, 6002,0.0,0.0,0.0);
	Tip(playerid,5,"Dostarcz towar do magazynu.");
	SetPVarInt(playerid,"Transport",2);
	UnfreezePlayer(playerid);
	SetPlayerCheckpoint(playerid,SettingInfo[sMagazineX],SettingInfo[sMagazineY],SettingInfo[sMagazineZ],8.0);
	return 1;
}
public FuelLoad(playerid)
{
	if(GetPVarInt(playerid, "TransportFuel")>0)
	{
		new result[4];
		new query[128];
		format(query, sizeof(query), "SELECT `station_id` FROM `srv_fuel_orders` WHERE `uid`='%d'",GetPVarInt(playerid,"TransportFuel"));
		mysql_query(query);
		mysql_store_result();
		mysql_fetch_row_format(result, "|");
		new stationid=strval(result);
		mysql_free_result();
		FreezePlayer(playerid);

		Tip(playerid,5,"Dostarcz paliwo na stacje.");
		SetPVarInt(playerid,"TransportFuel",-GetPVarInt(playerid, "TransportFuel"));
		SetPlayerCheckpoint(playerid, StationInfo[stationid][sPosX], StationInfo[stationid][sPosY], StationInfo[stationid][sPosZ], 10.0);
	}
	else if(GetPVarInt(playerid, "TransportFuel")<0)
	{
		new result[16],fuel,stationid;
		new query[128];
		format(query, sizeof(query), "SELECT `station_id`, `value` FROM `srv_fuel_orders` WHERE `uid`='%d'",-GetPVarInt(playerid,"TransportFuel"));
		mysql_query(query);
		mysql_store_result();
		mysql_fetch_row_format(result, "|");
		sscanf(result,"p<|>dd",stationid,fuel);
		mysql_free_result();

		AddStationFuel(stationid, fuel);
		fuel = (SettingInfo[sFuelCost] * fuel)/5;
		
		if(fuel > 400)
			fuel = 400;
		
		format(query, sizeof(query), "UPDATE `srv_fuel_orders` SET `status`='1' WHERE `uid`='%d'",-GetPVarInt(playerid, "TransportFuel"));
		mysql_query(query);
		new groupid=DutyGroup[playerid];
		new commission=GetMemberCommission(playerid,groupid);
		if(commission > 0)
		{
			commission= floatround( (float(fuel)/100.0) * float(commission));
			fuel-=commission;
			CharacterInfo[playerid][pCredit] += commission;
			SavePlayerStats(playerid,SAVE_PLAYER_BASIC);
			msg_infoFormat(playerid,128,"Paliwo dostarczone. Na konto grupy wp³ynê³o $%d.\nTwoja prowizja: $%d",fuel,commission);
		}
		else
			msg_infoFormat(playerid,64,"Paliwo dostarczone. Na konto grupy wp³ynê³o $%d.",fuel);

		GiveGroupCash(groupid,fuel);
		DeletePVar(playerid, "TransportFuel");
		LogGroupOffer(playerid,DutyGroup[playerid],"Transport paliwa",fuel);
	}
	UnfreezePlayer(playerid);
	return 1;
}

public SellDrugs(playerid)
{
	if(!CharacterInfo[playerid][pCorner]) return 1;
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
	{
		CharacterInfo[playerid][pCornerTimer] = SetTimerEx("SellDrugs", 60000+random(10)*30000, false, "i", playerid);
		return 1;
	}
	new count, drug[21];
	ForeachEx(i, _ITEM_COUNT)
	{
		if( (ItemInfo[i][iType] == ITEM_TYPE_MARIHUANA || ItemInfo[i][iType] == ITEM_TYPE_LSD || ItemInfo[i][iType] == ITEM_TYPE_KOKAINA || ItemInfo[i][iType] == ITEM_TYPE_HEROINA) && ItemInfo[i][iOwnerTyp]==OWNER_PLAYER && ItemInfo[i][iOwner]==CharacterInfo[playerid][pUID])
		{
			drug[count]=i;
			count++;
			if(count>19)
				break;
		}
	}
	if(!count)
	{
		CharacterInfo[playerid][pCorner]=0;
		return msg_error(playerid,"Nie masz przy sobie narkotyków. Sprzeda¿ anulowana.");
	}
	new itemid=drug[random(count)];
	new price;
	switch(ItemInfo[itemid][iType])
	{
		case ITEM_TYPE_MARIHUANA:
		{
			price = 40;
		}
		case ITEM_TYPE_HEROINA:
		{
			price = 100;
		}
		case ITEM_TYPE_KOKAINA:
		{
			price = 160;
		}
		case ITEM_TYPE_LSD:
		{
			price = 300;
		}
		default:
			price = 0;
	}
	if(!price)
		return msg_error(playerid,"Wyst¹pi³ b³¹d. Skontaktuj siê z administracj¹");
	price += price/10 * random(3);
	
	new ilosc = 1;
	if(ItemInfo[itemid][iValue1] > 1 && ItemInfo[itemid][iValue1] < 6)
		ilosc = 1+random(ItemInfo[itemid][iValue1]);
	else if(ItemInfo[itemid][iValue1] > 5)
		ilosc = 1+random(5);
	
	price *= ilosc;
	
	new string[196];
	format(string,sizeof(string),"Pojawia siê klient, który chce od Ciebie kupiæ %s (iloœæ: %d). Oferuje Ci $%d.\nCzy chcesz sprzedaæ narkotyk/i?", ItemInfo[itemid][iName], ilosc, price);
	SetPVarInt(playerid, "DrugID", itemid);
	SetPVarInt(playerid, "DrugPrice", price);
	SetPVarInt(playerid, "DrugCount", ilosc);
	return ShowPlayerDialog(playerid, D_CORNER, DIALOG_STYLE_MSGBOX, DEF_NAME" » narkotyki", string, "Tak", "Nie");
}
stock LogGroupOffer(playerid,groupid,type[32],income,customer=INVALID_PLAYER_ID)
{
	new query[256];
	if(customer==INVALID_PLAYER_ID)
		customer=0;
	else
		customer=CharacterInfo[customer][pUID];
	format(query,sizeof(query),"INSERT INTO `srv_group_offer_logs` VALUES (NULL,'%d','%d','%d','%d','%s','%d','%d')",groupid,CharacterInfo[playerid][pUID],CharacterInfo[playerid][pGID],customer,type,income,gettime());
	mysql_query(query);
}
public GiveSalary(playerid,groupid)
{
	if(DutyGroup[playerid] != groupid)
		return 0;
	new slot=GetPlayerGroupSlot(playerid,groupid);
	if(MemberGroup[playerid][slot][GroupPayment] < MAX_SALARY_PRE_DAY)
	{
		MemberGroup[playerid][slot][GroupPayment]++;
		new cash=MemberGroup[playerid][slot][GroupSalary];
		if(cash>0)
		{
			if(GroupInfo[groupid][gCash] >= cash || GroupInfo[groupid][gSalaryAccount]>=cash)
			{
				CharacterInfo[playerid][pCredit]+=cash;
				if(GroupInfo[groupid][gSalaryAccount]>=cash)
				{
					GroupInfo[groupid][gSalaryAccount] -= cash;
					SaveGroup(groupid,SAVE_GROUP_BASIC);
				}
				else
					GiveGroupCash(groupid,-cash);
				
				SendClientMessageFormat(playerid, GetGroupColor(groupid), "Otrzyma³eœ wyp³atê z grupy %s. Na Twoje konto wp³ynê³o $%d.",GroupInfo[groupid][gName],cash);
				LogGroupOffer(playerid,groupid,"Wyplata",-cash);
				new hour;
				gettime(hour);
				if(hour >= 18 && hour <= 21)
				{
					CharacterInfo[playerid][pCredit] += cash/2;
					SendClientMessageFormat(playerid, GetGroupColor(groupid), "W zwi¹zku z prac¹ w godzinach szczytu otrzymujesz dodatkowo $%d.", cash/2);
				}
				SavePlayerStats(playerid,SAVE_PLAYER_BASIC);
			}
			else
				SendClientMessage(playerid, GetGroupColor(groupid), "Przepracowa³eœ wyznaczony czas w grupie. Nie otrzymujesz wyp³aty, gdy¿ na koncie nie ma wystarczaj¹cych funduszy.");
		}
		else
			SendClientMessage(playerid, GetGroupColor(groupid), "Przepracowa³eœ wyznaczony czas w grupie. Nie otrzymujesz wyp³aty, gdy¿ lider Ci jej nie ustali³.");
		SaveMember(playerid,groupid);
	}
	else
		SendClientMessage(playerid, GetGroupColor(groupid), "Przepracowa³eœ wyznaczony czas w grupie. Nie otrzymujesz wyp³aty, gdy¿ osi¹gn¹³eœ dzienny limit.");
	return 1;
}
stock IsCriminalGroup(groupid)
{
	return (GroupInfo[groupid][gType] == GROUP_GANG || GroupInfo[groupid][gType] == GROUP_MAFIA || GroupInfo[groupid][gType] == GROUP_DRIVERS || GroupInfo[groupid][gType] == GROUP_SYNDICATE || GroupInfo[groupid][gType] == GROUP_CARTEL);
}
stock IsBusiness(groupid)
{
	return (GroupInfo[groupid][gType] >= 10 && GroupInfo[groupid][gType] != 20 && GroupInfo[groupid][gType] != 22);
}
public TakeItemFormPlayer(playerid,playerid2)
{
	new list[1024];
	ForeachEx(i,_ITEM_COUNT)
		if(ItemInfo[i][iUID])
			if(ItemInfo[i][iOwnerTyp] == OWNER_PLAYER && ItemInfo[i][iOwner] == CharacterInfo[playerid2][pUID])
				format(list, sizeof(list), "%s\n%3d: {878A87}%s", list, ItemInfo[i][iUID],ItemInfo[i][iName]);
	
	if(strlen(list) > 5) 
	{
		SetPVarInt(playerid, "TakenItemPlayer", playerid2);
		ShowPlayerDialog(playerid, D_OUT_ITEM, DIALOG_STYLE_LIST, DEF_NAME" » zabierz przedmiot", list, "Zabierz", "Anuluj");
	}
	else Tip(playerid,3,"Nic nie znalazles.");

	return 1;
}
public TakeMoneyFormPlayer(playerid,playerid2)
{
	if(!CharacterInfo[playerid2][pCash])
		return Tip(playerid,5,"Nic nie znalazles");
	
	new money=CharacterInfo[playerid2][pCash];
	GivePlayerCash(playerid,money);
	GivePlayerCash(playerid2, -money);
	new string[128];
	format(string,sizeof(string),"zabiera gotówkê znalezion¹ przy %s.",PlayerName2(playerid2));
	cmd_me(playerid,string);
	format(string,sizeof(string),"%s zabra³ Ci gotówkê - %d$",PlayerName2(playerid),money);

	log("%s[player:%d] zabiera %s[player:%d] %d$",PlayerName3(playerid),CharacterInfo[playerid][pUID],PlayerName3(playerid2),CharacterInfo[playerid2][pUID],money);
	return msg_info(playerid2, string);
}
stock GetOfferPrice(groupid,offer)
{
	new query[128],bool:found,price;
	if(offer==OFFER_REPAIR_ENG || offer==OFFER_REPAIR_BODY || offer==OFFER_REPAIR_TIRES || offer==OFFER_REPAIR_ALL || offer==OFFER_TAXI || offer==OFFER_GYM_SINGLE)
		format(query,sizeof(query),"SELECT `price1` FROM `srv_group_offer_prices` WHERE `groupid`='%d'",groupid);
	else if(offer==OFFER_PAINT || offer==OFFER_GYM_DAY)
		format(query,sizeof(query),"SELECT `price2` FROM `srv_group_offer_prices` WHERE `groupid`='%d'",groupid);
	else if(offer==OFFER_PAINTJOB || offer==OFFER_GYM_WEEK)
		format(query,sizeof(query),"SELECT `price3` FROM `srv_group_offer_prices` WHERE `groupid`='%d'",groupid);
	else if(offer==OFFER_TUNING)
		format(query,sizeof(query),"SELECT `price4` FROM `srv_group_offer_prices` WHERE `groupid`='%d'",groupid);
	else if(offer==OFFER_DISMOUNT)
		format(query,sizeof(query),"SELECT `price5` FROM `srv_group_offer_prices` WHERE `groupid`='%d'",groupid);
	else if(offer==OFFER_ADVERT)
		return SettingInfo[sLSNPrice];
	else if(offer==OFFER_MEDICINE)
		return SettingInfo[sHealPrice];
	else
		return -1;

	mysql_query(query);
	mysql_store_result();
	if(mysql_num_rows())
	{
		found=true;
		mysql_fetch_row_format(query);
		price=strval(query);
	}
	mysql_free_result();
	if(found)
		return price;

	return -1;
}
stock GetMemberCommission(playerid,groupid)
{
	new slot=GetPlayerGroupSlot(playerid,groupid);
	if(!slot) return 0;
	return MemberGroup[playerid][slot][GroupCommission]; 
}
stock LogJail(from,to,time,groupid,type)
{
	new query[256];
	
	format(query,sizeof(query),"INSERT INTO `srv_jail_logs` VALUES (NULL,'%d','%d', '%d','%d','%d','%d','%d', '%d')", CharacterInfo[to][pUID],CharacterInfo[to][pGID],CharacterInfo[from][pUID], CharacterInfo[from][pGID], groupid,time,type,gettime());
	mysql_query(query);
	return 1;
}