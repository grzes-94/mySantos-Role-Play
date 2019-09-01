forward SavePlayerStats(playerid, what);
forward FreezePlayer(playerid);
forward UnfreezePlayer(playerid);
forward SetPlayerSpawn(playerid);
forward SendPlayerToSpawn(playerid);
forward KickWithWait(playerid);
forward KickPlayer(playerid);
forward UpdatePlayer3DTextNick(playerid);
forward GetPlayerSpeed(playerid);
forward PlayerOnDrug(playerid);
forward PlayerTrackNumber(playerid, playerid2, numer);
forward Oferta(typ, playerid, playerid2, cena, uid);
forward DisableOffer(playerid,uid);
forward msg_error(playerid,string[]);
forward msg_info(playerid,string[]);
forward msg_usage(playerid,string[]);
forward Destroy3DText(playerid);
forward Tip(playerid,time,string[]);
forward DisableTip(playerid);
forward HidePlayerWeapons(playerid);
forward UnfreezeAll();
forward DamageColorNickDisable(playerid);
forward GivePlayerPremium(playerid, days);
forward PlayerLoginCheck(playerid);
forward NegateHavingWeapons(playerid);
forward GetUpAfterFall(playerid);

stock GetPlayerID(playeruid)
{
	new playerid = -1;
	
	ForeachPlayer(i)
	{
		if(Logged[i] && CharacterInfo[i][pUID] == playeruid)
		{
			playerid = i;
			break;
		}
	}
	
	return playerid;
}

stock PlayerName(playerid)
{
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, sizeof(name));
	return name;
}

stock PlayerName2(playerid)
{
	new name[MAX_PLAYER_NAME];

	GetPlayerName(playerid, name, sizeof(name));
	
	UnderscoreToSpace(name);
	return name;
}

stock PlayerName3(playerid)
{
	new name[MAX_PLAYER_NAME];
	
	if(!CharacterInfo[playerid][pMask])
		GetPlayerName(playerid, name, sizeof(name));
	else
		name = LoadPlayerName(CharacterInfo[playerid][pUID]);
	
	return name;
}

stock LoadPlayerName(player_uid,bool:underscore=false)
{
	new query[64],name[MAX_PLAYER_NAME];
	mysql_query_format("SELECT `nickname` FROM `srv_characters` WHERE `player_uid`='%d'", player_uid);
	mysql_store_result();
	mysql_fetch_row_format(query, "|");
	sscanf(query,"p<|>s[32]",name);
	mysql_free_result();
	if(!underscore)
		UnderscoreToSpace(name);
	return name;
}

stock LoadPlayerGlobalName(gid)
{
	new query[64], name[64];
	mysql_query_format("SELECT `members_display_name` FROM `members` WHERE `member_id`='%d'", gid);
	mysql_store_result();
	mysql_fetch_row_format(query, "|");
	sscanf(query,"p<|>s[64]",name);
	mysql_free_result();
	return name;
}

stock LoadPlayerGlobalNick(uid)
{
	new query[64],name[MAX_PLAYER_NAME];
	mysql_query_format("SELECT `members_display_name` FROM `members` WHERE `member_id`='%d'", uid);
	mysql_store_result();
	mysql_fetch_row_format(query, "|");
	sscanf(query,"p<|>s[32]",name);
	mysql_free_result();
	return name;
}

stock CharCode(playerid)
{
	new n=CharacterInfo[playerid][pUID];
	new prefix,temp,hex[5],i,code[8];
	new sufix=random(10);
	if(n<100)
	{
		prefix='A'+random(10);
		n+=5371+prefix+18*sufix;
	}
	else if(n<5000)
	{
		prefix='K'+random(10);
		n+=4357+prefix+18*sufix;
	}
	else
	{
		prefix='W'+random(4);
		n+=23+prefix+18*sufix;
	}
	while(n!=0)
	{
		temp = n % 17;
		if( temp < 10)
			temp =temp + 48;
	  	else
		 	temp = temp + 55;

	  	hex[i++]= temp;
	  	n = n / 17;
  	}
  	format(code,sizeof(code),"%s%s%d",prefix,hex,sufix);	

	return code;
}

stock strtoupper(string[])
{
	for(new l, i = strlen(string); l < i; l++)
		string[l] = toupper(string[l]);
}

stock UnderscoreToSpace(name[])
{
	for(new i = 0; i < strlen(name); i++)
		if(name[i] == '_') name[i] = ' ';
}

stock IsPlayerPremium(playerid)
{
	return (CharacterInfo[playerid][pPremium] > gettime() || CharacterInfo[playerid][pAdmin]);
}

stock SendWrappedMessageToPlayerRange(playerid, colour, colour1, colour2, colour3, colour4, msg[], range = 20, bool:chatooc = false, bool:ignore = false, maxlength = 100, const prefix[] = "...")
{
	new ignoreplayer = INVALID_PLAYER_ID;
	if(ignore)
		ignoreplayer = playerid;
	
	new length = strlen(msg);
	if(length <= maxlength)
	{
		SendPlayerText(range, playerid, msg, colour, colour1, colour2, colour3, colour4, chatooc, ignoreplayer);
		return 1;
	}
	new string[128], idx;
	for(new i, space, plen, bool:useprefix; i < length; i++)
	{
		if(i - idx + plen >= maxlength)
		{
			if(idx == space || i - space >= 25)
			{
				strmid(string, msg, idx, i);
				idx = i;
			}
			else
			{
				strmid(string, msg, idx, space);
				idx = space + 1;
			}
			if(useprefix)
			{
				strins(string, prefix, 0);
			}
			else
			{
				plen = strlen(prefix);
				useprefix = true;
			}
			format(string, sizeof(string), "%s ...", string);
			toupper(string[0]);
			SendPlayerText(range, playerid, string, colour, colour1, colour2, colour3, colour4, chatooc, ignoreplayer);
		} 
		else if(msg[i] == ' ')
		{
			space = i;
		}
	}
	if(idx < length)
	{
		strmid(string, msg, idx, length);
		strins(string, prefix, 0);
		toupper(string[0]);
		SendPlayerText(range, playerid, string, colour, colour1, colour2, colour3, colour4, chatooc, ignoreplayer);
	}
	return 1;
}

stock GivePlayerCash(playerid, money)
{
	CharacterInfo[playerid][pCash] += money;
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, CharacterInfo[playerid][pCash]);
	new query[128];
	format(query, sizeof(query), "UPDATE `srv_characters` SET `cash`='%d' WHERE `player_uid`='%d'", CharacterInfo[playerid][pCash], CharacterInfo[playerid][pUID]);
	mysql_query(query);
}

