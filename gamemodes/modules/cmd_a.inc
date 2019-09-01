CMD:apomoc(playerid,params[])
{
	if(!CharacterInfo[playerid][pAdmin]) return 1;
	
	SendClientMessage(playerid, COLOR_RED, "** Panel Administratora **");
	SendClientMessage(playerid, COLOR_ORANGE, "Opiekun:{FFFFFF} /zamroz, /odmroz, /slap, /tpdo, /a, /rep, /duty, /spec, /aprzeszukaj, /stats [id], /info, /nick, /askin");
	SendClientMessage(playerid, COLOR_ORANGE, "Opiekun:{FFFFFF} /tptutaj, /tpspawn, /tpcentrum, /krzakusun, /kick, /hp, /bw, /unbw, /glob, /ado, /pozar, /nauka, /vmodel, /mtextoff");
	if(CharacterInfo[playerid][pAdmin] > 1)
		SendClientMessage(playerid, COLOR_GM, "GameMaster 1:{FFFFFF} /tp,  /aj, /relog, /dekoduj, /vw");
	if(CharacterInfo[playerid][pAdmin] > 2)
		SendClientMessage(playerid, COLOR_GM, "GameMaster 2:{FFFFFF} /block, /ban, /warn, /nogun, /nocar, /norun, /noooc");
	if(CharacterInfo[playerid][pAdmin] > 3)
		SendClientMessage(playerid, COLOR_GM, "GameMaster 3:{FFFFFF} /unaj, /gamescore, /klatwa, /glod");
	if(CharacterInfo[playerid][pAdmin] > 4)
	{
		SendClientMessage(playerid, COLOR_DARKRED, "Administrator:{FFFFFF} /pos, /unwarn, /bany, /podglad, /int, /a3d, /czas, /pogoda");
		SendClientMessage(playerid, COLOR_DARKRED, "Administrator:{FFFFFF} /apojazd, /adrzwi, /agrupa, /aprzedmiot, /aprodukt, /abus, /mowner");
	}
	if(CharacterInfo[playerid][pAdmin] > 5) SendClientMessage(playerid, COLOR_RED, "Administrator G³ówny:{FFFFFF} /set, /restart, /premium, /gotoobj, /celebryta, /profiler, /clearvw, /countobj, /limits");
	
	return 1;
}

CMD:pos(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin] < 5) return 1;

	new vw, int;
	new Float:Pos[3];
	
	if(sscanf(params, "fffdd", Pos[0], Pos[1], Pos[2], vw, int))
		return msg_usage(playerid,"U¿yj: /pos [PosX] [PosY] [PosZ] [VW] [INT]");

	SetPlayerVirtualWorld(playerid, vw);
	SetPlayerInterior(playerid, int);
	SetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
	
	return 1;
}

CMD:zamroz(playerid,params[])
{
	if(!CharacterInfo[playerid][pAdmin]) return 1;

	new playerid2;
	if(sscanf(params, "i", playerid2))
		return msg_usage(playerid,"U¿yj: /zamroz [ID gracza]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		if(CharacterInfo[playerid2][pBW] || CharacterInfo[playerid2][pWounded])
			return msg_error(playerid,"Gracz o podanym ID ma status BW.");
		
		FreezePlayer(playerid2);
		
		SendClientMessageFormat(playerid, COLOR_RED, "[AI] Zamrozi³eœ gracza o ID: %d.", playerid2);
		msg_infoFormat(playerid2, 64, "Zosta³eœ zamro¿ony przez %s(%d)!", CharacterInfo[playerid][pGlobalNick], playerid);
	}
	
	return 1;
}

CMD:odmroz(playerid, params[])
{
	if(!CharacterInfo[playerid][pAdmin]) return 1;

	new playerid2;
	if(sscanf(params, "i", playerid2))
		return msg_usage(playerid,"U¿yj: /odmroz [ID gracza]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		if(CharacterInfo[playerid2][pBW] || CharacterInfo[playerid2][pWounded])
			return msg_error(playerid,"Gracz o podanym ID ma status BW.");
		
		UnfreezePlayer(playerid2);
		
		SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Odmrozi³eœ gracza o ID: %d.", playerid2);
		msg_infoFormat(playerid2, 64,"Zosta³eœ odmro¿ony przez %s(%d)!", CharacterInfo[playerid][pGlobalNick], playerid);
	}
	
	return 1;
}

CMD:set(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 6) return 1;
	new comm1[32], comm2[16];
	if(sscanf(params, "s[32]S()[16]", comm1, comm2))
		return msg_usage(playerid,"U¿yj: /set [admin | cash | bank | hours | minutes | skin | score | pogoda | czas | sila | stylwalki]");
	else
	{
		if(!strcmp(comm1, "admin", true))
		{
			new playerid2, level, string[128];
			if(sscanf(comm2, "id", playerid2, level))
				return msg_usage(playerid,"U¿yj: /set admin [ID gracza] [poziom (1-6)]\n\n1 - Opiekun \n2 - GameMaster poziomu 1\n3 - GameMaster poziomu 2\n4 - GameMaster poziomu 3\n5 - Administrator \n6 - Zarz¹d");
			else
			{
				if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
					return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
				if(level > 6 || level < 0)
					return msg_error(playerid,"Wprowadzony poziom administratora jest nieprawid³owy.");
				
				CharacterInfo[playerid2][pAdmin] = level;

				if(!level && CharacterInfo[playerid2][pAdminDuty])
				{
					CharacterInfo[playerid2][pAdminDuty] = false;
					if(IsPlayerPremium(playerid)) CharacterInfo[playerid][pNickColor] = COLOR_PREMIUM;
					else CharacterInfo[playerid][pNickColor] = COLOR_USER;
				}
				
				SavePlayerStats(playerid2, SAVE_PLAYER_ADMIN);
				
				format(string, sizeof(string), "Poziom administratora %s (ID: %d) zosta³ zmieniony na %d.", PlayerName3(playerid2), playerid2, level);
				SendAdminMessageFormat(COLOR_RED,"[AI] %s ustawi³ %s (%s) poziom admina na: %d.",CharacterInfo[playerid][pGlobalNick],PlayerName3(playerid2),CharacterInfo[playerid2][pGlobalNick],level);
				
				format(string, sizeof(string), "Administrator %s (ID: %d) zmieni³ Twój poziom administratora na %d.", CharacterInfo[playerid][pGlobalNick], playerid, level);
				msg_info(playerid2,string);
			}
		}
		else if(!strcmp(comm1, "premium", true))
		{
			new playerid2, days;
			if(sscanf(comm2, "id", playerid2, days))
				return msg_usage(playerid,"U¿yj: /set premium [ID gracza] [iloœæ dni]");
			else
			{
				if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
					return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
				else if(days < 0)
					return msg_error(playerid,"Wprowadzony czas jest nieprawid³owy.");
				
				GivePlayerPremium(playerid2, days);
				
				if(days == 0)
				{
					msg_infoFormat(playerid2, 64, "Administrator %s zabra³ Tobie konto premium.", CharacterInfo[playerid][pGlobalNick]);
					SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Zabra³eœ konto premium graczowi: %s!", PlayerName(playerid2));
				}
				else
				{
					msg_infoFormat(playerid2, 64, "Administrator %s przed³u¿y³ Twoje konto premium o %d dni!", CharacterInfo[playerid][pGlobalNick], days);
					SendClientMessageFormat(playerid, COLOR_YELLOW, "[AI] Przed³u¿y³eœ %s [%s] konto premium o %d dni!", PlayerName(playerid2), CharacterInfo[playerid2][pGlobalNick], days);
					log("%s ustawil premium %s na %d dni.",CharacterInfo[playerid][pGlobalNick],CharacterInfo[playerid2][pGlobalNick],days);
				}
				
				if(IsPlayerPremium(playerid2))
				{
					CharacterInfo[playerid2][pNickColor] = COLOR_PREMIUM;
					SetPlayerColor(playerid2, COLOR_PREMIUM);
				}
				else
				{
					CharacterInfo[playerid2][pNickColor] = COLOR_USER;
					SetPlayerColor(playerid2, COLOR_USER);
				}
			}
		}
		else if(!strcmp(comm1, "cash", true))
		{
			new playerid2, cash, string[128];
			if(sscanf(comm2, "id", playerid2, cash))
				return msg_usage(playerid,"U¿yj: /set cash [ID gracza] [stan gotówki]");
			else
			{
				if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
					return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
				if(cash < 0)
					return msg_error(playerid,"Wprowadzony stan gotówki jest nieprawid³owy.");
				
				log("%s zmiana $ %s[player:%d] %d - > %d ",CharacterInfo[playerid][pGlobalNick],PlayerName3(playerid2),CharacterInfo[playerid2][pUID],CharacterInfo[playerid2][pCash],cash);
				CharacterInfo[playerid2][pCash] = cash;
				SavePlayerStats(playerid2, SAVE_PLAYER_BASIC);
				
				ResetPlayerMoney(playerid2);
				GivePlayerMoney(playerid2, CharacterInfo[playerid2][pCash]);
				
				format(string, sizeof(string), "Gotówka gracza %s (ID: %d) zosta³a zmieniona na $%d.", PlayerName3(playerid2), playerid2, cash);
				msg_info(playerid, string);
				
				format(string, sizeof(string), "Administrator %s (ID: %d) zmieni³ Twój stan gotówki na $%d.", PlayerName2(playerid), playerid, cash);
				msg_info(playerid2, string);
			}
		}
		else if(!strcmp(comm1, "bank", true))
		{
			new playerid2, bank, string[128];
			if(sscanf(comm2, "id", playerid2, bank))
				return msg_usage(playerid,"U¿yj: /set bank [ID gracza] [stan gotówki]");
			else
			{
				if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
					return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
				if(bank < 0)
					return msg_error(playerid,"Wprowadzony stan gotówki w banku jest nieprawid³owy.");
				
				log("%s zmiana b$ %s[player:%d] %d - > %d ",CharacterInfo[playerid][pGlobalNick],PlayerName3(playerid2),CharacterInfo[playerid2][pUID],CharacterInfo[playerid2][pCredit],bank);
				CharacterInfo[playerid2][pCredit] = bank;
				SavePlayerStats(playerid2, SAVE_PLAYER_BASIC);
				
				format(string, sizeof(string), "Gotówka w banku gracza %s (ID: %d) zosta³a zmieniona na $%d.", PlayerName3(playerid2), playerid2, bank);
				msg_info(playerid, string);
				
				format(string, sizeof(string), "Administrator %s (ID: %d) zmieni³ Twój stan gotówki bankowej na $%d.", PlayerName3(playerid), playerid, bank);
				msg_info(playerid2, string);
			}
		}
		else if(!strcmp(comm1, "hours", true))
		{
			new playerid2, hours, string[128];
			if(sscanf(comm2, "id", playerid2, hours))
				return msg_usage(playerid,"U¿yj: /set hours [ID gracza] [iloœæ godzin]");
			else
			{
				if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
					return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
				if(hours < 0)
					return msg_error(playerid,"Wprowadzona iloœæ godzin jest nieprawid³owa.");
				
				CharacterInfo[playerid2][pHours] = hours;
				SavePlayerStats(playerid2, SAVE_PLAYER_BASIC);
				
				format(string, sizeof(string), "Godziny gracza %s (ID: %d) zosta³y zmienione na %d.", PlayerName2(playerid2), playerid2, hours);
				msg_info(playerid, string);
				
				format(string, sizeof(string), "Administrator %s (ID: %d) zmieni³ Twoj¹ iloœæ godzin na %d.", PlayerName2(playerid), playerid, hours);
				msg_info(playerid2, string);
			}
		}
		else if(!strcmp(comm1, "minutes", true))
		{
			new playerid2, minutes, string[128];
			if(sscanf(comm2, "id", playerid2, minutes))
				return msg_usage(playerid,"U¿yj: /set minutes [ID gracza] [iloœæ minut (1 - 60)]");
			else
			{
				if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
					return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
				if(minutes < 0 || minutes > 59)
					return msg_error(playerid,"Wprowadzona iloœæ minut jest nieprawid³owa.");
				
				CharacterInfo[playerid2][pMinutes] = minutes;
				SavePlayerStats(playerid2, SAVE_PLAYER_BASIC);
				
				format(string, sizeof(string), "Iloœæ minut gracza %s (ID: %d) zosta³a zmieniona na %d.", PlayerName2(playerid2), playerid2, minutes);
				msg_info(playerid, string);
				
				format(string, sizeof(string), "Administrator %s (ID: %d) zmieni³ Twoj¹ iloœæ minut na %d.", PlayerName2(playerid), playerid, minutes);
				msg_info(playerid2, string);
			}
		}
		else if(!strcmp(comm1, "skin", true))
		{
			new playerid2, skin, string[128];
			if(sscanf(comm2, "id", playerid2, skin))
				return msg_usage(playerid,"U¿yj: /set skin [ID gracza] [ID skina (0 - 311; 20001 - 21000)]");
			else
			{
				if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
					return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
				if(skin < 0 || (skin > 311 && skin < 20001) || skin > 21000)
					return msg_error(playerid,"Wprowadzone 'id' skina jest nieprawid³owe.");
				
				CharacterInfo[playerid2][pSkin] = skin;
				SavePlayerStats(playerid2, SAVE_PLAYER_BASIC);
				
				SetPlayerSkin(playerid2, CharacterInfo[playerid2][pSkin]);
				
				format(string, sizeof(string), "Skin gracza %s (ID: %d) zosta³a zmieniona na %d.", PlayerName2(playerid2), playerid2, skin);
				msg_info(playerid, string);
				
				format(string, sizeof(string), "Administrator %s (ID: %d) zmieni³ Twój skin na %d.", PlayerName2(playerid), playerid, skin);
				msg_info(playerid2, string);
			}
		}
		else if(!strcmp(comm1, "score", true))
		{
			new playerid2, score, string[128];
			if(sscanf(comm2, "id", playerid2, score))
				return msg_usage(playerid,"U¿yj: /set score [ID gracza] [iloœæ (max. 10000)]");
			else
			{
				if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
					return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
				if(score < 1 || score > 10000)
					return msg_error(playerid,"Wprowadzona iloœæ jest nieprawid³owa.");
				
				CharacterInfo[playerid2][pGlobalScore] = score;
				SavePlayerStats(playerid2, SAVE_PLAYER_GLOBAL);
				
				SetPlayerScore(playerid2, CharacterInfo[playerid2][pGlobalScore]);
				
				format(string, sizeof(string), "Iloœæ GameScore gracza %s (ID: %d) zosta³a zmieniona na %d.", PlayerName2(playerid2), playerid2, score);
				msg_info(playerid, string);
				
				format(string, sizeof(string), "Administrator %s (ID: %d) zmieni³ Twoj¹ iloœæ GameScore na %d.", PlayerName2(playerid), playerid, score);
				msg_info(playerid2, string);
			}
		}
		else if(!strcmp(comm1, "pogoda", true))
		{
			new weather_id;
			if(sscanf(comm2, "d", weather_id))
				return msg_usage(playerid,"U¿yj: /set pogoda [ID pogody]");
			else
			{
				SetWeather(weather_id);
				
				msg_info(playerid,"Pogoda zosta³a pomyœlnie zmieniona.");
			}
		}
		else if(!strcmp(comm1, "czas", true))
		{
			new time_id;
			if(sscanf(comm2, "d", time_id))
				return msg_usage(playerid,"U¿yj: /set czas [godzina]");
			else
			{
				if(time_id > 24 || time_id < 1)
					msg_error(playerid,"Wprowadzony czas jest nieprawid³owy.");
				
				SetWorldTime(time_id);
				
				msg_info(playerid,"Czas gry zosta³ pomyœlnie zmieniony.");
			}
		}
		else if(!strcmp(comm1, "sila", true))
		{
			new playerid2, sila, string[128];
			if(sscanf(comm2, "id", playerid2, sila))
				return msg_usage(playerid,"U¿yj: /set sila [ID gracza] [iloœæ J do ustawienia]");
			else
			{
				if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
					return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
				if(sila < 0 || sila > 1000)
					return msg_error(playerid, "Wprowadzona si³a nie jest prawid³owa.");
				
				log("%s zmiana SILY %s[player:%d] %d - > %d ", CharacterInfo[playerid][pGlobalNick], PlayerName3(playerid2), CharacterInfo[playerid2][pUID], CharacterInfo[playerid2][pStrength], sila);
				CharacterInfo[playerid2][pStrength] = sila;
				SavePlayerStats(playerid2, SAVE_PLAYER_OPTION);
				
				format(string, sizeof(string), "Si³a gracza %s (ID: %d) zosta³a zmieniona na %d.", PlayerName3(playerid2), playerid2, sila);
				msg_info(playerid, string);
				
				format(string, sizeof(string), "Administrator %s (ID: %d) zmieni³ Twój stan si³y na %d.", PlayerName2(playerid), playerid, sila);
				msg_info(playerid2, string);
			}
		}
		else if(!strcmp(comm1, "stylwalki", true))
		{
			new playerid2, styl, string[128];
			if(sscanf(comm2, "id", playerid2, styl))
				return msg_usage(playerid,"U¿yj: /set styl [ID gracza] [styl 0-3]");
			else
			{
				if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
					return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
				if(styl < 0 || styl > 3)
					return msg_error(playerid, "Wprowadzony styl walki nie jest prawid³owa.");
				
				log("%s zmiana STYLU WALKI %s[player:%d] %d - > %d ", CharacterInfo[playerid][pGlobalNick], PlayerName3(playerid2), CharacterInfo[playerid2][pUID], CharacterInfo[playerid2][pCash], styl);
				CharacterInfo[playerid2][pFightStyle] = styl;
				SavePlayerStats(playerid2, SAVE_PLAYER_OPTION);
				
				switch(CharacterInfo[playerid2][pFightStyle])
				{
					case 0:
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_GRABKICK);
					case 1:
						SetPlayerFightingStyle(playerid2, FIGHT_STYLE_BOXING);
					case 2:
						SetPlayerFightingStyle(playerid2, FIGHT_STYLE_KUNGFU);
					case 3:
						SetPlayerFightingStyle(playerid2, FIGHT_STYLE_KNEEHEAD);
				}
				
				format(string, sizeof(string), "Styl walki gracza %s (ID: %d) zosta³ zmieniona na %d.", PlayerName3(playerid2), playerid2, styl);
				msg_info(playerid, string);
				
				format(string, sizeof(string), "Administrator %s (ID: %d) zmieni³ Twój styl walki na %d.", PlayerName2(playerid), playerid, styl);
				msg_info(playerid2, string);
			}
		}
	}
	
	return 1;
}

CMD:slap(playerid, params[])
{
	if(!CharacterInfo[playerid][pAdmin]) return 1;
	new playerid2;
	if(sscanf(params, "i", playerid2))
		return msg_usage(playerid,"U¿yj: /slap [id gracza]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		if(CharacterInfo[playerid2][pBW] || CharacterInfo[playerid2][pWounded])
			return msg_error(playerid,"Gracz o podanym ID ma status BW.");
		
		new Float:x, Float:y, Float:z;
		GetPlayerPos(playerid2, x, y, z);
		
		SetPlayerPos(playerid2, x, y, z+3);
		
		SendClientMessageFormat(playerid, COLOR_RED, "[AI] U¿y³eœ /slap na %s(%d).", PlayerName3(playerid2), playerid2);
		msg_infoFormat(playerid2, 64, "Zosta³eœ uderzony przez %s(%d)! Popraw swoje zachowanie.", CharacterInfo[playerid][pGlobalNick], playerid);
		
		PlayerPlaySound(playerid2, 1190, 0.0, 0.0, 0.0);
	}
	
	return 1;
}

CMD:tpdo(playerid, params[])
{
	if(!CharacterInfo[playerid][pAdmin]) return 1;
	new playerid2;
	if(sscanf(params, "i", playerid2))
		return msg_usage(playerid,"U¿yj: /tpdo [ID gracza]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		
		if(playerid2 == playerid)
			return msg_error(playerid,"Nie mo¿esz teleportowaæ siê do samego siebie.");
		
		new Float:Pos[3];
		GetPlayerPos(playerid2, Pos[0], Pos[1], Pos[2]);
		
		SetPlayerPos(playerid, Pos[0], Pos[1] + 2.0, Pos[2]);
		SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(playerid2));
		SetPlayerInterior(playerid, GetPlayerInterior(playerid2));
		PlayerDoor[playerid]=PlayerDoor[playerid2];
		
		SetPlayerTime(playerid, SERVER_TIME, 0);
		SetPlayerWeather(playerid, SERVER_WEATHER);
	}
	
	return 1;
}
CMD:to(playerid,params[]) return cmd_tpdo(playerid,params);

CMD:tptutaj(playerid, params[])
{
	if(!CharacterInfo[playerid][pAdmin]) return 1;
	new playerid2;
	if(sscanf(params, "i", playerid2))
		return msg_usage(playerid,"U¿yj: /tptutaj [ID gracza]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		
		if(playerid2 == playerid)
			return msg_error(playerid,"Nie mo¿esz teleportowaæ samego siebie.");
		
		CharacterInfo[playerid][pACLastJustification] = gettime();
		new Float:Pos[3];
		GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
		
		SetPlayerPos(playerid2, Pos[0], Pos[1] + 2.0, Pos[2]);
		SetPlayerVirtualWorld(playerid2, GetPlayerVirtualWorld(playerid));
		SetPlayerInterior(playerid2, GetPlayerInterior(playerid));
		PlayerDoor[playerid2]=PlayerDoor[playerid];
		msg_infoFormat(playerid2, 64, "%s teleportowa³ Ciê do siebie.",CharacterInfo[playerid][pGlobalNick]);
		SetPlayerTime(playerid2, SERVER_TIME, 0);
		SetPlayerWeather(playerid2, SERVER_WEATHER);
	}
	
	return 1;
}
CMD:tm(playerid,params[]) return cmd_tptutaj(playerid,params);
CMD:tphere(playerid,params[]) return cmd_tptutaj(playerid,params);

CMD:tpspawn(playerid, params[])
{
	if(!CharacterInfo[playerid][pAdmin]) return 1;
	new playerid2;
	if(sscanf(params, "i", playerid2))
		return msg_usage(playerid,"U¿yj: /tpspawn [ID gracza]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");

		SendPlayerToSpawn(playerid2);
		
		PlayerDoor[playerid2] = 0;
		
		SetPlayerTime(playerid2, SERVER_TIME, 0);
		SetPlayerWeather(playerid2, SERVER_WEATHER);
		
		msg_infoFormat(playerid2, 64, "%s teleportowa³ Ciê na spawn.", CharacterInfo[playerid][pGlobalNick]);
		SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Teleportowa³eœ %s(%d) na spawn.",PlayerName3(playerid2),playerid2);
	}
	
	return 1;
}

