CMD:s(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!CanSpeak(playerid))
		return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
	
	new text[128], string[170];
	if(sscanf(params, "s[128]", text))
		return msg_usage(playerid,"U¿yj: /s(zept) [tekst]");
	else
	{
		text[0] = chrtoupper(text[0]);
		
		format(string, sizeof(string), "%s szepcze: %s", PlayerName2(playerid), text);
		SendWrappedMessageToPlayerRange(playerid, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, string, 2);
	}
	return 1;
}
CMD:szept(playerid, params[]) return cmd_s(playerid, params);
CMD:c(playerid, params[]) return cmd_s(playerid, params);

CMD:k(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!CanSpeak(playerid))
		return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
	new text[128], string[170];
	if(sscanf(params, "s[128]", text))
		return msg_usage(playerid,"U¿yj: /k(rzycz) [tekst]");
	else
	{
		text[0] = chrtoupper(text[0]);
		
		format(string, sizeof(string), "%s krzyczy: %s!!", PlayerName2(playerid), text);
		SendWrappedMessageToPlayerRange(playerid, COLOR_WHITE, COLOR_WHITE, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, string, 25);
		
		if(!(CharacterInfo[playerid][pTog] & TOG_KRZYK))
			ApplyAnimation(playerid, "ON_LOOKERS", "shout_01", 4.0, 0, 0, 0, 0, 0);
	}
	return 1;
}
CMD:krzycz(playerid, params[]) return cmd_k(playerid, params);

CMD:b(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	
	if(CharacterInfo[playerid][pAFKWarn])
		CharacterInfo[playerid][pAFKWarn] = 0;
	
	new text[145], string[170];
	if(sscanf(params, "s[145]", text))
		return msg_usage(playerid,"U¿yj: /b [tekst]");
	else
	{
		if(CharacterInfo[playerid][pBlockNoOOC])
		{
			SendClientMessage(playerid, COLOR_RED, "Posiadasz blokadê czatów OOC.");
			return 1;
		}
		format(string, sizeof(string), "(( %s(%d): %s ))", PlayerName2(playerid), playerid, text);
		SendWrappedMessageToPlayerRange(playerid, COLOR_GREY, COLOR_GREY, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, string, 10, true);
	}
	return 1;
}

CMD:w(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");

	new playerid2, text[128];
	if(sscanf(params, "is[128]", playerid2, text))
		return msg_usage(playerid,"U¿yj: /w [ID gracza] [wiadomoœæ]");
	else
	{
		if(playerid2 == playerid)
			return msg_error(playerid,"Nie mo¿esz wysy³aæ prywatnej wiadomoœci do samego siebie.");
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		if(CharacterInfo[playerid2][pTog] & TOG_PW && !CharacterInfo[playerid][pAdmin])
			return msg_error(playerid, "Wskazany gracz ma wy³¹czone otrzymywanie prywatnych wiadomoœci.");
		if(CharacterInfo[playerid2][pIgnore] != INVALID_PLAYER_ID && CharacterInfo[playerid2][pIgnore] == CharacterInfo[playerid][pUID] && !CharacterInfo[playerid][pAdmin] && !CharacterInfo[playerid2][pAdmin])
			return msg_error(playerid, "Wskazany gracz ignoruje twoje wiadomoœci.");
		if(CharacterInfo[playerid][pWorek])
			return msg_error(playerid,"Posiadasz za³o¿ony knebel/worek - nie mo¿esz pisaæ prywatnych wiadomoœci.");
		if(CharacterInfo[playerid][pBlockNoOOC] && !CharacterInfo[playerid2][pAdmin])
			return msg_error(playerid,"Posiadasz blokadê czatów OOC.");
		if((!CanMove(playerid) || !CanSpeak(playerid)) && !CharacterInfo[playerid2][pAdmin])
			return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
		new string[256];
		if((CharacterInfo[playerid2][pTog] & TOG_TOKEN) && CharacterInfo[playerid2][pAdminDuty] && !CharacterInfo[playerid][pAdmin])
		{
			new key[32];
			new val = random(500);
			
			format(key, sizeof(key), "%s%s%s", dechex(val), dechex(val + val), dechex(val + val + 2));
			
			text[0] = chrtoupper(text[0]);
			
			SetPVarString(playerid,"pKey",key);
			SetPVarInt(playerid,"pPrivTo",playerid2);
			SetPVarString(playerid, "pPrivMess", text);
			
			format(string, sizeof(string), "Administrator bêd¹cy na s³u¿bie wymusi³ przepisanie tokena.\nPrzepisz token administracyjny w pole poni¿ej, aby napisaæ wiadomoœæ.\n\n%s\n\nPamietaj, ¿e wiadomoœæ powinna byæ sensowna i treœciwa.", key);
			ShowPlayerDialog(playerid, D_PRIV_MSG, DIALOG_STYLE_INPUT, DEF_NAME" » token", string, "Wyœlij", "Zamknij");
		}
		else
		{		
			if(strlen(text) < 78)
			{
				if(CharacterInfo[playerid][pAdminDuty])
				{
					switch(CharacterInfo[playerid][pAdmin])
					{
						case 1: 
							format(string, sizeof(string), "(( {FF9900}[Opiekun]{F2DE00} %s(%d) napisa³: %s ))", CharacterInfo[playerid][pGlobalNick], playerid, text);
						case 2,3,4:
							format(string, sizeof(string), "(( {8B00B0}[GameMaster]{F2DE00} %s(%d) napisa³: %s ))", CharacterInfo[playerid][pGlobalNick], playerid, text);
						case 5,6:
							format(string, sizeof(string), "(( {B00000}[Administrator]{F2DE00} %s(%d) napisa³: %s ))", CharacterInfo[playerid][pGlobalNick], playerid, text);					}
				}
				else
					format(string, sizeof(string), "(( %s(%d) napisa³: %s ))", PlayerName2(playerid), playerid, text);
				
				SendClientMessage(playerid2, COLOR_GOT_PW, string);
				playerLog(playerid2,"PW",string);
				
				if(CharacterInfo[playerid2][pAdminDuty])
				{
					switch(CharacterInfo[playerid2][pAdmin])
					{
						case 1: 
							format(string, sizeof(string), "(( Wys³ano do {FF9900}[Opiekun]{00D11F} %s(%d): %s ))", CharacterInfo[playerid2][pGlobalNick], playerid2, text);
						case 2,3,4:
							format(string, sizeof(string), "(( Wys³ano do {8B00B0}[GameMaster]{00D11F} %s(%d): %s ))", CharacterInfo[playerid2][pGlobalNick], playerid2, text);
						case 5,6:
							format(string, sizeof(string), "(( Wys³ano do {B00000}[Administrator]{00D11F} %s(%d): %s ))", CharacterInfo[playerid2][pGlobalNick], playerid2, text);					}
				}
				else
					format(string, sizeof(string), "(( Wys³ano do %s(%d): %s ))", PlayerName2(playerid2), playerid2, text);
					
					
				playerLog(playerid,"PW",string);
				SendClientMessage(playerid, COLOR_SEND_PW, string);
				if(CharacterInfo[playerid2][pStatus] & STATUS_AFK)
					SendClientMessage(playerid, COLOR_SEND_PW, "Wybrany gracz jest aktualnie AFK.");
				
				format(string,sizeof(string),"[PW] %s(%d) >> %s(%d):{FFFFFF} %s", PlayerName2(playerid), playerid, PlayerName2(playerid2), playerid2, text);
				ForeachPlayer(i)
					if(CharacterInfo[i][pAdmin] > 4 && CharacterInfo[i][pMsgspy])
						SendClientMessage(i, COLOR_RED, string);
			}
			else
			{
				new pos = strfind(text, " ", true, strlen(text) / 2);
				if(pos != -1)
				{
					new text2[64];
					
					strmid(text2, text, pos + 1, strlen(text));
					strdel(text, pos, strlen(text));
					
					if(CharacterInfo[playerid][pAdminDuty])
					{
						switch(CharacterInfo[playerid][pAdmin])
						{
							case 1:
								format(string, sizeof(string), "(( {FF9900}[Opiekun]{F2DE00} %s(%d) napisa³: %s ..", CharacterInfo[playerid][pGlobalNick], playerid, text);
							case 2,3,4:
								format(string, sizeof(string), "(( {8B00B0}[GameMaster]{F2DE00} %s(%d) napisa³: %s ..", CharacterInfo[playerid][pGlobalNick], playerid, text);
							case 5,6:
								format(string, sizeof(string), "(( {B00000}[Administrator]{F2DE00} %s(%d) napisa³: %s ..", CharacterInfo[playerid][pGlobalNick], playerid, text);					}
					}
					else
						format(string, sizeof(string), "(( %s(%d) napisa³: %s ..", PlayerName2(playerid), playerid, text);
					
					SendClientMessage(playerid2, COLOR_GOT_PW, string);
					
					SendClientMessageFormat(playerid2, COLOR_GOT_PW, "...%s ))", text2);
					playerLog(playerid2,"PW",string);
					playerLog(playerid2,"PW",text2);
					
					if(CharacterInfo[playerid2][pAdminDuty])
					{
						switch(CharacterInfo[playerid2][pAdmin])
						{
							case 1: 
								format(string, sizeof(string), "(( Wys³ano do {FF9900}[Opiekun]{00D11F} %s(%d): %s ..", CharacterInfo[playerid2][pGlobalNick], playerid2, text);
							case 2,3,4:
								format(string, sizeof(string), "(( Wys³ano do {8B00B0}[GameMaster]{00D11F} %s(%d): %s ..", CharacterInfo[playerid2][pGlobalNick], playerid2, text);
							case 5,6:
								format(string, sizeof(string), "(( Wys³ano do {B00000}[Administrator]{00D11F} %s(%d): %s ..", CharacterInfo[playerid2][pGlobalNick], playerid2, text);					}
					}
					else
						format(string, sizeof(string), "(( Wys³ano do %s(%d): %s ..", PlayerName2(playerid2), playerid2, text);

					SendClientMessage(playerid, COLOR_SEND_PW, string);
					playerLog(playerid,"PW",string);
					playerLog(playerid,"PW",text2);
					SendClientMessageFormat(playerid, COLOR_SEND_PW, "...%s ))", text2);
					if(CharacterInfo[playerid2][pStatus] & STATUS_AFK)
						SendClientMessage(playerid, COLOR_SEND_PW, "Wybrany gracz jest aktualnie AFK.");
					
					new pwtext[96];
					format(string,sizeof(string),"[PW] %s(%d) >> %s(%d):{FFFFFF} %s ...", PlayerName2(playerid), playerid, PlayerName2(playerid2), playerid2, text);
					format(pwtext,sizeof(pwtext),"{ffffff}...%s",text2);
					ForeachPlayer(i)
					{
						if(CharacterInfo[i][pAdmin] > 4 && CharacterInfo[i][pMsgspy])
						{
							SendClientMessage(i, COLOR_RED, string);
							SendClientMessage(i, COLOR_RED, pwtext);
						}
					}
				}
			}
			CharacterInfo[playerid2][pLastW] = playerid;
			CharacterInfo[playerid][pLastW] = playerid2;
			
			if(CharacterInfo[playerid][pTog] & TOG_PW)
			{
				SendClientMessage(playerid, COLOR_GREEN, "[PW] Pamiêtaj, ¿e masz wy³¹czon¹ opcje odbierania wiadomoœci.");
				return 1;
			}
		}
	}
	return 1;
}
CMD:pm(playerid, params[]) return cmd_w(playerid, params);
CMD:pw(playerid, params[]) return cmd_w(playerid, params);

CMD:re(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(CharacterInfo[playerid][pLastW] == INVALID_PLAYER_ID)
		return msg_error(playerid,"Z nikim nie pisa³eœ przez ostatni czas.");
	new text[128], string[128];
	if(sscanf(params, "s[128]", text))
		return msg_usage(playerid,"U¿yj: /re [wiadomoœæ]");
	else
	{
		format(string, sizeof(string), "%d %s", CharacterInfo[playerid][pLastW], text);
		cmd_w(playerid, string);
	}
	return 1;
}

CMD:plac(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new playerid2, cash;
	if(sscanf(params, "id", playerid2, cash))
		return msg_usage(playerid,"U¿yj: /plac [ID gracza] [kwota]");
	else
	{
		if(playerid==playerid2)
			return msg_error(playerid,"Nie mo¿esz przekazaæ pieniêdzy samemu sobie.");
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		if(!PlayerToPlayer(5.0, playerid, playerid2))
			return msg_error(playerid,"Wybrany gracz znajduje siê zbyt daleko Ciebie.");
		if(cash < 1)
			return msg_error(playerid, "Nie mo¿esz przekazaæ takiej kwoty.");
		if(CharacterInfo[playerid][pCash] < cash)
			return msg_error(playerid,"Nie posiadasz takiej iloœci gotówki przy sobie.");
		if(CharacterInfo[playerid][pHours] < 3 && GroupInfo[DutyGroup[playerid2]][gType] != GROUP_KASYNO)
			return msg_error(playerid,"Musisz przegraæ 3 godziny aby móc przekazywaæ gotówkê.");
		new string[128];
		if(cash >= 300)
		{
			format(string,sizeof(string),"[AI] %s(%d) przekaza³  %s(%d) $%d.", PlayerName3(playerid), playerid, PlayerName3(playerid2), playerid2, cash);
			SendAdminMessage(COLOR_RED, string);
		}
		
		GivePlayerCash(playerid, -cash);
		GivePlayerCash(playerid2, cash);
		
		format(string, sizeof(string), "podaje gotówkê do %s.", PlayerName2(playerid2));
		cmd_me(playerid, string);
		
		format(string,sizeof(string),"INSERT INTO `srv_cash_logs` VALUES ('%d','%d','%d','%d','%d',1,'%d')",CharacterInfo[playerid][pUID],CharacterInfo[playerid][pGID],CharacterInfo[playerid2][pUID],CharacterInfo[playerid2][pGID],cash,gettime());
		mysql_query(string);
		
		format(string,sizeof(string),"Przekaza³eœ %s(%d) kwotê $%d.", PlayerName2(playerid2), playerid2, cash);
		SendClientMessage(playerid, COLOR_GREEN, string);
		format(string,sizeof(string),"%s(%d) przekaza³ Ci $%d.", PlayerName2(playerid), playerid, cash);
		SendClientMessage(playerid2, COLOR_GREEN, string);
	}
	
	return 1;
}

CMD:pomoc(playerid, params[])
{		
	ShowPlayerDialog(playerid, D_HELP, DIALOG_STYLE_LIST, DEF_NAME" » centrum pomocy", "Role Play - co to jest?\nJak zarabiaæ?\nPodstawowe komendy\nKontakt z administracj¹", "Wybierz", "Zamknij");
	return 1;
}

CMD:me(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(CharacterInfo[playerid][pBW]) return 1;
	
	if(CharacterInfo[playerid][pAFKWarn])
		CharacterInfo[playerid][pAFKWarn] = 0;
	
	new text[128], string[170];
	if(sscanf(params, "s[128]", text))
		return msg_usage(playerid,"U¿yj: /me [akcja]");
	else
	{
		text[0] = chrtolower(text[0]);
		if(text[strlen(text)-1] != '.')
			strins(text, ".", strlen(text));
		format(string, sizeof(string), "* %s %s", PlayerName2(playerid), text);
		SendWrappedMessageToPlayerRange(playerid, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, string, 10);
	}
	
	return 1;
}
CMD:ja(playerid, params[]) return cmd_me(playerid, params);

CMD:do(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	
	if(CharacterInfo[playerid][pAFKWarn])
		CharacterInfo[playerid][pAFKWarn] = 0;
	
	new text[128], string[170];
	if(sscanf(params, "s[128]", text))
		return msg_usage(playerid,"U¿yj: /do [sytuacja]");
	else
	{
		text[0] = chrtoupper(text[0]);

		format(string, sizeof(string), "* %s (( %s ))", text, PlayerName2(playerid));
		SendWrappedMessageToPlayerRange(playerid, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, string, 10);
	}
	return 1;
}

CMD:report(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new playerid2, report[128];
	if(sscanf(params, "is[128]", playerid2, report))
		return msg_usage(playerid,"U¿yj: /report [ID gracza] [powód]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		
		if((CharacterInfo[playerid][pReport] + 15) > gettime())
			return msg_error(playerid,"Odczekaj 15 sekund przed napisaniem kolejnego zg³oszenia.");
		
		CharacterInfo[playerid][pReport] = gettime();
		if(strlen(report) < 38)
			SendAdminMessageFormat(COLOR_RED, "[RAPORT] {02AD38}%s(%d) {ffffff}zg³osi³ gracza {C90000}%s(%d){ffffff}: %s", PlayerName3(playerid), playerid, PlayerName3(playerid2), playerid2, report);
		else
		{
			new pos = strfind(report, " ", true, 25);
			if(pos != -1)
			{
				new text2[128],string[128];
				
				strmid(text2, report, pos + 1, strlen(report));
				strdel(report, pos, strlen(report));
				
				format(string,sizeof(string),"[RAPORT] {02AD38}%s(%d) {ffffff}zg³osi³ gracza {C90000}%s(%d){ffffff}: %s...", PlayerName3(playerid), playerid, PlayerName3(playerid2), playerid2, report);
				format(text2, sizeof(text2), "{FFFFFF}...%s", text2);
				ForeachPlayer(i)
				{
					if(CharacterInfo[i][pAdmin])
					{
						SendClientMessage(i,COLOR_RED,string);
						SendClientMessage(i,COLOR_RED,text2);
					}
				}
			}
		}
		
		msg_info(playerid,"Zg³oszenie zosta³o pomyœlnie wys³ane.\nOczekuj na administratora.\n\nWa¿ne zasady:\n\t1. Pamiêtaj o zachowaniu kultury wobec administratora.\n\t2. Inni gracze te¿ potrzebuj¹ pomocy - oczekuj w spokoju.\n\t3. Wysy³anie ci¹g³ych zg³oszeñ nie przyœpieszy czasu realizacji.");
	}
	return 1;
}
CMD:raport(playerid, params[]) return cmd_report(playerid, params);

CMD:sprobuj(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(CharacterInfo[playerid][pBW] || CharacterInfo[playerid][pWounded]) return 1;
	new text[128], string[128];
	if(sscanf(params, "s[128]", text))
		return msg_usage(playerid,"U¿yj: /spróbuj [akcja np. podnieœæ ciê¿arek]");
	new loss = random(2);
	switch(loss)
	{
		case 0:
		{
			if(CharacterInfo[playerid][pSex])
			{
				format(string, sizeof(string), "{E8B200}zawiód³{C2A2DA} próbuj¹c %s", text);
				cmd_me(playerid, string);
			}
			else
			{
				format(string, sizeof(string), "{E8B200}zawiod³a{C2A2DA} próbuj¹c %s", text);
				cmd_me(playerid, string);
			}
		}
		case 1:
		{
			if(CharacterInfo[playerid][pSex])
			{
				format(string, sizeof(string), "{E8B200}odniós³ sukces{C2A2DA} próbuj¹c %s", text);
				cmd_me(playerid, string);
			}
			else
			{
				format(string, sizeof(string), "{E8B200}odnios³a sukces{C2A2DA} próbuj¹c %s", text);
				cmd_me(playerid, string);
			}
		}
	}
	return 1;
}

CMD:stats(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new playerid2;
	if(sscanf(params, "i", playerid2))
		ShowPlayerStats(playerid, playerid);
	else
	{
		if(!CharacterInfo[playerid][pAdmin]) return 1;
		else if(!IsPlayerConnected(playerid2) || !Logged[playerid2]) return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		else
			ShowPlayerStats(playerid, playerid2);
	}
	
	return 1;
}

CMD:pytanie(playerid,params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new text[128];
	if(sscanf(params, "s[128]", text))
		return msg_usage(playerid,"U¿yj: /pytanie [treœæ]");
	if((CharacterInfo[playerid][pPytanie] + 15) > gettime())
		return msg_error(playerid,"Pytanie mozesz wysy³aæ raz na 15 sekund!");
	else
	{
		if(strlen(text) < 78)
			SendAdminMessageFormat(COLOR_BLUE, "[PYT] {CC0000}%s[%d]:{ffffff} %s", PlayerName3(playerid),playerid, text);
		else
		{
			new pos = strfind(text, " ", true, strlen(text) / 2);
			if(pos != -1)
			{
				new text2[64];
				
				strmid(text2, text, pos + 1, strlen(text));
				strdel(text, pos, strlen(text));
				
				SendAdminMessageFormat(COLOR_BLUE, "[PYT] {CC0000}%s[%d]:{ffffff} %s", PlayerName3(playerid),playerid, text);
				
				SendAdminMessageFormat(COLOR_WHITE, "...%s", text2);
			}
		}
		msg_info(playerid, "Pytanie zosta³o pomyœlnie wys³ane!");
		CharacterInfo[playerid][pPytanie] = gettime();
	}
	return 1;
}

CMD:id(playerid,cmdtext[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new string[32];
	if(sscanf(cmdtext, "s[32]", string))
		return msg_usage(playerid,"U¿yj: /id [id/nazwa gracza]");
	new find = 0;
	SendClientMessage(playerid, COLOR_GREEN, "Znalezione osoby:");
	ForeachPlayer(i)
	{
		if(isNumeric(string))
		{
			new id = strval(string);
			if(CharacterInfo[id][pUID] == 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "Brak wyników.");
				return 1;
			}
			SendClientMessageFormat(playerid, COLOR_GREY, "[ID: %d] %s", id, PlayerName(id));
			return 1;
		}
		else
		{
			if(strfind(PlayerName(i), string, true) >= 0)
			{
				SendClientMessageFormat(playerid, COLOR_GREY, "[ID: %d] %s", i, PlayerName(i));
				find++;
			}
		}
	}
	if(find == 0)
		SendClientMessage(playerid, COLOR_GREY, "Brak wyników.");
	return 1;
}

CMD:tog(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new string[1024];
	
	if(CharacterInfo[playerid][pTog] & TOG_PW) format(string, sizeof(string), "%s\nBlokada wiadomoœci\t\t{99FF00}T", string);
	else format(string, sizeof(string), "%s\nBlokada wiadomoœci\t\t{990000}N", string);
		
	if(!(CharacterInfo[playerid][pTog] & TOG_NAME)) format(string, sizeof(string), "%s\nTextdraw serwera\t\t{99FF00}T", string);
	else format(string, sizeof(string), "%s\nTextdraw Serwera\t\t{990000}N", string);
	
	if(!(CharacterInfo[playerid][pTog] & TOG_GLOD)) format(string, sizeof(string), "%s\nPasek g³odu\t\t\t{99FF00}T", string);
	else format(string, sizeof(string), "%s\nPasek g³odu\t\t\t{990000}N", string);
	
	if(!(CharacterInfo[playerid][pTog] & TOG_LSN)) format(string, sizeof(string), "%s\nTextdraw LSN\t\t\t{99FF00}T", string);
	else format(string, sizeof(string), "%s\nTextdraw LSN\t\t\t{990000}N", string);
	
	if(!(CharacterInfo[playerid][pTog] & TOG_SAY)) format(string, sizeof(string), "%s\nAnimacja mowy\t\t\t{99FF00}T", string);
	else format(string, sizeof(string), "%s\nAnimacja mowy\t\t\t{990000}N", string);
	
	if(!(CharacterInfo[playerid][pTog] & TOG_KRZYK)) format(string, sizeof(string), "%s\nAnimacja krzyku\t\t{99FF00}T", string);
	else format(string, sizeof(string), "%s\nAnimacja krzyku\t\t{990000}N", string);

	if(!(CharacterInfo[playerid][pTog] & TOG_SPEEDOMETER)) format(string, sizeof(string), "%s\nLicznik w pojazdach\t\t{99FF00}T", string);
	else format(string, sizeof(string), "%s\nLicznik w pojazdach\t\t{990000}N", string);
	
	if(!(CharacterInfo[playerid][pTog] & TOG_FREEZE)) format(string, sizeof(string), "%s\nFreeze w drzwiach\t\t{99FF00}T", string);
	else format(string, sizeof(string), "%s\nFreeze w drzwiach\t\t{990000}N", string);
	
	if(!(CharacterInfo[playerid][pTog] & TOG_KIERUNKI)) format(string, sizeof(string), "%s\nKierunkowskazy\t\t{99FF00}T", string);
	else format(string, sizeof(string), "%s\nKierunkowskazy\t\t{990000}N", string);
	
	if(!(CharacterInfo[playerid][pTog] & TOG_SMIECH)) format(string, sizeof(string), "%s\nAnimacja œmiechu\t\t{99FF00}T", string);
	else format(string, sizeof(string), "%s\nAnimacja œmiechu\t\t{990000}N", string);
	
	if(!(CharacterInfo[playerid][pTog] & TOG_CHATOOC)) format(string, sizeof(string), "%s\nCzat OOC (/b)\t\t\t{99FF00}T", string);
	else format(string, sizeof(string), "%s\nCzat OOC (/b)\t\t\t{990000}N", string);

	if(!(CharacterInfo[playerid][pTog] & TOG_GUN_CARRY)) format(string, sizeof(string), "%s\nStyl noszenia broni\t\tPlecy", string);
	else format(string, sizeof(string), "%s\nStyl noszenia broni\t\tKlatka", string);
	
	if(!(CharacterInfo[playerid][pTog] & TOG_STATUS)) format(string, sizeof(string), "%s\nTextdraw Statusów\t\t{990000}N", string);
	else format(string, sizeof(string), "%s\nTextdraw Statusów\t\t{99FF00}T", string);
	
	if(CharacterInfo[playerid][pAdmin])
	{
		if(CharacterInfo[playerid][pTog] & TOG_TOKEN) format(string, sizeof(string), "%s\nToken administracyjny\t\t{99FF00}T", string);
		else format(string, sizeof(string), "%s\nToken administracyjny\t\t{990000}N", string);
	}
	
	ShowPlayerDialog(playerid, D_TOG, DIALOG_STYLE_LIST, DEF_NAME" » ustawienia", string, "Wybierz", "Zamknij");
	return 1;
}

CMD:przedmiot(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new comm1[16];
	
	if(sscanf(params, "s[16]", comm1))
	{
		SendClientMessage(playerid, COLOR_GREY, "U¿yj: /p(rzedmiot) [szukaj]");
		ListPlayerItemsForPlayer(playerid, playerid);
	}
	else if(!strcmp(comm1, "szukaj", true) || (!strcmp(comm1,"podnies",true)) || (!strcmp(comm1,"podnieœ",true)))
	{ 
		if(!CanMove(playerid))
			return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
		
		if(!GetPlayerVehicleID(playerid))
			ApplyAnimation(playerid, "PED", "XPRESSscratch", 4.1, 0, 0, 0, 0, 3000, 1);
			
		Tip(playerid, 3, "Rozgladasz sie po okolicy w poszukiwaniu przedmiotow.");
		
		SetTimerEx("ListNearItems", 3000, false, "i", playerid);
	}
	else if(strlen(params) >= 2)
	{
		ForeachEx(i,_ITEM_COUNT)
		{
			if(ItemInfo[i][iOwnerTyp]==OWNER_PLAYER && ItemInfo[i][iOwner]==CharacterInfo[playerid][pUID] && strfind(ItemInfo[i][iName], params, true)  != -1)
			{
				OnPlayerUseItem(playerid, i);
				break;
			}
		}
	}
	
	return 1;
}
CMD:p(playerid, params[]) return cmd_przedmiot(playerid, params);