stock ShowPlayerStats(playerid, playerid2)
{
	new Float:armor;
	GetPlayerArmour(playerid2, armor);
	new string[1024];
	
	format(string, sizeof(string), DEF_COLOR"# %s [%s] (UID: %d) (GID: %d)", PlayerName3(playerid2), CharacterInfo[playerid2][pGlobalNick], CharacterInfo[playerid2][pUID], CharacterInfo[playerid2][pGID]);
	format(string, sizeof(string), "%s\n\tP³eæ:\t\t\t\t\t%s", string, GetSexName(CharacterInfo[playerid2][pSex]));
	format(string, sizeof(string), "%s\n\tWiek:\t\t\t\t\t%d", string, CharacterInfo[playerid2][pAge]);
	format(string, sizeof(string), "%s\n\tZdrowie:\t\t\t\t%0.1f", string, CharacterInfo[playerid2][pHealth]);
	if(armor)
	format(string, sizeof(string), "%s\n\tKamizelka:\t\t\t\t%0.1f", string, armor);
	format(string, sizeof(string), "%s\n\tG³ód:\t\t\t\t\t%d/100", string, 100 - CharacterInfo[playerid2][pGlod]);
	format(string, sizeof(string), "%s\n\tSi³a:\t\t\t\t\t%dj", string, CharacterInfo[playerid2][pStrength]);
	format(string, sizeof(string), "%s\n\tCzas gry:\t\t\t\t%dh, %dmin", string, CharacterInfo[playerid2][pHours], CharacterInfo[playerid2][pMinutes]);
	format(string, sizeof(string), "%s\n\tPieni¹dze:\t\t\t\t{02AD38}${FFFFFF} %d", string, CharacterInfo[playerid2][pCash]);
	format(string, sizeof(string), "%s\n\tKonto bankowe:\t\t\t{02AD38}${FFFFFF} %d", string, CharacterInfo[playerid2][pCredit]);
	format(string, sizeof(string), "%s\n\tSkin:\t\t\t\t\t%d", string, CharacterInfo[playerid2][pSkin]);
	if( CharacterInfo[playerid2][pDrugsTime] >60 )
		format(string, sizeof(string), "%s\n\tEfekt narkotyków/alkoholu:\t\t%d min", string, CharacterInfo[playerid2][pDrugsTime]/60);
	else if(CharacterInfo[playerid2][pDrugsTime]) 
		format(string, sizeof(string), "%s\n\tEfekt narkotyków/alkoholu:\t\t%d sec", string, CharacterInfo[playerid2][pDrugsTime]);
	
	format(string, sizeof(string), "%s\n"DEF_COLOR"# System grup", string);
	for(new i=1;i<MAX_PLAYER_GROUPS;i++)
		if(MemberGroup[playerid2][i][GroupID])
			format(string, sizeof(string), "%s\n\t%d: %s [UID: %d]", string, i, GroupInfo[MemberGroup[playerid2][i][GroupID]][gName], MemberGroup[playerid2][i][GroupID]);
	
	format(string, sizeof(string), "%s\n"DEF_COLOR"# System kar", string);
	if(CharacterInfo[playerid2][pAJ])
		format(string, sizeof(string), "%s\n\tAdmin Jail:\t\t\t\t%d", string, (CharacterInfo[playerid2][pAJ]/60));
	if(CharacterInfo[playerid2][pBW])
		format(string, sizeof(string), "%s\n\tBW:\t\t\t\t\t%d", string, (CharacterInfo[playerid2][pBW]/60));
	if(CharacterInfo[playerid2][pWounded])
		format(string, sizeof(string), "%s\n\tPowalenie:\t\t\t\t%d", string, (CharacterInfo[playerid2][pWounded]/60));
	format(string, sizeof(string), "%s\n\tWarny:\t\t\t\t\t%d/4", string, CharacterInfo[playerid2][pWarn]);
	if(CharacterInfo[playerid2][pCurse] > gettime())
		format(string, sizeof(string), "%s\n\tKl¹twa:\t\t\t\t%d dni", string, 1 + (CharacterInfo[playerid2][pCurse]-gettime())/86400);
	if(CharacterInfo[playerid2][pJailTime] > gettime())
		format(string, sizeof(string), "%s\n\tAreszt:\t\t\t\t%d (godziny)", string, (CharacterInfo[playerid2][pJailTime]-gettime())/60/60);
	
	if(CharacterInfo[playerid2][pBlockNoRun] || CharacterInfo[playerid2][pBlockNoCar] || CharacterInfo[playerid2][pBlockNoOOC] || CharacterInfo[playerid2][pBlockNoGun])
	{
		format(string, sizeof(string), "%s\n"DEF_COLOR"# Aktywne blokady czasowe", string);
		
		if(CharacterInfo[playerid2][pBlockNoRun] > 60) 
			format(string, sizeof(string), "%s\n\tBlokada biegania:\t\t\t%d min", string, CharacterInfo[playerid2][pBlockNoRun]/60);
		else if(CharacterInfo[playerid2][pBlockNoRun]) 
			format(string, sizeof(string), "%s\n\tBlokada biegania:\t\t\t%d sec", string, CharacterInfo[playerid2][pBlockNoRun]);
		if(CharacterInfo[playerid2][pBlockNoCar]>60)
			format(string, sizeof(string), "%s\n\tBlokada prowadzenia pojazdów:\t%d min", string, CharacterInfo[playerid2][pBlockNoCar]/60);
		else if(CharacterInfo[playerid2][pBlockNoCar])
			format(string, sizeof(string), "%s\n\tBlokada prowadzenia pojazdów:\t%d sec", string, CharacterInfo[playerid2][pBlockNoCar]);
		if(CharacterInfo[playerid2][pBlockNoOOC]>60)
			format(string, sizeof(string), "%s\n\tBlokada czatów OOC:\t\t\t\t%d min", string, CharacterInfo[playerid2][pBlockNoOOC]/60);
		else if(CharacterInfo[playerid2][pBlockNoOOC])
			format(string, sizeof(string), "%s\n\tBlokada czatów OOC:\t\t\t\t%d sec", string, CharacterInfo[playerid2][pBlockNoOOC]);
		if(CharacterInfo[playerid2][pBlockNoGun]>60)
			format(string, sizeof(string), "%s\n\tBlokada u¿ywania broni:\t\t\t%d min", string, CharacterInfo[playerid2][pBlockNoGun]/60);
		else if(CharacterInfo[playerid2][pBlockNoGun])
			format(string, sizeof(string), "%s\n\tBlokada u¿ywania broni:\t\t\t%d sec", string, CharacterInfo[playerid2][pBlockNoGun]);
	}
	
	if(CharacterInfo[playerid2][pAdmin])
	{
		format(string, sizeof(string), "%s\n"DEF_COLOR"# System adminów{A9C4E4}", string);
		format(string, sizeof(string), "%s\n\tPoziom admina:\t\t\t\t%d", string, CharacterInfo[playerid2][pAdmin]);
	}
	
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, DEF_NAME" » statystyki postaci", string, "Zamknij", "");
	return 1;
}

stock GetSexName(sex)
{
	new name[32];
	if(sex) name = "Mê¿czyzna";
	else name = "Kobieta";
	return name;
}

stock isNumeric(string1[])
{
	new length=strlen(string1);
	if (length==0) return false;
	for (new i = 0; i < length; i++)
	{
		if ((string1[i] > '9' || string1[i] < '0' && string1[i]!='-' && string1[i]!='+') // Not a number,'+' or '-'
		|| (string1[i]=='-' && i!=0)											 // A '-' but not at first.
		|| (string1[i]=='+' && i!=0)											 // A '+' but not at first.
		) return false;
	}
	if (length==1 && (string1[0]=='-' || string1[0]=='+')) return false;
	return true;
}

stock EscapePL(name[])
{
	for(new i = 0; name[i] != 0; i++)
	{
		if(name[i] == 'œ') name[i] = 's';
		else if(name[i] == 'ê') name[i] = 'e';
		else if(name[i] == 'ó') name[i] = 'o';
		else if(name[i] == '¹') name[i] = 'a';
		else if(name[i] == '³') name[i] = 'l';
		else if(name[i] == '¿') name[i] = 'z';
		else if(name[i] == 'Ÿ') name[i] = 'z';
		else if(name[i] == 'æ') name[i] = 'c';
		else if(name[i] == 'ñ') name[i] = 'n';
		else if(name[i] == 'Œ') name[i] = 'S';
		else if(name[i] == 'Ê') name[i] = 'E';
		else if(name[i] == 'Ó') name[i] = 'O';
		else if(name[i] == '¥') name[i] = 'A';
		else if(name[i] == '£') name[i] = 'L';
		else if(name[i] == '¯') name[i] = 'Z';
		else if(name[i] == '') name[i] = 'Z';
		else if(name[i] == 'Æ') name[i] = 'C';
		else if(name[i] == 'Ñ') name[i] = 'N';
	}
}

stock GetAccountIP(playerid)
{
	new ip[16];
	GetPlayerIp(playerid, ip, sizeof(ip));
	return ip;
}