CMD:tpcentrum(playerid, params[])
{
	if(!CharacterInfo[playerid][pAdmin]) return 1;
	new playerid2;
	if(sscanf(params, "i", playerid2))
		return msg_usage(playerid,"U¿yj: /tpcentrum [ID gracza]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		if(CharacterInfo[playerid2][pBW] || CharacterInfo[playerid2][pWounded])
			return msg_error(playerid,"Gracz o podanym ID ma status BW.");
		
		SetPlayerPos(playerid2, SettingInfo[sSpawnX], SettingInfo[sSpawnY], SettingInfo[sSpawnZ]);
		SetPlayerFacingAngle(playerid2, 0);
		SetCameraBehindPlayer(playerid2);
		SetPlayerVirtualWorld(playerid2, 0);
		SetPlayerInterior(playerid2, 0);
		PlayerDoor[playerid2]=0;
		
		SetPlayerTime(playerid2, SERVER_TIME, 0);
		SetPlayerWeather(playerid2, SERVER_WEATHER);
		
		msg_infoFormat(playerid2, 64, "%s teleportowa³ Ciê na spawn.", CharacterInfo[playerid][pGlobalNick]);
	}
	
	return 1;
}

CMD:tp(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 2) return 1;
	new playerid2, to_player;
	if(sscanf(params, "ii", playerid2, to_player))
		return msg_usage(playerid,"U¿yj: /tp [ID gracza] [Do gracza]");
	else
	{
		if(!Logged[playerid2] || !Logged[to_player])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		
		if(playerid2 == to_player)
			return msg_error(playerid,"Nie mo¿esz teleportowaæ siê do samego siebie.");
		
		new Float:Pos[3];
		GetPlayerPos(to_player, Pos[0], Pos[1], Pos[2]);
		
		SetPlayerPos(playerid2, Pos[0], Pos[1] + 2.0, Pos[2]);
		SetPlayerVirtualWorld(playerid2, GetPlayerVirtualWorld(to_player));
		SetPlayerInterior(playerid2, GetPlayerInterior(to_player));
		PlayerDoor[playerid2]=PlayerDoor[to_player];
		
		SetPlayerTime(playerid2, SERVER_TIME, 0);
		SetPlayerWeather(playerid2, SERVER_WEATHER);
			
		SendClientMessageFormat(playerid,COLOR_GREEN,"Teleportowa³eœ %s(%d) do %s(%d)",PlayerName3(playerid2),playerid2,PlayerName3(to_player),to_player);
		msg_infoFormat(playerid2, 64, "%s teleportowa³ Ciê do %s(%d).",CharacterInfo[playerid][pGlobalNick],PlayerName2(to_player),to_player);
	}
	
	return 1;
}

CMD:a(playerid, params[])
{
	if(!CharacterInfo[playerid][pAdmin]) return cmd_admins(playerid,params);
	
	new text[128];
	if(sscanf(params, "s[128]", text))
		return msg_usage(playerid, "U¿yj: /a [tekst]");
	else
	{
		if(CharacterInfo[playerid][pAdmin] == 1)
		{
			if(strlen(text) < 78)
				SendAdminMessageFormat(COLOR_ORANGE, "[Opiekun]{FFFFFF} %s[%d]: %s ", CharacterInfo[playerid][pGlobalNick], playerid, text);
			else
			{
				new pos = strfind(text, " ", true, strlen(text) / 2);
				if(pos != -1)
				{
					new text2[64];
					
					strmid(text2, text, pos + 1, strlen(text));
					strdel(text, pos, strlen(text));
					
					SendAdminMessageFormat(COLOR_ORANGE, "[Opiekun]{FFFFFF} %s[%d]: %s ...", CharacterInfo[playerid][pGlobalNick], playerid, text);
					
					SendAdminMessageFormat(COLOR_WHITE, "...%s", text2);
				}
			}
		}
		else if(CharacterInfo[playerid][pAdmin] < 5)
		{
			if(strlen(text) < 78)
				SendAdminMessageFormat(COLOR_GM, "[GameMaster]{FFFFFF} %s[%d]: %s ", CharacterInfo[playerid][pGlobalNick], playerid, text);
			else
			{
				new pos = strfind(text, " ", true, strlen(text) / 2);
				if(pos != -1)
				{
					new text2[64];
					
					strmid(text2, text, pos + 1, strlen(text));
					strdel(text, pos, strlen(text));
					
					SendAdminMessageFormat(COLOR_GM, "[GameMaster]{FFFFFF} %s[%d]: %s ...", CharacterInfo[playerid][pGlobalNick], playerid, text);
					
					SendAdminMessageFormat(COLOR_WHITE, "...%s", text2);
				}
			}
		}
		else if(CharacterInfo[playerid][pAdmin] == 5)
		{
			if(strlen(text) < 78)
				SendAdminMessageFormat(COLOR_DARKRED, "[Administrator]{FFFFFF} %s[%d]: %s ", CharacterInfo[playerid][pGlobalNick], playerid, text);
			else
			{
				new pos = strfind(text, " ", true, strlen(text) / 2);
				if(pos != -1)
				{
					new text2[64];
					
					strmid(text2, text, pos + 1, strlen(text));
					strdel(text, pos, strlen(text));
					
					SendAdminMessageFormat(COLOR_DARKRED, "[Administrator]{FFFFFF} %s[%d]: %s ...", CharacterInfo[playerid][pGlobalNick], playerid, text);
					
					SendAdminMessageFormat(COLOR_WHITE, "...%s", text2);
				}
			}
		}
		else if(CharacterInfo[playerid][pAdmin] == 6)
		{
			if(strlen(text) < 78)
				SendAdminMessageFormat(COLOR_RED, "[Administrator G³ówny]{FFFFFF} %s[%d]: %s ", CharacterInfo[playerid][pGlobalNick], playerid, text);
			else
			{
				new pos = strfind(text, " ", true, strlen(text) / 2);
				if(pos != -1)
				{
					new text2[64];
					
					strmid(text2, text, pos + 1, strlen(text));
					strdel(text, pos, strlen(text));
					
					SendAdminMessageFormat(COLOR_RED, "[Administrator G³ówny]{FFFFFF} %s[%d]: %s ...", CharacterInfo[playerid][pGlobalNick], playerid, text);
					
					SendAdminMessageFormat(COLOR_WHITE, "...%s", text2);
				}
			}
		}
	}
	
	return 1;
}

CMD:hp(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 1) return 1;
	
	new playerid2, Float:health;
	if(sscanf(params, "if", playerid2, health))
	{
		SetPlayerHP(playerid, 100.0);
		return msg_usage(playerid,"U¿yj: /hp [ID gracza] [stan zdrowia]");
	}
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		if(CharacterInfo[playerid2][pBW] || CharacterInfo[playerid2][pWounded])
			return msg_error(playerid,"Gracz o podanym ID ma status BW.");
		
		if(health < 1.0 || health > 100.0)
			return msg_error(playerid,"Wprowadzony stan zdrowia jest nieprawid³owy.");
		else
		{
			SetPlayerHP(playerid2, health);
			SendAdminMessageFormat(COLOR_GREEN, "[AI] %s ustawi³ HP %s(%d) na: %0.1f", CharacterInfo[playerid][pGlobalNick], PlayerName3(playerid2), playerid2, health);
		}
	}
	
	return 1;
}

CMD:vw(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin] < 2) return 1;
	new playerid2, vw, string[128];
	if(sscanf(params, "id", playerid2, vw))
		return msg_usage(playerid,"U¿yj: /vw [id gracza] [vw]");
	else
	{
		SetPlayerVirtualWorld(playerid2, vw);
		
		format(string, sizeof(string), "Administrator %s zmieni³ Tobie Virtual World na %d.", PlayerName2(playerid), vw);
		msg_info(playerid2, string);
	}
	
	return 1;
}

CMD:restart(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 6) return 1;
	new czas;
	if(sscanf(params, "d", czas))
		return msg_usage(playerid,"U¿yj /restart [czas]");
	else
	{
		if(czas < 0)
			return msg_error(playerid, "Czas nie mo¿e byæ ujemny!");
		
		restart = czas;
		gmx = true;
	}
	
	return 1;
}

CMD:aj(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 2) return 1;
	new playerid2, time, reason[64];
	if(sscanf(params, "ids[64]", playerid2, time, reason))
		return msg_usage(playerid,"U¿yj: /aj [ID gracza] [czas (min)] [powód]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		if(CharacterInfo[playerid2][pAJ])
			return msg_error(playerid,"Ten gracz jest ju¿ uwiêziony w AdminJail.");
		if(CharacterInfo[playerid2][pCurse] > gettime())
		{
			SendClientMessage(playerid2, COLOR_RED, "Posiadasz aktywn¹ kl¹twe, na konto zostaje na³o¿ona banicja.");

			CharacterInfo[playerid2][pBlock]+=BLOCK_BAN;
			AddBan(playerid2);
			GivePenalty(playerid2, playerid, gettime(), PENALTY_BAN_CURSE, 0, reason);
			SavePlayerStats(playerid2, SAVE_PLAYER_PENALTY);	
			KickWithWait(playerid2);
		}
		else
		{	
			CharacterInfo[playerid2][pAJ] = time * 60;
			
			SavePlayerStats(playerid2, SAVE_PLAYER_GLOBAL);	
			SetPlayerPos(playerid2, 154.1221, -1951.9156, 47.8750);
			SetPlayerInterior(playerid2, 0);
			SetPlayerVirtualWorld(playerid2, 1000 + playerid2);
			
			SendClientMessageFormat(playerid2, COLOR_RED, "[AI] Otrzyma³eœ karê Admin Jail (%d minut) od %s, powód: %s", time, CharacterInfo[playerid][pGlobalNick], reason);
			GivePenalty(playerid2, playerid, gettime(), PENALTY_AJ, time, reason);
		}
	}
	
	return 1;
}

CMD:unaj(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 4) return 1;
	
	new playerid2, reason[64];
	if(sscanf(params, "is[64]", playerid2, reason))
		return msg_usage(playerid,"U¿yj: /unaj [ID gracza] [powód]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		if(!CharacterInfo[playerid2][pAJ])
			return msg_error(playerid,"Ten gracz nie jest uwiêziony w AdminJail.");
		
		CharacterInfo[playerid2][pAJ] = 0;
		SavePlayerStats(playerid2, SAVE_PLAYER_GLOBAL);	
		
		OnPlayerSpawn(playerid2);
		
		msg_infoFormat(playerid2, 128, "Kara Admin Jail zosta³a zdjêta przez %s, powód: %s", CharacterInfo[playerid][pGlobalNick], reason);
		
		new string[128];
		format(string, sizeof(string), "[AI] %s wypuszcza gracza %s(%d) z AdminJail'a.", CharacterInfo[playerid][pGlobalNick], PlayerName3(playerid2), playerid2);
		SendAdminMessage(COLOR_RED,string);
	}
	
	return 1;
}

CMD:kick(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 1) return 1;
	new playerid2, reason[64];
	
	if(sscanf(params, "is[64]", playerid2, reason))
		return msg_usage(playerid,"U¿yj: /kick [ID gracza] [powód]");
	else
	{
		GivePenalty(playerid2, playerid, gettime(), PENALTY_KICK, 0, reason);
		KickWithWait(playerid2);
	}
	
	return 1;
}

CMD:gamescore(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 4) return 1;
	new playerid2, score, reason[64];
	
	if(sscanf(params, "ids[64]", playerid2, score, reason))
		return msg_usage(playerid,"U¿yj: /gamescore [ID gracza] [iloœæ] [powód]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		if(score < 1 || score > 100)
			return msg_error(playerid,"Wprowadzona iloœæ jest nieprawid³owa.");
		
		CharacterInfo[playerid2][pGlobalScore] += score;
		SetPlayerScore(playerid2, CharacterInfo[playerid2][pGlobalScore]);
		SavePlayerStats(playerid2, SAVE_PLAYER_GLOBAL);
		
		SendClientMessageFormat(playerid2, COLOR_GREEN, "[AI] Gratulacje! Otrzyma³eœ %d GameScore od %s, powód: %s", score, CharacterInfo[playerid][pGlobalNick], reason);
		GivePenalty(playerid2, playerid, gettime(), PENALTY_SCORE, score, reason);
	}
	
	return 1;
}

CMD:bw(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 1) return 1;
	new playerid2, time, string[128];
	if(sscanf(params, "id", playerid2, time))
		return msg_usage(playerid,"U¿yj: /bw [ID gracza] [czas (minuty)]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		if(CharacterInfo[playerid2][pBW])
			return msg_error(playerid,"Ten gracz ma ju¿ BW.\nU¿yj /unbw, aby zdj¹æ BW.");
		if(time<1)
			return msg_error(playerid,"Podany czas jest nieprawid³owy.");
		
		if(CharacterInfo[playerid2][pWounded])
			CharacterInfo[playerid2][pWounded] = 0;
		else
		{
			if(GetPVarInt(playerid2, "OfferUID"))
				DisableOffer(playerid2, GetPVarInt(playerid2, "OfferUID"));
			if(GetPVarInt(playerid2, "OfferBuyer"))
			{
				new playerid3 = GetPVarInt(playerid, "OfferBuyer");
				DisableOffer(playerid3, GetPVarInt(playerid3, "OfferUID"));
			}
			
			new query[128];
			format(query, sizeof(query), "UPDATE `srv_items` SET `used` = 0 WHERE `owner` = '%d'", CharacterInfo[playerid2][pUID]);
			mysql_query(query);
			
			ForeachEx(i,_ITEM_COUNT)
				if(ItemInfo[i][iOwnerTyp] == OWNER_PLAYER && ItemInfo[i][iOwner] == CharacterInfo[playerid2][pUID] && ItemInfo[i][iType]!=ITEM_TYPE_TELEFON)
					ItemInfo[i][iUsed] = 0;
					
			if(CharacterInfo[playerid2][pHaveWeapon])
				HidePlayerWeapons(playerid2);
			
			SetPlayerHP(playerid2, 10.0);
			GetPlayerPos(playerid2, CharacterInfo[playerid2][pPos][0], CharacterInfo[playerid2][pPos][1], CharacterInfo[playerid2][pPos][2]);
			
			CharacterInfo[playerid2][pInt] = GetPlayerInterior(playerid);
			CharacterInfo[playerid2][pVW] = GetPlayerVirtualWorld(playerid);
			
			if(IsPlayerInAnyVehicle(playerid2))
				RemovePlayerFromVehicle(playerid2);
			
			StopAudioStreamForPlayer(playerid2);
			SetPlayerCameraPos(playerid2, CharacterInfo[playerid2][pPos][0] + 1, CharacterInfo[playerid2][pPos][1] + 2, CharacterInfo[playerid2][pPos][2] + 3);
			SetPlayerCameraLookAt(playerid2, CharacterInfo[playerid2][pPos][0], CharacterInfo[playerid2][pPos][1], CharacterInfo[playerid2][pPos][2]);
			
			TogglePlayerControllable(playerid2, 0);
			
			SavePlayerStats(playerid2, SAVE_PLAYER_POS);
		}
		
		CharacterInfo[playerid2][pBW] = time * 60;
		
		format(string, sizeof(string), "Administrator %s na³o¿y³ Ci BW. Czas: %d min", PlayerName2(playerid), time);
		msg_info(playerid2, string);
		
		format(string, sizeof(string), "Pomyœlnie na³o¿ono BW graczowi %s (ID: %d, UID: %d). Czas: %d min.", PlayerName2(playerid2), playerid2, CharacterInfo[playerid2][pUID], time);
		msg_info(playerid, string);
		
		SendAdminMessageFormat(COLOR_RED, "[AI] %s nada³ BW %s(%d) na %d minut.", CharacterInfo[playerid][pGlobalNick], PlayerName2(playerid2), playerid2, time);
	}
	return 1;
}

CMD:unbw(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 1) return 1;
	new playerid2;
	if(sscanf(params, "i", playerid2))
		return msg_usage(playerid,"U¿yj: /unbw [ID gracza]");
	else
	{
		new string[128];
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		if(!CharacterInfo[playerid2][pBW] && !CharacterInfo[playerid2][pWounded])
			return msg_error(playerid,"Ten gracz nie ma BW.");
		
		CharacterInfo[playerid2][pBW] = 0;
		CharacterInfo[playerid2][pWounded] = 0;
		
		ApplyAnimation(playerid2, "Attractors", "Stepsit_out", 4.0, 0, 0, 0, 0, 0, 1);
		TogglePlayerControllable(playerid2, 1);
		
		SetCameraBehindPlayer(playerid2);
		SetPlayerHP(playerid2, 100.0);
		SavePlayerStats(playerid2, SAVE_PLAYER_BASIC);
		
		format(string, sizeof(string), "Administrator %s zdj¹³ Ci BW.", CharacterInfo[playerid][pGlobalNick]);
		msg_info(playerid2, string);
		
		SendAdminMessageFormat(COLOR_GREEN, "[AI] %s zdj¹³ BW %s(%d).", CharacterInfo[playerid][pGlobalNick], PlayerName3(playerid2), playerid2);
	}
	
	return 1;
}

CMD:rep(playerid,params[])
{
	if(!CharacterInfo[playerid][pAdmin]) return 1;
	
	new playerid2, text[128];
	if(sscanf(params, "is[128]", playerid2, text))
		return msg_usage(playerid,"U¿yj: /rep [ID gracza] [wiadomoœæ]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		if(playerid == playerid2)
			return msg_error(playerid,"Nie mo¿esz odpowiadaæ samemu sobie.");
		else
		{			
			SendClientMessageFormat(playerid2, COLOR_GREEN, ">>%s(%d):{ffffff} %s", CharacterInfo[playerid][pGlobalNick], playerid, text);
			SendAdminMessageFormat(COLOR_GREEN,"[ODP] %s > %s(%d):{ffffff} %s", CharacterInfo[playerid][pGlobalNick], PlayerName2(playerid2), playerid2, text);
		}
	}
	
	return 1;
}

CMD:ck(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 3) return 1;
    new playerid2, reason[64];
    if(sscanf(params, "is[64]", playerid2, reason))
		return msg_usage(playerid,"U¿yj: /ck [ID gracza] [pow?d]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		
		new Float:x,Float:y,Float:z;
		GetPlayerPos(playerid2,x,y,z);
		new date[16],day,month,year;
		getdate(year,month,day);
		if(day < 10)
			format(date,sizeof(date),"0%d.",day);
		else
			format(date,sizeof(date),"%d.",day);
		if(month<10)
			format(date,sizeof(date),"%s0%d.",date,month);
		else
			format(date,sizeof(date),"%s%d.",date,month);
		format(date,sizeof(date),"%s%d",date,year);
		
		new reason2[128];
		format(reason2, sizeof(reason2), "%s", reason);
		mysql_real_escape_string(reason2, reason2);
		
		z-=1.0;
        mysql_query_format("INSERT INTO `srv_corpse` VALUES (NULL,'%d','%s','%s','%s','%d','%s','%d','%f','%f','%f','%d','%d')",CharacterInfo[playerid2][pUID],PlayerName3(playerid2),reason2,0,0,date,CharacterInfo[playerid2][pCash],x,y,z,GetPlayerInterior(playerid2),GetPlayerVirtualWorld(playerid2));
		new uid=mysql_insert_id();
		
		CorpseInfo[uid][corpseID]=uid;
		CorpseInfo[uid][corpsePlayerUID]=CharacterInfo[playerid2][pUID];
		CorpseInfo[uid][corpsePlayerName]=PlayerName3(playerid2);
		CorpseInfo[uid][corpseReason]=reason2;
		CorpseInfo[uid][corpseGun]=0;
		CorpseInfo[uid][corpseGunVal]=0;
		CorpseInfo[uid][corpseDate]=date;
		CorpseInfo[uid][corpseMoney]=CharacterInfo[playerid2][pCash];
		CorpseInfo[uid][corpseX]=x;
		CorpseInfo[uid][corpseY]=y;
		CorpseInfo[uid][corpseZ]=z;
		CorpseInfo[uid][corpseInt]=GetPlayerInterior(playerid2);
		CorpseInfo[uid][corpseVW]=GetPlayerVirtualWorld(playerid2);
		CorpseInfo[uid][corpseObject] = CreateDynamicObject(19944, CorpseInfo[uid][corpseX], CorpseInfo[uid][corpseY], CorpseInfo[uid][corpseZ], 0, 0, 0, CorpseInfo[uid][corpseVW], CorpseInfo[uid][corpseInt], -1);

		CharacterInfo[playerid2][pCash]=0;
		CharacterInfo[playerid2][pBlock]+=BLOCK_CK;
		ForeachEx(i,_ITEM_COUNT)
		{
			if(ItemInfo[i][iOwnerTyp]==OWNER_PLAYER && ItemInfo[i][iOwner]==CharacterInfo[playerid2][pUID])
			{
				ItemInfo[i][iUsed]=0;
				ItemInfo[i][iOwnerTyp]=OWNER_CORPSE;
				ItemInfo[i][iOwner]=uid;
				format(reason2,sizeof(reason2),"UPDATE `srv_items` SET `owner`='%d', `ownertyp`='%d' WHERE `UID`='%d' LIMIT 1",ItemInfo[i][iOwner],ItemInfo[i][iOwnerTyp],ItemInfo[i][iUID]);
				mysql_query(reason2);
			}
		}
		
		SendClientMessageFormat(playerid2, COLOR_RED, "[AI] Twoja postaæ zosta³a zablokowana przez %s, powód: %s.", CharacterInfo[playerid][pGlobalNick], reason);
		GivePenalty(playerid2, playerid, gettime(), PENALTY_BLOCK, 0, reason);
		
        format(reason, sizeof(reason), "Zw³oki {636363}(%d)",uid);
        CorpseInfo[uid][corpseText] = CreateDynamic3DTextLabel(reason, COLOR_RED, CorpseInfo[uid][corpseX], CorpseInfo[uid][corpseY], CorpseInfo[uid][corpseZ]+0.75, 7.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID,1, CorpseInfo[uid][corpseVW]);
		
		KickWithWait(playerid2);
	}
	
	return 1;
}

CMD:block(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 3) return 1;
	
	new playerid2, reason[64];
	if(sscanf(params, "is[64]", playerid2, reason))
		return msg_usage(playerid,"U¿yj: /block [ID gracza] [powód]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		
		CharacterInfo[playerid2][pBlock] += BLOCK_CHAR;
		
		SendClientMessageFormat(playerid2, COLOR_RED, "[AI] Twoja postaæ zosta³a zablokowana przez %s, powód: %s.", CharacterInfo[playerid][pGlobalNick], reason);
		GivePenalty(playerid2, playerid, gettime(), PENALTY_BLOCK, 0, reason);
		
		KickWithWait(playerid2);
	}
	
	return 1;
}

CMD:ban(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 3) return 1;
	
	new playerid2, reason[64];
	if(sscanf(params, "is[64]", playerid2, reason))
		return msg_usage(playerid,"U¿yj: /ban [ID gracza] [powód]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		
		CharacterInfo[playerid2][pBlock] += BLOCK_BAN;
		
		SendClientMessageFormat(playerid2, COLOR_RED, "[AI] Twoje konto zosta³o zbanowane przez %s, powód: %s", CharacterInfo[playerid][pGlobalNick], reason);
		
		GivePenalty(playerid2, playerid, gettime(), PENALTY_BAN, 0, reason);
		AddBan(playerid2);

		KickWithWait(playerid2);
	}
	
	return 1;
}

