//------------------------------------
//
//		mySantos Role Play
//		by Grzes & Infinity
//		30.01.2016-12.04.2017
//
//------------------------------------

#pragma dynamic 15000

#include "a_samp.inc"

#include "includes/a_mysql.inc"
#include "includes/profiler.inc"

//#define DEBUG_MODE 1

#include "includes\YSI\y_bit.inc"
#include "includes/zcmd.inc"
#include "includes/sscanf2.inc"
#include "includes/progress.inc"
#include "includes/md5.inc"
#include "includes/streamer.inc"
#include "includes/mSelection.inc"
#include "includes/strlib.inc"
#include "includes/filemanager.inc"

#include "modules/define.inc"
#include "modules/new.inc"
#include "modules/config.inc"
#include "modules/core.inc"
#include "modules/load.inc"
#include "modules/login.inc"
#include "modules/dialogs.inc"
#include "modules/timers.inc"
#include "modules/objects.inc"
#include "modules/utilities.inc"
#include "modules/actors.inc"

#include "modules/vehicles.inc"
#include "modules/doors.inc"
#include "modules/groups.inc"
#include "modules/items.inc"

#include "modules/admins.inc"
#include "modules/players.inc"
#include "modules/gym.inc"
#include "modules/fire.inc"

#include "modules/cmd_g.inc"
#include "modules/cmd_p.inc"
#include "modules/cmd_a.inc"
#include "modules/cmd_obj.inc"

#include "modules/cmd_debug.inc"

main() 
{
	print("------------------------------------------");
	print("\t\tmySantos Role Play");
	print("------------------------------------------");
}

/*
new SERVER_DOWNLOAD[] = "https://ms-rp.pl/models";
public OnPlayerRequestDownload(playerid, type, crc)
{
	if(!IsPlayerConnected(playerid))
		return 0;
	
	new filename[64], filefound, final_url[256];
	if(type == DOWNLOAD_REQUEST_TEXTURE_FILE)
		filefound = FindTextureFileNameFromCRC(crc, filename, sizeof(filename));
	else if(type == DOWNLOAD_REQUEST_MODEL_FILE)
		filefound = FindModelFileNameFromCRC(crc, filename, sizeof(filename));
	
	if(filefound)
	{
		format(final_url, sizeof(final_url), "%s/%s", SERVER_DOWNLOAD, filename);
		RedirectDownload(playerid, final_url);
	}
	
	PlayerTextDrawShow(playerid, PlayerLoadingInfo[playerid]);
	
	return 1;
}
*/

public OnPlayerFinishedDownloading(playerid, virtualworld)
{
	if(!Logged[playerid] && IsPlayerConnected(playerid))
		SetTimerEx("PlayerLoginCheck", 10000, false, "i", playerid);
	
	PlayerTextDrawHide(playerid, PlayerLoadingInfo[playerid]);
	
	return 1;
}

public OnGameModeInit()
{
	
	
	if(mysql_connect(SQL_HOST, SQL_USER, SQL_DB, SQL_PASSWORD))
	{
		print("Po³¹czenie z baz¹ SQL poprawne.");
	
		// Charset, gamemode
		mysql_set_charset("utf-8");
		SetGameModeText("mySantos RolePlay v2.2");
		mysql_debug(1);

		// Ustawienia g³ówne
		ShowNameTags(0);
		ShowPlayerMarkers(0);
		AllowInteriorWeapons(0);
		EnableStuntBonusForAll(0);
		DisableInteriorEnterExits();
		ManualVehicleEngineAndLights();
		
		// Wyczyszczenie INGAME
		mysql_query("UPDATE `srv_characters` SET `logged` = '0'");
		mysql_query("UPDATE `srv_items` SET `used` = '0'");
		
		format(advreklama, sizeof(advreklama), "~y~~h~SANN ~w~~>~ Aktualnie nikt nie nadaje.");
		format(advnews, sizeof(advnews), "~y~~h~SANN ~w~~>~ Aktualnie nikt nie nadaje.");

		Streamer_VisibleItems(STREAMER_TYPE_OBJECT, 750);
		
		// Ustawienia
		LoadSettings();
		
		LoadSafeKeeps();
		LoadItems();
		LoadDoors();
		LoadGroups();
		LoadPlants();
		LoadCorpse();
		LoadObjects();
		LoadTexture();
		LoadMaterialText();
		LoadVehicles();
		LoadFuelStations();
		LoadAnimations();
		LoadCorners();
		LoadBusStops();
		Load3DTexts();
		LoadTextDraws();
		LoadDescriptions();
		LoadActors();
		LoadCustomSkins();
		
		ForeachEx(i, MAX_PLAYERS)
			NameTags[i] = Create3DTextLabel(" ", COLOR_USER, 0.0, 0.0, 0.2, 10.0, 0, 1);

		// Timery
		SetTimer("TimerSecond", 1000, true);
		SetTimer("TimerMinute", 60000, true);

		// Ustawienia serwera
		mysql_query("UPDATE `srv_settings` SET `status` = 1");

		//Wczytanie stref
		PICKUP_GOV_DOCS = CreateDynamicPickup(1581, 1,1482.4791,-1759.8009,33.5197, 2, 0); //pickup do strefy
		AREA_GOV_DOCS = CreateDynamicSphere(1482.4791,-1759.8009,33.5197, 1.5, 2,0);
		
		PICKUP_GOV_JOBS = CreateDynamicPickup(1210, 1,1462.4341,-1751.8960,33.5197, 2,0); //pickup do strefy
		AREA_GOV_JOBS = CreateDynamicSphere(1462.4341,-1751.8960,33.5197, 1.5, 2,0);
		
		// Ustawienie godziny serwera
		new godzina, minuta;
		gettime(godzina, minuta);
		SetWorldTime(godzina + 2);
		SERVER_TIME = godzina;
		SetWeather(10);
		SERVER_WEATHER = 10;
		maleskinlist = LoadModelSelectionMenu("maleskins.txt");
		femaleskinlist = LoadModelSelectionMenu("femaleskins.txt");
		doczepialne_0 = LoadModelSelectionMenu("doczepialne_0.txt");
		doczepialne_1 = LoadModelSelectionMenu("doczepialne_1.txt");
		doczepialne_2 = LoadModelSelectionMenu("doczepialne_2.txt");
		doczepialne_3 = LoadModelSelectionMenu("doczepialne_3.txt");
		doczepialne_4 = LoadModelSelectionMenu("doczepialne_4.txt");

		ON_AIR = 0;

		SERVER_LAST_RESTART = gettime();
		SERVER_LAST_TIMER_HOUR = gettime();
		
		if(!dir_exists("scriptfiles/logs"))
		{
			dir_create("scriptfiles/logs");
		}
		
		if(Profiler_GetState() == PROFILER_STARTED)
			Profiler_Stop();

	}
	else
		SetGameModeText("SQL ERROR");
	
	return 1;
}

public OnGameModeExit()
{
	mysql_query("UPDATE `srv_settings` SET `status` = '0'");
	mysql_query("UPDATE `srv_characters` SET `logged` = '0'");
	
	ForeachEx(i, MAX_PLANTS)
	{
		if(PlantInfo[i][plantUID])
		{
			new query[128];
			format(query, sizeof(query), "UPDATE `srv_plants` SET `time` = '%d' WHERE `UID` = '%d' LIMIT 1", PlantInfo[i][plantTime], i);
			mysql_query(query);
		}
	}
	
	ForeachEx(i,_VEH_COUNT)
		if(VehicleInfo[i][vUID] && VehicleInfo[i][vSpawned])
			SaveVehicle(i, SAVE_VEH_BASIC);
	
	mysql_close();
	print("[EXIT] Koñczê dzia³anie GM ...");
	
	return 1;
}

public OnPlayerConnect(playerid)
{
	ClearCache(playerid);
	
	SetPlayerColor(playerid, 0x000000FF);
	
	LoadTD(playerid);
	RemoveCustomObjects(playerid);
	
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	if(CharacterInfo[playerid][pUID])
	{
		new query[256];
		if(GetPVarType(playerid, "BoomboxObject"))
		{
			DestroyDynamicObject(GetPVarInt(playerid, "BoomboxObject"));
			if(GetPVarType(playerid, "bboxareaid"))
				ForeachPlayer(i)
					if(IsPlayerInDynamicArea(i, GetPVarInt(playerid, "bboxareaid"))&& !GetPlayerVehicleID(i) && !(CharacterInfo[i][pStatus] & STATUS_MP3) )
						StopAudioStreamForPlayer(i);
		}
		
		if(GetPVarInt(playerid,"pPackageID"))
		{
			format(query, sizeof(query), "UPDATE `srv_orders` SET `driver` = 0, `status` = 0 WHERE `uid` = '%d'", GetPVarInt(playerid, "pPackageID"));
			mysql_query(query);
		}
		else if(GetPVarInt(playerid,"TransportFuel"))
		{
			new uid = GetPVarInt(playerid,"TransportFuel");
			if(uid < 0)
				uid *= -1;
			format(query,sizeof(query),"UPDATE `srv_fuel_orders` SET `driver` = 0, `status`= 0 WHERE `uid` ='%d'",uid);
			mysql_query(query);
		}
		else if(GetPVarInt(playerid, "Transport"))
		{
			new guid = GetPVarInt(playerid, "TransportGroup");
			GroupInfo[guid][gTransportTowary]++;
		}
		
		if(GetPVarInt(playerid,"pTaxiDriver"))
		{
			new driver=GetPVarInt(playerid,"pTaxiDriver");
			if(driver==-1) driver=0;
			new price=floatround(float(CharacterInfo[driver][pTaxiDistance])*GetPVarFloat(playerid,"pTaxiPrice"));
			if(price>CharacterInfo[playerid][pCash]) price = CharacterInfo[playerid][pCash];
			
			GivePlayerCash(playerid,-price);
			
			new commission=GetMemberCommission(driver,DutyGroup[driver]);
			if(commission)
			{
				commission=floatround( (float(price)/100.0) * float(commission));
				price-=commission;
				CharacterInfo[driver][pCredit] += commission;
				SavePlayerStats(driver,SAVE_PLAYER_BASIC);
				format(query,sizeof(query),"Klient opuœci³ grê. Na konto grupy wp³ynê³o $%d.Twoja prowizja: $%d",price,commission);
			}
			else
				format(query,sizeof(query),"Klient opuœci³ grê. Na konto grupy wp³ynê³o $%d.",price);
			SendClientMessage(driver, GetGroupColor(DutyGroup[driver]), query);
			
			GiveGroupCash(DutyGroup[driver],price);
			
			DeletePVar(playerid, "pTaxiDriver");
			CharacterInfo[driver][pTaxiDistance]=0;
			CharacterInfo[driver][pTaxiPassenger]=INVALID_PLAYER_ID;
			DisablePlayerCheckpoint(driver);
			LogGroupOffer(driver,DutyGroup[driver],"Przejazd Taxi",price,playerid);
		}
		if(CharacterInfo[playerid][pTaxiPassenger] != INVALID_PLAYER_ID)
		{
			msg_info(CharacterInfo[playerid][pTaxiPassenger],"Kierowca opuœci³ grê. Przejazd anulowany.");
			DeletePVar(CharacterInfo[playerid][pTaxiPassenger],"pTaxiDriver");
			CharacterInfo[playerid][pTaxiDistance]=0;
			CharacterInfo[playerid][pTaxiPassenger]=INVALID_PLAYER_ID;
		}

		if(GetPVarInt(playerid, "PlayerObject3dText"))
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
		}

		if(GetPVarInt(playerid, "OfferUID"))
			DisableOffer(playerid, GetPVarInt(playerid,"OfferUID"));
		if(GetPVarInt(playerid, "OfferBuyer"))
		{
			new playerid2 = GetPVarInt(playerid,"OfferBuyer");
			DisableOffer(playerid2, GetPVarInt(playerid2,"OfferUID"));
		}
		if(GetPVarInt(playerid,"CarryCorpse"))
		{
			new uid = GetPVarInt(playerid, "CarryCorpse");
			RemovePlayerAttachedObject(playerid, 9);
			DeletePVar(playerid, "CarryCorpse");
			new Float:x, Float:y, Float:z, interior, vw;
			GetPlayerPos(playerid, x, y, z);
			vw=GetPlayerVirtualWorld(playerid);
			interior=GetPlayerInterior(playerid);
			CorpseInfo[uid][corpseX] = x;
			CorpseInfo[uid][corpseY] = y;
			CorpseInfo[uid][corpseZ] = z-1.0;
			CorpseInfo[uid][corpseInt] = interior;
			CorpseInfo[uid][corpseVW] = vw;
			CorpseInfo[uid][corpseObject] = CreateDynamicObject(19944, CorpseInfo[uid][corpseX], CorpseInfo[uid][corpseY], CorpseInfo[uid][corpseZ], 0, 0, 0, CorpseInfo[uid][corpseVW], CorpseInfo[uid][corpseInt], -1);
			
			format(query, sizeof(query), "Zw³oki {636363}(%d)",uid);
			CorpseInfo[uid][corpseText] = CreateDynamic3DTextLabel(query, COLOR_RED, CorpseInfo[uid][corpseX], CorpseInfo[uid][corpseY], CorpseInfo[uid][corpseZ]+0.75, 7.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,1, CorpseInfo[uid][corpseVW]);
			format(query, sizeof(query), "UPDATE `srv_corpse` SET `pos_x`='%f', `pos_y`='%f', `pos_z`='%f', `int`='%d', `vw`='%d' WHERE `uid`='%d'", x, y, CorpseInfo[uid][corpseZ], interior, vw, uid);
			mysql_query(query);
		}
		
		if(CharacterInfo[playerid][pGymType])
			OnPlayerGymTrainStopped(playerid);
		
		if(CharacterInfo[playerid][pWounded])
			CharacterInfo[playerid][pBW] = 10 * 60;
		
		SavePlayerStats(playerid, SAVE_PLAYER_BASIC);
		SavePlayerStats(playerid, SAVE_PLAYER_PENALTY);
		SavePlayerStats(playerid, SAVE_PLAYER_POS);
		SavePlayerStats(playerid, SAVE_PLAYER_OPTION);
		SavePlayerStats(playerid, SAVE_PLAYER_GLOBAL);
		SavePlayerStats(playerid, SAVE_LAST_DAMAGE);
		
		format(query,sizeof(query),"UPDATE `srv_characters` SET `last_online` = '%d', `logged` = '0' WHERE `player_uid` = '%d'", gettime(), CharacterInfo[playerid][pUID]);
		mysql_query(query);
		format(query,sizeof(query),"UPDATE `srv_items` SET `used` = 0 WHERE `owner` = '%d'", CharacterInfo[playerid][pUID]);
		mysql_query(query);
		
		ForeachEx(i, _ITEM_COUNT)
		{
			if(ItemInfo[i][iOwnerTyp] == OWNER_PLAYER && ItemInfo[i][iOwner] == CharacterInfo[playerid][pUID] && ItemInfo[i][iUsed] && ItemInfo[i][iType] == ITEM_TYPE_KAMIZELKA)
			{
				new value = floatround(CharacterInfo[playerid][pArmor]);
				ItemInfo[i][iValue1] = value;
			}
			if(ItemInfo[i][iOwnerTyp] == OWNER_PLAYER && ItemInfo[i][iOwner] == CharacterInfo[playerid][pUID] && ItemInfo[i][iUsed])
				ItemInfo[i][iUsed] = 0;
		}
		
		if(CharacterInfo[playerid][pHaveWeapon])
		    HidePlayerWeapons(playerid);
		if(CharacterInfo[playerid][pCornerTimer])
		{
			KillTimer(CharacterInfo[playerid][pCornerTimer]);
			CharacterInfo[playerid][pCornerTimer] = 0;
		}
		if(CharacterInfo[playerid][pRepairTime])
		{
			msg_info(GetPVarInt(playerid,"pRepairCustomer"),"Mechanik opuœci³ grê. Naprawa anulowana");
			CharacterInfo[playerid][pRepairTime]=-1;
			CharacterInfo[playerid][pRepairVeh]=-1;
		}
		if(DutyGroup[playerid])
			SaveMember(playerid,DutyGroup[playerid]);
		
		if(GetPVarInt(playerid,"pRepairMechanic"))
		{
			new mechanic = GetPVarInt(playerid,"pRepairMechanic");
			if(mechanic==-1) mechanic = 0;
			msg_info(mechanic,"Klient opusci³ grê. Naprawa anulowana");
			
			DeletePVar(mechanic,"pRepairJobPrice");					
			DeletePVar(mechanic,"pRepairCustomer");					
			DeletePVar(mechanic,"pRepairType");					
			DeletePVar(mechanic,"pRepairPrice");
			DeletePVar(playerid,"pRepairMechanic");	
			CharacterInfo[mechanic][pRepairTime]=0;
			CharacterInfo[mechanic][pRepairVeh]=0;
		}
		StopAudioStreamForPlayer(playerid);
		new hour,minute;
		gettime(hour,minute);
		format(query,sizeof(query),"[%02d:%02d] %s [UID: %d]",hour,minute,PlayerName3(playerid),CharacterInfo[playerid][pUID]);
		switch(reason)
		{
			case 0:
			{
				format(query,sizeof(query),"%s - crash", query);

				if(GetPlayerState(playerid)==PLAYER_STATE_DRIVER)
				{
					new uid=GetVehicleUID(GetPlayerVehicleID(playerid));
					if(VehicleInfo[uid][vEngine])
					{
						VehicleInfo[uid][vEngine] = false;
						ChangeVehicleEngineStatus(VehicleInfo[uid][vSAMPID], false);
					}
					if(!VehicleInfo[uid][vLocked] && !IsABike(GetPlayerVehicleID(playerid)))
					{
						VehicleInfo[uid][vLocked]=true;
						SetVehicleLock(VehicleInfo[uid][vSAMPID],true);
					}
				}
			}
			case 1:
				format(query,sizeof(query),"%s - /q", query);
			case 2:
				if(CharacterInfo[playerid][pTog] & TOG_QS)
					format(query, sizeof(query),"%s - /qs", query);
				else
					format(query ,sizeof(query),"%s - Kick/Ban", query);
		}
		if(!gmx && !quited[playerid])
		{
			new vw = GetPlayerVirtualWorld(playerid);
			new int = GetPlayerInterior(playerid);
			new Float:x,Float:y,Float:z;
			GetPlayerPos(playerid,x,y,z);
			quit[playerid] = CreateDynamic3DTextLabel(query, COLOR_RED, x, y, z, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, vw, int);
			SetTimerEx("Destroy3DText", 10000, 0, "i", playerid);
			quited[playerid] = 1;
		}
		
		ClearCache(playerid);
	}
	
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	if(Logged[playerid])
	{
		SetPlayerSpawn(playerid);
		//SendPlayerToSpawn(playerid);
		SpawnPlayer(playerid);
		return 1;
	}
	ForeachEx(i, 10) SendClientMessage(playerid, COLOR_WHITE, "");
	TogglePlayerSpectating(playerid, true);

	SetPlayerVirtualWorld(playerid, 255);
	
	if(strfind(PlayerName(playerid), "_") != -1)
	{
		new string[128];
		format(string,sizeof(string),"SELECT `player_uid` FROM `srv_characters` WHERE `nickname` LIKE BINARY '%s' LIMIT 1", PlayerName(playerid));
		mysql_query(string);
		mysql_store_result();

		if(mysql_num_rows())
			ShowPlayerDialog(playerid, D_LOGIN_GLOBAL, DIALOG_STYLE_PASSWORD, DEF_NAME" » logowanie", "Witaj na serwerze {02AD38}mySantos Role Play{A9C4E4}, zaloguj siê u¿ywaj¹c swojego has³a z forum:", "Zaloguj", "Zamknij");
		else
		{
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » logowanie", "Postaæ na któr¹ siê próbujesz zalogowaæ nie istnieje.\nPamiêtaj, ¿e nale¿y logowaæ siê nickiem postaci, np: John_Doe\n\nAby za³o¿yæ postaæ, skorzystaj z panelu gracza na forum.", "OK", "");
			KickWithWait(playerid);
		}
		
		mysql_free_result();
	}
	else
	{
		new string[128];
		format(string,sizeof(string),"SELECT `member_id` FROM `members` WHERE `members_display_name` LIKE '%s' LIMIT 1", PlayerName(playerid));
		mysql_query(string);
		mysql_store_result();
		
		if(mysql_num_rows())
		{
			mysql_fetch_row_format(string);
			SetPVarInt(playerid, "CharacterGlobalID", strval(string));
			ShowPlayerDialog(playerid, D_LOGIN_GLOBAL_2, DIALOG_STYLE_PASSWORD, DEF_NAME" » logowanie", "Witaj na serwerze {02AD38}mySantos Role Play{A9C4E4}, zaloguj siê u¿ywaj¹c swojego has³a z forum:", "Zaloguj", "Zamknij");
		}
		else
		{
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » logowanie", "Konto na które próbujesz siê zalogowaæ nie istnieje.\nPamiêtaj, ¿e przed wejœciem na serwer nale¿y stworzyæ konto na naszym forum.\n\nAby dodatkowo za³o¿yæ postaæ, skorzystaj z panelu gracza na forum.", "OK", "");
			KickWithWait(playerid);
		}
		
		mysql_free_result();
	}

	
	return 1;
}