public UpdatePlayer3DTextNick(playerid)
{
	new nick[192];
	new status[128];
	
	if(CharacterInfo[playerid][pAdminDuty])
	{
		switch(CharacterInfo[playerid][pAdmin])
		{
			case 1: format(nick, sizeof(nick), "%s (%d)\n{FF9900}Opiekun", CharacterInfo[playerid][pGlobalNick], playerid);
			case 2,3,4: format(nick, sizeof(nick), "%s (%d)\n{8B00B0}GameMaster", CharacterInfo[playerid][pGlobalNick], playerid);
			case 5,6: format(nick, sizeof(nick), "%s (%d)\n{B00000}Administrator", CharacterInfo[playerid][pGlobalNick], playerid);
		}
		
		Update3DTextLabelText(NameTags[playerid], 0xFFFFFFCC, nick);
	}
	else
	{
		if(IsPlayerInAnyVehicle(playerid) && VehicleInfo[GetVehicleUID(GetPlayerVehicleID(playerid))][vGlass])
		{
			if(!CharacterInfo[playerid][pAlreadyHidedNick])
			{
				if(CharacterInfo[playerid][pSex])
					format(nick, sizeof(nick), "Zamaskowany %s (%d)", CharCode(playerid), playerid);
				else
					format(nick, sizeof(nick), "Zamaskowana %s (%d)", CharCode(playerid), playerid);
				
				CharacterInfo[playerid][pAlreadyHidedNick] = true;
				new nickname[32];
				format(nickname, sizeof(nickname), "%s", nick);
				CharacterInfo[playerid][pHidedNick] = nickname;
			}
			else
				format(nick, sizeof(nick), "%s", CharacterInfo[playerid][pHidedNick]);
		}
		else
		{
			if(CharacterInfo[playerid][pAlreadyHidedNick])
				CharacterInfo[playerid][pAlreadyHidedNick] = false;
			
			format(nick, sizeof(nick), "%s (%d)", PlayerName2(playerid), playerid);
		}
		
		format(status, sizeof(status), "(");
		
		new bool:first = false;
		if(CharacterInfo[playerid][pStrength]>=900)
		{
			if(CharacterInfo[playerid][pSex])
				format(status, sizeof(status), "%skulturysta", status);
			else
				format(status, sizeof(status), "%skulturystka", status);
			
			if(!first)
				first = true;
		}
		else if(CharacterInfo[playerid][pStrength]>=750)
		{
			if(CharacterInfo[playerid][pSex])
				format(status, sizeof(status), "%smuskularny", status);
			else
				format(status, sizeof(status), "%smuskularna", status);
			
			if(!first)
				first = true;
		}
		else if(CharacterInfo[playerid][pStrength]>=500)
		{
			if(CharacterInfo[playerid][pSex])
				format(status, sizeof(status), "%sumiêœniony", status);
			else
				format(status, sizeof(status), "%sumiêœniona", status);
			
			if(!first)
				first = true;
		}
		else if(CharacterInfo[playerid][pStrength]>=250)
		{
			if(CharacterInfo[playerid][pSex])
				format(status, sizeof(status), "%swysportowany", status);
			else
				format(status, sizeof(status), "%swysportowana", status);
			
			if(!first)
				first = true;
		}
		
		if(CharacterInfo[playerid][pCelebrity])
        {
            if(CharacterInfo[playerid][pCelebrity] == 2)
			{
				if(first)
					format(status, sizeof(status), "%s, ", status);
				else
					first = true;
				
				if(CharacterInfo[playerid][pSex])
					format(status, sizeof(status), "%sznany", status);
				else
					format(status, sizeof(status), "%sznana", status);
			}
            else
			{
				if(first)
					format(status, sizeof(status), "%s, ", status);
				else
					first = true;
				
				if(CharacterInfo[playerid][pSex])
					format(status, sizeof(status), "%scelebryta", status);
				else
					format(status, sizeof(status), "%scelebrytka", status);
			}   
        }
		if(CharacterInfo[playerid][pStatus])
		{
			if(CharacterInfo[playerid][pStatus] & STATUS_KAJDANKI)
			{
				if(first)
					format(status, sizeof(status), "%s, ", status);
				else
					first = true;
				
				format(status, sizeof(status), "%skajdanki", status);
			}
			if(CharacterInfo[playerid][pStatus] & STATUS_CIAGNIETY)
			{
				if(first)
					format(status, sizeof(status), "%s, ", status);
				else
					first = true;
			
				if(CharacterInfo[playerid][pSex])
					format(status, sizeof(status), "%sci¹gniêty", status);
				else
					format(status, sizeof(status), "%sci¹gniêta", status);
			}
			if(CharacterInfo[playerid][pStatus] & STATUS_KNEBEL)
			{
				if(first)
					format(status, sizeof(status), "%s, ", status);
				else
					first = true;
				
				format(status, sizeof(status), "%sknebel", status);
			}
			if(CharacterInfo[playerid][pStatus] & STATUS_ZWIAZANY)
			{
				if(first)
					format(status, sizeof(status), "%s, ", status);
				else
					first = true;
			
				if(CharacterInfo[playerid][pSex])
					format(status, sizeof(status), "%szwi¹zany", status);
				else
					format(status, sizeof(status), "%szwi¹zana", status);
			}
			if(CharacterInfo[playerid][pStatus] & STATUS_HEADBAG)
			{
				if(first)
					format(status, sizeof(status), "%s, ", status);
				else
					first = true;
				
				format(status, sizeof(status), "%sworek", status);
			}
			if(CharacterInfo[playerid][pStatus] & STATUS_PASY)
			{
				if(first)
					format(status, sizeof(status), "%s, ", status);
				else
					first = true;
				
				format(status, sizeof(status), "%spasy", status);
			}
			if(CharacterInfo[playerid][pStatus] & STATUS_MP3)
			{
				if(first)
					format(status, sizeof(status), "%s, ", status);
				else
					first = true;
				
				format(status, sizeof(status), "%ss³uchawki", status);
			}
		}
		if(CharacterInfo[playerid][pDrugs])
		{
			if(CharacterInfo[playerid][pDrugs] == DRUG_ALKO)
			{
				if(first)
					format(status, sizeof(status), "%s, ", status);
				else
					first = true;
				
				if(CharacterInfo[playerid][pSex])
					format(status, sizeof(status), "%spijany", status);
				else
					format(status, sizeof(status), "%spijana", status);
			}
			else if(CharacterInfo[playerid][pDrugs] == DRUG_MARIHUANA)
			{
				if(first)
					format(status, sizeof(status), "%s, ", status);
				else
					first = true;
			
				if(CharacterInfo[playerid][pSex])
					format(status, sizeof(status), "%szjarany", status);
				else
					format(status, sizeof(status), "%szjarana", status);
			}
			else
			{
				if(first)
					format(status, sizeof(status), "%s, ", status);
				else
					first = true;
			
				if(CharacterInfo[playerid][pSex])
					format(status, sizeof(status), "%snaæpany", status);
				else
					format(status, sizeof(status), "%snaæpana", status);
			}
		}
		if(CharacterInfo[playerid][pArmor] >= 50)
		{
			if(first)
				format(status, sizeof(status), "%s, ", status);
			else
				first = true;
			
			format(status, sizeof(status), "%skamizelka", status);
		}
		if(CharacterInfo[playerid][pHealth] <= 30)
		{
			if(first)
				format(status, sizeof(status), "%s, ", status);
			else
				first = true;
			
			if(CharacterInfo[playerid][pSex])
				format(status, sizeof(status), "%sos³abiony", status);
			else
				format(status, sizeof(status), "%sos³abiona", status);
		}
		if(CharacterInfo[playerid][pJailTime] > gettime())
		{
			if(first)
				format(status, sizeof(status), "%s, ", status);
			else
				first = true;
			
			if(CharacterInfo[playerid][pSex])
				format(status, sizeof(status), "%sprzetrzymywany", status);
			else
				format(status, sizeof(status), "%sprzetrzymywana", status);
		}
		if(CharacterInfo[playerid][pBW])
		{
			if(first)
				format(status, sizeof(status), "%s, ", status);
			else
				first = true;
			
			if(CharacterInfo[playerid][pSex])
				format(status, sizeof(status), "%snieprzytomny", status);
			else
				format(status, sizeof(status), "%snieprzytomna", status);
		}
		if(CharacterInfo[playerid][pWounded])
		{
			if(first)
				format(status, sizeof(status), "%s, ", status);
			else
				first = true;
			
			if(CharacterInfo[playerid][pSex])
				format(status, sizeof(status), "%spowalony", status);
			else
				format(status, sizeof(status), "%spowalona", status);
		}
		if(IsPlayerInAnyVehicle(playerid) && VehicleInfo[GetVehicleUID(GetPlayerVehicleID(playerid))][vGlass])
		{
			if(first)
				format(status, sizeof(status), "%s, ", status);
			else
				first = true;
			
			format(status, sizeof(status), "%sciemne szyby", status);
		}
		if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		{
			if(first)
				format(status, sizeof(status), "%s, ", status);
			else
				first = true;
			
			format(status, sizeof(status), "%sAFK od %02d:%02d", status, CharacterInfo[playerid][pAFKg], CharacterInfo[playerid][pAFKm]);
		}
			
		format(status, sizeof(status), "%s)", status);
		
		if(strlen(status) > 3)
			format(nick, sizeof(nick), "%s\n%s", nick, status);
		
		if(CharacterInfo[playerid][pNickDamageTook])
			Update3DTextLabelText(NameTags[playerid], 0xC90000CC, nick);
		else if(DutyGroup[playerid] && GroupInfo[DutyGroup[playerid]][gFlags] & FLAG_NICK)
		{
			format(nick, sizeof(nick), "%s\n[%s]", nick, GroupInfo[DutyGroup[playerid]][gTag]);
			Update3DTextLabelText(NameTags[playerid], GetGroupColor(DutyGroup[playerid]), nick);
		}
		else
			Update3DTextLabelText(NameTags[playerid], COLOR_PREMIUM, nick);
	}
}

stock PlayerToPlayer(Float:radi, playerid, targetid, bool:ignorespec=true)
{

	if(IsPlayerConnected(playerid) && IsPlayerConnected(targetid) && Logged[playerid] && Logged[targetid])
	{
		if(ignorespec && GetPlayerState(targetid)==PLAYER_STATE_SPECTATING)
			return 0;
		new Float:posx, Float:posy, Float:posz;
		new Float:oldposx, Float:oldposy, Float:oldposz;
		new Float:tempposx, Float:tempposy, Float:tempposz;
		
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		GetPlayerPos(targetid, posx, posy, posz);
		
		tempposx = (oldposx -posx);
		tempposy = (oldposy -posy);
		tempposz = (oldposz -posz);
		
		if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
			return 1;
	}
	
	return 0;
}

stock VehicleToPoint(vehid, Float:point_x, Float:point_y, Float:point_z, Float:radi)
{
	new Float:pos[3];
	GetVehiclePos(vehid, pos[0], pos[1], pos[2]);
	
	new Float:temppos[3];
	temppos[0] = (point_x -pos[0]);
	temppos[1] = (point_y -pos[1]);
	temppos[2] = (point_z -pos[2]);
	
	if(temppos[0] >= radi || -temppos[0] >= radi || temppos[1] >= radi || -temppos[1] >= radi || temppos[2] >= radi || -temppos[2] >= radi) return 1;
	
	return 0;
}