CMD:warn(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 3 ) return 1;
	
	new playerid2, reason[64];
	if(sscanf(params, "is[64]", playerid2, reason))
		return msg_usage(playerid,"U¿yj: /warn [ID gracza] [powód]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		
		CharacterInfo[playerid2][pWarn] += 1;
		SendClientMessageFormat(playerid2, COLOR_RED, "[AI] Otrzyma³eœ ostrze¿enie [%d/4] od %s, powód: %s", CharacterInfo[playerid2][pWarn], CharacterInfo[playerid][pGlobalNick], reason);
		if(CharacterInfo[playerid2][pCurse] > gettime())
		{
			SendClientMessage(playerid2, COLOR_RED, "Posiadasz aktywn¹ kl¹twe, na konto zostaje na³o¿ona banicja.");

			CharacterInfo[playerid2][pBlock]+=BLOCK_BAN;
			SavePlayerStats(playerid2,SAVE_PLAYER_PENALTY);
			AddBan(playerid2);
			GivePenalty(playerid2, playerid, gettime(), PENALTY_BAN_CURSE, 0, reason);
			KickWithWait(playerid2);
		}
		else if(CharacterInfo[playerid2][pWarn] > 3)
		{
			SendClientMessage(playerid2, COLOR_RED, "[AI] Otrzyma³eœ maksymaln¹ liczbe ostrze¿eñ. Twoja postaæ zosta³a zbanowana.");
			SendClientMessage(playerid, COLOR_RED, "[AI] Gracz otrzyma³ maksymaln¹ liczbe ostrze¿eñ. Jego postaæ zosta³a zbanowana.");
			
			CharacterInfo[playerid2][pBlock] += BLOCK_BAN;
			AddBan(playerid2);
			GivePenalty(playerid2, playerid, gettime(), PENALTY_BAN44, 0, reason);

			KickWithWait(playerid2);
		}
		else
		{
			GivePenalty(playerid2, playerid, gettime(), PENALTY_WARN, 0, reason);
			SavePlayerStats(playerid2, SAVE_PLAYER_GLOBAL);
		}
	}
	
	return 1;
}

CMD:unwarn(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin] < 5) return 1;
	new playerid2, reason[64];
	
	if(sscanf(params, "is[64]", playerid2, reason))
		return msg_usage(playerid,"U¿yj: /unwarn [ID gracza] [powód]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		if(CharacterInfo[playerid2][pWarn]==0)
			return msg_error(playerid,"Gracz o podanym ID nie posiada ¿adnych warnów.");
		
		CharacterInfo[playerid2][pWarn] -= 1;
		
		msg_infoFormat(playerid2, 128, "[AI] Otrzyma³eœ unwarn od administratora %s(%d), powód: %s", CharacterInfo[playerid][pGlobalNick], playerid, reason);
		SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Pomyslnie nadano unwarn %s(%d).",PlayerName2(playerid2), playerid2);
		GivePenalty(playerid2, playerid, gettime(), PENALTY_UNWARN, 0, reason);
		SavePlayerStats(playerid2, SAVE_PLAYER_GLOBAL);
	}
	
	return 1;
}

CMD:bany(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin] < 5) return 1;
	
	new value[32];
	if(sscanf(params, "s[32]", value))
		return msg_usage(playerid,"U¿yj: /bany [GID/IP]");
	
	new query[256];
	format(query, sizeof(query), "SELECT `player_global_id`, `ip` FROM `srv_bans` WHERE `player_global_id`='%s' OR `ip`='%s'", value, value);
	mysql_query(query);
	
	mysql_store_result();
	
	new ip[32], gid, list_bans[256], data[64];
	
	format(list_bans, sizeof(list_bans), "GID\tNick\tIP");
	
	while(mysql_fetch_row_format(data, "|"))
	{
		sscanf(data, "p<|>ds[32]", gid, ip);
		format(list_bans, sizeof(list_bans), "%s\n%d\t%s\t%s", list_bans, gid, LoadPlayerGlobalNick(gid), ip);
	}
	
	mysql_free_result();
	
	if(strlen(data))
		ShowPlayerDialog(playerid, D_BAN_LIST, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » lista banicji", list_bans, "Zdejmij", "Anuluj");
	else
		return msg_error(playerid,"Nie znaleziono banów.");
	
	return 1;
}

CMD:podglad(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin] < 5) return 1;
	
	new string[64];
	if(CharacterInfo[playerid][pMsgspy])
	{
		CharacterInfo[playerid][pMsgspy] = 0;
		format(string,sizeof(string),"[AI] %s wy³¹czy³ podgl¹d PW.", CharacterInfo[playerid][pGlobalNick]);
		SendHAdminMessage(COLOR_RED, string);
	}
	else
	{
		CharacterInfo[playerid][pMsgspy] = 1;
		format(string,sizeof(string),"[AI] %s rozpocz¹³ podgl¹d PW.", CharacterInfo[playerid][pGlobalNick]);
		SendHAdminMessage(COLOR_RED, string);
	}
	
	return 1;
}

CMD:glod(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin] < 3) return 1;

	new playerid2, value;
	if(sscanf(params, "id", playerid2, value))
		return msg_usage(playerid,"U¿yj: /glod [ID gracza] [wartoœæ]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		if(value > 100 || value < 0)
			return msg_error(playerid,"Wpisa³eœ b³êdn¹ wartoœæ. Dozwolone od 0 do 100.");
		
		CharacterInfo[playerid2][pGlod] = 100 - value;
		SavePlayerStats(playerid2, SAVE_PLAYER_BASIC);
		
		SetPlayerProgressBarValue(playerid2, FoodBar[playerid2], CharacterInfo[playerid2][pGlod]);
		UpdatePlayerProgressBar(playerid2, FoodBar[playerid2]);
		
		SetPlayerDrunkLevel(playerid2, 0);
		
		SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Ustawi³eœ %d g³odu graczowi %s(%d).", value,PlayerName3(playerid2), playerid2);
		msg_infoFormat(playerid2, 96, "%s(%d) zmieni³ Twój poziom g³odu na: %d.",CharacterInfo[playerid][pGlobalNick],playerid, value);
	}
	
	return 1;
}

CMD:duty(playerid, params[])
{
	if(!CharacterInfo[playerid][pAdmin]) return 1;
	
	new godzina, minuta, sekunda;
	gettime(godzina, minuta, sekunda);
	
	switch(CharacterInfo[playerid][pAdmin])
	{
		case 1:
		{
			if(CharacterInfo[playerid][pAdminDuty])
			{
				CharacterInfo[playerid][pAdminDuty] = false;
				SendClientMessageFormat(playerid, COLOR_ORANGE, "» Zszed³eœ ze s³u¿by Opiekuna, godzina zakoñczenia %02d:%02d.", godzina, minuta);
				
				if(IsPlayerPremium(playerid)) CharacterInfo[playerid][pNickColor] = COLOR_PREMIUM;
				else CharacterInfo[playerid][pNickColor] = COLOR_USER;
			}
			else
			{
				CharacterInfo[playerid][pAdminDuty] = true;
				SendClientMessageFormat(playerid, COLOR_ORANGE, "» Wszed³eœ na s³u¿bê Opiekuna, godzina rozpoczêcia %02d:%02d.", godzina, minuta);
				
				CharacterInfo[playerid][pNickColor] = COLOR_PREMIUM;
			}
		}
		case 2,3,4:
		{
			if(CharacterInfo[playerid][pAdminDuty])
			{
				CharacterInfo[playerid][pAdminDuty] = false;
				SendClientMessageFormat(playerid, COLOR_GM, "» Zszed³eœ ze s³u¿by GameMastera, godzina zakoñczenia %02d:%02d.", godzina, minuta);
				
				if(IsPlayerPremium(playerid)) CharacterInfo[playerid][pNickColor] = COLOR_PREMIUM;
				else CharacterInfo[playerid][pNickColor] = COLOR_USER;
			}
			else
			{
				CharacterInfo[playerid][pAdminDuty] = true;
				SendClientMessageFormat(playerid, COLOR_GM, "» Wszed³eœ na s³u¿bê GameMastera, godzina rozpoczêcia %02d:%02d.", godzina, minuta);
				
				CharacterInfo[playerid][pNickColor] = COLOR_PREMIUM;
			}
		}
		case 5:
		{
			if(CharacterInfo[playerid][pAdminDuty])
			{
				CharacterInfo[playerid][pAdminDuty] = false;
				SendClientMessageFormat(playerid, COLOR_RED, "» Zszed³eœ ze s³u¿by Administratora, godzina zakoñczenia %02d:%02d.", godzina, minuta);
				
				if(IsPlayerPremium(playerid)) CharacterInfo[playerid][pNickColor] = COLOR_PREMIUM;
				else CharacterInfo[playerid][pNickColor] = COLOR_USER;
			}
			else
			{
				CharacterInfo[playerid][pAdminDuty] = true;
				SendClientMessageFormat(playerid, COLOR_RED, "» Wszed³eœ na s³u¿bê Administratora, godzina rozpoczêcia %02d:%02d.", godzina, minuta);
				
				CharacterInfo[playerid][pNickColor] = COLOR_PREMIUM;
			}
		}
		case 6:
		{
			if(CharacterInfo[playerid][pAdminDuty])
			{
				CharacterInfo[playerid][pAdminDuty] = false;
				SendClientMessageFormat(playerid, COLOR_RED, "» Zszed³eœ ze s³u¿by Zarz¹du, godzina zakoñczenia %02d:%02d.", godzina, minuta);
				
				if(IsPlayerPremium(playerid)) CharacterInfo[playerid][pNickColor] = COLOR_PREMIUM;
				else CharacterInfo[playerid][pNickColor] = COLOR_USER;
			}
			else
			{
				CharacterInfo[playerid][pAdminDuty] = true;
				SendClientMessageFormat(playerid, COLOR_RED, "» Wszed³eœ na s³u¿bê Zarz¹du, godzina rozpoczêcia %02d:%02d.", godzina, minuta);
				
				CharacterInfo[playerid][pNickColor] = COLOR_PREMIUM;
			}
		}
	}
	
	return 1;
}

CMD:aprzedmiot(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 5) return 1;
	
	new comm1[32], comm2[32];
	if(sscanf(params, "s[32]S()[32]", comm1, comm2))
		return msg_usage(playerid,"U¿yj: /aprzedmiot [stworz | usun | nazwa | typ | owner | value | typy]");
	else
	{
		if(!strcmp(comm1, "stworz", true))
			ShowPlayerDialog(playerid, D_ITEM_CREATE, DIALOG_STYLE_INPUT, DEF_NAME" » nowy przedmiot", "Wpisz nazwê nowego przedmiotu, który chcesz stworzyæ.", "Dalej", "Anuluj");
		else if(!strcmp(comm1, "usun", true))
		{
			new item_uid, string[256], typename[64], type;
			if(sscanf(comm2, "d", item_uid))
				return msg_usage(playerid,"/aprzedmiot usun [UID przedmiotu]");
			else
			{
				if(!ItemInfo[item_uid][iUID])
					return msg_error(playerid, "Brak przedmiotu o podanym UID.");
			
				SetPVarInt(playerid, "apdeleteuid", item_uid);
				
				type = ItemInfo[item_uid][iType];
				
				format(typename, sizeof(typename), "%s", ItemTypeInfo[type][iTypeName]);
				
				format(string, sizeof(string), "Jesteœ pewny, ¿e chcesz usun¹æ ten przedmiot?\n\nUID: %d\nNazwa przedmiotu: %s\nTyp przedmiotu: %s\nWartoœæ (1) przedmiotu: %d\nWartoœæ (2) przedmiotu: %d", item_uid, ItemInfo[item_uid][iName], typename, ItemInfo[item_uid][iValue1], ItemInfo[item_uid][iValue2]);
				ShowPlayerDialog(playerid, D_AP_USUN, DIALOG_STYLE_MSGBOX, DEF_NAME" » usuwanie", string, "Usuñ", "Anuluj");
			}
		}
		else if(!strcmp(comm1, "nazwa", true))
		{
			new item_uid, string[64];
			if(sscanf(comm2, "d", item_uid))
				return msg_usage(playerid,"/aprzedmiot nazwa [UID przedmiotu]");
			else
			{
				if(!ItemInfo[item_uid][iUID])
					return msg_error(playerid, "Brak przedmiotu o podanym UID.");
				
				SetPVarInt(playerid, "apnameuid", item_uid);
				
				format(string, sizeof(string), "Wpisz now¹ nazwê przedmiotu o UID: %d", item_uid);
			
				ShowPlayerDialog(playerid, D_AP_NAME, DIALOG_STYLE_INPUT, DEF_NAME" » zmiana nazwy", string, "Zmieñ", "Anuluj");
			}
		}
		else if(!strcmp(comm1, "typ", true))
		{
			new item_uid;
			if(sscanf(comm2, "d", item_uid))
				return msg_usage(playerid,"/aprzedmiot typ [UID przedmiotu]");
			else
			{
				if(!ItemInfo[item_uid][iUID])
					return msg_error(playerid, "Brak przedmiotu o podanym UID.");
				
				new string[512];
				
				SetPVarInt(playerid, "aptypeuid", item_uid);
				
				ForeachEx(i, TYPE_COUNT+1)
					format(string, sizeof(string), "%s\n%s", string, ItemTypeInfo[i][iTypeName]);
				
				ShowPlayerDialog(playerid, D_AP_TYPE, DIALOG_STYLE_LIST, DEF_NAME" » wybierz typ", string, "Zmieñ", "Anuluj");			
			}
		}
		else if(!strcmp(comm1, "owner", true))
		{
			new item_uid,ownertype,owner;
			if(sscanf(comm2, "ddd", item_uid,ownertype,owner))
				return msg_usage(playerid,"/aprzedmiot typ [UID przedmiotu] [typ w³asciciela] [w³asciciel]\n\nTypy:\nGracz: 1 [UID GRACZA]\nGrupa: 2 [UID Grupy]");

			if(!ItemInfo[item_uid][iUID])
					return msg_error(playerid, "Brak przedmiotu o podanym UID.");

			if(ownertype<1 || ownertype > 23)
				return msg_error(playerid,"Niepoprawny typ w³aœciciela");

			if(ItemInfo[item_uid][iUsed])
				return msg_error(playerid,"Wybrany przedmiot jest aktualnie u¿ywany.");

			log("%s zmienil ownera %s[item:%d] %d:%d -> %d:%d",CharacterInfo[playerid][pGlobalNick],ItemInfo[item_uid][iName],ItemInfo[item_uid][iOwnerTyp],ItemInfo[item_uid][iOwner],ownertype, owner);

			new string[96];
			format(string,sizeof(string),"[AI] Zmieni³es ownera przedmiotu %s[UID:%d] %d:%d->%d:%d",ItemInfo[item_uid][iName],item_uid,ItemInfo[item_uid][iOwnerTyp],ItemInfo[item_uid][iOwner],ownertype, owner);
			SendClientMessage(playerid, COLOR_GREEN, string);

			ItemInfo[item_uid][iOwnerTyp]=ownertype;
			ItemInfo[item_uid][iOwner]=owner;

			
			format(string,sizeof(string),"UPDATE `srv_items` SET `ownertyp`='%d', `owner`='%d' WHERE `UID`='%d'",ownertype,owner,item_uid);
			mysql_query(string);
			

			return 1;

		}
		else if(!strcmp(comm1, "value", true))
		{
			new item_uid;
			if(sscanf(comm2, "d", item_uid))
				return msg_usage(playerid,"/aprzedmiot typ [UID przedmiotu]");
			else
			{
				if(!ItemInfo[item_uid][iUID])
					return msg_error(playerid, "Brak przedmiotu o podanym UID.");
				
				SetPVarInt(playerid, "apvalueuid", item_uid);
				
				ShowPlayerDialog(playerid, D_AP_VALUE1, DIALOG_STYLE_INPUT, DEF_NAME" » wartoœæ", "Wpisz wartoœæ (1) przedmiotu.", "Dalej", "Anuluj");
			}
		}
		else if(!strcmp(comm1, "typy", true))
		{
			new string [1024];
			format(string,sizeof(string), "1.  Broñ [id broni] [ammo]");
			format(string,sizeof(string),"%s\n2.  Telefon [numer] [0]",string);
			format(string,sizeof(string),"%s\n3.  Maska [0] [0]",string);
			format(string,sizeof(string),"%s\n4.  Jedzenie [glod] [0]",string);
			format(string,sizeof(string),"%s\n5.  Kostka [0] [0]",string);
			format(string,sizeof(string),"%s\n6.  Karty [0] [0]",string);
			format(string,sizeof(string),"%s\n7.  Lekarstwo [HP] [0]",string);
			format(string,sizeof(string),"%s\n8.  Kamizelka [armor] [0]",string);
			format(string,sizeof(string),"%s\n9.  Zegarek [0] [0]",string);
			format(string,sizeof(string),"%s\n10.  Kanister [paliwo] [0]",string);
			format(string,sizeof(string),"%s\n11.  Papierosy [0] [0]",string);
			format(string,sizeof(string),"%s\n12.  Alhohol [0] [0]",string);
			format(string,sizeof(string),"%s\n13.  Nasiono maihuany [0] [0]",string);
			format(string,sizeof(string),"%s\n14.  Marihuana [ilosc] [0]",string);
			format(string,sizeof(string),"%s\n15.  Kokaina [iloœæ] [0]",string);
			format(string,sizeof(string),"%s\n16.  Heroina [iloœæ] [0]",string);
			format(string,sizeof(string),"%s\n17.  LSD [iloœæ] [0]",string);
			format(string,sizeof(string),"%s\n18.  Krótkofalówka [0] [0]",string);
			format(string,sizeof(string),"%s\n19.  Megafon [0] [0]",string);
			format(string,sizeof(string),"%s\n20.  Suplementy [typ 1-3] [0]",string);
			format(string,sizeof(string),"%s\n21.  Boombox [0] [0]",string);
			format(string,sizeof(string),"%s\n22.  Amunicja [id broni] [ammo]",string);
			format(string,sizeof(string),"%s\n23.  Tuning [id komponentu] [0]",string);
			format(string,sizeof(string),"%s\n24.  T³umik [0] [0]",string);
			format(string,sizeof(string),"%s\n25.  Kluczyki [uid pojazdu] [0]",string);
			format(string,sizeof(string),"%s\n26.  Obiekt doczepiany [model] [bone]",string);
			format(string,sizeof(string),"%s\n27.  Zestaw naprawczy [iloœæ hp] [0]",string);
			format(string,sizeof(string),"%s\n28.  Kluczyk do skrytki [numer] [0]",string);
			format(string,sizeof(string),"%s\n29.  Przyciemniane szyby [0] [0]",string);
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » typy przedmiotów", string, "OK","");
		}
	}
	
	return 1;
}
CMD:ap(playerid,params[]) return cmd_aprzedmiot(playerid,params);

CMD:spec(playerid, params[])
{
	if(!CharacterInfo[playerid][pAdmin]) return 1;
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new playerid2;
	if(sscanf(params, "i", playerid2))
	{
		if(!CharacterInfo[playerid][pSpec] && GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
			return msg_usage(playerid,"/spec [ID gracza]");
		else
		{
			TogglePlayerSpectating(playerid, 0);
			CharacterInfo[playerid][pSpec] = false;
			DeletePVar(playerid,"SpecPlayerID");
			if(!(CharacterInfo[playerid][pTog] & TOG_GLOD))
			{
				ShowPlayerProgressBar(playerid, FoodBar[playerid]);
				SetPlayerProgressBarValue(playerid, FoodBar[playerid], CharacterInfo[playerid][pGlod]);
				UpdatePlayerProgressBar(playerid, FoodBar[playerid]);
			}
			
			OnPlayerSpawn(playerid);
		}
	}
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		if(playerid2 == playerid)
			return msg_error(playerid,"Nie mo¿esz specowaæ samego siebie.");
		if(CharacterInfo[playerid2][pSpec])
			return msg_error(playerid,"Wybrany gracz aktualnie u¿ywa /spec.");
		if(CharacterInfo[playerid2][pStatus]& STATUS_BUS)
			return msg_error(playerid,"Wybrany gracz aktualnie korzysta z busa");
		if(CharacterInfo[playerid2][pAdmin] > CharacterInfo[playerid][pAdmin])
			return msg_error(playerid,"Nie mo¿esz specowaæ admina o wy¿szym poziomie ni¿ Twój.");
		if(CharacterInfo[playerid][pHaveWeapon])
			HidePlayerWeapons(playerid);
		
		SetPlayerInterior(playerid, GetPlayerInterior(playerid2));
		SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(playerid2));
		
		CharacterInfo[playerid][pSpec] = true;
		SetPVarInt(playerid,"SpecPlayerID",playerid2);
		
		HidePlayerProgressBar(playerid, FoodBar[playerid]);
		
		if(GetPlayerState(playerid2) == PLAYER_STATE_DRIVER || GetPlayerState(playerid2) == PLAYER_STATE_PASSENGER)
		{
			TogglePlayerSpectating(playerid, 1);
			PlayerSpectateVehicle(playerid, GetPlayerVehicleID(playerid2));
		}
		else
		{
			TogglePlayerSpectating(playerid, 1);
			PlayerSpectatePlayer(playerid, playerid2);
		}
	}
	
	return 1;
}

CMD:int(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 5) return 1;
	
	new name[32], interior, string[512];
	if(sscanf(params, "s[32]", name))
		return msg_usage(playerid,"U¿yj: /int [id interioru / nazwa]");
	if(isNumeric(name))
	{
		interior = strval(name);
		if(interior<0 || interior > 145)
			return msg_error(playerid,"Brak interioru o podanym id");
		SetPlayerPos(playerid, Interior[interior][INTERIOR_X], Interior[interior][INTERIOR_Y], Interior[interior][INTERIOR_Z]);
		SetPlayerFacingAngle(playerid, Interior[interior][INTERIOR_A]);
		SetPlayerInterior(playerid, Interior[interior][INTERIOR_ID]);
	}
	else
	{
		ForeachEx(i, 146)
			if(strfind(Interior[i][INTERIOR_NAME], name, true) >= 0)
				format(string, sizeof(string), "%s\n%d - %s", string, i, Interior[i][INTERIOR_NAME]);
		
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, DEF_NAME" » interior", string, "Zamknij", "");
	}
	
	return 1;
}

CMD:aprzeszukaj(playerid, params[])
{
	if(!CharacterInfo[playerid][pAdmin]) return 1;
	
	new type[32], comm2[32];
	if(sscanf(params, "s[32]S()[32]", type, comm2))
		return msg_usage(playerid,"U¿yj: /aprzeszukaj [gracz, pojazd]");
	else if(!strcmp(type, "gracz", true))
	{
		new playerid2;
		if(sscanf(comm2, "i", playerid2))
			return msg_usage(playerid,"U¿yj: /przeszukaj gracz [ID gracza]");
		else
		{
			if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
				return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
			if(playerid == playerid2)
				return msg_error(playerid,"Nie mo¿esz przeszukaæ samego siebie.");
			
			ListPlayerItemsForPlayer(playerid, playerid2);
			SendClientMessageFormat(playerid, COLOR_GREEN, "[INFO] Gracz ma przy sobie: $%d.", CharacterInfo[playerid2][pCash]);
		}
	}
	else if(!strcmp(type, "pojazd", true))
	{
		new vehid;
		if(sscanf(comm2, "i", vehid))
			vehid = GetClosestVehicle(playerid);
		
		if(!vehid || vehid == INVALID_VEHICLE_ID || vehid >= MAX_VEHICLES) 
			return msg_error(playerid,"Nie znaleziono pojazdu.");
		
		SetPVarInt(playerid, "przeszukajid", vehid);
		
		ShowPlayerDialog(playerid, D_APRZESZUKAJ, DIALOG_STYLE_LIST, DEF_NAME" » przeszukiwanie", "1. Pojazd\n2. Baga¿nik", "Wybierz", "Zamknij");
	}
	
	return 1;
}