public OnPlayerSpawn(playerid)
{
	if(CharacterInfo[playerid][pStatus] & STATUS_BUS)
		return 1;

	if(!Logged[playerid])
	{
		SendAdminMessageFormat(COLOR_RED,"%s(%d) próbowa³ omin¹æ logowanie.",PlayerName3(playerid),playerid);
		Kick(playerid);
		return 1;
	}

	
	SendPlayerToSpawn(playerid);
	
	if((!IsPlayerNPC(playerid) && CharacterInfo[playerid][pHours] == 0 && CharacterInfo[playerid][pMinutes] == 0 && !CharacterInfo[playerid][pAdmin]) || (random(4) == 2 && !CharacterInfo[playerid][pAdmin]))
	{
		if(!IsChecked[playerid])
		{
			IsChecked[playerid] = true;
			SetTimerEx("spawn_ac", 2000, false, "i", playerid);
		}
	}
	
	PreloadAllAnimLibs(playerid);
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_SPECTATING)
	{
		if(!CharacterInfo[playerid][pUID])
		{
			switch(random(9))
			{
				case 0:
				{
					SetPlayerCameraPos(playerid, 1406.56, -1623.63, 65.65);
					SetPlayerCameraLookAt(playerid, 1540.56, -1739.20, 13.55);
				}
				case 1:
				{
					SetPlayerCameraPos(playerid, 241.82, -1812.65, 32.68);
					SetPlayerCameraLookAt(playerid, 368.10, -1922.10, 7.67);
				}
				case 2:
				{
					SetPlayerCameraPos(playerid, 505.50, -1125.44, 125.26);
					SetPlayerCameraLookAt(playerid, 949.52, -1052.11, 37.81);
				}
				case 3:
				{
					SetPlayerCameraPos(playerid, 2307.85, -1261.00, 160.03);
					SetPlayerCameraLookAt(playerid, 2184.54, -1419.79, 30.29);
				}
				case 4:
				{
					SetPlayerCameraPos(playerid, 2886.18, -1967.95, 106.29);
					SetPlayerCameraLookAt(playerid, 2743.05, -1707.38, 40.05);
				}
				case 5:
				{
					SetPlayerCameraPos(playerid, 2886.18, -1967.95, 106.29);
					SetPlayerCameraLookAt(playerid, 2743.05, -1707.38, 40.05);
				}
				case 6:
				{
					SetPlayerCameraPos(playerid, 1443.39, -1579.57, 62.23);
					SetPlayerCameraLookAt(playerid, 1367.70, -1671.67, 16.73);
				}
				case 7:
				{
					SetPlayerCameraPos(playerid, 1370.95, -2371.93, 49.94);
					SetPlayerCameraLookAt(playerid, 1532.01, -2298.24, 21.75);
				}
				case 8:
				{
					SetPlayerCameraPos(playerid, 2188.75, -1391.24, 92.48);
					SetPlayerCameraLookAt(playerid, 2325.86, -1299.98, 28.35);
				}
			}
		} else if(Logged[playerid] && !CharacterInfo[playerid][pAdmin] && !GetPVarInt(playerid, "pBus"))
			SendAdminMessageFormat(COLOR_RED, "Testowe wykrywanie GHOST. ID: %d, nick: %s", playerid, PlayerName(playerid));
	}
	else if(oldstate == PLAYER_STATE_DRIVER && newstate == PLAYER_STATE_ONFOOT)
	{
		for(new x = 0; x < 10; x++)
			PlayerTextDrawHide(playerid, Speedometer[playerid][x]);
		
		ForeachPlayer(i)
			if(CharacterInfo[i][pSpec] && GetPVarInt(i, "SpecPlayerID")==playerid)
				PlayerSpectatePlayer(i,playerid);
		
		//to ni¿ej wyjebaæ
		if(GetPVarInt(playerid,"pTaxiDriver"))
		{
			new driver=GetPVarInt(playerid,"pTaxiDriver");
			if(driver==-1) driver=0;
			new price=floatround(float(CharacterInfo[driver][pTaxiDistance])*GetPVarFloat(driver,"pTaxiPrice"));
			if(price>CharacterInfo[playerid][pCash]) price = CharacterInfo[playerid][pCash];

			new string[128];
			format(string,sizeof(string),"Przejazd zakonczony. Zap³aci³eœ $%d.",price);
			msg_info(playerid,string);
			GivePlayerCash(playerid,-price);

			new commission=GetMemberCommission(driver,DutyGroup[driver]);
			if(commission)
			{
				commission=floatround( (float(price)/100.0) * float(commission));
				price-=commission;
				CharacterInfo[driver][pCredit] += commission;
				SavePlayerStats(driver,SAVE_PLAYER_BASIC);
				format(string,sizeof(string),"Klient opuœci³ pojazd. Na konto grupy wp³ynê³o $%d.Twoja prowizja: $%d",price,commission);
			}
			else
				format(string,sizeof(string),"Klient opuœci³ pojazd. Na konto grupy wp³ynê³o $%d.",price);
			SendClientMessage(driver, GetGroupColor(DutyGroup[driver]), string);
			
			GiveGroupCash(DutyGroup[driver],price);
			
			DeletePVar(playerid, "pTaxiDriver");
			CharacterInfo[driver][pTaxiDistance]=0;
			CharacterInfo[driver][pTaxiPassenger]=INVALID_PLAYER_ID;
			LogGroupOffer(driver,DutyGroup[driver],"Przejazd Taxi",price,playerid);
			DisablePlayerCheckpoint(driver);
		}
		
		if(CharacterInfo[playerid][pCurrentDescription] != 0 && Description[playerid] == Text3D:INVALID_3DTEXT_ID)
			Description[playerid] = CreateDynamic3DTextLabel(WordWrap(CharacterInfo[playerid][pCurrentDescription], 5), COLOR_VEH_DESC, 0.0, 0.0, -0.6, 7.0, playerid, -1, 1);
	}
	else if(oldstate == PLAYER_STATE_PASSENGER && newstate == PLAYER_STATE_ONFOOT)
	{
		ForeachPlayer(i)
			if(CharacterInfo[i][pSpec] && GetPVarInt(i, "SpecPlayerID")==playerid)
				PlayerSpectatePlayer(i,playerid);
		if(GetPVarInt(playerid,"pTaxiDriver"))
		{
			new driver=GetPVarInt(playerid,"pTaxiDriver");
			if(driver==-1) driver=0;
			new price=floatround(float(CharacterInfo[driver][pTaxiDistance])*GetPVarFloat(driver,"pTaxiPrice"));
			if(price>CharacterInfo[playerid][pCash]) price = CharacterInfo[playerid][pCash];

			new string[128];
			format(string,sizeof(string),"Przejazd zakonczony. Zap³aci³eœ $%d.",price);
			msg_info(playerid,string);
			GivePlayerCash(playerid,-price);

			new commission=GetMemberCommission(driver,DutyGroup[driver]);
			if(commission)
			{
				commission=floatround( (float(price)/100.0) * float(commission));
				price-=commission;
				CharacterInfo[driver][pCredit] += commission;
				SavePlayerStats(driver,SAVE_PLAYER_BASIC);
				format(string,sizeof(string),"Klient opuœci³ pojazd. Na konto grupy wp³ynê³o $%d.Twoja prowizja: $%d",price,commission);
			}
			else
				format(string,sizeof(string),"Klient opuœci³ pojazd. Na konto grupy wp³ynê³o $%d.",price);
			SendClientMessage(driver, GetGroupColor(DutyGroup[driver]), string);
			
			GiveGroupCash(DutyGroup[driver],price);
			
			DeletePVar(playerid, "pTaxiDriver");
			CharacterInfo[driver][pTaxiDistance]=0;
			CharacterInfo[driver][pTaxiPassenger]=INVALID_PLAYER_ID;
			LogGroupOffer(driver,DutyGroup[driver],"Przejazd Taxi",price,playerid);
			DisablePlayerCheckpoint(driver);
		}
		
		if(CharacterInfo[playerid][pCurrentDescription] != 0 && Description[playerid] == Text3D:INVALID_3DTEXT_ID)
			Description[playerid] = CreateDynamic3DTextLabel(WordWrap(CharacterInfo[playerid][pCurrentDescription], 5), COLOR_VEH_DESC, 0.0, 0.0, -0.6, 7.0, playerid, -1, 1);
	}
	else if(newstate == PLAYER_STATE_DRIVER)
	{
		new model = GetVehicleModel(GetPlayerVehicleID(playerid));
		new vehid=GetVehicleUID(GetPlayerVehicleID(playerid));
		if(!vehid)
			return 1;
		if(model == 509 || model == 510 || model == 481) return 1;
		if(!(CharacterInfo[playerid][pTog] & TOG_SPEEDOMETER))
			SetTimerEx("SpeedMeterUP", 100, false, "i", playerid);
		Tip(playerid,5,"Aby uruchomic silnik uzyj ~g~~k~~CONVERSATION_YES~~w~. Do obslugi swiatel uzyj ~g~~k~~VEHICLE_FIREWEAPON_ALT~");
		ForeachPlayer(i)
			if(CharacterInfo[i][pSpec] && GetPVarInt(i, "SpecPlayerID")==playerid)
				PlayerSpectateVehicle(i,GetPlayerVehicleID(playerid));
		if(!(CharacterInfo[playerid][pStatus] & STATUS_MP3))
			StopAudioStreamForPlayer(playerid);
		if(VehicleInfo[vehid][vRadio] && !(CharacterInfo[playerid][pStatus] & STATUS_MP3) && !IsABike(GetPlayerVehicleID(playerid)))
			PlayAudioStreamForPlayer(playerid,LoadVehRadio(vehid));
		if(VehicleInfo[vehid][vLocked] && !VehicleInfo[vehid][vRecentlyLocked] && !CharacterInfo[playerid][pAdmin])
		{
			GivePenalty(playerid, -1, gettime(), PENALTY_KICK, 0, "Nieautoryzowane wejscie do pojazdu");
			KickWithWait(playerid);
		}
		
		if(CharacterInfo[playerid][pCurrentDescription] != 0 && Description[playerid] != Text3D:INVALID_3DTEXT_ID)
		{
			DestroyDynamic3DTextLabel(Description[playerid]);
			Description[playerid] = Text3D:INVALID_3DTEXT_ID;
		}
		
		if(CharacterInfo[playerid][pTog] & TOG_STATUS)
		{
			PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][3]);

			PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][4]);
			PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][5]);
		}
	}
	else if(newstate == PLAYER_STATE_PASSENGER)
	{
		new vehid=GetVehicleUID(GetPlayerVehicleID(playerid));
		if(!(CharacterInfo[playerid][pStatus] & STATUS_MP3))
			StopAudioStreamForPlayer(playerid);
		if(VehicleInfo[vehid][vRadio] && !(CharacterInfo[playerid][pStatus] & STATUS_MP3) && !IsABike(GetPlayerVehicleID(playerid)))
		{
			StopAudioStreamForPlayer(playerid);
			PlayAudioStreamForPlayer(playerid,LoadVehRadio(vehid));
		}
		ForeachPlayer(i)
			if(CharacterInfo[i][pSpec] && GetPVarInt(i, "SpecPlayerID")==playerid)
				PlayerSpectateVehicle(i,GetPlayerVehicleID(playerid));

		if(VehicleInfo[vehid][vLocked] && !VehicleInfo[vehid][vRecentlyLocked] && !CharacterInfo[playerid][pAdmin])
		{
			GivePenalty(playerid, -1, gettime(), PENALTY_KICK, 0, "Nieautoryzowane wejscie do pojazdu");
			KickWithWait(playerid);
		}
		
		if(CharacterInfo[playerid][pCurrentDescription] != 0 && Description[playerid] != Text3D:INVALID_3DTEXT_ID)
		{
			DestroyDynamic3DTextLabel(Description[playerid]);
			Description[playerid] = Text3D:INVALID_3DTEXT_ID;
		}
		
		if(CharacterInfo[playerid][pTog] & TOG_STATUS)
		{
			PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][3]);

			PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][4]);
			PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][5]);
		}
	}
	else if(oldstate == PLAYER_STATE_SPECTATING)
	{
		if(CharacterInfo[playerid][pSpec])
		{
			CharacterInfo[playerid][pSpec] = false;
			DeletePVar(playerid,"SpecPlayerID");
			ReattachObjectsToPlayer(playerid);
			
			if(!(CharacterInfo[playerid][pTog] & TOG_GLOD))
			{
				ShowPlayerProgressBar(playerid, FoodBar[playerid]);
				SetPlayerProgressBarValue(playerid, FoodBar[playerid], CharacterInfo[playerid][pGlod]);
				UpdatePlayerProgressBar(playerid, FoodBar[playerid]);
			}
		}
		else if(CharacterInfo[playerid][pStatus] & STATUS_BUS)
			ReattachObjectsToPlayer(playerid);
	}
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	if(IsPlayerPremium(playerid))
	{
		new string[256];
		if((!CharacterInfo[clickedplayerid][pMask] && !CharacterInfo[clickedplayerid][pHide]) || CharacterInfo[playerid][pAdmin])
		{
			format(string, sizeof(string), "ID: %d\nUID: %d\nImiê Nazwisko: %s\nNick na forum: %s", clickedplayerid, CharacterInfo[clickedplayerid][pUID], PlayerName3(clickedplayerid), CharacterInfo[clickedplayerid][pGlobalNick]);
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, DEF_NAME" » wybrana postaæ:", string, "Zamknij", "");
		}
		else
			msg_error(playerid, "Wybrana postaæ jest ukryta lub u¿ywa aktualnie maski.");
	}
	else
		msg_info(playerid, "Informacje o graczu dostêpne wy³¹cznie dla konta premium!");
	
	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
	return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
	return 1;
}