CMD:admins(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new list[2048];
	
	format(list, sizeof(list), "Je¿eli chcesz skontaktowaæ siê z administracj¹ mo¿esz skorzystaæ z /pytanie lub napisaæ prywatn¹ wiadomoœæ do cz³onka ekipy.\n\nCz³onkowie ekipy online:\n{FFFFFF}");
	
	ForeachPlayer(i)
	{
		if(CharacterInfo[i][pAdmin] && CharacterInfo[i][pAdminDuty])
		{
			switch(CharacterInfo[i][pAdmin])
			{
				case 1: format(list, sizeof(list), "%s\n{FF9900}Opiekun{FFFFFF}\t\t%s (ID: %d)", list, CharacterInfo[i][pGlobalNick],i);
				case 2,3,4: format(list, sizeof(list), "%s\n{800080}GameMaster{FFFFFF}\t\t%s (ID: %d)", list, CharacterInfo[i][pGlobalNick],i);
				case 5: format(list, sizeof(list), "%s\n{d80000}Administrator{FFFFFF}\t\t%s (ID: %d)", list, CharacterInfo[i][pGlobalNick],i);
				case 6: format(list, sizeof(list), "%s\n{ED0000}Administrator G³ówny{FFFFFF}\t%s (ID: %d)", list, CharacterInfo[i][pGlobalNick],i);
			}
		}
	}
	
	if(strlen(list) > 160) ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » lista administratorów", list, "Zamknij", "");
	else msg_info(playerid, "Brak administratorów online.");
	return 1;
}

CMD:kostka(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!PlayerHaveItemType(playerid, ITEM_TYPE_KOSTKA))
		return msg_error(playerid,"Nie posiadasz przy sobie kostki.");
	
	new rzut[128];
	format(rzut,sizeof(rzut),"rzuca kostk¹ i otrzymuje {E8B200}%d{C2A2DA} oczek.", random(6)+1);
	cmd_me(playerid,rzut);
	
	return 1;
}

CMD:karty(playerid, params[])
{
	if(!PlayerHaveItemType(playerid, ITEM_TYPE_KARTY))
		return msg_error(playerid,"Nie posiadasz przy sobie kart do gry.");
	new suit[32], rank[32], cardstring[64];
	switch(random(13))
	{
		case 0:
			rank="dwójka";
		case 1:
			rank="trójka";
		case 2:
			rank="czwórka";
		case 3:
			rank="pi¹tka";
		case 4:
			rank="szóstka";
		case 5:
			rank="siódemka";
		case 6:
			rank="ósemka";
		case 7:
			rank="dziewi¹tka";
		case 8:
			rank="dziesi¹tka"
		;case 9:
			rank="walet";
		case 10:
			rank="dama";
		case 11:
			rank="król";
		case 12:
			rank="as";
	}
	switch(random(4))
	{
		case 0:
			suit="trefl";
		case 1:
			suit="karo";
		case 2:
			suit="kier";
		case 3:
			suit="pik";
	}
	format(cardstring, sizeof(cardstring), "losuje z talii kartê {F2C200}%s %s.", rank, suit);
	cmd_me(playerid, cardstring);
	return 1;
}

CMD:maska(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid, "Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	
	new list[2048];
	
	format(list, sizeof(list), "UID\tNazwa\tWartoœæ 1\tWartoœæ 2");
	
	ForeachEx(i, _ITEM_COUNT)
	{
		if(ItemInfo[i][iUID])
		{
			if(ItemInfo[i][iOwnerTyp] == OWNER_PLAYER && ItemInfo[i][iOwner] == CharacterInfo[playerid][pUID] && ItemInfo[i][iType] == ITEM_TYPE_MASKA)
			{
				if(ItemInfo[i][iUsed]) format(list, sizeof(list), "%s\n%d\t{164713}%s\t%d\t%d", list, ItemInfo[i][iUID], ItemInfo[i][iName], ItemInfo[i][iValue1], ItemInfo[i][iValue2]);
				else format(list, sizeof(list), "%s\n%d\t{878A87}%s\t%d\t%d", list, ItemInfo[i][iUID], ItemInfo[i][iName], ItemInfo[i][iValue1], ItemInfo[i][iValue2]);
			}
		}
	}
	
	if(strlen(list) > 40) ShowPlayerDialog(playerid, D_ITEM, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » lista przedmiotów", list, "Opcje", "Zamknij");
	else Tip(playerid, 3, "Nie posiadasz maski.");
	
	return 1;
}

CMD:pojazd(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!CanMove(playerid))
		return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
	new comm1[32];
	if(sscanf(params, "s[32]", comm1))
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new vehid = GetPlayerVehicleID(playerid);
			new vehuid = GetVehicleUID(vehid);

			new bool:hasBonnets, bool:hasDoors;
			if(!IsABike(vehid, 1)) 
				hasBonnets=true;

			new title[64], string[512];
			
			format(title, sizeof(title), "Zarz¹dzanie pojazdem - sampID: %d, UID: %d", vehid, vehuid);
			
			if(hasBonnets)
			{
				if(GetVehicleBonnetStatus(vehid) != 1) 
					format(string,sizeof(string), "{FFFFFF}Status maski:\t\t\t{C90000}Zamkniêta");
				else 
					format(string,sizeof(string), "{FFFFFF}Status maski:\t\t\t{33AA33}Otwarta");
			
				if(GetVehicleBootStatus(vehid) != 1) 
					format(string, sizeof(string), "%s\n{FFFFFF}Status baga¿nika:\t\t{C90000}Zamkniêty",string);
				else 
					format(string, sizeof(string), "%s\n{FFFFFF}Status baga¿nika:\t\t{33AA33}Otwarty",string);
			}
			else
			{
				format(string,sizeof(string), "{FFFFFF}Status maski:\t\t\t{C3C3C3}-");
				format(string, sizeof(string), "%s\n{FFFFFF}Status baga¿nika:\t\t{C3C3C3}-",string);
			}
			
			if(GetVehicleLightsStatus(vehid) != 1) 
				format(string,sizeof(string), "%s\n{FFFFFF}Status œwiate³:\t\t\t{C90000}Wy³¹czone",string);
			else 
				format(string,sizeof(string), "%s\n{FFFFFF}Status œwiate³:\t\t\t{33AA33}W³¹czone",string);
			
			if(hasDoors)
			{
				if(VehicleInfo[vehuid][vLocked]) 
					format(string, sizeof(string), "%s\n{FFFFFF}Status drzwi:\t\t\t{C90000}Zamkniête",string);
				else 
					format(string, sizeof(string), "%s\n{FFFFFF}Status drzwi:\t\t\t{33AA33}Otwarte",string);
			}
			else
				format(string, sizeof(string), "%s\n{FFFFFF}Status drzwi:\t\t\t{C3C3C3}-",string);

			format(string,sizeof(string),"%s\n{6B6969}1. Informacje o pojeŸdzie\n{6B6969}2. Przedmioty w pojeŸdzie\n{6B6969}3. Tuning pojazdu\n{6B6969}4. Opis pojazdu\n{6B6969}5. Wyrób kluczyki do pojazdu ($2.500)\n{6B6969}6. Przepisz pojazd pod grupê",string);
			
			if(hasModelEngine(VehicleInfo[vehuid][vModel]))
			{
				format(string,sizeof(string),"%s\n{6B6969}7. Radio",string);
				if(IsPlayerPremium(playerid) && hasBonnets)
					format(string, sizeof(string), "%s\n{6B6969}8. Zmieñ rejestracje samochodu (PREMIUM)", string);
			}
			
			ShowPlayerDialog(playerid, D_VEH_MEN, DIALOG_STYLE_LIST, title, string, "Dalej", "Zamknij");
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "U¿yj: /pojazd [info | zaparkuj | zamknij | opis]");
			ListVehiclesForPlayer(playerid);
		}
	}
	else
	{
		if(!strcmp(comm1, "zaparkuj", true))
		{
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			{
				new vehid = GetPlayerVehicleID(playerid);
				new uid = GetVehicleUID(vehid);
				if(!CanPlayerManageVehicle(playerid,uid))
					return msg_error(playerid,"Nie posiadasz uprawnieñ do zarz¹dzania tym pojazdem.");
				if(VehicleInfo[uid][vEngine] && hasModelEngine(VehicleInfo[uid][vModel]))
					return msg_error(playerid,"Najpierw wy³¹cz silnik.");
			
				GetVehiclePos(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vposx], VehicleInfo[uid][vposy], VehicleInfo[uid][vposz]);
				VehicleInfo[uid][vVW] = GetVehicleVirtualWorld(VehicleInfo[uid][vSAMPID]);
				VehicleInfo[uid][vInt] = GetPlayerInterior(playerid);
				GetVehicleZAngle(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vAngle]);
				
				SaveVehicle(uid, SAVE_VEH_POS);
				
				UnspawnVehicle(uid);
				
				LoadVehicle(uid);
				
				PutPlayerInVehicle(playerid, VehicleInfo[uid][vSAMPID], 0);
				
				msg_infoFormat(playerid, 80, "Zaparkowa³eœ pojazd %s [UID: %d.]",GetVehicleModelName(VehicleInfo[uid][vModel]), uid);
			}
			else msg_error(playerid,"Musisz byæ kierowc¹ aby móc u¿yæ tej komendy.");
		}
		else if(!strcmp(comm1, "zamknij", true) || (!strcmp(comm1, "z", true)))
			cmd_kluczyk(playerid, "");
		else if(!strcmp(comm1, "l", true) || (!strcmp(comm1, "swiatla", true)))
		{
			new vehid = GetPlayerVehicleID(playerid);
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
				ChangeVehicleLightsStatus(vehid, !GetVehicleLightsStatus(vehid));
		}
		else if(!strcmp(comm1, "m", true) || !strcmp(comm1, "maska", true))
		{
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			{
				new uid = GetVehicleUID( GetPlayerVehicleID(playerid));
				if(IsABike(VehicleInfo[uid][vSAMPID]) || IsABoat(VehicleInfo[uid][vSAMPID]) || IsAPlane(VehicleInfo[uid][vSAMPID]))
					return 1;
				if(GetVehicleBonnetStatus(VehicleInfo[uid][vSAMPID]) != 1)
				{
					ChangeVehicleBonnetStatus(VehicleInfo[uid][vSAMPID], true);
					cmd_me(playerid, "otwiera maskê w pojeŸdzie.");
				}
				else
				{
					ChangeVehicleBonnetStatus(VehicleInfo[uid][vSAMPID], false);
					cmd_me(playerid, "zamyka maskê w pojeŸdzie.");
				}
			}
			else
			{
				if(DutyGroup[playerid] && GroupInfo[DutyGroup[playerid]][gType] == GROUP_WORKSHOP)
				{
					if(PlayerDoor[playerid] && DoorsInfo[PlayerDoor[playerid]][dOwnerTyp] == OWNER_GROUP && DoorsInfo[PlayerDoor[playerid]][dOwner] == DutyGroup[playerid])
					{
						new vehid = GetClosestVehicle(playerid);
						new vehuid = GetVehicleUID(vehid);
						
						if(CharacterInfo[playerid][pRepairVeh] == vehuid && CharacterInfo[playerid][pRepairTime] > 0)
						{
							if(GetVehicleBonnetStatus(VehicleInfo[vehuid][vSAMPID]) != 1)
							{
								ChangeVehicleBonnetStatus(VehicleInfo[vehuid][vSAMPID], true);
								cmd_me(playerid, "otwiera maskê w pojeŸdzie.");
							}
							else
							{
								ChangeVehicleBonnetStatus(VehicleInfo[vehuid][vSAMPID], false);
								cmd_me(playerid, "zamyka maskê w pojeŸdzie.");
							}
						}
					}
				}
			}
		}
		else if(!strcmp(comm1, "b", true) || !strcmp(comm1, "bagaznik", true))
		{
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			{
				new uid = GetVehicleUID(GetPlayerVehicleID(playerid));
				if(IsABike(VehicleInfo[uid][vSAMPID]) || IsABoat(VehicleInfo[uid][vSAMPID]) || IsAPlane(VehicleInfo[uid][vSAMPID]))
					return 1;
				
				if(GetVehicleBootStatus(VehicleInfo[uid][vSAMPID]) != 1)
				{
					ChangeVehicleBootStatus(VehicleInfo[uid][vSAMPID], true);
					cmd_me(playerid, "otwiera baga¿nik w pojeŸdzie.");
				}
				else
				{
					ChangeVehicleBootStatus(VehicleInfo[uid][vSAMPID], false);
					cmd_me(playerid, "zamyka baga¿nik w pojeŸdzie.");
				}
			}
		}
		else if(!strcmp(comm1, "radio", true))
		{
			if(!GetPlayerVehicleID(playerid)) return 1;
			if(!IsABike(GetPlayerVehicleID(playerid)))
			{
				new stations[512];
				ForeachEx(i,sizeof(RadioStations))
				{
					format(stations, sizeof(stations), "%s%s\n", stations,RadioStations[i][radioName]);
				}
				format(stations, sizeof(stations), "%sW³asny link\n{B30009}Wy³¹cz radio",stations);
				ShowPlayerDialog(playerid,D_VEH_RADIO,DIALOG_STYLE_LIST,DEF_NAME" » radio",stations,"Wybierz","Anuluj");
			}
			else
				msg_error(playerid,"W tym pojeŸdzie nie mo¿na u¿ywaæ radia");
		}
		else if(!strcmp(comm1, "opis", true) )
		{
			if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER || !GetPlayerVehicleID(playerid))
				return msg_error(playerid,"Musisz byæ kierowc¹ aby móc u¿yæ tej komendy.");
			new vehid=GetVehicleUID(GetPlayerVehicleID(playerid));
			if(!CanPlayerManageVehicle(playerid,vehid))
				return msg_error(playerid,"Nie posiadasz uprawnieñ do zarz¹dzania tym pojazdem.");

			if(strlen(VehicleInfo[vehid][vDesc]) > 1)
				ShowPlayerDialog(playerid,D_VEH_DESC,DIALOG_STYLE_LIST,DEF_NAME" » opis pojazdu","Ustaw nowy opis\nUsuñ aktualny opis","Wybierz","WyjdŸ");
			else
				ShowPlayerDialog(playerid, D_VEH_DESC_ADD, DIALOG_STYLE_INPUT, DEF_NAME" » opis pojazdu", "WprowadŸ opis pojazdu:", "Ustaw", "WyjdŸ");
		}
		else if(!strcmp(comm1, "kogut", true) )
		{
			new vehid=GetVehicleUID(GetPlayerVehicleID(playerid));
			if(!vehid || GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
				return 1; 
			if(VehicleInfo[vehid][vPolice])
			{
				DestroyDynamicObject(VehicleInfo[vehid][vPolice]);
				VehicleInfo[vehid][vPolice]=0;
				return 1;
			}
			if(VehicleInfo[vehid][vModel]==525)
			{
				VehicleInfo[vehid][vPolice]=CreateDynamicObject(19803, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
				AttachDynamicObjectToVehicle(VehicleInfo[vehid][vPolice], VehicleInfo[vehid][vSAMPID],0.0,0.0,0.0, 0.0, 0.0, 0.0);
				return 1;
			}
			if((VehicleInfo[vehid][vOwnerTyp]!=OWNER_GROUP) || !IsOwnerVehicle(playerid,vehid)) 
				return msg_error(playerid,"Ten pojazd nie posiada koguta.");
			new gid=VehicleInfo[vehid][vOwner];
			if(GroupInfo[gid][gType] != GROUP_PD && GroupInfo[gid][gType] != GROUP_MC && GroupInfo[gid][gType] != GROUP_FBI && GroupInfo[gid][gType] != GROUP_MILITARY)
				return msg_error(playerid,"Ten pojazd nie posiada koguta.");
			new syrenaid=Siren(vehid);
			if(!syrenaid)
				return msg_error(playerid,"W tym pojeŸdzie nie mo¿na u¿ywaæ koguta.");
			if(!VehicleInfo[vehid][vPolice])
			{
				VehicleInfo[vehid][vPolice]=CreateDynamicObject(SyrenaPos[syrenaid][sObject], 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
				AttachDynamicObjectToVehicle(VehicleInfo[vehid][vPolice], VehicleInfo[vehid][vSAMPID],SyrenaPos[syrenaid][sX], SyrenaPos[syrenaid][sY], SyrenaPos[syrenaid][sZ], 0.0, 0.0, 0.0);
				GameTextForPlayer(playerid, "~w~Kogut ~g~wyjety", 3000, 4);
			}
		}
		else if(!strcmp(comm1, "uid", true) || !strcmp(comm1, "id", true))
		{
			new vehid = GetClosestVehicle(playerid);
			
			if(!vehid) return 1;
			
			new vehuid = GetVehicleUID(vehid);
			
			SendClientMessageFormat(playerid, COLOR_GREEN, "[INFO] UID: %d, ID: %d, MODEL: %s.", vehuid, vehid, GetVehicleModelName(VehicleInfo[vehuid][vModel]));
		}
	}
	return 1;
}
CMD:v(playerid, params[]) return cmd_pojazd(playerid, params);
CMD:kogut(playerid,params[]) return cmd_pojazd(playerid,"kogut");

CMD:silnik(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!CanMove(playerid))
		return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		return 1;
	
	new vehid = GetPlayerVehicleID(playerid);
	new vehuid = GetVehicleUID(vehid);
	
	if(!IsOwnerVehicle(playerid, vehuid) && hasModelEngine(VehicleInfo[vehuid][vModel]))
		return msg_error(playerid, "Nie posiadasz kluczyków do tego pojazdu.");
	
	new string[128];
	
	if(VehicleInfo[vehuid][vHP] <= 300)
		return msg_info(playerid, "Pojazd jest uszkodzony, nie mo¿esz odpaliæ silnika.");
	
	if(VehicleInfo[vehuid][vFuel] <= 0 && hasModelEngine(VehicleInfo[vehuid][vModel]))
		return msg_info(playerid, "W pojeŸdzie nie ma benzyny.");
	
	if(VehicleInfo[vehuid][vHandBrake])
		return msg_error(playerid, "Masz zaci¹gniêty rêczny, aby uruchomiæ silnik u¿yj wpierw /reczny!");
	
	if(!hasModelEngine(VehicleInfo[vehuid][vModel]))
	{
		VehicleInfo[vehuid][vEngine] = true;
		ChangeVehicleEngineStatus(vehid, VehicleInfo[vehuid][vEngine]);
		return msg_error(playerid, "Twój pojazd nie ma silnika.");
	}
	else if(CharacterInfo[playerid][pEngineTime] <= gettime())
	{
		if(VehicleInfo[vehuid][vEngine])
		{
			VehicleInfo[vehuid][vEngine] = false;
			
			ChangeVehicleEngineStatus(vehid, VehicleInfo[vehuid][vEngine]);
			
			format(string, sizeof(string), "gasi silnik w pojezdzie %s.", GetVehicleModelName(VehicleInfo[vehuid][vModel]));
			cmd_me(playerid, string);
		}
		else
		{
			if(GetPVarInt(playerid, "pRepairMechanic") && VehicleInfo[vehuid][vUID] == GetPVarInt(playerid, "pRepairCarID"))
				return msg_error(playerid,"Nie mo¿esz odpalaæ silnika podczas prac przy pojeŸdzie.");
			
			Tip(playerid, 3, "Probujesz odpalic silnik w pojezdzie.");
			
			SetTimerEx("EngineStart", 1000, false, "i", playerid);
			
			CharacterInfo[playerid][pEngineTime] = gettime()+1;
		}
	}
	return 1;
}