CMD:apojazd(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 4) return 1;
	
	new comm1[32], comm2[64];
	if(sscanf(params, "s[32]S()[64]", comm1, comm2))
		return msg_usage(playerid,"U¿yj: /apojazd [lista | stworz | usun | przepisz | model | respawn | orespawn | jobrespawn | spawn | unspawn | gethere | goto\n kolor | karo | hp | hpall | zaparkuj | uid | tablica | paliwo | zarejestruj]");
	else
	{
		if(!strcmp(comm1, "lista", true))
		{	
			new owner[6],string[64];
			SendClientMessage(playerid, COLOR_GREEN, "\t* Lista pojazdów *");
			ForeachEx(uid, _VEH_COUNT)
			{
				if(VehicleInfo[uid][vUID])
				{
					if(VehicleInfo[uid][vOwnerTyp]==OWNER_PLAYER)
						format(owner,6,"gracz");
					else
						format(owner,6,"grupa");
					format(string,sizeof(string),"%d:{ffffff} %s, W³aœciciel: %s UID: %d", uid, GetVehicleModelName(VehicleInfo[uid][vModel]),owner,VehicleInfo[uid][vOwner]);
					SendClientMessage(playerid, COLOR_GREEN,string);
				}
			}
		}
		else if(!strcmp(comm1, "stworz", true))
		{
			if(CharacterInfo[playerid][pAdmin] < 5) return 1;
			new model, color1, color2;
			if(sscanf(comm2, "ddd", model, color1, color2))
				return msg_usage(playerid,"U¿yj: /apojazd stworz [MODEL] [COLOR1] [COLOR2]");
			else
			{
				if(model < 400 || model > 611)
					return msg_error(playerid,"Model pojazdu nie mo¿e byæ mniejszy ni¿ 400 oraz wiêkszy ni¿ 611.");
				if(color1 < 0 || color1 > 255 || color2 < 0 || color2 > 255)
					return msg_error(playerid,"ID koloru nie mo¿e byæ mniejsze ni¿ 0 oraz wiêksze ni¿ 255.");
				if(CharacterInfo[playerid][pAdmin] != 6 && model==432)
					return msg_info(playerid,"Na chuj Ci czo³g?");

				new Float:posx, Float:posy, Float:posz, Float:angle, vw, int;
				
				GetPlayerPos(playerid, posx, posy, posz);
				GetPlayerFacingAngle(playerid, angle);
				vw = GetPlayerVirtualWorld(playerid);
				int = GetPlayerInterior(playerid);
			
				new uid = StworzPojazd(playerid, model, color1, color2, vw, int, posx+2, posy+2, posz+1, angle);

				VehicleInfo[uid][vLocked]=false;
				SetVehicleLock(VehicleInfo[uid][vSAMPID], false);
				
				new string[128];
				format(string,sizeof(string),"[AI] Stworzy³eœ pojazd o UID: %d, model: %d, kolory: %d/%d.", uid, model, color1, color2);
				SendClientMessage(playerid, COLOR_GREEN, string);

				log("%s stworzyl %s[veh:%d]",CharacterInfo[playerid][pGlobalNick],GetVehicleModelName(model),uid);
			}
		}
		else if(!strcmp(comm1, "usun", true))
		{
			if(CharacterInfo[playerid][pAdmin] < 5) return 1;
			new uid;
			if(sscanf(comm2, "d", uid))
				return msg_usage(playerid,"U¿yj: /apojazd usun [UID]");
			else
			{
				if(uid >= MAX_VEHICLES || uid < 1)
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
				
				if(!VehicleInfo[uid][vUID])
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
			
				if(VehicleInfo[uid][vSpawned])
					UnspawnVehicle(uid);

				log("%s usuwa pojazd %s[veh:%d]",CharacterInfo[playerid][pGlobalNick],GetVehicleModelName(VehicleInfo[uid][vModel]),uid);
				
				DeleteVehicle(uid);
				
				msg_infoFormat(playerid, 32, "Usun¹³eœ pojazd o UID: %d.", uid);
			}
		}
		else if(!strcmp(comm1, "przepisz", true) || !strcmp(comm1, "owner", true))
		{
			if(CharacterInfo[playerid][pAdmin] < 5) return 1;
			new uid, type[16], gid;
			if(sscanf(comm2, "ds[16]d", uid, type, gid))
				return msg_usage(playerid,"U¿yj: /apojazd przepisz [UID] [gracz/grupa/praca] [ID gracza/grupy]");
			else
			{
				if(uid >= MAX_VEHICLES || uid < 1)
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
				if(!VehicleInfo[uid][vUID])
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
				if(!strcmp(type, "gracz", true))
				{
					new string[256];
				
					if(!Logged[gid])
						return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");

					log("%s przepisa³ %s[veh:%d] %d:%d -> %d:%d",CharacterInfo[playerid][pGlobalNick],GetVehicleModelName(VehicleInfo[uid][vModel]),uid,VehicleInfo[uid][vOwnerTyp],VehicleInfo[uid][vOwner],OWNER_PLAYER,CharacterInfo[gid][pUID]);
					
					VehicleInfo[uid][vOwnerTyp] = OWNER_PLAYER;
					VehicleInfo[uid][vOwner] = CharacterInfo[gid][pUID];
					
					SaveVehicle(uid, SAVE_VEH_OWNER);
					
					format(string, sizeof(string), "Pojazd %s (UID: %d) zosta³ przepisany pomyœlnie.\n\nTyp w³aœciciela: gracz\nW³aœciciel: %s (ID: %d, UID: %d)", GetVehicleModelName(VehicleInfo[uid][vModel]), uid, PlayerName2(gid), gid, CharacterInfo[gid][pUID]);
					msg_info(playerid,string);
				}
				else if(!strcmp(type, "grupa", true))
				{
					new string[256];
				
					if(!GroupInfo[gid][gUID])
						return msg_error(playerid,"Wybrana grupa nie istnieje.");

					log("%s przepisa³ %s[veh:%d] %d:%d -> %d:%d",CharacterInfo[playerid][pGlobalNick],GetVehicleModelName(VehicleInfo[uid][vModel]),uid,VehicleInfo[uid][vOwnerTyp],VehicleInfo[uid][vOwner],OWNER_GROUP,gid);
					
					VehicleInfo[uid][vOwnerTyp] = OWNER_GROUP;
					VehicleInfo[uid][vOwner] = gid;
					
					SaveVehicle(uid, SAVE_VEH_OWNER);
					
					format(string, sizeof(string), "Pojazd %s (UID: %d) zosta³ przepisany pomyœlnie.\n\nTyp w³aœciciela: grupa\nW³aœciciel: %s.", GetVehicleModelName(VehicleInfo[uid][vModel]), uid, GroupInfo[gid][gName]);
					msg_info(playerid,string);
				}
				else if(!strcmp(type,"praca",true))
				{
					VehicleInfo[uid][vOwnerTyp] = OWNER_JOB;
					VehicleInfo[uid][vOwner] = gid;
				}
			}
		}
		else if(!strcmp(comm1, "respawn", true))
		{
			ForeachEx(uid, _VEH_COUNT)
			{
				if(VehicleInfo[uid][vSpawned] && !IsVehicleOccupied(VehicleInfo[uid][vSAMPID]))
				{
					if(VehicleInfo[uid][vModel] == 435 || VehicleInfo[uid][vModel] == 450 || VehicleInfo[uid][vModel] == 584 || VehicleInfo[uid][vModel] == 591 || VehicleInfo[uid][vModel] == 611)
					{
						ForeachEx(i, _VEH_COUNT)
						{
							if(!(GetVehicleTrailer(VehicleInfo[i][vSAMPID]) == VehicleInfo[uid][vSAMPID]) && !IsVehicleOccupied(VehicleInfo[i][vSAMPID]))
							{
								UnspawnVehicle(uid);
								break;
							}
						}
					}
					else
						UnspawnVehicle(uid);
					
					if(VehicleInfo[uid][vOwnerTyp]!=OWNER_PLAYER)
						LoadVehicle(uid);
				}
			}
			new string[96];
			format(string,sizeof(string),"((%s wykona³ respawn nieu¿ywanych pojazdów.))",CharacterInfo[playerid][pGlobalNick]);
			SendClientMessageToAll(COLOR_GREEN, string);
		}
		else if(!strcmp(comm1,"orespawn", true))
		{
			new Float:distance;
			if(sscanf(comm2, "f", distance))
				 return msg_usage(playerid,"U¿yj: /apojazd orespawn [dystans]");
			if(distance > 0)
			{
				new Float:x,Float:y,Float:z;
				ForeachEx(uid, _VEH_COUNT)
				{
					if(VehicleInfo[uid][vSpawned] && !IsVehicleOccupied(VehicleInfo[uid][vSAMPID]))
					{
						GetVehiclePos(VehicleInfo[uid][vSAMPID],x,y,z);
						if(IsPlayerInRangeOfPoint(playerid, distance, x, y, z))
						{
							if(VehicleInfo[uid][vSpawned] && !IsVehicleOccupied(VehicleInfo[uid][vSAMPID]))
							{
								if(VehicleInfo[uid][vModel] == 435 || VehicleInfo[uid][vModel] == 450 || VehicleInfo[uid][vModel] == 584 || VehicleInfo[uid][vModel] == 591 || VehicleInfo[uid][vModel] == 611)
								{
									ForeachEx(i, _VEH_COUNT)
									{
										if(!(GetVehicleTrailer(VehicleInfo[i][vSAMPID]) == VehicleInfo[uid][vSAMPID]) && !IsVehicleOccupied(VehicleInfo[i][vSAMPID]))
										{
											UnspawnVehicle(uid);
											break;
										}
									}
								}
								else
									UnspawnVehicle(uid);
							
								if(VehicleInfo[uid][vOwnerTyp]!=OWNER_PLAYER)
									LoadVehicle(uid);
							}
						}
					}
				}
				GetPlayerPos(playerid,x,y,z);
				new string[96];
				format(string,sizeof(string),"((%s wykona³ obszarowy respawn nieu¿ywanych pojazdów.))",CharacterInfo[playerid][pGlobalNick]);
				ForeachPlayer(i)
					if(IsPlayerInRangeOfPoint(i, distance, x, y, z))
						SendClientMessage(i, COLOR_GREEN, string);
			}
		}
		else if(!strcmp(comm1,"jobrespawn",true))
		{
			ForeachEx(uid, _VEH_COUNT)
			{
				if(VehicleInfo[uid][vSpawned] && VehicleInfo[uid][vOwnerTyp] == OWNER_JOB && !IsVehicleOccupied(VehicleInfo[uid][vSAMPID]))
				{
					UnspawnVehicle(uid);
					LoadVehicle(uid);
					VehicleInfo[uid][vFuel]=GetVehicleMaxFuel(VehicleInfo[uid][vModel]);
					VehicleInfo[uid][vHP]=1000.0;
					SetVehicleHealth(VehicleInfo[uid][vSAMPID], 1000.0);
					UpdateVehicleDamageStatus(VehicleInfo[uid][vSAMPID], 0, 0, 0, 0);

				}
			}
		}
		else if(!strcmp(comm1, "spawn", true))
		{
			new uid;
			if(sscanf(comm2, "d", uid))
				return msg_usage(playerid,"U¿yj: /apojazd spawn [UID]");
			else
			{
				if(uid >= MAX_VEHICLES || uid < 1)
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
				if(!VehicleInfo[uid][vUID])
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
				else if(VehicleInfo[uid][vSpawned])
					return msg_error(playerid, "Pojazd jest zespawnowany.");
				
				LoadVehicle(uid);
				
				SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Zespawnowa³eœ pojazd o UID: %d", uid);
			}
		}
		else if(!strcmp(comm1, "unspawn", true))
		{
			new uid;
			if(sscanf(comm2, "d", uid))
				return msg_usage(playerid,"U¿yj: /apojazd unspawn [UID]");
			else
			{
				if(uid >= MAX_VEHICLES || uid < 1)
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
				if(!VehicleInfo[uid][vUID])
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
				else if(!VehicleInfo[uid][vSpawned])
					return msg_error(playerid, "Pojazd nie jest zespawnowany.");
				
				UnspawnVehicle(uid);
				
				SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Odspawnowa³eœ pojazd o UID: %d", uid);
			}
		}
		else if(!strcmp(comm1, "uid", true) || !strcmp(comm1, "id", true))
		{
			new vehid = GetClosestVehicle(playerid);
			new vehuid = GetVehicleUID(vehid);
			
			if(!vehuid)
				return msg_error(playerid, "Brak pojazdów blisko Ciebie.");
			
			SendClientMessageFormat(playerid, COLOR_GREEN, "[INFO] UID: %d, SampID: %d, MODEL: %s.", VehicleInfo[vehuid][vUID], vehid, GetVehicleModelName(VehicleInfo[vehuid][vModel]));
			
			if(VehicleInfo[vehuid][vOwnerTyp] == OWNER_GROUP) SendClientMessageFormat(playerid, COLOR_GREEN, "[INFO] W³aœciciel - GRUPA: %s (UID: %d)", GroupInfo[VehicleInfo[vehuid][vOwner]][gName], VehicleInfo[vehuid][vOwner]);
			else if(VehicleInfo[vehuid][vOwnerTyp] == OWNER_PLAYER) SendClientMessageFormat(playerid, COLOR_GREEN, "[INFO] W³aœciciel - GRACZ: %s (UID: %d)", LoadPlayerName(VehicleInfo[vehuid][vOwner]), VehicleInfo[vehuid][vOwner]);
		}
		else if(!strcmp(comm1, "gethere", true) || !strcmp(comm1, "tptutaj", true) || !strcmp(comm1, "tm", true))
		{
			new uid;
			if(sscanf(comm2, "d", uid))
				return msg_usage(playerid,"U¿yj: /apojazd tm [UID]");
			else
			{
				if(uid >= MAX_VEHICLES || uid < 1)
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
				if(!VehicleInfo[uid][vUID])
					return msg_error(playerid,"Brak pojazdu o podanym UID.");
				else if(!VehicleInfo[uid][vSpawned])
					return msg_error(playerid,"Pojazd nie jest zespawnowany.");
				
				new Float:posx, Float:posy, Float:posz, vw;
				
				GetPlayerPos(playerid, posx, posy, posz);
				vw = GetPlayerVirtualWorld(playerid);
				
				SetVehiclePos(VehicleInfo[uid][vSAMPID], posx+2, posy+2, posz+1);
				SetVehicleVirtualWorld(VehicleInfo[uid][vSAMPID], vw);
				LinkVehicleToInterior(VehicleInfo[uid][vSAMPID], GetPlayerInterior(playerid));
				
				SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Teleportowa³eœ do siebie pojazd o UID: %d.", uid);
			}
		}
		else if(!strcmp(comm1, "goto", true) || !strcmp(comm1, "tpdo", true) || !strcmp(comm1, "to", true))
		{
			new uid;
			if(sscanf(comm2, "d", uid))
				return msg_usage(playerid,"U¿yj: /apojazd to [UID]");
			else
			{
				if(uid >= MAX_VEHICLES || uid < 1)
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
				if(!VehicleInfo[uid][vUID])
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
				else if(!VehicleInfo[uid][vSpawned])
					return msg_error(playerid, "Pojazd nie jest zespawnowany.");
				
				new Float: posx, Float:posy, Float:posz, vw;
				
				GetVehiclePos(VehicleInfo[uid][vSAMPID], posx, posy, posz);
				vw = GetVehicleVirtualWorld(VehicleInfo[uid][vSAMPID]);
				
				SetPlayerPos(playerid, posx-2, posy-2, posz);
				SetPlayerVirtualWorld(playerid, vw);
				
				SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Teleportowa³eœ siê do pojazdu o UID: %d.", uid);
			}
		}
		else if(!strcmp(comm1, "kolor", true))
		{
			if(CharacterInfo[playerid][pAdmin] < 5) return 1;
			new uid, color1, color2;
			if(sscanf(comm2, "ddd", uid, color1, color2))
				return msg_usage(playerid,"U¿yj: /apojazd kolor [UID] [COLOR1] [COLOR2]");
			else
			{
				if(uid >= MAX_VEHICLES || uid < 1)
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
				if(!VehicleInfo[uid][vUID])
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
				else if(!VehicleInfo[uid][vSpawned])
					return msg_error(playerid, "Pojazd nie jest zespawnowany.");
				else if(color1 < 0 || color1 > 255 || color2 < 0 || color2 > 255)
					return msg_error(playerid,"ID koloru nie mo¿e byæ mniejsze ni¿ 0 oraz wiêksze ni¿ 255.");
				
				VehicleInfo[uid][vColor1] = color1;
				VehicleInfo[uid][vColor2] = color2;
				ChangeVehicleColor(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vColor1] , VehicleInfo[uid][vColor2]);
				
				SaveVehicle(uid, SAVE_VEH_BASIC);
				
				SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Zmieni³eœ kolor pojazdu o UID: %d na %d/%d.", uid, color1, color2);
			}
		}
		else if(!strcmp(comm1, "model", true))
		{
			if(CharacterInfo[playerid][pAdmin] < 5) return 1;
			new uid, model;
			if(sscanf(comm2, "dd", uid, model))
				return msg_usage(playerid,"U¿yj: /apojazd model [UID] [MODEL]");
			else
			{
				if(uid >= MAX_VEHICLES || uid < 1)
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
				if(!VehicleInfo[uid][vUID])
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
				else if(!VehicleInfo[uid][vSpawned])
					return msg_error(playerid, "Pojazd nie jest zespawnowany.");
				else if(model < 400 || model > 611)
					return msg_error(playerid,"Model pojazdu nie mo¿e byæ mniejszy ni¿ 400 oraz wiêkszy ni¿ 611.");
				
				if(CharacterInfo[playerid][pAdmin] != 6 && model==432)
					return msg_info(playerid,"Na chuj Ci czo³g?");
				
				log("%s zmiana modelu [veh:%d] %s->%s",CharacterInfo[playerid][pGlobalNick],uid,GetVehicleModelName(VehicleInfo[uid][vModel]),GetVehicleModelName(model));
				VehicleInfo[uid][vModel] = model;
				
				UnspawnVehicle(uid);
				LoadVehicle(uid);
				
				SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Zmieni³eœ model pojazdu o UID: %d na %d.", uid, model);
			}
		}
		else if(!strcmp(comm1, "zaparkuj", true))
		{
			new uid;
			if(sscanf(comm2, "d", uid))
				return msg_usage(playerid,"U¿yj: /apojazd zaparkuj [UID]");
			else
			{
				if(uid >= MAX_VEHICLES || uid < 1)
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
				if(!VehicleInfo[uid][vUID])
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
				else if(!VehicleInfo[uid][vSpawned])
					return msg_error(playerid, "Pojazd nie jest zespawnowany.");
				
				GetVehiclePos(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vposx], VehicleInfo[uid][vposy], VehicleInfo[uid][vposz]);
				VehicleInfo[uid][vVW] = GetVehicleVirtualWorld(VehicleInfo[uid][vSAMPID]);
				GetVehicleZAngle(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vAngle]);
				
				SaveVehicle(uid, SAVE_VEH_POS);
				
				UnspawnVehicle(uid);
				LoadVehicle(uid);
				
				SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Zaparkowa³eœ pojazd o UID: %d.", uid);
			}
		}
		else if(!strcmp(comm1, "hp", true))
		{
			new uid, hp;
			if(sscanf(comm2, "dd", uid, hp))
				return msg_usage(playerid,"U¿yj: /apojazd hp [UID] [HP]");
			else
			{
				if(uid >= MAX_VEHICLES || uid < 1)
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
				if(!VehicleInfo[uid][vUID])
					return msg_error(playerid,"Brak pojazdu o podanym UID.");
				else if(!VehicleInfo[uid][vSpawned])
					return msg_error(playerid,"Pojazd nie jest zespawnowany.");
				else if(hp > GetVehicleMaxHP(VehicleInfo[uid][vModel]) || hp < 0)
				{
					msg_errorFormat(playerid, 64, "HP danego pojazdu nie mo¿e byæ wiêksze ni¿ %s oraz mniejsze ni¿ 0.", GetVehicleMaxHP(VehicleInfo[uid][vModel]));
					return 1;
				}
				
				if(hp >= GetVehicleMaxHP(VehicleInfo[uid][vModel]))
				{ 
					hp = GetVehicleMaxHP(VehicleInfo[uid][vModel]);
					VehicleInfo[uid][vVisual][0]=0;
					VehicleInfo[uid][vVisual][1]=0;
					VehicleInfo[uid][vVisual][2]=0;
					VehicleInfo[uid][vVisual][3]=0;
					RepairVehicle(VehicleInfo[uid][vSAMPID]);
				}
				else SetVehicleHealth(VehicleInfo[uid][vSAMPID], hp);
				
				VehicleInfo[uid][vHP] = hp;
				
				SaveVehicle(uid, SAVE_VEH_BASIC);
				
				SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Ustawi³eœ %d HP pojazdowi o UID: %d", floatround(hp), uid);
			}
		}
		else if(!strcmp(comm1, "karo", true))
		{
			new uid;
			if(sscanf(comm2, "d", uid))
				return msg_usage(playerid,"U¿yj: /apojazd karo [UID]");
			
			if(uid >= MAX_VEHICLES || uid < 1)
				return msg_error(playerid, "Brak pojazdu o podanym UID.");
			if(!VehicleInfo[uid][vUID])
				return msg_error(playerid,"Brak pojazdu o podanym UID.");
			else if(!VehicleInfo[uid][vSpawned])
				return msg_error(playerid,"Pojazd nie jest zespawnowany.");
			VehicleInfo[uid][vVisual][0]=
			VehicleInfo[uid][vVisual][1]=
			VehicleInfo[uid][vVisual][2]=
			VehicleInfo[uid][vVisual][3]=0;
			UpdateVehicleDamageStatus(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vVisual][0],VehicleInfo[uid][vVisual][1],VehicleInfo[uid][vVisual][2],VehicleInfo[uid][vVisual][3]);
			SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Naprawi³eœ karoseriê pojazdu %s [UID:%d]", GetVehicleModelName(VehicleInfo[uid][vModel]), uid);
		}
		else if(!strcmp(comm1, "tablica", true))
		{
			new uid, tablica[8];
			if(sscanf(comm2, "ds[8]", uid, tablica))
				return msg_usage(playerid,"U¿yj: /apojazd tablica [UID] [TABLICA]");
			else
			{
				if(uid >= MAX_VEHICLES || uid < 1)
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
				if(!VehicleInfo[uid][vUID])
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
				else if(!VehicleInfo[uid][vSpawned])
					return msg_error(playerid, "Pojazd nie jest zespawnowany.");
				
				VehicleInfo[uid][vRegister] = tablica;
				
				SaveVehicle(uid, SAVE_VEH_BASIC);
				
				SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Ustawi³eœ rejestracje pojazdu o UID: %d na %s.", uid, tablica);
			}
		}
		else if(!strcmp(comm1, "hpall", true))
		{
			if(CharacterInfo[playerid][pAdmin] < 5) return 1;
			ForeachEx(vehuid, _VEH_COUNT)
			{
				if(VehicleInfo[vehuid][vUID] && VehicleInfo[vehuid][vSpawned])
				{
					RepairVehicle(VehicleInfo[vehuid][vSAMPID]);
					VehicleInfo[vehuid][vHP] = GetVehicleMaxHP(VehicleInfo[vehuid][vModel]);
					SetVehicleHealth(VehicleInfo[vehuid][vSAMPID], float(GetVehicleMaxHP(VehicleInfo[vehuid][vModel])));
					VehicleInfo[vehuid][vVisual][0]=0;
					VehicleInfo[vehuid][vVisual][1]=0;
					VehicleInfo[vehuid][vVisual][2]=0;
					VehicleInfo[vehuid][vVisual][3]=0;
					UpdateVehicleDamageStatus(VehicleInfo[vehuid][vSAMPID], VehicleInfo[vehuid][vVisual][0], VehicleInfo[vehuid][vVisual][1], VehicleInfo[vehuid][vVisual][2], VehicleInfo[vehuid][vVisual][3]);
					
					SaveVehicle(vehuid, SAVE_VEH_BASIC);
				}
			}
			new string[128];
			format(string,sizeof(string),"[AI] %s naprawi³ wszystkie zespawnowane pojazdy.",CharacterInfo[playerid][pGlobalNick]);
			SendAdminMessage(COLOR_RED, string);
		}
		else if(!strcmp(comm1, "paliwo", true))
		{
			new uid, paliwo;
			if(sscanf(comm2, "dd", uid, paliwo))
				return msg_usage(playerid,"U¿yj: /apojazd paliwo [UID] [ILOŒÆ PALIWA]");
			else
			{
				if(uid >= MAX_VEHICLES || uid < 1)
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
				if(!VehicleInfo[uid][vUID])
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
				else if(!VehicleInfo[uid][vSpawned])
					return msg_error(playerid, "Pojazd nie jest zespawnowany.");
				
				VehicleInfo[uid][vFuel] = paliwo;
				
				SaveVehicle(uid, SAVE_VEH_BASIC);
				
				SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Ustawi³eœ paliwo pojazdu o UID: %d na %d.", uid, paliwo);
			}
		}
		else if(!strcmp(comm1, "info", true))
		{
			new uid;
			if(sscanf(comm2, "d", uid))
				return msg_usage(playerid,"U¿yj: /apojazd info [UID]");
			
			if(uid >= MAX_VEHICLES || uid < 1)
				return msg_error(playerid, "Brak pojazdu o podanym UID.");
			if(!VehicleInfo[uid][vUID])
				return msg_error(playerid, "Brak pojazdu o podanym UID.");
			
			new string[256];
			format(string,sizeof(string),"UID:\t%d",uid);
			format(string,sizeof(string),"%s\nModel:\t%s",string,GetVehicleModelName(VehicleInfo[uid][vModel]));
			if(VehicleInfo[uid][vOwnerTyp]==OWNER_PLAYER)
				format(string,sizeof(string),"%s\nTyp w³aœciciela:\tGracz\nW³aœciciel:\t%d - %s",string,VehicleInfo[uid][vOwner],LoadPlayerName(VehicleInfo[uid][vOwner]));
			else if(VehicleInfo[uid][vOwnerTyp]==OWNER_GROUP)
				format(string,sizeof(string),"%s\nTyp w³aœciciela:\tGrupa\nW³aœciciel:\t%d - %s",string,VehicleInfo[uid][vOwner], GroupInfo[VehicleInfo[uid][vOwner]][gName]);
			else if(VehicleInfo[uid][vOwnerTyp]==OWNER_JOB)
				format(string,sizeof(string),"%s\nTyp w³aœciciela:\tPraca dorywcza\nW³aœciciel:\t%d",string,VehicleInfo[uid][vOwner]);
			
			format(string,sizeof(string),"%s\nHP:\t%.2f",string,VehicleInfo[uid][vHP]/100);
			format(string,sizeof(string),"%s\nPaliwo:\t%.1f / %.1f",string,VehicleInfo[uid][vFuel],GetVehicleMaxFuel(VehicleInfo[uid][vModel]));
			msg_info(playerid, string);
		}
		else if(!strcmp(comm1, "zarejestruj", true))
		{
			new uid, reg;
			if(sscanf(comm2, "dd", uid, reg))
				return msg_usage(playerid,"U¿yj: /apojazd zarejestruj [UID] [1/0]");
			else
			{
				if(uid >= MAX_VEHICLES || uid < 1)
					return msg_error(playerid, "Brak pojazdu o podanym UID.");
				if(!VehicleInfo[uid][vUID])
					return msg_error(playerid, "Nie ma pojazdu o takim UID!");
				
				switch(reg)
				{
					case 0:
					{
						if(VehicleInfo[uid][vRegistered])
						{
							VehicleInfo[uid][vRegistered] = 0;
							new string[8];
							format(string, sizeof(string), ".");
							VehicleInfo[uid][vRegister] = string;
							SaveVehicle(uid, SAVE_VEH_BASIC);
							msg_info(playerid, "Odrejestrowa³eœ pojazd.");
						}
						else
							return msg_error(playerid, "Pojazd nie jest zarejestrowany!");
					}
					case 1:
					{
						if(!VehicleInfo[uid][vRegistered])
						{
							VehicleInfo[uid][vRegistered] = 1;
							new string[8];
							format(string, sizeof(string), "LS-%04d", uid);
							VehicleInfo[uid][vRegister] = string;
							SaveVehicle(uid, SAVE_VEH_BASIC);
							msg_info(playerid, "Zarejestrowa³eœ pojazd.");
						}
						else
							return msg_error(playerid, "Pojazd jest ju¿ zarejestrowany!");
					}
				}
			}
		}
	}
	
	return 1;
}
CMD:av(playerid,params[]) return cmd_apojazd(playerid,params);