public OnPlayerText(playerid, text[])
{
	if(!CharacterInfo[playerid][pUID]) return 0;
	if(GetTickCount() - CharacterInfo[playerid][pLastMsg] < 1000)
	{
		CharacterInfo[playerid][pAntiFloodWarn]++;
		if(CharacterInfo[playerid][pAntiFloodWarn] == 3)
			SendClientMessage(playerid, COLOR_RED, "Wysy³asz zbyt du¿o wiadomoœæi. Je¿eli nie zwolnisz zostaniesz wyrzucony.");
		else if(CharacterInfo[playerid][pAntiFloodWarn] == 6)
		{
			GivePenalty(playerid, -1, gettime(), PENALTY_KICK, 0, "Spam/Flood");
			KickWithWait(playerid);
			return 0;
		}
	}
	
	if(CharacterInfo[playerid][pAFKWarn])
		CharacterInfo[playerid][pAFKWarn] = 0;
	
	CharacterInfo[playerid][pLastMsg] = GetTickCount();
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
	{
		msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
		return 0;
	}
	if(text[0] == '@')
	{
		if(!CanMove(playerid) && !CanSpeak(playerid))
		{
			msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
			return 0;
		}
		if(strlen(text)<4)
		{
			msg_usage(playerid, "U¿yj: @{1-5} [tekst]");
			return 0;
		}
		new ids[2];
		strmid(ids, text, 1, 2);
		new id=strval(ids);

		if(id<1||id>5)
		{
			msg_error(playerid,"Wprowadzono nieprawid³owy slot grupy.");
			return 0;
		}
		if(!MemberGroup[playerid][id][GroupID])
		{
			msg_error(playerid,"Nie posiadasz grupy na danym slocie.");
			return 0;
		}
		if(CharacterInfo[playerid][pBlockNoOOC])
		{
			msg_error(playerid,"Posiadasz aktywn¹ blokadê czatów OOC.");
			return 0;
		}
		if(GroupInfo[MemberGroup[playerid][id][GroupID]][gOOCBlock])
		{
			msg_error(playerid, "Czat OOC grupy jest wy³¹czony.");
			return 0;
		}
		new str[128];
		new str2[128];
		new groupid = MemberGroup[playerid][id][GroupID];
		new bool:tmp, text2[128];
		strmid(str, text, 3, 128);
		if(strlen(str) >= 64)
		{
			tmp=true;
			new pos = strfind(str, " ", true, strlen(str) / 2);
			if(pos != -1)
			{
				strmid(text2, str, pos + 1, strlen(str));
				strdel(str, pos, strlen(str));
			}
		}
		
		if(tmp)
			format(text2, sizeof(text2), "... %s ))", text2);
		
		ForeachPlayer(i)
		{
			for(new x = 1; x<MAX_PLAYER_GROUPS; x++)
			{
				if(MemberGroup[i][x][GroupID] == groupid && !(CharacterInfo[i][pTog] & TOG_CHATOOC))
				{
					if(!tmp)
					{
						format(str2, sizeof(str2), "(( [%s][%d] %s(%d): %s ))", GroupInfo[groupid][gTag], x, PlayerName2(playerid), playerid, str);
						playerLog(i,"GOOC",str2);
						SendClientMessage(i, GetGroupColor(MemberGroup[playerid][id][GroupID]), str2);
					}
					else
					{
						format(str2, sizeof(str2), "(( [%s][%d] %s(%d): %s ..", GroupInfo[groupid][gTag], x, PlayerName2(playerid), playerid, str);
						SendClientMessage(i, GetGroupColor(MemberGroup[playerid][id][GroupID]), str2);
						SendClientMessage(i, GetGroupColor(MemberGroup[playerid][id][GroupID]), text2);
						playerLog(i,"GOOC",str2);
						playerLog(i,"GOOC",text2);
					}
					break;
				}
			}
		}
		
		return 0;
	}
	
	if( text[0] == '.' )
	{
		if(CharacterInfo[playerid][pWounded] || CharacterInfo[playerid][pBW] || (IsPlayerInAnyVehicle(playerid) && strcmp(text, ".lokiec", true)))
		{
			msg_error(playerid, "Nie mo¿esz aktualnie u¿yæ tej animacji.");
			return 0;
		}
		if(!text[1])
			return 0;
		new bool:found = false;
		ForeachEx(anim_id, MAX_ANIMS)
		{
			if(!isnull(AnimInfo[anim_id][aCommand]))
			{
				if(!strcmp(text[1], AnimInfo[anim_id][aCommand], true))
				{
					if(AnimInfo[anim_id][aAction] != 2)
						ApplyAnimation(playerid, AnimInfo[anim_id][aLib], AnimInfo[anim_id][aName], AnimInfo[anim_id][aSpeed], AnimInfo[anim_id][aOpt1], AnimInfo[anim_id][aOpt2], AnimInfo[anim_id][aOpt3], AnimInfo[anim_id][aOpt4], AnimInfo[anim_id][aOpt5], 1);
					else
						SetPlayerSpecialAction(playerid, AnimInfo[anim_id][aOpt1]);

					Tip(playerid, 5, "Aby przerwac animacje uzyj ~g~PPM~w~.");
					if(!(CharacterInfo[playerid][pStatus] & STATUS_PLAY_ANIM))
						CharacterInfo[playerid][pStatus] += STATUS_PLAY_ANIM;
					
					found = true;
				}
			}
		}
		
		if(!found) PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		
		return 0;
	}
	
	if(!CanSpeak(playerid))
	{
		msg_error(playerid, "Nie mo¿esz mówiæ w obecnym stanie (knebel, AJ, BW).");
		return 0;
	}
	
	if(Rozmawia[playerid])
	{
		if(CharacterInfo[playerid][pBW] || CharacterInfo[playerid][pWounded])
		{
			msg_error(playerid,"Nie mo¿esz aktualnie rozmawiaæ.");
			return 0;
		}
		new playerid2 = RozmawiaZ[playerid];
		new str[170];

		SendClientMessageFormat(playerid2, COLOR_ORANGE, "[%d](%s): %s", ItemInfo[CharacterInfo[playerid][pPhone]][iValue1], GetSexName(CharacterInfo[playerid][pSex]), text);

		format(str, sizeof(str), "%s (telefon): %s", PlayerName2(playerid), text);
		SendWrappedMessageToPlayerRange(playerid, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, str, 10);
		return 0;
	}
	
	if(!strcmp(text, ":)", true) || !strcmp(text, " :)", true) || !strcmp(text, ":) ", true) || !strcmp(text, ":)", true))
	{
		cmd_me(playerid, "uœmiecha siê.");
		return 0;
	}
	else if(!strcmp(text, ":(", true) || !strcmp(text, " :(", true) || !strcmp(text, ":( ", true) || !strcmp(text, ";(", true) || !strcmp(text, ";0", true))
	{
		cmd_me(playerid, "robi smutn¹ minê.");
		return 0;
	}
	else if(!strcmp(text, ":D", true) || !strcmp(text, " :D", true) || !strcmp(text, ":D ", true) || !strcmp(text, ";D", true))
	{
		if(!(CharacterInfo[playerid][pTog] & TOG_SMIECH))
			ApplyAnimation(playerid, "RAPPING", "Laugh_01", 4.1, 0, 0, 0, 0, 0, 1);
		
		cmd_me(playerid, "œmieje siê.");
		return 0;
	}
	else if(!strcmp(text, ":P", true) || !strcmp(text, " :P", true) || !strcmp(text, ":P ", true) || !strcmp(text, ";P", true))
	{
		cmd_me(playerid, "wystawia jêzyk.");
		return 0;
	}
	else if(!strcmp(text, ":/", true) || !strcmp(text, " :/", true) || !strcmp(text, ":/ ", true) || !strcmp(text, ";/", true))
	{
		cmd_me(playerid, "krzywi siê.");
		return 0;
	}
	else if(!strcmp(text, ":o", true) || !strcmp(text, " :o", true) || !strcmp(text, ":o ", true) || !strcmp(text, ";o", true))
	{
		cmd_me(playerid, "robi zdziwion¹ minê.");
		return 0;
	}
	else if(!strcmp(text, ";)", true) || !strcmp(text, " ;)", true) || !strcmp(text, ";) ", true) || !strcmp(text, ";)", true))
	{
		cmd_me(playerid, "puszcza oczko.");
		return 0;
	}
	else if(!strcmp(text, ":*", true) || !strcmp(text, " :*", true) || !strcmp(text, ":* ", true) || !strcmp(text, ":*", true))
	{
		cmd_me(playerid, "daje buziaka.");
		return 0;
	}
	else if(!strcmp(text, "xd", true))
	{
		if(!(CharacterInfo[playerid][pTog] & TOG_SMIECH))
			ApplyAnimation(playerid, "RAPPING", "Laugh_01", 4.1, 0, 0, 0, 0, 0, 1);
		
		cmd_me(playerid, "wybucha œmiechem.");
		return 0;
	}

	text[0] = toupper(text[0]);	
	new str[170];
	if(CharacterInfo[playerid][pAdminDuty])
	{
		new name[64];

		switch(CharacterInfo[playerid][pAdmin])
		{
			case 1:
				format(name, sizeof(name), "{E6E6E6}%s ({FF9900}Opiekun{E6E6E6})", CharacterInfo[playerid][pGlobalNick]);
			case 2,3,4:
				format(name, sizeof(name), "{E6E6E6}%s ({8B00B0}GameMaster{E6E6E6})", CharacterInfo[playerid][pGlobalNick]);
			case 5,6:
				format(name, sizeof(name), "{E6E6E6}%s ({B00000}Administrator{E6E6E6})", CharacterInfo[playerid][pGlobalNick]);
		}

		format(str, sizeof(str), "%s: %s", name, text);
		SendWrappedMessageToPlayerRange(playerid, COLOR_FADE1, COLOR_FADE1, COLOR_FADE1, COLOR_FADE1, COLOR_FADE1, str, 10);
	}
	else
	{
		if(!(CharacterInfo[playerid][pTog] & TOG_SAY))
			ApplyAnimation(playerid, "PED", "IDLE_chat", 1.0, 0, 0, 0, 0, 0);
		
		new lpos, rpos;
		lpos = strfind(text, "<");
		rpos = strfind(text, ">");
		if(lpos >= 0 && rpos > 0 && rpos > lpos +2)
		{
			new string[196];
			format(string ,sizeof(string),"%s",str_replace("<","{C2A2DD}*",text));
			format(string ,sizeof(string),"%s",str_replace(">","*{FFFFFF}",string));
			format(str, sizeof(str), "%s mówi: %s", PlayerName2(playerid), string);
			SendWrappedMessageToPlayerRange(playerid, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, str, 10);
		}
		else 
		{
			format(str, sizeof(str), "%s mówi: %s", PlayerName2(playerid), text);
			SendWrappedMessageToPlayerRange(playerid, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, str, 10);
		}
	}

	return 0;
}

public OnPlayerCommandPerformed(playerid, cmdtext[], success)
{
	if(!CharacterInfo[playerid][pUID]) return 1;
	if(!success) return PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
	return 1;
}

public OnPlayerCommandReceived(playerid, cmdtext[])
{
	if(!CharacterInfo[playerid][pUID])
		return 0;
	
	return 1;
}

public OnRconLoginAttempt(ip[], password[], success)
{
	SendAdminMessageFormat(COLOR_RED, "Nast¹pi³a próba logowania do RCON. IP: %d, has³o: %s, sukces: %d", ip, password, success);
	return 1;
}

