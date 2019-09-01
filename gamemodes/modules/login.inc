forward OnPlayerLogin(playerid, charid);
forward ClearCache(playerid);
forward PlayerTogQsOffOnLogin(playerid);

public OnPlayerLogin(playerid, charid)
{
	new query[512],
	last_online,
	logged,
	data[64];
	
	mysql_query_format("SELECT * FROM `srv_characters` WHERE `player_uid` = '%d' LIMIT 1", charid);
	
	mysql_store_result();
	if(mysql_num_rows())
	{
		mysql_fetch_row_format(query);
		sscanf(query,  "p<|>dds[24]ddddddfddddfffdddddddddddddddddddddddddddddfddd",
		CharacterInfo[playerid][pUID],
		CharacterInfo[playerid][pGID],
		CharacterInfo[playerid][pNick],
		CharacterInfo[playerid][pAge],
		CharacterInfo[playerid][pSex],
		CharacterInfo[playerid][pSkin],
		CharacterInfo[playerid][pCash],
		CharacterInfo[playerid][pHours],
		CharacterInfo[playerid][pMinutes],
		CharacterInfo[playerid][pHealth],
		CharacterInfo[playerid][pAdmin],
		CharacterInfo[playerid][pHide],
		CharacterInfo[playerid][pCredit],
		CharacterInfo[playerid][pBW],
		CharacterInfo[playerid][pPos][0],
		CharacterInfo[playerid][pPos][1],
		CharacterInfo[playerid][pPos][2],
		CharacterInfo[playerid][pVW],
		CharacterInfo[playerid][pInt],
		CharacterInfo[playerid][pTog],
		CharacterInfo[playerid][pBlock],
		CharacterInfo[playerid][pGlod],
		CharacterInfo[playerid][pSpawnOption],
		CharacterInfo[playerid][pSpawnOptionHouseID],
		CharacterInfo[playerid][pBlockNoGun],
		CharacterInfo[playerid][pBlockNoCar],
		CharacterInfo[playerid][pBlockNoOOC],
		CharacterInfo[playerid][pBlockNoRun],
		CharacterInfo[playerid][pJail],
		CharacterInfo[playerid][pJailTime],
		logged,
		last_online,
		CharacterInfo[playerid][pOnlineToday],
		CharacterInfo[playerid][pJob],
		CharacterInfo[playerid][pJobCount],
		CharacterInfo[playerid][pDocs],
		CharacterInfo[playerid][pPhone],
		CharacterInfo[playerid][pKanal],
		CharacterInfo[playerid][pHotel],
		CharacterInfo[playerid][pPenaltyPoints],
		CharacterInfo[playerid][pStrength],
		CharacterInfo[playerid][pStrengthToday],
		CharacterInfo[playerid][pDriverPenalty],
		CharacterInfo[playerid][pCelebrity],
		CharacterInfo[playerid][pFightStyle],
		CharacterInfo[playerid][pSuplement],
		CharacterInfo[playerid][pLastDMG],
		CharacterInfo[playerid][pLastHB],
		CharacterInfo[playerid][pLastWEAP],
		CharacterInfo[playerid][pWalkStyle]);
		
		mysql_free_result();
		
		if(GetPVarInt(playerid, "CharacterGlobalID") && CharacterInfo[playerid][pGID] != GetPVarInt(playerid, "CharacterGlobalID"))
		{
			KickWithWait(playerid);
			return 1;
		}
		
		DeletePVar(playerid, "CharacterGlobalID");
		
		new logDirName[24];
		format(logDirName,sizeof(logDirName),"scriptfiles/logs/%d",CharacterInfo[playerid][pUID]);
		if(!dir_exists(logDirName))
		{
			dir_create(logDirName);
		}
		
		// Wczytywanie informacji OOC
		format(query,sizeof(query),"SELECT `members_display_name`, `score`,  `premium`, `warn`, `curse`, `aj` FROM `members` WHERE `member_id` = '%d'", CharacterInfo[playerid][pGID]);
		mysql_query(query);
		mysql_store_result();
		
		while(mysql_fetch_row_format(data, "|") == 1)
			sscanf(data, "p<|>s[32]ddddd", CharacterInfo[playerid][pGlobalNick], CharacterInfo[playerid][pGlobalScore], CharacterInfo[playerid][pPremium], CharacterInfo[playerid][pWarn], CharacterInfo[playerid][pCurse], CharacterInfo[playerid][pAJ]);
		
		mysql_free_result();
		
		if(CheckBan(playerid, CharacterInfo[playerid][pGID]))
		{
			msg_info(playerid,"Twoje konto jest niekatywne lub posiada aktywn¹ banicjê.\nJeœli jest to b³¹d - zapraszamy na forum.");
			KickWithWait(playerid);
		}
		else if((CharacterInfo[playerid][pBlock] & BLOCK_CHAR) || (CharacterInfo[playerid][pBlock] & BLOCK_CK))
		{
			msg_info(playerid,"Twoja postaæ zosta³a zablokowana lub uœmiercona.");
			KickWithWait(playerid);
		}		
		else if(CharacterInfo[playerid][pBlock] & BLOCK_BAN)
		{
			msg_info(playerid,"Twoja postaæ zosta³a zbanowana.");
			KickWithWait(playerid);
		}
		else
		{
			ForeachPlayer(i)
			{
				if(CharacterInfo[i][pGID] == CharacterInfo[playerid][pGID] && Logged[i])
				{
					msg_error(playerid, "Jedna z Twoich postaci jest ju¿ zalogowana na serwerze.");
					KickWithWait(playerid);
					break;
				}
			}
			
			format(query,sizeof(query),"UPDATE `srv_characters` SET `logged` = '1', `last_online` = '%d' WHERE `player_uid` = '%d'", gettime(), CharacterInfo[playerid][pUID]);
			mysql_query(query);
			
			format(query,sizeof(query),"INSERT INTO `srv_login_logs` VALUES ('%d','%d','%s','%d')", CharacterInfo[playerid][pGID], CharacterInfo[playerid][pUID], GetAccountIP(playerid), gettime());
			mysql_query(query);

			LoadPlayerGroups(playerid);
			
			if(!(CharacterInfo[playerid][pTog] & TOG_QS) && (gettime()-last_online < 900))
				CharacterInfo[playerid][pTog] += TOG_QS;
			
			if(Spawned[playerid] < 5)
				Spawned[playerid] = 5;
			
			SetPlayerSpawn(playerid);
			
			TogglePlayerSpectating(playerid, false);
			
			SpawnPlayer(playerid);
			
			if(CharacterInfo[playerid][pTog] & TOG_QS)
				SetTimerEx("PlayerTogQsOffOnLogin", 1500, false, "i", playerid);
			
			// Ustawianie HP
			SetPlayerHealth(playerid, CharacterInfo[playerid][pHealth]);
			SetPlayerScore(playerid, CharacterInfo[playerid][pGlobalScore]);
			
			// Aktualizacja gotówki
			ResetPlayerMoney(playerid);
			GivePlayerMoney(playerid, CharacterInfo[playerid][pCash]);
			
			//Skill broni
			SetPlayerSkillLevel(playerid, 0, 500);
			SetPlayerSkillLevel(playerid, 1, 999);
			SetPlayerSkillLevel(playerid, 2, 999);
			SetPlayerSkillLevel(playerid, 3, 999);
			SetPlayerSkillLevel(playerid, 4, 500);
			SetPlayerSkillLevel(playerid, 5, 500);
			SetPlayerSkillLevel(playerid, 6, 500);
			SetPlayerSkillLevel(playerid, 7, 999);
			SetPlayerSkillLevel(playerid, 8, 999);
			SetPlayerSkillLevel(playerid, 9, 999);
			SetPlayerSkillLevel(playerid, 10, 500);
			
			SetPlayerName(playerid, CharacterInfo[playerid][pNick]);
			
			switch(CharacterInfo[playerid][pFightStyle])
			{
				case 0:
					SetPlayerFightingStyle(playerid, FIGHT_STYLE_GRABKICK);
				case 1:
					SetPlayerFightingStyle(playerid, FIGHT_STYLE_BOXING);
				case 2:
					SetPlayerFightingStyle(playerid, FIGHT_STYLE_KUNGFU);
				case 3:
					SetPlayerFightingStyle(playerid, FIGHT_STYLE_KNEEHEAD);
				default:
					SetPlayerFightingStyle(playerid, FIGHT_STYLE_GRABKICK);
			}
			
			// Ustawienia TOG
			if(!(CharacterInfo[playerid][pTog] & TOG_NAME))
			{
				TextDrawShowForPlayer(playerid, TDEditor_TD[0]);
				TextDrawShowForPlayer(playerid, TDEditor_TD[1]);
			}
			
			if(!(CharacterInfo[playerid][pTog] & TOG_LSN))
			{
				TextDrawShowForPlayer(playerid, TD_LSN);
				TextDrawShowForPlayer(playerid, TD_LSN2);
			}
			
			if(IsPlayerGroupPerm(playerid, FLAG_GPS))
			{
				if(CharacterInfo[playerid][pTog] & TOG_STATUS)
				{
					PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][0]);
					
					PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][1]);
					PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][2]);
				}
			}
			
			if(IsPlayerInOfficialGroup(playerid) || IsPlayerInBuisnessGroup(playerid))
			{
				if(CharacterInfo[playerid][pTog] & TOG_STATUS)
				{
					PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][6]);
					
					PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][7]);
					PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][8]);
				}
			}
			
			// Aktualizacja g³odu
			FoodBar[playerid] = CreatePlayerProgressBar(playerid, 548.4, 28.0, 57.7, 4.5, COLOR_GREEN, 100.0);
			if(!(CharacterInfo[playerid][pTog] & TOG_GLOD))
			{
				ShowPlayerProgressBar(playerid, FoodBar[playerid]);
				
				SetPlayerProgressBarValue(playerid, FoodBar[playerid], CharacterInfo[playerid][pGlod]);
				UpdatePlayerProgressBar(playerid, FoodBar[playerid]);
			}

			//w³¹czenie telefonu
			new phone = CharacterInfo[playerid][pPhone];
			if(phone && ItemInfo[phone][iType] == ITEM_TYPE_TELEFON && ItemInfo[phone][iOwnerTyp] == OWNER_PLAYER &&  ItemInfo[phone][iOwner] == CharacterInfo[playerid][pUID])
			{
				ItemInfo[phone][iUsed] = 1;
				format(query,sizeof(query),"UPDATE `srv_items` SET `used` = 1 WHERE `uid` = '%d' LIMIT 1", phone);
				mysql_query(query);
			}
			else
				CharacterInfo[playerid][pPhone] = 0;
			
			// Informacje startowe //CC990
			new first_string[144]; 
			format(first_string, sizeof(first_string),"** {ffffff}Witaj %s na mySantos Role Play!", CharacterInfo[playerid][pGlobalNick]);
			SendClientMessage(playerid, COLOR_GREEN, first_string);
			format(first_string, sizeof(first_string),"** {ffffff}Zalogowano siê na postaæ: {02AD38}%s {ffffff}(ID: %d, UID: %d)", PlayerName2(playerid), playerid, CharacterInfo[playerid][pUID]);
			SendClientMessage(playerid, COLOR_GREEN, first_string);
			
			if(CharacterInfo[playerid][pAdmin])
			{
				switch(CharacterInfo[playerid][pAdmin])
				{
					case 1:
						format(first_string,sizeof(first_string),"** {FFFFFF}Status konta: {FF9900}Opiekun");
					case 2,3,4:
						format(first_string,sizeof(first_string),"** {FFFFFF}Status konta: {8B00B0}GameMaster");
					case 5:
						format(first_string,sizeof(first_string),"** {FFFFFF}Status konta: {B00000}Administrator");
					case 6:
						format(first_string,sizeof(first_string),"** {FFFFFF}Status konta: {FF0000}Administrator G³ówny");	
				}
				SendClientMessage(playerid, COLOR_GREEN, first_string);
			}
			else if(IsPlayerPremium(playerid)) SendClientMessage(playerid, COLOR_GREEN, "** {ffffff}Status konta: {FCDF1E}Premium{FFFFFF}.");
			else SendClientMessage(playerid, COLOR_GREEN, "** {ffffff}Status konta: U¿ytkownik (brak premium).");
			
			#if defined DEBUG_MODE
				SendClientMessage(playerid, COLOR_RED, "Tryb testowy aktywny!");
			#endif
			
			for(new i=1;i<MAX_PLAYER_GROUPS;i++)
				if(MemberGroup[playerid][i][GroupID] && strlen(GroupInfo[MemberGroup[playerid][i][GroupID]][gNotice])>4)
					SendClientMessageFormat(playerid, GetGroupColor(MemberGroup[playerid][i][GroupID]), "[GRUPA][%s] Og³oszenie: %s", GroupInfo[MemberGroup[playerid][i][GroupID]][gTag], GroupInfo[MemberGroup[playerid][i][GroupID]][gNotice]);
			
			if(SettingInfo[sPremiumEventDays] && !IsPlayerPremium(playerid))
			{
				SendClientMessageFormat(playerid, COLOR_YELLOW, "[INFO] W zwi¹zku z trwaj¹cym aktualnie eventem otrzymujesz KONTO PREMIUM na okres %d dni.", SettingInfo[sPremiumEventDays]);
				
				GivePlayerPremium(playerid, SettingInfo[sPremiumEventDays]);
			}
			
			if(IsPlayerPremium(playerid))
			{
				CharacterInfo[playerid][pNickColor] = COLOR_PREMIUM;
				SetPlayerColor(playerid, COLOR_PREMIUM);
			}
			else
			{
				CharacterInfo[playerid][pNickColor] = COLOR_USER;
				SetPlayerColor(playerid, COLOR_USER);
			}
			
			Attach3DTextLabelToPlayer(NameTags[playerid], playerid, 0.0, 0.0, 0.2);
			
			Attach3DTextLabelToPlayer(Description[playerid], playerid, 0.0, 0.0, -0.6);
			
			if(!IsPlayerNPC(playerid))
				Logged[playerid] = true;
			
			SetPlayerMapIcon(playerid, 0, 1776.1733, -1114.6, 24.11, 55, 0, MAPICON_GLOBAL);
			//ICONID 10-30 zajête na cornery
			
			for(new d = 0; d<MAX_DOORS_MAPICONS; d++)
			{
				if(DOORS_MAPICONS[playerid][d] != -1)
					DestroyDynamicMapIcon(DOORS_MAPICONS[playerid][d]);
				
				DOORS_MAPICONS[playerid][d] = -1;
			}
			
			for(new i = 0; i<_DOOR_COUNT; i++)
			{
				if(DoorsInfo[i][dIconID])
				{
					new icon = -1;
					for(new s = 0; s<MAX_DOORS_MAPICONS; s++)
					{
						if(DOORS_MAPICONS[playerid][s] == -1)
						{
							icon = s;
							break;
						}
					}
					
					DOORS_MAPICONS[playerid][icon] = CreateDynamicMapIcon(DoorsInfo[i][dEnterX], DoorsInfo[i][dEnterY], DoorsInfo[i][dEnterZ], DoorsInfo[i][dIconID], 0, -1, -1, playerid, -1, MAPICON_LOCAL );
				}
			}
			
			new gangid;
			if((gangid = IsPlayerInGroupType(playerid,GROUP_GANG)))
				for(new i=1;i<MAX_CORNERS;i++)
					if(CornerInfo[i][cOwner]==gangid)
						SetPlayerMapIcon(playerid, CornerInfo[i][cIcon], CornerInfo[i][cPosX], CornerInfo[i][cPosY], CornerInfo[i][cPosZ], 23, 0, MAPICON_LOCAL_CHECKPOINT);
		}
	}

	return 1;
}