CMD:adrzwi(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 5) return 1;
	
	new comm1[32], comm2[64];
	if(sscanf(params, "s[32]S()[64]", comm1, comm2))
		return msg_usage(playerid,"U¿yj: /ad(rzwi) [stworz | usun | lista | nazwa | wejscie | wyjscie | pickup | wlasciciel | goto | garaz | ikona]");
	else
	{
		if(!strcmp(comm1, "stworz", true))
		{
			new ownertyp, owner, name[31];
			if(sscanf(comm2, "dds[31]", ownertyp, owner, name))
				return msg_usage(playerid,"U¿yj: /ad(rzwi) stwórz [rodzaj w³aœciciela] [w³aœciciel] [nazwa drzwi]\n\nRodzaje w³aœcicieli:\n1. Gracz/Dom (ID gracza) \n2. Grupa (UID)\n3. Dom (ID domu)\n4. Dom na sprzeda¿ (KWOTA)\n5. Salon pojazdów (TYLKO JEDEN)\n6. Bankomat\n7. Areszt\n8. Sklep odzie¿owy\n14. Hotel\n22. Skrytka\n24. /uleczsie");
			else
			{
				if(ownertyp == OWNER_PLAYER)
				{
					if(!Logged[owner])
						return msg_error(playerid, "Wybrany gracz nie jest zalogowany.");
					
					owner = CharacterInfo[owner][pUID];
				}
				else if(ownertyp == OWNER_BANKOMAT || ownertyp == OWNER_SVEHICLE || ownertyp == OWNER_SAFEKEEP)
					owner = 0;
				
				new dooruid = StworzDrzwi(playerid, ownertyp, owner, name);
				
				log("%s tworzy drzwi %s[door:%d] owner: %d:%d",CharacterInfo[playerid][pGlobalNick],name,dooruid,ownertyp,owner);
				SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Pomyœlnie stworzy³eœ drzwi %s (UID: %d).", DoorsInfo[dooruid][dName], DoorsInfo[dooruid][dUID]);
			}
		}
		else if(!strcmp(comm1, "usun", true))
		{
			new uid;
			if(sscanf(comm2, "d", uid))
				return msg_usage(playerid,"U¿yj: /ad(rzwi) usun [uid]");
			else
			{
				if(!DoorsInfo[uid][dUID])
					return msg_error(playerid, "Drzwi o podanym UID nie istniej¹.");
				
				new string[256];
				
				SetPVarInt(playerid, "doorremoveuid", uid);
				
				format(string, sizeof(string), "Czy jesteœ pewny usuniêcia tych drzwi?\n\nUID: %d\nNazwa: %s\n", uid, DoorsInfo[uid][dName]);
				
				ShowPlayerDialog(playerid, D_DOORS_REMOVE, DIALOG_STYLE_MSGBOX, DEF_NAME" » usuwanie drzwi", string, "Tak", "Nie");
			}
		}
		else if(!strcmp(comm1, "lista", true))
		{
			SendClientMessage(playerid, COLOR_GREEN, "\t* Lista drzwi *");
			new string[96];
			ForeachEx(i,_DOOR_COUNT)
			{
				if(DoorsInfo[i][dUID])
				{
					format(string,sizeof(string),"%d:{ffffff} %s, Typ: %d, W³aœciciel: %d" , i, DoorsInfo[i][dName],DoorsInfo[i][dOwnerTyp],DoorsInfo[i][dOwner]);
					SendClientMessage(playerid,COLOR_GREEN,string);
				}
			}
		}
		else if(!strcmp(comm1, "nazwa", true))
		{
			new uid;
			if(sscanf(comm2, "d", uid))
				return msg_usage(playerid,"U¿yj: /ad(rzwi) nazwa [uid]");
			else
			{
				if(!DoorsInfo[uid][dUID])
					return msg_error(playerid, "Drzwi o podanym UID nie istniej¹.");
				
				new string[128];
				
				SetPVarInt(playerid, "doornameuid", uid);
				
				format(string, sizeof(string), "Wpisz now¹ nazwê dla drzwi o UID: %d", uid);
				
				ShowPlayerDialog(playerid, D_DOORS_NAME, DIALOG_STYLE_INPUT, DEF_NAME" » zmiana nazwy", string, "Zmieñ", "Anuluj");
			}
		}
		else if(!strcmp(comm1, "wejscie", true))
		{
			new uid;
			if(sscanf(comm2, "d", uid))
				return msg_usage(playerid,"U¿yj: /ad(rzwi) wejscie [uid]");
			else
			{
				if(!DoorsInfo[uid][dUID])
					return msg_error(playerid, "Drzwi o podanym UID nie istniej¹.");
				
				new Float:PosX, Float:PosY, Float:PosZ, Float:PosAngle;
				
				GetPlayerPos(playerid, PosX, PosY, PosZ);
				GetPlayerFacingAngle(playerid, PosAngle);
				
				DoorsInfo[uid][dEnterX] = PosX;
				DoorsInfo[uid][dEnterY] = PosY;
				DoorsInfo[uid][dEnterZ] = PosZ;
				DoorsInfo[uid][dEnterAngle] = PosAngle;
				DoorsInfo[uid][dEnterInt] = GetPlayerInterior(playerid);
				DoorsInfo[uid][dEnterVW] = GetPlayerVirtualWorld(playerid);
				
				DestroyDynamicPickup(DoorsInfo[uid][dPickup]);
				DoorsInfo[uid][dPickup] = CreateDynamicPickup(DoorsInfo[uid][dPickupID], 1, DoorsInfo[uid][dEnterX], DoorsInfo[uid][dEnterY], DoorsInfo[uid][dEnterZ], DoorsInfo[uid][dEnterVW], DoorsInfo[uid][dEnterInt]);
				
				SaveDoors(uid, SAVE_DOORS_POS);
				
				SendClientMessage(playerid, COLOR_GREEN, "[AI] Pomyœlnie ustawi³eœ wejœcie drzwi.");
				
				ForeachPlayer(i)
				{
					for(new d = 0; d<MAX_DOORS_MAPICONS; d++)
					{
						if(DOORS_MAPICONS[i][d] != -1)
							DestroyDynamicMapIcon(DOORS_MAPICONS[i][d]);
						
						DOORS_MAPICONS[i][d] = -1;
					}
					
					for(new u = 0; u<_DOOR_COUNT; u++)
					{
						if(DoorsInfo[u][dIconID])
						{
							new icon = -1;
							for(new s = 0; s<MAX_DOORS_MAPICONS; s++)
							{
								if(DOORS_MAPICONS[i][s] == -1)
								{
									icon = s;
									break;
								}
							}
							
							DOORS_MAPICONS[i][icon] = CreateDynamicMapIcon(DoorsInfo[u][dEnterX], DoorsInfo[u][dEnterY], DoorsInfo[u][dEnterZ], DoorsInfo[u][dIconID], 0, -1, -1, i, -1, MAPICON_LOCAL);
						}
					}
				}
			}
		}
		else if(!strcmp(comm1, "wyjscie", true))
		{
			new uid;
			if(sscanf(comm2, "d", uid))
				return msg_usage(playerid,"U¿yj: /ad(rzwi) wyjscie [uid]");
			else
			{
				if(!DoorsInfo[uid][dUID])
					return msg_error(playerid, "Drzwi o podanym UID nie istniej¹.");
				
				new Float:PosX, Float:PosY, Float:PosZ, Float:PosAngle;
				
				GetPlayerPos(playerid, PosX, PosY, PosZ);
				GetPlayerFacingAngle(playerid, PosAngle);
				
				DoorsInfo[uid][dExitX] = PosX;
				DoorsInfo[uid][dExitY] = PosY;
				DoorsInfo[uid][dExitZ] = PosZ;
				DoorsInfo[uid][dExitAngle] = PosAngle;
				DoorsInfo[uid][dExitInt] = GetPlayerInterior(playerid);
				DoorsInfo[uid][dExitVW] = GetPlayerVirtualWorld(playerid);
				
				SaveDoors(uid, SAVE_DOORS_POS);
				if(DoorsInfo[uid][dExitVW]==  0)
					SendClientMessage(playerid, COLOR_RED, "Ustawi³eœ wyjœcie drzwi na vw0 noobie. Grzeœ Cie dojedzie.");
				else
					SendClientMessage(playerid, COLOR_GREEN, "[AI] Pomyœlnie ustawi³eœ wyjœcie drzwi.");
			}
		}
		else if(!strcmp(comm1, "pickup", true))
		{
			new uid, id;
			if(sscanf(comm2, "dd", uid, id))
				return msg_usage(playerid,"U¿yj: /ad(rzwi) pickup [uid] [ID pickupa]");
			else
			{
				if(!DoorsInfo[uid][dUID])
					return msg_error(playerid, "Drzwi o podanym UID nie istniej¹.");
				
				if(id < 0 || id > 21)
					return msg_error(playerid," ID pickupa musi byæ w zakresie 0-21.");
				
				new pickup_model = PickupID[id];
				
				DoorsInfo[uid][dPickupID] = pickup_model;
				
				DestroyDynamicPickup(DoorsInfo[uid][dPickup]);
				DoorsInfo[uid][dPickup] = CreateDynamicPickup(DoorsInfo[uid][dPickupID], 1, DoorsInfo[uid][dEnterX], DoorsInfo[uid][dEnterY], DoorsInfo[uid][dEnterZ], DoorsInfo[uid][dEnterVW], DoorsInfo[uid][dEnterInt]);
				
				SaveDoors(uid, SAVE_DOORS_BASIC);
				
				SendClientMessage(playerid, COLOR_GREEN, "[AI] Pomyœlnie zmieni³eœ PICKUP drzwi.");
			}
		}
		else if(!strcmp(comm1, "wlasciciel", true) || !strcmp(comm1, "owner", true))
		{
			new uid, ownertyp, owner;
			if(sscanf(comm2, "ddd", uid, ownertyp, owner))
				return msg_usage(playerid,"U¿yj: /ad(rzwi) wlasciciel [uid] [rodzaj w³aœciciela] [w³aœciciel]\n\nRodzaje w³aœcicieli:\n1. Gracz/Dom (ID gracza)\n2. Grupa\n3. Dom (ID domu)\n4. Dom na sprzeda¿ (KWOTA)\n5. Salon pojazdów (TYLKO JEDEN)\n6. Bankomat (UID)\n7. Areszt\n8. Sklep odzie¿owy\n14. Hotel\n22. Skrytka\n24. /uleczsie");
			else
			{
				if(!DoorsInfo[uid][dUID])
					return msg_error(playerid, "Drzwi o podanym UID nie istniej¹.");
				
				if(ownertyp == OWNER_PLAYER)
				{
					if(!Logged[owner])
						return msg_error(playerid, "Gracz o podanym ID nie jest zalogowany.");
					
					DoorsInfo[uid][dOwnerTyp] = OWNER_PLAYER;
					DoorsInfo[uid][dOwner] = CharacterInfo[owner][pUID];
				}
				else if(ownertyp == OWNER_HOUSE)
				{

					if(DoorsInfo[owner][dOwnerTyp] != OWNER_PLAYER)
						return msg_error(playerid,"Wybrane id domu nie jest poprawne.");
					
					DoorsInfo[uid][dOwnerTyp] = OWNER_HOUSE;
					DoorsInfo[uid][dOwner] = owner;
				}
				else 
				{
					DoorsInfo[uid][dOwnerTyp] = ownertyp;
					DoorsInfo[uid][dOwner] = owner;
				}
				
				SaveDoors(uid, SAVE_DOORS_BASIC);
				
				SendClientMessage(playerid, COLOR_GREEN, "[AI] Pomyœlnie zmieni³eœ w³aœciciela drzwi.");
			}
		}
		else if(!strcmp(comm1, "goto", true))
		{
			new uid;
			if(sscanf(comm2, "d", uid))
				return msg_usage(playerid,"U¿yj: /ad(rzwi) goto [uid]");
			else
			{
				if(!DoorsInfo[uid][dUID])
					return msg_error(playerid, "Drzwi o podanym UID nie istniej¹.");
				
				SetPlayerPos(playerid, DoorsInfo[uid][dEnterX], DoorsInfo[uid][dEnterY], DoorsInfo[uid][dEnterZ]);
				SetPlayerVirtualWorld(playerid, DoorsInfo[uid][dEnterVW]);
				SetPlayerInterior(playerid, DoorsInfo[uid][dEnterInt]);
				SetPlayerFacingAngle(playerid, DoorsInfo[uid][dEnterAngle]);
				
				SendClientMessage(playerid, COLOR_GREEN, "[AI] Przeteleportowa³eœ siê do wybranych drzwi.");
			}
		}
		else if(!strcmp(comm1, "garaz", true))
		{
			new uid, garage;
			if(sscanf(comm2, "dd", uid, garage))
				return msg_usage(playerid,"U¿yj: /ad(rzwi) garaz [uid] [0/1]");
			else
			{
				if(!DoorsInfo[uid][dUID])
					return msg_error(playerid, "Drzwi o podanym UID nie istniej¹.");
				
				if(garage < 0 || garage > 1)
					return msg_error(playerid, "Wartoœæ musi byæ w zakresie 0/1.");
				
				DoorsInfo[uid][dGarage] = garage;
				
				SaveDoors(uid, SAVE_DOORS_BASIC);
				
				SendClientMessage(playerid, COLOR_GREEN, "[AI] Pomyœlnie zmieni³eœ ustawienie gara¿u.");
			}
		}
		else if(!strcmp(comm1, "ikona", true))
		{
			new uid, id;
			if(sscanf(comm2, "dd", uid, id))
				return msg_usage(playerid,"U¿yj: /ad(rzwi) ikona [uid] [ID ikony]");
			else
			{
				if(!DoorsInfo[uid][dUID])
					return msg_error(playerid, "Drzwi o podanym UID nie istniej¹.");

				if(DoorsInfo[uid][dEnterVW])
					return msg_error(playerid,"Nie mo¿esz tworzyæ ikon drzwi na vw innym, ni¿ vw0.");
				
				if(((id < 5 && id != 0) || id > 64) && id != 41)
					return msg_error(playerid, "ID ikony musi byæ w zakresie 5-64 z wy³¹czeniem 41 (0 - usuniêcie ikony).");
				
				if(id == 0 && DoorsInfo[uid][dIconID])
				{
					DoorsInfo[uid][dIconID] = 0;
					SaveDoors(uid, SAVE_DOORS_BASIC);
					
					ForeachPlayer(i)
					{
						for(new d = 0; d<MAX_DOORS_MAPICONS; d++)
						{
							if(DOORS_MAPICONS[i][d] != -1)
								DestroyDynamicMapIcon(DOORS_MAPICONS[i][d]);
							
							DOORS_MAPICONS[i][d] = -1;
						}
						
						for(new u = 0; u<_DOOR_COUNT; u++)
						{
							if(DoorsInfo[u][dIconID])
							{
								new icon = -1;
								for(new s = 0; s<MAX_DOORS_MAPICONS; s++)
								{
									if(DOORS_MAPICONS[i][s] == -1)
									{
										icon = s;
										break;
									}
								}
								
								DOORS_MAPICONS[i][icon] = CreateDynamicMapIcon(DoorsInfo[u][dEnterX], DoorsInfo[u][dEnterY], DoorsInfo[u][dEnterZ], DoorsInfo[u][dIconID], 0, -1, -1, i, -1, MAPICON_LOCAL);
							}
						}
					}
				}
				else if(id == 0)
					msg_error(playerid, "Wybrane drzwi nie posiadaj¹ ikony.");
				else
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
					
					if(icon == -1)
						return msg_error(playerid, "Osi¹gniêto limit ikonek na mapie dla drzwi.");
					else
					{
						DoorsInfo[uid][dIconID] = id;
						SaveDoors(uid, SAVE_DOORS_BASIC);
						
						ForeachPlayer(i)
						{
							for(new d = 0; d<MAX_DOORS_MAPICONS; d++)
							{
								if(DOORS_MAPICONS[i][d] != -1)
									DestroyDynamicMapIcon(DOORS_MAPICONS[i][d]);
								
								DOORS_MAPICONS[i][d] = -1;
							}
							
							for(new u = 0; u<_DOOR_COUNT; u++)
							{
								if(DoorsInfo[u][dIconID])
								{
									new icon2 = -1;
									for(new s = 0; s<MAX_DOORS_MAPICONS; s++)
									{
										if(DOORS_MAPICONS[i][s] == -1)
										{
											icon2 = s;
											break;
										}
									}
									
									DOORS_MAPICONS[i][icon2] = CreateDynamicMapIcon(DoorsInfo[u][dEnterX], DoorsInfo[u][dEnterY], DoorsInfo[u][dEnterZ], DoorsInfo[u][dIconID], 0, -1, -1, i, -1, MAPICON_LOCAL);
								}
							}
						}
						
						SendClientMessage(playerid, COLOR_GREEN, "[AI] Pomyœlnie zmieni³eœ IKONE drzwi.");
					}
				}
			}
		}
	}
	
	return 1;
}
CMD:ad(playerid,params[]) return cmd_adrzwi(playerid,params);

CMD:info(playerid, params[])
{
	if(!CharacterInfo[playerid][pAdmin]) return 1;
	
	new string[128];
	new Float: PosX, Float: PosY, Float:PosZ, Float: Angle;
	
	GetPlayerPos(playerid, PosX, PosY, PosZ);
	GetPlayerFacingAngle(playerid, Angle);
	
	format(string, sizeof(string), "[AI] VW: %d, INT: %d, PosX: %f, PosY: %f, PosZ: %f, Angle: %f.", GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), PosX, PosY, PosZ, Angle);

	SendClientMessage(playerid, COLOR_GREEN, string);
	
	return 1;
}