public OnRconCommand(cmd[])
{
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	if(killerid != INVALID_PLAYER_ID)
	{
		if(IsPlayerInAnyVehicle(killerid) && reason == 24 && !CharacterInfo[killerid][pPenalty])
		{
			SendClientMessage(playerid, COLOR_RED, "Zosta³eœ zabity przez DB z DE. Zg³oœ to administracji (skarga na forum). Twoja postaæ otrzyma UNBW.");
			SendClientMessageFormat(playerid, COLOR_RED, "Postaæ, która ciê zabi³a: %s (%d).", PlayerName3(killerid), killerid);

			CharacterInfo[playerid][pReanimation] = 7;
			CharacterInfo[playerid][pReanimationID] = playerid;
		}
		else if(CharacterInfo[killerid][pHaveWeapon] && reason != CharacterInfo[killerid][pWeaponID] && CharacterInfo[playerid][pDamaged])
		{
		    SendClientMessage(playerid, COLOR_RED, "Wykryto mo¿liwe u¿ycie cheatów, twoja postaæ otrzyma UNBW. Zapisano w logach, mo¿esz napisaæ ew. skargê.");

			CharacterInfo[playerid][pReanimation] = 7;
			CharacterInfo[playerid][pReanimationID] = playerid;
		}
		
		if(!CharacterInfo[playerid][pDamaged])
			SendAdminMessageFormat(COLOR_RED, "[AC] Wykryto mo¿liwe u¿ycie FAKEKILL, osoba podejrzana: %s (%d).", PlayerName3(playerid), playerid);
		else
			CharacterInfo[playerid][pDamaged] = false;
	}

	if(CharacterInfo[playerid][pBW])
	{
		msg_error(playerid,"Posiadasz ju¿ stan nieprzytomnoœci dlatego nie otrzymasz ponownego BW.");
		SetPlayerHP(playerid, 20);
		return 1;
	}
	else if(CharacterInfo[playerid][pWounded])
	{
		
		if(IsPlayerInAnyVehicle(playerid))
			RemovePlayerFromVehicle(playerid);
		
		GetPlayerPos(playerid, CharacterInfo[playerid][pPos][0], CharacterInfo[playerid][pPos][1], CharacterInfo[playerid][pPos][2]);
	
		CharacterInfo[playerid][pInt] = GetPlayerInterior(playerid);
		CharacterInfo[playerid][pVW] = GetPlayerVirtualWorld(playerid);
		
		SetPlayerHP(playerid, 20);
		SavePlayerStats(playerid, SAVE_PLAYER_POS);
		
		SetPlayerCameraPos(playerid, CharacterInfo[playerid][pPos][0] + 1, CharacterInfo[playerid][pPos][1] + 2, CharacterInfo[playerid][pPos][2] + 3);
		SetPlayerCameraLookAt(playerid, CharacterInfo[playerid][pPos][0], CharacterInfo[playerid][pPos][1], CharacterInfo[playerid][pPos][2]);
		
		TogglePlayerControllable(playerid, 0);
		
		if(reason < 22)
		{		
			CharacterInfo[playerid][pBW] = 5 * 60;
			msg_info(playerid,"Zosta³eœ pobity do nieprzytomnoœci. Twój aktualny stan nie pozwala na poruszanie siê.\nMusisz przeczekaæ stan nieprzytomnoœci, a¿ siê ockniesz lub zostaniesz uratowany.");
		}
		else
		{	
			CharacterInfo[playerid][pBW] = 5 * 60;
			msg_info(playerid,"Zosta³eœ postrzelony z broni. Twój aktualny stan nie pozwala na poruszanie siê.\nMusisz przeczekaæ stan nieprzytomnoœci, a¿ siê ockniesz lub zostaniesz uratowany.");
		}
		
		if(GetPVarInt(playerid, "KillerWeaponID") >= 0)
		{
			new gunname[32];
			new weapon_val;
			
			if(GetPVarInt(playerid, "KillerWeaponID") == 0)
			{
				format(gunname, sizeof(gunname), "Piêœci");
				weapon_val = CharacterInfo[killerid][pUID];
			}
			else
			{
				GetWeaponName(GetPVarInt(playerid, "KillerWeaponID"), gunname, sizeof(gunname));
				weapon_val=CharacterInfo[GetPVarInt(playerid, "KillerID")][pWeaponUID];
			}
			
			DeletePVar(playerid, "KillerWeaponID");
			DeletePVar(playerid, "KillerID");
			
			SendAdminMessageFormat(COLOR_RED, "[AI] %s (ID: %d) zosta³ zabity (BW W£AŒCIWE) przez %s (ID: %d) (Broñ: %s).", PlayerName3(playerid), playerid, PlayerName3(GetPVarInt(playerid, "KillerID")), GetPVarInt(playerid, "KillerID"), gunname);
			log("%s[player:%d] zabity (BW W£AŒCIWE) przez %s[player:%d] typ:%d bron:[itemid:%d]",PlayerName3(playerid),CharacterInfo[playerid][pUID],PlayerName3(GetPVarInt(playerid, "KillerID")),CharacterInfo[GetPVarInt(playerid, "KillerID")][pUID],GetPVarInt(playerid, "KillerWeaponID"),CharacterInfo[GetPVarInt(playerid, "KillerID")][pWeaponUID]);
		
			SetPVarString(playerid, "KillWeapon", gunname);
			SetPVarInt(playerid, "KillWeaponVal", weapon_val);
		}
		else
		{
			SendAdminMessageFormat(COLOR_RED, "[AI] %s (ID: %d) zosta³ zabity (BW W£AŒCIWE).", PlayerName3(playerid), playerid);
			log("%s[player:%d] zabity (BW W£AŒCIWE) ale chuj wie przez kogo.", PlayerName3(playerid), CharacterInfo[playerid][pUID]);
		}
		
		CharacterInfo[playerid][pWounded] = 0;
		CharacterInfo[playerid][pDeathTimer] = 5;
		
		return 1;
	}
	
	if(CharacterInfo[playerid][pStatus] & STATUS_MP3)
		CharacterInfo[playerid][pStatus]-=STATUS_MP3;
	
	StopAudioStreamForPlayer(playerid);

	for(new i=0;i<10;i++)
		CharacterInfo[playerid][pAttached][i]=0;
	
	for(new x = 0; x < 10; x++)
		PlayerTextDrawHide(playerid, Speedometer[playerid][x]);
	
	CharacterInfo[playerid][pAnimacja] = 0;
	
	if(GetPVarInt(playerid,"OfferUID"))
		DisableOffer(playerid,GetPVarInt(playerid,"OfferUID"));
	
	if(GetPVarInt(playerid,"OfferBuyer"))
	{
		new playerid2=GetPVarInt(playerid,"OfferBuyer");
		DisableOffer(playerid2,GetPVarInt(playerid2,"OfferUID"));
	}
	
	new query[128];
	format(query, sizeof(query), "UPDATE `srv_items` SET `used` = 0 WHERE `owner` = '%d'", CharacterInfo[playerid][pUID]);
	mysql_query(query);
	
	ForeachEx(i,_ITEM_COUNT)
	{
		if(ItemInfo[i][iOwnerTyp] == OWNER_PLAYER && ItemInfo[i][iOwner] == CharacterInfo[playerid][pUID])
		{
			if(CharacterInfo[playerid][pMask] && ItemInfo[i][iType] == ITEM_TYPE_MASKA && ItemInfo[i][iUsed])
			{
				new index;
				format(query, sizeof(query), "SELECT `ind` FROM `srv_attached` WHERE `UID`='%d'", ItemInfo[i][iUID]);
				mysql_query(query);
				mysql_store_result();
				if(mysql_num_rows())
				{
					mysql_fetch_row_format(query);
					index=strval(query);
					RemovePlayerAttachedObject(playerid, index);
					CharacterInfo[playerid][pAttached][index] = 0;
				}
				CharacterInfo[playerid][pMask] = false;
				SetPlayerName(playerid, LoadPlayerName(CharacterInfo[playerid][pUID], true));
			}
			else if(CharacterInfo[playerid][pHaveArmor] && ItemInfo[i][iType] == ITEM_TYPE_KAMIZELKA && ItemInfo[i][iUsed] && reason > 18 && reason < 35)
			{
				ItemInfo[i][iValue1] = 0;
				format(query, sizeof(query), "UPDATE `srv_items` SET `value1` = '%d' WHERE `UID` = '%d' LIMIT 1", ItemInfo[i][iValue1], i);
				mysql_query(query);
			}
			
			if(ItemInfo[i][iUsed])
				ItemInfo[i][iUsed] = 0;
		}
	}

	if(CharacterInfo[playerid][pHaveWeapon])
		HidePlayerWeapons(playerid);
	
	if(CharacterInfo[playerid][pHaveArmor])
		CharacterInfo[playerid][pHaveArmor] = false;
	
	if(IsPlayerInAnyVehicle(playerid))
		RemovePlayerFromVehicle(playerid);
	
	new weapon_val;
	new gun[32];
	
	GetPlayerPos(playerid, CharacterInfo[playerid][pPos][0], CharacterInfo[playerid][pPos][1], CharacterInfo[playerid][pPos][2]);
	
	CharacterInfo[playerid][pInt] = GetPlayerInterior(playerid);
	CharacterInfo[playerid][pVW] = GetPlayerVirtualWorld(playerid);
	
	SetPlayerCameraPos(playerid, CharacterInfo[playerid][pPos][0] + 1, CharacterInfo[playerid][pPos][1] + 2, CharacterInfo[playerid][pPos][2] + 3);
	SetPlayerCameraLookAt(playerid, CharacterInfo[playerid][pPos][0], CharacterInfo[playerid][pPos][1], CharacterInfo[playerid][pPos][2]);
	
	SetPlayerHP(playerid, 20);
	SavePlayerStats(playerid, SAVE_PLAYER_POS);
	
	TogglePlayerControllable(playerid, 0);
	
	CharacterInfo[playerid][pDeathTimer] = 3;
	
	if(CharacterInfo[playerid][pWoundedTimer])
	{
		if(reason < 22)
		{		
			CharacterInfo[playerid][pBW] = 5 * 60;
			msg_info(playerid,"Zosta³eœ pobity do nieprzytomnoœci. Twój aktualny stan nie pozwala na poruszanie siê.\nMusisz przeczekaæ stan nieprzytomnoœci, a¿ siê ockniesz lub zostaniesz uratowany.");
		}
		else
		{	
			CharacterInfo[playerid][pBW] = 5 * 60;
			msg_info(playerid,"Zosta³eœ postrzelony z broni. Twój aktualny stan nie pozwala na poruszanie siê.\nMusisz przeczekaæ stan nieprzytomnoœci, a¿ siê ockniesz lub zostaniesz uratowany.");
		}
		
		if(killerid == INVALID_PLAYER_ID && !GetPVarInt(playerid, "KillerWeaponID"))
		{
			SendAdminMessageFormat(COLOR_RED, "[AI] %s (ID: %d) zosta³ zabity œmierci¹ naturaln¹.", PlayerName3(playerid), playerid);
			weapon_val=0;
			format(gun,sizeof(gun),"-");
			log("%s[player:%d] otrzyma³ powalenie (œmierc naturalna).", PlayerName3(playerid), CharacterInfo[playerid][pUID]);
		}
		else
		{
			if(GetPVarInt(playerid, "KillerWeaponID") >= 0)
			{
				if(GetPVarInt(playerid, "KillerWeaponID") == 0)
				{
					format(gun, sizeof(gun), "Piêœci");
					weapon_val = CharacterInfo[killerid][pUID];
				}
				else
				{
					GetWeaponName(GetPVarInt(playerid, "KillerWeaponID"), gun, sizeof(gun));
					weapon_val=CharacterInfo[GetPVarInt(playerid, "KillerID")][pWeaponUID];
				}
				
				SendAdminMessageFormat(COLOR_RED, "[AI] %s (ID: %d) zosta³ zabity (BW W£AŒCIWE) przez %s (ID: %d) (Broñ: %s).", PlayerName3(playerid), playerid, PlayerName3(GetPVarInt(playerid, "KillerID")), GetPVarInt(playerid, "KillerID"), gun);
				log("%s[player:%d] zabity (BW W£AŒCIWE) przez %s[player:%d] typ:%d bron:[itemid:%d]",PlayerName3(playerid),CharacterInfo[playerid][pUID],PlayerName3(GetPVarInt(playerid, "KillerID")),CharacterInfo[GetPVarInt(playerid, "KillerID")][pUID],GetPVarInt(playerid, "KillerWeaponID"),CharacterInfo[GetPVarInt(playerid, "KillerID")][pWeaponUID]);
			
				SetPVarString(playerid, "KillWeapon", gun);
				SetPVarInt(playerid, "KillWeaponVal", weapon_val);
			}
			else
			{
				SendAdminMessageFormat(COLOR_RED, "[AI] %s (ID: %d) zosta³ zabity (BW W£AŒCIWE).", PlayerName3(playerid), playerid);
				log("%s[player:%d] zabity (BW W£AŒCIWE) ale chuj wie przez kogo.", PlayerName3(playerid), CharacterInfo[playerid][pUID]);
			}
		}
		
		return 1;
	}
	else
	{
		if(reason < 22)
			CharacterInfo[playerid][pWounded] = 3 * 60;
		else
			CharacterInfo[playerid][pWounded] = 2 * 60;
		
		if(killerid == INVALID_PLAYER_ID && !GetPVarInt(playerid, "KillerWeaponID"))
		{
			SendAdminMessageFormat(COLOR_RED, "[AI] %s (ID: %d) zosta³ zabity (POWALONY) œmierci¹ naturaln¹.", PlayerName3(playerid), playerid);
			weapon_val=0;
			format(gun,sizeof(gun),"-");
			log("%s[player:%d] otrzyma³ powalenie (œmierc naturalna).", PlayerName3(playerid), CharacterInfo[playerid][pUID]);
		}
		else
		{
			if(GetPVarInt(playerid, "KillerWeaponID") >= 0)
			{
				if(GetPVarInt(playerid, "KillerWeaponID") == 0)
				{
					format(gun, sizeof(gun), "Piêœci");
					weapon_val = CharacterInfo[killerid][pUID];
				}
				else
				{
					GetWeaponName(GetPVarInt(playerid, "KillerWeaponID"), gun, sizeof(gun));
					weapon_val=CharacterInfo[GetPVarInt(playerid, "KillerID")][pWeaponUID];
				}
				
				SendAdminMessageFormat(COLOR_RED, "[AI] %s (ID: %d) zosta³ zabity (POWALONY) przez %s (ID: %d) (Broñ: %s).", PlayerName3(playerid), playerid, PlayerName3(GetPVarInt(playerid, "KillerID")), GetPVarInt(playerid, "KillerID"), gun);
				log("%s[player:%d] zabity (POWALONY) przez %s[player:%d] typ:%d bron:[itemid:%d]",PlayerName3(playerid),CharacterInfo[playerid][pUID],PlayerName3(GetPVarInt(playerid, "KillerID")),CharacterInfo[GetPVarInt(playerid, "KillerID")][pUID],GetPVarInt(playerid, "KillerWeaponID"),CharacterInfo[GetPVarInt(playerid, "KillerID")][pWeaponUID]);
			}
			else
			{
				if(reason)
				{
					GetWeaponName(reason, gun, sizeof(gun));
					weapon_val=CharacterInfo[killerid][pWeaponUID];
				}
				else
				{
					format(gun,sizeof(gun), "Pobicie");
					weapon_val = CharacterInfo[killerid][pUID];
				}
				
				SendAdminMessageFormat(COLOR_RED, "[AI] %s (ID: %d) zosta³ zabity (POWALONY) przez %s (ID: %d) (Broñ: %s).", PlayerName3(playerid), playerid, PlayerName3(killerid), killerid, gun);
				log("%s[player:%d] zabity (POWALONY) przez %s[player:%d] typ:%d bron:[itemid:%d]",PlayerName3(playerid),CharacterInfo[playerid][pUID],PlayerName3(killerid),CharacterInfo[killerid][pUID],reason,CharacterInfo[killerid][pWeaponUID]);
			}
		}
		
		SetPVarString(playerid, "KillWeapon", gun);
		SetPVarInt(playerid, "KillWeaponVal", weapon_val);
	}
	
	CharacterInfo[playerid][pWoundedTimer] = 5 * 60;
	
	return 1;
}