public SavePlayerStats(playerid, what)
{
	new query[512];
	if(what == SAVE_PLAYER_BASIC)
	{
		format(query, sizeof(query), "UPDATE `srv_characters` SET `skin` = '%d', `cash` = '%d', `hours` = '%d', `minutes` = '%d', `hp` = '%f', `credit` = '%d', `bw` = '%d', `glod` = '%d', `online_today`='%d' WHERE `player_uid` = '%d' LIMIT 1",
		CharacterInfo[playerid][pSkin],
		CharacterInfo[playerid][pCash],
		CharacterInfo[playerid][pHours],
		CharacterInfo[playerid][pMinutes],
		CharacterInfo[playerid][pHealth],
		CharacterInfo[playerid][pCredit],
		CharacterInfo[playerid][pBW],
		CharacterInfo[playerid][pGlod],
		CharacterInfo[playerid][pOnlineToday],
		
		CharacterInfo[playerid][pUID]);
		
		mysql_query(query);
	}
	else if(what == SAVE_PLAYER_PENALTY)
	{
		format(query, sizeof(query), "UPDATE `srv_characters` SET  `block` = '%d', `nogun` = '%d', `nocar` = '%d', `noooc` = '%d', `norun` = '%d' WHERE `player_uid` = '%d' LIMIT 1",
		CharacterInfo[playerid][pBlock],
		CharacterInfo[playerid][pBlockNoGun],
		CharacterInfo[playerid][pBlockNoCar],
		CharacterInfo[playerid][pBlockNoOOC],
		CharacterInfo[playerid][pBlockNoRun],
		
		CharacterInfo[playerid][pUID]);
		
		mysql_query(query);
	}
	else if(what == SAVE_PLAYER_ADMIN)
	{
		format(query, sizeof(query), "UPDATE `srv_characters` SET `admin` = '%d' WHERE `player_uid` = '%d' LIMIT 1",
		CharacterInfo[playerid][pAdmin],
		
		CharacterInfo[playerid][pUID]);
		
		mysql_query(query);
	}
	else if(what == SAVE_PLAYER_GLOBAL)
	{
		format(query, sizeof(query), "UPDATE `members` SET `score` = '%d', `warn`='%d', `curse`='%d', `aj`='%d' WHERE `member_id` = '%d' LIMIT 1",
		CharacterInfo[playerid][pGlobalScore],
		CharacterInfo[playerid][pWarn],
		CharacterInfo[playerid][pCurse],
		CharacterInfo[playerid][pAJ],
		
		CharacterInfo[playerid][pGID]);
		
		mysql_query(query);
	}
	else if(what == SAVE_PLAYER_POS)
	{
		if(GetPVarInt(playerid,"pBus"))
		{
			new bus=GetPVarInt(playerid,"pBus");
			CharacterInfo[playerid][pPos][0]=BusInfo[bus][bPosX];
			CharacterInfo[playerid][pPos][1]=BusInfo[bus][bPosY];
			CharacterInfo[playerid][pPos][2]=BusInfo[bus][bPosZ];
		}
		else
			GetPlayerPos(playerid,CharacterInfo[playerid][pPos][0],CharacterInfo[playerid][pPos][1],CharacterInfo[playerid][pPos][2]);
		CharacterInfo[playerid][pInt] =GetPlayerInterior(playerid);
		CharacterInfo[playerid][pVW] =GetPlayerVirtualWorld(playerid);
		format(query, sizeof(query), "UPDATE `srv_characters` SET `pos_x` = '%f', `pos_y` = '%f', `pos_z` = '%f', `vw` = '%d', `interior` = '%d' WHERE `player_uid` = '%d' LIMIT 1",
		CharacterInfo[playerid][pPos][0],
		CharacterInfo[playerid][pPos][1],
		CharacterInfo[playerid][pPos][2],
		CharacterInfo[playerid][pVW],
		CharacterInfo[playerid][pInt],
		
		CharacterInfo[playerid][pUID]);
		
		mysql_query(query);
	}
	else if(what == SAVE_PLAYER_OPTION)
	{
		format(query, sizeof(query), "UPDATE `srv_characters` SET `tog` = '%d', `docs`='%d', `phone_uid` = '%d', `radio_channel`='%d', `penaltypoints`='%d', `strength`='%d', `strength_today`='%d', `driverpenalty`='%d', `fightstyle`='%d', `suplement`='%d' WHERE `player_uid` = '%d' LIMIT 1",
		CharacterInfo[playerid][pTog],
		CharacterInfo[playerid][pDocs],
		CharacterInfo[playerid][pPhone],
		CharacterInfo[playerid][pKanal],
		CharacterInfo[playerid][pPenaltyPoints],
		CharacterInfo[playerid][pStrength],
		CharacterInfo[playerid][pStrengthToday],
		CharacterInfo[playerid][pDriverPenalty],
		CharacterInfo[playerid][pFightStyle],
		CharacterInfo[playerid][pSuplement],
		
		CharacterInfo[playerid][pUID]);
		
		mysql_query(query);
	}
	else if(what == SAVE_PLAYER_SPAWN)
	{
		format(query, sizeof(query), "UPDATE `srv_characters` SET `spawnopt` = '%d', `spawnhouseopt` = '%d' WHERE `player_uid` = '%d' LIMIT 1",
		CharacterInfo[playerid][pSpawnOption],
		CharacterInfo[playerid][pSpawnOptionHouseID],
		
		CharacterInfo[playerid][pUID]);
		
		mysql_query(query);
	}
	else if(what == SAVE_PLAYER_JAIL)
	{
		format(query, sizeof(query), "UPDATE `srv_characters` SET `jail` = '%d', `jail_time` = '%d' WHERE `player_uid` = '%d' LIMIT 1",
		CharacterInfo[playerid][pJail],
		CharacterInfo[playerid][pJailTime],
		
		CharacterInfo[playerid][pUID]);
		
		mysql_query(query);
	}
	else if(what == SAVE_PLAYER_JOBS)
	{
		format(query, sizeof(query), "UPDATE `srv_characters` SET `job` = '%d', `job_count` = '%d' WHERE `player_uid` = '%d' LIMIT 1",
		CharacterInfo[playerid][pJob],
		CharacterInfo[playerid][pJobCount],
		
		CharacterInfo[playerid][pUID]);
		
		mysql_query(query);
	}
	else if(what == SAVE_PLAYER_PREMIUM)
	{
		format(query, sizeof(query), "UPDATE `members` SET `premium` = '%d' WHERE `member_id` = '%d' LIMIT 1",
		CharacterInfo[playerid][pPremium],
		
		CharacterInfo[playerid][pGID]);
		
		mysql_query(query);
	}
	else if(what == SAVE_LAST_DAMAGE)
	{
		format(query, sizeof(query), "UPDATE `srv_characters` SET `lastdmg` = '%f', `lasthb` = '%d', `lastweap` = '%d' WHERE `player_uid` = '%d' LIMIT 1",
		CharacterInfo[playerid][pLastDMG],
		CharacterInfo[playerid][pLastHB],
		CharacterInfo[playerid][pLastWEAP],
		
		CharacterInfo[playerid][pUID]);
		
		mysql_query(query);
	}
	return 1;
}

stock SendPlayerText(Float:radi, playerid, string2[], col1, col2, col3, col4, col5, bool:chatooc, ignoreplayer)
{
	if(IsPlayerConnected(playerid))
	{
		new Float:posx, Float:posy, Float:posz;
		new Float:oldposx, Float:oldposy, Float:oldposz;
		new Float:tempposx, Float:tempposy, Float:tempposz;
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		ForeachPlayer(i)
		{
			if(IsPlayerConnected(i) && (GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i)) && !(chatooc && CharacterInfo[i][pTog] & TOG_CHATOOC) && !(ignoreplayer != INVALID_PLAYER_ID && ignoreplayer == i))
			{
				GetPlayerPos(i, posx, posy, posz);
				tempposx = (oldposx -posx);
				tempposy = (oldposy -posy);
				tempposz = (oldposz -posz);
				new color = 0;
				if (((tempposx < radi/16) && (tempposx > -radi/16)) && ((tempposy < radi/16) && (tempposy > -radi/16)) && ((tempposz < radi/16) && (tempposz > -radi/16)))
					color = col1;
				else if (((tempposx < radi/8) && (tempposx > -radi/8)) && ((tempposy < radi/8) && (tempposy > -radi/8)) && ((tempposz < radi/8) && (tempposz > -radi/8)))
					color = col2;
				else if (((tempposx < radi/4) && (tempposx > -radi/4)) && ((tempposy < radi/4) && (tempposy > -radi/4)) && ((tempposz < radi/4) && (tempposz > -radi/4)))
					color = col3;
				else if (((tempposx < radi/2) && (tempposx > -radi/2)) && ((tempposy < radi/2) && (tempposy > -radi/2)) && ((tempposz < radi/2) && (tempposz > -radi/2)))
					color = col4;
				else if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
					color = col5;
					
				if(color != 0) {
					SendClientMessage(i, color, string2);
					if(!chatooc)
						playerLog(i,"IC",string2);
					else
						playerLog(i,"OOC",string2);
						
				}
					
			}
		}
	}
	return 1;
}

public FreezePlayer(playerid)
{
	TogglePlayerControllable(playerid,0);
	return 1;
}

public UnfreezePlayer(playerid)
{
	TogglePlayerControllable(playerid,1);
	return 1;
}