CMD:nogun(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 3) return 1;
	
	new playerid2, time, reason[64];
	if(sscanf(params, "dds[64]", playerid2, time, reason))
		return msg_usage(playerid,"U¿yj: /nogun [ID gracza] [czas(min)] [powód]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		
		if(time == 0)
		{
			if(CharacterInfo[playerid2][pBlock] & BLOCK_NOGUN)
			{
				CharacterInfo[playerid2][pBlock] -= BLOCK_NOGUN;
				CharacterInfo[playerid2][pBlockNoGun] = 0;
				msg_infoFormat(playerid2, 96, "Administrator %s zdj¹³ Ci blokadê broni.", CharacterInfo[playerid][pGlobalNick]);
				SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Zdj¹³eœ blokadê broni graczowi %s (%d).", PlayerName3(playerid2), playerid2);
				SendAdminMessageFormat(COLOR_GREEN,"[AI] %s zdja³ blokadê broni graczowi %s (%d).", CharacterInfo[playerid][pGlobalNick], PlayerName3(playerid2), playerid2);
				SavePlayerStats(playerid2, SAVE_PLAYER_PENALTY);
				return 1;
			}
			else
				return msg_error(playerid, "Wybrany gracz nie posiada aktywnej blokady broni.");
		}
		else
		{
			if(CharacterInfo[playerid2][pBlockNoGun])
				return msg_error(playerid, "Wybrany gracz ma ju¿ blokadê.");
			if(CharacterInfo[playerid2][pCurse] > gettime() && time >30)
			{
				SendClientMessage(playerid2, COLOR_RED, "Posiadasz aktywn¹ kl¹twe, na konto zostaje na³o¿ona banicja.");

				CharacterInfo[playerid2][pBlock]+=BLOCK_BAN;
				AddBan(playerid2);
				GivePenalty(playerid2, playerid, gettime(), PENALTY_BAN_CURSE, 0, reason);
				SavePlayerStats(playerid2, SAVE_PLAYER_PENALTY);	
				KickWithWait(playerid2);
				return 1;
			}
		
			CharacterInfo[playerid2][pBlock] += BLOCK_NOGUN;
			CharacterInfo[playerid2][pBlockNoGun] += time*60;
			GivePenalty(playerid2, playerid, gettime(), PENALTY_NOGUN, time, reason);
			
			//msg_infoFormat(playerid2, 256, "Administrator %s na³o¿y³ Ci blokadê broni na %d minut.\n Powód: %s", CharacterInfo[playerid][pGlobalNick], time, reason);
			SendClientMessageFormat(playerid, COLOR_RED, "[AI] Na³o¿y³eœ blokadê broni na gracza %s (%d). Czas: %d min.", PlayerName3(playerid2), playerid2, time);
			SavePlayerStats(playerid2, SAVE_PLAYER_PENALTY);
			
			new query[128];
			format(query, sizeof(query), "UPDATE `srv_items` SET `used` = 0 WHERE `owner` = '%d' AND `type` = '%d'", CharacterInfo[playerid2][pUID], ITEM_TYPE_BRON);
			mysql_query(query);
			
			ForeachEx(i,_ITEM_COUNT)
				if(ItemInfo[i][iOwnerTyp] == OWNER_PLAYER && ItemInfo[i][iOwner] == CharacterInfo[playerid2][pUID] && ItemInfo[i][iType] == ITEM_TYPE_BRON)
					ItemInfo[i][iUsed] = 0;
			
			if(CharacterInfo[playerid2][pHaveWeapon])
				HidePlayerWeapons(playerid2);
		}
	}
	
	return 1;
}

CMD:nocar(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 3) return 1;
	
	new playerid2, time, reason[64];
	if(sscanf(params, "dds[64]", playerid2, time, reason))
		return msg_usage(playerid,"U¿yj: /nocar [ID gracza] [czas(min)] [powód]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		
		if(time == 0)
		{
			if(CharacterInfo[playerid2][pBlock] & BLOCK_NOCAR)
			{
				CharacterInfo[playerid2][pBlock] -= BLOCK_NOCAR;
				CharacterInfo[playerid2][pBlockNoCar] = 0;
				msg_infoFormat(playerid2, 96, "Administrator %s zdj¹³ Ci blokadê prowadzenia pojazdów.", CharacterInfo[playerid][pGlobalNick]);
				SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Zdj¹³eœ blokadê prowadzenia pojazdów graczowi %s (%d).", PlayerName3(playerid2), playerid2);
				SendAdminMessageFormat(COLOR_GREEN,"[AI] %s zdja³ blokadê prowadzenia pojazdów graczowi %s (%d).", CharacterInfo[playerid][pGlobalNick], PlayerName3(playerid2), playerid2);
				SavePlayerStats(playerid2, SAVE_PLAYER_PENALTY);
				return 1;
			}
			else
				return msg_error(playerid, "Wybrany gracz nie posiada aktywnej blokady prowadzenia pojazdów.");
		}
		else
		{
			if(CharacterInfo[playerid2][pBlock] & BLOCK_NOCAR)
				return msg_error(playerid, "Wybrany gracz ma ju¿ blokadê.");
			if(CharacterInfo[playerid2][pCurse] > gettime() && time >30)
			{
				SendClientMessage(playerid2, COLOR_RED, "Posiadasz aktywn¹ kl¹twe, na konto zostaje na³o¿ona banicja.");

				CharacterInfo[playerid2][pBlock]+=BLOCK_BAN;
				AddBan(playerid2);
				GivePenalty(playerid2, playerid, gettime(), PENALTY_BAN_CURSE, 0, reason);
				SavePlayerStats(playerid2, SAVE_PLAYER_PENALTY);	
				KickWithWait(playerid2);
				return 1;
			}
		
			CharacterInfo[playerid2][pBlock] += BLOCK_NOCAR;
			CharacterInfo[playerid2][pBlockNoCar] += time*60;
			GivePenalty(playerid2, playerid, gettime(), PENALTY_NOCAR, time, reason);
			
			//msg_infoFormat(playerid2, 256, "Administrator %s na³o¿y³ Ci blokadê prowadzenia pojazdów na %d minut.\nPowód: %s", CharacterInfo[playerid][pGlobalNick], time, reason);
			SendClientMessageFormat(playerid, COLOR_RED, "[AI] Na³o¿y³eœ blokadê prowadzenia pojazdów na gracza %s (%d). Czas: %d min.", PlayerName3(playerid2), playerid2, time);
			SavePlayerStats(playerid2, SAVE_PLAYER_PENALTY);
			
			if(GetPlayerState(playerid2) == PLAYER_STATE_DRIVER)
				RemovePlayerFromVehicle(playerid2);
		}
	}
	
	return 1;
}

CMD:noooc(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 3) return 1;
	
	new playerid2, time, reason[64];
	if(sscanf(params, "dds[64]", playerid2, time, reason))
		return msg_usage(playerid,"U¿yj: /noooc [ID gracza] [czas(min)] [powód]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		
		if(time == 0)
		{
			if(CharacterInfo[playerid2][pBlock] & BLOCK_NOOOC)
			{
				CharacterInfo[playerid2][pBlock] -= BLOCK_NOOOC;
				CharacterInfo[playerid2][pBlockNoOOC] = 0;
				SendClientMessageFormat(playerid2, COLOR_GREEN, "[AI] Administrator %s zdj¹³ Ci blokadê czatów OOC.", CharacterInfo[playerid][pGlobalNick]);
				SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Zdj¹³eœ blokadê czatów OOC graczowi %s (%d).", PlayerName3(playerid2), playerid2);
				SendAdminMessageFormat(COLOR_GREEN,"[AI] %s zdja³ blokadê czatów OOC graczowi %s (%d).", CharacterInfo[playerid][pGlobalNick], PlayerName3(playerid2), playerid2);
				SavePlayerStats(playerid2, SAVE_PLAYER_PENALTY);
				return 1;
			}
			else
				return msg_error(playerid, "Wybrany gracz nie posiada aktywnej blokady czatów OOC.");
		}
		else
		{
			if(CharacterInfo[playerid2][pBlockNoOOC])
				return msg_error(playerid, "Wybrany gracz ma ju¿ blokadê.");
			if(CharacterInfo[playerid2][pCurse] > gettime() && time >30)
			{
				SendClientMessage(playerid2, COLOR_RED, "Posiadasz aktywn¹ kl¹twe, na konto zostaje na³o¿ona banicja.");

				CharacterInfo[playerid2][pBlock]+=BLOCK_BAN;
				AddBan(playerid2);
				GivePenalty(playerid2, playerid, gettime(), PENALTY_BAN_CURSE, 0, reason);
				SavePlayerStats(playerid2, SAVE_PLAYER_PENALTY);	
				KickWithWait(playerid2);
				return 1;
			}
		
			CharacterInfo[playerid2][pBlock] += BLOCK_NOOOC;
			CharacterInfo[playerid2][pBlockNoOOC] += time*60;
			GivePenalty(playerid2, playerid, gettime(), PENALTY_NOOOC, time, reason);
			
			//SendClientMessageFormat(playerid2, COLOR_RED, "[AI] Administrator %s na³o¿y³ Ci blokadê czatów OOC na %d minut. Powód: %s", CharacterInfo[playerid][pGlobalNick], time, reason);
			SendClientMessageFormat(playerid, COLOR_RED, "[AI] Na³o¿y³eœ blokadê czatów OOC na gracza %s (%d). Czas: %d min.", PlayerName3(playerid2), playerid2, time);
			SavePlayerStats(playerid2, SAVE_PLAYER_PENALTY);
		}
	}
	
	return 1;
}

CMD:norun(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 3) return 1;
	
	new playerid2, time, reason[64];
	if(sscanf(params, "dds[64]", playerid2, time, reason))
		return msg_usage(playerid,"U¿yj: /norun [ID gracza] [czas(min)] [powód]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		
		if(time == 0)
		{
			if(CharacterInfo[playerid2][pBlock] & BLOCK_NORUN)
			{
				CharacterInfo[playerid2][pBlock] -= BLOCK_NORUN;
				CharacterInfo[playerid2][pBlockNoRun] = 0;
				SendClientMessageFormat(playerid2, COLOR_GREEN, "[AI] Administrator %s zdj¹³ Ci blokadê biegania.", CharacterInfo[playerid][pGlobalNick]);
				SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Zdj¹³eœ blokadê biegania graczowi %s (%d).", PlayerName3(playerid2), playerid2);
				SendAdminMessageFormat(COLOR_GREEN,"[AI] %s zdja³ blokadê biegania graczowi %s (%d).", CharacterInfo[playerid][pGlobalNick], PlayerName3(playerid2), playerid2);
				SavePlayerStats(playerid2, SAVE_PLAYER_PENALTY);
			}
			else
				return msg_error(playerid, "Wybrany gracz nie posiada aktywnej blokady biegania.");
		}
		else
		{
			if(CharacterInfo[playerid2][pBlockNoRun])
				return msg_error(playerid, "Wybrany gracz ma ju¿ blokadê.");
			if(CharacterInfo[playerid2][pCurse] > gettime() && time >30)
			{
				SendClientMessage(playerid2, COLOR_RED, "Posiadasz aktywn¹ kl¹twe, na konto zostaje na³o¿ona banicja.");

				CharacterInfo[playerid2][pBlock]+=BLOCK_BAN;
				AddBan(playerid2);
				GivePenalty(playerid2, playerid, gettime(), PENALTY_BAN_CURSE, 0, reason);
				SavePlayerStats(playerid2, SAVE_PLAYER_PENALTY);	
				KickWithWait(playerid2);
				return 1;
			}
		
			CharacterInfo[playerid2][pBlock] += BLOCK_NORUN;
			CharacterInfo[playerid2][pBlockNoRun] += time*60;
			GivePenalty(playerid2, playerid, gettime(), PENALTY_NORUN, time, reason);
			
			//SendClientMessageFormat(playerid2, COLOR_RED, "[AI] Administrator %s na³o¿y³ Ci blokadê biegania na %d minut. Powód: %s", CharacterInfo[playerid][pGlobalNick], time, reason);
			SendClientMessageFormat(playerid, COLOR_RED, "[AI] Na³o¿y³eœ blokadê biegania na gracza %s (%d). Czas: %d min.", PlayerName3(playerid2), playerid2, time);
			SavePlayerStats(playerid2, SAVE_PLAYER_PENALTY);
		}
	}
	
	return 1;
}

CMD:agrupa(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 5) return 1;
	
	new comm1[32], comm2[64];
	if(sscanf(params, "s[32]S()[64]", comm1, comm2))
		return msg_usage(playerid,"U¿yj: /agrupa [lista | stworz | nazwa | tag | lider | cash | flagi | usun | dolacz | rejestracja | typ | czysc]");
	else
	{
		if(!strcmp(comm1, "lista", true))
		{
			SendClientMessage(playerid, COLOR_GREEN, "\t* Lista grup *");
			new string[96];	
			ForeachEx(i, MAX_GROUPS)
			{
				if(GroupInfo[i][gUID])
				{
					format(string,sizeof(string),"%d:{ffffff} %s %s $%d, Lider: %d", i, GroupInfo[i][gName], GroupInfo[i][gTag], GroupInfo[i][gCash],GroupInfo[i][gLeader]);
					SendClientMessage(playerid,COLOR_GREEN,string);
				}
			}
			
		}
		else if(!strcmp(comm1, "stworz", true))
		{
			ShowPlayerDialog(playerid, D_GROUP_CREATE, DIALOG_STYLE_INPUT, DEF_NAME" » tworzenie grupy", "Wpisz nazwê nowej grupy:", "Dalej", "Anuluj");
		}
		else if(!strcmp(comm1, "nazwa", true))
		{
			new uid;
			if(sscanf(comm2, "d", uid))
				return msg_usage(playerid,"/agrupa nazwa [UID grupy]");
			else
			{
				if(!GroupInfo[uid][gUID])
					return msg_error(playerid, "Brak grupy o podanym UID.");
				
				SetPVarInt(playerid, "GroupNameChangeUID", uid);
				
				ShowPlayerDialog(playerid, D_GROUP_CHANGE_NAME, DIALOG_STYLE_INPUT, DEF_NAME" » zmiana nazwy", "Wpisz now¹ nazwe:", "Dalej", "Anuluj");
			}
		}
		else if(!strcmp(comm1, "tag", true))
		{
			new uid;
			if(sscanf(comm2, "d", uid))
				return msg_usage(playerid,"/agrupa tag [UID grupy]");
			else
			{
				if(!GroupInfo[uid][gUID])
					return msg_error(playerid, "Brak grupy o podanym UID.");
				
				SetPVarInt(playerid, "GroupTagChangeUID", uid);
				
				ShowPlayerDialog(playerid, D_GROUP_CHANGE_TAG, DIALOG_STYLE_INPUT, DEF_NAME" » zmiana tagu", "Wpisz nowy tag:", "Dalej", "Anuluj");
			}
		}
		else if(!strcmp(comm1, "lider", true))
		{
			new uid, playerid2;
			if(sscanf(comm2, "di", uid, playerid2))
				return msg_usage(playerid,"/agrupa lider [UID grupy] [ID gracza]");
			else
			{
				if(!GroupInfo[uid][gUID])
					return msg_error(playerid, "Brak grupy o podanym UID.");
				if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
					return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
				if(IsPlayerInGroup(playerid2, uid))
					return msg_error(playerid,"Wybrany gracz jest cz³onkiem tej grupy.");
				if(!HaveFreeSlotGroup(playerid2))
					return msg_error(playerid,"Wybrany gracz nie posiada wolnego slota.");
				
				new bool:have[2] = false;
				if(IsPlayerGroupPerm(playerid2, FLAG_GPS))
					have[0] = true;
				if(IsPlayerInOfficialGroup(playerid2) || IsPlayerInBuisnessGroup(playerid2))
					have[1] = true;
				
				GroupInfo[uid][gLeader] = CharacterInfo[playerid2][pUID];
				SaveGroup(uid, SAVE_GROUP_BASIC);
				AddMember(playerid2,uid,255);
				
				SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Pomyœlnie nada³eœ %s lidera grupy %s [UID: %d] .", PlayerName3(playerid2), GroupInfo[uid][gName], uid);
				msg_infoFormat(playerid2, 128, "Zosta³eœ mianowany liderem grupy %s [UID: %d] przez administratora %s.", GroupInfo[uid][gName], uid, CharacterInfo[playerid][pGlobalNick]);
				
				if(IsPlayerGroupPerm(playerid2, FLAG_GPS) && !have[0])
				{
					if(CharacterInfo[playerid2][pTog] & TOG_STATUS)
					{
						PlayerTextDrawShow(playerid2, TDEditor_PTD[playerid2][0]);
						
						PlayerTextDrawHide(playerid2, TDEditor_PTD[playerid2][1]);
						PlayerTextDrawShow(playerid2, TDEditor_PTD[playerid2][2]);
					}
				}
				
				if(IsPlayerInOfficialGroup(playerid2) || IsPlayerInBuisnessGroup(playerid2) && !have[1])
				{
					if(CharacterInfo[playerid2][pTog] & TOG_STATUS)
					{
						PlayerTextDrawShow(playerid2, TDEditor_PTD[playerid2][6]);
						
						PlayerTextDrawHide(playerid2, TDEditor_PTD[playerid2][7]);
						PlayerTextDrawShow(playerid2, TDEditor_PTD[playerid2][8]);
					}
				}
			}
		}
		else if(!strcmp(comm1, "dolacz", true) || !strcmp(comm1, "do³¹cz", true))
		{
			new uid;
			if(sscanf(comm2, "di", uid))
				return msg_usage(playerid,"/agrupa dolacz [UID grupy]");
			else
			{
				if(!GroupInfo[uid][gUID])
					return msg_error(playerid, "Brak grupy o podanym UID.");
				if(IsPlayerInGroup(playerid, uid))
					return msg_error(playerid,"Jesteœ ju¿ cz³onkiem tej grupy.");
				if(!HaveFreeSlotGroup(playerid))
					return msg_error(playerid,"Nie posiadasz wolnego slota.");
				
				new bool:have[2] = false;
				if(IsPlayerGroupPerm(playerid, FLAG_GPS))
					have[0] = true;
				if(IsPlayerInOfficialGroup(playerid) || IsPlayerInBuisnessGroup(playerid))
					have[1] = true;
				
				AddMember(playerid,uid,255);
				SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Pomyœlnie do³¹czy³eœ do grupy %s [UID: %d] .",GroupInfo[uid][gName],uid);
				
				if(IsPlayerGroupPerm(playerid, FLAG_GPS) && !have[0])
				{
					if(CharacterInfo[playerid][pTog] & TOG_STATUS)
					{
						PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][0]);
						
						PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][1]);
						PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][2]);
					}
				}
				
				if(IsPlayerInOfficialGroup(playerid) || IsPlayerInBuisnessGroup(playerid) && !have[1])
				{
					if(CharacterInfo[playerid][pTog] & TOG_STATUS)
					{
						PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][6]);
						
						PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][7]);
						PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][8]);
					}
				}
			}
		}
		else if(!strcmp(comm1, "cash", true))
		{
			if(CharacterInfo[playerid][pAdmin]<6)
				return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy");
			new uid, cash;
			if(sscanf(comm2, "dd", uid, cash))
				return msg_usage(playerid,"/agrupa cash [UID grupy] [iloœæ gotówki do dodania]");
			else
			{
				if(!GroupInfo[uid][gUID])
					return msg_error(playerid, "Brak grupy o podanym UID.");
				
				GroupInfo[uid][gCash] += cash;
				SaveGroup(uid, SAVE_GROUP_BASIC);
				
				SendClientMessage(playerid, COLOR_GREEN, "[AI] Pomyœlnie doda³eœ pieni¹dze do banku grupy.");
			}
		}
		else if(!strcmp(comm1, "pracownicze", true))
		{
			if(CharacterInfo[playerid][pAdmin]<6)
				return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy");
			new uid, cash;
			if(sscanf(comm2, "dd", uid, cash))
				return msg_usage(playerid,"/agrupa pracownicze [UID grupy] [nowy stan konta]");
			else
			{
				if(!GroupInfo[uid][gUID])
					return msg_error(playerid, "Brak grupy o podanym UID.");
				
				GroupInfo[uid][gSalaryAccount] = cash;
				SaveGroup(uid, SAVE_GROUP_BASIC);
				
				SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Konto pracownicze grupy %s[UID:%d] zosta³o zmienione na $%d.",GroupInfo[uid][gName],uid,cash);
			}
		}
		else if(!strcmp(comm1, "flagi", true))
		{
			new uid;
			if(sscanf(comm2, "d", uid))
				return msg_usage(playerid,"/agrupa flagi [UID grupy]");
			else
			{
				if(!GroupInfo[uid][gUID])
					return msg_error(playerid, "Brak grupy o podanym UID.");
				new name[64];
				format(name,sizeof(name),DEF_NAME" » flagi %s [%d]",GroupInfo[uid][gName], uid);
				
				SetPVarInt(playerid, "GroupFlagsUID", uid);
				new string[384];
				
				if(GroupInfo[uid][gFlags] & FLAG_DEPARTMENT) format(string, sizeof(string), "%s\nCzat departamentowy (/d)\t\t{99FF00}T", string);
				else format(string, sizeof(string), "%s\nCzat departamentowy (/d)\t\t{990000}N", string);
				
				if(GroupInfo[uid][gFlags] & FLAG_MEGAPHONE) format(string, sizeof(string), "%s\nU¿ywanie megafonu (/m)\t\t{99FF00}T", string);
				else format(string, sizeof(string), "%s\nU¿ywanie megafonu (/m)\t\t{990000}N", string);
				
				if(GroupInfo[uid][gFlags] & FLAG_NICK) format(string, sizeof(string), "%s\nKolorowy nick (s³u¿ba)\t\t\t{99FF00}T", string);
				else format(string, sizeof(string), "%s\nKolorowy nick (s³u¿ba)\t\t\t{990000}N", string);
				
				if(GroupInfo[uid][gFlags] & FLAG_OUT) format(string, sizeof(string), "%s\nMo¿liwoœæ opuszczania grupy\t\t{99FF00}T", string);
				else format(string, sizeof(string), "%s\nMo¿liwoœæ opuszczania grupy\t\t{990000}N", string);
				
				if(GroupInfo[uid][gFlags] & FLAG_CASH) format(string, sizeof(string), "%s\nDostêp do banku\t\t\t{99FF00}T", string);
				else format(string, sizeof(string), "%s\nDostêp do banku\t\t\t{990000}N", string);
				
				if(GroupInfo[uid][gFlags] & FLAG_JAIL) format(string, sizeof(string), "%s\nPrzetrzymywanie (cele)\t\t\t{99FF00}T", string);
				else format(string, sizeof(string), "%s\nPrzetrzymywanie (cele)\t\t\t{990000}N", string);
				
				if(GroupInfo[uid][gFlags] & FLAG_ITEM) format(string, sizeof(string), "%s\nZabieranie przedmiotów\t\t{99FF00}T", string);
				else format(string, sizeof(string), "%s\nZabieranie przedmiotów\t\t{990000}N", string);
				
				if(GroupInfo[uid][gFlags] & FLAG_911) format(string, sizeof(string), "%s\nNumer alarmowy (911)\t\t\t{99FF00}T", string);
				else format(string, sizeof(string), "%s\nNumer alarmowy (911)\t\t\t{990000}N", string);
				
				if(GroupInfo[uid][gFlags] & FLAG_REPORTS) format(string, sizeof(string), "%s\nZg³oszenia grupowe\t\t\t{99FF00}T", string);
				else format(string, sizeof(string), "%s\nZg³oszenia grupowe\t\t\t{990000}N", string);
				
				if(GroupInfo[uid][gFlags] & FLAG_GPS) format(string, sizeof(string), "%s\nGPS w pojazdach\t\t\t{99FF00}T", string);
				else format(string, sizeof(string), "%s\nGPS w pojazdach\t\t\t{990000}N", string);
				
				ShowPlayerDialog(playerid, D_GROUP_LIST_FLAGS, DIALOG_STYLE_LIST, name, string, "Zmieñ", "Zamknij");
			}
		}
		else if(!strcmp(comm1, "usun", true))
		{
			new uid;
			if(sscanf(comm2, "d", uid))
				return msg_usage(playerid,"/agrupa usun [UID grupy]");
			else
			{
				if(!GroupInfo[uid][gUID])
					return msg_error(playerid, "Brak grupy o podanym UID.");
				
				new string[128];
				format(string,sizeof(string),"Czy na pewno chcesz usun¹æ grupê %s [UID: %d]?\nOperacji nie mozna cofn¹æ.",GroupInfo[uid][gName],uid);
				SetPVarInt(playerid,"GroupDeleteID",uid);
				ShowPlayerDialog(playerid,D_AG_DELETE,DIALOG_STYLE_MSGBOX,DEF_NAME" » usuwanie grupy",string,"Tak","Nie");
			}
		}
		else if(!strcmp(comm1, "rejestracja", true))
		{
			new uid, reg;
			if(sscanf(comm2, "dd", uid, reg))
				return msg_usage(playerid,"/agrupa rejestracja [UID grupy] [0/1]");
			else
			{
				if(!GroupInfo[uid][gUID])
					return msg_error(playerid, "Brak grupy o podanym UID.");
				
				switch(reg)
				{
					case 0:
					{
						if(GroupInfo[uid][gRegistered])
						{
							GroupInfo[uid][gRegistered] = 0;
							SaveGroup(uid, SAVE_GROUP_BASIC);
							msg_info(playerid, "Odrejestrowa³eœ grupê.");
						}
						else
							return msg_error(playerid, "Grupa nie jest zarejestrowana.");
					}
					case 1:
					{
						if(!GroupInfo[uid][gRegistered])
						{
							GroupInfo[uid][gRegistered] = 1;
							SaveGroup(uid, SAVE_GROUP_BASIC);
							msg_info(playerid, "Zarejestrowa³eœ grupê.");
						}
						else
							return msg_error(playerid, "Grupa jest ju¿ zarejestrowana.");
					}
				}
			}
		}
		else if(!strcmp(comm1, "typ", true))
		{
			new uid;
			if(sscanf(comm2, "d", uid))
				return msg_usage(playerid,"/agrupa typ [UID grupy]");
			else
			{
				if(!GroupInfo[uid][gUID])
					return msg_error(playerid, "Brak grupy o podanym UID.");
				
				SetPVarInt(playerid, "agrupatyp", uid);
				
				new string[1496];
				ForeachEx(i, GROUP_COUNT + 1)
					format(string, sizeof(string), "%s\n%s", string, GroupTypeInfo[i][gTypeName]);
				
				ShowPlayerDialog(playerid, D_GROUP_CHANGE_TYPE, DIALOG_STYLE_LIST, DEF_NAME" » typ grupy", string, "Wybierz", "Anuluj");
			}
		}
		if(!strcmp(comm1, "czysc", true))
		{
			new uid;
			if(sscanf(comm2, "d", uid))
				return msg_usage(playerid,"/agrupa czysc [UID grupy]\n\nUsuwa wszystkich pracowników z grupy.");

			if(!GroupInfo[uid][gUID])
				return msg_error(playerid, "Brak grupy o podanym UID.");

			SetPVarInt(playerid, "clearGroupID", uid);
			new string[96];
			format(string,sizeof(string),"Czy na pewno chcesz usunac wszystkich pracowników z grupy %s[UID:%d]?",GroupInfo[uid][gName],uid);
			ShowPlayerDialog(playerid, D_GROUP_CLEAR, DIALOG_STYLE_MSGBOX, DEF_NAME" » czyszczenie grupy", string, "PotwierdŸ", "Anuluj");
		}
	}
	
	return 1;
}
CMD:ag(playerid, params[]) return cmd_agrupa(playerid,params);