public ClearCache(playerid)
{
	memcpy(CharacterInfo[playerid], ClearInfo, 0, sizeof(ClearInfo)*4, sizeof(CharacterInfo[]));

	CharacterInfo[playerid][pTaxiPassenger] = INVALID_PLAYER_ID;
	CharacterInfo[playerid][pIgnore] = INVALID_PLAYER_ID;

	if(Description[playerid] != Text3D:INVALID_3DTEXT_ID)
	{
		DestroyDynamic3DTextLabel(Description[playerid]);
		Description[playerid] = Text3D:INVALID_3DTEXT_ID;
	}
	
	for(new i = 0; i<MAX_WS_MAPICONS; i++)
	{
		if(WS_MAPICONS[playerid][i] != -1)
			DestroyDynamicMapIcon(WS_MAPICONS[playerid][i]);
		
		WS_MAPICONS[playerid][i] = -1;
	}
	
	if(!CharacterInfo[playerid][p911Icon])
		DestroyDynamicMapIcon(CharacterInfo[playerid][p911Icon]);
	
	CharacterInfo[playerid][p911] = -1;
	
	MemberGroup[playerid][1][GroupID] = 
	MemberGroup[playerid][2][GroupID] = 
	MemberGroup[playerid][3][GroupID] = 
	MemberGroup[playerid][4][GroupID] = 
	MemberGroup[playerid][5][GroupID] = 0;

	DutyGroup[playerid] = 
	DutyGroupTime[playerid] = 
	PlayerDoor[playerid] = 	
	Checkpoint[playerid] = 
	VehSpawned[playerid] =
	PlayerEditObject[playerid] = 
	Spawned[playerid] = 0;
	
	IsChecked[playerid] = false;
	Logged[playerid] = false;
	Rozmawia[playerid] = false;
	
	if(Streamer_IsToggleIdleUpdate(playerid))
		Streamer_ToggleIdleUpdate(playerid, 0);
	
	Update3DTextLabelText(Description[playerid], COLOR_WHITE, " ");
	
	RozmawiaZ[playerid] = INVALID_PLAYER_ID;
	
	PlayerTextDrawDestroy(playerid, DoorsTD[playerid]);
	PlayerTextDrawDestroy(playerid, EditObjectText[playerid]);
	PlayerTextDrawDestroy(playerid, OFFER[playerid]);
	PlayerTextDrawDestroy(playerid, ACCEPT[playerid]);
	PlayerTextDrawDestroy(playerid, REJECT[playerid]);
	
	for(new x = 0; x < 9; x++)
		PlayerTextDrawDestroy(playerid, TDEditor_PTD[playerid][x]);
	
	for(new x = 0; x < 10; x++)
		PlayerTextDrawDestroy(playerid, Speedometer[playerid][x]);
}