public SetPlayerSpawn(playerid)
{
	if(CharacterInfo[playerid][pBW] || CharacterInfo[playerid][pTog] & TOG_QS || CharacterInfo[playerid][pWounded])
		SetSpawnInfo(playerid, 0, CharacterInfo[playerid][pSkin], CharacterInfo[playerid][pPos][0], CharacterInfo[playerid][pPos][1], CharacterInfo[playerid][pPos][2], 0.0, -1,-1,-1,-1,-1,-1);
	else if(CharacterInfo[playerid][pJailTime] > gettime())
	{
		new dooruid = CharacterInfo[playerid][pJail];
		SetSpawnInfo(playerid, 0, CharacterInfo[playerid][pSkin], DoorsInfo[dooruid][dExitX], DoorsInfo[dooruid][dExitY], DoorsInfo[dooruid][dExitZ], 0.0, -1,-1,-1,-1,-1,-1);
	}
	else switch(CharacterInfo[playerid][pSpawnOption])
	{
		case SPAWN_TYPE_CENTRUM:
			SetSpawnInfo(playerid, 0, CharacterInfo[playerid][pSkin], SettingInfo[sSpawnX], SettingInfo[sSpawnY], SettingInfo[sSpawnZ], SettingInfo[sSpawnAngle], -1,-1,-1,-1,-1,-1);
		case SPAWN_TYPE_HOUSE:
		{
			if(CharacterInfo[playerid][pOnlineToday] <= 10)
			{
				CharacterInfo[playerid][pGlod] = 100;
				SetPlayerHP(playerid, 100);
			}
			
			new dooruid = CharacterInfo[playerid][pSpawnOptionHouseID];
			SetSpawnInfo(playerid, 0, CharacterInfo[playerid][pSkin], DoorsInfo[dooruid][dExitX], DoorsInfo[dooruid][dExitY], DoorsInfo[dooruid][dExitZ], DoorsInfo[dooruid][dExitAngle], -1,-1,-1,-1,-1,-1);
		}
		case SPAWN_TYPE_LASTPOS:
			SetSpawnInfo(playerid, 0, CharacterInfo[playerid][pSkin], CharacterInfo[playerid][pPos][0], CharacterInfo[playerid][pPos][1], CharacterInfo[playerid][pPos][2], 0.0, -1,-1,-1,-1,-1,-1);
		case SPAWN_TYPE_GROUP:
		{
			new groupid = CharacterInfo[playerid][pSpawnOptionHouseID];
			SetSpawnInfo(playerid, 0,CharacterInfo[playerid][pSkin], GroupInfo[groupid][gSpawnX], GroupInfo[groupid][gSpawnY], GroupInfo[groupid][gSpawnZ], GroupInfo[groupid][gSpawnAngle], -1,-1,-1,-1,-1,-1);
		}
		case SPAWN_TYPE_HOTEL:
			SetSpawnInfo(playerid, 0, CharacterInfo[playerid][pSkin], 2233.618408, -1114.630249, 1050.882812, 0.0, -1,-1,-1,-1,-1,-1);
		case SPAWN_TYPE_LMEXICO:
			SetSpawnInfo(playerid, 0, CharacterInfo[playerid][pSkin], 1722.4227, -1712.8549, 13.5069, 182.4612, -1,-1,-1,-1,-1,-1);
		default:
			SetSpawnInfo(playerid, 0, CharacterInfo[playerid][pSkin], SettingInfo[sSpawnX], SettingInfo[sSpawnY], SettingInfo[sSpawnZ], SettingInfo[sSpawnAngle], -1,-1,-1,-1,-1,-1);
	}
	return 1;
}

public SendPlayerToSpawn(playerid)
{
	if(CharacterInfo[playerid][pBW] || CharacterInfo[playerid][pWounded])
	{
		SetPlayerPos(playerid, CharacterInfo[playerid][pPos][0], CharacterInfo[playerid][pPos][1], CharacterInfo[playerid][pPos][2]);
		SetPlayerVirtualWorld(playerid, CharacterInfo[playerid][pVW]);
		SetPlayerInterior(playerid, CharacterInfo[playerid][pInt]);
		
		SetPlayerCameraPos(playerid, CharacterInfo[playerid][pPos][0] + 1, CharacterInfo[playerid][pPos][1] + 2, CharacterInfo[playerid][pPos][2] + 3);
		SetPlayerCameraLookAt(playerid, CharacterInfo[playerid][pPos][0], CharacterInfo[playerid][pPos][1], CharacterInfo[playerid][pPos][2]);
		
		TogglePlayerControllable(playerid, 0);
	}
	else if(CharacterInfo[playerid][pJailTime] > gettime())
	{
		new dooruid = CharacterInfo[playerid][pJail];
		SetPlayerPos(playerid, DoorsInfo[dooruid][dExitX], DoorsInfo[dooruid][dExitY], DoorsInfo[dooruid][dExitZ]);
		SetPlayerFacingAngle(playerid, DoorsInfo[dooruid][dExitAngle]);
		SetCameraBehindPlayer(playerid);
		PlayerDoor[playerid]=dooruid;
		
		SetPlayerVirtualWorld(playerid, DoorsInfo[dooruid][dExitVW]);
		SetPlayerInterior(playerid, DoorsInfo[dooruid][dExitInt]);
	}
	else if(CharacterInfo[playerid][pTog] & TOG_QS)
	{
		SetPlayerPos(playerid, CharacterInfo[playerid][pPos][0], CharacterInfo[playerid][pPos][1], CharacterInfo[playerid][pPos][2]);
		SetPlayerFacingAngle(playerid, 0);
		SetCameraBehindPlayer(playerid);
		
		SetPlayerVirtualWorld(playerid, CharacterInfo[playerid][pVW]);
		SetPlayerInterior(playerid, CharacterInfo[playerid][pInt]);
		PlayerDoor[playerid]=0;
	}
	else
	{
		switch(CharacterInfo[playerid][pSpawnOption])
		{
			case SPAWN_TYPE_CENTRUM:
			{
				SetPlayerPos(playerid, SettingInfo[sSpawnX], SettingInfo[sSpawnY], SettingInfo[sSpawnZ]);
				SetPlayerFacingAngle(playerid, SettingInfo[sSpawnAngle]);
				SetCameraBehindPlayer(playerid);
				
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerInterior(playerid, 0);
				PlayerDoor[playerid]=0;
			}
			case SPAWN_TYPE_HOUSE:
			{
				new dooruid = CharacterInfo[playerid][pSpawnOptionHouseID];
				
				if(DoorsInfo[dooruid][dUID] && (IsDoorOwner(playerid, dooruid) || IsDoorMember(playerid, dooruid)))
				{
					PlayerDoor[playerid]=dooruid;
					SetPlayerPos(playerid, DoorsInfo[dooruid][dExitX], DoorsInfo[dooruid][dExitY], DoorsInfo[dooruid][dExitZ]);
					SetPlayerFacingAngle(playerid, DoorsInfo[dooruid][dExitAngle]);
					SetCameraBehindPlayer(playerid);
					
					SetPlayerVirtualWorld(playerid, DoorsInfo[dooruid][dExitVW]);
					SetPlayerInterior(playerid, DoorsInfo[dooruid][dExitInt]);
				}
				else
				{
					SetPlayerPos(playerid, SettingInfo[sSpawnX], SettingInfo[sSpawnY], SettingInfo[sSpawnZ]);
					SetPlayerFacingAngle(playerid, SettingInfo[sSpawnAngle]);
					SetCameraBehindPlayer(playerid);
					
					SetPlayerVirtualWorld(playerid, 0);
					SetPlayerInterior(playerid, 0);
					PlayerDoor[playerid]=0;
					
					CharacterInfo[playerid][pSpawnOption] = 0;
					CharacterInfo[playerid][pSpawnOptionHouseID] = 0;
					
					SavePlayerStats(playerid, SAVE_PLAYER_SPAWN);
				}
			}
			case SPAWN_TYPE_LASTPOS:
			{
				SetPlayerPos(playerid, CharacterInfo[playerid][pPos][0], CharacterInfo[playerid][pPos][1], CharacterInfo[playerid][pPos][2]);
				SetPlayerFacingAngle(playerid, 0);
				SetCameraBehindPlayer(playerid);
				PlayerDoor[playerid]=0;
		
				SetPlayerVirtualWorld(playerid, CharacterInfo[playerid][pVW]);
				SetPlayerInterior(playerid, CharacterInfo[playerid][pInt]);
			}
			case SPAWN_TYPE_GROUP:
			{
				new groupid = CharacterInfo[playerid][pSpawnOptionHouseID];
				
				if(IsPlayerInGroup(playerid, groupid))
				{
					SetPlayerPos(playerid, GroupInfo[groupid][gSpawnX], GroupInfo[groupid][gSpawnY], GroupInfo[groupid][gSpawnZ]);
					SetPlayerFacingAngle(playerid, GroupInfo[groupid][gSpawnAngle]);
					SetCameraBehindPlayer(playerid);
					PlayerDoor[playerid]=0;
					
					SetPlayerVirtualWorld(playerid, GroupInfo[groupid][gSpawnVW]);
					SetPlayerInterior(playerid, GroupInfo[groupid][gSpawnInt]);
				}
				else
				{
					SetPlayerPos(playerid, SettingInfo[sSpawnX], SettingInfo[sSpawnY], SettingInfo[sSpawnZ]);
					SetPlayerFacingAngle(playerid, SettingInfo[sSpawnAngle]);
					SetCameraBehindPlayer(playerid);
					PlayerDoor[playerid]=0;
					
					SetPlayerVirtualWorld(playerid, 0);
					SetPlayerInterior(playerid, 0);
					
					CharacterInfo[playerid][pSpawnOption] = 0;
					CharacterInfo[playerid][pSpawnOptionHouseID] = 0;
					
					SavePlayerStats(playerid, SAVE_PLAYER_SPAWN);
				}
			}
			case SPAWN_TYPE_HOTEL:
			{
				if(!CharacterInfo[playerid][pHotel] || DoorsInfo[CharacterInfo[playerid][pHotel]][dOwnerTyp]!=OWNER_HOTEL)
				{
					CharacterInfo[playerid][pHotel]=0;
					new query[128];
					format(query,sizeof(query),"UPDATE `srv_characters` SET `hotel`='0' WHERE `player_uid`='%d'",CharacterInfo[playerid][pUID]);
					mysql_query(query);
					SetPlayerPos(playerid, SettingInfo[sSpawnX], SettingInfo[sSpawnY], SettingInfo[sSpawnZ]);
					SetPlayerFacingAngle(playerid, SettingInfo[sSpawnAngle]);
					SetCameraBehindPlayer(playerid);
					
					SetPlayerVirtualWorld(playerid, 0);
					SetPlayerInterior(playerid, 0);
					PlayerDoor[playerid]=0;
					
					CharacterInfo[playerid][pSpawnOption] = 0;
					SavePlayerStats(playerid, SAVE_PLAYER_SPAWN);
				}
				else
				{
					SetCameraBehindPlayer(playerid);
					SetPlayerInterior(playerid, 5);
					SetPlayerPos(playerid,2233.618408, -1114.630249, 1050.882812);
					SetPlayerVirtualWorld(playerid, CharacterInfo[playerid][pUID]+37);
					SetPlayerFacingAngle(playerid, 0.0);

					PlayerDoor[playerid]=CharacterInfo[playerid][pHotel];
				}
			}
			case SPAWN_TYPE_LMEXICO:
			{
				SetPlayerPos(playerid, 1722.4227, -1712.8549, 13.5069);
				SetPlayerFacingAngle(playerid, 182.4612);
				SetCameraBehindPlayer(playerid);
				
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerInterior(playerid, 0);
				PlayerDoor[playerid]=0;
			}
		}
	}
	
	return 1;
}