CMD:kluczyk(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid, "Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!CanMove(playerid))
		return msg_error(playerid, "Nie mo¿esz aktualnie u¿yæ tej komendy.");
	
	new vehid = GetClosestVehicle(playerid);
	
	if(!vehid || vehid == INVALID_VEHICLE_ID) return 1;
	new vehuid = GetVehicleUID(vehid);
	new string[64];
	
	
	if(!IsOwnerVehicle(playerid, vehuid))
		return msg_error(playerid,"Nie posiadasz kluczyków do tego pojazdu.");
	
	if(VehicleInfo[vehuid][vLocked])
	{
		ApplyAnimation(playerid,"INT_HOUSE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
		PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
		
		format(string, sizeof(string), "Otwierasz pojazd %s.", GetVehicleModelName(VehicleInfo[vehuid][vModel]));
		Tip(playerid, 3, string);
		
		VehicleInfo[vehuid][vLocked] = false;
		SetVehicleLock(vehid, false);
	}
	else
	{
		ApplyAnimation(playerid,"INT_HOUSE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
		PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
		
		format(string, sizeof(string), "Zamykasz pojazd %s.", GetVehicleModelName(VehicleInfo[vehuid][vModel]));
		Tip(playerid, 3, string);
		
		VehicleInfo[vehuid][vLocked] = true;
		SetVehicleLock(vehid, true);
		VehicleInfo[vehuid][vRecentlyLocked] = true;
		SetTimerEx("RecentlyLocked", 5000, false, "i", vehuid);
	}
	
	return 1;
}

CMD:zegarek(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid, "Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!PlayerHaveItemType(playerid, ITEM_TYPE_ZEGAREK))
		return msg_error(playerid, "Nie posiadasz zegarka.");
	
	new hours, minutes;
	gettime(hours, minutes);
	
	cmd_me(playerid, "spogl¹da na zegarek.");
	
	new string[16];
	format(string,sizeof(string),"~w~%02d~r~:~w~%02d",hours,minutes);
	GameTextForPlayer(playerid, string, 5000, 1);

	return 1;
}

CMD:telefon(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new title[64];

	if(!PlayerHaveItemType(playerid, ITEM_TYPE_TELEFON))
		return msg_error(playerid,"Nie posiadasz telefonu.");
	else if(!CharacterInfo[playerid][pPhone])
		return msg_error(playerid,"Nie posiadasz w³¹czonego telefonu.\nZrób to u¿ywaj¹c telefon poprzez komendê /p.");
	
	format(title, sizeof(title), DEF_NAME" » telefon [numer: %d]", ItemInfo[CharacterInfo[playerid][pPhone]][iValue1]);
	
	new string[256];
	
	if(CharacterInfo[playerid][pTog] & TOG_TELSOUND)
		format(string, sizeof(string), "1. Zadzwoñ\n2. Wyœlij SMS\n3. Kontakty\n4. Dodaj kontakt\n5. S³uchaj muzyki\n{990000}6. Wycisz telefon/w³¹cz dŸwiêk");
	else
		format(string, sizeof(string), "1. Zadzwoñ\n2. Wyœlij SMS\n3. Kontakty\n4. Dodaj kontakt\n5. S³uchaj muzyki\n{99FF00}6. Wycisz telefon/w³¹cz dŸwiêk");
	
	ShowPlayerDialog(playerid, D_PHONE, DIALOG_STYLE_LIST, title, string, "Wybierz", "Zamknij");
	
	return 1;
}
CMD:tel(playerid,params[]) return cmd_telefon(playerid,params);
CMD:t(playerid,params[]) return cmd_telefon(playerid,params);

CMD:sms(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	else if(CharacterInfo[playerid][pAJ])
		return msg_error(playerid,"W czasie kary Admin Jail nie mo¿esz u¿ywaæ telefonu.");
	if(!CanMove(playerid))
		return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
	
	if(!PlayerHaveItemType(playerid, ITEM_TYPE_TELEFON))
		return msg_error(playerid,"Nie posiadasz przy sobie telefonu.");
	else if(!CharacterInfo[playerid][pPhone])
		return msg_error(playerid,"Nie posiadasz w³¹czonego telefonu.\nZrób to u¿ywaj¹c telefon poprzez komendê /p.");

	new numer, text[128];
	
	if(sscanf(params, "ds[128]", numer, text))
		return msg_usage(playerid,"U¿yj: /sms [numer telefonu] [wiadomoœæ]");
	else
	{
		new playerid2 = GetPhoneID(numer);
		
		if(playerid2 < 0 || !Logged[playerid2])
			return msg_error(playerid,"Wybrany abonent jest poza zasiêgiem.");
		else if(!CharacterInfo[playerid2][pPhone])
			return msg_error(playerid,"Wybrany abonent jest poza zasiêgiem.");
		else if(playerid == playerid2)
			return msg_error(playerid,"Nie jesteœ w stanie wysy³aæ wiadomoœci do samego siebie.");
		
		cmd_me(playerid, "wyci¹ga telefon i wysy³a SMS.");
		
		if(CharacterInfo[playerid2][pTog] & TOG_TELSOUND)
			cmd_do(playerid2, "Telefon wibruje.");
		else
			cmd_do(playerid2, "S³ychaæ dŸwiêk przychodz¹cego SMS.");
		
		SendClientMessageFormat(playerid, COLOR_ORANGE, "[SMS] %d » %s", numer, text);
		SendClientMessageFormat(playerid2, COLOR_ORANGE, "[SMS] %d « %s", ItemInfo[CharacterInfo[playerid][pPhone]][iValue1], text);
	}
	
	return 1;
}

CMD:dzwon(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!CanMove(playerid) || !CanSpeak(playerid))
		return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
	if(!PlayerHaveItemType(playerid, ITEM_TYPE_TELEFON))
		return msg_error(playerid,"Nie posiadasz przy sobie telefonu.");
	else if(!CharacterInfo[playerid][pPhone])
		return msg_error(playerid,"Nie posiadasz w³¹czonego telefonu.\nZrób to u¿ywaj¹c telefon poprzez komendê /p.");
	
	new numer;
	if(sscanf(params, "d", numer))
		return msg_usage(playerid,"U¿yj: /dzwoñ [numer telefonu]");
	if(numer==555)
	{
		new doorid=PlayerDoor[playerid];
		if(DoorsInfo[doorid][dOwnerTyp] != OWNER_GROUP)
			return msg_error(playerid,"Nie znajdujesz siê w ¿adnych drzwiach grupowych.");
		if(DoorsInfo[doorid][dEnterVW] != 0)
			return msg_error(playerid,"Drzwi musz¹ byæ drzwiami wejœciowymi do budynku.");
		if(!IsPlayerPermInGroup(playerid, DoorsInfo[doorid][dOwner], PERM_PRODUCT))
			return msg_error(playerid,"Nie posiadasz uprawnieñ do zamawiania produktów.");

		new string[512];
		switch(GroupInfo[DoorsInfo[doorid][dOwner]][gType])
		{
			case GROUP_PD,GROUP_MILITARY,GROUP_FBI:
				format(string,sizeof(string),"Uzbrojenie\nAmunicja\nPozosta³e");
			case GROUP_WORKSHOP:
				format(string,sizeof(string),"Felgi\nHydraulika & przyciemniane szyby\nSultan\nJester\nElegy\nFlash\nWydechy\nSpoilery\nSavanna\nBlade\nStratum\nUranus\nSlamvan\nRemington\nTornado\nBroadway");
			case GROUP_SECURITY:
				format(string,sizeof(string),"Uzbrojenie\nPozosta³e");
			case GROUP_RESTAURANT:
				format(string,sizeof(string),"Jedzenie\nNapoje\nPapierosy");
			default:
				format(string,sizeof(string),"Podstawowe");
		}

		ShowPlayerDialog(playerid, D_ORDER_PRODUCT_CATEGORY, DIALOG_STYLE_LIST, DEF_NAME" » typ przedmiotu", string, "Wybierz", "WyjdŸ");

		SetPVarInt(playerid, "ProductDoor", doorid);
	}
	else if(numer==911)
	{
		new string[256];
		ForeachEx(i, MAX_GROUPS)
		{
			if(GroupInfo[i][gFlags] & FLAG_911)
				format(string,sizeof(string),"%s\n{c8c8c8}%2d: {ffffff}%s",string,i,GroupInfo[i][gName]);
		}
		ShowPlayerDialog(playerid, D_911, DIALOG_STYLE_LIST, DEF_NAME" » numer alarmowy", string, "Wybierz", "WyjdŸ");
	}
	else if(numer == 777)
	{
		new list[256],onduty;
		ForeachEx(i, MAX_GROUPS)
		if(GroupInfo[i][gType]==GROUP_TAXI && GroupInfo[i][gFlags] & FLAG_REPORTS)
		{
			ForeachPlayer(j)
				if(DutyGroup[j]==i)
					onduty++;
			if(onduty)
				format(list,sizeof(list),"%s\n{c8c8c8}%d: {ffffff}%s  (%d na s³u¿bie)",list,i,GroupInfo[i][gName],onduty);
			onduty=0;
		}
		if(strlen(list)>4)
			ShowPlayerDialog(playerid,D_CALL_TAXI,DIALOG_STYLE_LIST,DEF_NAME" » taxi",list,"Wybierz","WyjdŸ");
		else msg_info(playerid,"Brak dostepnych taksówek");
	}
	else if(numer == 333)
	{
		new list[512],onduty = 0;
		ForeachEx(i, MAX_GROUPS)
		{
			if(GroupInfo[i][gType] == GROUP_WORKSHOP && GroupInfo[i][gFlags] & FLAG_REPORTS)
			{
				ForeachPlayer(j)
					if(DutyGroup[j] == i)
						onduty++;
				if(onduty)
					format(list, sizeof(list), "%s\n{c8c8c8}%d\t{ffffff}%s  (%d na s³u¿bie)", list, i, GroupInfo[i][gName], onduty);
				onduty=0;
			}
		}
		if(strlen(list) > 4)
			ShowPlayerDialog(playerid, D_CALL_ASSISTANCE, DIALOG_STYLE_LIST, DEF_NAME" » pomoc drogowa", list, "Wybierz", "WyjdŸ");
		else msg_info(playerid, "Brak dostêpnych warsztatów oferuj¹cych pomoc drogow¹.");
	}
	else if(numer == 444)
	{
		new string[256];
		format(string, sizeof(string), "Wpisz treœæ, która zostanie przekazana pracownikom na s³u¿bie w grupie SANN (radio). \nPamiêtaj, ¿e aktualny koszt takiego SMSa to $%d (ustalany przez lidera).", SettingInfo[sSANNPay]);
		
		ShowPlayerDialog(playerid, D_SANN_PHONE, DIALOG_STYLE_INPUT, DEF_NAME" » Network News", string, "Wyœlij", "WyjdŸ");
	}
	else if(numer == 888)
	{
		new list[512],onduty = 0;
		ForeachEx(i, MAX_GROUPS)
		{
			if(GroupInfo[i][gType] == GROUP_RESTAURANT && GroupInfo[i][gFlags] & FLAG_REPORTS)
			{
				ForeachPlayer(j)
					if(DutyGroup[j] == i)
						onduty++;
				
				if(onduty)
					format(list, sizeof(list), "%s\n{c8c8c8}%d\t{ffffff}%s  (%d na s³u¿bie)", list, i, GroupInfo[i][gName], onduty);
				
				onduty = 0;
			}
		}
		if(strlen(list) > 4)
			ShowPlayerDialog(playerid, D_CALL_RESTAURANT, DIALOG_STYLE_LIST, DEF_NAME" » zamówienie", list, "Wybierz", "WyjdŸ");
		else msg_info(playerid, "Brak dostêpnych restauracji oferuj¹cych dowóz jedzenia.");
	}
	else
	{
		new playerid2 = GetPhoneID(numer);
		if(playerid2 < 0 || !Logged[playerid2])
			return msg_error(playerid,"Wybrany abonent jest poza zasiêgiem.");
		else if(!CharacterInfo[playerid2][pPhone] || ItemInfo[CharacterInfo[playerid2][pPhone]][iValue1] != numer)
			return msg_error(playerid,"Wybrany abonent jest poza zasiêgiem.");
		else if(playerid == playerid2)
			return msg_error(playerid,"Nie jesteœ w stanie dzwoniæ do samego siebie.");
			
		if(RozmawiaZ[playerid2] != INVALID_PLAYER_ID)
			return msg_error(playerid,"Wybrany numer jest zajêty.");
		
		RozmawiaZ[playerid] = playerid2;
		RozmawiaZ[playerid2] = playerid;
		
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
		SetPlayerAttachedObject(playerid, SLOT_PHONE, -2002, 6, 0, 0.006, 0.015, -28.8, 0, 2.8);
		
		SendClientMessageFormat(playerid, COLOR_ORANGE, "** Dzwonisz do numeru %d, zaczekaj a¿ odbierze. **", numer);
		
		CharacterInfo[playerid2][pLastNumberCalled] = ItemInfo[CharacterInfo[playerid][pPhone]][iValue1];
		
		new query[128];
		format(query, sizeof(query), "SELECT `name` FROM `srv_vcards` WHERE `number` = '%d' AND `phone_uid` = '%d' LIMIT 1", ItemInfo[CharacterInfo[playerid][pPhone]][iValue1], CharacterInfo[playerid2][pPhone]);
		mysql_query(query);
		mysql_store_result();
		
		if(mysql_num_rows())
		{
			new name[25];
			mysql_fetch_row_format(query, "|");
			sscanf(query, "p<|>s[25]", name);
			SendClientMessageFormat(playerid2, COLOR_ORANGE, "** Telefon dzwoni, aby odebraæ wpisz /odbierz (%s). **", name);
		}
		else
			SendClientMessageFormat(playerid2, COLOR_ORANGE, "** Telefon dzwoni, aby odebraæ wpisz /odbierz (%d). **", ItemInfo[CharacterInfo[playerid][pPhone]][iValue1]);
		
		mysql_free_result();
		
		if(CharacterInfo[playerid2][pTog] & TOG_TELSOUND)
			cmd_do(playerid2, "Telefon wibruje.");
		else
			cmd_do(playerid2, "S³ychaæ dzwonienie telefonu.");
	}
	return 1;
}

CMD:oddzwon(playerid, params)
{
	if(!CharacterInfo[playerid][pLastNumberCalled])
		return 1;
	new playerid2 = GetPhoneID(CharacterInfo[playerid][pLastNumberCalled]);
	if(playerid2 < 0 || !Logged[playerid2])
		return msg_error(playerid,"Wybrany abonent jest poza zasiêgiem.");
	else if(!CharacterInfo[playerid2][pPhone] || ItemInfo[CharacterInfo[playerid2][pPhone]][iValue1] != CharacterInfo[playerid][pLastNumberCalled])
		return msg_error(playerid,"Wybrany abonent jest poza zasiêgiem.");
	else if(playerid == playerid2)
		return msg_error(playerid,"Nie jesteœ w stanie dzwoniæ do samego siebie.");
		
	if(RozmawiaZ[playerid2] != INVALID_PLAYER_ID)
		return msg_error(playerid,"Wybrany numer jest zajêty.");
	
	RozmawiaZ[playerid] = playerid2;
	RozmawiaZ[playerid2] = playerid;
	
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
	SetPlayerAttachedObject(playerid, SLOT_PHONE, -2002, 6, 0, 0.006, 0.015, -28.8, 0, 2.8);
	
	SendClientMessageFormat(playerid, COLOR_ORANGE, "** Dzwonisz do numeru %d, zaczekaj a¿ odbierze. **", CharacterInfo[playerid][pLastNumberCalled]);
	
	CharacterInfo[playerid2][pLastNumberCalled] = ItemInfo[CharacterInfo[playerid][pPhone]][iValue1];
	
	new query[128];
	format(query, sizeof(query), "SELECT `name` FROM `srv_vcards` WHERE `number` = '%d' AND `phone_uid` = '%d' LIMIT 1", ItemInfo[CharacterInfo[playerid][pPhone]][iValue1], CharacterInfo[playerid2][pPhone]);
	mysql_query(query);
	mysql_store_result();
	
	if(mysql_num_rows())
	{
		new name[25];
		mysql_fetch_row_format(query, "|");
		sscanf(query, "p<|>s[25]", name);
		SendClientMessageFormat(playerid2, COLOR_ORANGE, "** Telefon dzwoni, aby odebraæ wpisz /odbierz (%s). **", name);
	}
	else
		SendClientMessageFormat(playerid2, COLOR_ORANGE, "** Telefon dzwoni, aby odebraæ wpisz /odbierz (%d). **", ItemInfo[CharacterInfo[playerid][pPhone]][iValue1]);
	
	mysql_free_result();
	
	if(CharacterInfo[playerid2][pTog] & TOG_TELSOUND)
		cmd_do(playerid2, "Telefon wibruje.");
	else
		cmd_do(playerid2, "S³ychaæ dzwonienie telefonu.");
	
	return 1;
}

CMD:odbierz(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(CharacterInfo[playerid][pBW] || CharacterInfo[playerid][pWounded])
		return msg_error(playerid,"Nie mo¿esz odbieraæ telefonu podczas BW.");
	if(RozmawiaZ[playerid] == INVALID_PLAYER_ID)
		return msg_error(playerid,"Nikt aktualnie do Ciebie nie dzwoni.");
	if(Rozmawia[playerid])
		return msg_error(playerid, "Jesteœ aktualnie w trakcie rozmowy, nie mo¿esz odbieraæ kolejnych.");
	
	new playerid2 = RozmawiaZ[playerid];
	
	Rozmawia[playerid] = true;
	Rozmawia[playerid2] = true;
	
	SendClientMessage(playerid, COLOR_ORANGE, "** Odebra³eœ telefon, aby zakoñczyæ u¿yj '/z(akoncz)'. **");
	SendClientMessage(playerid2, COLOR_ORANGE, "** Osoba odebra³a telefon, aby zakoñczyæ u¿yj '/z(akoncz)'. **");
	
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
	SetPlayerAttachedObject(playerid, SLOT_PHONE, -2002, 6, 0, 0.006, 0.015, -28.8, 0, 2.8);
	
	return 1;
}

CMD:zakoncz(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(RozmawiaZ[playerid] == INVALID_PLAYER_ID)
		return msg_error(playerid,"Nikt aktualnie do Ciebie nie dzwoni.");
	
	new playerid2 = RozmawiaZ[playerid];
	
	Rozmawia[playerid] = false;
	Rozmawia[playerid2] = false;
	
	RozmawiaZ[playerid] = INVALID_PLAYER_ID;
	RozmawiaZ[playerid2] = INVALID_PLAYER_ID;
	
	SendClientMessage(playerid, COLOR_ORANGE, "** Rozmowa zosta³a zakoñczona. **");
	SendClientMessage(playerid2, COLOR_ORANGE, "** Rozmowa zosta³a zakoñczona. **");
	
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
	SetPlayerSpecialAction(playerid2, SPECIAL_ACTION_STOPUSECELLPHONE);
	RemovePlayerAttachedObject(playerid, SLOT_PHONE);
	RemovePlayerAttachedObject(playerid2, SLOT_PHONE);
	
	return 1;
}
CMD:mp3(playerid,params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!PlayerHaveItemType(playerid, ITEM_TYPE_TELEFON))
		return msg_error(playerid,"Nie posiadasz telefonu.");
	else if(!CharacterInfo[playerid][pPhone])
		return msg_error(playerid,"Nie posiadasz w³¹czonego telefonu.\nZrób to u¿ywaj¹c telefon poprzez komendê /p.");
		
	new stations[512];
	ForeachEx(i,sizeof(RadioStations))
	{
		format(stations, sizeof(stations), "%s%s\n", stations,RadioStations[i][radioName]);
	}
	format(stations, sizeof(stations), "%sW³asny link\n{B30009}Wy³¹cz MP3",stations);
	ShowPlayerDialog(playerid,D_PHONE_MP3,DIALOG_STYLE_LIST,DEF_NAME" » MP3",stations,"Wybierz","Anuluj");
	return 1;
}

CMD:l(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!CanSpeak(playerid))
		return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
	
	new text[128], string[196];
	if(sscanf(params, "s[128]", text))
		return msg_usage(playerid,"U¿yj: /l [tekst]");
	text[0] = chrtoupper(text[0]);
	
	new lpos, rpos;
	lpos = strfind(text, "<");
	rpos = strfind(text, ">");
	if(lpos >= 0 && rpos > 0 && rpos > lpos +2)
	{
		format(string ,sizeof(string),"%s",str_replace("<","{C2A2DD}*",text));
		format(string ,sizeof(string),"%s",str_replace(">","*{FFFFFF}",string));
		format(string, sizeof(string), "%s mówi: %s", PlayerName2(playerid), string);
		SendWrappedMessageToPlayerRange(playerid, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, string, 10);
	}
	else 
	{
		format(string, sizeof(string), "%s mówi: %s", PlayerName2(playerid), text);
		SendWrappedMessageToPlayerRange(playerid, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, string, 10);
	}
	
	return 1;
}
CMD:z(playerid,params[]) return cmd_zakoncz(playerid,params);

CMD:drzwi(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new comm1[32];
	if(sscanf(params, "s[32]", comm1))
		return msg_info(playerid,"U¿yj: /drzwi [zamknij | radio | wywaz | oplata | godzina | pogoda]");
	else
	{
		if(!strcmp(comm1, "zamknij", true) || !strcmp(comm1, "z", true))
		{
			new dooruid = GetClosestDoor(playerid);
			if(!dooruid) return 1;
			
			if(!IsDoorOwner(playerid, dooruid))
				return msg_error(playerid,"Nie jesteœ w³aœcicielem tego budynku.");
			
			if(DoorsInfo[dooruid][dLock])
			{
				DoorsInfo[dooruid][dLock] = 0;
				
				SaveDoors(dooruid, SAVE_DOORS_BASIC);
				
				ForeachPlayer(i)
					if(PlayerToPlayer(10.0, playerid, i))
						PlayerPlaySound(i, 1145, 0.0, 0.0, 0.00);
				
				ApplyAnimation(playerid, "INT_HOUSE", "wash_up", 4.1, 0, 0, 0, 0, 0);
				Tip(playerid, 3, "Otwierasz drzwi za pomoca klucza.");
			}
			else
			{
				DoorsInfo[dooruid][dLock] = 1;
				
				SaveDoors(dooruid, SAVE_DOORS_BASIC);
				
				ForeachPlayer(i)
					if(PlayerToPlayer(10.0, playerid, i))
						PlayerPlaySound(i, 1145, 0.0, 0.0, 0.00);
				
				ApplyAnimation(playerid, "INT_HOUSE", "wash_up", 4.1, 0, 0, 0, 0, 0);
				Tip(playerid, 3, "Zamykasz drzwi.");
			}
		}
		else if(!strcmp(comm1, "radio", true))
		{
			new doorid=PlayerDoor[playerid];
			if(!doorid)
				return msg_error(playerid,"Nie znajdujesz siê w ¿adnych drzwiach.");
			if(!IsDoorOwner(playerid,doorid))
				return msg_error(playerid,"Nie posiadasz uprawnieñ do edycji radia w tych drzwiach.");
			ShowPlayerDialog(playerid,D_DOOR_CHANGE_RADIO,DIALOG_STYLE_INPUT,DEF_NAME" » radio","WprowadŸ adres URL radia:","Dalej","Wy³¹cz");
		}
		else if(!strcmp(comm1, "oplata", true))
		{
			new doorid=PlayerDoor[playerid];
			if(!doorid)
				return msg_error(playerid,"Nie znajdujesz siê w ¿adnych drzwiach.");
			if(!IsDoorOwner(playerid, doorid) || DoorsInfo[doorid][dOwnerTyp] != OWNER_GROUP || DoorsInfo[doorid][dEnterVW] != 0 || !IsBusiness(DoorsInfo[doorid][dOwner]))
				return msg_error(playerid,"Nie posiadasz uprawnieñ do edycji kwoty wejœciowej w tych drzwiach.");
			ShowPlayerDialog(playerid,D_DOOR_CHANGE_PRICE,DIALOG_STYLE_INPUT,DEF_NAME" » op³ata za wejœcie","Wprowadz now¹ cene wejœciow¹ (max $100):","Dalej","Anuluj");
		}
		else if(!strcmp(comm1, "wywaz", true))
		{
			if(!IsPlayerOnDutyInGroup(playerid, GROUP_PD) && !IsPlayerOnDutyInGroup(playerid, GROUP_FBI) && !IsPlayerOnDutyInGroup(playerid, GROUP_MILITARY) && !IsPlayerInCriminalGroup(playerid))
				return msg_error(playerid, "Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na s³u¿bie odpowiedniej grupy.");
		
			new dooruid = GetClosestDoor(playerid);
			if(!dooruid) return 1;
			if(DoorsInfo[dooruid][dOwnerTyp]== OWNER_JAIL)
				return msg_error(playerid,"Nie mo¿esz wywa¿yæ tych drzwi.");
			
			if(DoorsInfo[dooruid][dLock])
			{
				cmd_me(playerid, "wywa¿a drzwi.");
				msg_info(playerid, "Wywa¿yleœ drzwi przy ktorych stoisz!\nZachowaj screeny z odegrania tej akcji - mo¿esz zostac o nie poproszony.");
				DoorsInfo[dooruid][dLock] = 0;
				SaveDoors(dooruid, SAVE_DOORS_BASIC);
				log("%s[player:%d] wywaza drzwi %s[door:%d]",PlayerName3(playerid),CharacterInfo[playerid][pUID],DoorsInfo[dooruid][dName],dooruid);
			}
		}
		else if(!strcmp(comm1, "godzina", true))
		{
			new doorid=PlayerDoor[playerid];
			if(!doorid)
				return msg_error(playerid,"Nie znajdujesz siê w ¿adnych drzwiach.");
			if(!IsDoorOwner(playerid, doorid) || (DoorsInfo[doorid][dOwnerTyp] != OWNER_GROUP && DoorsInfo[doorid][dOwnerTyp] != OWNER_PLAYER && DoorsInfo[doorid][dOwnerTyp] != OWNER_HOUSE))
				return msg_error(playerid,"Nie posiadasz uprawnieñ do edycji godziny w tych drzwiach.");
			ShowPlayerDialog(playerid,D_DOOR_CHANGE_TIME,DIALOG_STYLE_INPUT,DEF_NAME" » godzina","Wpisz wartoœæ godziny, jak¹ chcesz mieæ w interiorze (miêdzy 1-24):","Dalej","Anuluj");
		}
		else if(!strcmp(comm1, "pogoda", true))
		{
			new doorid=PlayerDoor[playerid];
			if(!doorid)
				return msg_error(playerid,"Nie znajdujesz siê w ¿adnych drzwiach.");
			if(!IsDoorOwner(playerid, doorid) || (DoorsInfo[doorid][dOwnerTyp] != OWNER_GROUP && DoorsInfo[doorid][dOwnerTyp] != OWNER_PLAYER && DoorsInfo[doorid][dOwnerTyp] != OWNER_HOUSE))
				return msg_error(playerid,"Nie posiadasz uprawnieñ do edycji pogody w tych drzwiach.");
			ShowPlayerDialog(playerid,D_DOOR_CHANGE_WEATHER,DIALOG_STYLE_INPUT,DEF_NAME" » pogoda","Wpisz wartoœæ pogody, jak¹ chcesz mieæ w interiorze (powy¿ej 0):","Dalej","Anuluj");
		}
	}
	return 1;
}

CMD:bankomat(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!PlayerNearDoorType(playerid, OWNER_BANKOMAT, 1.0))
		return msg_error(playerid,"Nie znajdujesz siê blisko bankomatu.");
	
	ShowPlayerDialog(playerid, D_BANKOMAT, DIALOG_STYLE_LIST, DEF_NAME" » bankomat", "1. Poka¿ stan konta\n2. Wyp³aæ œrodki", "Dalej", "Zamknij");
	
	return 1;
}

CMD:dom(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new comm1[32], comm2[32];
	if(sscanf(params, "s[32]S()[32]", comm1, comm2))
		return msg_info(playerid,"U¿yj: /dom [lista | zapros | schowek]");
	else
	{
		if(!strcmp(comm1, "lista", true))
		{
			new list[256];
			
			format(list, sizeof(list), "Uid\tNazwa\tTyp");
			
			ForeachEx(i, _DOOR_COUNT)
				if(DoorsInfo[i][dOwnerTyp] == OWNER_PLAYER && DoorsInfo[i][dOwner] == CharacterInfo[playerid][pUID])
					format(list, sizeof(list), "%s\n%d\t%s\tW³aœciciel", list, i, DoorsInfo[i][dName]);
			
			new uid, data[4];
			
			new query[128];
			format(query, sizeof(query), "SELECT `UID` from `srv_doors_members` WHERE `player_uid` = '%d'", CharacterInfo[playerid][pUID]);
			mysql_query(query);
			mysql_store_result();
			
			if(mysql_num_rows())
			{
				while(mysql_fetch_row_format(data, "|"))
				{
					sscanf(data, "p<|>d", uid);
					if(DoorsInfo[uid][dUID] == uid)
					{
						format(list, sizeof(list), "%s\n%d\t%s\tMieszkaniec", list, uid, DoorsInfo[uid][dName]);
					}
				}
			}
			
			mysql_free_result();
			
			if(strlen(list) > 16)
				ShowPlayerDialog(playerid, D_HOUSE_INFO, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » lista domów", list, "Wybierz", "Zamknij");
			else
				return msg_error(playerid,"Nie posiadasz ¿adnych domów.");
		}
		else if(!strcmp(comm1, "zapros", true))
		{
			new dooruid = GetClosestDoor(playerid);
			
			if(!dooruid || !(DoorsInfo[dooruid][dOwnerTyp] == OWNER_PLAYER && DoorsInfo[dooruid][dOwner] == CharacterInfo[playerid][pUID]))
				return msg_error(playerid, "Nie znajdujesz siê obok swojego domu.");
			
			new playerid2;
			if(sscanf(comm2, "i", playerid2))
				return msg_usage(playerid,"U¿yj: /dom zapros [ID gracza]");
			else
			{
				if(playerid == playerid2)
					return msg_error(playerid, "Nie mo¿esz zaprosiæ samego siebie.");
			
				if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
					return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
				
				if(!PlayerToPlayer(5.0, playerid, playerid2))
					return msg_error(playerid,"Nie znajdujesz siê w pobli¿u wybranego gracza.");
				
				new string[128];
				
				format(string, sizeof(string), "SELECT `player_uid` from `srv_doors_members` WHERE `UID` = '%d'", dooruid);
				mysql_query(string);
				mysql_store_result();
				
				new uid, data[4];
				
				while(mysql_fetch_row_format(data, "|"))
				{
					sscanf(data, "p<|>d", uid);
					if(uid == CharacterInfo[playerid2][pUID])
						return msg_error(playerid, "Wybrany gracz jest ju¿ mieszkañcem tego domu.");
				}
				
				mysql_free_result();
				
				format(string, sizeof(string), "INSERT INTO `srv_doors_members` VALUES ('%d', '%d')", DoorsInfo[dooruid][dUID], CharacterInfo[playerid2][pUID]);
				mysql_query(string);
				
				format(string, sizeof(string), "Pomyœlnie doda³eœ gracza %s(%d) do swojego domu (UID: %d).", PlayerName3(playerid2),playerid2, dooruid);
				msg_info(playerid, string);
				
				format(string, sizeof(string), "Gracz %s(%d) doda³ Ciê do swojego domu (UID: %d).", PlayerName3(playerid),playerid, dooruid);
				SendClientMessage(playerid2, COLOR_GREEN, string);
			}
		}
		else if(!strcmp(comm1, "schowek", true))
		{
			new dooruid = PlayerDoor[playerid];
			
			if(!dooruid) return 1;
			
			if((DoorsInfo[dooruid][dOwner] == CharacterInfo[playerid][pUID] || CharacterInfo[playerid][pAdmin]>4) && DoorsInfo[dooruid][dOwnerTyp] == OWNER_PLAYER)
			{
				SetPVarInt(playerid, "placedooruid", dooruid);
			
				ShowPlayerDialog(playerid, D_HOUSE_PLACE, DIALOG_STYLE_LIST, DEF_NAME" » schowek", "1. Wyci¹gnij przedmiot ze schowka\n2. W³ó¿ przedmiot do schowka", "Wybierz", "Zamknij");
			}
		}
	}
	return 1;
}

CMD:kupdom(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new dooruid = GetClosestDoor(playerid);
	
	if(!dooruid) return 1;
	
	if(DoorsInfo[dooruid][dOwnerTyp] == OWNER_HOUSE_BUY)
	{
		new title[32];
		SetPVarInt(playerid, "housebuyuid", dooruid);
		
		format(title, sizeof(title), DEF_NAME" » p³atnoœæ ($%d)", DoorsInfo[dooruid][dOwner]);
		
		new string[64];
		format(string, sizeof(string), "1. Portfel ($%d)\n2. Konto bankowe ($%d)", CharacterInfo[playerid][pCash], CharacterInfo[playerid][pCredit]);
		
		ShowPlayerDialog(playerid, D_HOUSE_BUY, DIALOG_STYLE_LIST, title, string, "Wybierz", "Anuluj");
	}
	
	return 1;
}

CMD:sprawdzdom(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new comm1[32];
	if(sscanf(params, "s[32]", comm1))
	{
		new dooruid = GetClosestDoor(playerid);
		
		if(!dooruid) return 1;
	
		if(CharacterInfo[playerid][pDamageTook])
			return msg_info(playerid, "Musi min¹æ minimum 5 minut od otrzymania obra¿en aby móc u¿yæ tej komendy.");
		
		if(DoorsInfo[dooruid][dOwnerTyp] == OWNER_HOUSE_BUY)
		{
			SetPVarInt(playerid, "housecheckuid", dooruid);
			
			ShowPlayerDialog(playerid, D_HOUSE_BUY_CHECK, DIALOG_STYLE_MSGBOX, DEF_NAME" » sprawdzanie domu", "Czy jesteœ pewny, ¿e chcesz wejœæ i zobaczyæ wybrany dom od œrodka (interior)?", "Wejdz", "Anuluj");
		}
	}
	else
	{
		if(!strcmp(comm1, "wyjdz", true))
		{
			if(!CharacterInfo[playerid][pHouseCheckID]) return 1;
			
			new dooruid = CharacterInfo[playerid][pHouseCheckID];
			
			SetPlayerPos(playerid, DoorsInfo[dooruid][dEnterX], DoorsInfo[dooruid][dEnterY], DoorsInfo[dooruid][dEnterZ]);
			SetPlayerVirtualWorld(playerid, DoorsInfo[dooruid][dEnterVW]);
			SetPlayerInterior(playerid, DoorsInfo[dooruid][dEnterInt]);
			SetPlayerFacingAngle(playerid, DoorsInfo[dooruid][dEnterAngle]);
		}
	}
	return 1;
}

CMD:wjedz(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		return 1;
	
	new vehid = GetPlayerVehicleID(playerid);
	
	ForeachEx(i, _DOOR_COUNT)
	{
		if(IsPlayerInRangeOfPoint(playerid, 4.0, DoorsInfo[i][dEnterX], DoorsInfo[i][dEnterY], DoorsInfo[i][dEnterZ]) && GetPlayerVirtualWorld(playerid) == DoorsInfo[i][dEnterVW] && !DoorsInfo[i][dLock] && DoorsInfo[i][dGarage])
		{
			if(DoorsInfo[i][dOwnerTyp] == OWNER_GROUP && IsBusiness(DoorsInfo[i][dOwner]))
			{
				if(!GroupInfo[DoorsInfo[i][dOwner]][gRegistered] && !CharacterInfo[playerid][pAdmin] && DutyGroup[playerid] != DoorsInfo[i][dOwner]) 
				{		
					Tip(playerid, 3, "Biznes nie jest zarejestrowany.");
					return 1;
				}
			}
			SetVehicleVirtualWorld(vehid, DoorsInfo[i][dExitVW]);
			SetVehiclePos(vehid, DoorsInfo[i][dExitX], DoorsInfo[i][dExitY], DoorsInfo[i][dExitZ]);
			SetVehicleZAngle(vehid, DoorsInfo[i][dExitAngle]);
			LinkVehicleToInterior(vehid, DoorsInfo[i][dExitInt]);
			
			ForeachPlayer(x)
			{
				if(GetPlayerVehicleID(x) == vehid)
				{
					SetPlayerVirtualWorld(x, DoorsInfo[i][dExitVW]);
					SetPlayerInterior(x, DoorsInfo[i][dExitInt]);
					PlayerDoor[x] = i;
				}
			}
			break;
		}
		else if(IsPlayerInRangeOfPoint(playerid, 4.0, DoorsInfo[i][dExitX], DoorsInfo[i][dExitY], DoorsInfo[i][dExitZ]) && GetPlayerVirtualWorld(playerid) == DoorsInfo[i][dExitVW] && !DoorsInfo[i][dLock])
		{
			SetVehicleVirtualWorld(vehid, DoorsInfo[i][dEnterVW]);
			SetVehiclePos(vehid, DoorsInfo[i][dEnterX], DoorsInfo[i][dEnterY], DoorsInfo[i][dEnterZ]);
			SetVehicleZAngle(vehid, DoorsInfo[i][dEnterAngle]);
			LinkVehicleToInterior(vehid, DoorsInfo[i][dEnterInt]);
		
			ForeachPlayer(x)
			{
				if(GetPlayerVehicleID(x) == vehid)
				{
					SetPlayerVirtualWorld(x, DoorsInfo[i][dEnterVW]);
					SetPlayerInterior(x, DoorsInfo[i][dEnterInt]);
					PlayerDoor[x] = 0;
					
					if(DoorsInfo[i][dRadio] && !VehicleInfo[GetVehicleUID(vehid)][vRadio])
						StopAudioStreamForPlayer(x);
				}
			}
			break;
		}
	}
	
	return 1;
}
CMD:przejazd(playerid, params[]) return cmd_wjedz(playerid, params);

CMD:kuppojazd(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new dooruid = GetClosestDoor(playerid);
	
	if(CharacterInfo[playerid][pHours] < 1)
		return msg_error(playerid,"Aby zakupiæ pojazd postaæ musi mieæ powy¿ej 1h online");
	
	if(DoorsInfo[dooruid][dOwnerTyp] == OWNER_SVEHICLE)
		ShowPlayerDialog(playerid, D_SVEHICLE, DIALOG_STYLE_LIST, DEF_NAME" » salon pojazdów", "Jednoœlady\nTrzydrzwiowe\nPiêciodrzwiowe\nOffroad\nDostawcze\nSportowe", "Wybierz", "Zamknij");
	
	return 1;
}

CMD:spawn(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	ShowPlayerDialog(playerid, D_CHOOSE_SPAWN, DIALOG_STYLE_LIST, DEF_NAME" » wybór spawna", "1. Spawny g³ówne\n2. Domy\n3. Grupy", "Wybierz", "Zamknij");
	
	return 1;
}

CMD:awaryjne(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		if(!IsAPlane(GetPlayerVehicleID(playerid)) && !IsABoat(GetPlayerVehicleID(playerid)))
		{
			new vehid = GetPlayerVehicleID(playerid);
			new vehuid = GetVehicleUID(vehid);
			
			if(Kierunki_V[vehuid][2] || Kierunki_V[vehuid][0])
			{
				DestroyObject(Kierunki_V[vehuid][5]);
				DestroyObject(Kierunki_V[vehuid][2]);
				DestroyObject(Kierunki_V[vehuid][3]);
				
				Kierunki_V[vehuid][2] = 0;
				
				DestroyObject(Kierunki_V[vehuid][4]);
				DestroyObject(Kierunki_V[vehuid][0]);
				DestroyObject(Kierunki_V[vehuid][1]);
				
				Kierunki_V[vehuid][0] = 0;
			}
			else SetVehicleIndicator(vehuid, 1, 1);
		}
	}
	return 1;
}