CMD:aprodukt(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin]<5) return 1;
	new comm1[16], comm2[64];
	if(sscanf(params, "s[16]S()[64]", comm1, comm2))
		return msg_usage(playerid,"U¿yj: /aprodukt  [dodaj]");
	else
	{
		if(!strcmp(comm1, "dodaj", true))
		{
			new groupid, name[32], type, value1, value2, count;
			if(sscanf(comm2, "ddddds[32]", groupid, type, value1, value2, count,name))
				return msg_usage(playerid,"U¿yj: /aprodukt dodaj [UID grupy] [typ] [wartoœæ1] [wartoœæ2] [iloœæ] [nazwa]\n\nTypy przedmiotów dostepne pod /ap(rzedmiot) typy");
			if(!GroupInfo[groupid][gUID])
				return msg_error(playerid,"Mie znaleziono grupy o podanym UID");
			
			StworzPrzedmiot(OWNER_GROUP, groupid, name, type, value1, value2, count);
			
			msg_infoFormat(playerid, 256, "[AI] Stworzy³eœ %d przedmiot/ów %s [%d:%d] dla grupy %s",count, name,value1,value2,GroupInfo[groupid][gName]);
			
			return 1;
		}
	}

	return 1;
}

CMD:premium(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin]<6) return 1;
	new comm1[16], comm2[16];
	if(sscanf(params, "s[16]S()[16]", comm1, comm2))
		return msg_usage(playerid,"U¿yj: /premium [on | off]");
	else
	{
		if(!strcmp(comm1, "on", true))
		{
			new days;
			if(sscanf(comm2, "d", days))
				return msg_usage(playerid,"U¿yj: /premium on [ilosc dni]");
			else
			{
				if(days < 1)
					return msg_error(playerid,"Nie mo¿esz ustawiæ mniej ni¿ jeden dzieñ.");
				if(SettingInfo[sPremiumEventDays])
					return msg_error(playerid,"Obecnie trwa ju¿ EVENT PREMIUM. Aby zmieniæ iloœæ dni najpierw go zakoñcz.");
				
				SettingInfo[sPremiumEventDays] = days;
				
				new query[64];
				format(query, sizeof(query), "UPDATE `srv_settings` SET `premiumeventdays` = '%d'", days);
				mysql_query(query);
				
				SendAdminMessageFormat(COLOR_YELLOW, "[AI] %s w³¹czy³ event PREMIUM (%d dni)!", CharacterInfo[playerid][pGlobalNick], days);
			}
		}
		else if(!strcmp(comm1, "off", true))
		{
			if(!SettingInfo[sPremiumEventDays])
				return msg_error(playerid,"Obecnie nie trwa EVENT PREMIUM.");
			
			SettingInfo[sPremiumEventDays] = 0;
			
			new query[64];
			format(query, sizeof(query), "UPDATE `srv_settings` SET `premiumeventdays` = 0");
			mysql_query(query);
			
			SendAdminMessageFormat(COLOR_YELLOW, "[AI] %s wy³¹czy³ event PREMIUM.", CharacterInfo[playerid][pGlobalNick]);
		}
	}
	
	
	return 1;
}

CMD:glob(playerid, params[])
{
	if(!CharacterInfo[playerid][pAdmin]) return 1;
	
	new text[144];
	if(sscanf(params, "s[144]", text))
		return msg_usage(playerid,"U¿yj: /glob [treœæ]");
	else
	{
		ForeachPlayer(i)
		{
			if(strlen(text) < 64)
			{
				if(CharacterInfo[playerid][pAdmin] == 1)
					SendClientMessageFormat(i, COLOR_WHITE, "(({FF9900}[Opiekun]{FFFFFF} %s (%d): %s))", CharacterInfo[playerid][pGlobalNick], playerid, text);
				else if(CharacterInfo[playerid][pAdmin] < 5)
					SendClientMessageFormat(i, COLOR_WHITE, "(({8B00B0}[GameMaster]{FFFFFF} %s (%d): %s))", CharacterInfo[playerid][pGlobalNick], playerid, text);
				else
					SendClientMessageFormat(i, COLOR_WHITE, "(({B00000}[Administrator]{FFFFFF} %s (%d): %s))", CharacterInfo[playerid][pGlobalNick], playerid, text);
			}
			else
			{
				new pos = strfind(text, " ", true, strlen(text)/2);
				if(pos != -1)
				{
					new text2[72];
					
					strmid(text2, text, pos+1, strlen(text));
					strdel(text, pos, strlen(text));
					
					if(CharacterInfo[playerid][pAdmin] == 1)
					{
						SendClientMessageFormat(i, COLOR_WHITE, "(({FF9900}[Opiekun]{FFFFFF} %s (%d): %s ...", CharacterInfo[playerid][pGlobalNick], playerid, text);
						SendClientMessageFormat(i, COLOR_WHITE, "...%s))", text2);
					}
					else if(CharacterInfo[playerid][pAdmin] < 5)
					{
						SendClientMessageFormat(i, COLOR_WHITE, "(({8B00B0}[GameMaster]{FFFFFF} %s (%d): %s ...", CharacterInfo[playerid][pGlobalNick], playerid, text);
						SendClientMessageFormat(i, COLOR_WHITE, "...%s))", text2);
					}
					else
					{
						SendClientMessageFormat(i, COLOR_WHITE, "(({B00000}[Administrator]{FFFFFF} %s (%d): %s ...", CharacterInfo[playerid][pGlobalNick], playerid, text);
						SendClientMessageFormat(i, COLOR_WHITE, "...%s))", text2);
					}
				}
			}
		}
	}
	
	return 1;
}

CMD:ado(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin]<1) return 1;
	
	new text[144];
	if(sscanf(params, "s[128]", text))
		return msg_usage(playerid,"U¿yj: /ado [sytuacja]");
	else
	{
		ForeachPlayer(i)
		{
			text[0] = chrtoupper(text[0]);
		
			if(strlen(text) < 72)
				SendClientMessageFormat(i, COLOR_DO, "** %s **", text);
			else
			{
				new pos = strfind(text, " ", true, strlen(text) / 2);
				if(pos != -1)
				{
					new text2[72];
					
					strmid(text2, text, pos + 1, strlen(text));
					strdel(text, pos, strlen(text));
					
					SendClientMessageFormat(i, COLOR_DO, "** %s", text);
					
					SendClientMessageFormat(i, COLOR_DO, "...%s **", text2);
				}
			}
		}
	}
	
	return 1;
}

CMD:askin(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin]) 
	{
		new skin;
		if(sscanf(params,"d",skin))
			return msg_usage(playerid,"U¿yj: /askin [id skina]");
		else if(skin < 1 || skin > 311)
			return msg_error(playerid,"Niepoprawne id skina.");
		
		CharacterInfo[playerid][pSkin]=skin;
		SetPlayerSkin(playerid,skin);
		SendClientMessageFormat(playerid, COLOR_GREEN, "Zmieni³eœ swój skin na %d.", skin);
	}

	return 1;
}

CMD:nick(playerid,params[])
{
	if(!CharacterInfo[playerid][pAdmin] && !IsPlayerOnDutyInGroup(playerid, GROUP_FBI)) return 1;
	
	new nick[32];
	if(sscanf(params, "s[32]", nick))
		return msg_usage(playerid, "U¿yj: /nick [Imie_Nazwisko]");
	if(strlen(nick) < 3 || strlen(nick) > 21)
		return msg_error(playerid, "Niepoprawna d³ugoœæ nicku.");
	
	SetPlayerName(playerid, nick);
	msg_info(playerid, "Zmieni³eœ swój nick.");
	
	log("%s [player: %d] zmieni³ sobie nick na: %s", PlayerName3(playerid), CharacterInfo[playerid][pUID], nick);
	
	return 1;
}

CMD:astacja(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin] < 5) return 1;
	
	new comm1[16],comm2[8];

	if(sscanf(params,"s[16]S()[8]",comm1,comm2))
		return msg_usage(playerid,"U¿yj: /astacja [ stworz | usun | owner | paliwo | goto | lista]");
	else if(!strcmp(comm1, "stworz", true))
	{
		if(GetPlayerStationID(playerid))
			return msg_error(playerid,"W tym miejscu znajduje siê inna stacja.");
		
		new Float:x,Float:y,Float:z;
		GetPlayerPos(playerid, x, y, z);

		new uid = CreateFuelStation(1,x,y,z);
		if(uid)
			SendClientMessageFormat(playerid, COLOR_GREEN,"[AI] Stacja uid %d stworzona pomyœlnie.",uid);
		else
			msg_error(playerid,"Nie mo¿na stworzyæ wiêcej stacji.");
	}
	else if(!strcmp(comm1, "usun", true))
	{
		new uid = GetPlayerStationID(playerid);
		if(!uid)
			return msg_error(playerid,"Nie znajdujesz siê na ¿adnej stacji paliw.");
		
		SetPVarInt(playerid, "DeleteStationID", uid);
		ShowPlayerDialog(playerid, D_STATION_DELETE, DIALOG_STYLE_MSGBOX, DEF_NAME" » usuwanie stacji", "Czy na pewno chcesz usun¹æ stacjê na której siê znajdujesz?", "PotwierdŸ", "Anuluj");
	}
	else if(!strcmp(comm1, "owner", true))
	{
		new stationid = GetPlayerStationID(playerid);
		if(!stationid)
			return msg_error(playerid,"Nie znajdujesz siê na ¿adnej stacji paliw.");
		
		new groupid;
		if(sscanf(comm2,"d",groupid))
			return msg_usage(playerid,"U¿yj: /astacja owner [ID grupy].\n\n0 - brak w³aœciciela");
		if(groupid && !GroupInfo[groupid][gUID])
			return msg_error(playerid,"Grupa o podanym ID nie istnieje.");
		
		StationInfo[stationid][sOwner] = groupid;
		
		new query[128];
		format(query, sizeof(query), "UPDATE `srv_fuel_stations` SET `owner`='%d' WHERE `uid`='%d'", groupid, stationid);
		mysql_query(query);
		
		SendClientMessageFormat(playerid,COLOR_GREEN,"[AI] W³aœciciel stacji zosta³ zmieniony na %d.",groupid);
	}
	else if(!strcmp(comm1, "paliwo", true))
	{
		new stationid = GetPlayerStationID(playerid);
		if(!stationid)
			return msg_error(playerid,"Nie znajdujesz siê na ¿adnej stacji paliw.");
		
		new value;
		if(sscanf(comm2,"d",value))
			return msg_usage(playerid,"U¿yj: /astacja paliwo [iloœæ].");
		if(value < 0 || value > 20000)
			return msg_error(playerid,"Niepoprawna ilosæ paliwa.");
		
		AddStationFuel(stationid,-StationInfo[stationid][sFuel]);
		AddStationFuel(stationid,value);
		SendClientMessageFormat(playerid,COLOR_GREEN,"Iloœæ paliwa na stacji zosta³¹ zmieniona na: %d.", value);
	}
	else if(!strcmp(comm1, "lista", true))
	{
		SendClientMessage(playerid,COLOR_GREEN,"\t*Lista stacji paliw*");
		new string[64];
		for(new i=1;i<MAX_STATIONS;i++)
		{
			if(StationInfo[i][sUID])
			{
				format(string,sizeof(string),"%d:{ffffff} Paliwo: %4d   W³aœciciel: %d.", i,StationInfo[i][sFuel],StationInfo[i][sOwner]);
				SendClientMessage(playerid,COLOR_GREEN,string);
			}
		}	
	}
	else if(!strcmp(comm1, "goto", true))
	{
		new stationid;
		if(sscanf(comm2,"d",stationid))
			return msg_usage(playerid,"U¿yj: /astacja goto [ID stacji].");
		if(stationid >= MAX_STATIONS)
			return msg_error(playerid,"Stacja o podanym ID nie istnieje.");
		if(!StationInfo[stationid][sUID])
			return msg_error(playerid,"Stacja o podanym ID nie istnieje.");
		
		SetPlayerPos(playerid, StationInfo[stationid][sPosX], StationInfo[stationid][sPosY], StationInfo[stationid][sPosZ]);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
	}

	return 1;
}
CMD:abus(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin] < 5) return 1;
	new comm1[8],comm2[32];
	if(sscanf(params,"s[8]S()[32]",comm1,comm2))
		return msg_usage(playerid,"U¿yj: /abus [stworz | usun | lista | goto]");
	if(!strcmp(comm1,"stworz",true) || !strcmp(comm1,"stwórz",true))
	{
		new name[32];
		if(GetPlayerVirtualWorld(playerid))
			return msg_error(playerid,"Przystanki mo¿na tworzyæ tylko na vw0.");
		if(sscanf(comm2,"s[32]",name))
			return msg_usage(playerid,"U¿yj: /abus stworz [nazwa]");
		new uid;
		for(new i=1;i<MAX_BUS_STOPS;i++)
		{
			if(!BusInfo[i][bUID])
			{
				uid=i;
				break;
			}
		}
		if(!uid)
			return msg_error(playerid,"Nie mo¿na stworzyæ wiêcej przystanków");
		new Float:x,Float:y,Float:z,Float:angle,string[128];
		GetPlayerPos(playerid,x,y,z);
		GetPlayerFacingAngle(playerid, angle);

		format(string,sizeof(string),"Przystanek:{ffffff} %s ((/bus))",name);

		BusInfo[uid][bUID]=uid;
		BusInfo[uid][bName]=name;
		BusInfo[uid][bPosX]=x;
		BusInfo[uid][bPosY]=y;
		BusInfo[uid][bPosZ]=z;
		BusInfo[uid][bAngle]=angle;
		BusInfo[uid][b3Dtext]=CreateDynamic3DTextLabel(string, 0x1231FFFF, x, y, z, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
		format(string,sizeof(string),"INSERT INTO `srv_bus` VALUES ('%d','%s','%f','%f','%f','%f')",uid,name,x,y,z,angle);
		mysql_query(string);
		format(string,sizeof(string),"Stworzy³es przystanek %d:%s. Dodaj obiekt: 1257 - przystanek, 1229 - tabliczka",uid,name);
		SendClientMessage(playerid, COLOR_GREEN, string);
	}
	else if(!strcmp(comm1,"usun",true) || !strcmp(comm1,"usuñ",true))
	{
		new uid;
		if(sscanf(comm2,"d",uid))
			return msg_usage(playerid,"U¿yj: /abus usun [id]");

		if((uid && !BusInfo[uid][bUID]) || (!uid && !BusInfo[uid][bPosX]))
			return msg_error(playerid,"Przystanek o wybraym id nie istnieje.");

		new string[128];
		format(string,sizeof(string),"Usun¹³eœ przystanek %d:%s",uid,BusInfo[uid][bName]);
		SendClientMessage(playerid, COLOR_RED, string);
		BusInfo[uid][bUID]=0;
		BusInfo[uid][bName]=0;
		BusInfo[uid][bPosX]=
		BusInfo[uid][bPosY]=
		BusInfo[uid][bPosZ]=
		BusInfo[uid][bAngle]=0;
		format(string,sizeof(string),"DELETE FROM `srv_bus` WHERE `uid`='%d'",uid);
		mysql_query(string);
		DestroyDynamic3DTextLabel(BusInfo[uid][b3Dtext]);
	}
	else if(!strcmp(comm1,"lista",true))
	{
		new string[64];
		SendClientMessage(playerid, COLOR_GREEN, "\t* Lista przystanków *");
		for(new i=1;i<MAX_BUS_STOPS;i++)
		{
			if(BusInfo[i][bUID])
			{
				format(string,sizeof(string),"%d:{ffffff} %s",i,BusInfo[i][bName]);
				SendClientMessage(playerid, COLOR_GREEN, string);
			}
		}
	}
	else if(!strcmp(comm1,"goto",true))
	{
		new uid;
		if(sscanf(comm2,"d",uid))
			return msg_usage(playerid,"U¿yj: /abus goto [id]");

		if(!BusInfo[uid][bPosX])
			return msg_error(playerid,"Przystanek o podanym id nie istnieje");

		SetPlayerPos(playerid,BusInfo[uid][bPosX],BusInfo[uid][bPosY],BusInfo[uid][bPosZ]);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerInterior(playerid, 0);
		SetPlayerFacingAngle(playerid, BusInfo[uid][bAngle]);
	}

	return 1;
}
CMD:dekoduj(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin] < 2) return 1;
	new code[8];
	if(sscanf(params,"s[8]",code))
		return msg_usage(playerid,"U¿yj: /dekoduj [kod maski]");
	if(strlen(code)>6 || strlen(code)<5)
		return msg_error(playerid,"Wprowadzono nieprawid³owy kod.");
	for(new i=0;i<6;i++)
		code[i]=toupper(code[i]);
	new pref=code[0];
  	new suf=strval(code[5]);
  	new dec[5];
  	strmid(dec, code, 1, 5);

  	for(new j=0;j<4;j++)
  	{
  		if(dec[j]>60)
  			dec[j]-=55;
  		else
  			dec[j]-=48;
  	}
  	new number=dec[0]+ dec[1]*17 + dec[2]*289 + dec[3]*4913;
  	if(pref<'K')
  		number=number-pref-5371-18*suf;
  	else if(pref>='W')
  		number=number-pref-23-18*suf;
  	else
  		number=number-pref-4357-18*suf;

  	if(number<0 || number> 80000)
  		return msg_error(playerid,"Wprowadzono nieprawid³owy kod.");

  	new query[256],name[MAX_PLAYER_NAME],global[16];
  	new bool:found=false;
  	format(query,sizeof(query),"SELECT `srv_characters`.`nickname`, `members`.`members_display_name` FROM `srv_characters`, `members` WHERE `srv_characters`.`player_uid`='%d' AND `srv_characters`.`global_id`=`members`.`member_id`",number);
  	mysql_query(query);
  	mysql_store_result();
  	if(mysql_num_rows())
  	{
  		found=true;
  		mysql_fetch_row_format(query);
  		sscanf(query, "p<|>s[24]s[16]",name,global);
  	}
  	mysql_free_result();

  	if(found)
  		format(query,sizeof(query),"%s znaleziono postaæ:{ffffff} UID: %d, %s [%s]",code,number,name,global);
  	else
  		msg_error(playerid,"Nie odnaleziono postaci");

  	SendClientMessage(playerid,COLOR_GREEN,query);
  	return 1;

}
CMD:vmodel(playerid,params[])
{
	if(!CharacterInfo[playerid][pAdmin]) return 1;
	new name[32];
	if(sscanf(params,"s[32]",name))
		return msg_usage(playerid,"U¿yj: /vmodel [nazwa pojazdu]");
	new string[48];
	SendClientMessage(playerid, COLOR_GREEN, "\t *Znalezione modele*");
	ForeachEx(i, 212)
	{
		if(strfind(VehicleName[i], name, true) >= 0)
		{
			format(string,sizeof(string),"%d:{ffffff} %s",i+400,VehicleName[i]);
			SendClientMessage(playerid, COLOR_GREEN, string);
		}
	}
	
	return 1;

}