public KickWithWait(playerid)
{
	SetTimerEx("KickPlayer", 350, false, "i", playerid);
}

public KickPlayer(playerid)
{
	Kick(playerid);
}

public GetPlayerSpeed(playerid)
{
	new Float:X, Float:Y, Float:Z;
	GetPlayerVelocity(playerid, X, Y, Z);
	return floatround(floatsqroot(floatabs(X*X) + floatabs(Y*Y) + floatabs(Z*Z)) * 200.0);
}

public PlayerOnDrug(playerid)
{
	switch(CharacterInfo[playerid][pDrugs])
	{
		case DRUG_MARIHUANA:
		{
			SetPlayerWeather(playerid, 65);
			SetPlayerDrunkLevel(playerid, 3000);
			CharacterInfo[playerid][pDrugsTime] = 600;
		}
		case DRUG_KOKAINA:
		{
			SetPlayerWeather(playerid, -53);
			CharacterInfo[playerid][pDrugsTime] = 600;
		}
		case DRUG_HEROINA:
		{
			SetPlayerWeather(playerid, -66);
			SetPlayerDrunkLevel(playerid, 5000);
			CharacterInfo[playerid][pDrugsTime] = 600;
		}
		case DRUG_LSD:
		{
			SetPlayerWeather(playerid, -107);
			SetPlayerDrunkLevel(playerid, 5000);
			CharacterInfo[playerid][pDrugsTime] = 600;
		}
		case DRUG_ALKO:
		{
			SetPlayerDrunkLevel(playerid, 7000);
			CharacterInfo[playerid][pDrugsTime] = 600;
		}
	}
	
	return 1;
}

public PlayerTrackNumber(playerid, playerid2, numer)
{
	if(!IsPlayerOnDutyInGroup(playerid, GROUP_PD))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
	
	if(!PlayerDoor[playerid])
		return msg_error(playerid,"Nie znajdujesz siê w pomieszczeniu komisariatu policji.");
	
	else if(!(DoorsInfo[PlayerDoor[playerid]][dOwnerTyp] == OWNER_GROUP && GroupInfo[DoorsInfo[PlayerDoor[playerid]][dOwner]][gType] == GROUP_PD))
		return msg_error(playerid,"Nie znajdujesz siê w pomieszczeniu komisariatu policji.");
	
	if(playerid2 < 0 || !Logged[playerid2])
		return cmd_do(playerid, "Wybrany abonent jest poza zasiêgiem, procedura namierzania przerwana.");
	
	else if(!CharacterInfo[playerid2][pPhone])
		return cmd_do(playerid, "Wybrany abonent jest poza zasiêgiem, procedura namierzania przerwana.");
	
	new ran = random(50)-25;
	
	if(PlayerDoor[playerid2])
		SetPlayerMapIcon(playerid, 99, DoorsInfo[PlayerDoor[playerid2]][dEnterX]+ran, DoorsInfo[PlayerDoor[playerid2]][dEnterY]+ran, DoorsInfo[PlayerDoor[playerid2]][dEnterZ], 61, 0, MAPICON_GLOBAL);
	else
	{
		new Float:Pos[3];
		
		GetPlayerPos(playerid2, Pos[0], Pos[1], Pos[2]);
		
		SetPlayerMapIcon(playerid, 99, Pos[0]+ran, Pos[1]+ran, Pos[2], 61, 0, MAPICON_GLOBAL);
	}
	
	SendClientMessage(playerid, COLOR_GREEN, "Namierzanie zakoñczone, zaznaczono na mapie. Aby usun¹æ ikonke z mapy, namierz ponownie lub wpisz: /namierz wylacz");
	
	return 1;
}

stock SetPlayerHP(playerid, Float:amount)
{
	if(amount > 100)
	{
		CharacterInfo[playerid][pHealth] = 100.0;
		SetPlayerHealth(playerid, CharacterInfo[playerid][pHealth]);
	}
	else if(amount < 0)
	{
		CharacterInfo[playerid][pHealth] = 0;
		SetPlayerHealth(playerid, CharacterInfo[playerid][pHealth]);
	}
	else
	{
		CharacterInfo[playerid][pHealth] = amount;
		SetPlayerHealth(playerid, CharacterInfo[playerid][pHealth]);
	}
}

stock WordWrap(givenString[], spaces)
{
	new editingString[144], spaceCounter = 0;
	memcpy(editingString, givenString, 0, 144 * 4);

	for (new i = 0; editingString[i] != 0; i++)
	{
		if(editingString[i] == ',' || editingString[i] == '.')
			if(editingString[i+1] != ' ') strins(editingString, " ", i + 1);

		if(editingString[i] == ' ' && editingString[i+1] != ' ') spaceCounter++;

		if(spaceCounter >= spaces)
		{
			editingString[i] = '\n';
			spaceCounter = 0;
		}
	}
	return editingString;
}