public OnPlayerUpdate(playerid)
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK && GetPVarInt(playerid, "ESC"))
	{
		CharacterInfo[playerid][pStatus] -= STATUS_AFK;
		playerLog(playerid,"AFK","%s zakonczyl AFK",PlayerName(playerid));
		DeletePVar(playerid, "ESC");
	} 
	CharacterInfo[playerid][pLastUpdate] = GetTickCount();
	
	if(CharacterInfo[playerid][pHaveWeapon])
	{
		if(GetPlayerWeapon(playerid) == 0 && !IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON))
		{
			new weapon_id = CharacterInfo[playerid][pWeaponID];
			switch(GetWeaponType(CharacterInfo[playerid][pWeaponID]))
			{
				case WEAPON_TYPE_LIGHT:

					SetPlayerAttachedObject(playerid, SLOT_WEAPON, WeaponModel[weapon_id], 8, 0.0, -0.1, 0.15, -100.0, 0.0, 0.0);
				case WEAPON_TYPE_MELEE:
					SetPlayerAttachedObject(playerid, SLOT_WEAPON, WeaponModel[weapon_id], 7, 0.0, 0.0, -0.18, 100.0, 45.0, 0.0);
				case WEAPON_TYPE_HEAVY:
				{
					if(CharacterInfo[playerid][pTog] & TOG_GUN_CARRY)
						SetPlayerAttachedObject(playerid, SLOT_WEAPON, WeaponModel[weapon_id], 1, 0.08, 0.23, -0.158, -5.2, 18.6, 180.0);
					else
						SetPlayerAttachedObject(playerid, SLOT_WEAPON, WeaponModel[weapon_id], 1, 0.2, -0.125, -0.1, 0.0, 25.0, 180.0);
				}
				case WEAPON_TYPE_MELEE_BIG:
					SetPlayerAttachedObject(playerid, SLOT_WEAPON, WeaponModel[weapon_id], 1, 0.429, -0.131, -0.131, 0.0, -53.5, 180.0);
			}
		}
		else if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON) && GetPlayerWeapon(playerid))
			RemovePlayerAttachedObject(playerid, SLOT_WEAPON);
	}
	
	return 1;
}

public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{
	new vehuid = GetVehicleUID(vehicleid);
	new v0, v1, v2, v3;
	if(!CharacterInfo[playerid][pRepairVeh])
	{
		GetVehicleDamageStatus(vehicleid, v0, v1, v2, v3);
		if(v0>VehicleInfo[vehuid][vVisual][0])
			VehicleInfo[vehuid][vVisual][0] = v0;
		if(v1>VehicleInfo[vehuid][vVisual][1])
			VehicleInfo[vehuid][vVisual][1] = 0;
		if(v2>VehicleInfo[vehuid][vVisual][2])
			VehicleInfo[vehuid][vVisual][2] = v2;
		if(v3>VehicleInfo[vehuid][vVisual][3])
			VehicleInfo[vehuid][vVisual][3] = v3;
	}
	
	UpdateVehicleDamageStatus(vehicleid, VehicleInfo[vehuid][vVisual][0], VehicleInfo[vehuid][vVisual][1], VehicleInfo[vehuid][vVisual][2], VehicleInfo[vehuid][vVisual][3]);

	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	new uid=GetVehicleUID(vehicleid);
	SetVehiclePos(vehicleid, VehicleInfo[uid][vposx], VehicleInfo[uid][vposy], VehicleInfo[uid][vposz]);
	SetVehicleHealth(vehicleid, VehicleInfo[uid][vHP]);
	UpdateVehicleDamageStatus(vehicleid, VehicleInfo[uid][vVisual][0], VehicleInfo[uid][vVisual][1], VehicleInfo[uid][vVisual][2], VehicleInfo[uid][vVisual][3]);
	SetVehicleNumberPlate(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vRegister]);
	ChangeVehicleEngineStatus(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vEngine]);
	ChangeVehicleLightsStatus(VehicleInfo[uid][vSAMPID],false);
	if(VehicleInfo[uid][vTuning] & TUNING_PAINTJOB)
	{
		if(VehicleInfo[uid][vTuning] & TUNING_PAINTJOB_0)
			ChangeVehiclePaintjob(VehicleInfo[uid][vSAMPID],0);					
		else if(VehicleInfo[uid][vTuning] & TUNING_PAINTJOB_1)
			ChangeVehiclePaintjob(VehicleInfo[uid][vSAMPID],1);
		else if(VehicleInfo[uid][vTuning] & TUNING_PAINTJOB_2)
			ChangeVehiclePaintjob(VehicleInfo[uid][vSAMPID],2);
	}

	if(VehicleInfo[uid][vTuning] & TUNING_VISUAL)
	{
		new query[128];
		format(query, sizeof(query), "SELECT `component_id` FROM `srv_tuning` WHERE `vehicle`='%d'", uid);
		mysql_query(query);
		mysql_store_result();
		while(mysql_fetch_row_format(query, "|") == 1)
			AddVehicleComponent(VehicleInfo[uid][vSAMPID], strval(query));
		
		mysql_free_result();
	}
	SetVehicleLock(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vLocked]);

	ChangeVehicleColor(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vColor1], VehicleInfo[uid][vColor2]);
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	new vehuid = GetVehicleUID(vehicleid);

	GetVehicleDamageStatus(VehicleInfo[vehuid][vSAMPID], VehicleInfo[vehuid][vVisual][0], VehicleInfo[vehuid][vVisual][1], VehicleInfo[vehuid][vVisual][2], VehicleInfo[vehuid][vVisual][3]);
	VehicleInfo[vehuid][vHP] = 300.0;
	SetVehicleHealth(vehicleid,VehicleInfo[vehuid][vHP]);

	log("%s[veh:%d] zostalo zniszczone. Ostatni kierowca: %d",GetVehicleModelName(VehicleInfo[vehuid][vModel]),vehuid,VehicleInfo[vehuid][vLastDriver]);
	
	GetVehiclePos(VehicleInfo[vehuid][vSAMPID], VehicleInfo[vehuid][vposx], VehicleInfo[vehuid][vposy], VehicleInfo[vehuid][vposz]);
	GetVehicleZAngle(VehicleInfo[vehuid][vSAMPID], VehicleInfo[vehuid][vAngle]);
	
	VehicleInfo[vehuid][vVW] = GetVehicleVirtualWorld(VehicleInfo[vehuid][vSAMPID]);
	if(VehicleInfo[vehuid][vModel] == 509 || VehicleInfo[vehuid][vModel] == 510 || VehicleInfo[vehuid][vModel] == 481)
		VehicleInfo[vehuid][vEngine] = true;
	else
		VehicleInfo[vehuid][vEngine] = false;

	ChangeVehicleEngineStatus(vehuid, VehicleInfo[vehuid][vEngine]);
	if(VehicleInfo[vehuid][vPolice])
	{
		DestroyDynamicObject(VehicleInfo[vehuid][vPolice]);
		VehicleInfo[vehuid][vPolice] = 0;
	}
	
	if(VehicleInfo[vehuid][vHandBrake])
	{
		VehicleInfo[vehuid][vHandBrake] = false;
		VehicleInfo[vehuid][vHB][0] = 
		VehicleInfo[vehuid][vHB][1] = 
		VehicleInfo[vehuid][vHB][2] = 
		VehicleInfo[vehuid][vHB][3] = 0;
	}
	
	SetVehicleLock(VehicleInfo[vehuid][vSAMPID], VehicleInfo[vehuid][vLocked]);
	
	SaveVehicle(vehuid, SAVE_VEH_POS);
	SaveVehicle(vehuid, SAVE_VEH_BASIC);
	
	return 1;
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	if(hitid >= MAX_PLAYERS) return 0;
	
	if(hittype == BULLET_HIT_TYPE_PLAYER)
		if(CharacterInfo[hitid][pAdmin] && CharacterInfo[hitid][pAdminDuty])
			return 0;
	
	if(GetPlayerWeapon(playerid) && !CharacterInfo[playerid][pHaveWeapon])
		return 0;
	
	// Zapis amunicji
	new ammo, weapon;
	GetPlayerWeaponData(playerid,  GetWeaponSlot(CharacterInfo[playerid][pWeaponID]), weapon, ammo);
	if(CharacterInfo[playerid][pHaveWeapon])
	{
		if(CharacterInfo[playerid][pWeaponID] > 15 && CharacterInfo[playerid][pWeaponID] < 43)
		{
			if(ammo >= CharacterInfo[playerid][pWeaponAmmo])
				CharacterInfo[playerid][pWeaponAmmo] --;
			else
				CharacterInfo[playerid][pWeaponAmmo] = ammo;

			if(CharacterInfo[playerid][pWeaponAmmo] <= 0)
			{
				new query[128];
				format(query, sizeof(query), "UPDATE `srv_items` SET `value2` = 0, `used` = 0 WHERE `uid` = '%d' LIMIT 1", CharacterInfo[playerid][pWeaponUID]);
				mysql_query(query);

				ResetPlayerWeapons(playerid);
				ItemInfo[CharacterInfo[playerid][pWeaponUID]][iUsed] = 
				ItemInfo[CharacterInfo[playerid][pWeaponUID]][iValue2]=0;

				CharacterInfo[playerid][pWeaponUID] = 
				CharacterInfo[playerid][pWeaponID] = 
				CharacterInfo[playerid][pWeaponAmmo] = 0;
				SetTimerEx("NegateHavingWeapons", 2000, false, "i", playerid);
			}
		}
	}
	
	if(hittype != BULLET_HIT_TYPE_VEHICLE)
	{
		new Float:fOriginX, Float:fOriginY, Float:fOriginZ, Float:fHitPosX, Float:fHitPosY, Float:fHitPosZ;
		GetPlayerLastShotVectors(playerid, Float:fOriginX, Float:fOriginY, Float:fOriginZ, Float:fHitPosX, Float:fHitPosY, Float:fHitPosZ);
		
		if(!IsPlayerInRangeOfPoint(hitid, Float:1.5, Float:fHitPosX, Float:fHitPosY, Float:fHitPosZ))
		{
			CharacterInfo[hitid][pAimBotWarn]++;
			
			if(CharacterInfo[hitid][pAimBotWarn] > 3)
			{
				SendAdminMessageFormat(COLOR_RED, "[AI] %s(%d) [%s] prawdopodobnie cheatuje (AimBot), obserwuj go!", PlayerName3(playerid), playerid, CharacterInfo[playerid][pGlobalNick]);
				CharacterInfo[hitid][pAimBotWarn] = 0;
			}
		} 
	}
	
	return 1;
}