CMD:zbierz(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new plant;
	
	if(!IsPlayerInGroupType(playerid, GROUP_PD) || !IsPlayerOnDutyInGroup(playerid, GROUP_FBI))
	{
		plant=GetClosestPlant(playerid, 1);
		if(!plant) return 1;
		if(PlantInfo[plant][plantTime] <= 0)
		{
			DestroyDynamic3DTextLabel(PlantInfo[plant][planttext]);
			DestroyDynamicObject(PlantInfo[plant][plantObject]);
			
			new ilosc = 5+random(6);
			
			StworzPrzedmiot(OWNER_PLAYER, CharacterInfo[playerid][pUID], "Marihuana", ITEM_TYPE_MARIHUANA, ilosc, 1, 1);
			
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
			
			msg_infoFormat(playerid,32,"Zebra³eœ %d gram marihuany.", ilosc);
		}
	}
	else
	{
		plant=GetClosestPlant(playerid, 0);
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
		
		msg_info(playerid, "Krzak marihuany zosta³ zabezpieczony i przekazany do magazynu dowodów.");
	}
	
	return 1;
}

CMD:relog(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	
	if(!CharacterInfo[playerid][pAdmin])
	{
		if(CharacterInfo[playerid][pDamageTook])
			return msg_info(playerid, "Musi min¹æ minimum 5 minut od otrzymania obra¿en aby móc u¿yæ tej komendy.");
		
		if(!(CharacterInfo[playerid][pTog] & TOG_QS))
			CharacterInfo[playerid][pTog] += TOG_QS;
		SavePlayerStats(playerid, SAVE_PLAYER_OPTION);
		SavePlayerStats(playerid, SAVE_PLAYER_POS);
		
		SetPlayerName(playerid, CharacterInfo[playerid][pNick]);
		SetPVarString(playerid, "RelogGlobalName", CharacterInfo[playerid][pGlobalNick]);
		
		OnPlayerDisconnect(playerid, 2);
		OnPlayerConnect(playerid);
		
		new name[32];
		GetPVarString(playerid, "RelogGlobalName", name, 32);
		
		SetPlayerName(playerid, name);
		
		OnPlayerRequestClass(playerid, 1);
		return 1;
	}
	new playerid2;
	if(sscanf(params, "i", playerid2))
	{
		if(CharacterInfo[playerid][pAdmin] > 1)
			return msg_usage(playerid,"U¿yj: /relog [ID gracza]");
	}
	else if(CharacterInfo[playerid][pAdmin])
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Wybrany gracz nie jest zalogowany.");
		
		SendAdminMessageFormat(COLOR_RED, "[AI] %s (%d) u¿y³ komendy /relog na graczu %s (%d).", PlayerName3(playerid), playerid, PlayerName3(playerid2), playerid2);
			
		if(!(CharacterInfo[playerid2][pTog] & TOG_QS))
			CharacterInfo[playerid2][pTog] += TOG_QS;
		SavePlayerStats(playerid2, SAVE_PLAYER_OPTION);
		SavePlayerStats(playerid2, SAVE_PLAYER_POS);
		
		SetPlayerName(playerid2, CharacterInfo[playerid][pNick]);
		SetPVarString(playerid2, "RelogGlobalName", CharacterInfo[playerid2][pGlobalNick]);
		
		OnPlayerDisconnect(playerid2, 2);
		OnPlayerConnect(playerid2);
		
		new name[32];
		GetPVarString(playerid2, "RelogGlobalName", name, 32);
		
		SetPlayerName(playerid2, name);
		
		OnPlayerRequestClass(playerid2, 1);
	}
	
	return 1;
}

CMD:login(playerid,params[]) return cmd_relog(playerid,params);


CMD:kupubranie(playerid,params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new doorid=PlayerDoor[playerid];
	if(DoorsInfo[doorid][dOwnerTyp] != OWNER_CLOTHESSHOP)
		return msg_error(playerid,"Nie znajdujesz siê w sklepie odzie¿owym.");
	if(!CharacterInfo[playerid][pSex])
		ShowModelSelectionMenu(playerid, femaleskinlist, "Zakup ubranie");
	else
		ShowModelSelectionMenu(playerid, maleskinlist, "Zakup ubranie");
	return 1;
}
CMD:ubranie(playerid,params[]) return cmd_kupubranie(playerid,params);

CMD:akceptujsmierc(playerid,params[])
{
	if(!CharacterInfo[playerid][pBW])
		return msg_error(playerid,"Aby skorzystaæ z tej komendy postaæ musi byæ nieprzytomna (w³aœciwe BW).");
	if(CharacterInfo[playerid][pHours] < 2)
		return msg_error(playerid,"Postaæ nie posiada wystarczaj¹cej iloœci godzin (dwóch).");
	
	ShowPlayerDialog(playerid, D_DEATH, DIALOG_STYLE_INPUT,DEF_NAME" » uœmiercanie postaci", "Wpisz powód zgonu:", "Akceptuj", "Anuluj");
	return 1;
}

CMD:opis(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	
	ShowPlayerDialog(playerid, D_DESCRIPTION, DIALOG_STYLE_LIST, DEF_NAME" » opis postaci", "1. Lista opisów\n2. Dodaj opis do listy\n3. Usuñ swój aktualny opis\n4. Zobacz swój aktualny opis", "Wybierz", "WyjdŸ");
	return 1;
}

CMD:radio(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!PlayerHaveItemType(playerid, ITEM_TYPE_RADIO))
		return msg_error(playerid,"Nie posiadasz przy sobie krótkofalówki.");

	if(!CanMove(playerid) || !CanSpeak(playerid))
		return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");

	new comm1[144];
	if(sscanf(params, "s[144]", comm1))
		return msg_info(playerid,"U¿yj: /radio [treœæ | kanal | zalozkanal | opcje]");
	else
	{
		if(!strcmp(comm1, "kanal", true))
			ShowPlayerDialog(playerid, D_WALKIE_CHANGE, DIALOG_STYLE_INPUT, DEF_NAME" » zmieñ kanal radiowy", "Podaj numer kana³u. Zasiêg kana³ów obejmuje 1-2000.", "Zmieñ", "Anuluj");
		else if(!strcmp(comm1, "zalozkanal", true))
		{
			ShowPlayerDialog(playerid,D_WALKIE_CREATE,DIALOG_STYLE_INPUT,DEF_NAME" » nowy kana³","Podaj numer kana³u.\nZasiêg kana³ów obejmuje 1-2000.","Wybierz","WyjdŸ");
			return 1;
		}
		else if(!strcmp(comm1, "opcje", true))
		{
			new kanal=CharacterInfo[playerid][pKanal];
			if(kanal < 1)
			 	return msg_error(playerid,"Nie jesteœ po³¹czony z ¿adnym kana³em.");
			new query[128], creator;
			format(query,sizeof(query),"SELECT `creator` FROM `srv_walkie_channels` WHERE `channel`='%d'",kanal);
			mysql_query(query);
			mysql_store_result();
			mysql_fetch_row_format(query);
			creator = strval(query);
			mysql_free_result();

			if(creator!=CharacterInfo[playerid][pUID])
				return msg_error(playerid,"Tylko w³aœciciel kana³u mo¿e nim zarz¹dzaæ.");

			SetPVarInt(playerid,"pWalkieChannel",kanal);
			ShowPlayerDialog(playerid,D_WALKIE_OPT,DIALOG_STYLE_LIST,DEF_NAME" » radio","Zmieñ has³o\nUsuñ kana³","Wybierz", "WyjdŸ");
		}
		else
		{
			new kanal = CharacterInfo[playerid][pKanal];
			
			if(kanal < 1)
				return msg_error(playerid,"Nie jesteœ po³¹czony z ¿adnym kana³em.");
			new str1[170],text2[64],bool:long;
			comm1[0] = chrtoupper(comm1[0]);
			if(strlen(comm1) < 78)
				format(str1,sizeof(str1),"*R*[%d] {ffffff}%s: %s", kanal, PlayerName2(playerid), comm1);
			else
			{
				long=true;
				new pos = strfind(comm1, " ", true, strlen(comm1) / 2);
				if(pos != -1)
				{
					new commdup[196];
					strmid(commdup, comm1, 0, 196);
					
					strmid(text2, commdup, pos + 1, strlen(commdup));
					strdel(commdup, pos, strlen(commdup));
					
					format(str1,sizeof(str1),"*R*[%d] {ffffff}%s: %s ...", kanal, PlayerName2(playerid), commdup);
					
					strins(text2, "...", 0);
				}
			}
			
			ForeachPlayer(i)
			{
				if(CharacterInfo[i][pKanal] == kanal && PlayerHaveItemType(i, ITEM_TYPE_RADIO))
				{
					
					if(!long)
					{
						SendClientMessage(i, COLOR_ORANGE, str1);
						playerLog(i,"RADIO",str1);
					}
					else
					{
						SendClientMessage(i, COLOR_ORANGE, str1);
						SendClientMessage(i, COLOR_WHITE, text2);
						playerLog(i,"RADIO",str1);
						playerLog(i,"RADIO",text2);
					}
				}
			}
			
			format(str1, sizeof(str1), "%s (radio): %s", PlayerName2(playerid), comm1);
			SendWrappedMessageToPlayerRange(playerid, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, str1, 10, false, true);
		}
	}
	
	return 1;
}
CMD:r(playerid,params[]) return cmd_radio(playerid,params);