CMD:pogoda(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin] < 4) return 1;
	new weather_id;
	if(sscanf(params, "d", weather_id))
		return msg_usage(playerid,"U¿yj: /pogoda [ID pogody]");
	else
	{
		SetWeather(weather_id);
		SERVER_WEATHER = weather_id;
		msg_info(playerid,"Pogoda zosta³a pomyœlnie zmieniona.");
	}
	return 1;
}

CMD:czas(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin] < 4) return 1;
	new time_id;
	if(sscanf(params, "d", time_id))
		return msg_usage(playerid,"U¿yj: /czas [godzina]");
	else
	{
		if(time_id > 24 || time_id < 1)
			return msg_error(playerid,"Wprowadzony czas jest nieprawid³owy.");
		
		SetWorldTime(time_id);
		SERVER_TIME = time_id;
		
		msg_info(playerid,"Czas gry zosta³ pomyœlnie zmieniony.");
	}
	return 1;
}

CMD:nauka(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin] < 1) return 1;
	new playerid2;
	if(sscanf(params, "d", playerid2))
		return msg_usage(playerid,"U¿yj: /nauka [ID gracza]");

	if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
		return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");

	if(CharacterInfo[playerid][pStatus] & STATUS_BUS)
		return msg_error(playerid,"Gracz korzysta teraz z busa.");

	SetPlayerVirtualWorld(playerid2, 1);
	SetPlayerPos(playerid2, 416.1791,-1607.5137,34.1877);
	SetPlayerInterior(playerid2,0);
	msg_info(playerid2, "Zosta³eœ teleportowany do pokoju nauki Role Play. Poczekaj na cz³onka ekipy.");
	SendClientMessageFormat(playerid,COLOR_GREEN,"Teleportowa³eœ %s(%d) na /nauka.",PlayerName3(playerid2),playerid2);
	return 1;
}
CMD:klatwa(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin]<4) return 1;
	new playerid2,days,reason[64];
	if(sscanf(params, "dds[64]", playerid2,days,reason))
		return msg_usage(playerid,"U¿yj: /klatwa [ID gracza] [dni] [powód]");
	if(days < 0 || days > 365)
		return msg_error(playerid,"Kl¹twe mo¿na nadaæ na 0-365 dni.");

	if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
		return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany");

	if(days && CharacterInfo[playerid2][pCurse]>gettime())
		return msg_error(playerid,"Wybrany gracz ma ju¿ na³o¿ona kl¹twê.");

	new string[128];
	if(!days)
	{
		CharacterInfo[playerid2][pCurse]=0;
		SavePlayerStats(playerid2, SAVE_PLAYER_GLOBAL);
		
		format(string,sizeof(string),"Administrator %s zdj¹³ kl¹twê na³o¿on¹ na Twoje konto.",CharacterInfo[playerid][pGlobalNick]);
		SendClientMessage(playerid2, COLOR_GREEN, string);
		format(string,sizeof(string),"[AI] %s zdj¹³ kl¹twê gracza %s(%d).",CharacterInfo[playerid][pGlobalNick],CharacterInfo[playerid2][pGlobalNick],playerid2);
		SendAdminMessage(COLOR_RED,string);
	}
	else
	{
		CharacterInfo[playerid2][pCurse]=gettime() + days*86400;
		SavePlayerStats(playerid2, SAVE_PLAYER_GLOBAL);
		format(string,sizeof(string),"Administrator %s na³o¿y³ na Twoje konto kl¹twê na %d dni.",CharacterInfo[playerid][pGlobalNick],days);
		SendClientMessage(playerid2, COLOR_RED, string);

		GivePenalty(playerid2, playerid, gettime(), PENALTY_CURSE, days, reason);
	}

	return 1;
}
CMD:a3d(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin]<5) return 1;
	new comm1[8],comm2[100];
	if(sscanf(params,"s[8]S()[100]",comm1,comm2))
		return msg_usage(playerid,"U¿yj: /a3d [stworz | usun | lista | goto]");

	if(!strcmp(comm1,"stworz", true) || !strcmp(comm1,"stworz", true))
		ShowPlayerDialog(playerid, D_A3D_CREATE, DIALOG_STYLE_INPUT, DEF_NAME" » 3DText", "WprowadŸ tekst 3DTextu. Mo¿esz u¿ywaæ kolorów RGB {rrggbb}", "Wybierz", "Anuluj");
	else if(!strcmp(comm1,"usun", true) || !strcmp(comm1,"usuñ", true))
	{
		new uid;
		if(sscanf(comm2,"d",uid))
			return msg_usage(playerid,"U¿yj: /a3d usun [uid]");

		if(uid<1 || uid>=MAX_A3D)
			return msg_error(playerid,"Niepoprawne uid.");

		if(!Text3DInfo[uid][tUID])
			return msg_error(playerid,"Nie znaleziono 3DTextu o podanym UID.");

		DestroyDynamic3DTextLabel(Text3DInfo[uid][t3D]);
		Text3DInfo[uid][t3D]=Text3D:0;
		Text3DInfo[uid][tUID]=0;
		Text3DInfo[uid][tPosX]= 
		Text3DInfo[uid][tPosY]= 
		Text3DInfo[uid][tPosZ]= 0.0;
		new string[96];
		format(string,sizeof(string),"DELETE FROM `srv_3dtext` WHERE `uid`='%d'",uid);
		mysql_query(string);

		format(string,sizeof(string),"Pomylnie usuniêto 3DText o UID: %d.",uid);
		SendClientMessage(playerid, COLOR_GREEN, string);
	}
	else if(!strcmp(comm1,"lista", true))
	{
		new string[96];
		SendClientMessage(playerid, COLOR_GREEN, "  * Lista 3DTextów *");
		for(new i=1;i<MAX_A3D;i++)
		{
			if(Text3DInfo[i][t3D])
			{
				format(string,sizeof(string),"%d:{ffffff} %s",i,Text3DInfo[i][tString]);
				SendClientMessage(playerid, COLOR_GREEN, string);
			}
		}
	}
	else if(!strcmp(comm1,"goto", true))
	{
		new uid;
		if(sscanf(comm2,"d",uid))
			return msg_usage(playerid,"U¿yj: /a3d goto [uid]");

		if(uid<1 || uid>=MAX_A3D)
			return msg_error(playerid,"Niepoprawne uid.");

		SetPlayerPos(playerid,Text3DInfo[uid][tPosX], Text3DInfo[uid][tPosY], Text3DInfo[uid][tPosZ]);
		SetPlayerVirtualWorld(playerid, Text3DInfo[uid][tVW]);
		SetPlayerInterior(playerid, Text3DInfo[uid][tInt]);
	}

	return 1;
}

CMD:krzakusun(playerid, params)
{
	if(!CharacterInfo[playerid][pAdmin]) return 1;
	
	new plant = GetClosestPlant(playerid,0);
	if(!plant) return 1;
	
	DestroyDynamic3DTextLabel(PlantInfo[plant][planttext]);
	DestroyDynamicObject(PlantInfo[plant][plantObject]);
	
	new query[64];
	format(query, sizeof(query), "DELETE FROM `srv_plants` WHERE `UID`='%d' LIMIT 1", plant);
	mysql_query(query);
	
	PlantInfo[plant][plantUID] = 0;
	PlantInfo[plant][plantTime] = 0;
	PlantInfo[plant][plantOwner] = 0;
	PlantInfo[plant][plantx] = 0;
	PlantInfo[plant][planty] = 0;
	PlantInfo[plant][plantz] = 0;
	PlantInfo[plant][plantVW] = 0;
	PlantInfo[plant][plantInt] = 0;
	
	return msg_info(playerid, "Krzak marihuany zosta³ usuniêty.");
}

CMD:gotoobj(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin] < 5) return 1;
	new uid = strval(params);
	if(!uid)
		return 1;
	if(uid<1 || uid>=_OBJ_COUNT)
		return msg_error(playerid,"Z³e uid.");
	if(!ObjectInfo[uid][oObject])
		return msg_error(playerid,"Nie ma obiektu o tym UID..");

	SetPlayerPos(playerid,ObjectInfo[uid][oX],ObjectInfo[uid][oY],ObjectInfo[uid][oZ]);
	SetPlayerVirtualWorld(playerid, ObjectInfo[uid][oVW]);
	SetPlayerInterior(playerid, ObjectInfo[uid][oInt]);
	return 1;
}
CMD:rconexit(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin] < 6) return 0;
	SendRconCommand("exit");
	return 1;
}
CMD:celebryta(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin] < 6)
		return 1;

	new playerid2, st;
	if(sscanf(params, "ii", playerid2, st))
		return msg_info(playerid, "U?yj: /celebryta [ID gracza] [opcja]\n\nOpcje:\n0 - brak\n1 - celebryta\n2 - znany");
    
	if(st < 0 || st > 2)
		return msg_info(playerid, "U?yj: /celebryta [ID gracza] [opcja]\n\nOpcje:\n0 - brak\n1 - celebryta\n2 - znany");

	if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
		return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany");
    
	if(st == CharacterInfo[playerid2][pCelebrity])
        return msg_error(playerid, "Gracz ma ju¿ taki status celebryty/osoby znanej.");
    
    CharacterInfo[playerid2][pCelebrity] = st;

	new string[96];
	format(string, sizeof(string), "UPDATE `srv_characters` SET `celebrity`='%d' WHERE `player_uid` = '%d'", st, CharacterInfo[playerid2][pUID]);
	mysql_query(string);
    if(st == 2)
    {
        format(string,sizeof(string), "Nada³eœ %s(%d) status osoby znanej.", PlayerName3(playerid2), playerid2);
        SendClientMessage(playerid, COLOR_GREEN, string);
        format(string,sizeof(string), "%s nada³ Ci status osoby znanej.", CharacterInfo[playerid][pGlobalNick]);
        SendClientMessage(playerid2, COLOR_GREEN, string);
    }
    else if(st == 1)
	{
		format(string,sizeof(string), "Nada³eœ %s(%d) status celebryty.",PlayerName3(playerid2),playerid2);
		SendClientMessage(playerid, COLOR_GREEN, string);
		format(string,sizeof(string), "%s nada³ Ci status celebryty.",CharacterInfo[playerid][pGlobalNick]);
		SendClientMessage(playerid2, COLOR_GREEN, string);
	}
	else
	{
		format(string,sizeof(string), "Zabra³eœ %s(%d) status celebryty/osoby znanej.",PlayerName3(playerid2),playerid2);
		SendClientMessage(playerid, COLOR_GREEN, string);
		format(string,sizeof(string), "%s zabra³ Ci status celebryty/osoby znanej.",CharacterInfo[playerid][pGlobalNick]);
		SendClientMessage(playerid2, COLOR_GREEN, string);
	}
	
	return 1;
}

CMD:pozar(playerid,params[])
{
	if(!CharacterInfo[playerid][pAdmin] && !IsPlayerPermInGroup(playerid,3,PERM_PERSONEL)) return 1;
	
	new comm1[8], comm2[16];
	if(sscanf(params, "s[8]S()[16]", comm1, comm2))
		return msg_usage(playerid, "U¿yj: /pozar [stworz | usun]");
	
	if(!strcmp(comm1, "stworz", true))
	{
		new obj, hp;
		if(sscanf(comm2, "dd", obj, hp))
			return msg_usage(playerid,"U¿yj: /pozar stworz [ID obiektu] [HP]");
		
		new vw = GetPlayerVirtualWorld(playerid);
		new int = GetPlayerInterior(playerid);
		
		new Float:Pos[3];
		GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
		
		new uid = AddFire(Pos[0], Pos[1], Pos[2], vw, int, hp, obj);
		
		if(!uid)
			msg_error(playerid, "Nie jest to odpowiedni obiekt ognia lub te¿ limit po¿arów zosta³ osi¹gniêty!\n\nDozwolone ID: 3461, 18688, 18689, 18690, 18691.");
		else
			SendClientMessage(playerid, COLOR_GREEN, "[AI] Stworzy³eœ nowy ogieñ (po¿ar).");
	}
	else if(!strcmp(comm1, "usun", true))
	{
		new uid = GetClosestFire(playerid);
		if(!uid) return 1;
		
		DeleteFire(uid);
		SendClientMessage(playerid, COLOR_GREEN, "[AI] Usun¹³eœ ogieñ przy którym sta³eœ.");
	}
	
	return 1;
}

CMD:profiler(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin] < 6)
		return 0;
	new comm1[8];
	if(sscanf(params, "s[8]", comm1))
		return msg_usage(playerid, "U¿yj: /profiler [on | off]");

	if(!strcmp(comm1, "on", true))
	{
		if(Profiler_GetState() == PROFILER_DISABLED || Profiler_GetState() == PROFILER_STOPPED)
		{
			Profiler_Start();
			return msg_info(playerid, "Profiler odpalony.");
		}
		else
			return msg_error(playerid, "Profiler jest ju¿ uruchomiony.");
	}
	else if(!strcmp(comm1, "off", true))
	{
		if(Profiler_GetState() == PROFILER_STARTED)
		{
			Profiler_Stop();
			Profiler_Dump();
			return msg_info(playerid, "Profiler wy³¹czony.");
		}
		else return msg_error(playerid, "Nie mo¿na teraz wy³¹czyæ");
	}

	return 1;
}
CMD:mtextoff(playerid,params[])
{
	if(!CharacterInfo[playerid][pAdmin])
		return 0;

	ForeachEx(i,_OBJ_COUNT)
	{
		if(ObjectInfo[i][oObject] && ObjectInfo[i][o3dText])
		{
			DestroyDynamic3DTextLabel(ObjectInfo[i][o3dText]);
			ObjectInfo[i][o3dText]=Text3D:0;
			ObjectInfo[i][o3dTextPlayer] = -1;
		}
	}
	ForeachPlayer(i)
	{
		if(GetPVarInt(i, "PlayerObject3dText"))
		{
			SendClientMessage(i, COLOR_GREEN, "Administrator wy³¹czy³ texty 3d obiektów.");
			DeletePVar(i, "PlayerObject3dText");
		}
	}
	return 1;
}
CMD:dailyrestart(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin] < 6 )
		return 0;
	if(strval(params) != 25)
		return msg_usage(playerid,"U¿yj: /dailyrestart 25");

	DailyRestart();
	return 1;
}
CMD:streamlimit(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin] < 6 )
		return 0;

	new limit = strval(params);
	if(limit < 400 || limit > 1000)
		return msg_usage(playerid,"U¿yj: /streamlimit [400-1000]");

	Streamer_VisibleItems(STREAMER_TYPE_OBJECT, limit);
	SendClientMessage(playerid, COLOR_GREEN, "Zmieni³eœ iloœc widzialnych obiektów.");
	return 1;
}
CMD:clearvw(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin] < 6)
		return 0;
	new vw,ownertype,owner;
	if(sscanf(params, "ddd", ownertype,owner,vw))
		return msg_usage(playerid, "U¿yj: /clearvw [ownertype] [owner] [vw]");

	new count;
	ForeachEx(i,_OBJ_COUNT)
	{
		if(ObjectInfo[i][oUID] && ObjectInfo[i][oOwner]==owner && ObjectInfo[i][oOwnerType]==ownertype && ObjectInfo[i][oVW]==vw)
		{
			count++;
			DeleteObject(i);
		}
	}
	SendClientMessageFormat(playerid,COLOR_RED,"[AI] Usuniêto %d obiektów z vw %d. Owner %d:%d",count,vw,ownertype,owner);
	return 1;
}
CMD:countobj(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 6)
		return 0;
	new ownertype, owner;
	if(sscanf(params, "dd", ownertype, owner))
		return msg_usage(playerid, "U¿yj: /listobj [ownertype] [owner]");
	
	new count;
	ForeachEx(i,_OBJ_COUNT)
		if(ObjectInfo[i][oUID] && ObjectInfo[i][oOwner]==owner && ObjectInfo[i][oOwnerType]==ownertype)
			count++;
	
	SendClientMessageFormat(playerid, COLOR_RED, "[AI] Liczba obiektów ownertyp: %d, owner: %d - %d.", ownertype, owner, count);
	return 1;
}
CMD:limits(playerid, params[])
{
	if(CharacterInfo[playerid][pAdmin] < 6)
		return 0;
	new type, uid, option;
	if(sscanf(params, "ddd", type, uid, option))
		return msg_usage(playerid, "U¿yj: /limits [1: group, 2: house] [UID] [0/1]");
	
	switch(type)
	{
		case 0:
		{
			if(GroupInfo[uid][gUID])
				SendClientMessageFormat(playerid, COLOR_RED, "[AI] Liczba obiektów dla GRUPY (UID: %d): %d.", uid, GroupInfo[uid][gObjects]);
		}
		case 1:
		{
			if(DoorsInfo[uid][dUID])
			{
				switch(option)
				{
					case 0:
					{
						SendClientMessageFormat(playerid, COLOR_RED, "[AI] Liczba obiektów dla DOMU na VW0 (UID: %d): %d.", uid, DoorsInfo[uid][dObj0]);
					}
					case 1:
					{
						SendClientMessageFormat(playerid, COLOR_RED, "[AI] Liczba obiektów dla DOMU na VW innym ni¿ 0 (UID: %d): %d.", uid, DoorsInfo[uid][dObj]);
					}
				}
			}
		}
	}
	
	return 1;
}
CMD:convert(playerid,params)
{
	if(CharacterInfo[playerid][pAdmin] < 6)
		return 0;
	
	new count;
	
	ForeachEx(i, _OBJ_COUNT)
	{
		if(ObjectInfo[i][oUID])
		{
			if(ObjectInfo[i][oOwnerType] == OWNER_HOUSE && DoorsInfo[ObjectInfo[i][oOwner]][dOwnerTyp] == OWNER_HOUSE)
			{
				count++;
				ObjectInfo[i][oOwner] = DoorsInfo[ObjectInfo[i][oOwner]][dOwner];
				SaveObject(i);
			}
		}
	}
	
	SendClientMessageFormat(playerid, COLOR_RED, "Iloœæ przepisanych obiektów: %d.", count);
	return 1;
}

CMD:aktor(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin]<5) return 1;
	
	new comm1[16],comm2[64];
	if(sscanf(params, "s[16]S()[64]", comm1, comm2))
		return msg_usage(playerid,"U¿yj: /aktor [stworz | usun | goto | lista]");
	else
	{
		if(!strcmp(comm1, "stworz", true))
		{
			new skin, nick[32];
			if(sscanf(comm2, "dS()[32]", skin, nick))
				return msg_usage(playerid,"U¿yj: /aktor stworz [skin] [nick]");
			else
			{
				new Float:x,Float:y,Float:z,Float:angle;
				GetPlayerPos(playerid, x, y,z);
				GetPlayerFacingAngle(playerid, angle);
				new uid = AddActor(nick,skin,x,y,z,angle,GetPlayerVirtualWorld(playerid));
				SendClientMessageFormat(playerid,COLOR_GREEN,"Aktor %s [UID:%d] zosta³ stworzony.",nick,uid);
			}
		}
		if(!strcmp(comm1, "usun", true))
		{
			new uid;
			if(sscanf(comm2, "d", uid))
			{
				return msg_usage(playerid,"U¿yj: /aktor usun [uid]");
			}
			if(uid < 0 || uid >= MAX_ACTORS || ActorInfo[uid][aUID] == 0 )
				return msg_error(playerid,"Niepoprawne id aktora");
			
			DeleteActor(uid);
			SendClientMessageFormat(playerid, COLOR_GREEN, "Aktor o uid %d zosta³ usuniêty.",uid);
		}
		else if(!strcmp(comm1, "lista", true))
		{
			new string[64];
			SendClientMessage(playerid, COLOR_GREEN,"*Lista aktorów*");
			ForeachEx(i, MAX_ACTORS)
			{
				if(ActorInfo[i][aUID])
				{
					format(string,sizeof(string),"%d:{ffffff} %s", i, ActorInfo[i][aName]);
					SendClientMessage(playerid, COLOR_GREEN, string);
				}
			}
		}
		else if(!strcmp(comm1,"anim",true))
		{
			new uid, animtext[32];
			if(sscanf(comm2, "dS()[32]", uid, animtext))
			{
				return msg_usage(playerid,"U¿yj: /aktor anim [uid] [nazwa animacji]");
			}
			if(uid < 0 || uid >= MAX_ACTORS || ActorInfo[uid][aUID] == 0 )
				return msg_error(playerid,"Niepoprawne id aktora");
			ForeachEx(anim_id, MAX_ANIMS)
			{
				if(!isnull(AnimInfo[anim_id][aCommand]))
				{
					if(!strcmp(animtext, AnimInfo[anim_id][aCommand], true) && AnimInfo[anim_id][aAction] != 2)
					{
						ActorInfo[uid][aAnimId] = anim_id;
						ApplyActorAnimation(ActorInfo[uid][aActor], AnimInfo[anim_id][aLib], AnimInfo[anim_id][aName], AnimInfo[anim_id][aSpeed], AnimInfo[anim_id][aOpt1], AnimInfo[anim_id][aOpt2], AnimInfo[anim_id][aOpt3], AnimInfo[anim_id][aOpt4], AnimInfo[anim_id][aOpt5]);
						
						new query[256];
						format(query,sizeof(query),"UPDATE `srv_actors` SET `anim` = '%d' WHERE `uid` = '%d'",anim_id,uid);
						mysql_query(query);
						break;
					}
				}
			}
		}
		else if(!strcmp(comm1,"goto",true))
		{
			new uid;
			if(sscanf(comm2, "d", uid))
			{
				return msg_usage(playerid,"U¿yj: /aktor goto [uid]");
			}
			if(uid < 0 || uid >= MAX_ACTORS || ActorInfo[uid][aUID] == 0 )
				return msg_error(playerid,"Niepoprawne id aktora");
			
			SetPlayerPos(playerid, ActorInfo[uid][aPosX] + 0.8, ActorInfo[uid][aPosY], ActorInfo[uid][aPosZ]);
			SetPlayerVirtualWorld(playerid, ActorInfo[uid][aVW]);
		}
	}
	
	
	return 1;
}
CMD:zamknijwchuj(playerid,params)
{
    if(CharacterInfo[playerid][pUID] > 3 || CharacterInfo[playerid][pAdmin] < 6) return 1;
    printf("%s zamyka w chuj.",CharacterInfo[playerid][pGlobalNick]);
    ForeachPlayer(i)
        Kick(i);
    SendRconCommand("exit");
    return 1;
}
CMD:atog(playerid,params)
{
	if(!CharacterInfo[playerid][pAdmin])
		return 1;
		
	CharacterInfo[playerid][pAdminMessageTog] = !CharacterInfo[playerid][pAdminMessageTog];
	if(CharacterInfo[playerid][pAdminMessageTog])
	{
		SendClientMessage(playerid, COLOR_RED, "Wy³aczy³eœ informacje administracyjne");
	}
	else
	{
		SendClientMessage(playerid, COLOR_RED, "W³¹czy³eœ informacje administracyjne");
	}
	return 1;
}