public Oferta(typ, playerid, playerid2, cena, uid)
{
	if(typ == OFFER_MANDAT || typ == OFFER_REPAIR_ENG || typ == OFFER_REPAIR_BODY || typ == OFFER_REPAIR_TIRES || typ == OFFER_REPAIR_ALL || typ == OFFER_PAINT || typ == OFFER_PAINTJOB || typ == OFFER_TUNING || typ == OFFER_DISMOUNT)
	{
		if(CharacterInfo[playerid2][pCash] < cena && CharacterInfo[playerid2][pCredit] < cena)
		{
			msg_infoFormat(playerid, 128, "Wybrany gracz nie posiada odpowiedniej iloœci gotówki.\nPotrzebuje $%d.", cena);
			return 1;
		}
	}
	else
	{
		if(CharacterInfo[playerid2][pCash] < cena)
		{
			msg_infoFormat(playerid, 128, "Wybrany gracz nie posiada odpowiedniej iloœci gotówki.\nPotrzebuje $%d.", cena);
			return 1;
		}
	}

	if(!uid && typ != OFFER_MANDAT) return 1;

	if(GetPVarInt(playerid2,"OfferUID") || GetPVarInt(playerid,"OfferUID"))
		return msg_error(playerid,"Jeden z graczy posiada ju¿ aktywn¹ ofertê");
	new string[160];
	switch(typ)
	{
		case OFFER_ITEM:
			format(string,sizeof(string),"~g~Oferta od:~w~ %s~n~~g~Typ:~w~ Przedmiot~n~%s [%d:%d]~n~~g~Cena: $~w~%d", PlayerName2(playerid), ItemInfo[uid][iName], ItemInfo[uid][iValue1], ItemInfo[uid][iValue2], cena);
		case OFFER_VEHICLE:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ: ~w~Pojazd~n~%s [%d]~n~~g~Cena: $~w~%d", PlayerName2(playerid), GetVehicleModelName(VehicleInfo[uid][vModel]), uid, cena);
		case OFFER_HOUSE:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ:~w~ Dom~n~[UID: %d]~n~~g~Cena: $~w~%d", PlayerName2(playerid), uid, cena);
		case OFFER_VCARD:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ: ~w~Kontakt", PlayerName2(playerid));
		case OFFER_REPAIR_ENG:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ: ~w~Naprawa silnika~n~%s [%d]~n~~g~Cena: $~w~%d", PlayerName2(playerid), GetVehicleModelName(VehicleInfo[uid][vModel]), uid, cena);
		case OFFER_REPAIR_BODY:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ:~w~ Naprawa karoserii~n~%s [%d]~n~~g~Cena: $~w~%d", PlayerName2(playerid), GetVehicleModelName(VehicleInfo[uid][vModel]), uid, cena);
		case OFFER_REPAIR_TIRES:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ:~w~ Naprawa opon~n~%s [%d]~n~~g~Cena: $~w~%d", PlayerName2(playerid), GetVehicleModelName(VehicleInfo[uid][vModel]), uid, cena);
		case OFFER_REPAIR_ALL:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ:~w~ Naprawa calkowita~n~%s [%d]~n~~g~Cena: $~w~%d", PlayerName2(playerid), GetVehicleModelName(VehicleInfo[uid][vModel]), uid, cena);
		case OFFER_PAINT:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ:~w~ Malowanie~n~%s [%d:%d]~n~~g~Cena: $~w~%d", PlayerName2(playerid), GetVehicleModelName(VehicleInfo[uid][vModel]), GetPVarInt(playerid,"pRepairColor1"),GetPVarInt(playerid,"pRepairColor2"),cena);
		case OFFER_PAINTJOB:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ:~w~ Paintjob~n~%s [%d]~n~~g~Cena: $~w~%d", PlayerName2(playerid), GetVehicleModelName(VehicleInfo[uid][vModel]), GetPVarInt(playerid,"pRepairPaint"),cena);
		case OFFER_TUNING:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ:~w~ Tuning~n~%s~n~~g~Cena: $~w~%d", PlayerName2(playerid), ItemInfo[GetPVarInt(playerid,"pRepairPart")][iName],cena);
		case OFFER_TAXI:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ:~w~ Przejazd taxi~n~~n~~g~Cena: $~w~%d za 1km", PlayerName2(playerid),cena);
		case OFFER_MANDAT:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ:~w~ Mandat karny~n~~g~Cena: $~w~%d ~n~~g~Punkty karne: ~w~%d", PlayerName2(playerid), cena, uid);
		case OFFER_DISMOUNT:
		{
			new query[64];
			format(query,sizeof(query),"SELECT `name` FROM `srv_tuning` WHERE `id`='%d'",GetPVarInt(playerid, "pRepairPart"));
			mysql_query(query);
			mysql_store_result();
			mysql_fetch_row_format(query);
			mysql_free_result();
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ:~w~ Demontaz~n~%s~n~~g~Cena: $~w~%d", PlayerName2(playerid), query,cena);
		}
		case OFFER_ADVERT:
		{
			new adv[128];
			GetPVarString(playerid, "advert", adv, 128);
			
			format(string, sizeof(string), "~g~Oferta od: ~w~%s~n~~g~Typ:~w~ Reklama~n~~g~Cena: $~w~%d~n~~g~Czas: ~w~%d min", PlayerName2(playerid), cena, uid);
			SendClientMessageFormat(playerid2, COLOR_GREEN, "[REKLAMA] Treœæ: %s", adv);
			if(playerid != playerid2)
				SendClientMessageFormat(playerid, COLOR_GREEN, "[REKLAMA] Treœæ: %s", adv);
		}
		case OFFER_DOCID:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ:~w~ Dowod osobisty~n~~n~~g~Cena: $~w~%d", PlayerName2(playerid),cena);
		case OFFER_DOCDRIVER:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ:~w~ Prawo jazdy~n~~n~~g~Cena: $~w~%d", PlayerName2(playerid),cena);
		case OFFER_DOCPILOT:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ:~w~ Licencja pilota~n~~n~~g~Cena: $~w~%d", PlayerName2(playerid), cena);
		case OFFER_DOCWEAPONS:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ:~w~ Licencja na bron~n~~n~~g~Cena: $~w~%d", PlayerName2(playerid),cena);
		case OFFER_DOCMED:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ:~w~ Dokument o poczytalnosci~n~~n~~g~Cena: $~w~%d", PlayerName2(playerid),cena);
		case OFFER_REGISTERCAR:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ:~w~ Rejestracja pojazdu~n~%s [%d]~n~~g~Cena: $~w~%d",PlayerName2(playerid),GetVehicleModelName(VehicleInfo[uid][vModel]),uid,cena);
		case OFFER_REGISTERGROUP:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ:~w~ Rejestracja biznesu~n~%s[%d]~n~~g~Cena: $~w~%d",PlayerName2(playerid),GroupInfo[uid][gName],uid,cena);
		case OFFER_GYM_SINGLE:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ:~w~ Karnet jednorazowy~n~~g~Cena: $~w~%d",PlayerName2(playerid),cena);
		case OFFER_GYM_DAY:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ:~w~ Karnet jednodniowy~n~~g~Cena: $~w~%d",PlayerName2(playerid),cena);
		case OFFER_GYM_WEEK:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ:~w~ Karnet tygodniowy~n~~g~Cena: $~w~%d",PlayerName2(playerid),cena);
		case OFFER_RESTAURANT_ITEM:
			format(string,sizeof(string),"~g~Oferta od:~w~ %s~n~~g~Typ:~w~ Przedmiot~n~%s ~n~~g~Cena: $~w~%d", PlayerName2(playerid), ItemInfo[uid][iName], cena);
		case OFFER_MEDICINE:
			format(string,sizeof(string),"~g~Oferta od:~w~ %s~n~~g~Typ:~w~ Uleczenie~n~~g~Cena: $~w~%d", PlayerName2(playerid), cena);
		case OFFER_VEHICLE_KOMIS:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ: ~w~Pojazd~n~%s [%d]~n~~g~Cena: $~w~%d", GroupInfo[DutyGroup[playerid]][gName], GetVehicleModelName(VehicleInfo[uid][vModel]), uid, cena);
		case OFFER_YO:
			format(string,sizeof(string),"~g~Oferta od: ~w~%s~n~~g~Typ: ~w~Przywitanie~n~0~n~~g~Cena: $~w~0", PlayerName2(playerid2));
	}
	
	SendClientMessage(playerid2,COLOR_GREEN,"Otrzyma³es now¹ ofertê. U¿yj /akceptuj lub /odrzuc");
	PlayerTextDrawSetString(playerid2,OFFER[playerid2],string);
	PlayerTextDrawShow(playerid2, OFFER[playerid2]);
	PlayerTextDrawShow(playerid2, ACCEPT[playerid2]);
	PlayerTextDrawShow(playerid2, REJECT[playerid2]);
	SelectTextDraw(playerid2,-1);
	SetPVarInt(playerid,"OfferBuyer",playerid2);
	SetPVarInt(playerid2,"OfferUID",uid);
	SetPVarInt(playerid2,"OfferPrice",cena);
	SetPVarInt(playerid2,"OfferSeller",playerid);
	SetPVarInt(playerid2,"OfferType",typ);
	GameTextForPlayer(playerid, "~g~Oferta wyslana", 3000, 4);
	OfferTimer[playerid2]= SetTimerEx("DisableOffer",15000,false,"ii",playerid2,uid);

	return 1;
}

public DisableOffer(playerid,uid)
{
	if(GetPVarInt(playerid,"OfferUID") && GetPVarInt(playerid,"OfferUID") != uid)
		return 1;
	KillTimer(OfferTimer[playerid]);
	CancelSelectTextDraw(playerid);
	PlayerTextDrawHide(playerid, OFFER[playerid]);
	PlayerTextDrawHide(playerid, ACCEPT[playerid]);
	PlayerTextDrawHide(playerid, REJECT[playerid]);
	
	new seller = GetPVarInt(playerid,"OfferSeller");
	DeletePVar(playerid,"OfferUID");
	DeletePVar(seller,"OfferBuyer");
	DeletePVar(playerid,"OfferPrice");
	DeletePVar(playerid,"OfferSeller");
	DeletePVar(playerid,"OfferType");
	SendClientMessage(seller,COLOR_GREEN,"Oferta anulowana. Up³yn¹³ czas oczekiwania lub gracz wylogowa³ siê.");
	if(playerid != seller)
		SendClientMessage(playerid,COLOR_GREEN,"Oferta anulowana. Up³yn¹³ czas oczekiwania lub gracz wylogowa³ siê.");
	return 1;
}
public msg_error(playerid,string[])
{
	ShowPlayerDialog(playerid,D_INFO,DIALOG_STYLE_MSGBOX,DEF_NAME" » b³¹d",string,"Zamknij","");
	return 1;
}

public msg_info(playerid,string[])
{
	ShowPlayerDialog(playerid,D_INFO,DIALOG_STYLE_MSGBOX,DEF_NAME" » informacja",string,"Zamknij","");
	return 1;
}

public msg_usage(playerid,string[])
{
	ShowPlayerDialog(playerid,D_INFO,DIALOG_STYLE_MSGBOX,DEF_NAME" » zastosowanie",string,"Zamknij","");
	return 1;
}

public Destroy3DText(playerid)
{
	if(quited[playerid])
	{
		DestroyDynamic3DTextLabel(quit[playerid]);
		quited[playerid] = 0;
	}
	return 1;
}

public Tip(playerid,time,string[])
{
	PlayerTextDrawSetString(playerid,TipText[playerid],string);
	PlayerTextDrawShow(playerid,TipText[playerid]);
	SetTimerEx("DisableTip",time*1000,false,"i",playerid);
	return 1;
}

public DisableTip(playerid)
{
	PlayerTextDrawHide(playerid,TipText[playerid]);
	return 1;
}

public HidePlayerWeapons(playerid)
{
	new slot = GetWeaponSlot(CharacterInfo[playerid][pWeaponID]);
	new uid = CharacterInfo[playerid][pWeaponUID];
	new ammo, weapon;
	GetPlayerWeaponData(playerid, slot, weapon, ammo);
	if(ammo > CharacterInfo[playerid][pWeaponAmmo])
		ammo = CharacterInfo[playerid][pWeaponAmmo];
	if(CharacterInfo[playerid][pWeaponAmmo] <= 0) ammo = 0;
	ResetPlayerWeapons(playerid);
	
	mysql_query_format("UPDATE `srv_items` SET `used` = 0, `value2` = '%d' WHERE `uid` = '%d' LIMIT 1", ammo, uid);
	
	ItemInfo[uid][iUsed] = 0;
	ItemInfo[uid][iValue2] = ammo;
	
	CharacterInfo[playerid][pWeaponAmmo] = 0;
	CharacterInfo[playerid][pWeaponID] = 0;
	CharacterInfo[playerid][pWeaponUID] = 0;
	SetTimerEx("NegateHavingWeapons", 2000, false, "i", playerid);

	if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON))
		RemovePlayerAttachedObject(playerid, SLOT_WEAPON);
	
	return 1;
}