CMD:oferuj(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new comm1[32], comm2[128];
	if(sscanf(params, "s[32]S()[128]", comm1, comm2))
	{
		new string[196];
		format(string,sizeof(string),"U¿yj: /oferuj [przedmiot | pojazd | dom | vcard");
		if(IsPlayerInGroupType(playerid, GROUP_WORKSHOP)) 
			format(string,sizeof(string),"%s | naprawa | malowanie | paintjob | tuning | demontaz",string);
		if(IsPlayerInGroupType(playerid, GROUP_TAXI))
			format(string,sizeof(string),"%s | przejazd",string);
		if(IsPlayerInGroupType(playerid, GROUP_GOV))
			format(string, sizeof(string), "%s | dokument | rejestracja",string);
		if(IsPlayerInGroupType(playerid, GROUP_PD))
			format(string, sizeof(string), "%s | mandat | licencja (lider)", string);
		if(IsPlayerInGroupType(playerid, GROUP_MC))
			format(string, sizeof(string), "%s | leczenie | poczytalnosc (lider)", string);
		if(IsPlayerInGroupType(playerid, GROUP_NEWS))
			format(string, sizeof(string), "%s | reklama", string);
		if(IsPlayerInGroupType(playerid, GROUP_GYM))
			format(string, sizeof(string), "%s | karnet", string);
		format(string,sizeof(string),"%s]", string);
		msg_usage(playerid,string);
		return 1;
	}
	else
	{
		if(!strcmp(comm1, "przedmiot", true))
		{
			if(CharacterInfo[playerid][pHours] < 2)
				return msg_error(playerid,"Nie mo¿esz oferowaæ przedmiotów przed przegraniem 2 godzin.");
			new price;
			if(sscanf(comm2, "d", price))
				return msg_usage(playerid,"U¿yj: /o(feruj) przedmiot [cena]");
			if(price < 0)
				return msg_error(playerid,"Podana cena jest niepoprawna.");
			
			if(!CanMove(playerid))
				return msg_error(playerid, "Nie mo¿esz aktualnie u¿yæ tej komendy.");
			
			SetPVarInt(playerid, "OfertaPrzedmiotCena", price);
			
			new list[1024];
	
			format(list, sizeof(list), "Uid\tNazwa\tWartoœæ 1\tWartoœæ 2");
	
			ForeachEx(i,_ITEM_COUNT)
				if(ItemInfo[i][iUID])
					if(ItemInfo[i][iOwnerTyp] == OWNER_PLAYER && ItemInfo[i][iOwner] == CharacterInfo[playerid][pUID] && !ItemInfo[i][iUsed])
						format(list, sizeof(list), "%s\n%d\t{878A87}%s\t%d\t%d", list, ItemInfo[i][iUID], ItemInfo[i][iName], ItemInfo[i][iValue1], ItemInfo[i][iValue2]);
			
			if(strlen(list) > 27) ShowPlayerDialog(playerid, D_OFFER_ITEM, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » wybierz przedmiot", list, "Wybierz", "Anuluj");
			else Tip(playerid, 3, "Nie posiadasz przedmiotow.");
		}
		else if(!strcmp(comm1, "pojazd", true))
		{
			if(CharacterInfo[playerid][pHours] < 2)
				return msg_error(playerid,"Nie mo¿esz oferowaæ pojazdów przed przegraniem 2 godzin.");
			if(!GetPlayerVehicleID(playerid))
				return msg_error(playerid,"Aby oferowaæ pojazd musisz siê w nim znajdowaæ!");
			new vehid = GetVehicleUID(GetPlayerVehicleID(playerid));
			if(VehicleInfo[vehid][vOwner]!=CharacterInfo[playerid][pUID] || VehicleInfo[vehid][vOwnerTyp] != OWNER_PLAYER)
				return msg_error(playerid,"Nie jesteœ w³aœcicielem tego pojazdu!");
			new string[512];
			ForeachPlayer(i)
				if(PlayerToPlayer(5.0, playerid, i) && i != playerid)
					format(string, sizeof(string), "%s\n%d\t%s", string, i, CharacterInfo[i][pNick]);
			new price;
			if(sscanf(comm2, "d", price))
				return msg_usage(playerid,"U¿yj: /o(feruj) pojazd [cena]");
			if(price < 0)
				return msg_error(playerid,"Podana cena jest niepoprawna.");
			SetPVarInt(playerid, "OfferVehicleUID", vehid);
			SetPVarInt(playerid,"OfferPrice",price);
			if(strlen(string))
				ShowPlayerDialog(playerid, D_OFFER_VEHICLE, DIALOG_STYLE_LIST, DEF_NAME" » wybierz gracza", string, "Wybierz", "Anuluj");
			else
				msg_error(playerid,"Nie ma nikogo w pobli¿u!");

			return 1;
		}
		else if(!strcmp(comm1, "naprawa", true))
		{
			if(!IsPlayerOnDutyInGroup(playerid,GROUP_WORKSHOP))
				return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na s³u¿bie odpowiedniej grupy.");
			new giveplayer_id;
			if(sscanf(comm2, "i", giveplayer_id))
				return msg_usage(playerid,"U¿yj: /o(feruj) naprawa [id gracza]");
			if(CharacterInfo[playerid][pRepairTime]>0)
				return msg_error(playerid,"Jesteœ w trakcie wykonywania innej us³ugi.");
			new price=GetOfferPrice(DutyGroup[playerid],OFFER_REPAIR_ENG);
			if(price < 0)
				return msg_error(playerid,"Cena naprawy jest nieprawid³owa. Lider musi j¹ ustaliæ.");
			if(!(PlayerDoor[playerid] && DoorsInfo[PlayerDoor[playerid]][dOwnerTyp]==OWNER_GROUP && DoorsInfo[PlayerDoor[playerid]][dOwner]==DutyGroup[playerid]))
				return msg_error(playerid,"Aby naprawiæ pojazd musisz znajdowaæ siê w warsztacie.");
			if(!Logged[giveplayer_id])
				return msg_error(playerid,"Wybrany gracz nie jest zalogowany.");
			if(!PlayerToPlayer(5.0,playerid,giveplayer_id))
				return msg_error(playerid,"Wybrany gracz nie znajduje siê obok Ciebie.");
			if(!GetPlayerVehicleID(giveplayer_id))
				return msg_error(playerid,"Wybrany gracz nie znajduje siê w pojeŸdzie.");
		
			new vehid=GetVehicleUID(GetPlayerVehicleID(giveplayer_id));
			if(VehicleInfo[vehid][vEngine])
				return msg_error(playerid,"Silnik pojazdu nie mo¿e byæ uruchomiony.");
			SetPVarInt(playerid, "pRepairCarID", vehid);
			SetPVarInt(playerid,"pRepairJobPrice",price);
			SetPVarInt(playerid,"pRepairCustomer",giveplayer_id);
			ShowPlayerDialog(playerid,D_REPAIR,DIALOG_STYLE_LIST,DEF_NAME" » naprawa pojazdu","Naprawa silnika\nNaprawa karoserii\nNaprawa opon\nNaprawa ca³oœciowa","Wybierz","WyjdŸ");

			//price += floatround(1000.0 - VehicleInfo[vehid][vHP] );
			//Oferta(OFFER_REPAIR,playerid,giveplayer_id,price,vehid);
		}
		else if(!strcmp(comm1, "malowanie", true))
		{
			if(!IsPlayerOnDutyInGroup(playerid,GROUP_WORKSHOP))
				return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na s³u¿bie odpowiedniej grupy.");
			new giveplayer_id,color1,color2;
			if(sscanf(comm2, "idd", giveplayer_id, color1,color2))
				return msg_usage(playerid,"U¿yj: /o(feruj) malowanie [id gracza] [kolor1] [kolor2]");
			if(CharacterInfo[playerid][pRepairTime]>0)
				return msg_error(playerid,"Jesteœ w trakcie wykonywania innej us³ugi.");
			if(color1 < 0 || color1 > 255 || color2<0 || color2 > 255)
				return msg_error(playerid,"Jeden z kolorów nie jest prawid³owy. (0-255)");
			if(!(PlayerDoor[playerid] && DoorsInfo[PlayerDoor[playerid]][dOwnerTyp]==OWNER_GROUP && DoorsInfo[PlayerDoor[playerid]][dOwner]==DutyGroup[playerid]))
				return msg_error(playerid,"Aby naprawiæ pojazd musisz znajdowaæ siê w warsztacie.");
			if(!Logged[giveplayer_id])
				return msg_error(playerid,"Wybrany gracz nie jest zalogowany.");
			if(!PlayerToPlayer(5.0,playerid,giveplayer_id))
				return msg_error(playerid,"Wybrany gracz nie znajduje siê obok Ciebie.");
			if(!GetPlayerVehicleID(giveplayer_id))
				return msg_error(playerid,"Wybrany gracz nie znajduje siê w pojeŸdzie.");
			new price=GetOfferPrice(DutyGroup[playerid],OFFER_PAINT);
			if(price < 0)
				return msg_error(playerid,"Cena naprawy jest nieprawid³owa. Lider musi j¹ ustaliæ.");
			new vehid=GetVehicleUID(GetPlayerVehicleID(giveplayer_id));
			
			if(VehicleInfo[vehid][vEngine] && hasModelEngine(VehicleInfo[vehid][vModel]))
				return msg_error(playerid,"Silnik pojazdu nie mo¿e byæ uruchomiony.");
			
			SetPVarInt(playerid, "pRepairCarID", vehid);
			SetPVarInt(playerid,"pRepairJobPrice",price);
			SetPVarInt(playerid,"pRepairCustomer",giveplayer_id);
			SetPVarInt(playerid,"pRepairColor1",color1);
			SetPVarInt(playerid,"pRepairColor2",color2);
			Oferta(OFFER_PAINT,playerid,giveplayer_id,price+300,vehid);
		}
		else if(!strcmp(comm1, "paintjob", true))
		{
			if(!IsPlayerOnDutyInGroup(playerid,GROUP_WORKSHOP))
				return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na s³u¿bie odpowiedniej grupy.");
			if(CharacterInfo[playerid][pRepairTime]>0)
				return msg_error(playerid,"Jesteœ w trakcie wykonywania innej us³ugi.");
			if(!(PlayerDoor[playerid] && DoorsInfo[PlayerDoor[playerid]][dOwnerTyp]==OWNER_GROUP && DoorsInfo[PlayerDoor[playerid]][dOwner]==DutyGroup[playerid]))
				return msg_error(playerid,"Aby przemalowaæ pojazd musisz znajdowaæ siê w warsztacie.");
			new giveplayer_id,paint;
			if(sscanf(comm2, "id", giveplayer_id, paint))
				return msg_usage(playerid,"U¿yj: /o(feruj) paintjob [id gracza] [paintjob]\nPaintjob id 3 usuwa paintjob z pojazdu.");
			
			if(paint < 0 || paint > 3)
				return msg_error(playerid,"Nieprawid³owe id paintjoba. (0-3)");
			if(!(PlayerDoor[playerid] && DoorsInfo[PlayerDoor[playerid]][dOwnerTyp]==OWNER_GROUP && DoorsInfo[PlayerDoor[playerid]][dOwner]==DutyGroup[playerid]))
				return msg_error(playerid,"Aby przemalowaæ pojazd musisz znajdowaæ siê w warsztacie.");
			if(!Logged[giveplayer_id])
				return msg_error(playerid,"Wybrany gracz nie jest zalogowany.");
			if(!PlayerToPlayer(5.0,playerid,giveplayer_id))
				return msg_error(playerid,"Wybrany gracz nie znajduje siê obok Ciebie.");
			if(!GetPlayerVehicleID(giveplayer_id))
				return msg_error(playerid,"Wybrany gracz nie znajduje siê w pojeŸdzie.");
			new price=GetOfferPrice(DutyGroup[playerid],OFFER_PAINTJOB);
			if(price < 0)
				return msg_error(playerid,"Cena naprawy jest nieprawid³owa. Lider musi j¹ ustaliæ.");
			new model=GetVehicleModel(GetPlayerVehicleID(giveplayer_id));
			
			if(! (model==483 || model ==534 || model ==535 || model ==536 || model ==558 || model ==559 || model ==560 || model ==561 || model ==562 || model ==565 || model ==567 || model ==575 || model ==576))
				return msg_error(playerid,"Na ten pojazd nie mo¿na na³o¿yæ paintjoba.");
			new vehid=GetVehicleUID(GetPlayerVehicleID(giveplayer_id));
			if(VehicleInfo[vehid][vEngine])
				return msg_error(playerid,"Silnik pojazdu nie mo¿e byæ uruchomiony.");
			SetPVarInt(playerid, "pRepairCarID", vehid);
			SetPVarInt(playerid,"pRepairJobPrice",price);
			SetPVarInt(playerid,"pRepairCustomer",giveplayer_id);
			SetPVarInt(playerid,"pRepairPaint",paint);
			Oferta(OFFER_PAINTJOB,playerid,giveplayer_id,price+600,vehid);
		}
		else if(!strcmp(comm1, "tuning", true))
		{
			if(!IsPlayerOnDutyInGroup(playerid,GROUP_WORKSHOP))
				return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na s³u¿bie odpowiedniej grupy.");
			if(CharacterInfo[playerid][pRepairTime]>0)
				return msg_error(playerid,"Jesteœ w trakcie wykonywania innej us³ugi.");
			if(!(PlayerDoor[playerid] && DoorsInfo[PlayerDoor[playerid]][dOwnerTyp]==OWNER_GROUP && DoorsInfo[PlayerDoor[playerid]][dOwner]==DutyGroup[playerid]))
				return msg_error(playerid,"Aby modyfikowaæ pojazd musisz znajdowaæ siê w warsztacie.");
			new giveplayer_id;
			if(sscanf(comm2, "i", giveplayer_id))
				return msg_usage(playerid,"U¿yj: /o(feruj) tuning [id gracza]");
			
			if(!Logged[giveplayer_id])
				return msg_error(playerid,"Wybrany gracz nie jest zalogowany.");
			if(!PlayerToPlayer(5.0,playerid,giveplayer_id))
				return msg_error(playerid,"Wybrany gracz nie znajduje siê obok Ciebie.");
			if(!GetPlayerVehicleID(giveplayer_id))
				return msg_error(playerid,"Wybrany gracz nie znajduje siê w pojeŸdzie.");
			new price=GetOfferPrice(DutyGroup[playerid],OFFER_TUNING);
			if(price <= 0)
				return msg_error(playerid,"Cena modyfikacji jest nieprawid³owa. Lider musi j¹ ustaliæ.");
			new model=GetVehicleModel(GetPlayerVehicleID(giveplayer_id));

			if(IsAPlane(model) || IsABike(model))
				return msg_error(playerid,"Tego pojazdu nie mo¿na modyfikowaæ.");
			new string[1024];
			format(string,sizeof(string),"UID\tNazwa\tSztuk\tCena");
			
			ForeachEx(i, _ITEM_COUNT)
				if(ItemInfo[i][iOwnerTyp]==OWNER_GROUP && ItemInfo[i][iOwner]==DutyGroup[playerid] && (ItemInfo[i][iType] == ITEM_TYPE_TUNING || ItemInfo[i][iType] == ITEM_TYPE_GLASS) && ItemInfo[i][iPrice] > 0)
					format(string,sizeof(string),"%s\n{c8c8c8}%3d:\t{ffffff}%s\t%d\t$%d",string,i,ItemInfo[i][iName],ItemInfo[i][iIlosc],ItemInfo[i][iPrice]);
			if(strlen(string)<24)
				return msg_error(playerid,"Brak czêœci w magazynie warsztatu.");
			new vehid=GetVehicleUID(GetPlayerVehicleID(giveplayer_id));
			if(VehicleInfo[vehid][vEngine])
				return msg_error(playerid,"Silnik pojazdu nie mo¿e byæ uruchomiony.");
			SetPVarInt(playerid, "pRepairCarID", vehid);
			SetPVarInt(playerid,"pRepairJobPrice",price);
			SetPVarInt(playerid,"pRepairCustomer",giveplayer_id);
			ShowPlayerDialog(playerid,D_TUNING,DIALOG_STYLE_TABLIST_HEADERS,DEF_NAME" » tuning pojazdu",string,"ok","");
		}
		else if(!strcmp(comm1, "demontaz", true))
		{
			if(!IsPlayerOnDutyInGroup(playerid,GROUP_WORKSHOP))
				return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na s³u¿bie odpowiedniej grupy.");
			new giveplayer_id;
			if(sscanf(comm2, "dd", giveplayer_id))
				return msg_usage(playerid,"U¿yj: /o(feruj) demontaz [id gracza]");
			if(CharacterInfo[playerid][pRepairTime]>0)
				return msg_error(playerid,"Jesteœ w trakcie wykonywania innej us³ugi.");

			if(!(PlayerDoor[playerid] && DoorsInfo[PlayerDoor[playerid]][dOwnerTyp]==OWNER_GROUP && DoorsInfo[PlayerDoor[playerid]][dOwner]==DutyGroup[playerid]))
				return msg_error(playerid,"Aby modyfikowaæ pojazd musisz znajdowaæ siê w warsztacie.");
			if(!Logged[giveplayer_id])
				return msg_error(playerid,"Wybrany gracz nie jest zalogowany.");
			if(!PlayerToPlayer(5.0,playerid,giveplayer_id))
				return msg_error(playerid,"Wybrany gracz nie znajduje siê obok Ciebie.");
			if(!GetPlayerVehicleID(giveplayer_id))
				return msg_error(playerid,"Wybrany gracz nie znajduje siê w pojeŸdzie.");
			new price=GetOfferPrice(DutyGroup[playerid],OFFER_DISMOUNT);
			if(price < 0)
				return msg_error(playerid,"Cena naprawy jest nieprawid³owa. Lider musi j¹ ustaliæ.");
			new vehuid=GetVehicleUID(GetPlayerVehicleID(giveplayer_id));
			new query[96],string[512],uid,name[32];
			format(query,sizeof(query),"SELECT `id`, `name` FROM `srv_tuning` WHERE `vehicle`='%d'",vehuid);
			mysql_query(query);
			mysql_store_result();
			while(mysql_fetch_row_format(query, "|") == 1)
			{
				sscanf(query,"p<|>ds[32]",uid,name);
				format(string,sizeof(string),"%s\n{d8d8d8}%d:\t{ffffff}%s",string,uid,name);
			}
			mysql_free_result();
			if(strlen(string)<3)
				return msg_error(playerid,"W pojeŸdzie nie ma zamontowanego tuningu.");
			SetPVarInt(playerid, "pRepairCarID", vehuid);
			SetPVarInt(playerid,"pRepairJobPrice",price);
			SetPVarInt(playerid,"pRepairCustomer",giveplayer_id);
			ShowPlayerDialog(playerid,D_TUNING_DISMOUNT,DIALOG_STYLE_LIST,DEF_NAME" » demonta¿ tuningu",string,"Wybierz","WyjdŸ");
		}
		else if(!strcmp(comm1, "dom", true))
		{
			new dooruid = GetClosestDoor(playerid);
			
			if(!dooruid || !(DoorsInfo[dooruid][dOwnerTyp] == OWNER_PLAYER && DoorsInfo[dooruid][dOwner] == CharacterInfo[playerid][pUID]))
				return msg_error(playerid, "Nie znajdujesz siê obok swojego domu.");
			
			new playerid2, price;
			if(sscanf(comm2, "id", playerid2, price))
				return msg_usage(playerid,"U¿yj: /o(feruj) dom [id gracza] [cena]");
			else
			{
				if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
					return msg_error(playerid,"Wybrany gracz nie jest zalogowany.");
				
				Oferta(OFFER_HOUSE, playerid, playerid2, price, dooruid);
			}
		}
		else if(!strcmp(comm1,"vcard",true))
		{
			new giveplayer_id;
			if(sscanf(comm2, "d", giveplayer_id))
				return msg_usage(playerid,"U¿yj: /o(feruj) vcard [id gracza]");
			if(!Logged[giveplayer_id] || !PlayerToPlayer(5.0,playerid,giveplayer_id) || playerid == giveplayer_id)
				return msg_error(playerid,"Wybrany gracz nie znajduje siê obok Ciebie.");
			if(!CharacterInfo[playerid][pPhone])
				return msg_error(playerid,"Nie posiadasz w³¹czonego telefonu.");
			if(!CharacterInfo[giveplayer_id][pPhone])
				return msg_error(playerid,"Wybrany gracz nie posiada w³¹czonego telefonu.");
			Oferta(OFFER_VCARD,playerid,giveplayer_id,0,1);
		}
		else if(!strcmp(comm1, "przejazd", true))
		{
			if(!IsPlayerOnDutyInGroup(playerid, GROUP_TAXI))
				return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na s³u¿bie odpowiedniej grupy.");
			if(CharacterInfo[playerid][pTaxiPassenger]!=INVALID_PLAYER_ID)
				return msg_error(playerid,"Aktualnie przewozisz innego pasa¿era.");
			if(!(GetPlayerVehicleID(playerid) && GetPlayerState(playerid)==PLAYER_STATE_DRIVER))
				return msg_error(playerid,"Nie znajdujesz siê w taksówce.");
			new vehuid=GetVehicleUID(GetPlayerVehicleID(playerid));
			if(!(VehicleInfo[vehuid][vOwnerTyp]==OWNER_GROUP && VehicleInfo[vehuid][vOwner]==DutyGroup[playerid]))
				return msg_error(playerid,"Nie znajdujesz siê w pojeŸdzie grupy.");

			new giveplayer_id;
			if(sscanf(comm2,"d",giveplayer_id))
				return msg_usage(playerid,"U¿yj: /o przejazd [id gracza]");

			if(!Logged[giveplayer_id])
				return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany");
			if(GetPlayerVehicleID(playerid)!=GetPlayerVehicleID(giveplayer_id))
				return msg_error(playerid,"Gracz nie znajduje siê w Twoim pojeŸdzie.");
			new price=GetOfferPrice(DutyGroup[playerid],OFFER_TAXI);
			Oferta(OFFER_TAXI,playerid,giveplayer_id,price,1);
		}
		else if(!strcmp(comm1, "mandat", true))
		{
			new giveplayer_id, price, points;
			if(sscanf(comm2, "ddd", giveplayer_id, price, points))
				return msg_usage(playerid,"U¿yj: /o(feruj) mandat [id gracza] [cena] [punkty karne]");
		
			if(!IsPlayerOnDutyInGroup(playerid, GROUP_PD))
				return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na s³u¿bie odpowiedniej grupy.");
			if(!Logged[giveplayer_id])
				return msg_error(playerid,"Wybrany gracz nie jest zalogowany.");
			if(!PlayerToPlayer(5.0,playerid,giveplayer_id))
				return msg_error(playerid,"Wybrany gracz nie znajduje siê obok Ciebie.");
			if(!(CharacterInfo[giveplayer_id][pDocs] & DOC_DRIVER) && points > 0)
				return msg_error(playerid, "Wybrany gracz nie posiada prawa jazdy.");
			if(price < 1)
				return msg_error(playerid, "Wpisana kwota mandatu nie jest prawid³owa.");
			if(points < 0)
				return msg_error(playerid, "Wpisane punkty mandatu nie s¹ prawid³owe.");
			
			Oferta(OFFER_MANDAT,playerid,giveplayer_id,price,points);
		}
		else if(!strcmp(comm1, "licencja", true))
		{
			new giveplayer_id;
			if(sscanf(comm2, "d", giveplayer_id))
				return msg_usage(playerid,"U¿yj: /o(feruj) licencja [id gracza]");
		
			if(!IsPlayerOnDutyInGroup(playerid, GROUP_PD))
				return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na s³u¿bie odpowiedniej grupy.");
			if(GroupInfo[DutyGroup[playerid]][gLeader] != CharacterInfo[playerid][pUID])
				return msg_error(playerid,"Nie jesteœ liderem grupy!");
			if(!Logged[giveplayer_id])
				return msg_error(playerid,"Wybrany gracz nie jest zalogowany.");
			if(!PlayerToPlayer(5.0,playerid,giveplayer_id))
				return msg_error(playerid,"Wybrany gracz nie znajduje siê obok Ciebie.");
			if(CharacterInfo[giveplayer_id][pDocs] & DOC_WEAPONS)
				return msg_error(playerid, "Wybrany gracz posiada ju¿ licencje na broñ.");
			if(CharacterInfo[giveplayer_id][pCash] < SettingInfo[sDocWeapons])
				return msg_error(playerid, "Wybrany gracz nie posiada odpowiedniej iloœci gotówki.");
			
			Oferta(OFFER_DOCWEAPONS,playerid,giveplayer_id,SettingInfo[sDocWeapons],1);
		}
		else if(!strcmp(comm1, "leczenie", true))
		{
			new giveplayer_id, price;
			if(sscanf(comm2, "dd", giveplayer_id, price))
				return msg_usage(playerid,"U¿yj: /o(feruj) leczenie [id gracza] [cena]");
		
			if(!IsPlayerOnDutyInGroup(playerid, GROUP_MC))
				return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na s³u¿bie odpowiedniej grupy.");
			if(!Logged[giveplayer_id])
				return msg_error(playerid,"Wybrany gracz nie jest zalogowany.");
			if(!PlayerToPlayer(5.0,playerid,giveplayer_id))
				return msg_error(playerid,"Wybrany gracz nie znajduje siê obok Ciebie.");
			if(price < 0)
				return msg_error(playerid, "Kwota nie jest poprawna!");
			if(CharacterInfo[giveplayer_id][pCash] < price)
				return msg_error(playerid, "Wybrany gracz nie posiada odpowiedniej iloœci gotówki.");
			
			Oferta(OFFER_MEDICINE,playerid,giveplayer_id,price,1);
		}
		else if(!strcmp(comm1, "poczytalnosc", true))
		{
			new giveplayer_id;
			if(sscanf(comm2, "d", giveplayer_id))
				return msg_usage(playerid,"U¿yj: /o(feruj) poczytalnosc [id gracza]");
		
			if(!IsPlayerOnDutyInGroup(playerid, GROUP_MC))
				return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na s³u¿bie odpowiedniej grupy.");
			if(GroupInfo[DutyGroup[playerid]][gLeader] != CharacterInfo[playerid][pUID])
				return msg_error(playerid,"Nie jesteœ liderem grupy!");
			if(!Logged[giveplayer_id])
				return msg_error(playerid,"Wybrany gracz nie jest zalogowany.");
			if(!PlayerToPlayer(5.0,playerid,giveplayer_id))
				return msg_error(playerid,"Wybrany gracz nie znajduje siê obok Ciebie.");
			if(CharacterInfo[giveplayer_id][pDocs] & DOC_MED)
				return msg_error(playerid, "Wybrany gracz posiada ju¿ dokument o poczytalnoœci.");
			if(CharacterInfo[giveplayer_id][pCash] < SettingInfo[sDocMed])
				return msg_error(playerid, "Wybrany gracz nie posiada odpowiedniej iloœci gotówki.");
			
			Oferta(OFFER_DOCMED,playerid,giveplayer_id,SettingInfo[sDocMed],1);
		}
		else if(!strcmp(comm1, "reklama", true))
		{
			if(!IsPlayerOnDutyInGroup(playerid, GROUP_NEWS))
				return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na s³u¿bie odpowiedniej grupy.");
			if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 582 && !(DoorsInfo[PlayerDoor[playerid]][dOwner] == DutyGroup[playerid] && DoorsInfo[PlayerDoor[playerid]][dOwnerTyp]==OWNER_GROUP))
				return msg_error(playerid,"Aby nadaæ newsa musisz znajdowaæ siê w wozie transmisyjnym lub budynku radia.");
			new giveplayer_id, time, adv[96];
			if(sscanf(comm2, "dds[96]", giveplayer_id, time, adv))
				return msg_usage(playerid,"U¿yj: /o(feruj) reklama [id gracza] [czas trwania - minuty] [treœæ reklamy]");
		
			if(!Logged[giveplayer_id])
				return msg_error(playerid,"Wybrany gracz nie jest zalogowany.");
			if(!PlayerToPlayer(5.0,playerid,giveplayer_id))
				return msg_error(playerid,"Wybrany gracz nie znajduje siê obok Ciebie.");
			if(ON_AIR)
			{
				msg_infoFormat(playerid,128, "Aktualnie jest ju¿ nadawana reklama.\nPozosta³y czas: %d min",1+ON_AIR/60);
				return 1;
			}
			if(time < 1 || time > 180)
				return msg_error(playerid, "Wpisany czas reklamy nie jest prawid³owy. Maksymalnie 3 godziny.");
			if(strlen(adv)>110)
				return msg_error(playerid,"Treœc reklamy jest zbyt d³uga. (Max. 110 znaków)");
			if(adv[strlen(adv)-1]==' ')
				return msg_error(playerid,"Treœæ reklamy nie mo¿e koñczyæ siê spacj¹");
			ReplacePolishLetters(adv,strlen(adv));
			SetPVarString(playerid, "advert", adv);
			
			new price = SettingInfo[sLSNPrice]*time;
			
			Oferta(OFFER_ADVERT,playerid,giveplayer_id,price,time);
		}
		else if(!strcmp(comm1, "dokument", true))
		{
			if(!IsPlayerOnDutyInGroup(playerid, GROUP_GOV))
				return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na s³u¿bie odpowiedniej grupy.");
			
			new type[15], giveplayer_id;
			if(sscanf(comm2, "s[15]dd", type, giveplayer_id))
				return msg_usage(playerid,"U¿yj: /o(feruj) dokument [dowod | prawojazdy | licencjapilota] [ID gracza]");
			
			if(!Logged[giveplayer_id])
				return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
			
			if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
				return msg_error(playerid,"Wybrany gracz nie znajduje siê obok Ciebie.");
			
			if(!(DoorsInfo[PlayerDoor[playerid]][dOwner] == DutyGroup[playerid] && DoorsInfo[PlayerDoor[playerid]][dOwnerTyp] == OWNER_GROUP))
				return msg_error(playerid,"Musisz znajdowaæ siê w budynku GOV.");
			
			if(!strcmp(type, "dowod", true))
			{
				if(CharacterInfo[giveplayer_id][pDocs] & DOC_ID)
					return msg_error(playerid,"Wybrany gracz posiada ju¿ dowód osobisty.");
				
				if(CharacterInfo[giveplayer_id][pCash] < SettingInfo[sDocID])
					return msg_error(playerid,"Wybrany gracz nie posiada odpowiedniej kwoty.");
				
				Oferta(OFFER_DOCID,playerid,giveplayer_id,SettingInfo[sDocID],1);
			}
			else if(!strcmp(type, "prawojazdy", true))
			{
				if(CharacterInfo[giveplayer_id][pDocs] & DOC_DRIVER)
					return msg_error(playerid,"Wybrany gracz posiada ju¿ prawo jazdy.");
				
				if(CharacterInfo[giveplayer_id][pCash] < SettingInfo[sDocDriver])
					return msg_error(playerid,"Wybrany gracz nie posiada odpowiedniej kwoty.");
				
				if(CharacterInfo[giveplayer_id][pDriverPenalty])
				{
					new string[64];
					format(string, sizeof(string), "Po zabraniu prawa jazda musisz odczekaæ odpowiedni¹ iloœæ czasu (pozosta³o: %d minut).", CharacterInfo[playerid][pDriverPenalty]);
					msg_error(giveplayer_id, string);
					msg_error(playerid, "Gracz musi odczekaæ przed wyrobieniem kolejnego prawa jazdy.");
					return 1;
				}
				
				Oferta(OFFER_DOCDRIVER,playerid,giveplayer_id,SettingInfo[sDocDriver],1);
			}
			else if(!strcmp(type, "licencjapilota", true))
			{
				if(CharacterInfo[giveplayer_id][pDocs] & DOC_PILOT)
					return msg_error(playerid,"Wybrany gracz posiada ju¿ licencje pilota.");
				
				if(CharacterInfo[giveplayer_id][pCash] < SettingInfo[sDocPilot])
					return msg_error(playerid,"Wybrany gracz nie posiada odpowiedniej kwoty.");
				
				Oferta(OFFER_DOCPILOT,playerid,giveplayer_id,SettingInfo[sDocPilot],1);
			}
		}
		else if(!strcmp(comm1, "rejestracja", true))
		{
			if(!IsPlayerOnDutyInGroup(playerid, GROUP_GOV))
				return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na s³u¿bie odpowiedniej grupy.");
			
			new type[8],data[16];
			if(sscanf(comm2, "s[8]S()[16]", type,data))
				return msg_usage(playerid,"U¿yj: /o(feruj) rejestracja [pojazd | biznes]");
			
			if(!(DoorsInfo[PlayerDoor[playerid]][dOwner] == DutyGroup[playerid] && DoorsInfo[PlayerDoor[playerid]][dOwnerTyp] == OWNER_GROUP))
				return msg_error(playerid,"Musisz znajdowaæ siê w budynku GOV.");
			
			if(!strcmp(type, "pojazd", true))
			{
				new giveplayer_id, vehuid;
				if(sscanf(data, "dd", giveplayer_id, vehuid))
					return msg_usage(playerid,"U¿yj: /o(feruj) rejestracja pojazd [ID gracza] [UID pojazdu]");
				if(!Logged[giveplayer_id])
					return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
				
				if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
					return msg_error(playerid,"Wybrany gracz nie znajduje siê obok Ciebie.");
				
				if(!VehicleInfo[vehuid][vUID])
					return msg_error(playerid,"Nie znaleziono pojazdu o podanym UID.");
				
				if(CharacterInfo[giveplayer_id][pCash] < SettingInfo[sPlateCharge])
					return msg_error(playerid,"Wybrany gracz nie posiada odpowiedniej kwoty.");
				
				if(VehicleInfo[vehuid][vRegistered])
					return msg_error(playerid,"Wpisany pojazd jest ju¿ zarejestrowany");
				
				if((VehicleInfo[vehuid][vOwnerTyp] == OWNER_PLAYER && VehicleInfo[vehuid][vOwner] == CharacterInfo[giveplayer_id][pUID]) || (VehicleInfo[vehuid][vOwnerTyp] == OWNER_GROUP && GroupInfo[VehicleInfo[vehuid][vOwner]][gLeader] == CharacterInfo[giveplayer_id][pUID]))
					Oferta(OFFER_REGISTERCAR,playerid,giveplayer_id,SettingInfo[sPlateCharge],vehuid);
				else
					msg_error(playerid,"Pojazd o podanym UID nie mo¿e zostaæ zarejestrowany, wybrany gracz nie jest jego w³aœcicielem");
			}
			else if(!strcmp(type, "biznes", true))
			{
				new giveplayer_id, guid;
				if(sscanf(data, "dd", giveplayer_id, guid))
					return msg_usage(playerid,"U¿yj: /o(feruj) rejestracja biznes [ID gracza] [UID biznesu]");
				if(!Logged[giveplayer_id])
					return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
				
				if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
					return msg_error(playerid,"Wybrany gracz nie znajduje siê obok Ciebie.");
				
				if(!GroupInfo[guid][gUID])
					return msg_error(playerid,"Wprowadzono niepoprawne id grupy.");
				
				if(CharacterInfo[giveplayer_id][pCash] < SettingInfo[sGroupRegisterCharge])
					return msg_error(playerid,"Wybrany gracz nie posiada odpowiedniej kwoty.");
				
				if(GroupInfo[guid][gRegistered])
					return msg_error(playerid,"Wpisana grupa jest ju¿ zarejestrowana.");
				
				if(GroupInfo[guid][gLeader] == CharacterInfo[giveplayer_id][pUID])
					Oferta(OFFER_REGISTERGROUP,playerid,giveplayer_id,SettingInfo[sGroupRegisterCharge],guid);
				else
					msg_error(playerid,"Grupa o podanym UID nie mo¿e zostaæ zarejestrowana, wybrany gracz nie jest jej liderem.");
			}
		}
		else if(!strcmp(comm1, "karnet", true))
		{
			if(!IsPlayerOnDutyInGroup(playerid, GROUP_GYM))
				return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na s³u¿bie odpowiedniej grupy.");
			if(!(DoorsInfo[PlayerDoor[playerid]][dOwner] == DutyGroup[playerid] && DoorsInfo[PlayerDoor[playerid]][dOwnerTyp] == OWNER_GROUP))
				return msg_error(playerid,"Nie znajdujesz siê w si³owni.");
			
			new giveplayer_id,type;
			if(sscanf(comm2, "dd",giveplayer_id,type))
				return msg_usage(playerid,"U¿yj: /o(feruj) karnet [ID gracza] [typ]\n\nTypy:\n1. Jednorazowy\n2. Ca³odniowy\n3. Tygodniowy");
			if(type < 1 || type > 3)
				return msg_error(playerid,"Niepoprawny typ karnetu.");
			if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
				return msg_error(playerid,"Wybrany gracz nie znajduje siê obok Ciebie.");

			new query[128],bool:found;
			format(query,sizeof(query),"SELECT * FROM `srv_gym_pass` WHERE `player_uid`='%d' AND `groupid`='%d' AND `time`>'%d'",CharacterInfo[giveplayer_id][pUID],DutyGroup[playerid],gettime());
			mysql_query(query);
			mysql_store_result();
			if(mysql_num_rows())
				found=true;
			mysql_free_result();

			if(found || CharacterInfo[giveplayer_id][pGymPass]==DutyGroup[playerid])
				return msg_error(playerid,"Wybrany gracz posiada ju¿ karnet w tej si³owni.");

			if(type==1)
				type=OFFER_GYM_SINGLE;
			else if(type==2)
				type=OFFER_GYM_DAY;
			else if(type==3)
				type=OFFER_GYM_WEEK;

			Oferta(type, playerid, giveplayer_id, GetOfferPrice(DutyGroup[playerid],type), DutyGroup[playerid]);
		}
	}
	
	return 1;
}
CMD:o(playerid,params[]) return cmd_oferuj(playerid,params);

