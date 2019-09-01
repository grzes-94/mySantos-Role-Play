forward RestartGMX();
forward DailyRestart();
forward GivePenalty(playerid, admin, time, type, value, reason[64]);
forward AddBan(playerid);
forward HidePenaltyText();

stock SendAdminMessage(color, const string[])
{
	ForeachPlayer(i)
	{
		if(CharacterInfo[i][pAdmin] && !CharacterInfo[i][pAdminMessageTog])
			SendClientMessage(i, color, string);
	}

	return 1;
}

stock SendHAdminMessage(color, const string[])
{
	ForeachPlayer(i)
	{
		if(CharacterInfo[i][pAdmin] > 4 && !CharacterInfo[i][pAdminMessageTog])
			SendClientMessage(i, color, string);
	}
}

stock dechex(number)
{
	new hexadecimal_string[15];
	format(hexadecimal_string, 15, "%x", number);
	return hexadecimal_string;
}

public RestartGMX()
{
	SendRconCommand("gmx");
}
public DailyRestart()
{
	ForeachPlayer(i)
		Kick(i);
	
	new query[512],tmp[16],totalTime,cash;
	LoadGroups();
	//dotacje
	
	for (new i=1;i<MAX_GROUPS;i++)
	{
		if(GroupInfo[i][gUID] && GroupInfo[i][gRegistered]==1 && GroupInfo[i][gGrant]>0)
		{
			format(query,sizeof(query),"SELECT SUM(time) AS ok FROM `srv_groups_members` WHERE `group_uid`='%d' AND `time`>=1800",i);
			mysql_query(query);
			mysql_store_result();
			if(mysql_fetch_row_format(tmp))
				sscanf(tmp,"p<|>d",totalTime);
			else 
				totalTime=0;
			mysql_free_result();

			cash = (GroupInfo[i][gGrant]*totalTime)/3600;
			if(cash>0)
			{
				GroupInfo[i][gSalaryAccount] += cash;
				SaveGroup(i,SAVE_GROUP_BASIC);

				new governor_uid=33;
				new governor_gid=22;

				format(query,sizeof(query),"INSERT INTO `srv_group_offer_logs` VALUES (NULL, '%d', '%d', '%d', '0', '[GOV] Dotacja dzienna', '%d', '%d')",i,governor_uid,governor_gid,cash,gettime());
				mysql_query(query);
			}
		}
	}

	mysql_query("UPDATE `srv_groups_members` SET `time` = 0, `payment` = 0 WHERE 1");
	mysql_query("UPDATE `srv_characters` SET `logged` = 0, `online_today` = 0, `strength_today` = 0, `job_count` = 0, `suplement` = 0 WHERE 1");
	
	format(query, sizeof(query), "DELETE FROM `srv_login_logs` WHERE `time` < '%d'", gettime()-3600*24*31);
	mysql_query(query);
	format(query, sizeof(query), "DELETE FROM `srv_gym_pass` WHERE `time` < '%d'", gettime()); //nieaktywne karnety
	mysql_query(query);
	
	format(query, sizeof(query), "DELETE FROM `srv_items` WHERE `ownertyp` = 1 AND `owner` IN (SELECT `player_uid` FROM `srv_characters` WHERE (`block` & 1 OR `block` & 4) AND `last_online` < '%d')", gettime()-3600*24*14);
	mysql_query(query);
	format(query, sizeof(query), "DELETE FROM `srv_items` WHERE (`ownertyp` = 20 OR `ownertyp` = 21) AND `owner` IN (SELECT `UID` FROM `srv_vehicles` WHERE `ownertyp` = 1 AND `owner` IN (SELECT `player_uid` FROM `srv_characters` WHERE (`block` & 1 OR `block` & 4) AND `last_online` < '%d'))", gettime()-3600*24*14);
	mysql_query(query);
	format(query, sizeof(query), "DELETE FROM `srv_vehicles` WHERE `ownertyp` = 1 AND `owner` IN (SELECT `player_uid` FROM `srv_characters` WHERE (`block` & 1 OR `block` & 4) AND `last_online` < '%d')", gettime()-3600*24*14);
	mysql_query(query);
	
	ForeachEx(i, MAX_SAFEKEEPS)
	{
		if(SafeKeep[i][sUID])
		{
			SafeKeep[i][sInactive]++;
			
			if(SafeKeep[i][sInactive] >= 7)
			{
				format(query, sizeof(query), "DELETE FROM `srv_safekeeps` WHERE `UID` = '%d'", i);
				mysql_query(query);
				format(query, sizeof(query), "DELETE FROM `srv_items` WHERE `type` = '%d' AND `value1` = '%d'", ITEM_TYPE_KEEPKEY, i);
				mysql_query(query);
				format(query, sizeof(query), "DELETE FROM `srv_items` WHERE `ownertyp` = '%d' AND `owner` = '%d'", OWNER_SAFEKEEP_ITEM, i);
				mysql_query(query);
				
				SafeKeep[i][sUID] = 0;
				SafeKeep[i][sInactive] = 0;
			}
			else
			{
				format(query, sizeof(query), "UPDATE `srv_safekeeps` SET `inactive`='%d' WHERE `UID`='%d'", SafeKeep[i][sInactive], i);
				mysql_query(query);
			}
		}
	}

	SetTimerEx("RestartGMX", 1000, false, "");
}