public OnPlayerPickUpDynamicPickup(playerid, pickupid)
{
	if(pickupid == PICKUP_GOV_DOCS || pickupid == PICKUP_GOV_JOBS)
		return 1;
	else if(!CharacterInfo[playerid][pShowDoors])
	{
		new dooruid = GetPickupUID(pickupid);
		new name_door[144];
		
		if(CharacterInfo[playerid][pAdmin] < 3)
		{
			if(DoorsInfo[dooruid][dOwnerTyp] == OWNER_GROUP)
			{
				if(DoorsInfo[dooruid][dLock]) format(name_door, sizeof(name_door), "%s~n~~r~[ZAMKNIETE]", DoorsInfo[dooruid][dName]);
				else
				{
					if(DoorsInfo[dooruid][dEnterVW] == 0 && DoorsInfo[dooruid][dPriceForEntry])
					{
						if(DoorsInfo[dooruid][dExitVW] != 0)
						{
							new count = 0;
							ForeachPlayer(i)
								if(GetPlayerVirtualWorld(i) == DoorsInfo[dooruid][dExitVW])
									count++;
							
							format(name_door, sizeof(name_door), "%s~n~~g~[OTWARTE]~n~~w~Oplata za wejscie: ~y~$%d~n~~w~Ilosc osob w interiorze: ~y~%d~n~~w~Nacisnij ALT + SPACJA", DoorsInfo[dooruid][dName], DoorsInfo[dooruid][dPriceForEntry], count);
						}
						else
							format(name_door, sizeof(name_door), "%s~n~~g~[OTWARTE]~n~~w~Oplata za wejscie: ~y~$%d~n~~w~Nacisnij ALT + SPACJA", DoorsInfo[dooruid][dName], DoorsInfo[dooruid][dPriceForEntry]);
					}
					else
						format(name_door, sizeof(name_door), "%s~n~~g~[OTWARTE]~n~~w~Nacisnij ALT + SPACJA", DoorsInfo[dooruid][dName]);
				}
			}
			else if(DoorsInfo[dooruid][dOwnerTyp] == OWNER_BANKOMAT)
				format(name_door, sizeof(name_door), "%s~n~/bankomat", DoorsInfo[dooruid][dName]);
			else if(DoorsInfo[dooruid][dOwnerTyp] == OWNER_HOUSE_BUY)
				format(name_door, sizeof(name_door), "%s~n~/sprawdzdom, /kupdom~n~~g~Cena: $%d", DoorsInfo[dooruid][dName], DoorsInfo[dooruid][dOwner]);
			else if(DoorsInfo[dooruid][dOwnerTyp] == OWNER_SVEHICLE)
				format(name_door, sizeof(name_door), "%s~n~/kuppojazd", DoorsInfo[dooruid][dName]);
			else if(DoorsInfo[dooruid][dOwnerTyp] == OWNER_ULECZSIE)
				format(name_door, sizeof(name_door), "%s~n~/uleczsie", DoorsInfo[dooruid][dName]);
			else if(DoorsInfo[dooruid][dOwnerTyp] == OWNER_PLAYER && DoorsInfo[dooruid][dOwner] == CharacterInfo[playerid][pUID])
				if(DoorsInfo[dooruid][dLock]) format(name_door, sizeof(name_door), "%s~n~~r~[ZAMKNIETE]~n~~n~~y~UID: %d", DoorsInfo[dooruid][dName], DoorsInfo[dooruid][dUID]);
				else format(name_door, sizeof(name_door), "%s~n~~g~[OTWARTE]~n~~w~Nacisnij ALT + SPACJA~n~~n~~y~UID: %d", DoorsInfo[dooruid][dName], DoorsInfo[dooruid][dUID]);
			else if(DoorsInfo[dooruid][dOwnerTyp] == OWNER_SAFEKEEP)
				format(name_door, sizeof(name_door), "%s~n~/skrytka", DoorsInfo[dooruid][dName]);
			else if(DoorsInfo[dooruid][dOwnerTyp])
			{
				if(DoorsInfo[dooruid][dLock]) format(name_door, sizeof(name_door), "%s~n~~r~[ZAMKNIETE]", DoorsInfo[dooruid][dName]);
				else format(name_door, sizeof(name_door), "%s~n~~g~[OTWARTE]~n~~w~Nacisnij ALT + SPACJA", DoorsInfo[dooruid][dName]);
			}
		}
		else
		{
			if(DoorsInfo[dooruid][dOwnerTyp] == OWNER_GROUP)
			{
				if(DoorsInfo[dooruid][dLock]) format(name_door, sizeof(name_door), "%s~n~~r~[ZAMKNIETE]~n~~n~~y~UID: %d", DoorsInfo[dooruid][dName], DoorsInfo[dooruid][dUID]);
				else
				{
					if(DoorsInfo[dooruid][dEnterVW] == 0 && DoorsInfo[dooruid][dPriceForEntry])
					{
						if(DoorsInfo[dooruid][dExitVW] != 0)
						{
							new count = 0;
							ForeachPlayer(i)
								if(GetPlayerVirtualWorld(i) == DoorsInfo[dooruid][dExitVW])
									count++;
							
							format(name_door, sizeof(name_door), "%s~n~~g~[OTWARTE]~n~~w~Oplata za wejscie: ~y~$%d~n~~w~Ilosc osob w interiorze: ~y~%d~n~~w~Nacisnij ALT + SPACJA~n~~n~~y~UID: %d", DoorsInfo[dooruid][dName], DoorsInfo[dooruid][dPriceForEntry], count, DoorsInfo[dooruid][dUID]);
						}
						else
							format(name_door, sizeof(name_door), "%s~n~~g~[OTWARTE]~n~~w~Oplata za wejscie: ~y~$%d~n~~w~Nacisnij ALT + SPACJA~n~~n~~y~UID: %d", DoorsInfo[dooruid][dName], DoorsInfo[dooruid][dPriceForEntry], DoorsInfo[dooruid][dUID]);
					}
					else
						format(name_door, sizeof(name_door), "%s~n~~g~[OTWARTE]~n~~w~Nacisnij ALT + SPACJA~n~~n~~y~UID: %d", DoorsInfo[dooruid][dName], DoorsInfo[dooruid][dUID]);
				}
			}
			else if(DoorsInfo[dooruid][dOwnerTyp] == OWNER_BANKOMAT)
				format(name_door, sizeof(name_door), "%s~n~/bankomat~n~~n~~y~UID: %d", DoorsInfo[dooruid][dName], DoorsInfo[dooruid][dUID]);
			else if(DoorsInfo[dooruid][dOwnerTyp] == OWNER_HOUSE_BUY)
				format(name_door, sizeof(name_door), "%s~n~/sprawdzdom, /kupdom~n~~g~Cena: $%d~n~~n~~y~UID: %d", DoorsInfo[dooruid][dName], DoorsInfo[dooruid][dOwner], DoorsInfo[dooruid][dUID]);
			else if(DoorsInfo[dooruid][dOwnerTyp] == OWNER_SVEHICLE)
				format(name_door, sizeof(name_door), "%s~n~/kuppojazd~n~~n~~y~UID: %d", DoorsInfo[dooruid][dName], DoorsInfo[dooruid][dUID]);
			else if(DoorsInfo[dooruid][dOwnerTyp] == OWNER_ULECZSIE)
				format(name_door, sizeof(name_door), "%s~n~/uleczsie~n~~n~~y~UID: %d", DoorsInfo[dooruid][dName], DoorsInfo[dooruid][dUID]);
			else if(DoorsInfo[dooruid][dOwnerTyp])
			{
				if(DoorsInfo[dooruid][dLock]) format(name_door, sizeof(name_door), "%s~n~~r~[ZAMKNIETE]~n~~n~~y~UID: %d", DoorsInfo[dooruid][dName], DoorsInfo[dooruid][dUID]);
				else format(name_door, sizeof(name_door), "%s~n~~g~[OTWARTE]~n~~w~Nacisnij ALT + SPACJA~n~~n~~y~UID: %d", DoorsInfo[dooruid][dName], DoorsInfo[dooruid][dUID]);
			}
		}

		PlayerTextDrawSetString(playerid, DoorsTD[playerid], name_door);

		PlayerTextDrawShow(playerid, DoorsTD[playerid]);

		CharacterInfo[playerid][pShowDoors] = 3;
	}
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys == KEY_HANDBRAKE)
	{
		if( (CharacterInfo[playerid][pStatus] & STATUS_PLAY_ANIM))
		{
			CharacterInfo[playerid][pStatus] -= STATUS_PLAY_ANIM;
			ApplyAnimation( playerid, "CARRY", "crry_prtial", 4.1, 0, 0, 0, 0, 0 );
			if(!IsPlayerInAnyVehicle(playerid))
				ClearAnimations(playerid);
		}
	}
	else if(newkeys == (KEY_WALK + KEY_SPRINT))
	{
		if(CharacterInfo[playerid][pBW] || CharacterInfo[playerid][pWounded]) return 1;
	
		if(!IsPlayerInAnyVehicle(playerid))
		{
			ForeachEx(i, MAX_DOORS)
			{
				if(IsPlayerInRangeOfPoint(playerid, 1.0, DoorsInfo[i][dEnterX], DoorsInfo[i][dEnterY], DoorsInfo[i][dEnterZ]) && GetPlayerVirtualWorld(playerid) == DoorsInfo[i][dEnterVW])
				{
					if(DoorsInfo[i][dLock])
					{
						if(DoorsInfo[i][dOwnerTyp] == OWNER_BANKOMAT || DoorsInfo[i][dOwnerTyp] == OWNER_SVEHICLE) return 1;
						else if(DoorsInfo[i][dOwnerTyp] == OWNER_HOUSE_BUY && !CharacterInfo[playerid][pAdmin]) return 1;
						
						Tip(playerid, 3, "Drzwi sa zamkniete.");
						return 1;
					}
					else if(DoorsInfo[i][dOwnerTyp] == OWNER_GROUP && IsBusiness(DoorsInfo[i][dOwner]))
					{
						if(!GroupInfo[DoorsInfo[i][dOwner]][gRegistered] && !CharacterInfo[playerid][pAdmin] && DutyGroup[playerid] != DoorsInfo[i][dOwner]) 
						{		
							Tip(playerid, 3, "Biznes nie jest zarejestrowany.");
							return 1;
						}
						PlayerEnterDoor(playerid, i);
						return 1;
					}
					else
					{
						if(DoorsInfo[i][dOwnerTyp] == OWNER_BANKOMAT || DoorsInfo[i][dOwnerTyp] == OWNER_SVEHICLE || DoorsInfo[i][dOwnerTyp] == OWNER_ULECZSIE) return 1;
						else if(DoorsInfo[i][dOwnerTyp] == OWNER_HOUSE_BUY && !CharacterInfo[playerid][pAdmin]) return 1;
					
						PlayerEnterDoor(playerid, i);
						return 1;
					}
				}
				else if(IsPlayerInRangeOfPoint(playerid, 1.0, DoorsInfo[i][dExitX], DoorsInfo[i][dExitY], DoorsInfo[i][dExitZ]) && GetPlayerVirtualWorld(playerid) == DoorsInfo[i][dExitVW])
				{
					if(DoorsInfo[i][dLock])
					{
						Tip(playerid, 3, "Drzwi sa zamkniete.");
						return 1;
					}
					else
					{
						PlayerExitDoor(playerid, i);
						return 1;
					}
				}
			}
		}
	}
	else if(newkeys == KEY_FIRE && CharacterInfo[playerid][pStatus] & STATUS_AFK)
	{
		msg_info(playerid,"Przesta³eœ byæ AFK. Twoje statystki bêd¹ naliczane.");
		
		CharacterInfo[playerid][pStatus] -= STATUS_AFK;
		CharacterInfo[playerid][pAFKg] = 0;
		CharacterInfo[playerid][pAFKm] = 0;
		
		playerLog(playerid,"AFK","%s zakonczyl AFK",PlayerName(playerid));
		
		if(CanMove(playerid) && !CharacterInfo[playerid][pGymType])
			UnfreezePlayer(playerid);
	}
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		static vehid,vehuid;
		vehid = GetPlayerVehicleID(playerid);
		vehuid = GetVehicleUID(vehid);
			
		if(newkeys == (KEY_YES))
			cmd_silnik(playerid,"");
		else if(newkeys & KEY_ACTION)
		{
			cmd_pojazd(playerid,"l");
			if(VehicleInfo[vehuid][vModel]==509 || VehicleInfo[vehuid][vModel]==510 || VehicleInfo[vehuid][vModel]==481)
			{
				if(!IsPlayerInRangeOfPoint(playerid, 100.0, 1916.3630,-1408.7148,13.5703))
				{
					ClearAnimations(playerid,1);
					SendClientMessage(playerid, COLOR_RED, "Nie mo¿na skakaæ rowerem poza skateparkiem!");
				}
			}
		}
		else if (newkeys==KEY_FIRE)
		{
			if (GetVehicleModel(vehid) == 525)
			{
				new Float:pX,Float:pY,Float:pZ,Float:vX,Float:vY,Float:vZ,vid;
				new Found;
				GetPlayerPos(playerid,pX,pY,pZ);
				new vehPool=GetVehiclePoolSize()+1;
				while( (vid<vehPool)&&(!Found))
				{
					vid++;
					GetVehiclePos(vid,vX,vY,vZ);
					if  ((floatabs(pX-vX)<7.0)&&(floatabs(pY-vY)<7.0)&&(floatabs(pZ-vZ)<7.0)&&(vid!=GetPlayerVehicleID(playerid))&& !IsAPlane(vid))
					{
						Found=1;
						if(IsTrailerAttachedToVehicle(GetPlayerVehicleID(playerid)))
							DetachTrailerFromVehicle(GetPlayerVehicleID(playerid));
						else
						{
							AttachTrailerToVehicle(vid,GetPlayerVehicleID(playerid));
							new towtruck = GetVehicleUID(GetPlayerVehicleID(playerid));
							new car = GetVehicleUID(vid);
							log("%s[player:%d] podpina %s[veh:%d] pod holownik [veh:%d]",PlayerName3(playerid),CharacterInfo[playerid][pUID],GetVehicleModelName(VehicleInfo[car][vModel]),car,towtruck);
						}
					}
				}
			}
		}
		if(!IsAPlane(vehid) && !IsABoat(vehid) && hasModelEngine(VehicleInfo[vehuid][vModel]))
		{
			if(newkeys & KEY_LOOK_RIGHT && !(CharacterInfo[playerid][pTog] & TOG_KIERUNKI))
			{
				if(Kierunki_V[vehuid][0])
				{
                    DestroyObject(Kierunki_V[vehuid][4]);
					DestroyObject(Kierunki_V[vehuid][0]);
					DestroyObject(Kierunki_V[vehuid][1]);

					Kierunki_V[vehuid][0]=0;
				}
				else if(Kierunki_V[vehuid][2])
				{
                    DestroyObject(Kierunki_V[vehuid][5]);
					DestroyObject(Kierunki_V[vehuid][2]);
					DestroyObject(Kierunki_V[vehuid][3]);

					Kierunki_V[vehuid][2]=0;
				}
				else SetVehicleIndicator(vehuid, 0, 1);

			}
			if(newkeys & KEY_LOOK_LEFT && !(CharacterInfo[playerid][pTog] & TOG_KIERUNKI))
			{
				if(Kierunki_V[vehuid][2])
				{
                    DestroyObject(Kierunki_V[vehuid][5]);
					DestroyObject(Kierunki_V[vehuid][2]);
					DestroyObject(Kierunki_V[vehuid][3]);

					Kierunki_V[vehuid][2]=0;
				}
				else if(Kierunki_V[vehuid][0])
				{
					DestroyObject(Kierunki_V[vehuid][4]);
					DestroyObject(Kierunki_V[vehuid][0]);
					DestroyObject(Kierunki_V[vehuid][1]);
					
					Kierunki_V[vehuid][0]=0;
				}
				else SetVehicleIndicator(vehuid, 1, 0);
			}
		}
	}
	else if(CharacterInfo[playerid][pGymType] != TRAIN_NONE)
	{
		if(CharacterInfo[playerid][pGymType] == TRAIN_BARBELL)
		{
			if(newkeys & KEY_SPRINT)
			{
				if(CharacterInfo[playerid][pGymPhase] == 1)
				{
					CharacterInfo[playerid][pGymPhase] = 2;

					ApplyAnimation(playerid, "FREEWEIGHTS", "gym_free_A", 4.0, 0, 0, 0, 1, 0, 1);
					SetTimerEx("OnPlayerTrainRep", 2000, 0, "i", playerid);
				}
			}
			if(newkeys & KEY_SECONDARY_ATTACK)
			{
				CharacterInfo[playerid][pGymPhase] = 0;

				ApplyAnimation(playerid, "FREEWEIGHTS", "gym_free_putdown", 4.0, 0, 0, 0, 0, 0, 1);
				SetTimerEx("OnPlayerGymTrainStopped", 1500, 0, "i", playerid);
			}
		} 
		else if(CharacterInfo[playerid][pGymType] == TRAIN_BENCH)
		{
			if(newkeys & KEY_YES)
			{
				if(CharacterInfo[playerid][pGymPhase] == 1)
				{
					CharacterInfo[playerid][pGymPhase] = 3;

					ApplyAnimation(playerid, "BENCHPRESS", "gym_bp_up_A", 4.0, 0, 0, 0, 1, 0, 1);
					SetTimerEx("OnPlayerTrainRep", 2500, 0, "i", playerid);
				}
			}
			else if(newkeys & KEY_NO)
			{
				if(CharacterInfo[playerid][pGymPhase] == 2)
				{
					CharacterInfo[playerid][pGymPhase] = 4;

					ApplyAnimation(playerid, "BENCHPRESS", "gym_bp_down", 4.0, 0, 0, 0, 1, 0, 1);
					SetTimerEx("OnPlayerTrainRep", 1000, 0, "i", playerid);
				}
			}
			else if(newkeys & KEY_SECONDARY_ATTACK)
			{
				CharacterInfo[playerid][pGymPhase]= 0;

				ApplyAnimation(playerid, "BENCHPRESS", "gym_bp_getoff", 4.0, 0, 0, 0, 0, 0, 1);

				SetTimerEx("OnPlayerGymTrainStopped", 3500, 0, "i", playerid);
			}
		}
		else if(CharacterInfo[playerid][pGymType] == TRAIN_PUNCH_BAG)
		{
			if(oldkeys & KEY_HANDBRAKE && newkeys & KEY_SECONDARY_ATTACK)
			{
				new uid=CharacterInfo[playerid][pGymObject];
				if(CharacterInfo[playerid][pGymPhase] == 0 && PlayerFaces(playerid, ObjectInfo[uid][oX], ObjectInfo[uid][oY], ObjectInfo[uid][oZ]-0.75, 2.0))
				{
					CharacterInfo[playerid][pGymPhase] = 1;
					SetTimerEx("OnPlayerTrainRep", 750, 0, "i", playerid);
				}
			}
		}
	}
	else if(newkeys & KEY_WALK && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && CanMove(playerid))
		WalkAnim(playerid);
	else if(oldkeys & KEY_WALK && CharacterInfo[playerid][pStatus] & STATUS_WALK_ANIM && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		StopWalkAnim(playerid);
	
	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	new vehuid = GetVehicleUID(vehicleid);
	
	if(!CanMove(playerid))
	{
		new Float:PosX, Float:PosY, Float:PosZ;
		GetPlayerPos(playerid, PosX, PosY, PosZ);
		SetPlayerPos(playerid, PosX, PosY, PosZ);
		return 0;
	}
	
	if(!ispassenger)
	{
		if(VehicleInfo[vehuid][vOwnerTyp] == OWNER_GROUP && !IsOwnerVehicle(playerid, vehuid))
		{
			new Float:PosX, Float:PosY, Float:PosZ;
			GetPlayerPos(playerid, PosX, PosY, PosZ);
			
			SetPlayerPos(playerid, PosX, PosY, PosZ);
			return 0;
		}
	
		ForeachPlayer(i)
		{
			if(GetPlayerState(i) == PLAYER_STATE_DRIVER && GetPlayerVehicleID(i) == vehicleid)
			{
				new Float:PosX, Float:PosY, Float:PosZ;
				GetPlayerPos(playerid, PosX, PosY, PosZ);
				
				SetPlayerPos(playerid, PosX, PosY, PosZ);
				return 0;
			}
		}
	}
	
	if(CharacterInfo[playerid][pBlock] & BLOCK_NOCAR && !ispassenger)
	{
		new Float:PosX, Float:PosY, Float:PosZ;
		GetPlayerPos(playerid, PosX, PosY, PosZ);
		SetPlayerPos(playerid, PosX, PosY, PosZ);
		
		msg_info(playerid, "Posiadasz aktywn¹ blokade prowadzenia pojazdów.");
		return 0;
	}
	
	if(VehicleInfo[vehuid][vBlokada])
	{
		new Float:PosX, Float:PosY, Float:PosZ;
		GetPlayerPos(playerid, PosX, PosY, PosZ);
		SetPlayerPos(playerid, PosX, PosY, PosZ);
		
	    msg_info(playerid, "Pojazd posiada na³o¿on¹ blokadê.");
	    return 0;
	}
	
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	new vehid=GetVehicleUID(vehicleid);
	if(VehicleInfo[vehid][vRadio] && !(CharacterInfo[playerid][pStatus] & STATUS_MP3))
		StopAudioStreamForPlayer(playerid);
	
	if(PlayerDoor[playerid] && DoorsInfo[PlayerDoor[playerid]][dRadio] && !(CharacterInfo[playerid][pStatus] & STATUS_MP3))
		PlayAudioStreamForPlayer(playerid, DoorsInfo[PlayerDoor[playerid]][dRadio]);
	
	if(CharacterInfo[playerid][pStatus] & STATUS_PASY)
	{
		CharacterInfo[playerid][pStatus] -= STATUS_PASY;
		
		if(CharacterInfo[playerid][pTog] & TOG_STATUS)
		{
			PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][3]);

			PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][4]);
			PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][5]);
		}
	}

	UpdatePlayer3DTextNick(playerid);
	
	return 1;
}