CMD:akceptuj(playerid,params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid, "Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new type = GetPVarInt(playerid, "OfferType");
	if(!GetPVarInt(playerid, "OfferUID") && type != OFFER_MANDAT)
		return msg_error(playerid, "Nie posiadasz aktywnej oferty.");
	new uid=GetPVarInt(playerid, "OfferUID");
	PlayerTextDrawHide(playerid, OFFER[playerid]);
	PlayerTextDrawHide(playerid, ACCEPT[playerid]);
	PlayerTextDrawHide(playerid, REJECT[playerid]);
	CancelSelectTextDraw(playerid);
	new price = GetPVarInt(playerid, "OfferPrice");
	new seller = GetPVarInt(playerid, "OfferSeller");
	
	DeletePVar(seller,"OfferBuyer");
	DeletePVar(playerid,"OfferType");
	
	if(type != OFFER_MANDAT && type != OFFER_REPAIR_ENG && type != OFFER_REPAIR_BODY && type != OFFER_REPAIR_TIRES && type != OFFER_REPAIR_ALL && type !=OFFER_PAINT && type != OFFER_PAINTJOB && type != OFFER_TUNING && type != OFFER_DISMOUNT)
	{
		DeletePVar(playerid,"OfferUID");
		DeletePVar(playerid,"OfferPrice");
		DeletePVar(playerid,"OfferSeller");
	}
	
	if(!PlayerToPlayer(5.0, playerid, seller))
		return msg_error(playerid, "Znajdujesz siê zbyt daleko od drugiego gracza!");
	
	if(type == OFFER_MANDAT || type == OFFER_REPAIR_ENG || type == OFFER_REPAIR_BODY || type == OFFER_REPAIR_TIRES || type == OFFER_REPAIR_ALL || type == OFFER_PAINT || type==OFFER_PAINTJOB || type==OFFER_TUNING || type==OFFER_DISMOUNT)
	{
		if(CharacterInfo[playerid][pCash] < price && CharacterInfo[playerid][pCredit] < price)
		{
			msg_error(playerid,"Nie posiadasz wystarczaj¹cej iloœci gotówki.");
			SendClientMessage(seller,COLOR_GREEN,"Oferta anulowana. Gracz nie posiada wystarczaj¹cej iloœci gotówki.");
			return 1;
		}
	}
	else
	{
		if(CharacterInfo[playerid][pCash] < price)
		{
			msg_error(playerid,"Nie posiadasz wystarczaj¹cej iloœci gotówki.");
			SendClientMessage(seller,COLOR_GREEN,"Oferta anulowana. Gracz nie posiada wystarczaj¹cej iloœci gotówki.");
			return 1;
		}
	}
	
	KillTimer(OfferTimer[playerid]);
	
	if(type == OFFER_ITEM)
	{
		if(ItemInfo[uid][iOwner] != CharacterInfo[seller][pUID] || ItemInfo[uid][iUsed])
			return msg_error(playerid, "Przedmiot nie jest mo¿liwy do wymiany - jest u¿ywany lub nie nale¿y do sprzedaj¹cego.");
		ItemInfo[uid][iOwner]=CharacterInfo[playerid][pUID];
		new query[128];
		format(query, sizeof(query), "UPDATE `srv_items` SET `owner`='%d' WHERE `UID`='%d' LIMIT 1",CharacterInfo[playerid][pUID],uid);
		mysql_query(query);
		SendClientMessageFormat(seller,COLOR_GREEN,"Transakcja zaakceptowana. Sprzeda³eœ przedmiot %s (UID: %d) graczowi %s (%d) za $%d.", ItemInfo[uid][iName], uid, PlayerName2(playerid), playerid, price);

		if(price > 500)
			SendAdminMessageFormat(COLOR_RED,"%s(%d) sprzeda³ %s(%d) przedmiot %s za $%d!",PlayerName3(seller),seller,PlayerName3(playerid),playerid,ItemInfo[uid][iName],price);
		
		format(query, sizeof(query), "INSERT INTO `srv_items_logs` VALUES (NULL, '%d','%d','%d','%d','%d','%d','%d')", CharacterInfo[seller][pUID], CharacterInfo[seller][pGID], CharacterInfo[playerid][pUID], CharacterInfo[playerid][pGID], uid, price, gettime());
		mysql_query(query);
		SendClientMessageFormat(playerid,COLOR_GREEN,"Transakcja zaakceptowana. Kupi³eœ przedmiot %s (UID: %d) za $%d.", ItemInfo[uid][iName], uid, price);
		
		format(query, sizeof(query), "podaje przedmiot %s.", ItemInfo[uid][iName]);
		cmd_me(seller, query);
		
		GivePlayerCash(seller,price);
		GivePlayerCash(playerid,-price);
	}
	else if(type==OFFER_VEHICLE)
	{
		VehicleInfo[uid][vOwner]=CharacterInfo[playerid][pUID];
		SaveVehicle(uid,SAVE_VEH_OWNER);
		SendClientMessageFormat(seller,COLOR_GREEN,"Transakcja zaakceptowana. Sprzeda³eœ pojazd %s (UID: %d) graczowi %s (%d) za $%d.", GetVehicleModelName(VehicleInfo[uid][vModel]), uid, PlayerName2(playerid), playerid, price);
		
		if(seller != playerid)
			SendClientMessageFormat(playerid,COLOR_GREEN,"Transakcja zaakceptowana. Kupi³eœ pojazd %s (UID: %d) za $%d.", GetVehicleModelName(VehicleInfo[uid][vModel]), uid, price);
		
		new string[128];
		format(string,sizeof(string),"[AI] %s(%d) sprzeda³ %s(%d) pojazd %s [UID:%d] za $%d.",PlayerName3(seller),seller,PlayerName3(playerid),playerid,GetVehicleModelName(VehicleInfo[uid][vModel]),uid, price);
		SendAdminMessage(COLOR_RED,string);

		format(string,sizeof(string),"INSERT INTO `srv_veh_logs` VALUES ('%d','%d','%d','%d','%d','%d','%d','1','%d')",CharacterInfo[seller][pUID], CharacterInfo[seller][pGID], CharacterInfo[playerid][pUID],CharacterInfo[playerid][pGID], price, uid, VehicleInfo[uid][vModel],gettime());
		mysql_query(string);

		GivePlayerCash(seller,price);
		GivePlayerCash(playerid,-price);
	}
	else if(type==OFFER_REPAIR_ENG || type==OFFER_REPAIR_BODY ||type==OFFER_REPAIR_TIRES || type==OFFER_REPAIR_ALL || type==OFFER_PAINT || type==OFFER_PAINTJOB || type==OFFER_TUNING || type==OFFER_DISMOUNT)
	{
		if(GroupInfo[DutyGroup[seller]][gType] != GROUP_WORKSHOP)
			return msg_error(playerid,"Wybrany gracz nie jest na s³u¿bie odpowiedniej grupy.");
		
		new string[128];
		format(string, sizeof(string), "1. Portfel ($%d)\n2. Konto bankowe ($%d)", CharacterInfo[playerid][pCash], CharacterInfo[playerid][pCredit]);
		
		new title[64];
		format(title, sizeof(title), DEF_NAME" » usluga ($%d)", GetPVarInt(playerid, "OfferPrice"));
		
		SetPVarInt(playerid, "WorkshopTypeOfWork", type);
		
		ShowPlayerDialog(playerid, D_WORKSHOP_ACCEPT, DIALOG_STYLE_LIST, title, string, "Wybierz", "Anuluj");
	}
	else if(type == OFFER_HOUSE)
	{
		new doorname[31];
		DoorsInfo[uid][dOwner] = CharacterInfo[playerid][pUID];
		format(doorname, sizeof(doorname), "[DOM] %s", PlayerName3(playerid));
		DoorsInfo[uid][dName] = doorname;
		SaveDoors(uid, SAVE_DOORS_BASIC);
		
		SendClientMessageFormat(seller,COLOR_GREEN,"Transakcja zaakceptowana. Sprzeda³eœ dom (UID: %d) graczowi %s (%d) za $%d.", uid, PlayerName2(playerid), playerid, price);
		
		if(seller != playerid)
			SendClientMessageFormat(playerid,COLOR_GREEN,"Transakcja zaakceptowana. Kupi³eœ dom (UID: %d) za $%d.", uid, price);
		
		GivePlayerCash(seller,price);
		GivePlayerCash(playerid,-price);
	}
	else if(type == OFFER_VCARD)
	{
		new query[128],i;
		format(query,sizeof(query),"SELECT * FROM `srv_vcards` WHERE `phone_uid`='%d' AND `number`='%d'",CharacterInfo[playerid][pPhone],ItemInfo[CharacterInfo[seller][pPhone]][iValue1]);
		mysql_query(query);
		mysql_store_result();
		if(mysql_num_rows())
		{
			i++;
			msg_info(playerid,"Posiadasz ju¿ ten numer.");
		}
		else
		{
			format(query,sizeof(query),"INSERT INTO `srv_vcards` VALUES (NULL,'%d','%d','%s')",CharacterInfo[playerid][pPhone],ItemInfo[CharacterInfo[seller][pPhone]][iValue1],PlayerName3(seller));
			mysql_query(query);
		}
		mysql_free_result();

		format(query,sizeof(query),"SELECT * FROM `srv_vcards` WHERE `phone_uid`='%d' AND `number`='%d'",CharacterInfo[seller][pPhone],ItemInfo[CharacterInfo[playerid][pPhone]][iValue1]);
		mysql_query(query);
		mysql_store_result();
		if(mysql_num_rows())
		{
			i++;
			msg_info(seller,"Posiadasz ju¿ ten numer.");
		}
		else
		{
			format(query,sizeof(query),"INSERT INTO `srv_vcards` VALUES (NULL,'%d','%d','%s')",CharacterInfo[seller][pPhone],ItemInfo[CharacterInfo[playerid][pPhone]][iValue1],PlayerName3(playerid));
			mysql_query(query);
		}
		mysql_free_result();

		if(i!=2)
		{
			format(query,sizeof(query),"i %s wymienili siê kontaktami.",PlayerName2(playerid));
			cmd_me(seller,query);
		}
	}
	else if(type==OFFER_TAXI)
	{
		if(seller)
			SetPVarInt(playerid, "pTaxiDriver", seller);
		else
			SetPVarInt(playerid, "pTaxiDriver", -1);
		SetPVarFloat(seller,"pTaxiPrice",float(price)/10.0);
		CharacterInfo[seller][pTaxiPassenger]=playerid;
		CharacterInfo[seller][pTaxiDistance]=0;
		GameTextForPlayer(seller, "~g~Oferta zaakceptowana", 3000, 4);
		Tip(playerid,5,"Mozesz takze zaznaczyc punkt docelowy na mapie.");
	}
	else if(type == OFFER_MANDAT)
	{
		if(GroupInfo[DutyGroup[seller]][gType] != GROUP_PD)
			return msg_error(playerid,"Wybrany gracz nie jest na s³u¿bie odpowiedniej grupy.");
		
		new string[128];
		format(string, sizeof(string), "1. Portfel ($%d)\n2. Konto bankowe ($%d)", CharacterInfo[playerid][pCash], CharacterInfo[playerid][pCredit]);
		
		new title[64];
		format(title, sizeof(title), DEF_NAME" » mandat ($%d)", GetPVarInt(playerid, "OfferPrice"));
		
		ShowPlayerDialog(playerid, D_MANDAT_ACCEPT, DIALOG_STYLE_LIST, title, string, "Wybierz", "Anuluj");
	}
	else if(type == OFFER_ADVERT)
	{
		if(GroupInfo[DutyGroup[seller]][gType] != GROUP_NEWS)
			return msg_error(playerid,"Wybrany gracz nie jest na s³u¿bie odpowiedniej grupy.");
		
		new adv[128];
		GetPVarString(seller, "advert", adv, 128);
		
		if(seller != playerid)
			SendClientMessageFormat(playerid,COLOR_GREEN,"Oferta reklamy zaakceptowana. Kwota: $%d, czas trwania: %d min.", price, uid);

		GivePlayerCash(playerid,-price);
		
		new commission=GetMemberCommission(seller,DutyGroup[seller]);
		if(commission)
		{
			commission=floatround( (float(price)/100.0) * float(commission));
			price-=commission;
			CharacterInfo[seller][pCredit] += commission;
			SavePlayerStats(seller,SAVE_PLAYER_BASIC);
			SendClientMessageFormat(seller,COLOR_GREEN,"Oferta zaakceptowana. Kwota: $%d, czas trwania: %d min. Twoja prowizja: $%d. ", price, uid,commission);
		}
		else
			SendClientMessageFormat(seller,COLOR_GREEN,"Oferta reklamy zaakceptowana. Kwota: $%d, czas trwania: %d min.", price, uid);

		GiveGroupCash(DutyGroup[seller],price);
		
		LogGroupOffer(seller,DutyGroup[seller],"Reklama",price,playerid);
		
		ON_AIR = uid*60;

		format(advreklama, sizeof(advreklama), "~y~~h~SANN ~w~~>~ %s: %s", PlayerName3(seller), adv);

		TextDrawSetString(TD_LSN, advreklama);
	}
	else if(type == OFFER_DOCID)
	{
		if(GroupInfo[DutyGroup[seller]][gType] != GROUP_GOV)
			return msg_error(playerid,"Wybrany gracz nie jest na s³u¿bie odpowiedniej grupy.");
		
		SendClientMessageFormat(seller,COLOR_GREEN,"Oferta dowodu osobistego zaakceptowana. Kwota: $%d.", price);
		
		if(seller != playerid)
			SendClientMessageFormat(playerid,COLOR_GREEN,"Oferta dowodu osobistego zaakceptowana. Kwota: $%d.", price);
		
		GiveGroupCash(DutyGroup[seller],price);
		GivePlayerCash(playerid,-price);
		LogGroupOffer(seller,DutyGroup[seller],"Dowod osobisty",price,playerid);
		
		CharacterInfo[playerid][pDocs] += DOC_ID;
		SavePlayerStats(playerid, SAVE_PLAYER_OPTION);
	}
	else if(type == OFFER_DOCDRIVER)
	{
		if(GroupInfo[DutyGroup[seller]][gType] != GROUP_GOV)
			return msg_error(playerid,"Wybrany gracz nie jest na s³u¿bie odpowiedniej grupy.");
		
		SendClientMessageFormat(seller,COLOR_GREEN,"Oferta prawa jazdy zaakceptowana. Kwota: $%d.", price);
		
		if(seller != playerid)
			SendClientMessageFormat(playerid,COLOR_GREEN,"Oferta prawa jazdy zaakceptowana. Kwota: $%d.", price);
		
		GiveGroupCash(DutyGroup[seller],price);
		GivePlayerCash(playerid,-price);
		LogGroupOffer(seller,DutyGroup[seller],"Prawo jazdy",price,playerid);
		
		CharacterInfo[playerid][pDocs] += DOC_DRIVER;
		SavePlayerStats(playerid, SAVE_PLAYER_OPTION);
	}
	else if(type == OFFER_DOCPILOT)
	{
		if(GroupInfo[DutyGroup[seller]][gType] != GROUP_GOV)
			return msg_error(playerid,"Wybrany gracz nie jest na s³u¿bie odpowiedniej grupy.");
		
		SendClientMessageFormat(seller,COLOR_GREEN,"Oferta licencji pilota zaakceptowana. Kwota: $%d.", price);
		
		if(seller != playerid)
			SendClientMessageFormat(playerid,COLOR_GREEN,"Oferta licencji pilota zaakceptowana. Kwota: $%d.", price);
		
		GiveGroupCash(DutyGroup[seller],price);
		GivePlayerCash(playerid,-price);
		LogGroupOffer(seller,DutyGroup[seller],"Licencja pilota",price,playerid);
		
		CharacterInfo[playerid][pDocs] += DOC_PILOT;
		SavePlayerStats(playerid, SAVE_PLAYER_OPTION);
	}
	else if(type == OFFER_DOCWEAPONS)
	{
		if(GroupInfo[DutyGroup[seller]][gType] != GROUP_PD)
			return msg_error(playerid,"Wybrany gracz nie jest na s³u¿bie odpowiedniej grupy.");
		
		SendClientMessageFormat(seller,COLOR_GREEN,"Oferta licencji na broñ zaakceptowana. Kwota: $%d.", price);
		
		if(seller != playerid)
			SendClientMessageFormat(playerid,COLOR_GREEN,"Oferta licencji na broñ zaakceptowana. Kwota: $%d.", price);
		
		GiveGroupCash(DutyGroup[seller],price);
		GivePlayerCash(playerid,-price);
		LogGroupOffer(seller,DutyGroup[seller],"Licencja na broñ",price,playerid);
		
		CharacterInfo[playerid][pDocs] += DOC_WEAPONS;
		SavePlayerStats(playerid, SAVE_PLAYER_OPTION);
	}
	else if(type == OFFER_DOCMED)
	{
		if(GroupInfo[DutyGroup[seller]][gType] != GROUP_MC)
			return msg_error(playerid,"Wybrany gracz nie jest na s³u¿bie odpowiedniej grupy.");
		
		SendClientMessageFormat(seller,COLOR_GREEN,"Oferta dokumentu o poczytalnoœci zaakceptowana. Kwota: $%d.", price);
		
		if(seller != playerid)
			SendClientMessageFormat(playerid,COLOR_GREEN,"Oferta dokumentu o poczytalnoœci zaakceptowana. Kwota: $%d.", price);
		
		GiveGroupCash(DutyGroup[seller],price);
		GivePlayerCash(playerid,-price);
		LogGroupOffer(seller,DutyGroup[seller],"Dokument o poczytalnoœci",price,playerid);
		
		CharacterInfo[playerid][pDocs] += DOC_MED;
		SavePlayerStats(playerid, SAVE_PLAYER_OPTION);
	}
	else if(type == OFFER_REGISTERCAR)
	{
		if(GroupInfo[DutyGroup[seller]][gType] != GROUP_GOV)
			return msg_error(playerid,"Wybrany gracz nie jest na s³u¿bie odpowiedniej grupy.");
		
		SendClientMessageFormat(seller,COLOR_GREEN,"Oferta rejestracji pojazdu zaakceptowana. Kwota: $%d.", price);
		
		if(seller != playerid)
			SendClientMessageFormat(playerid,COLOR_GREEN,"Oferta rejestracji pojazdu zaakceptowana. Kwota: $%d.", price);
		
		GiveGroupCash(DutyGroup[seller],price);
		GivePlayerCash(playerid,-price);
		LogGroupOffer(seller,DutyGroup[seller],"Rejestracja pojazdu",price,playerid);
		
		VehicleInfo[uid][vRegistered] = 1;
		
		new tablica[8];
		format(tablica, sizeof(tablica), "LS-%04d", uid);
		VehicleInfo[uid][vRegister] = tablica;
		
		SaveVehicle(uid, SAVE_VEH_BASIC);
	}
	else if(type == OFFER_REGISTERGROUP)
	{
		if(GroupInfo[DutyGroup[seller]][gType] != GROUP_GOV)
			return msg_error(playerid,"Wybrany gracz nie jest na s³u¿bie odpowiedniej grupy.");
		
		SendClientMessageFormat(seller,COLOR_GREEN,"Oferta rejestracji biznesu zaakceptowana. Kwota: $%d.", price);
		
		if(seller != playerid)
			SendClientMessageFormat(playerid,COLOR_GREEN,"Oferta rejestracji biznesu zaakceptowana. Kwota: $%d.", price);
		
		GiveGroupCash(DutyGroup[seller],price);
		GivePlayerCash(playerid,-price);
		LogGroupOffer(seller,DutyGroup[seller],"Rejestracja biznesu",price,playerid);
		
		GroupInfo[uid][gRegistered] = 1;
		SaveGroup(uid, SAVE_GROUP_BASIC);
	}
	else if(type == OFFER_GYM_SINGLE || type == OFFER_GYM_DAY || type==OFFER_GYM_WEEK)
	{
		if(GroupInfo[DutyGroup[seller]][gType] != GROUP_GYM)
			return msg_error(playerid,"Pracownik nie jest na s³u¿bie odpowiedniej grupy.");
		new commission=GetMemberCommission(seller,DutyGroup[seller]);
		GivePlayerCash(playerid,-price);
		if(commission)
		{
			commission=floatround( (float(price)/100.0) * float(commission));
			price-=commission;
			CharacterInfo[seller][pCredit] += commission;
			SavePlayerStats(seller,SAVE_PLAYER_BASIC);
			msg_infoFormat(seller,128,"Oferta zaakceptowana. Na konto grupy wp³ynê³o $%d\nTwoja prowizja: $%d. ", price,commission);
		}
		else
			SendClientMessageFormat(seller,COLOR_GREEN,"Oferta zaakceptowana. Na konto grupy wp³ynê³o: $%d", price);
		GiveGroupCash(DutyGroup[seller],price);
		CharacterInfo[playerid][pGymPass]=DutyGroup[seller];
		if(type==OFFER_GYM_SINGLE)
		{
			LogGroupOffer(seller,DutyGroup[seller],"Karnet jednorazowy",price,playerid);
			msg_info(playerid,"Zakupi³eœ karnet jednorazowy. Aby rozpocz¹æ trening u¿yj /cwiczenia.");
		}
		else if(type==OFFER_GYM_DAY)
		{
			LogGroupOffer(seller,DutyGroup[seller],"Karnet jednodniowy",price,playerid);

			msg_info(playerid,"Zakupi³eœ karnet ca³odniowy. Aby rozpocz¹æ trening u¿yj /cwiczenia.");
			new query[128];
			format(query,sizeof(query),"INSERT INTO `srv_gym_pass` VALUES (NULL,'%d','%d','%d')",CharacterInfo[playerid][pUID],DutyGroup[seller],gettime()+86400);
			mysql_query(query);
		}
		else if(type==OFFER_GYM_WEEK)
		{
			LogGroupOffer(seller,DutyGroup[seller],"Karnet tygodniowy",price,playerid);

			msg_info(playerid,"Zakupi³eœ karnet tygodniowy. Aby rozpocz¹æ trening u¿yj /cwiczenia.");
			new query[128];
			format(query,sizeof(query),"INSERT INTO `srv_gym_pass` VALUES (NULL,'%d','%d','%d')",CharacterInfo[playerid][pUID],DutyGroup[seller],gettime()+(604800));
			mysql_query(query);
		}
	}
	else if(type == OFFER_RESTAURANT_ITEM)
	{
		if(GroupInfo[DutyGroup[seller]][gType] != GROUP_RESTAURANT && GroupInfo[DutyGroup[seller]][gType] != GROUP_GYM && GroupInfo[DutyGroup[seller]][gType] != GROUP_KLUB && GroupInfo[DutyGroup[seller]][gType] != GROUP_GUNSHOP)
			return msg_error(playerid, "Wybrany gracz nie jest na s³u¿bie odpowiedniej grupy.");

		new uid2 = StworzPrzedmiot(OWNER_PLAYER, CharacterInfo[playerid][pUID], ItemInfo[uid][iName], ItemInfo[uid][iType], ItemInfo[uid][iValue1], ItemInfo[uid][iValue2], 1);
		ItemInfo[uid][iIlosc]--;
		if(ItemInfo[uid][iIlosc] < 1)
			DeleteItem(uid);
		else
		{
			new query[128];
			format(query,sizeof(query),"UPDATE `srv_items` SET `ilosc` = '%d' WHERE `UID` = '%d'",ItemInfo[uid][iIlosc], uid);
			mysql_query(query);
		}
		new commission = GetMemberCommission(seller, DutyGroup[seller]);
		GivePlayerCash(playerid, -price);
		GiveGroupCash(DutyGroup[seller], price);
		msg_infoFormat(playerid, 96, "Zakupi³eœ przedmiot %s za $%d.", ItemInfo[uid][iName], price);
		
		if(commission)
		{
			commission = floatround( (float(price)/100.0) * float(commission));
			price -= commission;
			CharacterInfo[seller][pCredit] += commission;
			SavePlayerStats(seller, SAVE_PLAYER_BASIC);
			msg_infoFormat(seller, 128, "Oferta zaakceptowana. Na konto grupy wp³ynê³o $%d\nTwoja prowizja: $%d. ", price, commission);
		}
		else
			msg_infoFormat(seller, 96, "Oferta zaakceptowana. Na konto grupy wp³ynê³o: $%d", price);

		if(ItemInfo[uid2][iType] == 1 && ItemInfo[uid2][iValue1] >= 22 && ItemInfo[uid2][iValue1] != 41)
		{
			new query[128];
			format(query, sizeof(query), "INSERT INTO `srv_legal_weapons` VALUES ('%d', '%d', '%d', '%d', '%d')", uid2, CharacterInfo[playerid][pUID],CharacterInfo[playerid][pGID],CharacterInfo[seller][pUID], gettime());
			mysql_query(query);
		}
		
		LogGroupOffer(seller, DutyGroup[seller], "Sprzedaz", price, playerid);
	}
	else if(type == OFFER_MEDICINE)
	{
		if(GroupInfo[DutyGroup[seller]][gType] != GROUP_MC)
			return msg_error(playerid,"Wybrany gracz nie jest na s³u¿bie odpowiedniej grupy.");
		
		GivePlayerCash(playerid, -price);
		GiveGroupCash(DutyGroup[seller], (price/10)*8);
		GivePlayerCash(seller, price/5);
		
		LogGroupOffer(seller,DutyGroup[seller],"Leczenie",price,playerid);
		
		SetPlayerHP(playerid, 100.0);
		
		if(CharacterInfo[playerid][pLastWEAP])
		{
			CharacterInfo[playerid][pLastDMG] = 0;
			CharacterInfo[playerid][pLastWEAP] = 0;
			CharacterInfo[playerid][pLastHB] = 0;
		}
		
		msg_infoFormat(playerid, 128, "Zosta³eœ uleczony przez medyka %s.", PlayerName2(seller));
		SendClientMessageFormat(seller, COLOR_GREEN, "Pomyœlnie uleczy³eœ gracza %s.", PlayerName2(playerid));
	}
	else if(type==OFFER_VEHICLE_KOMIS)
	{
		if(!DutyGroup[seller] || GroupInfo[DutyGroup[seller]][gType] != GROUP_CARDEALER)
			return msg_error(playerid, "Sprzedaj¹cy nie jest na odpowiedniej s³u¿bie.");
		
		VehicleInfo[uid][vOwner] = CharacterInfo[playerid][pUID];
		VehicleInfo[uid][vOwnerTyp] = OWNER_PLAYER;
		SaveVehicle(uid,SAVE_VEH_OWNER);
		SendClientMessageFormat(seller,COLOR_GREEN,"Transakcja zaakceptowana. Sprzeda³eœ pojazd %s (UID: %d) graczowi %s (%d) za $%d.", GetVehicleModelName(VehicleInfo[uid][vModel]), uid, PlayerName2(playerid), playerid, price);
		
		if(seller != playerid)
			SendClientMessageFormat(playerid,COLOR_GREEN,"Transakcja zaakceptowana. Kupi³eœ pojazd %s (UID: %d) za $%d.", GetVehicleModelName(VehicleInfo[uid][vModel]), uid, price);
		
		new string[128];
		format(string,sizeof(string),"[AI] %s(%d) sprzeda³ %s(%d) pojazd %s [UID:%d] za $%d.",PlayerName3(seller),seller,PlayerName3(playerid),playerid,GetVehicleModelName(VehicleInfo[uid][vModel]),uid, price);
		SendAdminMessage(COLOR_RED,string);

		format(string,sizeof(string),"INSERT INTO `srv_veh_logs` VALUES ('%d','%d','%d','%d','%d','%d','%d','2','%d')", CharacterInfo[seller][pUID], DutyGroup[seller], CharacterInfo[playerid][pUID], CharacterInfo[playerid][pGID], price, uid, VehicleInfo[uid][vModel], gettime());
		mysql_query(string);
		
		new string2[32];
		format(string2, sizeof(string2), "Sprzeda¿ pojazdu [UID: %d]", uid);
		LogGroupOffer(seller,DutyGroup[seller],string2,price,playerid);
		
		GiveGroupCash(DutyGroup[seller], price);
		GivePlayerCash(playerid, -price);
	}
	else if(type == OFFER_YO)
	{
		if(!PlayerToPlayer(2.0, seller, playerid))
			return msg_error(playerid,"Nie znajdujesz si? w pobli?u wybranego gracza.");

		new Float:p1x,Float:p1y,Float:p2x,Float:p2y,Float:tmp;
		GetPlayerPos(seller,p1x,p1y,tmp);
		GetPlayerPos(playerid,p2x,p2y,tmp);
		SetPlayerLookAt(seller, p2x, p2y);
		SetPlayerLookAt(playerid, p1x, p1y);
		ApplyAnimation(playerid, "GANGS", "HNDSHKAA", 4.1, 0, 0, 0, 0, 0, 1);
		ApplyAnimation(seller, "GANGS", "HNDSHKAA", 4.1, 0, 0, 0, 0, 0, 1);
	}

	
	return 1;
}