public NegateHavingWeapons(playerid)
{
	if(!CharacterInfo[playerid][pWeaponUID])
		CharacterInfo[playerid][pHaveWeapon] = false;
	return 1;
}

public UnfreezeAll()
{
	ForeachPlayer(i)
		TogglePlayerControllable(i,1);

	return 1;
}

stock CanSpeak(playerid)
{
	return !(CharacterInfo[playerid][pBW] || CharacterInfo[playerid][pAJ] || CharacterInfo[playerid][pStatus] & STATUS_KNEBEL);
}

stock CanMove(playerid)
{
	return !(CharacterInfo[playerid][pBW] || CharacterInfo[playerid][pStatus] & STATUS_ZWIAZANY || CharacterInfo[playerid][pStatus] & STATUS_CIAGNIETY || CharacterInfo[playerid][pStatus] & STATUS_KAJDANKI || CharacterInfo[playerid][pWounded]);
}

public DamageColorNickDisable(playerid)
{
	CharacterInfo[playerid][pNickDamageTook] = false;
	UpdatePlayer3DTextNick(playerid);
	
	return 1;
}

public GivePlayerPremium(playerid, days)
{
	if(days == 0)
	{
		new guid, data[8];
		
		CharacterInfo[playerid][pPremium] = 0;
		
		mysql_query_format("SELECT `member_group_id` FROM `members` WHERE `member_id` = '%d' LIMIT 1", CharacterInfo[playerid][pGID]);
		mysql_store_result();
		
		mysql_fetch_row_format(data, "|");
		sscanf(data,  "d", guid);
		
		mysql_free_result();
		
		if(guid == FORUM_GROUP_PREMIUM)
			mysql_query_format("UPDATE `members` SET `member_group_id` = '%d' WHERE `member_id` = '%d' LIMIT 1", FORUM_GROUP_USER, CharacterInfo[playerid][pGID]);
		
		SavePlayerStats(playerid, SAVE_PLAYER_PREMIUM);
	}
	else
	{
		new guid, data[8], time;
		
		if(CharacterInfo[playerid][pPremium] > gettime()) time = CharacterInfo[playerid][pPremium]+days*24*3600;
		else time = gettime() + days*24*3600;
		
		CharacterInfo[playerid][pPremium] = time;
		
		mysql_query_format("SELECT `member_group_id` FROM `members` WHERE `member_id` = '%d' LIMIT 1", CharacterInfo[playerid][pGID]);
		mysql_store_result();
		
		mysql_fetch_row_format(data, "|");
		sscanf(data,  "d", guid);
		
		mysql_free_result();
		
		if(guid == FORUM_GROUP_USER)
			mysql_query_format("UPDATE `members` SET `member_group_id` = '%d' WHERE `member_id` = '%d' LIMIT 1", FORUM_GROUP_PREMIUM, CharacterInfo[playerid][pGID]);
		
		SavePlayerStats(playerid, SAVE_PLAYER_PREMIUM);
	}
	
	return 1;
}

public PlayerLoginCheck(playerid)
{
	if(!Logged[playerid] && IsPlayerConnected(playerid))
	{
		if(GetPlayerVirtualWorld(playerid) != 255)
		{
			KickPlayer(playerid);
			return 1;
		}
		
		SetTimerEx("PlayerLoginCheck", 500, false, "i", playerid);
	}
	
	return 1;
}

stock WalkAnim(playerid)
{
    switch (CharacterInfo[playerid][pWalkStyle])
    {
        case WALK_NORMAL:
        {
			ApplyAnimation(playerid,"PED","WALK_player",4.1,1,1,1,1,1,1);
        }
        case WALK_PED:
        {
			ApplyAnimation(playerid,"PED","WALK_civi",4.1,1,1,1,1,1,1);
        }
        case WALK_GANGSTA:
        {
			ApplyAnimation(playerid,"PED","WALK_gang1",4.1,1,1,1,1,1,1);
        }
        case WALK_GANGSTA2:
        {
			ApplyAnimation(playerid,"PED","WALK_gang2",4.1,1,1,1,1,1,1);
        }
        case WALK_OLD:
        {
			ApplyAnimation(playerid,"PED","WALK_old",4.1,1,1,1,1,1,1);
        }
        case WALK_FAT_OLD:
        {
			ApplyAnimation(playerid,"PED","WALK_fatold",4.1,1,1,1,1,1,1);
        }
        case WALK_FAT:
        {
			ApplyAnimation(playerid,"PED","WALK_fat",4.1,1,1,1,1,1,1);
        }
        case WALK_LADY:
        {
			ApplyAnimation(playerid,"PED","WOMAN_walknorm",4.1,1,1,1,1,1,1);
        }
        case WALK_LADY2:
        {
			ApplyAnimation(playerid,"PED","WOMAN_walkbusy",4.1,1,1,1,1,1,1);
        }
        case WALK_WHORE:
        {
			ApplyAnimation(playerid,"PED","WOMAN_walkpro",4.1,1,1,1,1,1,1);
        }
        case WALK_WHORE2:
        {
			ApplyAnimation(playerid,"PED","WOMAN_walksexy",4.1,1,1,1,1,1,1);
        }
        case WALK_DRUNK:
        {
			ApplyAnimation(playerid,"PED","WALK_drunk",4.1,1,1,1,1,1,1);
        }
        case WALK_BLIND:
        {
			ApplyAnimation(playerid,"PED","Walk_Wuzi",4.1,1,1,1,1,1,1);
        }
        default:
        {
            return 1;
        }
        
    }
    CharacterInfo[playerid][pStatus] |= STATUS_WALK_ANIM;
    return 1;
}
stock StopWalkAnim(playerid)
{
    switch (CharacterInfo[playerid][pWalkStyle])
    {
        case WALK_NORMAL:
        {
			ApplyAnimation(playerid,"PED","WALK_player",4.1,0,0,0,0,1,1);
        }
        case WALK_PED:
        {
			ApplyAnimation(playerid,"PED","WALK_civi",4.1,0,0,0,0,1,1);
        }
        case WALK_GANGSTA:
        {
			ApplyAnimation(playerid,"PED","WALK_gang1",4.1,0,0,0,0,1,1);
        }
        case WALK_GANGSTA2:
        {
			ApplyAnimation(playerid,"PED","WALK_gang2",4.1,0,0,0,0,1,1);
        }
        case WALK_OLD:
        {
			ApplyAnimation(playerid,"PED","WALK_old",4.1,0,0,0,0,1,1);
        }
        case WALK_FAT_OLD:
        {
			ApplyAnimation(playerid,"PED","WALK_fatold",4.1,0,0,0,0,1,1);
        }
        case WALK_FAT:
        {
			ApplyAnimation(playerid,"PED","WALK_fat",4.1,0,0,0,0,1,1);
        }
        case WALK_LADY:
        {
			ApplyAnimation(playerid,"PED","WOMAN_walknorm",4.1,0,0,0,0,1,1);
        }
        case WALK_LADY2:
        {
			ApplyAnimation(playerid,"PED","WOMAN_walkbusy",4.1,0,0,0,0,1,1);
        }
        case WALK_WHORE:
        {
			ApplyAnimation(playerid,"PED","WOMAN_walkpro",4.1,0,0,0,0,1,1);
        }
        case WALK_WHORE2:
        {
			ApplyAnimation(playerid,"PED","WOMAN_walksexy",4.1,0,0,0,0,1,1);
        }
        case WALK_DRUNK:
        {
			ApplyAnimation(playerid,"PED","WALK_drunk",4.1,0,0,0,0,1,1);
        }
        case WALK_BLIND:
        {
			ApplyAnimation(playerid,"PED","Walk_Wuzi",4.1,0,0,0,0,1,1);
        }
        default:
        {
            return 1;
        }
        
    }
    if(CharacterInfo[playerid][pStatus] & STATUS_WALK_ANIM)
        CharacterInfo[playerid][pStatus] -= STATUS_WALK_ANIM;
    return 1;
}

stock SetPlayerLookAt(playerid, Float:X, Float:Y)
{
	new Float:Px, Float:Py, Float: Pa;
	GetPlayerPos(playerid, Px, Py, Pa);
	if(Y-Py == 0.0 || X-Px == 0)
		Pa = 0.0;
	else
		Pa = floatabs(atan((Y-Py)/(X-Px)));
	if (X <= Px && Y >= Py) Pa = floatsub(180, Pa);
	else if (X < Px && Y < Py) Pa = floatadd(Pa, 180);
	else if (X >= Px && Y <= Py) Pa = floatsub(360.0, Pa);
	Pa = floatsub(Pa, 90.0);
	SetPlayerFacingAngle(playerid, Pa);
}

public GetUpAfterFall(playerid)
{
	if(GetPlayerAnimationIndex(playerid) == 1206)
		ApplyAnimation(playerid, "Attractors", "Stepsit_out", 4.0, 0, 0, 0, 0, 0, 1);
	
	return 1;
}