public OnPlayerSelectDynamicObject(playerid, objectid, modelid, Float:x, Float:y, Float:z)
{
	new searchid = GetObjectIndex(objectid);
	if(!IsObjectOwner(playerid,searchid))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do edycji tego obiektu.");
	
	PlayerEditObject[playerid] = searchid;
	EditDynamicObject(playerid, objectid);
	new string[256];
	new Float:rx,Float:ry,Float:rz;
	GetDynamicObjectRot(objectid, rx, ry, rz);
	format(string, sizeof(string), "~b~EDYCJA OBIEKTU~n~Model: ~w~%d~b~ UID: ~w~%d~n~~b~X: ~w~%.5f ~b~Y: ~w~%.5f ~b~Z: ~w~%.5f~n~~b~RX: ~w~%.5f ~b~RY: ~w~%.5f ~b~RZ: ~w~%.5f~n~~b~Owner: ~w~%d~b~:~w~%d", ObjectInfo[searchid][oModel], searchid,x,y,z,rx,ry,rz,ObjectInfo[searchid][oOwnerType],ObjectInfo[searchid][oOwner]);
	PlayerTextDrawSetString(playerid, EditObjectText[playerid], string);
	PlayerTextDrawShow(playerid, EditObjectText[playerid]);
	
	return 1;
}

public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	new Float:Pos[3], Float:Rot[3];
	new uid = PlayerEditObject[playerid];

	GetDynamicObjectPos(objectid, Pos[0], Pos[1], Pos[2]);
	GetDynamicObjectRot(objectid, Rot[0], Rot[1], Rot[2]);
	PlayerTextDrawShow(playerid, EditObjectText[playerid]);
	new string[256];
	format(string, sizeof(string), "~b~EDYCJA OBIEKTU~n~Model: ~w~%d~b~ UID: ~w~%d~n~~b~X: ~w~%.5f ~b~Y: ~w~%.5f ~b~Z: ~w~%.5f~n~~b~RX: ~w~%.5f ~b~RY: ~w~%.5f ~b~RZ: ~w~%.5f~n~~b~Owner: ~w~%d~b~:~w~%d", ObjectInfo[uid][oModel], uid,x,y,z,rx,ry,rz,ObjectInfo[uid][oOwnerType],ObjectInfo[uid][oOwner]);
	PlayerTextDrawSetString(playerid, EditObjectText[playerid], string);
	if(ObjectInfo[uid][o3dText])
	{
		DestroyDynamic3DTextLabel(ObjectInfo[uid][o3dText]);
		format(string,sizeof(string),"UID: %d, Model: %d",uid,ObjectInfo[uid][oModel]);
		ObjectInfo[uid][o3dText]=CreateDynamic3DTextLabel(string, COLOR_BLUE, ObjectInfo[uid][oX], ObjectInfo[uid][oY], ObjectInfo[uid][oZ], 50.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0, ObjectInfo[uid][oVW]);
	}
	if(GetPVarInt(playerid, "Msave"))
		response = EDIT_RESPONSE_FINAL;
	switch(response)
	{
		case EDIT_RESPONSE_CANCEL:
		{
			if(PlayerEditGate[playerid])
				{
					// Przenieœ obiekt na pozycjê
					SetDynamicObjectPos(objectid, Pos[0], Pos[1], Pos[2]);
					SetDynamicObjectRot(objectid, Rot[0], Rot[1], Rot[2]);
					
					// Aktualizowanie zmiennych
					ObjectInfo[uid][oX] = Pos[0];
					ObjectInfo[uid][oY] = Pos[1];
					ObjectInfo[uid][oZ] = Pos[2];
					
					ObjectInfo[uid][oRX] = Rot[0];
					ObjectInfo[uid][oRY] = Rot[1];
					ObjectInfo[uid][oRZ] = Rot[2];
					
					ObjectInfo[uid][oGateX] = x;
					ObjectInfo[uid][oGateY] = y;
					ObjectInfo[uid][oGateZ] = z;
					
					ObjectInfo[uid][oGateRX] = rx;
					ObjectInfo[uid][oGateRY] = ry;
					ObjectInfo[uid][oGateRZ] = rz;
					
					ObjectInfo[uid][oGate] = 1;
					ObjectInfo[uid][oGateOpen] = false;
					
					// Zapisywanie obiektu i bramy
					SaveObject(uid);
					SaveObjectGate(uid);
					
					// Zakoñcz edycjê obiektu
					PlayerTextDrawHide(playerid, EditObjectText[playerid]);
					PlayerEditObject[playerid] = 0;
					PlayerEditGate[playerid] = false;
				}
				else if(PlayerEditObject[playerid])
				{
					// Przenieœ obiekt na pozycjê
					SetDynamicObjectPos(objectid, Pos[0], Pos[1], Pos[2]);
					SetDynamicObjectRot(objectid, Rot[0], Rot[1], Rot[2]);
					
					// Aktualizowanie zmiennych
					ObjectInfo[uid][oX] = Pos[0];
					ObjectInfo[uid][oY] = Pos[1];
					ObjectInfo[uid][oZ] = Pos[2];
					ObjectInfo[uid][oRX] = Rot[0];
					ObjectInfo[uid][oRY] = Rot[1];
					ObjectInfo[uid][oRZ] = Rot[2];
					PlayerTextDrawHide(playerid, EditObjectText[playerid]);
					
					if(!GetPVarInt(playerid,"Mclone"))
						PlayerEditObject[playerid] = 0;
					else
						DeletePVar(playerid,"Mclone");
				}
		}
		case EDIT_RESPONSE_FINAL:
		{
			SetDynamicObjectPos(objectid, x, y, z);
			SetDynamicObjectRot(objectid, rx, ry, rz);
					
			ObjectInfo[uid][oX] = x;
			ObjectInfo[uid][oY] = y;
			ObjectInfo[uid][oZ] = z;
					
			ObjectInfo[uid][oRX] = rx;
			ObjectInfo[uid][oRY] = ry;
			ObjectInfo[uid][oRZ] = rz;
			
			if(ObjectInfo[uid][oOwnerType]==OWNER_GROUP)
				GroupInfo[ObjectInfo[uid][oOwner]][gObjects]++;
			
			SaveObject(uid);
			PlayerTextDrawHide(playerid, EditObjectText[playerid]);
			DeletePVar(playerid, "Msave");
			PlayerEditObject[playerid] = 0;
		}
	}
	//PlayerTextDrawHide(playerid, EditObjectText[playerid]);
	return 1;
}

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
	if(CharacterInfo[damagedid][pStatus] & STATUS_AFK || CharacterInfo[damagedid][pAdminDuty] || CharacterInfo[damagedid][pBW])
	{
		SetPlayerHealth(damagedid, CharacterInfo[damagedid][pHealth]);
		return 1;
	}
	else if(playerid == INVALID_PLAYER_ID)
	{
		SetPlayerHealth(damagedid, CharacterInfo[damagedid][pHealth]);
		return 1;
	}
	else if(!Logged[playerid])
	{
		SetPlayerHealth(damagedid, CharacterInfo[damagedid][pHealth]);
		return 1;
	}
	else if(weaponid > 0 && !CharacterInfo[playerid][pHaveWeapon])
	{
		SetPlayerHealth(damagedid, CharacterInfo[damagedid][pHealth]);
		return 1;
	}
	else if(weaponid > 34)
	{
		SetPlayerHealth(damagedid, CharacterInfo[damagedid][pHealth]);
		return 1;
	}
	
	new Float:ilosc = 0.0;
	
	switch(weaponid)
	{
		case 0://Piêœæ
		{
			if(CharacterInfo[playerid][pHaveTaser])
			{
			    if(!CharacterInfo[damagedid][pWounded])
					CharacterInfo[damagedid][pAnimacja] = 10;
			}
			else
			{
				if(CharacterInfo[damagedid][pDrugs] == DRUG_HEROINA)
					ilosc = 3.0;
				else ilosc = 5.0;
				
				if(CharacterInfo[playerid][pDrugs] == DRUG_KOKAINA)
					ilosc = ilosc*2.0;
				
				ilosc+=float(CharacterInfo[playerid][pStrength])/100.0;
			}
		}
		case 1://Kastet
		{
			if(CharacterInfo[damagedid][pDrugs] == DRUG_HEROINA)
				ilosc = 8.0;
			else ilosc = 15.0;
			
			if(CharacterInfo[playerid][pDrugs] == DRUG_KOKAINA)
				ilosc = ilosc*2.0;
			
			ilosc+=float(CharacterInfo[playerid][pStrength])/100.0;
		}
		case 3://Pa³ka policyjna
		{
			if(CharacterInfo[damagedid][pDrugs] == DRUG_HEROINA)
				ilosc = 11.0;
			else ilosc = 20.0;
			
			if(CharacterInfo[playerid][pDrugs] == DRUG_KOKAINA)
				ilosc = ilosc*2.0;
			
			ilosc+=float(CharacterInfo[playerid][pStrength])/100.0;
		}
		case 4://Nó¿
		{
			if(CharacterInfo[damagedid][pDrugs] == DRUG_HEROINA)
				ilosc = 16.0;
			else ilosc = 25.0;
			
			if(CharacterInfo[playerid][pDrugs] == DRUG_KOKAINA)
				ilosc = ilosc*2.0;
		}
		case 5://Baseball
		{
			if(CharacterInfo[damagedid][pDrugs] == DRUG_HEROINA)
				ilosc = 11.0;
			else ilosc = 20.0;
			
			if(CharacterInfo[playerid][pDrugs] == DRUG_KOKAINA)
				ilosc = ilosc*2.0;
			
			ilosc+=float(CharacterInfo[playerid][pStrength])/100.0;
		}
		case 8://Katana
		{
			if(CharacterInfo[damagedid][pDrugs] == DRUG_HEROINA)
				ilosc = 11.0;
			else ilosc = 20.0;
			
			if(CharacterInfo[playerid][pDrugs] == DRUG_KOKAINA)
				ilosc = ilosc*2.0;
			
			ilosc+=float(CharacterInfo[playerid][pStrength])/100.0;
		}
		case 22://9mm
		{
			if(CharacterInfo[damagedid][pDrugs] == DRUG_HEROINA)
				ilosc = 12.0;
			else ilosc = 20.0;
		}
		case 23://Silenced 9mm
		{
			if(CharacterInfo[damagedid][pDrugs] == DRUG_HEROINA)
				ilosc = 12.0;
			else ilosc = 20.0;
		}
		case 24://DE
		{
			if(CharacterInfo[damagedid][pDrugs] == DRUG_HEROINA)
				ilosc = 30.0;
			else ilosc = 40.0;
		}
		case 25://Shotgun
		{
			if(CharacterInfo[damagedid][pDrugs] == DRUG_HEROINA)
				ilosc = 30.0;
			else ilosc = 45.0;
		}
		case 26://Sawnoff
		{
			if(CharacterInfo[damagedid][pDrugs] == DRUG_HEROINA)
				ilosc = 20.0;
			else ilosc = 30.0;
		}
		case 28://UZI
		{
			if(CharacterInfo[damagedid][pDrugs] == DRUG_HEROINA)
				ilosc = 7.0;
			else ilosc = 15.0;
		}
		case 29://MP5
		{
			if(CharacterInfo[damagedid][pDrugs] == DRUG_HEROINA)
				ilosc = 11.0;
			else ilosc = 20.0;
		}
		case 30://AK47
		{
			if(CharacterInfo[damagedid][pDrugs] == DRUG_HEROINA)
				ilosc = 10.0;
			else ilosc = 20.0;
		}
		case 31://M4
		{
			if(CharacterInfo[damagedid][pDrugs] == DRUG_HEROINA)
				ilosc = 10.0;
			else ilosc = 20.0;
		}
		case 32://TEC9
		{
			if(CharacterInfo[damagedid][pDrugs] == DRUG_HEROINA)
				ilosc = 7.0;
			else ilosc = 15.0;
		}
		case 33://RIFLE
		    if(!CharacterInfo[damagedid][pWounded])
				CharacterInfo[damagedid][pAnimacja] = 10;
		case 34://SNIPER
			ilosc = 250.0;
	}
	
	if(bodypart == 9)
		ilosc = ilosc*1.5;
	
	if(weaponid > 18 && CharacterInfo[damagedid][pArmor])
	{
		static Float:liczba;
		liczba = CharacterInfo[damagedid][pArmor]-ilosc;
		
		if(liczba <= 0)
		{
			SetPlayerArmour(damagedid, 0);
			CharacterInfo[damagedid][pArmor] = 0;
			SetPlayerHP(damagedid, CharacterInfo[damagedid][pHealth]+liczba);
		}
		else
		{
			SetPlayerArmour(damagedid, liczba);
			CharacterInfo[damagedid][pArmor] = liczba;
		}
	}
	else
	{
		if(weaponid <= 8 && CharacterInfo[damagedid][pStrength])
			ilosc -= ilosc*(float(CharacterInfo[damagedid][pStrength])/2000.0);
		
		if(CharacterInfo[damagedid][pHealth]-ilosc <= 0)
		{
			SetPVarInt(damagedid, "KillerWeaponID", weaponid);
			SetPVarInt(damagedid, "KillerID", playerid);
			
			CharacterInfo[damagedid][pDamaged] = true;
		}
		else
		{
			if(GetPVarInt(damagedid, "KillerWeaponID"))
			{
				DeletePVar(damagedid, "KillerWeaponID");
				DeletePVar(damagedid, "KillerID");
			}
		}
		
		SetPlayerHP(damagedid, CharacterInfo[damagedid][pHealth]-ilosc);
	}
	
	if(IsPlayerInAnyVehicle(damagedid))
	{
		new vehicleid = GetPlayerVehicleID(damagedid);
		new model = GetVehicleModel(vehicleid);
		if(model == 509 || model == 510 || model == 481 || model == 586 || model == 581 || model == 521 || model == 468 || model == 463 || model == 462 || model == 461 || model == 522)
			RemovePlayerFromVehicle(playerid);
	}
	
	CharacterInfo[damagedid][pDamageTook] = 300;
	
	CharacterInfo[damagedid][pNickDamageTook] = true;
	UpdatePlayer3DTextNick(damagedid);
	
	SetTimerEx("DamageColorNickDisable", 1500, false, "i", damagedid);
	
	if(weaponid)
	{
		CharacterInfo[damagedid][pLastDMG] = ilosc;
		CharacterInfo[damagedid][pLastHB] = bodypart;
		CharacterInfo[damagedid][pLastWEAP] = weaponid;
	}
	
	return 1;
}