CMD:odrzuc(playerid,params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!GetPVarInt(playerid,"OfferUID"))
		return msg_error(playerid,"Nie posiadasz aktywnej oferty.");
	KillTimer(OfferTimer[playerid]);
	//new uid=GetPVarInt(playerid,"OfferUID");
	PlayerTextDrawHide(playerid, OFFER[playerid]);
	PlayerTextDrawHide(playerid, ACCEPT[playerid]);
	PlayerTextDrawHide(playerid, REJECT[playerid]);
	CancelSelectTextDraw(playerid);
	new seller = GetPVarInt(playerid,"OfferSeller");
	DeletePVar(playerid,"OfferUID");
	DeletePVar(seller,"OfferBuyer");
	DeletePVar(playerid,"OfferPrice");
	DeletePVar(playerid,"OfferSeller");
	DeletePVar(playerid,"OfferType");
	SendClientMessage(seller,COLOR_GREEN,"Gracz odrzuci³ ofertê.");
	SendClientMessage(playerid,COLOR_GREEN,"Oferta odrzucona.");

	return 1;
}

CMD:bagaznik(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new vehid = GetClosestVehicle(playerid);
	new vehuid = GetVehicleUID(vehid);
	
	if(!vehuid) return 1;
	if(IsABike(vehid) || IsABoat(vehid) || IsAPlane(vehid))
		return 1;
	
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER) return 1;
	
	if(!VehicleInfo[vehuid][vLocked])
	{
		if(VehicleInfo[vehuid][vOwnerTyp] == OWNER_GROUP && !IsOwnerVehicle(playerid, vehuid)) return 1;
		SetPVarInt(playerid, "BagaznikID", vehid);
		
		ShowPlayerDialog(playerid, D_BAGAZNIK, DIALOG_STYLE_LIST, DEF_NAME" » baga¿nik", "1. Wyci¹gnij przedmiot z baga¿nika\n2. Od³ó¿ przedmiot w baga¿niku", "Wybierz", "Anuluj");
	}
	else
		Tip(playerid, 3, "Pojazd jest zamkniêty.");
	
	return 1;
}

CMD:boombox(playerid, params[])
{
	if(!PlayerHaveItemType(playerid, ITEM_TYPE_BOOMBOX))
		return msg_error(playerid,"Nie posiadasz przy sobie boomboxa.");
	if(!CanMove(playerid))
		return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
	new boomboxid=GetPlayerItemTypeID(playerid,ITEM_TYPE_BOOMBOX);
	if(!GetPVarType(playerid, "BoomboxObject"))
	{
		if(sscanf(params, "s[256]", params))
		{
			new stations[512];
			ForeachEx(i,sizeof(RadioStations))
			{
				format(stations, sizeof(stations), "%s%s\n", stations,RadioStations[i][radioName]);
			}
			format(stations, sizeof(stations), "%sW³asny link",stations);
			ShowPlayerDialog(playerid,D_BOOMBOX,DIALOG_STYLE_LIST,DEF_NAME" » boombox",stations,"Wybierz","Anuluj");
			return 1;
		}
		ForeachPlayer(i)
			if(GetPVarType(i, "BoomboxObject"))
				if(IsPlayerInRangeOfPoint(playerid, 30.0, GetPVarFloat(i, "bposX"), GetPVarFloat(i, "bposY"), GetPVarFloat(i, "bposZ")))
					return msg_error(playerid,"W pobli¿y znajduje siê inny boombox.");
		
		new Float:x, Float:y, Float:z, Float:a;
		GetPlayerPos(playerid, x, y, z); GetPlayerFacingAngle(playerid, a);
		SetPVarInt(playerid, "BoomboxObject", CreateDynamicObject(2226, x, y, z-1.0, 0.0, 0.0, a+180.0,GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid)));
		SetPVarFloat(playerid, "bposX", x); SetPVarFloat(playerid, "bposY", y); SetPVarFloat(playerid, "bposZ", z);
		SetPVarInt(playerid, "bboxareaid", CreateDynamicSphere(x, y, z, 30.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid)));
		msg_info(playerid,"Boombox ustawiony pomyœlnie.");
		ApplyAnimation( playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 1 );
		cmd_me(playerid,"ustawia boombox na ziemi.");
		ForeachPlayer(i)
			if(IsPlayerInDynamicArea(i, GetPVarInt(playerid, "bboxareaid")) && !(CharacterInfo[i][pStatus] & STATUS_MP3) )
				PlayAudioStreamForPlayer(i, params, GetPVarFloat(playerid, "bposX"), GetPVarFloat(playerid, "bposY"), GetPVarFloat(playerid, "bposZ"), 30.0, 1);
		
		SetPVarString(playerid, "BoomboxURL", params);
		ItemInfo[boomboxid][iUsed]=1;
	}
	else
	{
		DestroyDynamicObject(GetPVarInt(playerid, "BoomboxObject"));
		DeletePVar(playerid, "BoomboxObject"); DeletePVar(playerid, "BoomboxURL");
		DeletePVar(playerid, "bposX"); DeletePVar(playerid, "bposY"); DeletePVar(playerid, "bposZ");
		if(GetPVarType(playerid, "bboxareaid"))
		{
			ForeachPlayer(i)
				if(IsPlayerInDynamicArea(i, GetPVarInt(playerid, "bboxareaid")) && !(CharacterInfo[i][pStatus] & STATUS_MP3) )
					StopAudioStreamForPlayer(i);
			
			DeletePVar(playerid, "bboxareaid");
		}
		ItemInfo[boomboxid][iUsed]=0;
		msg_info(playerid,"Boombox zosta³ usuniêty.");
	}
	return 1;
}

CMD:qs(playerid, params[])
{
	if(! (CharacterInfo[playerid][pTog] & TOG_QS))
		CharacterInfo[playerid][pTog] += TOG_QS;
	SavePlayerStats(playerid, SAVE_PLAYER_OPTION);
	SavePlayerStats(playerid, SAVE_PLAYER_POS);
	KickWithWait(playerid);
	return 1;
}

CMD:bank(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new doorid = PlayerDoor[playerid];
	if(!doorid)
		return msg_error(playerid, "Nie znajdujesz siê w banku.");
	new doorgroupid = DoorsInfo[doorid][dOwner];
	
	if(DoorsInfo[doorid][dOwnerTyp] != OWNER_GROUP || GroupInfo[doorgroupid][gType] != GROUP_BANK)
		return msg_error(playerid, "Nie znajdujesz siê w banku.");
	
	new comm1[32], comm2[32];
	if(sscanf(params, "s[32]S()[32]", comm1, comm2))
		return msg_usage(playerid,"U¿yj: /bank [stan | wplac | wyplac | przelew]");
	else
	{
		if(!strcmp(comm1, "stan", true))
		{
			new string[128];
			format(string, sizeof(string), "Obecny stan konta bankowego: $%d.", CharacterInfo[playerid][pCredit]);
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » bank - stan konta", string, "Zamknij", "");
		}
		else if(!strcmp(comm1, "wplac", true))
		{
			new cash;
			if(sscanf(comm2, "d", cash))
				return msg_usage(playerid,"U¿yj: /bank wplac [kwota]");
			else
			{
				if(cash < 1)
					return msg_error(playerid, "Nie mo¿esz wp³aciæ takiej kwoty.");
				else if(CharacterInfo[playerid][pCash] < cash)
					return msg_error(playerid, "Nie masz tylu pieniêdzy przy sobie!");
				
				CharacterInfo[playerid][pCredit] += cash;
				GivePlayerCash(playerid, -cash);
				SavePlayerStats(playerid,SAVE_PLAYER_BASIC);
				
				SendClientMessageFormat(playerid, COLOR_GREEN, "[BANK] Pomyslnie wp³aci³eœ $%d na konto bankowe.", cash);
			}
		}
		else if(!strcmp(comm1, "wyplac", true))
		{
			new cash;
			if(sscanf(comm2, "d", cash))
				return msg_usage(playerid,"U¿yj: /bank wyplac [kwota]");
			else
			{
				if(cash < 1)
					return msg_error(playerid, "Nie mo¿esz wyp³aciæ takiej kwoty.");
				else if(CharacterInfo[playerid][pCredit] < cash)
					return msg_error(playerid, "Nie masz tylu pieniêdzy na koncie bankowym!");
				
				CharacterInfo[playerid][pCredit] -= cash;
				GivePlayerCash(playerid, cash);
				SavePlayerStats(playerid,SAVE_PLAYER_BASIC);
				
				SendClientMessageFormat(playerid, COLOR_GREEN, "[BANK] Pomyslnie wyp³aci³eœ $%d z konta bankowego.", cash);
			}
		}
		else if(!strcmp(comm1, "przelew", true))
		{
			new option[16], id, cash;
			if(sscanf(comm2, "s[16]dd", option, id, cash))
				return msg_usage(playerid,"U¿yj: /bank przelew [gracz | grupa] [id] [kwota]");
			else
			{
				if(!strcmp(option, "gracz", true))
				{
					if(playerid==id)
						return msg_error(playerid,"Nie mo¿esz wys³aæ przelewu do samego siebie.");
					if(!Logged[id])
						return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");

					if(CharacterInfo[playerid][pHours]< 2 || CharacterInfo[id][pHours] < 2)
						return msg_error(playerid,"Jedna z postaci ma mniej ni¿ 2 godziny online.");
					
					if(cash < 1)
						return msg_error(playerid, "Nie mo¿esz przelaæ takiej kwoty.");
					else if(CharacterInfo[playerid][pCredit] < cash)
						return msg_error(playerid, "Nie masz tylu pieniêdzy na koncie bankowym!");
					
					CharacterInfo[playerid][pCredit] -= cash;
					CharacterInfo[id][pCredit] += cash;
					
					SavePlayerStats(playerid, SAVE_PLAYER_BASIC);
					SavePlayerStats(id, SAVE_PLAYER_BASIC);
					
					new string[128];
					format(string,sizeof(string),"INSERT INTO `srv_cash_logs` VALUES ('%d','%d','%d','%d','%d',1,'%d')",CharacterInfo[playerid][pUID],CharacterInfo[playerid][pGID],CharacterInfo[id][pUID],CharacterInfo[id][pGID],cash,gettime());
					mysql_query(string);

					format(string,sizeof(string),"[BANK] Przela³eœ kwotê $%d na konto %s.", cash, PlayerName2(id));
					SendClientMessage(playerid, COLOR_GREEN, string);
					format(string,sizeof(string),"[BANK] Otrzyma³eœ przelew w wysokoœci $%d od %s.", cash, PlayerName2(playerid));
					SendClientMessage(id, COLOR_GREEN, string);
				}	
				else if(!strcmp(option, "grupa", true))
				{
					if(CharacterInfo[playerid][pHours]< 2)
						return msg_error(playerid,"Postaæ ma mniej, ni¿ 2 godziny online.");
					if(!GroupInfo[id][gUID])
						return msg_error(playerid,"Wybrana grupa nie istnieje.");
					if(!(GroupInfo[id][gFlags] & FLAG_CASH))
						return msg_error(playerid,"Wybrana grupa nie posiada konta bankowego.");
					if(cash < 1)
						return msg_error(playerid, "Nie mo¿esz przelaæ takiej kwoty.");
					else if(CharacterInfo[playerid][pCredit] < cash)
						return msg_error(playerid, "Nie masz tylu pieniêdzy na koncie bankowym!");
					
					CharacterInfo[playerid][pCredit] -= cash;
					SavePlayerStats(playerid,SAVE_PLAYER_BASIC);
					GroupInfo[id][gCash] += cash;
					
					SaveGroup(id, SAVE_GROUP_BASIC);
					new string[128];
					format(string,sizeof(string),"INSERT INTO `srv_cash_logs` VALUES ('%d','%d','%d',0,'%d',2,'%d')",CharacterInfo[playerid][pUID],CharacterInfo[playerid][pGID],id,cash,gettime());
					mysql_query(string);
					
					format(string,sizeof(string),"[BANK] Przela³eœ kwotê $%d na konto grupy %s.", cash, GroupInfo[id][gName]);
					SendClientMessage(playerid, COLOR_GREEN, string);
					LogGroupOffer(playerid, id, "Wplata srodkow na konto", cash);
				}
			}
		}
	}
	
	return 1;
}
CMD:pokaz(playerid,params[])
{
	if(!CanMove(playerid))
		return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
	new comm1[32], comm2[32];
	if(sscanf(params, "s[32]S()[32]", comm1, comm2))
	{
		msg_usage(playerid, "U¿yj: /poka¿ [dowód | licencje]");
		return 1;
	}
	else
	{
		if(!strcmp(comm1,"dowód",true) || !strcmp(comm1,"dowod",true))
		{
			new playerid2;
			if(sscanf(comm2, "i", playerid2))
				return msg_usage(playerid, "U¿yj: /poka¿ dowód [ID gracza]");
			else
			{
				if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
					return msg_error(playerid,"Wybrany gracz nie jest zalogowany.");
				if(!PlayerToPlayer(5.0, playerid, playerid2))
					return msg_error(playerid,"Wybrany gracz nie znajduje siê obok Ciebie.");
				if(!(CharacterInfo[playerid][pDocs] & DOC_ID))
					return msg_error(playerid,"Nie posiadasz dowodu osobistego.");
				new text[256];
				format(text, sizeof(text), "Imiê i Nazwisko:\t\t%s\nP³eæ:\t\t\t%s\nWiek:\t\t\t%d lat", PlayerName3(playerid), GetSexName(CharacterInfo[playerid][pSex]), CharacterInfo[playerid][pAge]);
				
				ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » dowód osobisty", text, "Zamknij", "");

				format(text, sizeof(text), "pokazuje dowód osobisty %s.", PlayerName2(playerid2));
				cmd_me(playerid, text);
			}
		}
		else if(!strcmp(comm1,"licencje",true))
		{
			new playerid2;
			if(sscanf(comm2, "i", playerid2))
				return msg_usage(playerid, "U¿yj: /poka¿ licencje [ID gracza]");
			else
			{
				if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
					return msg_error(playerid,"Wybrany gracz nie jest zalogowany.");
				if(!PlayerToPlayer(5.0, playerid, playerid2))
					return msg_error(playerid,"Wybrany gracz nie znajduje siê obok Ciebie.");
				
				new text[256];
				format(text, sizeof(text), "Imiê Nazwisko:\t\t%s\nP³eæ:\t\t\t%s\nWiek:\t\t\t%d lat\n\n\nPrawo jazdy: ", PlayerName3(playerid), GetSexName(CharacterInfo[playerid][pSex]), CharacterInfo[playerid][pAge]);
				
				if(CharacterInfo[playerid][pDocs] & DOC_DRIVER)
					format(text, sizeof(text), "%s{02AD38}POSIADA\n{A9C4E4}", text);
				else
					format(text, sizeof(text), "%s{C90000}BRAK\n{A9C4E4}", text);
				
				format(text, sizeof(text), "%sLicencja pilota: ", text);
				
				if(CharacterInfo[playerid][pDocs] & DOC_PILOT)
					format(text, sizeof(text), "%s{02AD38}POSIADA\n{A9C4E4}", text);
				else
					format(text, sizeof(text), "%s{C90000}BRAK\n{A9C4E4}", text);
				
				format(text, sizeof(text), "%sLicencja na broñ: ", text);
				
				if(CharacterInfo[playerid][pDocs] & DOC_WEAPONS)
					format(text, sizeof(text), "%s{02AD38}POSIADA\n{A9C4E4}", text);
				else
					format(text, sizeof(text), "%s{C90000}BRAK\n{A9C4E4}", text);
					
				format(text, sizeof(text), "%sMetryczka zdrowia: ", text);
					
				if(CharacterInfo[playerid][pDocs] & DOC_MED)
					format(text, sizeof(text), "%s{02AD38}POSIADA\n{A9C4E4}", text);
				else
					format(text, sizeof(text), "%s{C90000}BRAK\n{A9C4E4}", text);
				
				ShowPlayerDialog(playerid2, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » licencje", text, "Zamknij", "");

				format(text, sizeof(text), "pokazuje licencje %s.", PlayerName2(playerid2));
				cmd_me(playerid, text);
			}
		}
	}

	return 1;
}

CMD:anim(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(CharacterInfo[playerid][pBW] || CharacterInfo[playerid][pWounded])
		return msg_error(playerid,"Nie mo¿esz u¿ywaæ animacji gdy postaæ jest nieprzytomna.");
	
	new list_anims[1024];
	
	ForeachEx(anim_id, MAX_ANIMS)
		format(list_anims, sizeof(list_anims), "%s\n%s", list_anims, AnimInfo[anim_id][aCommand]);
	
	if(strlen( list_anims ) != 0) ShowPlayerDialog( playerid, D_PLAY_ANIM, DIALOG_STYLE_LIST, DEF_NAME" » lista animacji", list_anims, "U¿yj", "Zamknij");
	else  msg_error(playerid,"Nie znaleziono animacji. Skontaktuj siê z administracj¹.");
	
	return 1;
}

CMD:pasy(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!IsPlayerInAnyVehicle(playerid))
		return 1;
	
	new vehid = GetPlayerVehicleID(playerid);
	new vehuid = GetVehicleUID(vehid);
	
	if(VehicleInfo[vehuid][vModel] == 448 || VehicleInfo[vehuid][vModel] == 461 || VehicleInfo[vehuid][vModel] == 462 || VehicleInfo[vehuid][vModel] == 463 || VehicleInfo[vehuid][vModel] == 468 || VehicleInfo[vehuid][vModel] == 471)
		return 1;
	else if(VehicleInfo[vehuid][vModel] == 481 || VehicleInfo[vehuid][vModel] == 509 || VehicleInfo[vehuid][vModel] == 510 || VehicleInfo[vehuid][vModel] == 521 || VehicleInfo[vehuid][vModel] == 522 || VehicleInfo[vehuid][vModel] == 523)
		return 1;
	
	if(CharacterInfo[playerid][pStatus] & STATUS_PASY)
	{
		CharacterInfo[playerid][pStatus] -= STATUS_PASY;
		GameTextForPlayer(playerid, "Pasy ~r~odpiete", 1000, 6);
		
		if(CharacterInfo[playerid][pTog] & TOG_STATUS)
		{
			PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][3]);
			
			PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][4]);
			PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][5]);
		}
	}
	else
	{
		CharacterInfo[playerid][pStatus] += STATUS_PASY;
		GameTextForPlayer(playerid, "Pasy ~g~zapiete", 1000, 6);
		
		if(CharacterInfo[playerid][pTog] & TOG_STATUS)
		{
			PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][3]);
			
			PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][4]);
			PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][5]);
		}
	}
	
	return 1;
}

CMD:kup(playerid,params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new doorid = PlayerDoor[playerid];
	if(!doorid || !(doorid && ((DoorsInfo[doorid][dOwnerTyp] == OWNER_GROUP && (GroupInfo[DoorsInfo[doorid][dOwner]][gType] == GROUP_SHOP || GroupInfo[DoorsInfo[doorid][dOwner]][gType] == GROUP_FUELSTATION || GroupInfo[DoorsInfo[doorid][dOwner]][gType] == GROUP_RESTAURANT)) || DoorsInfo[doorid][dOwnerTyp] == OWNER_CLOTHESSHOP)))
	{
		msg_error(playerid,"Nie znajdujesz siê w odpowiednim sklepie/miejscu!");
		return 1;
	}
	
	new string[1024];
	new groupid = DoorsInfo[doorid][dOwner];
	
	if(GroupInfo[groupid][gType] == GROUP_RESTAURANT)
	{
		new list[512], onduty = 0;
		
		ForeachEx(i, MAX_GROUPS)
		{
			if(GroupInfo[i][gType] == GROUP_RESTAURANT)
			{
				ForeachPlayer(j)
					if(DutyGroup[j] && DutyGroup[j] == i && PlayerDoor[j] && DoorsInfo[PlayerDoor[j]][dOwnerTyp] == OWNER_GROUP && DoorsInfo[PlayerDoor[j]][dOwner] == i)
						onduty++;
				
				if(onduty)
					format(list, sizeof(list), "%s\n%s  (%d na s³u¿bie)", list, GroupInfo[i][gName], onduty);
				
				onduty = 0;
			}
		}
		
		if(strlen(list) > 4)
		{
			format(string, sizeof(string), "Aktualnie nie mo¿esz kupiæ jedzenia poprzez komendê /kup.\nW mieœcie znajduje siê restauracja lub restauracje, w których pracownicy s¹ aktualnie na s³u¿bie.\n\n\nLista restauracji:\n%s", list);
			msg_error(playerid, string);
		}
		else
		{
			format(string, sizeof(string), "{FFFFFF}Frytki (10)\t\t\t\t{FCDF1E}$30\n{FFFFFF}Hamburger (20)\t\t\t\t{FCDF1E}$60\n{FFFFFF}Pizza (30)\t\t\t\t{FCDF1E}$80");
			ShowPlayerDialog(playerid, D_GASTRO_BUY, DIALOG_STYLE_LIST, DEF_NAME" » restauracja", string, "Kup", "WyjdŸ");
		}
	}
	else if(DoorsInfo[doorid][dOwnerTyp] == OWNER_CLOTHESSHOP)
		ShowPlayerDialog(playerid, D_ATTACHED_BUY, DIALOG_STYLE_LIST, DEF_NAME" » sklep odzie¿owy", "1. Nakrycia g³owy\n2. Okulary\n3. Zegarki\n4. Maski\n5. Pozosta³e", "Dalej", "Zamknij");
	else
	{
		format(string,sizeof(string),"UID\tNazwa\tCena\tIloœæ");
		ForeachEx(i,_ITEM_COUNT)
			if(ItemInfo[i][iOwnerTyp]==OWNER_GROUP && ItemInfo[i][iOwner]==groupid && ItemInfo[i][iPrice] > 0)
				format(string,sizeof(string),"%s\n%d\t%s\t$%d\t%d\n",string,i,ItemInfo[i][iName],ItemInfo[i][iPrice],ItemInfo[i][iIlosc]);
		
		if(strlen(string)>22)
		{
			SetPVarInt(playerid, "ItemBuyGroupID", groupid);
			ShowPlayerDialog(playerid, D_ITEM_BUY, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » kup przedmiot", string, "Kup", "WyjdŸ");
		}
		else
		{
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » sklep", "Brak produktów w sklepie.", "Zamknij", "");
			return 1;
		}
	}

	return 1;
}
CMD:tankuj(playerid,params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new vehid = GetPlayerVehicleID(playerid);
	new vehuid=GetVehicleUID(vehid);
	if(!vehid)
		return msg_error(playerid,"Aby skorzystaæ z tej komendy musiz znajdowaæ siê w pojeŸdzie.");
	
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		return msg_error(playerid, "Musisz byæ kierowc¹ pojazdu aby uzupe³niæ w nim paliwo");
	
	new stationid=GetPlayerStationID(playerid);
	if(!stationid)
		return msg_error(playerid,"Nie znajdujesz siê na stacji benzynowej.");
	if(VehicleInfo[GetVehicleUID(vehid)][vEngine])
		return msg_error(playerid,"Silnik w pojeŸdzie musi byæ wy³¹czony.");
	new value;
	if(sscanf(params,"d",value))
		return msg_usage(playerid,"U¿yj: /tankuj [iloœæ]");
	if(value <= 0)
		return msg_error(playerid,"Wprowadzona iloœæ jest nieprawid³owa.");
	if(StationInfo[stationid][sFuel] < value)
		return msg_error(playerid,"Brak paliwa na stacji benzynowej!");
	if(floatround(VehicleInfo[vehuid][vFuel])+ value > GetVehicleMaxFuel(VehicleInfo[vehuid][vModel]))
		return msg_error(playerid,"W pojeŸdzie nie zmieœci siê wybrana ilosc paliwa.");
	
	new price = value * StationInfo[stationid][sFuelCost];
	
	new string[256];
	format(string, sizeof(string), "Iloœæ paliwa do zatankowania: %dl\nKoszt paliwa/1litr: $%d\nKoszt ca³kowity paliwa: $%d\n\nCzy jesteœ pewny, ¿e chcesz zatankowaæ na tej stracji?", value, StationInfo[stationid][sFuelCost], price);
	
	SetPVarInt(playerid, "sFuelPrice", price);
	SetPVarInt(playerid, "sFuelStat", stationid);
	SetPVarInt(playerid, "sFuelVeh", vehuid);
	SetPVarInt(playerid, "sFuelVal", value);
	ShowPlayerDialog(playerid, D_FUELSTATION_TANK, DIALOG_STYLE_MSGBOX, DEF_NAME" » tankowanie", string, "Tak", "Nie");
	return 1;
}

CMD:afk(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
	{
		msg_info(playerid,"Przesta³eœ byæ AFK. Twoje statystki bêd¹ naliczane.");
		
		CharacterInfo[playerid][pStatus] -= STATUS_AFK;
		CharacterInfo[playerid][pAFKg] = 0;
		CharacterInfo[playerid][pAFKm] = 0;
		
		playerLog(playerid,"AFK","%s zakonczyl AFK",PlayerName(playerid));
		
		if(CanMove(playerid) && !CharacterInfo[playerid][pGymType])
			UnfreezePlayer(playerid);
	}
	else
	{
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » system AFK", "Jesteœ teraz AFK. Aby wy³¹czyæ wpisz ponownie /afk.", "Zamknij", "");
		
		CharacterInfo[playerid][pStatus] += STATUS_AFK;
		playerLog(playerid,"AFK","%s jest AFK",PlayerName(playerid));
		
		new hour, minute;
		gettime(hour, minute);
		
		CharacterInfo[playerid][pAFKg] = hour;
		CharacterInfo[playerid][pAFKm] = minute;
		
		FreezePlayer(playerid);
	}
	
	return 1;
}
CMD:hotel(playerid,params[])
{
	new comm1[16],comm2[4];
	if(sscanf(params,"s[16]S()[4]",comm1,comm2))
		return msg_usage(playerid,"U¿yj: /hotel [info | zamelduj | wymelduj | wejdz | wyjdz | z(amknij) | odwiedŸ]");
	new doorid=PlayerDoor[playerid];
	if(!strcmp(comm1,"info",true))
	{
		if(!CharacterInfo[playerid][pHotel])
			return msg_info(playerid,"Nie jesteœ zameldowany w hotelu");
		else
		{
			msg_infoFormat(playerid,196,"Jesteœ zameldowany w hotelu: %s\nNumer pokoju: %d",DoorsInfo[CharacterInfo[playerid][pHotel]][dName],CharacterInfo[playerid][pUID]+37);
			return 1;
		}
	}
	else if(!strcmp(comm1,"zamelduj",true))
	{
		if(!doorid || (doorid && DoorsInfo[doorid][dOwnerTyp] != OWNER_HOTEL))
			return msg_error(playerid,"Nie znajdujesz siê w hotelu");
		CharacterInfo[playerid][pHotel]=doorid;
		new query[128];
		format(query,sizeof(query),"UPDATE `srv_characters` SET `hotel`='%d' WHERE `player_uid`='%d'",doorid,CharacterInfo[playerid][pUID]);
		mysql_query(query);
		msg_infoFormat(playerid,196,"Zosta³eœ zameldowany w hotelu. Twój numer pokoju to: %d.\nAby dostaæ siê do pokoju u¿yj /hotel wejdz.",CharacterInfo[playerid][pUID]+37);
		return 1;
	}
	else if(!strcmp(comm1,"wymelduj",true))
	{
		if(!doorid || (doorid && DoorsInfo[doorid][dOwnerTyp] != OWNER_HOTEL))
			return msg_error(playerid,"Nie znajdujesz siê w hotelu");
		CharacterInfo[playerid][pHotel]=0;
		new query[128];
		format(query,sizeof(query),"UPDATE `srv_characters` SET `hotel`='0' WHERE `player_uid`='%d'",CharacterInfo[playerid][pUID]);
		mysql_query(query);
		msg_info(playerid,"Pomyslnie wymeldowa³eœ siê z hotelu.");
		if(GetPlayerVirtualWorld(playerid) != DoorsInfo[doorid][dExitVW])
		{
			SetPlayerPos(playerid,DoorsInfo[doorid][dExitX],DoorsInfo[doorid][dExitY],DoorsInfo[doorid][dExitZ]);
			SetPlayerVirtualWorld(playerid, DoorsInfo[doorid][dExitVW]);
			SetPlayerInterior(playerid, DoorsInfo[doorid][dExitInt]);
		}
		return 1;
	}
	else if(!strcmp(comm1,"wejdz",true) || !strcmp(comm1,"wejdŸ",true))
	{
		if(!doorid || (doorid && DoorsInfo[doorid][dOwnerTyp] != OWNER_HOTEL))
			return msg_error(playerid,"Nie znajdujesz siê w hotelu");
		if(GetPlayerVirtualWorld(playerid) != DoorsInfo[doorid][dExitVW])
			return msg_error(playerid,"Nie znajdujesz siê w lobby hotelu");
		if(CharacterInfo[playerid][pHotel] != doorid)
			return msg_error(playerid,"Nie jesteœ zameldowany w tym hotelu.");

		SetPlayerInterior(playerid, 5);
		SetPlayerPos(playerid,2233.618408, -1114.630249, 1050.882812);
		SetPlayerVirtualWorld(playerid, CharacterInfo[playerid][pUID]+37);
		SetPlayerFacingAngle(playerid, 0.0);
	}
	else if(!strcmp(comm1,"wyjdz",true) || !strcmp(comm1,"wyjdŸ",true))
	{
		if(!doorid || (doorid && DoorsInfo[doorid][dOwnerTyp] != OWNER_HOTEL))
			return msg_error(playerid,"Nie znajdujesz siê w hotelu");
		if(GetPlayerVirtualWorld(playerid) == DoorsInfo[doorid][dExitVW])
			return msg_error(playerid,"Nie znajdujesz siê w pokoju");

		SetPlayerPos(playerid,DoorsInfo[doorid][dExitX],DoorsInfo[doorid][dExitY],DoorsInfo[doorid][dExitZ]);
		SetPlayerVirtualWorld(playerid, DoorsInfo[doorid][dExitVW]);
		SetPlayerInterior(playerid, DoorsInfo[doorid][dExitInt]);
	}
	else if(!strcmp(comm1,"zamknij",true) || !strcmp(comm1,"z",true))
	{
		if(!doorid || (doorid && DoorsInfo[doorid][dOwnerTyp] != OWNER_HOTEL))
			return msg_error(playerid,"Nie znajdujesz siê w hotelu");
		if(CharacterInfo[playerid][pHotel] != doorid)
			return msg_error(playerid,"Nie jesteœ zameldowany w tym hotelu.");
		if(CharacterInfo[playerid][pHotelUnlocked])
		{
			CharacterInfo[playerid][pHotelUnlocked]=false;
			return msg_info(playerid,"Pokój w hotelu zosta³ zamkniêty.");	
		}
		else
		{
			CharacterInfo[playerid][pHotelUnlocked]=true;
			return msg_info(playerid,"Pokój w hotelu zosta³ otwarty.");
		}
	}
	else if(!strcmp(comm1,"odwiedŸ",true) || !strcmp(comm1,"odwiedz",true))
	{
		if(!doorid || (doorid && DoorsInfo[doorid][dOwnerTyp] != OWNER_HOTEL))
			return msg_error(playerid,"Nie znajdujesz siê w hotelu");
		new roomid;
		if(sscanf(comm2,"d",roomid))
			return msg_usage(playerid,"U¿yj /hotel odwiedŸ [numer pokoju]");
		ForeachPlayer(i)
		{
			if(Logged[i] && CharacterInfo[i][pHotel] == doorid && CharacterInfo[i][pHotelUnlocked] && CharacterInfo[i][pUID]+37==roomid)
			{
				SetPlayerInterior(playerid, 5);
				SetPlayerPos(playerid,2233.618408, -1114.630249, 1050.882812);
				SetPlayerVirtualWorld(playerid, roomid+37);
				SetPlayerFacingAngle(playerid, 0.0);
				msg_infoFormat(playerid,64,"Wszed³eœ do pokoju o numerze %d.",roomid);
				return 1;
			}
		}
		return msg_info(playerid,"Wybrany pokój jest zamkniêty.");
	}

	return 1;
}

CMD:pukaj(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	
	new dooruid = GetClosestDoor(playerid);
	
	if(!dooruid) return 1;
	
	if(DoorsInfo[dooruid][dOwnerTyp] == OWNER_PLAYER && !GetPlayerVirtualWorld(playerid))
	{
		cmd_me(playerid, "puka do drzwi.");
		
		ForeachPlayer(i)
			if(PlayerDoor[i] == dooruid && i != playerid)
				SendClientMessage(i, COLOR_DO, "** S³ychaæ pukanie do drzwi. **");
	}

	return 1;
}

CMD:sprawdz(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	
	new dooruid = GetClosestDoor(playerid);
	
	if(!dooruid) return 1;
	
	if(DoorsInfo[dooruid][dOwnerTyp] == OWNER_PLAYER && GetPlayerVirtualWorld(playerid))
	{
		new string[1024];
		
		ForeachPlayer(i)
			if(GetClosestDoor(i) && DoorsInfo[GetClosestDoor(i)][dUID] == dooruid && !GetPlayerVirtualWorld(i))
				format(string, sizeof(string), "%s\n%d\t%s", string, i, PlayerName2(i));
		
		if(strlen(string) > 4)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_TABLIST, DEF_NAME" » osoby przy wejsciu", string, "Zamknij", "");
		else
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_TABLIST, DEF_NAME" » osoby przy wejsciu", "Nie ma nikogo przy wejœciu do domu.", "Zamknij", "");
	}

	return 1;
}