stock CheckBan(playerid, globalid)
{
	new query[128],gid,group;
	format(query,sizeof(query),"SELECT * FROM `srv_bans` WHERE `ip`='%s' OR `player_global_id`='%d'", GetAccountIP(playerid), globalid);
	mysql_query(query);
	
	mysql_store_result();
	
	if(mysql_num_rows())
	{
		gid=true;
		format(query,sizeof(query),"INSERT INTO `srv_falied_logins` VALUES (NULL,'%d','%d','%s','%d','Ban IG')", CharacterInfo[playerid][pUID],CharacterInfo[playerid][pGID], GetAccountIP(playerid), gettime());
		mysql_query(query);
	}
	mysql_free_result();
	if(gid) return true;
	if(globalid)
	{
		format(query,sizeof(query),"SELECT `member_group_id` FROM `members` WHERE `member_id` ='%d'", globalid);
		mysql_query(query);
		mysql_store_result();
		mysql_fetch_row_format(query);
		group=strval(query);
		mysql_free_result();
		if(group==5)
		{
			
			format(query,sizeof(query),"INSERT INTO `srv_falied_logins` VALUES (NULL,'%d','%d','%s','%d','Ban forum')",  CharacterInfo[playerid][pUID],CharacterInfo[playerid][pGID], GetAccountIP(playerid), gettime());
			mysql_query(query);
			return true;

		}
		else if(group==1)
		{
			format(query,sizeof(query),"INSERT INTO `srv_falied_logins` VALUES (NULL,'%d','%d','%s','%d','Nieaktywne konto na forum')",  CharacterInfo[playerid][pUID],CharacterInfo[playerid][pGID], GetAccountIP(playerid), gettime());
			mysql_query(query);
			return true;
		}
	}
	format(query,sizeof(query),"SELECT * FROM `banfilters` WHERE `ban_content`='%s'", GetAccountIP(playerid));
	mysql_query(query);
	
	mysql_store_result();
	
	if(mysql_num_rows())
	{
		gid=true;
		format(query,sizeof(query),"INSERT INTO `srv_falied_logins` VALUES (NULL,'%d','%d','%s','%d','Zbanowane IP forum')", CharacterInfo[playerid][pUID],CharacterInfo[playerid][pGID], GetAccountIP(playerid), gettime());
		mysql_query(query);

	}
	mysql_free_result();

	


	return gid;
}

stock PreloadAllAnimLibs(playerid)
{
  ApplyAnimation(playerid,"BOMBER","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"RAPPING","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"SHOP","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"BEACH","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"SMOKING","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"FOOD","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"ON_LOOKERS","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"DEALER","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"CRACK","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"CARRY","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"COP_AMBIENT","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"PARK","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"INT_HOUSE","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"FOOD","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"PED","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"SWEET","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"FREEWEIGHTS","null",0.0,0,0,0,0,0);
		
  ApplyAnimation(playerid,"AIRPORT","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"Attractors","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"BAR","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"BASEBALL","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"BD_FIRE","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"benchpress","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"BF_injection","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"BLOWJOBZ","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"BOX","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"BSKTBALL","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"BUDDY","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"CAMERA","null",0.0,0,0,0,0,0);
  ApplyAnimation(playerid,"CARRY","null",0.0,0,0,0,0,0);

  ClearAnimations(playerid);
  return 1;
}

public PlayerTogQsOffOnLogin(playerid)
{
	CharacterInfo[playerid][pTog] -= TOG_QS;
	SavePlayerStats(playerid, SAVE_PLAYER_OPTION);
	return 1;
}