public OnPlayerModelSelection(playerid, response, listid, modelid)
{
	if(listid == maleskinlist || listid == femaleskinlist)
	{
	    if(response)
	    {
	    	if(CharacterInfo[playerid][pCash] < 100)
	    		return msg_error(playerid, "Nie posiadasz wystarczaj¹cej iloœci gotówki. Ubranie kosztuje $100.");
			
		    msg_info(playerid, "Ubranie kupione pomyœlnie.");
			
			new name[16];
			format(name, sizeof(name), "Ubranie (%d)", modelid);
			StworzPrzedmiot(OWNER_PLAYER, CharacterInfo[playerid][pUID], name, ITEM_TYPE_CLOTH, modelid, 1, 1);
			
	    	GivePlayerCash(playerid, -100);
	    }
	}
	else if(listid == doczepialne_0 || listid == doczepialne_1 || listid == doczepialne_2 || listid == doczepialne_3 || listid == doczepialne_4)
	{
		if(response)
		{
			new type;
			new boneid;
			new name[32];
			
			if(CharacterInfo[playerid][pCash] < 30)
	    		return msg_error(playerid, "Nie posiadasz wystarczaj¹cej iloœci gotówki. Przedmiot doczepialny kosztuje $30");
			
			switch(modelid)
			{
				case 18891,18892,18893,18895,18896,18897,18898,18899,18901,18902,18903,18904,18939,18941,18940,18942,18943,18955,18956,18957,18958,18959,19093,19161,18926,18927,18928,18929,18930,18931,18932,18933,18934,18935,18961,18964:
				{
					type = ITEM_TYPE_ATTACHED;
					boneid = 2;
					format(name, sizeof(name), "Nakrycie na g³owê");
				}
				case 19095,18962,19097,19096,19098,18639,18947,18944,18948,18945,18949,18946,18950,18951,18971,18969,18968,19067,19068,19069,18954,18953:
				{
					type = ITEM_TYPE_ATTACHED;
					boneid = 2;
					format(name, sizeof(name), "Kapelusz");
				}
				case 18645,18976,18977,18978,18974:
				{
					type = ITEM_TYPE_ATTACHED;
					boneid = 2;
					format(name, sizeof(name), "Kask motocyklowy");
				}
				case 19006,19007,19010,19008,19009,19011,19012,19013,19014,19015,19016,19017,19018,19019,19020,19021,19022,19023,19024,19025,19026,19027,19028,19029,19030,19031,19032,19033,19034,19035,19138,19139,19140:
				{
					type = ITEM_TYPE_ATTACHED;
					boneid = 2;
					format(name, sizeof(name), "Okulary");
				}
				case 19039,19040,19041,19042,19043,19044,19045,19046,19047,19048,19049,19050,19051,19052,19053:
				{
					type = ITEM_TYPE_ATTACHED;
					boneid = 5;
					format(name, sizeof(name), "Zegarek na rêkê");
				}
				case 19163,19036,19037,19038,18911,18912,18913,18914:
				{
					type = ITEM_TYPE_MASKA;
					boneid = 2;
					format(name, sizeof(name), "Kominiarka");
				}
				case 19559:
				{
					type = ITEM_TYPE_ATTACHED;
					boneid = 1;
					format(name, sizeof(name), "Plecak");
				}
				case 19624,1210,18635:
				{
					type = ITEM_TYPE_ATTACHED;
					boneid = 6;
					
					switch(modelid)
					{
						case 19624,1210:
							format(name, sizeof(name), "Walizka");
						case 18635:
							format(name, sizeof(name), "M³otek");
					}
				}
			}
			
			GivePlayerCash(playerid, -30);
			StworzPrzedmiot(OWNER_PLAYER, CharacterInfo[playerid][pUID], name, type, modelid, boneid, 1);
			msg_info(playerid, "Przedmiot doczepialny zosta³ zakupiony, znajdziesz go pod /p.");
		}
	}
	return 1;
}
public OnPlayerEnterDynamicArea(playerid, areaid)
{
	if(areaid == AREA_GOV_DOCS)
	{
		if(SettingInfo[sGovBots])
		{
			new string[256];
			if(CharacterInfo[playerid][pDocs] & DOC_ID)
				format(string, sizeof(string), "{02AD38}Dowód osobisty\t{FCDF1E}$%d", SettingInfo[sDocID]);
			else
				format(string, sizeof(string), "{FFFFFF}Dowód osobisty\t{FCDF1E}$%d", SettingInfo[sDocID]);

			if(CharacterInfo[playerid][pDocs] & DOC_DRIVER)
				format(string, sizeof(string), "%s\n{02AD38}Prawo jazdy\t{FCDF1E}$%d", string, SettingInfo[sDocDriver]);
			else
				format(string, sizeof(string), "%s\n{FFFFFF}Prawo jazdy\t{FCDF1E}$%d", string, SettingInfo[sDocDriver]);

			if(CharacterInfo[playerid][pDocs] & DOC_PILOT)
				format(string, sizeof(string), "%s\n{02AD38}Licencja pilota\t{FCDF1E}$%d", string, SettingInfo[sDocPilot]);
			else
				format(string, sizeof(string), "%s\n{FFFFFF}Licencja pilota\t{FCDF1E}$%d", string, SettingInfo[sDocPilot]);
			
			format(string, sizeof(string), "%s\n{FFFFFF}Rejestracja pojazdu\t{FCDF1E}$%d", string, SettingInfo[sPlateCharge]);
			
			format(string, sizeof(string), "%s\n{FFFFFF}Rejestracja biznesu\t{FCDF1E}$%d", string, SettingInfo[sGroupRegisterCharge]);

			ShowPlayerDialog(playerid, D_DOCS, DIALOG_STYLE_TABLIST,DEF_NAME" » dokumenty", string, "Wybierz", "Zamknij");
		}
		else
			SendClientMessage(playerid, COLOR_GREEN, "[GOV] Aktualnie automatyczne boty s¹ wy³¹czone, przyjdŸ w godzinach otwarcia urzêdu (17:00 - 22:00)!");
	}
	else if(areaid == AREA_GOV_JOBS)
	{
		ShowPlayerDialog(playerid, D_GOV_JOBS, DIALOG_STYLE_LIST, DEF_NAME" » praca dorwycza", "Pracownik na magazynie", "Wybierz", "WyjdŸ");
	}
	else if(!GetPlayerVehicleID(playerid) && !(CharacterInfo[playerid][pStatus] & STATUS_MP3) )
	{
		ForeachPlayer(i)
		{
			if(GetPVarType(i, "bboxareaid"))
			{
				new station[128];
				GetPVarString(i, "BoomboxURL", station, sizeof(station));
				if(areaid == GetPVarInt(i, "bboxareaid"))
				{
					PlayAudioStreamForPlayer(playerid, station, GetPVarFloat(i, "bposX"), GetPVarFloat(i, "bposY"), GetPVarFloat(i, "bposZ"), 30.0, 1);
					return 1;
				}
			}
		}
	}
	return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	if(playertextid==ACCEPT[playerid])
		cmd_akceptuj(playerid,"");
	else if(playertextid==REJECT[playerid])
		cmd_odrzuc(playerid,"");
	return 1;
}
public OnPlayerEnterCheckpoint(playerid)
{
	if(GetPVarInt(playerid,"Transport")==1)
	{
		if(!IsPlayerOnDutyInGroup(playerid, GROUP_LOGISTIC) || DutyGroup[playerid] != GetPVarInt(playerid, "TransportGroup"))
			return msg_error(playerid,"Nie jesteœ na s³uzbie odpowiedniej grupy.");
		new model=GetVehicleModel(GetPlayerVehicleID(playerid));
		new vehicleid=GetPlayerVehicleID(playerid);
		new trailer=GetVehicleModel(GetVehicleTrailer(vehicleid));
		if(!((model==514 || model==515 || model==403) && (trailer==435 || trailer == 591 || trailer==450)))
			return msg_error(playerid,"Aby wykonaæ zlecenie musisz znajdowaæ siê w trucku z naczep¹.");
		DisablePlayerCheckpoint(playerid);
		FreezePlayer(playerid);
		SetTimerEx("TransportLoad",10000,false,"i",playerid);
		Tip(playerid,10,"Trwa zaladunek.");
	}
	else if(GetPVarInt(playerid,"Transport")==2)
	{
		if(!IsPlayerOnDutyInGroup(playerid, GROUP_LOGISTIC) || DutyGroup[playerid] != GetPVarInt(playerid, "TransportGroup"))
			return msg_error(playerid, "Nie jesteœ na s³uzbie odpowiedniej grupy.");
		new model=GetVehicleModel(GetPlayerVehicleID(playerid));
		new vehicleid=GetPlayerVehicleID(playerid);
		new trailer=GetVehicleModel(GetVehicleTrailer(vehicleid));
		if(!((model==514 || model==515 || model==403) && (trailer==435 || trailer == 591 || trailer==450)))
			return msg_error(playerid,"Aby wykonaæ zlecenie musisz znajdowaæ siê w trucku z naczep¹.");
		
		FreezePlayer(playerid);
		SetTimerEx("UnfreezePlayer", 2000, false, "i", playerid);
		
		DisablePlayerCheckpoint(playerid);
		new groupid=DutyGroup[playerid];
		new cash=random(101)+300;
		new commission=GetMemberCommission(playerid,groupid);
		if(commission > 0)
		{
			commission= floatround( (float(cash)/100.0) * float(commission));
			cash-=commission;
			CharacterInfo[playerid][pCredit] += commission;
			SavePlayerStats(playerid,SAVE_PLAYER_BASIC);
			msg_infoFormat(playerid,128,"Towar dostarczony. Na konto grupy wp³ynê³o $%d.\nTwoja prowizja: $%d.",cash,commission);
		}
		else
			msg_infoFormat(playerid,64,"Towar dostarczony. Na konto grupy wp³ynê³o $%d.",cash);

		GiveGroupCash(groupid,cash);

		LogGroupOffer(playerid,groupid,"Transport towaru",cash);
		DeletePVar(playerid,"Transport");
		DeletePVar(playerid,"TransportGroup");
	}
	else if(GetPVarInt(playerid,"TransportFuel") > 0)
	{
		if(!IsPlayerOnDutyInGroup(playerid, GROUP_LOGISTIC))
			return msg_error(playerid, "Nie jesteœ na s³uzbie odpowiedniej grupy.");
		new model=GetVehicleModel(GetPlayerVehicleID(playerid));
		new vehicleid=GetPlayerVehicleID(playerid);
		new trailer=GetVehicleModel(GetVehicleTrailer(vehicleid));
		if(!((model==514 || model==515 || model==403) && trailer==584) )
			return msg_error(playerid,"Aby wykonaæ zlecenie musisz znajdowaæ siê w trucku z cystern¹.");
		DisablePlayerCheckpoint(playerid);
		FreezePlayer(playerid);
		SetTimerEx("FuelLoad",10000,false,"i",playerid);
		Tip(playerid,10,"Trwa zaladunek.");
	}
	else if(GetPVarInt(playerid,"TransportFuel") < 0)
	{
		if(!IsPlayerOnDutyInGroup(playerid, GROUP_LOGISTIC))
			return msg_error(playerid, "Nie jesteœ na s³uzbie odpowiedniej grupy.");
		new model=GetVehicleModel(GetPlayerVehicleID(playerid));
		new vehicleid=GetPlayerVehicleID(playerid);
		new trailer=GetVehicleModel(GetVehicleTrailer(vehicleid));
		if(!((model==514 || model==515 || model==403) && trailer==584) )
			return msg_error(playerid,"Aby wykonaæ zlecenie musisz znajdowaæ siê w trucku z cystern¹.");
		DisablePlayerCheckpoint(playerid);
		FreezePlayer(playerid);
		SetTimerEx("FuelLoad",10000,false,"i",playerid);
		Tip(playerid,10,"Trwa rozladunek.");
	}
	else if(GetPVarInt(playerid,"pJob") == JOB_WEARHOUSE)
	{
		DisablePlayerCheckpoint(playerid);
		if(CharacterInfo[playerid][pJobPhase] == 1)
		{
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
			SetPlayerAttachedObject(playerid, SLOT_JOB, 2969, 5, 0.0769,0.1010,0.1790,-84.4,-8.099,113.099);
			SetPlayerCheckpoint(playerid,2762.8875,-2344.4080,13.6421,1.5);
			CharacterInfo[playerid][pJobPhase]=2;
		}
		else if(CharacterInfo[playerid][pJobPhase] == 2)
		{
			new point=random(11);
			SetPlayerCheckpoint(playerid, DocksJob[point][posX], DocksJob[point][posY], DocksJob[point][posZ], 1.5);
			CharacterInfo[playerid][pJobPhase]=1;
			RemovePlayerAttachedObject(playerid, SLOT_JOB);
			SetPlayerSpecialAction(playerid,0);
			GivePlayerCash(playerid,CASH_WEARHOUSE);
			CharacterInfo[playerid][pJobCount]++;
			SavePlayerStats(playerid,SAVE_PLAYER_JOBS);
			if(CharacterInfo[playerid][pJobCount] >= NAX_JOB_WEARHOUSE_REPS)
			{
				msg_info(playerid,"Wyczerpa³eœ dzisiejszy limit pracy. Wróæ jutro.");
				EndJob(playerid);
			}
		}
	}
	else if(CharacterInfo[playerid][pCheckpoint])
	{
		DisablePlayerCheckpoint(playerid);
		CharacterInfo[playerid][pCheckpoint]=0;
	}
	return 1;
}
public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	if(GetPVarInt(playerid,"pTaxiDriver"))
	{
		new driver=GetPVarInt(playerid,"pTaxiDriver");
		if(driver==-1) driver=0;
		if(CharacterInfo[driver][pCheckpoint])
			DisablePlayerCheckpoint(playerid);
		SetPlayerCheckpoint(driver, fX, fY, fZ, 5.0);
		SendClientMessage(driver,GetGroupColor(DutyGroup[playerid]),"Klient wybra³ punkt docelowy. Zosta³ on pokazany na mapie");
	}
	return 1;
}
public OnVehicleMod(playerid, vehicleid, componentid)
{
	return 1;
}
public OnVehicleSirenStateChange(playerid, vehicleid, newstate)
{
	new vehid=GetVehicleUID(vehicleid);
    new syrenaid=Siren(vehid);
    if(newstate)
    {
    	if(syrenaid && !VehicleInfo[vehid][vPolice] && (VehicleInfo[vehid][vModel] < 596 || VehicleInfo[vehid][vModel] > 599))
    	{
			VehicleInfo[vehid][vPolice]=CreateDynamicObject(SyrenaPos[syrenaid][sObject], 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
			AttachDynamicObjectToVehicle(VehicleInfo[vehid][vPolice], VehicleInfo[vehid][vSAMPID],SyrenaPos[syrenaid][sX], SyrenaPos[syrenaid][sY], SyrenaPos[syrenaid][sZ], 0.0, 0.0, 0.0);
    	}
    }
    else
	{
		if(VehicleInfo[vehid][vPolice])
		{
			DestroyDynamicObject(VehicleInfo[vehid][vPolice]);
			VehicleInfo[vehid][vPolice]=0;
		}
	}
    return 1;
}

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
	if(response)
	{
		new uid=CharacterInfo[playerid][pAttached][index];
		if(uid<0)
			return 1;
		new query[256],bool:exist;
		format(query, sizeof(query), "SELECT `UID` FROM `srv_attached` WHERE `UID`='%d'", uid);
		mysql_query(query);
		mysql_store_result();
		if(mysql_num_rows())
			exist=true;
		mysql_free_result();

		if(!exist)
		{
			format(query,sizeof(query),"INSERT INTO `srv_attached` VALUES ('%d','%d','%d','%d','%f','%f','%f','%f','%f','%f','%f','%f','%f')", uid, index, modelid, boneid, 
			fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);		
		}
		else
			format(query,sizeof(query),"UPDATE `srv_attached` SET `x`='%f',`y`='%f',`z`='%f',`rx`='%f',`ry`='%f',`rz`='%f',`sx`='%f',`sy`='%f',`sz`='%f' WHERE `uid`='%d'",fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ,uid);

		mysql_query(query);	
		Tip(playerid,3,"Pozycja obiektu zapisana");
	}
	
	return 1;
}

public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z)
{
	new vehuid = GetVehicleUID(vehicleid);
	
	if(vehuid && VehicleInfo[vehuid][vUID] && VehicleInfo[vehuid][vSpawned] && VehicleInfo[vehuid][vHandBrake])
	{
		new Float:pos[3];
		new Float:angle;
		GetVehiclePos(vehicleid, pos[0], pos[1], pos[2]);
		GetVehicleZAngle(vehicleid, angle);
		
		if(pos[0] != VehicleInfo[vehuid][vHB][0] || pos[1] != VehicleInfo[vehuid][vHB][1] || pos[2] != VehicleInfo[vehuid][vHB][2] || angle != VehicleInfo[vehuid][vHB][3])
		{
			SetVehiclePos(vehicleid, VehicleInfo[vehuid][vHB][0], VehicleInfo[vehuid][vHB][1], VehicleInfo[vehuid][vHB][2]);
			SetVehicleZAngle(vehicleid, VehicleInfo[vehuid][vHB][3]);
		}
	}
	
	return 1;
}