CMD:bus(playerid,params[])
{
	new busstop=GetPlayerBusStop(playerid);
	if(!busstop)
		return msg_error(playerid,"Nie znajdujesz siê na przystanku");
	new taxis = 0;
	ForeachPlayer(i)
		if(IsPlayerOnDutyInGroup(i, GROUP_TAXI))
			taxis++;
	if(taxis > 1)
		return msg_info(playerid,"Aktualnie na s³u¿bie znajduje siê wiêcej, ni¿ jeden taksówkarz. Skorzystaj z ich us³ug.");
	new string[1024];
	for(new i=1;i<MAX_BUS_STOPS;i++)
		if(i != busstop && BusInfo[i][bUID])
			format(string,sizeof(string),"%s\n{c8c8c8}%2d: {ffffff}%s",string,i,BusInfo[i][bName]);
	ShowPlayerDialog(playerid,D_BUS,DIALOG_STYLE_LIST,DEF_NAME" » wybierz przystanek",string,"Wybierz","WyjdŸ");

	return 1;
}
CMD:cwiczenia(playerid,params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!CanMove(playerid) || !CanSpeak(playerid))
		return msg_error(playerid,"Nie mo¿esz teraz tego zrobiæ.");
	if(CharacterInfo[playerid][pGymType] == TRAIN_PUNCH_BAG)
	{
		OnPlayerGymTrainStopped(playerid);
		return msg_info(playerid, "Zakoñczy³eœ æwiczenia.");
	}
	else if(CharacterInfo[playerid][pGymType] != TRAIN_NONE)
		return msg_error(playerid,"Jesteœ ju¿ w trakcie æwiczeñ.");
	
	if(CharacterInfo[playerid][pStrengthToday] >= 50 && CharacterInfo[playerid][pSuplement] != 2)
		return msg_error(playerid,"Dzienny limit æwiczeñ zosta³ wyczerpany. Wróæ jutro.");
	else if(CharacterInfo[playerid][pStrengthToday] >= 70 && CharacterInfo[playerid][pSuplement] == 2)
		return msg_error(playerid,"Dzienny limit æwiczeñ zosta³ wyczerpany. Wróæ jutro.");

	new doorid=PlayerDoor[playerid];
	if(!doorid || DoorsInfo[doorid][dOwnerTyp] != OWNER_GROUP || GroupInfo[DoorsInfo[doorid][dOwner]][gType] != GROUP_GYM)
		return msg_error(playerid, "Nie znajdujesz siê w si³owni");
	new groupid=DoorsInfo[doorid][dOwner];

	if(CharacterInfo[playerid][pGymPass] != groupid)
	{
		new query[128],bool:found;
		format(query,sizeof(query),"SELECT * FROM `srv_gym_pass` WHERE `player_uid`='%d' AND `groupid`='%d' AND `time`>'%d'",CharacterInfo[playerid][pUID],groupid,gettime());
		mysql_query(query);
		mysql_store_result();
		if(mysql_num_rows())
			found=true;
		mysql_free_result();

		if(found)
			CharacterInfo[playerid][pGymPass] = groupid;
		else
			return msg_error(playerid,"Nie posiadasz wykupionego karnetu w tej si³owni.");
	}
	new comm1[8],object,type;
	if(sscanf(params,"s[8]",comm1))
		return msg_usage(playerid,"U¿yj: /cwiczenia [hantle | lawka | worek]");

	if(!strcmp(comm1,"hantle", true))
	{
		type=TRAIN_BARBELL;
		object=2915;
	}
	else if(!strcmp(comm1,"lawka", true))
	{
		type = TRAIN_BENCH;
		object=2629;
	}
	else if(!strcmp(comm1,"worek", true))
	{
		if(CharacterInfo[playerid][pStrength] < 100)
			return msg_error(playerid, "Masz za ma³o si³y aby nauczyæ siê nowego stylu walki. Wymagane 100j.");
		
		if(CharacterInfo[playerid][pStrengthToday] > 30 && CharacterInfo[playerid][pSuplement] != 2)
			return msg_error(playerid,"Cwiczy³eœ dziœ zbyt du¿o. Nie mo¿esz trenowaæ stylu walki.");
		else if(CharacterInfo[playerid][pStrengthToday] > 50 && CharacterInfo[playerid][pSuplement] == 2)
			return msg_error(playerid,"Cwiczy³eœ dziœ zbyt du¿o. Nie mo¿esz trenowaæ stylu walki.");
		type = TRAIN_PUNCH_BAG;
		object=1985;
	}
	else return msg_usage(playerid,"U¿yj: /cwiczenia [hantle | lawka | worek]");

	new bool:used;
	ForeachEx(i, _OBJ_COUNT)
	{
		if(ObjectInfo[i][oModel] == object && IsPlayerInRangeOfPoint(playerid, 3.0, ObjectInfo[i][oX], ObjectInfo[i][oY], ObjectInfo[i][oZ]-0.75))
		{
			ForeachPlayer(j)
			{
				if(CharacterInfo[j][pGymObject]==i)
				{
					used=true;
					break;
				}
			}
			if(!used)
			{
				if(type != TRAIN_PUNCH_BAG)
					OnPlayerGymTrainStarted(playerid, type, i);
				else
				{
					CharacterInfo[playerid][pGymObject] = i;
					ShowPlayerDialog(playerid, D_GYM_PUNCH_BAG, DIALOG_STYLE_LIST, DEF_NAME" » styl walki", "Podstawowy\nBoks\nKarate\nKick-boxing", "Dalej", "WyjdŸ");
				}
				return 1;
			}
		}
	}
	return msg_error(playerid,"Nie znajdujesz siê w pobli¿u wolnego obiektu do æwiczeñ.");
}

CMD:skrytka(playerid, params[])
{
	new dooruid = GetClosestDoor(playerid);
	
	if(!dooruid || DoorsInfo[dooruid][dOwnerTyp] != OWNER_SAFEKEEP)
		return msg_error(playerid, "Nie stoisz przy odpowiednich drzwiach (skrytce).");
	
	if(!CanMove(playerid))
		return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
	
	ShowPlayerDialog(playerid, D_SAFEKEEP, DIALOG_STYLE_LIST, DEF_NAME" » skrytka", "1. U¿yj klucza [otwórz skrytkê]\n2. Kup skrytkê [$150]", "Wybierz", "Zamknij");
	
	return 1;
}
CMD:praca(playerid,params[])
{
	if(CharacterInfo[playerid][pJob] == JOB_NONE)
		return msg_error(playerid,"Nie posiadasz pracy dorywczej. Udaj siê do urzêdu miasta.");
	if(CharacterInfo[playerid][pJob] == JOB_WEARHOUSE)
	{
		if(CharacterInfo[playerid][pJobCount] >= NAX_JOB_WEARHOUSE_REPS)
			return msg_error(playerid,"Wyczerpa³eœ dzisiejszy limit pracy. Wróæ jutro.");
		if(!GetPVarInt(playerid,"pJob"))
		{
			if(!IsPlayerInRangeOfPoint(playerid, 50.0, 2762.8875,-2344.4080,13.6421) || GetPlayerVirtualWorld(playerid)!=8)
				return msg_error(playerid,"Nie znajdujesz siê na terenie magazynu paczek.");

			SetPVarInt(playerid,"pJob", JOB_WEARHOUSE);
			msg_info(playerid,"Rozpocz¹³eœ pracê w magazynie. Twoje zadanie to przenoszenie paczek w wybrane miejsce.\nZa ka¿d¹ przeniesiona paczkê otrzymasz 10$.\n\nAby zakoñczyæ pracê ponownie wpisz /praca");

			new point=random(6);
			SetPlayerCheckpoint(playerid, DocksJob[point][posX], DocksJob[point][posY], DocksJob[point][posZ], 1.5);
			CharacterInfo[playerid][pJobPhase]=1;
		}
		else
		{		
			EndJob(playerid);
			msg_info(playerid,"Zakoñczy³eœ pracê w magazynie");
		}
	}
	return 1;
}

CMD:uleczsie(playerid,params)
{
	new dooruid = GetClosestDoor(playerid);
	
	if(!dooruid || DoorsInfo[dooruid][dOwnerTyp] != OWNER_ULECZSIE)
		return msg_error(playerid, "Nie znajdujesz siê w odpowiednim miejscu (przy pickupie)");
	if(!PlayerDoor[playerid] || DoorsInfo[PlayerDoor[playerid]][dOwnerTyp] != OWNER_GROUP)
		return msg_error(playerid, "Nie znajdujesz siê w odpowiednim miejscu (przy pickupie)");
	
	if(CharacterInfo[playerid][pHealth] >= 75.0)
		return msg_error(playerid, "Posiadasz wiêcej lub równo 75 HP, nie mo¿esz u¿yæ tej komendy.");
	
	if(CharacterInfo[playerid][pDamageTook])
		return msg_info(playerid, "Musi min¹æ minimum 5 minut od otrzymania obra¿en aby móc u¿yæ lekarstwa.");
	
	if(CharacterInfo[playerid][pCash] < SettingInfo[sHealPrice])
	{
		new string[64];
		format(string, sizeof(string), "Aby siê uleczyæ musisz zap³aciæ $%d.", SettingInfo[sHealPrice]);
		return msg_error(playerid, string);
	}
	else
	{
		GivePlayerCash(playerid, -SettingInfo[sHealPrice]);
		GiveGroupCash(playerid, DoorsInfo[PlayerDoor[playerid]][dOwner]);
		SetPlayerHP(playerid, 75.0);
		if(CharacterInfo[playerid][pLastWEAP])
		{
			CharacterInfo[playerid][pLastDMG] = 0;
			CharacterInfo[playerid][pLastWEAP] = 0;
			CharacterInfo[playerid][pLastHB] = 0;
		}
	}
	
	return 1;
}
CMD:odczep(playerid,params[])
{

	new vehid = GetPlayerVehicleID(playerid);
	if(vehid!=INVALID_VEHICLE_ID)
	{
		if(IsTrailerAttachedToVehicle(vehid))
			DetachTrailerFromVehicle(vehid);
	}
	return 1;
}

CMD:ignore(playerid, params[])
{
	new playerid2;
	if(sscanf(params, "d", playerid2))
		return msg_usage(playerid,"U¿yj: /ignore [ID gracza]");
	if(playerid2 == -1)
	{
		CharacterInfo[playerid][pIgnore] = INVALID_PLAYER_ID;
		return msg_info(playerid,"Przesta³es ignorowaæ wybranego gracza");
	}
	
	if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
		return msg_error(playerid, "Gracz o podanym ID nie jest zalogowany.");

	CharacterInfo[playerid][pIgnore] = CharacterInfo[playerid2][pUID];
	
	return msg_info(playerid, "Od teraz ignorujesz PW od wskazanego gracza. Aby przestaæ ignorowaæ wykonaj relog lub wpisz jako ID gracza \"-1\".");
}

CMD:obrazenia(playerid, params[])
{
	new playerid2;
	if(sscanf(params, "d", playerid2))
	{
		if(!CharacterInfo[playerid][pLastDMG] || !CharacterInfo[playerid][pLastHB] || !CharacterInfo[playerid][pLastWEAP])
			return msg_error(playerid, "Nie posiadasz ¿adnych \"ostatnio\" otrzymanych obra¿eñ.");
		
		new dostalw[32];
		switch(CharacterInfo[playerid][pLastHB])
		{
			case 3:
				format(dostalw, sizeof(dostalw), "{C90000}KLATKA PIERSIOWA");
			case 4:
				format(dostalw, sizeof(dostalw), "{C90000}TORS");
			case 5:
				format(dostalw, sizeof(dostalw), "{C90000}LEWE RAMIE");
			case 6:
				format(dostalw, sizeof(dostalw), "{C90000}PRAWE RAMIE");
			case 7:
				format(dostalw, sizeof(dostalw), "{C90000}LEWA NOGA");
			case 8:
				format(dostalw, sizeof(dostalw), "{C90000}PRAWA NOGA");
			case 9:
				format(dostalw, sizeof(dostalw), "{C90000}G£OWA");
		}
		
		new bron[16];
		GetWeaponName(CharacterInfo[playerid][pLastWEAP], bron, sizeof(bron));
		
		new string[256];
		format(string, sizeof(string), "Ostatnie obra¿enia otrzymane przez postaæ:\n\n%0.1f z broni %s - %s", CharacterInfo[playerid][pLastDMG], bron, dostalw);
		
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » obra¿enia", string, "Zamknij", "");
	}
	else
	{
		if(!CharacterInfo[playerid][pAdmin] && !IsPlayerOnDutyInGroup(playerid, GROUP_MC) && !CharacterInfo[playerid2][pBW] && !CharacterInfo[playerid][pWounded])
			return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie odpowiedniej grupy.");
		
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid, "Gracz o podanym ID nie jest zalogowany.");
		
		if(playerid == playerid2)
			return msg_error(playerid, "Aby sprawdziæ swoje obra¿enia u¿yj /obrazenia");
		
		if(!PlayerToPlayer(5.0, playerid, playerid2))
			return msg_error(playerid,"Nie znajdujesz siê w pobli¿u wybranego gracza.");
		
		if(!CharacterInfo[playerid2][pLastDMG] || !CharacterInfo[playerid2][pLastHB] || !CharacterInfo[playerid2][pLastWEAP])
			return msg_error(playerid, "Wybrana postaæ nie posiada ¿adnych \"ostatnio\" otrzymanych obra¿eñ.");
		
		new dostalw[32];
		switch(CharacterInfo[playerid2][pLastHB])
		{
			case 3:
				format(dostalw, sizeof(dostalw), "{C90000}KLATKA PIERSIOWA");
			case 4:
				format(dostalw, sizeof(dostalw), "{C90000}TORS");
			case 5:
				format(dostalw, sizeof(dostalw), "{C90000}LEWE RAMIE");
			case 6:
				format(dostalw, sizeof(dostalw), "{C90000}PRAWE RAMIE");
			case 7:
				format(dostalw, sizeof(dostalw), "{C90000}LEWA NOGA");
			case 8:
				format(dostalw, sizeof(dostalw), "{C90000}PRAWA NOGA");
			case 9:
				format(dostalw, sizeof(dostalw), "{C90000}G£OWA");
		}
		
		new bron[16];
		GetWeaponName(CharacterInfo[playerid2][pLastWEAP], bron, sizeof(bron));
		
		new string[256];
		format(string, sizeof(string), "Ostatnie obra¿enia otrzymane przez postaæ:\n\n%0.1f z broni %s - %s", CharacterInfo[playerid2][pLastDMG], bron, dostalw);
		
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » obra¿enia", string, "Zamknij", "");
	}
	
	return 1;
}

CMD:reczny(playerid, params[])
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		new vehid = GetPlayerVehicleID(playerid);
		new vehuid = GetVehicleUID(vehid);
		
		if(!hasModelEngine(GetVehicleModel(vehid)))
			return msg_error(playerid, "Pojazd nie posiada hamulca rêcznego!");
		
		if(VehicleInfo[vehuid][vEngine])
			return msg_error(playerid, "Najpierw wy³¹cz silnik.");
		
		if(IsOwnerVehicle(playerid, vehuid))
		{
			switch(VehicleInfo[vehuid][vHandBrake])
			{
				case 0:
				{
					GetVehiclePos(vehid, VehicleInfo[vehuid][vHB][0], VehicleInfo[vehuid][vHB][1], VehicleInfo[vehuid][vHB][2]);
					GetVehicleZAngle(vehid, VehicleInfo[vehuid][vHB][3]);
					VehicleInfo[vehuid][vHandBrake] = true;
					msg_info(playerid, "Zaci¹gn¹³eœ hamulec rêczny w pojeŸdzie - uniemo¿liwia on przepychanie pojazdu.");
				}
				case 1:
				{
					VehicleInfo[vehuid][vHB][0] = 
					VehicleInfo[vehuid][vHB][1] = 
					VehicleInfo[vehuid][vHB][2] = 
					VehicleInfo[vehuid][vHB][3] = 0;
					VehicleInfo[vehuid][vHandBrake] = false;
					msg_info(playerid, "Hamulec rêczny zosta³ przywrócony do normalnego stanu - wy³¹czony.");
				}
			}
		}
		else
			return msg_error(playerid, "Nie jesteœ w³aœcicielem tego pojazdu!");
	}
	else
		return msg_error(playerid, "Nie znajdujesz siê na miejscu kierowcy w pojeŸdzie!");
	
	return 1;
}

CMD:styl(playerid,params[]) 
{
	new style[] = "Brak\nZwyk³y\nCywil\nGangster 1\nGangster 2\nDziadek\nGruby dziadek\nGrubas\nKobieta 1\nKobieta 2\nDziwka 1\nDziwka 2\nPijany\nŒlepy";
	ShowPlayerDialog(playerid, D_WALKSTYLE, DIALOG_STYLE_LIST, DEF_NAME" » styl chodzenia",style, "Wybierz", "WyjdŸ");
	return 1;
}

CMD:yo(playerid,params[])
{
	if(!CanMove(playerid) || !CanSpeak(playerid))
		return msg_error(playerid,"Nie mo¿esz teraz tego zrobiæ.");

	new playerid2;
	if(sscanf(params, "d", playerid2))
		return msg_usage(playerid,"U¿yj: /yo [ID gracza]");

	if(playerid == playerid2)
		return msg_error(playerid, "Nie mo¿esz oferowaæ samemu sobie.");
	if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
		return msg_error(playerid, "Gracz o podanym ID nie jest zalogowany.");
	if(!PlayerToPlayer(2.0, playerid, playerid2))
		return msg_error(playerid,"Nie znajdujesz siê w pobli¿u wybranego gracza.");
	if(!CanMove(playerid2) || !CanSpeak(playerid2))
		return msg_error(playerid,"Nie mo¿esz teraz tego zrobiæ.");

	Oferta(OFFER_YO, playerid, playerid2, 0, 1);
	return 1;
}

CMD:podnies(playerid,params[])
{
	if(!CanMove(playerid))
		return msg_error(playerid,"Nie mo¿esz teraz tego zrobiæ.");
	
	new playerid2;
	if(sscanf(params, "d", playerid2))
		return msg_usage(playerid,"U¿yj: /podnies [ID gracza]");
	
	if(playerid == playerid2)
		return msg_error(playerid, "Nie mo¿esz podniesc samego siebie.");
	if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
		return msg_error(playerid, "Gracz o podanym ID nie jest zalogowany.");
	if(!PlayerToPlayer(2.0, playerid, playerid2))
		return msg_error(playerid,"Nie znajdujesz siê w pobli¿u wybranego gracza.");
	if(!CharacterInfo[playerid2][pWounded] || CharacterInfo[playerid2][pBW])
		return msg_error(playerid,"Gracz nie jest powalony.");
	if(CharacterInfo[playerid2][pDeathTimer])
		return msg_error(playerid,"Nie mo¿esz tego jeszcze zrobiæ (cooldown po œmierci).");
	
	ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0, 1);
	
	CharacterInfo[playerid2][pReanimation] = 4;
	CharacterInfo[playerid2][pReanimationID] = playerid;
	
	return 1;
}

CMD:skin(playerid,params)
{
	new list[1024];
	format(list, sizeof(list), "ID\tModel ID");
	
	ForeachEx(i, MAX_SKINS)
	{
		if(SkinInfo[i][sID] && SkinInfo[i][sType] == SKIN_TYPE_PLAYER && SkinInfo[i][sUID] == CharacterInfo[playerid][pGID])
		{
			new query[128];
			format(query, sizeof(query), "SELECT `player_uid` FROM `srv_characters` WHERE `skin` = '%d' AND `global_id` = '%d' LIMIT 1", SkinInfo[i][sModel], CharacterInfo[playerid][pUID]);
			mysql_query(query);
			mysql_store_result();
			
			if(!mysql_num_rows())
				format(list, sizeof(list), "%s\n%d\t%d", list, SkinInfo[i][sID], SkinInfo[i][sModel]);
			
			mysql_free_result();
		}
	}
	
	if(strlen(list) > 12) ShowPlayerDialog(playerid, D_SKIN_CHANGE, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » dostêpne skiny", list, "U¿yj", "Anuluj");
	else Tip(playerid, 3, "Nie masz dostepu do unikalnego skina.");
}