public GivePenalty(playerid, admin, time, type, value, reason[64])
{
	if(!Logged[playerid]) return 1;
	EscapePL(reason);
	
	new str[256], typs[32], nadawca[32];
	if(admin == -1)
		format(str, sizeof(str), "INSERT INTO `srv_penalty` VALUES (NULL, '%d', '%d', '-1', '%d', '%d', '%d', '%s');", CharacterInfo[playerid][pUID], CharacterInfo[playerid][pGID], time, type, value, reason);
	else
		format(str, sizeof(str), "INSERT INTO `srv_penalty` VALUES (NULL, '%d', '%d', '%d', '%d', '%d', '%d', '%s');", CharacterInfo[playerid][pUID], CharacterInfo[playerid][pGID], CharacterInfo[admin][pGID], time, type, value, reason);
	
	mysql_query(str);
	
	switch(type)
	{
		case PENALTY_KICK:  typs = "Kick";
		case PENALTY_WARN:  typs = "Warn";
		case PENALTY_BAN:   typs = "Ban";
		case PENALTY_AJ:	typs = "Admin Jail";
		case PENALTY_UNWARN:  typs = "UnWarn";
		case PENALTY_BLOCK: typs = "Blokada postaci";
		case PENALTY_SCORE: typs = "GameScore";
		case PENALTY_NORUN: typs = "Blokada biegania";
		case PENALTY_NOGUN: typs = "Blokada uzywania broni";
		case PENALTY_NOCAR: typs = "Blokada prowadzenia pojazdow";
		case PENALTY_NOOOC: typs = "Blokada czatow OOC";
		case PENALTY_BAN44: typs = "Ban [4/4 ostrzezenia]";
		case PENALTY_CURSE:format(typs,sizeof(typs),"Klatwa (%d dni)",value);
		case PENALTY_BAN_CURSE: typs = "Ban (klatwa)";
	}
	
	if(admin != -1)
		format(nadawca, sizeof(nadawca), "%s(%d)", CharacterInfo[admin][pGlobalNick],admin);
	else
		format(nadawca, sizeof(nadawca), "System");
	
	format(str,sizeof(str),"{ffffff}Otrzyma³eœ: {E30B0F}%s\n{ffffff}Nadawca: {E30B0F}%s\n{ffffff}Powód: %s\n\nJe¿eli nie zgadzasz siê z kar¹ z³ó¿ apelacjê na forum.",typs,nadawca,reason);

	msg_info(playerid,str);
	
	if(type == PENALTY_WARN) 
		format(str,sizeof(str),"~r~%s [%d/4]~n~~w~Odbiorca: ~w~%s (%s)~n~~w~Nadawca: ~w~%s~n~~y~%s",typs,CharacterInfo[playerid][pWarn],PlayerName3(playerid), CharacterInfo[playerid][pGlobalNick],nadawca, reason);
	else 
		format(str,sizeof(str),"~r~%s~n~~w~Odbiorca: ~w~%s (%s)~n~~w~Nadawca: ~w~%s~n~~y~%s",typs,PlayerName3(playerid), CharacterInfo[playerid][pGlobalNick],nadawca, reason);

	TextDrawSetString(TextPenalty, str);	
	TextDrawShowForAll(TextPenalty);
	
	SetTimer("HidePenaltyText", 10000, false);
	
	return 1;
}

public AddBan(playerid)
{
	new query[128];
	format(query,sizeof(query),"INSERT INTO `srv_bans` VALUES (NULL, '%s', '%d')", GetAccountIP(playerid), CharacterInfo[playerid][pGID]);
	mysql_query(query);
	
	return 1;
}

stock AdminLog(playerid,log[])
{
	new query[256];
	format(query,sizeof(query),"INSERT INTO `panel_admin_log` VALUES (NULL, '%d','%s','%d',0)",CharacterInfo[playerid][pGID],log,gettime());
	mysql_query(query);
	return 1;
}

public HidePenaltyText()
{
	TextDrawHideForAll(TextPenalty);
}
stock log(const pString[], va_args<>)
{
	new string[170],timestamp[20],h,m,File:secretLogs,year,month,day;
	getdate(year, month, day);
	gettime(h,m);
	format(timestamp,sizeof(timestamp),"[%d-%02d-%02d %02d:%02d]",year,month,day,h,m);
	
	va_format(string,sizeof(string),pString,va_start<1>);
	strins(string, timestamp, 0);
	strins(string,"\n",strlen(string));
	secretLogs = fopen("logs.txt",io_append);
	fwrite(secretLogs,string);
	fclose(secretLogs);
}
stock playerLog(playerid, type[], const pString[], va_args<>) 
{
	if(!Logged[playerid])
		return;
		
	new string[170],timestamp[24],fileName[24],h,m,s,File:secretLogs,year,month,day;
	getdate(year, month, day);
	gettime(h,m,s);
	format(timestamp,sizeof(timestamp),"[%02d:%02d:%02d][%s]",h,m,s,type);
	format(fileName,sizeof(fileName),"logs/%d/%d-%02d-%02d.txt",CharacterInfo[playerid][pUID],year,month,day);
	
	va_format(string,sizeof(string),pString,va_start<1>);
	strins(string, timestamp, 0);
	strins(string,"\n",strlen(string));
	secretLogs = fopen(fileName,io_append);
	fwrite(secretLogs,string);
	fclose(secretLogs);
}

forward GetPlayerAdminLevel(playerid);
public GetPlayerAdminLevel(playerid)
{
	return CharacterInfo[playerid][pAdmin];
}