public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	A_CHAR(inputtext);
	switch(dialogid)
	{
		case D_INFO: 
			return 1;
		case D_LOGIN_GLOBAL:
		{
			if(response)
			{
				mysql_real_escape_string(inputtext, inputtext);
				
				mysql_query_format("SELECT c.player_uid FROM `members` m, `srv_characters` c WHERE m.`members_pass_hash` = MD5(CONCAT(MD5(m.members_pass_salt),'', MD5('%s'))) AND m.`member_id` = c.`global_id` AND c.`nickname` = '%s' LIMIT 1", inputtext, PlayerName(playerid));
				mysql_store_result();
				
				if(mysql_num_rows())
					OnPlayerLogin(playerid, mysql_fetch_int());
				else
				{
					new string[32];
					
					format(string, sizeof(string), "Poda³eœ nieprawid³owe has³o.");
					ShowPlayerDialog(playerid, D_LOGIN_GLOBAL, DIALOG_STYLE_PASSWORD, DEF_NAME" » logowanie", string, "Zaloguj", "Zamknij");
				}
				
				mysql_free_result();
			}
			else
				KickWithWait(playerid);
			return 1;
		}
		case D_HELP:
		{
			if(response)
			{
				new string[512];
				switch(listitem)
				{
					case 0:
						format(string, sizeof(string), "W ksi¹¿kach narrator wybiera los dla postaci fikcyjnej, a tutaj ty jesteœ tym narratorem, lecz dla swojej postaci.\nMusisz trzymaæ siê zasad realnego ¿ycia (Nie przesadzaj¹c, lecz z rozs¹dkiem kreuj swój charakter), tzn. Jakbyœ sam w nim uczestniczy³.\n\nCo to jest OOC i IC ?\nOOC - Out Of Character, sprawy wychodz¹ce poza gr¹, np. Marcin jesteœ chory ¿e nie chodzisz do szko³y?\nIC - In Character, sprawy wychodz¹ce z gry, np. Marcin jak tam w pracy?");
					case 1:
						format(string, sizeof(string), "Nasz serwer oferuje graczom pe³ny wachlarz ró¿nych mo¿liwoœci.\n Mo¿esz podj¹æ jak¹œ pracê dorywcz¹ w urzêdzie, zostaæ stró¿em prawa, lekarzem lub zatrudniæ siê w czyjejœ firmie, a kto wie - Mo¿e nawet za³o¿ysz kiedyœ swój biznes.\n\nJeœli jednak jesteœ trochê leniwy, mo¿esz spaœæ na drogê przestêpcy.");
					case 2:
						format(string, sizeof(string), "/stats, /me, /do, /s(zept), /k(rzycz), /v(/pojazd), /p(rzedmiot), /wjedz, /report, /pytanie, /g(rupa), /w, /relog, /qs, /q, /bagaznik, /dom,\n/pokaz, /o(feruj), /dzwon, /sms, /tel, /kup, /drzwi, /kluczyk, /praca, /admins.");
					case 3:
						format(string, sizeof(string), "Wszystkie sprawy zwi¹zane z apelacjami od kar, skargami na graczy za³atwiamy poprzez forum w odpowiednim dziale.\n Z administracj¹ mo¿esz siê skontaktowaæ poprzez /pytanie lub pisz¹c prywatn¹ wiadomoœæ do jednego z nich.\nAdministratorów na s³u¿bie mo¿esz sprawdziæ pod komend¹ /admins.");
				}
				
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » centrum pomocy", string, "Zamknij", "");
			}
			return 1;
		}
		case D_TOG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0: // Wy³¹czone wiadomoœci PW
					{
						if(CharacterInfo[playerid][pTog] & TOG_PW) CharacterInfo[playerid][pTog] -= TOG_PW;
						else CharacterInfo[playerid][pTog] += TOG_PW;
					}
					case 1: // Ukryty textdraw nazwy serwera
					{
						if(CharacterInfo[playerid][pTog] & TOG_NAME)
						{
							CharacterInfo[playerid][pTog] -= TOG_NAME;
							TextDrawShowForPlayer(playerid, TDEditor_TD[0]);
							TextDrawShowForPlayer(playerid, TDEditor_TD[1]);
						}
						else
						{
							CharacterInfo[playerid][pTog] += TOG_NAME;
							TextDrawHideForPlayer(playerid, TDEditor_TD[0]);
							TextDrawHideForPlayer(playerid, TDEditor_TD[1]);
						}
					}
					case 2: // Pasek g³odu
					{
						if(CharacterInfo[playerid][pTog] & TOG_GLOD)
						{
							CharacterInfo[playerid][pTog] -= TOG_GLOD;
							ShowPlayerProgressBar(playerid, FoodBar[playerid]);
							SetPlayerProgressBarValue(playerid, FoodBar[playerid], 100-CharacterInfo[playerid][pGlod]);
						}
						else
						{
							CharacterInfo[playerid][pTog] += TOG_GLOD;
							HidePlayerProgressBar(playerid, FoodBar[playerid]);
						}
					}
					case 3: //Textdraw LSN
					{
						if(CharacterInfo[playerid][pTog] & TOG_LSN)
						{
							CharacterInfo[playerid][pTog] -= TOG_LSN;
							TextDrawShowForPlayer(playerid, TD_LSN);
							TextDrawShowForPlayer(playerid, TD_LSN2);
						}
						else
						{
							CharacterInfo[playerid][pTog] += TOG_LSN;
							TextDrawHideForPlayer(playerid, TD_LSN);
							TextDrawHideForPlayer(playerid, TD_LSN2);
						}
					}
					case 4: // Animacja mówienia
					{
						if(CharacterInfo[playerid][pTog] & TOG_SAY) CharacterInfo[playerid][pTog] -= TOG_SAY;
						else CharacterInfo[playerid][pTog] += TOG_SAY;
					}
					case 5: // Animacja krzyku
					{
						if(CharacterInfo[playerid][pTog] & TOG_KRZYK) CharacterInfo[playerid][pTog] -= TOG_KRZYK;
						else CharacterInfo[playerid][pTog] += TOG_KRZYK;
					}
					case 6:
					{
						if(CharacterInfo[playerid][pTog] & TOG_SPEEDOMETER)
						{
							if(!(CharacterInfo[playerid][pTog] & TOG_SPEEDOMETER) && IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
								SetTimerEx("SpeedMeterUP", 100, false, "i", playerid);
							
							CharacterInfo[playerid][pTog] -= TOG_SPEEDOMETER;
						}
						else
							CharacterInfo[playerid][pTog] += TOG_SPEEDOMETER;
					}
					case 7: // Freeze
					{
						if(CharacterInfo[playerid][pTog] & TOG_FREEZE)
							CharacterInfo[playerid][pTog] -= TOG_FREEZE;
						else
							CharacterInfo[playerid][pTog] += TOG_FREEZE;
					}
					case 8: // Kierunki
					{
						if(CharacterInfo[playerid][pTog] & TOG_KIERUNKI)
							CharacterInfo[playerid][pTog] -= TOG_KIERUNKI;
						else
							CharacterInfo[playerid][pTog] += TOG_KIERUNKI;
					}
					case 9: // Animacja œmiechu
					{
						if(CharacterInfo[playerid][pTog] & TOG_SMIECH)
							CharacterInfo[playerid][pTog] -= TOG_SMIECH;
						else
							CharacterInfo[playerid][pTog] += TOG_SMIECH;
					}
					case 10: // Czat OOC (/b)
					{
						if(CharacterInfo[playerid][pTog] & TOG_CHATOOC)
							CharacterInfo[playerid][pTog] -= TOG_CHATOOC;
						else
							CharacterInfo[playerid][pTog] += TOG_CHATOOC;
					}
					case 11: // Styl noszenia broni
					{
						if(CharacterInfo[playerid][pTog] & TOG_GUN_CARRY)
							CharacterInfo[playerid][pTog] -= TOG_GUN_CARRY;
						else
							CharacterInfo[playerid][pTog] += TOG_GUN_CARRY;
					}
					case 12: // Textdraw statusów
					{
						if(CharacterInfo[playerid][pTog] & TOG_STATUS)
						{
							for(new x = 0; x < 9; x++)
								PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][x]);
							
							CharacterInfo[playerid][pTog] -= TOG_STATUS;
						}
						else
						{
							if(IsPlayerInOfficialGroup(playerid) || IsPlayerInBuisnessGroup(playerid))
							{
								if(DutyGroup[playerid])
								{
									PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][6]);
									
									PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][7]);
									PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][8]);
								} else {
									PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][6]);
									
									PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][7]);
									PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][8]);
								}
							}
							
							if(IsPlayerGroupPerm(playerid, FLAG_GPS))
							{
								if(CharacterInfo[playerid][pGPS])
								{
									PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][0]);
									
									PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][1]);
									PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][2]);
								} else {
									PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][0]);
									
									PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][1]);
									PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][2]);
								}
							}
							
							if(IsPlayerInAnyVehicle(playerid))
							{
								if(CharacterInfo[playerid][pStatus] & STATUS_PASY)
								{
									PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][3]);
									
									PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][4]);
									PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][5]);
								} else {
									PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][3]);
									
									PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][4]);
									PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][5]);
								}
							}
							
							CharacterInfo[playerid][pTog] += TOG_STATUS;
						}
					}
					case 13: // Token administracyjny
					{
						if(CharacterInfo[playerid][pTog] & TOG_TOKEN)
							CharacterInfo[playerid][pTog] -= TOG_TOKEN;
						else
							CharacterInfo[playerid][pTog] += TOG_TOKEN;
					}
				}
				
				SavePlayerStats(playerid, SAVE_PLAYER_OPTION);
				cmd_tog(playerid, "");
			}
			return 1;
		}
		case D_BAN_LIST:
		{
			if(response)
			{
				new gid = strval(inputtext);
				new string[256];
				format(string,sizeof(string),"DELETE FROM `srv_bans` WHERE `player_global_id`='%d' LIMIT 1", gid);
				mysql_query(string);
				format(string,sizeof(string),"[AI] %s zdj¹³ banicjê u¿ytkownika GID: %d: %s", CharacterInfo[playerid][pGlobalNick], gid,LoadPlayerGlobalNick(gid));
				SendAdminMessage(COLOR_GREEN, string);
				format(string,sizeof(string),"Unban gracza %d: %s",gid,LoadPlayerGlobalNick(gid));
				AdminLog(playerid,string);
			}
			return 1;
		}
		case D_PRIV_MSG:
		{
			if(response)
			{
				new key[32];
				GetPVarString(playerid, "pKey", key, 32);
				if(!strcmp(inputtext, key, true) && !isnull(inputtext))
				{
					new playerid2 = GetPVarInt(playerid,"pPrivTo");
					new text[128],string[256];
					
					GetPVarString(playerid, "pPrivMess", text, 128);
						
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
										format(string, sizeof(string), "(( {001BEB}[Opiekun]{F2DE00} %s(%d) napisa³: %s ..", CharacterInfo[playerid][pGlobalNick], playerid, text);
									case 2,3,4:
										format(string, sizeof(string), "(( {8B00B0}[GameMaster]{F2DE00} %s(%d) napisa³: %s ..", CharacterInfo[playerid][pGlobalNick], playerid, text);
									case 5,6:
										format(string, sizeof(string), "(( {B00000}[Administrator]{F2DE00} %s(%d) napisa³: %s ..", CharacterInfo[playerid][pGlobalNick], playerid, text);					}
							}
							else
								format(string, sizeof(string), "(( %s(%d) napisa³: %s ..", PlayerName2(playerid), playerid, text);
							
							SendClientMessage(playerid2, COLOR_GOT_PW, string);
							SendClientMessageFormat(playerid2, COLOR_GOT_PW, "...%s ))", text2);
							
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
								format(string, sizeof(string), "(( Wys³ano do %s (ID: %d): %s ..", PlayerName2(playerid2), playerid2, text);

							SendClientMessage(playerid, COLOR_SEND_PW, string);
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
				}
				else
				{
					msg_error(playerid,"Wprowadzony token administracyjny jest niepoprawny.\nSpróbuj ponownie napisaæ wiadomoœæ.");
					
				}
				DeletePVar(playerid,"pKey");
				DeletePVar(playerid,"pPrivMess");
				DeletePVar(playerid,"pPrivTo");
			}
			return 1;
		}
		case D_ITEM_CREATE:
		{
			if(response)
			{
				new name[32], string[512];
				
				if(strlen(inputtext) == 0)
				{
					ShowPlayerDialog(playerid, D_ITEM_CREATE, DIALOG_STYLE_INPUT, DEF_NAME" » tworzenie przedmiotu", "Wpisz nazwê nowego przedmiotu.", "Dalej", "Anuluj");
					return 1;
				}
				mysql_real_escape_string(inputtext,inputtext);
				format(name, sizeof(name), "%s", inputtext);
				EscapePL(name);
				mysql_real_escape_string(name,name);
				SetPVarString(playerid, "ItemCreateName", name);
			
				ForeachEx(i, TYPE_COUNT+1)
					format(string, sizeof(string), "%s\n%s", string, ItemTypeInfo[i][iTypeName]);
			
				ShowPlayerDialog(playerid, D_ITEM_CREATE_TYPE, DIALOG_STYLE_LIST, DEF_NAME" » typ przedmiotu", string, "Wybierz", "Zamknij");
			}
			return 1;
		}
		case D_ITEM_CREATE_TYPE:
		{
			if(response)
			{
				SetPVarInt(playerid, "ItemCreateType", listitem);
				
				ShowPlayerDialog(playerid, D_ITEM_CREATE_VALUE1, DIALOG_STYLE_INPUT, DEF_NAME" » wartoœæ przedmiotu", "WprowadŸ wartoœæ (1) przedmiotu.", "Dalej", "Zamknij");
			}
			return 1;
		}
		case D_ITEM_CREATE_VALUE1:
		{
			if(response)
			{
				new value1 = strval(inputtext);
				SetPVarInt(playerid, "ItemCreateValue1", value1);
				
				ShowPlayerDialog(playerid, D_ITEM_CREATE_VALUE2, DIALOG_STYLE_INPUT, DEF_NAME" » wartoœæ przedmiotu", "WprowadŸ wartoœæ (2) przedmiotu.", "Dalej", "Zamknij");
			}
			return 1;
		}
		case D_ITEM_CREATE_VALUE2:
		{
			if(response)
			{
				new value2 = strval(inputtext);
				new value1 = GetPVarInt(playerid, "ItemCreateValue1");
				new type = GetPVarInt(playerid, "ItemCreateType");
				new string[256];
				
				new name[32];
				
				GetPVarString(playerid, "ItemCreateName", name, sizeof(name));
				
				if(type == ITEM_TYPE_TELEFON)
				{
					new val1, data[64], bool:ex;
					mysql_query_format("SELECT `value1` FROM `srv_items` WHERE `type` = '%d'", type);
					
					mysql_store_result();
					
					while(mysql_fetch_row_format(data))
					{
						sscanf(data, "d", val1);
						if(value1 == val1)
						{
							cmd_aprzedmiot(playerid, "stworz");
							SendClientMessage(playerid, COLOR_RED, "[AI] Numer telefonu (value1) jest ju¿ w bazie.");
							ex = true;
							break;
						}
					}
					mysql_free_result();
					
					if(ex) return 1;
				}
				
				new uid = StworzPrzedmiot(OWNER_PLAYER, CharacterInfo[playerid][pUID], name, type, value1, value2, 1);
				log("%s stworzyl %s[item:%d] typ:%d",CharacterInfo[playerid][pGlobalNick],name,uid,type);
				
				DeletePVar(playerid, "ItemCreateName");
				DeletePVar(playerid, "ItemCreateType");
				DeletePVar(playerid, "ItemCreateValue1");
				
				format(string, sizeof(string), "Przedmiot zosta³ pomyœlnie stworzony, znajdziesz go w swoim ekwipunku (/przedmiot).");
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » przedmiot stworzony", string, "Zamknij", "");
			}
			return 1;
		}
		case D_ITEM:
		{
			if(response)
			{
				new title[64];
				new uid = strval(inputtext);
				
				SetPVarInt(playerid, "ItemUID", uid);	
				
				format(title, sizeof(title), "Przedmiot %s (UID: %d)", ItemInfo[uid][iName], uid);
				if(ItemInfo[uid][iType] == ITEM_TYPE_MARIHUANA || ItemInfo[uid][iType] == ITEM_TYPE_KOKAINA || ItemInfo[uid][iType] == ITEM_TYPE_HEROINA || ItemInfo[uid][iType] == ITEM_TYPE_LSD)
					ShowPlayerDialog(playerid, D_ITEM_OPTIONS, DIALOG_STYLE_LIST, title, "1. U¿yj przedmiot\n2. Od³ó¿ w pobli¿u\n3. Zniszcz przedmiot\n4. Informacje ogólne\n5. Rozdziel przedmiot\n6. Po³¹cz podobne w ca³oœæ", "Wybierz", "Zamknij");
				else
					ShowPlayerDialog(playerid, D_ITEM_OPTIONS, DIALOG_STYLE_LIST, title, "1. U¿yj przedmiot\n2. Od³ó¿ w pobli¿u\n3. Zniszcz przedmiot\n4. Informacje ogólne\n5. Rozdziel przedmiot", "Wybierz", "Zamknij");
			}
			return 1;
		}
		case D_ITEM_OPTIONS:
		{
			if(response)
			{
				new uid = GetPVarInt(playerid, "ItemUID");
				switch(listitem)
				{
					case 0: OnPlayerUseItem(playerid, uid);
					case 1: OnPlayerDropItem(playerid, uid);
					case 2:
					{
						if(ItemInfo[uid][iUsed])
							return msg_error(playerid,"Nie mo¿esz zniszczyæ przedmiotu, którego u¿ywasz.");
						
						if(CharacterInfo[playerid][pBW] || CharacterInfo[playerid][pWounded])
							return msg_error(playerid,"Nie mo¿esz zniszczyæ przedmiotów podczas BW.");
						
						new name[32];
						format(name, sizeof(name), "%s", ItemInfo[uid][iName]);
						new string[64];
						DeleteItem(uid);
						format(string, sizeof(string), "niszczy przedmiot %s.", name);
						cmd_me(playerid, string);
						log("%s[player:%d] niszczy %s[item:%d]",PlayerName3(playerid),CharacterInfo[playerid][pUID],name,uid);
					}
					case 3:
					{
						new string[512], title[128], name[32], value1, value2, type, typename[32];
						name = ItemInfo[uid][iName];
						value1 = ItemInfo[uid][iValue1];
						value2 = ItemInfo[uid][iValue2];
						type = ItemInfo[uid][iType];
						
						format(typename, sizeof(typename), "%s", ItemTypeInfo[type][iTypeName]);
						
						format(title, sizeof(title), "Przedmiot %s (UID: %d)", ItemInfo[uid][iName], uid);
						
						format(string, sizeof(string), "UID przedmiotu:\t%d", uid);
						format(string, sizeof(string), "%s\nNazwa przedmiotu:\t%s", string, ItemInfo[uid][iName]);
						format(string, sizeof(string), "%s\nTyp przedmiotu:\t%s", string, typename);
						format(string, sizeof(string), "%s\nWartoœæ (1) przedmiotu:\t%d", string, value1);
						format(string, sizeof(string), "%s\nWartoœæ (2) przedmiotu:\t%d", string, value2);
						format(string, sizeof(string), "%s\nTyp w³aœciciela:\tGracz", string);
						
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_TABLIST, title, string, "Zamknij", "");
					}
					case 4:
					{
						if(ItemInfo[uid][iValue1] > 1)
						{
							if(ItemInfo[uid][iType] == ITEM_TYPE_SEED || ItemInfo[uid][iType] == ITEM_TYPE_MARIHUANA || ItemInfo[uid][iType] == ITEM_TYPE_KOKAINA || ItemInfo[uid][iType] == ITEM_TYPE_HEROINA || ItemInfo[uid][iType] == ITEM_TYPE_LSD)
								ShowPlayerDialog(playerid, D_SPLIT, DIALOG_STYLE_INPUT, DEF_NAME" » rozdzielanie przedmiotu", "Wartoœæ dzielimy na dwa, czyli np. pierwotnie przedmiot ma 4, a dzielimy go na dwa przedmioty 3 i 1.\n\nWpisz wartoœæ, któr¹ chcesz uzyskaæ:", "Dalej", "Zamknij");
							else if(ItemInfo[uid][iType] == ITEM_TYPE_BRON && ItemInfo[uid][iValue1] == 23)
							{
								if(!ItemInfo[uid][iUsed])
								{
									ItemInfo[uid][iValue1] = 22;
									StworzPrzedmiot(OWNER_PLAYER, ItemInfo[uid][iOwner], "T³umik [9mm]", ITEM_TYPE_SILENCER, 1, 1, 1);
									mysql_query_format("UPDATE `srv_items` SET `value1` = '%d' WHERE `uid` = '%d' LIMIT 1", ItemInfo[uid][iValue1], uid);
								}
								else
									msg_error(playerid,"Nie mo¿esz odmontowaæ t³umika w u¿ywanej broni.");
							}
							else
								return msg_error(playerid,"Nie mo¿esz rozdzieliæ tego przedmiotu.");
						}
						else
							return msg_error(playerid,"Nie mo¿esz rozdzieliæ tego przedmiotu.");
					}
					case 5:
					{
						ForeachEx(i, _ITEM_COUNT)
						{
							if(ItemInfo[i][iOwnerTyp] == OWNER_PLAYER && ItemInfo[i][iOwner] == CharacterInfo[playerid][pUID] && ItemInfo[i][iUID] != uid)
							{
								if(ItemInfo[uid][iType] == ItemInfo[i][iType])
								{
									ItemInfo[uid][iValue1] += ItemInfo[i][iValue1];
								
									DeleteItem(i);
								}
							}
						}
						
						new query[128];
						format(query, sizeof(query), "UPDATE `srv_items` SET `value1` = '%d' WHERE `uid` = '%d' LIMIT 1", ItemInfo[uid][iValue1], uid);
						mysql_query(query);
						
						msg_info(playerid, "Po³¹czy³eœ wszystkie podobne przedmioty (ten sam typ) w jeden.");
					}
				}
			}
			return 1;
		}
		case D_ITEM_PICK:
		{
			if(response)
			{
				new uid = strval(inputtext);
				OnPlayerPickItem(playerid, uid);
			}
			return 1;
		}
		case D_AP_USUN:
		{
			if(response)
			{
				new item_uid = GetPVarInt(playerid, "apdeleteuid");
				DeletePVar(playerid, "apdeleteuid");
				
				if(ItemInfo[item_uid][iOwnerTyp] == OWNER_NONE && ItemInfo[item_uid][iDroppedInfo])
					Delete3DTextLabel(ItemInfo[item_uid][iDroppedInfo]);
				
				log("%s usuwa przedmiot %s[item:%d]",CharacterInfo[playerid][pGlobalNick],ItemInfo[item_uid][iName],item_uid);
				
				DeleteItem(item_uid);
				
				SendClientMessageFormat(playerid, COLOR_RED, "[AI] Przedmiot o UID: %d zosta³ usuniêty.", item_uid);
			}
			return 1;
		}
		case D_AP_NAME:
		{
			if(response)
			{
				new name[32];
				mysql_real_escape_string(inputtext,inputtext);
				format(name, sizeof(name), "%s", inputtext);
				
				new item_uid = GetPVarInt(playerid, "apnameuid");
				DeletePVar(playerid, "apnameuid");
				
				mysql_query_format("UPDATE `srv_items` SET `name` = '%s' WHERE `UID` = '%d' LIMIT 1", name, item_uid);
				
				ItemInfo[item_uid][iName] = name;
				
				SendClientMessage(playerid, COLOR_GREEN, "[AI] Zmiana nazwy przedmiotu zakoñczona powodzeniem.");
			}
			return 1;
		}
		case D_AP_TYPE:
		{
			if(response)
			{
				new type = listitem;
				new item_uid = GetPVarInt(playerid, "aptypeuid");
				DeletePVar(playerid, "aptypeuid");
				
				mysql_query_format("UPDATE `srv_items` SET `type` = '%d' WHERE `UID` = '%d' LIMIT 1", type, item_uid);
				
				ItemInfo[item_uid][iType] = type;
				
				SendClientMessage(playerid, COLOR_GREEN, "[AI] Zmiana typu przedmiotu zakoñczona powodzeniem.");
			}
			return 1;
		}
		case D_AP_VALUE1:
		{
			if(response)
			{
				new value1 = strval(inputtext);
				SetPVarInt(playerid, "value1", value1);
				
				ShowPlayerDialog(playerid, D_AP_VALUE2, DIALOG_STYLE_INPUT, DEF_NAME" » wartoœæ przedmiotu", "Wpisz wartoœæ (2) przedmiotu.", "Zmieñ", "Anuluj");
			}
			return 1;
		}
		case D_AP_VALUE2:
		{
			if(response)
			{
				new item_uid = GetPVarInt(playerid, "apvalueuid");
				new value1 = GetPVarInt(playerid, "value1");
				new value2 = strval(inputtext);
				
				mysql_query_format("UPDATE `srv_items` SET `value1` = '%d', `value2` = '%d' WHERE `UID` = '%d' LIMIT 1", value1, value2, item_uid);
				
				ItemInfo[item_uid][iValue1] = value1;
				ItemInfo[item_uid][iValue2] = value2;
				
				DeletePVar(playerid, "value1");
				DeletePVar(playerid, "apvalueuid");
				
				SendClientMessage(playerid, COLOR_GREEN, "[AI] Zmiana wartoœci przedmiotu zakoñczona powodzeniem.");
			}
			return 1;
		}
		case D_LIST_VEH:
		{
			if(response)
			{
				new title[32];
				new vehuid = strval(inputtext);
				SetPVarInt(playerid, "vehuid", vehuid);
				
				format(title, sizeof(title), DEF_NAME" » Pojazd UID: %d", vehuid);
				
				ShowPlayerDialog(playerid, D_VEH_OPT, DIALOG_STYLE_LIST, title, "1. Spawn/Unspawn pojazdu\n2. Namierz pojazd", "Wybierz", "Zamknij");
			}
			return 1;
		}
		case D_VEH_OPT:
		{
			if(response)
			{
				new vehuid = GetPVarInt(playerid, "vehuid");
			
				switch(listitem)
				{
					case 0:
					{
						if(VehicleInfo[vehuid][vSpawned]) 
						{
							UnspawnVehicle(vehuid);
							Tip(playerid,3,"Pojazd odspawnowany.");
						}
						else 
						{
							switch(IsPlayerPremium(playerid))
							{
								case 0:
								{
									if(VehSpawned[playerid])
										msg_info(playerid, "Maksymalna liczba pojazdów jak¹ mo¿esz zespawnowaæ to 1 (dla premium 3).");
									else
									{
										LoadVehicle(vehuid);
										Tip(playerid,3,"Pojazd zespawnowany.");
									}
								}
								case 1:
								{
									if(VehSpawned[playerid] > 2)
										msg_info(playerid, "Maksymalna liczba pojazdów jak¹ mo¿esz zespawnowaæ to 3.");
									else
									{
										LoadVehicle(vehuid);
										Tip(playerid,3,"Pojazd zespawnowany.");
									}
								}
							}
						}
					}
					case 1:
					{
						if(!VehicleInfo[vehuid][vSpawned])
							return msg_error(playerid,"Wybrany pojazd nie jest zespawnowany.");
						if(GetPVarInt(playerid,"pPackage") || GetPVarInt(playerid,"TransportFuel") || GetPVarInt(playerid,"Transport"))
							return msg_error(playerid,"Podczas transportu paczek nie mo¿esz skorzystaæ z tej komendy");

						if(!CharacterInfo[playerid][pCheckpoint])
						{
							new Float:x,Float:y,Float:z;
							GetVehiclePos(VehicleInfo[vehuid][vSAMPID],x,y,z);
							CharacterInfo[playerid][pCheckpoint] = SetPlayerCheckpoint(playerid,x,y,z, 5.0);
						}
						else
						{
							DisablePlayerCheckpoint(playerid);
							CharacterInfo[playerid][pCheckpoint]=0;
						}
					}
				}
				
				DeletePVar(playerid, "vehuid");
			}
			return 1;
		}
		case D_VEH_MEN:
		{
			if(response)
			{
				new vehuid = GetVehicleUID(GetPlayerVehicleID(playerid));
				
				switch(listitem)
				{
					case 0:
						cmd_pojazd(playerid,"m");
					case 1:
						cmd_pojazd(playerid,"b");
					case 2:
					{
						cmd_pojazd(playerid,"l");
						cmd_pojazd(playerid,"");
					}
					case 3:
					{
						cmd_kluczyk(playerid, "");
						cmd_pojazd(playerid, "");
					}
					case 4:
					{
						new string[128];
						format(string, sizeof(string), "UID:\t\t%d\nSAMPID:\t%d\nModel:\t\t%s (%d)\nHP:\t\t%.2f\n", vehuid, VehicleInfo[vehuid][vSAMPID], GetVehicleModelName(VehicleInfo[vehuid][vModel]), VehicleInfo[vehuid][vModel], VehicleInfo[vehuid][vHP]);
						if(VehicleInfo[vehuid][vOwnerTyp]==OWNER_PLAYER)
							format(string,sizeof(string),"%s\nW³aœciciel:\t%s",string,LoadPlayerName(VehicleInfo[vehuid][vOwner]));
						else if(VehicleInfo[vehuid][vOwnerTyp]==OWNER_GROUP)
							format(string,sizeof(string),"%s\nW³aœciciel:\t%s [UID: %d]",string,GroupInfo[VehicleInfo[vehuid][vOwner]][gName],VehicleInfo[vehuid][vOwner]);					
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » informacje o pojezdzie", string, "Zamknij", "");
					}
					case 5:
						cmd_przedmiot(playerid,"szukaj");
					case 6:
					{
						if(VehicleInfo[vehuid][vTuning] & TUNING_VISUAL)
						{
							new query[96],string[512];
							format(query,sizeof(query),"SELECT `name` FROM `srv_tuning` WHERE `vehicle`='%d'",vehuid);
							mysql_query(query);
							mysql_store_result();
							while(mysql_fetch_row_format(query, "|") == 1)
								format(string,sizeof(string),"%s\n%s",string,query);
							mysql_free_result();
							ShowPlayerDialog(playerid,D_INFO,DIALOG_STYLE_LIST, DEF_NAME" » tuning pojazdu",string,"OK","");
						}
						else
							msg_info(playerid,"Brak tuningu w pojeŸdzie");
					}
					case 7:
						cmd_pojazd(playerid,"opis");
					case 8:
					{
						if(IsOwnerVehicle(playerid, vehuid, true))
						{
							if(CharacterInfo[playerid][pCash] < 2500)
								return msg_error(playerid, "Nie posiadasz odpowiedniej kwoty ($2.500).");
							
							GivePlayerCash(playerid, -2500);
							StworzPrzedmiot(OWNER_PLAYER, CharacterInfo[playerid][pUID], "Kluczyki do pojazdu", ITEM_TYPE_CARKEYS, vehuid, 1, 1);
							msg_info(playerid, "Stworzy³eœ kluczyki do pojazdu. Znajdziesz je pod /p.");
						}
						else
							msg_error(playerid, "Nie jesteœ w³aœcicielem pojazdu.");
					}
					case 9:
					{
						if(IsOwnerVehicle(playerid, vehuid, true))
						{
							new list[256];
							
							format(list, sizeof(list), "#\tUID\tNazwa\tRanga");
							
							for(new i=1;i < MAX_PLAYER_GROUPS; i++)
								if(MemberGroup[playerid][i][GroupID])
									format(list, sizeof(list), "%s\n%d\t%d\t%s\t%s", list, i, MemberGroup[playerid][i][GroupID], GroupInfo[MemberGroup[playerid][i][GroupID]][gName], MemberGroup[playerid][i][GroupRankName]);
							
							SetPVarInt(playerid, "changevehowner", vehuid);
							
							if(strlen(list) > 21) ShowPlayerDialog(playerid, D_CHANGE_VEH_OWNER_V, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » lista grup", list, "Przepisz", "Anuluj");
							else msg_error(playerid, "Nie nale¿ysz do ¿adnej grupy.");
						}
						else
							msg_error(playerid, "Nie jesteœ w³aœcicielem pojazdu.");
					}
					case 10:
						cmd_pojazd(playerid,"radio");
					case 11:
					{
						if(IsOwnerVehicle(playerid, vehuid))
						{
							if(VehicleInfo[vehuid][vRegistered])
							{
								SetPVarInt(playerid, "vehuidplates", vehuid);
								
								ShowPlayerDialog(playerid, D_PLATESCHANGE, DIALOG_STYLE_INPUT, DEF_NAME" » zmiana rejestracji", "Wpisz nowa rejestracje (max 7 znaków):", "Dalej", "Anuluj");
							}
							else
								msg_error(playerid,"Twój pojazd nie jest zarejestrowany!");
						}
						else
							msg_error(playerid, "Nie jesteœ w³aœcicielem pojazdu.");
					}
				}
			}
			return 1;
		}
		case D_PHONE:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » telefon", "Aby zadzwoniæ u¿yj komendy: /dzwon [numer].", "Zamknij", "");
					case 1:
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » telefon", "Aby wys³aæ do kogoœ SMS u¿yj komendy: /sms [numer] [treœæ].", "Zamknij", "");
					case 2:
					{
						new string[2048],query[64],number,name[25];
						format(string,sizeof(string),"Numer\tNazwa\n");
						format(string,sizeof(string),"%s911\tNumer alarmowy\n555\tHurtownia\n777\tTaxi\n333\tPomoc drogowa\n{c8c8c8}--------------------{ffffff}",string);
						mysql_query_format("SELECT `number`, `name` FROM `srv_vcards` WHERE `phone_uid`='%d'",CharacterInfo[playerid][pPhone]);
						mysql_store_result();
						while(mysql_fetch_row_format(query, "|"))
						{
							sscanf(query,"p<|>ds[25]",number,name);
							format(string,sizeof(string),"%s\n%d\t%s",string,number,name);
						}
						mysql_free_result(); 
						ShowPlayerDialog(playerid, D_PHONE_CONTACTS, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » kontakty", string, "Wybierz", "WyjdŸ");
					}
					case 3:
						ShowPlayerDialog(playerid,D_PHONE_ADD_CONT,DIALOG_STYLE_INPUT,DEF_NAME" » dodaj kontakt","WprowadŸ numer kontaktu:","OK","WyjdŸ");
					case 4:
						return cmd_mp3(playerid,"");
					case 5:
					{
						if(CharacterInfo[playerid][pTog] & TOG_TELSOUND)
							CharacterInfo[playerid][pTog] -= TOG_TELSOUND;
						else
							CharacterInfo[playerid][pTog] += TOG_TELSOUND;
						
						cmd_telefon(playerid, "");
					}
				}
			}
			return 1;
		}
		case D_PHONE_CONTACTS:
		{
			if(response)
			{
				new number = strval(inputtext);
				new string[16];
				format(string,sizeof(string),"%d",number);
				if(listitem > 4)
				{
					SetPVarString(playerid, "ContactsNumber", string);
					format(string,sizeof(string),DEF_NAME" » Numer: %d",number);
					ShowPlayerDialog(playerid, D_PHONE_CONTACTS_OPT, DIALOG_STYLE_LIST ,string, "Zadzwoñ\nWyslij SMS\nZmieñ nazwê kontaktu\nUsuñ numer", "Wybierz", "WyjdŸ");
				}
				else if(listitem < 4)
					cmd_dzwon(playerid,string);
			}
			return 1;
		}
		case D_PHONE_CONTACTS_OPT:
		{
			if(response)
			{
				new number[8];
				GetPVarString(playerid, "ContactsNumber", number, 8);
				
				switch(listitem)
				{
					case 0: //Dzwoñ
					{
						cmd_dzwon(playerid, number);
						DeletePVar(playerid,"ContactsNumber");
					}
					case 1: //SMS
						ShowPlayerDialog(playerid, D_PHONE_SMS, DIALOG_STYLE_INPUT, DEF_NAME" » SMS", "Podaj treœæ wiadomoœci", "Wyslij", "WyjdŸ");
					case 2: //Zmiana nazwy
						ShowPlayerDialog(playerid, D_PHONE_CHANGE_CONT_NAME, DIALOG_STYLE_INPUT, DEF_NAME" » telefon", "Podaj now¹ nazwê kontaktu", "Wyslij", "WyjdŸ");
					case 3: //Usuñ
					{
						mysql_query_format("DELETE FROM `srv_vcards` WHERE `phone_uid`='%d' AND `number`='%d'",CharacterInfo[playerid][pPhone],strval(number));
						msg_infoFormat(playerid,64,"Numer %d zosta³ usuniêty z kontaktów.",strval(number));
						DeletePVar(playerid,"ContactsNumber");
					}
				}
			}
			else
				DeletePVar(playerid,"ContactsNumber");
			return 1;
		}
		case D_PHONE_SMS:
		{
			if(response)
			{
				if(strlen(inputtext) > 120)
					return msg_error(playerid,"Wiadomoœæ jest zbyt d³uga.");
				new number[8],msg[128];
				GetPVarString(playerid, "ContactsNumber", number, 8);
				format(msg,sizeof(msg),"%s %s",number,inputtext);
				cmd_sms(playerid,msg);
			}
			DeletePVar(playerid,"ContactsNumber");
			return 1;
		}
		case D_PHONE_CHANGE_CONT_NAME:
		{
			if(response)
			{
				if(strlen(inputtext) > 24)
					return msg_error(playerid,"Wprowadzona nazwa kontaktu jest zbyt d³uga");
				
				new number[8];
				GetPVarString(playerid, "ContactsNumber", number, 8);
				
				new name[32];
				mysql_real_escape_string(inputtext,inputtext);
				format(name, sizeof(name), "%s", inputtext);
				EscapePL(name);
				mysql_real_escape_string(name, name);
				
				mysql_query_format("UPDATE `srv_vcards` SET `name`='%s' WHERE `number`='%d' AND `phone_uid` = '%d' LIMIT 1", name, strval(number), CharacterInfo[playerid][pPhone]);
				msg_info(playerid,"Nazwa kontaktu zmieniona pomyœlnie.");
			}
			DeletePVar(playerid,"ContactsNumber");
			return 1;
		}
		case D_DOORS_REMOVE:
		{
			if(response)
			{
				new uid = GetPVarInt(playerid, "doorremoveuid");
				DeletePVar(playerid, "doorremoveuid");
				if(DoorsInfo[uid][dOwnerTyp]==OWNER_PLAYER)
					ForeachEx(i,_DOOR_COUNT)
						if(DoorsInfo[i][dOwnerTyp]==OWNER_HOUSE && DoorsInfo[i][dOwner]==uid)
							DeleteDoor(i);
				
				DeleteDoor(uid);
				
				SendClientMessageFormat(playerid, COLOR_GREEN, "[AI] Pomyœlnie usuniêto drzwi o UID: %d.", uid);
				
				ForeachEx(i,_ITEM_COUNT)
				{
					if(ItemInfo[i][iType] == ITEM_TYPE_KEEPKEY && ItemInfo[i][iValue2] == uid)
					{
						ForeachEx(x,_ITEM_COUNT)
						{
							if(ItemInfo[x][iOwnerTyp] == OWNER_SAFEKEEP_ITEM && ItemInfo[x][iOwner] == ItemInfo[i][iValue1])
								DeleteItem(i);
						}
						
						mysql_query_format("DELETE FROM `srv_safekeeps` WHERE `UID`='%d'", uid);
						
						SafeKeep[uid][sUID] = 0;
						SafeKeep[uid][sInactive] = 0;
						
						DeleteItem(i);
					}
					else if(ItemInfo[i][iOwnerTyp] == OWNER_DOOR && ItemInfo[i][iOwner] == uid)
						DeleteItem(uid);
				}
				
				ForeachEx(i,_OBJ_COUNT)
				{
					if(ObjectInfo[i][oOwnerType] == OWNER_HOUSE && ObjectInfo[i][oOwner] == uid)
						DeleteObject(i);
				}
				
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
			return 1;
		}
		case D_DOORS_NAME:
		{
			if(response)
			{
				new uid = GetPVarInt(playerid, "doornameuid");
				DeletePVar(playerid, "doornameuid");
				new name[31];
				mysql_real_escape_string(inputtext,inputtext);
				format(name, sizeof(name), "%s", inputtext);

				mysql_real_escape_string(name,name);
				DoorsInfo[uid][dName] = name;
				
				SaveDoors(uid, SAVE_DOORS_BASIC);
				
				SendClientMessage(playerid, COLOR_GREEN, "[AI] Pomyœlnie zmieni³eœ nazwê drzwi.");
			}
			return 1;
		}
		case D_BANKOMAT:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
					{
						new string[128];
						
						format(string, sizeof(string), "Twój obecny stan konta bankowego: $%d", CharacterInfo[playerid][pCredit]);
						
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » bankomat - stan konta", string, "Zamknij", "");
					}
					case 1:
					{
						if(!CharacterInfo[playerid][pCredit])
							return msg_error(playerid,"Brak œrodków na koncie.");
						
						ShowPlayerDialog(playerid, D_BANKOMAT_CASH, DIALOG_STYLE_INPUT, DEF_NAME" » bankomat", "Wpisz iloœæ gotówki do wyp³acenia:", "Wyp³aæ", "Anuluj");
					}
				}
			}
			return 1;
		}
		case D_BANKOMAT_CASH:
		{
			if(response)
			{
				new cash = strval(inputtext);
				
				if(cash <= 0 || cash > CharacterInfo[playerid][pCredit] || cash > 3000)
					return msg_error(playerid,"Wprowadzona iloœæ nie jest poprawna (nie masz wystarczaj¹co œrodków na koncie lub kwota wychodzi poza przedzia³: 1-3000).");
				
				CharacterInfo[playerid][pCredit] -= cash;
				GivePlayerCash(playerid, cash);
				
				SavePlayerStats(playerid, SAVE_PLAYER_BASIC);
				
				msg_infoFormat(playerid,64,"Pomyœlnie wyp³aci³eœ z bankomatu kwotê: $%d.", cash);
			}
			return 1;
		}
		case D_HOUSE_BUY:
		{
			if(response)
			{
				new dooruid = GetPVarInt(playerid, "housebuyuid");
				DeletePVar(playerid, "housebuyuid");
				new cash = DoorsInfo[dooruid][dOwner];
				
				switch(listitem)
				{
					case 0:
					{
						if(cash > CharacterInfo[playerid][pCash])
							return msg_error(playerid,"Nie masz wystarczaj¹co gotówki przy sobie aby dokonaæ tego zakupu.");
						
						new doorname[31];
						
						format(doorname, sizeof(doorname), "[DOM] %s", PlayerName3(playerid));
						
						DoorsInfo[dooruid][dOwnerTyp] = OWNER_PLAYER;
						DoorsInfo[dooruid][dOwner] = CharacterInfo[playerid][pUID];
						DoorsInfo[dooruid][dPickupID] = 1272;
						DoorsInfo[dooruid][dName] = doorname;
						log("%s [player:%d] kupil dom [door:%d] za $%d",PlayerName3(playerid),CharacterInfo[playerid][pUID],dooruid,cash);
						
						GivePlayerCash(playerid, -cash);
						
						new gid = -1;
						ForeachEx(guid, MAX_GROUPS)
						{
							if(GroupInfo[guid][gType] == GROUP_GOV)
							{
								gid = guid;
								break;
							}
						}
						
						if(gid != -1)
							GiveGroupCash(gid, cash);
						
						DestroyDynamicPickup(DoorsInfo[dooruid][dPickup]);
						DoorsInfo[dooruid][dPickup] = CreateDynamicPickup(DoorsInfo[dooruid][dPickupID], 1, DoorsInfo[dooruid][dEnterX], DoorsInfo[dooruid][dEnterY], DoorsInfo[dooruid][dEnterZ], DoorsInfo[dooruid][dEnterVW], DoorsInfo[dooruid][dEnterInt]);
						
						SaveDoors(dooruid, SAVE_DOORS_BASIC);
					}
					case 1:
					{
						if(cash > CharacterInfo[playerid][pCredit])
							return msg_error(playerid,"Nie masz wystarczaj¹co gotówki w banku aby dokonaæ tego zakupu.");
						
						new doorname[31];
						
						format(doorname, sizeof(doorname), "[DOM] %s", PlayerName3(playerid));
						
						DoorsInfo[dooruid][dOwnerTyp] = OWNER_PLAYER;
						DoorsInfo[dooruid][dOwner] = CharacterInfo[playerid][pUID];
						DoorsInfo[dooruid][dPickupID] = 1272;
						DoorsInfo[dooruid][dName] = doorname;
						log("%s [player:%d] kupil dom [door:%d] za $%d",PlayerName3(playerid),CharacterInfo[playerid][pUID],dooruid,cash);
						
						CharacterInfo[playerid][pCredit] -= cash;
						SavePlayerStats(playerid, SAVE_PLAYER_BASIC);
						
						new gid = -1;
						ForeachEx(guid, MAX_GROUPS)
						{
							if(GroupInfo[guid][gType] == GROUP_GOV)
							{
								gid = guid;
								break;
							}
						}
						
						if(gid != -1)
							GiveGroupCash(gid, cash);
						
						DestroyDynamicPickup(DoorsInfo[dooruid][dPickup]);
						DoorsInfo[dooruid][dPickup] = CreateDynamicPickup(DoorsInfo[dooruid][dPickupID], 1, DoorsInfo[dooruid][dEnterX], DoorsInfo[dooruid][dEnterY], DoorsInfo[dooruid][dEnterZ], DoorsInfo[dooruid][dEnterVW], DoorsInfo[dooruid][dEnterInt]);
						
						SaveDoors(dooruid, SAVE_DOORS_BASIC);
					}
				}
			}
			return 1;
		}
		case D_HOUSE_BUY_CHECK:
		{
			if(response)
			{
				CharacterInfo[playerid][pHouseCheck] = 15;
				
				SendClientMessage(playerid, COLOR_GREEN, "Przejœcie do interioru nast¹pi za 15 sekund.");
			}
			return 1;
		}
		case D_HOUSE_INFO:
		{
			if(response)
			{
				new uid = strval(inputtext);
				SetPVarInt(playerid, "houseinfo", uid);
			
				ShowPlayerDialog(playerid, D_HOUSE_INFO_MENU, DIALOG_STYLE_LIST, DEF_NAME" » zarz¹dzanie domem", "1. Informacje\n2. Lista mieszkañców", "Wybierz", "Anuluj");
			}
			return 1;
		}
		case D_HOUSE_INFO_MENU:
		{
			if(response)
			{
				new uid = GetPVarInt(playerid, "houseinfo");
			
				switch(listitem)
				{
					case 0:
					{
						new string[128];
						
						format(string, sizeof(string), "UID domu: %d\nNazwa domu: %s", uid, DoorsInfo[uid][dName]);
					
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » zarz¹dzanie domem", string, "Zamknij", "");
					}
					case 1:
					{
						if(DoorsInfo[uid][dOwner] == CharacterInfo[playerid][pUID])
						{
							new list[2048];
						
							new puid, data[512];
							
							format(list, sizeof(list), "UID\tNICK");
							
							mysql_query_format("SELECT `player_uid` from `srv_doors_members` WHERE `UID` = '%d'", uid);
							mysql_store_result();
							
							if(mysql_num_rows())
							{
								while(mysql_fetch_row_format(data, "|"))
								{
									sscanf(data, "p<|>d", puid);
									
									format(list, sizeof(list), "%s\n%d\t%s", list, puid, LoadPlayerName(puid));
								}
							}
				
							mysql_free_result();
							
							if(strlen(list) > 10) ShowPlayerDialog(playerid, D_HOUSE_MEMBERS_MEN, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » zarz¹dzanie domem", list, "Wyrzuæ", "Zamknij");
							else msg_info(playerid, "W tym domu nie ma mieszkañców.");
						}
						else msg_error(playerid, "Tylko w³aœciciel domu mo¿e u¿yæ tej opcji.");
					}
				}
			}
			return 1;
		}
		case D_HOUSE_MEMBERS_MEN:
		{
			if(response)
			{
				new puid = strval(inputtext);
				new uid = GetPVarInt(playerid, "houseinfo");
				DeletePVar(playerid, "houseinfo");
				
				mysql_query_format("DELETE FROM `srv_doors_members` WHERE `player_uid`='%d' AND `UID` = '%d' LIMIT 1", puid, uid);
				
				msg_infoFormat(playerid, 128, "Pomyœlnie wyrzuci³eœ ze swojego domu gracza o UID: %d.", puid);
			}
			return 1;
		}
		case D_HOUSE_PLACE:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
					{
						new dooruid = GetPVarInt(playerid, "placedooruid");
					
						new list[2048];
						
						ForeachEx(i,_ITEM_COUNT)
							if(ItemInfo[i][iOwnerTyp] == OWNER_HOUSE_ITEM && ItemInfo[i][iOwner] == dooruid)
								format(list, sizeof(list), "%s\n{c8c8c8}%4d:\t{ffffff}%s", list, i, ItemInfo[i][iName]);
						
						if(strlen(list) > 2) ShowPlayerDialog(playerid, D_HOUSE_PLACE_DROP, DIALOG_STYLE_LIST, DEF_NAME" » lista przedmiotów", list, "Wybierz", "Zamknij");
						else msg_info(playerid,"Brak przedmiotów w schowku.");
					}
					case 1:
					{
						new list[2048];
						
						format(list, sizeof(list), "UID\tNazwa\tWartoœæ 1\tWartoœæ 2");
						
						ForeachEx(i,_ITEM_COUNT)
							if(ItemInfo[i][iOwnerTyp] == OWNER_PLAYER && ItemInfo[i][iOwner] == CharacterInfo[playerid][pUID] && !ItemInfo[i][iUsed])
								format(list, sizeof(list), "%s\n%d\t%s\t%d\t%d", list, i, ItemInfo[i][iName], ItemInfo[i][iValue1], ItemInfo[i][iValue2]);
						
						if(strlen(list) > 34) ShowPlayerDialog(playerid, D_HOUSE_PLACE_IN, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » lista przedmiotów", list, "Wybierz", "Zamknij");
						else msg_info(playerid, "Nie posiadasz przedmiotów.");
					}
				}
			}
			return 1;
		}
		case D_HOUSE_PLACE_DROP:
		{
			if(response)
			{
				new uid = strval(inputtext);
				
				mysql_query_format("UPDATE `srv_items` SET `ownertyp` = '%d', `owner` = '%d' WHERE `UID` = '%d' LIMIT 1", OWNER_PLAYER, CharacterInfo[playerid][pUID], uid);
				
				ItemInfo[uid][iOwnerTyp] = OWNER_PLAYER;
				ItemInfo[uid][iOwner] = CharacterInfo[playerid][pUID];
				
				SendClientMessageFormat(playerid, COLOR_GREEN, "Wyci¹gn¹³eœ przedmiot (UID: %d) ze schowka.", uid);
			}
			return 1;
		}
		case D_HOUSE_PLACE_IN:
		{
			if(response)
			{
				new uid = strval(inputtext);
				new dooruid = GetPVarInt(playerid, "placedooruid");
				DeletePVar(playerid, "placedooruid");
				
				if(ItemInfo[uid][iType] == ITEM_TYPE_BRON && ItemInfo[uid][iUsed])
					return msg_error(playerid, "Nie mo¿esz schowaæ aktywnej broni.");
				
				mysql_query_format("UPDATE `srv_items` SET `ownertyp` = '%d', `owner` = '%d' WHERE `UID` = '%d' LIMIT 1", OWNER_HOUSE_ITEM, dooruid, uid);
				
				ItemInfo[uid][iOwnerTyp] = OWNER_HOUSE_ITEM;
				ItemInfo[uid][iOwner] = dooruid;
				
				msg_infoFormat(playerid, 128, "Wsadzi³eœ przedmiot %s [UID: %d] do schowka.", ItemInfo[uid][iName],uid);
			}
			return 1;
		}
		case D_SVEHICLE:
		{
			if(response)
			{
				new cat = listitem;
				
				new data[64], model, name[32], price;
				new list_cars[1024];
				
				format(list_cars, sizeof(list_cars), "MODEL\tNAZWA\tCENA");
				
				mysql_query_format("SELECT `model`, `name`, `price` FROM `srv_salon_vehicles` WHERE `category`='%d' ORDER BY `price`", cat);
				mysql_store_result();
				
				while(mysql_fetch_row_format(data, "|"))
				{
					sscanf(data, "p<|>ds[32]d", model, name, price);
					
					format(list_cars, sizeof(list_cars), "%s\n%d\t%s\t$%d", list_cars, model, name, price);
				}

				
				mysql_free_result();
				
				if(strlen(data)) ShowPlayerDialog(playerid, D_SVEHICLE_BUY, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » salon pojazdów", list_cars, "Kup", "Zamknij");
				else SendClientMessage(playerid, COLOR_RED, "Brak dostêpnych pojazdów.");
			}
			return 1;
		}
		case D_SVEHICLE_BUY:
		{
			if(response)
			{
				new model=strval(inputtext);
				
				new data[64], name[32], price;
				
				mysql_query_format("SELECT `name`, `price` FROM `srv_salon_vehicles` WHERE `model`='%d'", model);
				mysql_store_result();
				
				if(mysql_num_rows())
				{
					mysql_fetch_row_format(data);
					sscanf(data,  "p<|>s[32]d", name, price);
				}
				
				mysql_free_result();
				
				if(CharacterInfo[playerid][pCash] < price || price<=0)
				{
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » salon pojazdów", "Nie posiadasz odpowiedniej kwoty gotówki aby zakupiæ ten pojazd.", "Zamknij", "");
					return 1;
				}
				
				if(!IsPlayerPremium(playerid))
				{
					GivePlayerCash(playerid, -price);
					
					new ran = random(7);
					new uid = StworzPojazd(playerid, model, random(255), random(255), 0, 0, SalonInfo[ran][SX], SalonInfo[ran][SY], SalonInfo[ran][SZ], SalonInfo[ran][SA]);
					SendClientMessageFormat(playerid, COLOR_GREEN, "Pomyœlnie zakupi³eœ pojazd za $%d (UID: %d).", price, uid);
					log("%s[player:%d] kupi³ w salonie %s[vehicle:%d]",PlayerName3(playerid),CharacterInfo[playerid][pUID],GetVehicleModelName(model),uid);
				}
				else
				{
					SetPVarInt(playerid, "BuyVehModel", model);
					SetPVarInt(playerid, "BuyVehPrice", price);
					ShowPlayerDialog(playerid, D_SVEHICLE_BUY_P, DIALOG_STYLE_INPUT, DEF_NAME" » salon pojazdów", "Podaj kolor (1) pojazdu:", "Dalej", "Anuluj");
				}
			}
			return 1;
		}
		case D_SVEHICLE_BUY_P:
		{
			if(response)
			{
				SetPVarInt(playerid, "BuyVehC1", strval(inputtext));
				ShowPlayerDialog(playerid, D_SVEHICLE_BUY_P2, DIALOG_STYLE_INPUT, DEF_NAME" » salon pojazdów", "Podaj kolor (2) pojazdu:", "Dalej", "Anuluj");
			}
			return 1;
		}
		case D_SVEHICLE_BUY_P2:
		{
			if(response)
			{
				new model = GetPVarInt(playerid, "BuyVehModel");
				new price = GetPVarInt(playerid, "BuyVehPrice");
				new color1 = GetPVarInt(playerid, "BuyVehC1");
				new color2 = strval(inputtext);
				
				DeletePVar(playerid, "BuyVehModel");
				DeletePVar(playerid, "BuyVehPrice");
				DeletePVar(playerid, "BuyVehPrice");
				
				GivePlayerCash(playerid, -price);
				
				new ran = random(7);
				new uid = StworzPojazd(playerid, model, color1, color2, 0, 0, SalonInfo[ran][SX], SalonInfo[ran][SY], SalonInfo[ran][SZ], SalonInfo[ran][SA]);
				SendClientMessageFormat(playerid, COLOR_GREEN, "Pomyœlnie zakupi³eœ pojazd %s za $%d (UID: %d).",GetVehicleModelName(VehicleInfo[uid][vModel]) ,price, uid);
				log("%s[player:%d] kupi³ w salonie %s[vehicle:%d]",PlayerName3(playerid),CharacterInfo[playerid][pUID],GetVehicleModelName(model),uid);
			}
			return 1;
		}
		case D_CHOOSE_SPAWN:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
						ShowPlayerDialog(playerid, D_CHOOSE_SPAWN_MAIN, DIALOG_STYLE_LIST, DEF_NAME" » wybór spawnu", "Centrum (Pershing Square)\nLittle Mexico\nOstatnia zapisana pozycja\nHotel", "Wybierz", "Zamknij");
					case 1:
					{
						new list[512];
						
						format(list, sizeof(list), "Uid\tNazwa");
						
						ForeachEx(i, _DOOR_COUNT)
							if(DoorsInfo[i][dOwnerTyp] == OWNER_PLAYER && DoorsInfo[i][dOwner] == CharacterInfo[playerid][pUID])
								format(list, sizeof(list), "%s\n%d\t%s", list, i, DoorsInfo[i][dName]);
						
						new uid, data[4];
						
						mysql_query_format("SELECT `UID` from `srv_doors_members` WHERE `player_uid` = '%d'", CharacterInfo[playerid][pUID]);
						mysql_store_result();
						
						if(mysql_num_rows())
						{
							while(mysql_fetch_row_format(data, "|"))
							{
								sscanf(data, "p<|>d", uid);
								if(DoorsInfo[uid][dUID] == uid)
								{
									format(list, sizeof(list), "%s\n%d\t%s", list, uid, DoorsInfo[uid][dName]);
								}
							}
						}
						
						mysql_free_result();
						
						if(strlen(list) > 11)
							ShowPlayerDialog(playerid, D_CHOOSE_SPAWN_HOUSE, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » spawn", list, "Wybierz", "Zamknij");
						else
							return msg_error(playerid,"Nie posiadasz ¿adnych domów.");
					}
					case 2:
					{
						new list[512];
						
						format(list, sizeof(list), "Uid\tNazwa");
						
						for(new i=1;i < MAX_PLAYER_GROUPS; i++)
							if(MemberGroup[playerid][i][GroupID])
								format(list, sizeof(list), "%s\n%d\t%s", list, MemberGroup[playerid][i][GroupID], GroupInfo[MemberGroup[playerid][i][GroupID]][gName]);
						
						if(strlen(list) > 11) ShowPlayerDialog(playerid, D_CHOOSE_SPAWN_GROUPS, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » spawn", list, "Wybierz", "Zamknij");
						else msg_error(playerid,"Nie posiadzasz ¿adnych grup!");
					}
				}
			}
			return 1;
		}
		case D_CHOOSE_SPAWN_MAIN:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
						CharacterInfo[playerid][pSpawnOption] = SPAWN_TYPE_CENTRUM;
					case 1:
						CharacterInfo[playerid][pSpawnOption] = SPAWN_TYPE_LMEXICO;
					case 2:
						CharacterInfo[playerid][pSpawnOption] = SPAWN_TYPE_LASTPOS;
					case 3:
					{
						if(CharacterInfo[playerid][pHotel])
							CharacterInfo[playerid][pSpawnOption] = SPAWN_TYPE_HOTEL;
						else
							return msg_error(playerid,"Postaæ nie jest zameldowana w hotelu.");
					}
				}
				
				CharacterInfo[playerid][pSpawnOptionHouseID] = 0;
				
				SavePlayerStats(playerid, SAVE_PLAYER_SPAWN);
				
				msg_info(playerid, "Pomyœlnie zmieni³eœ spawn.");
				SetPlayerSpawn(playerid);
			}
			return 1;
		}
		case D_CHOOSE_SPAWN_HOUSE:
		{
			if(response)
			{
				CharacterInfo[playerid][pSpawnOption] = SPAWN_TYPE_HOUSE;
				CharacterInfo[playerid][pSpawnOptionHouseID] = strval(inputtext);
				
				SavePlayerStats(playerid, SAVE_PLAYER_SPAWN);
				
				msg_info(playerid, "Pomyœlnie zmieni³eœ spawn.");
				SetPlayerSpawn(playerid);
			}
			return 1;
		}
		case D_GROUP_CREATE:
		{
			if(response)
			{
				new name[32];
				if(strlen(inputtext)<3)
					return msg_error(playerid,"Nazwa grupy jest za krótka.");
				mysql_real_escape_string(inputtext,inputtext);
				
				format(name, sizeof(name), "%s", inputtext);
				
				EscapePL(name);
				
				SetPVarString(playerid, "GroupCreateName", name);
				
				ShowPlayerDialog(playerid, D_GROUP_CREATE_TAG, DIALOG_STYLE_INPUT, DEF_NAME" » tworzenie grupy", "Wpisz tag nowej grupy:", "Dalej", "Anuluj");
			}
			return 1;
		}
		case D_GROUP_CREATE_TAG:
		{
			if(response)
			{
				new tag[8], string[512];
				if(strlen(inputtext)<2)
					return msg_error(playerid,"Tag grupy jest za krótki.");
				
				format(tag, sizeof(tag), "%s", inputtext);
				
				EscapePL(tag);
				mysql_real_escape_string(tag,tag);
				
				SetPVarString(playerid, "GroupCreateTag", tag);
				
				ForeachEx(i, GROUP_COUNT + 1)
					format(string, sizeof(string), "%s\n%s", string, GroupTypeInfo[i][gTypeName]);
				
				ShowPlayerDialog(playerid, D_GROUP_CREATE_TYPE, DIALOG_STYLE_LIST, DEF_NAME" » tworzenie grupy", string, "Dalej", "Anuluj");
			}
			return 1;
		}
		case D_GROUP_CREATE_TYPE:
		{
			if(response)
			{
				new name[32], tag[8];
				new type = listitem;
				
				GetPVarString(playerid, "GroupCreateName", name, sizeof(name));
				GetPVarString(playerid, "GroupCreateTag", tag, sizeof(tag));
				
				DeletePVar(playerid, "GroupCreateName");
				DeletePVar(playerid, "GroupCreateTag");
				
				new uid = AddGroup(name, tag, type, CharacterInfo[playerid][pUID]);
				new string[128];
				format(string,sizeof(string),"[AI] Stworzy³eœ grupê UID %d: %s", uid,GroupInfo[uid][gName]);
				SendClientMessage(playerid, COLOR_GREEN, string);
				format(string,sizeof(string),"stworzyl grupe %d: %s", uid,GroupInfo[uid][gName]);
				AdminLog(playerid,string);
			}
			return 1;
		}
		case D_GROUP_CHANGE_NAME:
		{
			if(response)
			{
				new name[32];
				mysql_real_escape_string(inputtext,inputtext);
				format(name, sizeof(name), "%s", inputtext);
				
				EscapePL(name);
				
				new uid = GetPVarInt(playerid, "GroupNameChangeUID");
				DeletePVar(playerid, "GroupNameChangeUID");
				mysql_real_escape_string(name,name);
				GroupInfo[uid][gName] = name;
				SaveGroup(uid, SAVE_GROUP_BASIC);
				
				SendClientMessage(playerid, COLOR_GREEN, "[AI] Pomyœlnie zmieni³eœ nazwê grupy.");
			}
			return 1;
		}
		case D_GROUP_CHANGE_TAG:
		{
			if(response)
			{
				new tag[8];
				
				format(tag, sizeof(tag), "%s", inputtext);
				mysql_real_escape_string(tag,tag);
				EscapePL(tag);
				
				new uid = GetPVarInt(playerid, "GroupTagChangeUID");
				DeletePVar(playerid, "GroupTagChangeUID");
				
				GroupInfo[uid][gTag] = tag;
				SaveGroup(uid, SAVE_GROUP_BASIC);
				
				SendClientMessage(playerid, COLOR_GREEN, "[AI] Pomyœlnie zmieni³eœ tag grupy.");
			}
			return 1;
		}
		case D_GROUP_LIST_FLAGS:
		{
			if(response)
			{
				new uid = GetPVarInt(playerid, "GroupFlagsUID");
				DeletePVar(playerid, "GroupFlagsUID");
				
				switch(listitem)
				{
					case 0:
					{
						if(GroupInfo[uid][gFlags] & FLAG_DEPARTMENT) GroupInfo[uid][gFlags] -= FLAG_DEPARTMENT;
						else GroupInfo[uid][gFlags] += FLAG_DEPARTMENT;		
					}
					case 1:
					{
						if(GroupInfo[uid][gFlags] & FLAG_MEGAPHONE) GroupInfo[uid][gFlags] -= FLAG_MEGAPHONE;
						else GroupInfo[uid][gFlags] += FLAG_MEGAPHONE;
					}
					case 2:
					{
						if(GroupInfo[uid][gFlags] & FLAG_NICK) GroupInfo[uid][gFlags] -= FLAG_NICK;
						else GroupInfo[uid][gFlags] += FLAG_NICK;
					}
					case 3:
					{
						if(GroupInfo[uid][gFlags] & FLAG_OUT) GroupInfo[uid][gFlags] -= FLAG_OUT;
						else GroupInfo[uid][gFlags] += FLAG_OUT;
					}
					case 4:
					{
						if(GroupInfo[uid][gFlags] & FLAG_CASH) GroupInfo[uid][gFlags] -= FLAG_CASH;
						else GroupInfo[uid][gFlags] += FLAG_CASH;
					}
					case 5:
					{
						if(GroupInfo[uid][gFlags] & FLAG_JAIL) GroupInfo[uid][gFlags] -= FLAG_JAIL;
						else GroupInfo[uid][gFlags] += FLAG_JAIL;
					}
					case 6:
					{
						if(GroupInfo[uid][gFlags] & FLAG_ITEM) GroupInfo[uid][gFlags] -= FLAG_ITEM;
						else GroupInfo[uid][gFlags] += FLAG_ITEM;
					}	
					case 7:
					{
						if(GroupInfo[uid][gFlags] & FLAG_911) GroupInfo[uid][gFlags] -= FLAG_911;
						else GroupInfo[uid][gFlags] += FLAG_911;
					}
					case 8:
					{
						if(GroupInfo[uid][gFlags] & FLAG_REPORTS) GroupInfo[uid][gFlags] -= FLAG_REPORTS;
						else GroupInfo[uid][gFlags] += FLAG_REPORTS;
					}
					case 9:
					{
						if(GroupInfo[uid][gFlags] & FLAG_GPS) GroupInfo[uid][gFlags] -= FLAG_GPS;
						else GroupInfo[uid][gFlags] += FLAG_GPS;
					}
				}
				
				SaveGroup(uid, SAVE_GROUP_FLAGS);		
				new string[128];
				format(string, sizeof(string), "flagi %d", uid);
				return cmd_agrupa(playerid, string);
			}
			return 1;
		}
		case D_GROUP_VEH_OPTIONS:
		{
			if(!response) return 0;
			new veh = strval(inputtext);
			SetPVarInt(playerid, "VehicleID", veh);
					
			ShowPlayerDialog(playerid, D_GROUP_VEH_OPTIONS_SELECT, DIALOG_STYLE_LIST, DEF_NAME" » informacja", "1. Namierz pojazd\n2. SPAWN/UNSPAWN pojazdu", "Wybierz", "Zamknij");
			return 1;
		}
		case D_GROUP_VEH_OPTIONS_SELECT:
		{
			if(!response) return 0;
			new vehid = GetPVarInt(playerid, "VehicleID");
			DeletePVar(playerid, "VehicleID");
			if(listitem == 0)
			{
				if(Checkpoint[playerid])
					{
						DisablePlayerCheckpoint(playerid);
						Checkpoint[playerid] = 0;
						
						msg_info(playerid,"Namierzanie zosta³o wy³¹czone.");
					}
				else
				{
					if(GetPVarInt(playerid,"Transport"))
						return msg_error(playerid,"Podczas dostarczania paczki nie mo¿esz namierzyæ pojazdu.");	
					new Float:x, Float:y, Float:z;
					GetVehiclePos(VehicleInfo[vehid][vSAMPID], x, y, z);
						
					SetPlayerCheckpoint(playerid, x, y, z, 5.0);
					Checkpoint[playerid] = 1;
				}
			}
			else if(listitem == 1)
			{
				new string[128];
				if(!VehicleInfo[vehid][vSAMPID])
				{
					LoadVehicle(vehid);
							
					format(string, sizeof(string), "Pojazd %s (UID: %d) zosta³ zespawnowany pomyœlnie.", GetVehicleModelName(VehicleInfo[vehid][vModel]), vehid);
					msg_info(playerid, string);
				}
				else				
				{
					UnspawnVehicle(vehid);
					msg_info(playerid, "Pojazd zosta³ odspawnowany pomyœlnie.");
				}
			}
		}
		case D_GROUP_CHANGE_PERM:
		{
			if(!response) return 1;
			new giveplayer_id = GetPVarInt(playerid,"GroupPermGiveplayer");
			new slot = GetPVarInt(playerid,"GroupPermGiveplayerSlot");
			DeletePVar(playerid,"GroupPermGiveplayerSlot");
			DeletePVar(playerid,"GroupPermGiveplayer");
			switch (listitem)
			{
				case 0:
				{
					if(GroupInfo[MemberGroup[giveplayer_id][slot][GroupID]][gLeader] != CharacterInfo[playerid][pUID] && !(MemberGroup[giveplayer_id][slot][GroupPerm] & PERM_SPECIAL_LEADER))
						return msg_error(playerid,"Tylko g³ówny lider mo¿e zmieniæ to uprawnienie.");
					if(playerid==giveplayer_id)
						Tip(playerid,5,"Nie mozesz zmienic tej opcji samemu sobie.");
					else if(MemberGroup[giveplayer_id][slot][GroupPerm] & PERM_PERSONEL)
						MemberGroup[giveplayer_id][slot][GroupPerm] -= PERM_PERSONEL;
					else
						MemberGroup[giveplayer_id][slot][GroupPerm] += PERM_PERSONEL;
				}
				case 1:
				{
					if(GroupInfo[MemberGroup[giveplayer_id][slot][GroupID]][gLeader] != CharacterInfo[playerid][pUID] && !(MemberGroup[giveplayer_id][slot][GroupPerm] & PERM_SPECIAL_LEADER))
						return msg_error(playerid,"Tylko g³ówny lider mo¿e zmieniæ to uprawnienie.");
					if(MemberGroup[giveplayer_id][slot][GroupPerm] & PERM_CASH)
						MemberGroup[giveplayer_id][slot][GroupPerm] -= PERM_CASH;
					else
						MemberGroup[giveplayer_id][slot][GroupPerm] += PERM_CASH;
				}
				case 2:
				{
					if(MemberGroup[giveplayer_id][slot][GroupPerm] & PERM_VEHICLES)
						MemberGroup[giveplayer_id][slot][GroupPerm] -= PERM_VEHICLES;
					else
						MemberGroup[giveplayer_id][slot][GroupPerm] += PERM_VEHICLES;
				}
				case 3:
				{
					if(MemberGroup[giveplayer_id][slot][GroupPerm] & PERM_VEHICLES_MAN)
						MemberGroup[giveplayer_id][slot][GroupPerm] -= PERM_VEHICLES_MAN;
					else
						MemberGroup[giveplayer_id][slot][GroupPerm] += PERM_VEHICLES_MAN;
				}
				case 4:
				{
					if(MemberGroup[giveplayer_id][slot][GroupPerm] & PERM_DOOR)
						MemberGroup[giveplayer_id][slot][GroupPerm] -= PERM_DOOR;
					else
						MemberGroup[giveplayer_id][slot][GroupPerm] += PERM_DOOR;
				}
				case 5:
				{
					if(GroupInfo[MemberGroup[giveplayer_id][slot][GroupID]][gLeader] != CharacterInfo[playerid][pUID] && !(MemberGroup[giveplayer_id][slot][GroupPerm] & PERM_SPECIAL_LEADER))
						return msg_error(playerid,"Tylko g³ówny lider mo¿e zmieniæ to uprawnienie.");
					if(MemberGroup[giveplayer_id][slot][GroupPerm] & PERM_OBJECT)
						MemberGroup[giveplayer_id][slot][GroupPerm] -= PERM_OBJECT;
					else
						MemberGroup[giveplayer_id][slot][GroupPerm] += PERM_OBJECT;
				}
				case 6:
				{
					if(GroupInfo[MemberGroup[giveplayer_id][slot][GroupID]][gLeader] != CharacterInfo[playerid][pUID] && !(MemberGroup[giveplayer_id][slot][GroupPerm] & PERM_SPECIAL_LEADER))
						return msg_error(playerid,"Tylko g³ówny lider mo¿e zmieniæ to uprawnienie.");
					if(MemberGroup[giveplayer_id][slot][GroupPerm] & PERM_MAGAZINE)
						MemberGroup[giveplayer_id][slot][GroupPerm] -= PERM_MAGAZINE;
					else
						MemberGroup[giveplayer_id][slot][GroupPerm] += PERM_MAGAZINE;
				}
				case 7:
				{
					if(MemberGroup[giveplayer_id][slot][GroupPerm] & PERM_PRODUCT)
						MemberGroup[giveplayer_id][slot][GroupPerm] -= PERM_PRODUCT;
					else
						MemberGroup[giveplayer_id][slot][GroupPerm] += PERM_PRODUCT;
				}
				case 8:
				{
					if(GroupInfo[MemberGroup[giveplayer_id][slot][GroupID]][gLeader] != CharacterInfo[playerid][pUID])
						return msg_error(playerid,"Tylko g³ówny lider mo¿e zmieniæ to uprawnienie.");
					if(MemberGroup[giveplayer_id][slot][GroupPerm] & PERM_SPECIAL_LEADER)
						MemberGroup[giveplayer_id][slot][GroupPerm] -= PERM_SPECIAL_LEADER;
					else
						MemberGroup[giveplayer_id][slot][GroupPerm] += PERM_SPECIAL_LEADER;
				}
				case 9:
				{
					if(MemberGroup[giveplayer_id][slot][GroupPerm] & PERM_EXTRA)
						MemberGroup[giveplayer_id][slot][GroupPerm] -= PERM_EXTRA;
					else
						MemberGroup[giveplayer_id][slot][GroupPerm] += PERM_EXTRA;
				}
			}
			SaveMember(giveplayer_id,MemberGroup[giveplayer_id][slot][GroupID]);
			new string[64];
			format(string,sizeof(string),"%d uprawnienia %d",GetPVarInt(playerid,"GroupPermPlayerSlot"), giveplayer_id);

			DeletePVar(playerid,"GroupPermPlayerSlot");
			
			return cmd_grupa(playerid,string);
		}
		case D_LOGISTIC_ORDERS:
		{
			if(!response) return 1;
			new pack_id=strval(inputtext);
			new data[32], order_uid, status, driver, doorid;
			mysql_query_format("SELECT `uid`, `status`, `driver`, `door_uid` FROM `srv_orders` WHERE `uid` = '%d'", pack_id);

			mysql_store_result();
			mysql_fetch_row_format(data, "|");
			
			sscanf(data, "p<|>dddd", order_uid, status, driver, doorid);
			mysql_free_result();
			if(driver || status)
			{
				new string[256];
				format(string, sizeof(string), "Paczka zosta³a ju¿ dostarczona przez kuriera.\n\nNumer paczki: %d\nUID kuriera: %s", order_uid, driver);
				return msg_error(playerid,string);
			}
			mysql_query_format("UPDATE `srv_orders` SET `driver` = '%d' WHERE `uid` = '%d'", CharacterInfo[playerid][pUID], order_uid);
			
			DisablePlayerCheckpoint(playerid);
			SetPlayerCheckpoint(playerid, DoorsInfo[doorid][dEnterX], DoorsInfo[doorid][dEnterY], DoorsInfo[doorid][dEnterZ], 3.0);
			SetPVarInt(playerid,"pPackage",1);
			SetPVarInt(playerid,"pPackageID",order_uid);
			SetPVarInt(playerid,"pPackageDoor",doorid);
			SetPVarInt(playerid,"pPackegeCourierGroup",DutyGroup[playerid]);
			msg_info(playerid, "Paczka zosta³a pobrana z magazynu.\nNa mapie zosta³o oznaczone miejsce odbioru paczki.");
		}
		case D_ORDER_PRODUCT_CATEGORY:
		{
			if(!response) return 1;
			new groupid=DoorsInfo[GetPVarInt(playerid, "ProductDoor")][dOwner];
			new list_products[1024], data[64], product_uid, product_name[32], product_cash;

			format(list_products,sizeof(list_products),"SELECT `uid`, `name`, `price` FROM `srv_order_products` WHERE `grouptype` = '%d' AND `category`='%d'",GroupInfo[groupid][gType],listitem);
			mysql_query(list_products);
			mysql_store_result();
			strmid(list_products, "", 0, 0);
			format(list_products, sizeof(list_products),"Uid\tNazwa\tCena");
			while(mysql_fetch_row_format(data, "|"))
			{
				sscanf(data, "p<|>ds[32]d", product_uid, product_name, product_cash);
				
				format(list_products, sizeof(list_products), "%s\n%d\t%s\t$%d", list_products, product_uid, product_name, product_cash);
			}
			
			mysql_free_result();
			if(strlen(list_products)>20)
				ShowPlayerDialog(playerid,D_ORDER_PRODUCT, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » produkty do zamówienia", list_products, "Wybierz", "Wróæ");
			else
				msg_error(playerid,"Brak produktów do zamówienia.");

			return 1;
		}
		case D_ORDER_PRODUCT:
		{
			if(!response) return 1;
			new product_uid=strval(inputtext);			
			SetPVarInt(playerid, "ProductID", product_uid);
			
			ShowPlayerDialog(playerid, D_ORDER_VALUE, DIALOG_STYLE_INPUT, DEF_NAME" » iloœæ sztuk", "WprowadŸ iloœæ sztuk do zamówienia:", "Zamów", "Zamknij");

			return 1;
		}
		case D_ORDER_VALUE:
		{
			if(!response) return 1;
			new amount = strval(inputtext);
			new doorid = GetPVarInt(playerid, "ProductDoor");
			
			switch(GroupInfo[DoorsInfo[doorid][dOwner]][gType])
			{
				case GROUP_RESTAURANT, GROUP_KLUB, GROUP_GANG, GROUP_MAFIA:
				{
					if(amount < 1 || amount > 10)
						return msg_error(playerid,"Wprowadzona iloœæ sztuk jest nieprawid³owa (1-10).");
				}
				case GROUP_GOV, GROUP_PD, GROUP_MC, GROUP_NEWS, GROUP_FBI, GROUP_MILITARY, GROUP_SECURITY, GROUP_CARTEL, GROUP_GUNSHOP, GROUP_FUELSTATION, GROUP_GYM, GROUP_DRIVERS:
				{
					if(amount < 1 || amount > 20)
						return msg_error(playerid,"Wprowadzona iloœæ sztuk jest nieprawid³owa (1-20).");
				}
				default:
				{
					if(amount < 1 || amount > 1000)
						return msg_error(playerid,"Wprowadzona iloœæ sztuk jest nieprawid³owa.");
				}
			}
			
			if(GroupInfo[DoorsInfo[doorid][dOwner]][gType] == GROUP_RESTAURANT || GroupInfo[DoorsInfo[doorid][dOwner]][gType] == GROUP_KLUB)
			{
				SetPVarInt(playerid, "ProductValue", amount);
				ShowPlayerDialog(playerid, D_ORDER_END, DIALOG_STYLE_INPUT, DEF_NAME" » nazwa produktu", "WprowadŸ nazwê produktu, który chcesz dostaæ na magazyn:", "Zamów", "Zamknij");
			}
			else
			{
				new string[512], data[64], product_value1, product_value2, product_cash, product_kind, product_name[32];
				new product_id = GetPVarInt(playerid, "ProductID");
				DeletePVar(playerid, "ProductID");
				format(string,sizeof(string),"SELECT `value1`, `value2`, `price`, `type`, `name` FROM `srv_order_products` WHERE `uid` = '%d'", product_id);
				
				mysql_query(string);
				mysql_store_result();			
				mysql_fetch_row_format(data, "|");
				sscanf(data, "p<|>dddds[32]", product_value1, product_value2, product_cash, product_kind, product_name);
				mysql_free_result();

				new price = product_cash * amount;
				new shippment;
				
				switch(GroupInfo[DoorsInfo[doorid][dOwner]][gType])
				{
					case GROUP_FUELSTATION, GROUP_GYM, GROUP_GANG, GROUP_MAFIA:
						shippment = 20 + price/10;
					default:
						shippment = 50 + price/10;
				}
				
				if(shippment > 400)
					shippment = 400;
				
				if(GroupInfo[DoorsInfo[doorid][dOwner]][gCash] < (price + shippment))
					return msg_error(playerid,"Na koncie grupowym nie znajduje siê odpowiednia kwota na zakup produktu.");
				
				GiveGroupCash(DoorsInfo[doorid][dOwner], -(price+shippment));
				
				mysql_query_format("INSERT INTO `srv_orders` (`door_uid`, `value1`, `value2`, `name`, `count`, `driver`, `kind`, `shippment_cost`) VALUES ('%d', '%d', '%d', '%s', '%d', '%d', '%d', '%d')", DoorsInfo[doorid][dUID], product_value1, product_value2, product_name, amount, 0, product_kind, shippment);
				
				new uid = mysql_insert_id();
				
				format(string, sizeof(string), "{008000}Produkt zamówiony!");
				format(string, sizeof(string), "%s\n\n{FFFFFF}Numer przesy³ki: %d", string, uid);
				format(string, sizeof(string), "%s\nNazwa: %s", string, product_name);
				format(string, sizeof(string), "%s\nIloœæ: %d", string, amount);
				format(string, sizeof(string), "%s\nCena za szt.: $%d\n", string, product_cash);
				format(string, sizeof(string), "%s\nTransport: $%d\n£¹cznie: $%d\n\n", string, shippment, shippment + price);
				
				new bool:logistics = false;
				
				ForeachPlayer(i)
				{
					if(IsPlayerOnDutyInGroup(i, GROUP_LOGISTIC) && !(CharacterInfo[i][pStatus] & STATUS_AFK))
					{
						SendClientMessage(i, COLOR_YELLOW, "Do firmy logistycznej trafi³o nowe zamówienie, udaj siê do magazynu aby je odebraæ i zrealizowaæ!");
						if(!logistics)
							logistics = true;
					}
				}
				
				if(!logistics)
					SendClientMessage(playerid, COLOR_YELLOW, "Aktualnie ¿adna firma logistyczna nie pracuje, wiêc twoje zamówienie mo¿e przyjechaæ z opóŸnieniem.");
				
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » produkt zamówiony!", string, "Zamknij", "");
			}
			
			return 1;
		}
		case D_OUT_ITEM:
		{
			if(response)
			{
				new uid = strval(inputtext);
				new playerid2=GetPVarInt(playerid,"TakenItemPlayer");
				DeletePVar(playerid,"TakenItemPlayer");
				
				mysql_query_format("UPDATE `srv_items` SET `ownertyp` = '%d', `owner` = '%d' WHERE `UID` = '%d' LIMIT 1", OWNER_PLAYER, CharacterInfo[playerid][pUID], uid);
				
				ItemInfo[uid][iOwnerTyp] = OWNER_PLAYER;
				ItemInfo[uid][iOwner] = CharacterInfo[playerid][pUID];
				
				log("%s[player:%d] zabiera %s[player:%d] %s[item:%d]",PlayerName3(playerid),CharacterInfo[playerid][pUID],PlayerName3(playerid2),CharacterInfo[playerid2][pUID],ItemInfo[uid][iName],uid);
				new string[64];
				format(string, sizeof(string), "zabiera %s przedmiot %s.", PlayerName2(playerid2),ItemInfo[uid][iName]);
				SendClientMessageFormat(playerid2,COLOR_RED,"%s(%d) zabra³ Ci przedmiot %s [UID: %d]",PlayerName2(playerid),playerid,ItemInfo[uid][iName],uid);
				cmd_me(playerid, string);
			}
			DeletePVar(playerid, "TakenItemPlayer");
			return 1;
		}
		case D_DEATH:
		{
			if(!response) return 1;
			new gun[32];
			if(GetPVarString(playerid, "KillWeapon", gun, sizeof(gun) < 3))
				format(gun, sizeof(gun), "-");
			new gun_val = GetPVarInt(playerid, "KillWeaponVal");
			
			DeletePVar(playerid, "KillWeapon");
			DeletePVar(playerid, "KillWeaponVal");
			
			new Float:x,Float:y,Float:z;
			GetPlayerPos(playerid,x,y,z);
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

			mysql_real_escape_string(inputtext,inputtext);
			z-=1.0;
			mysql_query_format("INSERT INTO `srv_corpse` VALUES (NULL,'%d','%s','%s','%s','%d','%s','%d','%f','%f','%f','%d','%d')",CharacterInfo[playerid][pUID],PlayerName3(playerid),inputtext,gun,gun_val,date,CharacterInfo[playerid][pCash],x,y,z,GetPlayerInterior(playerid),GetPlayerVirtualWorld(playerid));
			new uid=mysql_insert_id();
			new reason[128];
			format(reason,sizeof(reason),"%s",inputtext);
			CorpseInfo[uid][corpseID]=uid;
			CorpseInfo[uid][corpsePlayerUID]=CharacterInfo[playerid][pUID];
			CorpseInfo[uid][corpsePlayerName]=PlayerName3(playerid);
			CorpseInfo[uid][corpseReason]=reason;
			CorpseInfo[uid][corpseGun]=gun;
			CorpseInfo[uid][corpseGunVal]=gun_val;
			CorpseInfo[uid][corpseDate]=date;
			CorpseInfo[uid][corpseMoney]=CharacterInfo[playerid][pCash];
			CorpseInfo[uid][corpseX]=x;
			CorpseInfo[uid][corpseY]=y;
			CorpseInfo[uid][corpseZ]=z;
			CorpseInfo[uid][corpseInt]=GetPlayerInterior(playerid);
			CorpseInfo[uid][corpseVW]=GetPlayerVirtualWorld(playerid);
			CorpseInfo[uid][corpseObject] = CreateDynamicObject(19944, CorpseInfo[uid][corpseX], CorpseInfo[uid][corpseY], CorpseInfo[uid][corpseZ], 0, 0, 0, CorpseInfo[uid][corpseVW], CorpseInfo[uid][corpseInt], -1);
			format(reason, sizeof(reason), "Zw³oki {636363}(%d)",uid);
			CorpseInfo[uid][corpseText] = CreateDynamic3DTextLabel(reason, COLOR_RED, CorpseInfo[uid][corpseX], CorpseInfo[uid][corpseY], CorpseInfo[uid][corpseZ]+0.75, 7.0,INVALID_PLAYER_ID, INVALID_VEHICLE_ID,1, CorpseInfo[uid][corpseVW]);

			CharacterInfo[playerid][pCash]=0;
			CharacterInfo[playerid][pBlock]+=BLOCK_CK;
			ForeachEx(i,_ITEM_COUNT)
			{
				if(ItemInfo[i][iOwnerTyp]==OWNER_PLAYER && ItemInfo[i][iOwner]==CharacterInfo[playerid][pUID])
				{
					ItemInfo[i][iUsed]=0;
					ItemInfo[i][iOwnerTyp]=OWNER_CORPSE;
					ItemInfo[i][iOwner]=uid;
					format(reason,sizeof(reason),"UPDATE `srv_items` SET `owner`='%d', `ownertyp`='%d' WHERE `UID`='%d' LIMIT 1",ItemInfo[i][iOwner],ItemInfo[i][iOwnerTyp],ItemInfo[i][iUID]);
					mysql_query(reason);
				}
			}

			KickWithWait(playerid);
			return 1;
		}
		case D_DESCRIPTION:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
					{
						new string[2048];
						new data[256];
						new text[128];
						
						format(string, sizeof(string), "UID\tTREŒÆ");
						
						ForeachEx(uid, _DESC_COUNT)
						{
							if(DescriptionInfo[uid][descUID] && DescriptionInfo[uid][descOwner] == CharacterInfo[playerid][pUID])
							{
								mysql_query_format("SELECT `text` FROM `srv_descriptions_text` WHERE `UID` = '%d'", uid);
								mysql_store_result();
								
								if(mysql_num_rows())
								{
									mysql_fetch_row_format(data);
									sscanf(data, "p<|>s[128]", text);
									
									if(strlen(text) > 20)
									{
										new pos = strfind(text, " ", true, 20);
										if(pos != -1)
										{
											strdel(text, pos, strlen(text));
											format(text, sizeof(text), "%s ...", text);
										}
									}
									
									format(string, sizeof(string), "%s\n%d\t%s", string, uid, text);
								}
								
								mysql_free_result();
							}
						}
						
						if(strlen(string) > 11) 
							ShowPlayerDialog(playerid, D_DESCRIPTION_OPT, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » lista opisów", string, "Opcje", "Anuluj");
						else
							return msg_error(playerid, "Nie posiadasz ¿adnych opisów.");
					}
					case 1:
					{
						ShowPlayerDialog(playerid, D_DESCRIPTION_CREATE, DIALOG_STYLE_INPUT, DEF_NAME" » nowy opis", "WprowadŸ nowy opis do listy:", "Dodaj", "Anuluj");
					}
					case 2:
					{
						if(Description[playerid] != Text3D:INVALID_3DTEXT_ID)
						{
							DestroyDynamic3DTextLabel(Description[playerid]);
							Description[playerid] = Text3D:INVALID_3DTEXT_ID;
							CharacterInfo[playerid][pCurrentDescription] = 0;
							msg_info(playerid, "Usun¹³eœ swój aktualny opis z postaci.");
						}
						else
							msg_error(playerid, "Nie posiadasz na sobie ¿adnego opisu.");
					}
					case 3:
					{
						if(Description[playerid] != Text3D:INVALID_3DTEXT_ID)
							msg_info(playerid, CharacterInfo[playerid][pCurrentDescription]);
						else
							msg_error(playerid, "Nie posiadasz na sobie ¿adnego opisu.");
					}
				}
			}
			return 1;
		}
		case D_WALKIE_CHANGE:
		{
			if(response)
			{
				new kanal = strval(inputtext);
				
				if(kanal < 1 || kanal > 2000)
					return msg_error(playerid,"Wprowadzono niepoprawny numer kana³u.");
				new query[128],channel = -1, creator, password[12];
				format(query,sizeof(query),"SELECT * FROM `srv_walkie_channels` WHERE `channel`='%d'",kanal);
				mysql_query(query);
				mysql_store_result();
				mysql_fetch_row_format(query);
				if(mysql_num_rows())
					sscanf(query, "p<|>dds[12]",channel,creator,password);
				mysql_free_result();
				if(channel == -1)
					return msg_error(playerid,"Nie znaleziono kana³u o podanym numerze.\nAby stworzyc kana³ u¿yj /radio zalozkanal.");

				if(!strlen(password))
				{
					CharacterInfo[playerid][pKanal] = kanal;
					SavePlayerStats(playerid,SAVE_PLAYER_OPTION);
					
					return msg_info(playerid, "Kana³ radiowy zosta³ zmieniony.");
				}
				else
				{
					SetPVarInt(playerid,"pWalkieChannel",kanal);
					ShowPlayerDialog(playerid, D_WALKIE_CHANGE_PASSWD, DIALOG_STYLE_INPUT, DEF_NAME" » kana³ radiowy", "WprowadŸ has³o kana³u radiowego:", "Wybierz", "WyjdŸ");
				}

			}
			return 1;
		}
		case D_DESCRIPTION_CREATE:
		{
			if(response)
			{
				if(strlen(inputtext) > 127)
					return msg_error(playerid, "Wpisany opis jest zbyt d³ugi.");
				
				if(!ValidateDesc(inputtext, IsPlayerPremium(playerid)))
					return msg_error(playerid, "Opis postaci zawiera niedozwolony znak lub znaki!");
				
				new current = 0;
				ForeachEx(uid, _DESC_COUNT)
				{
					if(DescriptionInfo[uid][descUID] && DescriptionInfo[uid][descOwner] == CharacterInfo[playerid][pUID])
						current++;
					
					if(current == 5)
						break;
				}
				
				if(IsPlayerPremium(playerid))
				{
					if(current < 5)
					{
						new uid;
						
						ForeachEx(i, MAX_DESCRIPTIONS)
						{
							if(DescriptionInfo[i][descUID] == 0 && i != 0)
							{
								uid = i;
								break;
							}
						}
						if(!uid)
							return msg_error(playerid, "Osi¹gniêto maksymaln¹ iloœc opisów na serwerze.");
						
						if(uid+1>_DESC_COUNT)
							_DESC_COUNT = uid + 1;
						
						mysql_query_format("INSERT INTO `srv_descriptions` VALUES ('%d', '%d')", uid, CharacterInfo[playerid][pUID]);
						mysql_real_escape_string(inputtext, inputtext);
						mysql_query_format("INSERT INTO `srv_descriptions_text` VALUES ('%d', '%s')", uid, inputtext);
						
						DescriptionInfo[uid][descUID] = uid;
						DescriptionInfo[uid][descOwner] = CharacterInfo[playerid][pUID];
						
						msg_info(playerid, "Doda³eœ nowy opis do swojej listy.");
					}
					else
						return msg_error(playerid, "Nie mo¿esz dodaæ wiêcej opisów (max 5).");
				}
				else
				{
					if(current < 3)
					{
						new uid;
						
						ForeachEx(i, MAX_DESCRIPTIONS)
						{
							if(DescriptionInfo[i][descUID] == 0 && i != 0)
							{
								uid = i;
								break;
							}
						}
						if(!uid)
							return msg_error(playerid, "Osi¹gniêto maksymaln¹ iloœc opisów na serwerze.");
						
						if(uid+1>_DESC_COUNT)
							_DESC_COUNT = uid + 1;
						
						mysql_query_format("INSERT INTO `srv_descriptions` VALUES ('%d', '%d')", uid, CharacterInfo[playerid][pUID]);
						
						DescriptionInfo[uid][descUID] = uid;
						DescriptionInfo[uid][descOwner] = CharacterInfo[playerid][pUID];
						
						mysql_real_escape_string(inputtext, inputtext);
						mysql_query_format("INSERT INTO `srv_descriptions_text` VALUES ('%d', '%s')", uid, inputtext);
						
						msg_info(playerid, "Doda³eœ nowy opis do swojej listy.");
					}
					else
						return msg_error(playerid, "Nie mo¿esz dodaæ wiêcej opisów (max 3).");
				}
			}
			return 1;
		}
		case D_OFFER_ITEM:
		{
			if(response)
			{
				new uid = strval(inputtext);
				
				if(ItemInfo[uid][iUsed])
					return msg_error(playerid,"Nie mo¿esz oferowaæ przedmiotu, którego u¿ywasz.");
				
				new string[256];
				
				ForeachPlayer(i)
					if(PlayerToPlayer(5.0, playerid, i) && i != playerid)
						format(string, sizeof(string), "%s\n%d\t%s", string, i, PlayerName2(i));
				
				SetPVarInt(playerid, "OfertaPrzedmiotUID", uid);
				
				if(strlen(string))
					ShowPlayerDialog(playerid, D_OFFER_ITEM_END, DIALOG_STYLE_LIST, DEF_NAME" » wybierz gracza", string, "Wybierz", "Anuluj");
				else
					msg_error(playerid,"Nie ma nikogo w pobli¿u!");
			}
			return 1;
		}
		case D_OFFER_ITEM_END:
		{
			if(response)
			{
				new playerid2 = strval(inputtext);
				new uid = GetPVarInt(playerid, "OfertaPrzedmiotUID");
				new cena = GetPVarInt(playerid, "OfertaPrzedmiotCena");
				if(CharacterInfo[playerid2][pHours]<2)
					return msg_error(playerid,"Nie mo¿na oferowaæ przedmiotów postaciom maj¹cym mniej, ni¿ 2 godziny online.");
				
				Oferta(OFFER_ITEM, playerid, playerid2, cena, uid);
			}
			return 1;
		}
		case D_OFFER_VEHICLE:
		{
			if(!response) return 1;
			new playerid2=strval(inputtext);
			new uid = GetPVarInt(playerid, "OfferVehicleUID");
			new price = GetPVarInt(playerid, "OfferPrice");
			if(CharacterInfo[playerid2][pHours]<2)
					return msg_error(playerid,"Nie mo¿na oferowaæ pojazdów postaciom maj¹cym mniej, ni¿ 2 godziny online.");
			SetPVarInt(playerid,"OfferBuyer",playerid2);
			new string[128];
			format(string,sizeof(string),"Czy na pewno chcesz sprzedaæ %s(%d) pojazd %s [UID:%d] za $%d?",PlayerName2(playerid2),playerid2,GetVehicleModelName(VehicleInfo[uid][vModel]),uid,price);
			ShowPlayerDialog(playerid,D_OFFER_VEHICLE_END,DIALOG_STYLE_MSGBOX,DEF_NAME" » sprzeda¿ pojazdu",string,"Tak","Nie");
			return 1;
		}
		case D_OFFER_VEHICLE_END:
		{
			if(!response) return 1;

			Oferta(OFFER_VEHICLE, playerid, GetPVarInt(playerid,"OfferBuyer"), GetPVarInt(playerid, "OfferPrice"), GetPVarInt(playerid, "OfferVehicleUID"));
			return 1;
		}
		case D_BAGAZNIK:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
					{
						new vehid = GetPVarInt(playerid, "BagaznikID");
						new vehuid = GetVehicleUID(vehid);
					
						if(!GetVehicleBootStatus(vehid))
							ChangeVehicleBootStatus(vehid, true);
						
						new list[2048];
						
						format(list, sizeof(list), "UID\tNAZWA\tVALUE1\tVALUE2");
						
						ForeachEx(i,_ITEM_COUNT)
							if(ItemInfo[i][iUID])
								if(ItemInfo[i][iOwnerTyp] == OWNER_BAGAZNIK && ItemInfo[i][iOwner] == vehuid)
									format(list, sizeof(list), "%s\n%d\t{878A87}%s\t%d\t%d", list, ItemInfo[i][iUID], ItemInfo[i][iName], ItemInfo[i][iValue1], ItemInfo[i][iValue2]);
						
						if(strlen(list) > 27) ShowPlayerDialog(playerid, D_BAGAZNIK_OUT, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » baga¿nik", list, "Wybierz", "Anuluj");
						else
						{
							Tip(playerid, 3, "Brak przedmiotow w bagazniku.");
							
							if(GetVehicleBootStatus(vehid))
								ChangeVehicleBootStatus(vehid, false);
						}
					}
					case 1:
					{
						new vehid = GetPVarInt(playerid, "BagaznikID");
					
						if(!GetVehicleBootStatus(vehid))
							ChangeVehicleBootStatus(vehid, true);
						
						new list[2048];
						
						format(list, sizeof(list), "UID\tNAZWA\tVALUE1\tVALUE2");
						
						ForeachEx(i,_ITEM_COUNT)
							if(ItemInfo[i][iUID])
								if(ItemInfo[i][iOwnerTyp] == OWNER_PLAYER && ItemInfo[i][iOwner] == CharacterInfo[playerid][pUID] && !ItemInfo[i][iUsed])
									format(list, sizeof(list), "%s\n%d\t{878A87}%s\t%d\t%d", list, ItemInfo[i][iUID], ItemInfo[i][iName], ItemInfo[i][iValue1], ItemInfo[i][iValue2]);
						
						if(strlen(list) > 27) ShowPlayerDialog(playerid, D_BAGAZNIK_IN, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » baga¿nik", list, "Wybierz", "Anuluj");
						else
						{
							Tip(playerid, 3, "Nie posiadasz przedmiotow.");
							
							if(GetVehicleBootStatus(vehid))
								ChangeVehicleBootStatus(vehid, false);
						}
					}
				}
			}
			return 1;
		}
		case D_BAGAZNIK_OUT:
		{
			if(response)
			{
				new vehid = GetPVarInt(playerid, "BagaznikID");
				DeletePVar(playerid, "BagaznikID");
				new uid = strval(inputtext);
				
				if(GetVehicleBootStatus(vehid))
					ChangeVehicleBootStatus(vehid, false);
				
				mysql_query_format("UPDATE `srv_items` SET `ownertyp` = '%d', `owner` = '%d' WHERE `UID` = '%d' LIMIT 1", OWNER_PLAYER, CharacterInfo[playerid][pUID], uid);
				
				ItemInfo[uid][iOwnerTyp] = OWNER_PLAYER;
				ItemInfo[uid][iOwner] = CharacterInfo[playerid][pUID];

				log("%s[player:%d] wyciaga %s[item:%d] z bagaznika [veh:%d]",PlayerName3(playerid),CharacterInfo[playerid][pUID],ItemInfo[uid][iName],uid,GetVehicleUID(vehid));
				
				new string[128];
				
				format(string, sizeof(string), "wyci¹ga przedmiot %s z baga¿nika.", ItemInfo[uid][iName]);
				cmd_me(playerid, string);
			}
			else
			{
				new vehid = GetPVarInt(playerid, "BagaznikID");
				DeletePVar(playerid, "BagaznikID");
				
				if(GetVehicleBootStatus(vehid))
					ChangeVehicleBootStatus(vehid, false);
				
				return 1;
			}
		}
		case D_BAGAZNIK_IN:
		{
			if(response)
			{
				new vehid = GetPVarInt(playerid, "BagaznikID");
				DeletePVar(playerid, "BagaznikID");
				new vehuid = GetVehicleUID(vehid);
				new uid = strval(inputtext);
				
				if(GetVehicleBootStatus(vehid))
					ChangeVehicleBootStatus(vehid, false);
				
				mysql_query_format("UPDATE `srv_items` SET `ownertyp` = '%d', `owner` = '%d' WHERE `UID` = '%d' LIMIT 1", OWNER_BAGAZNIK, vehuid, uid);
				
				ItemInfo[uid][iOwnerTyp] = OWNER_BAGAZNIK;
				ItemInfo[uid][iOwner] = vehuid;

				log("%s[player:%d] odklada %s[item:%d] w bagazniku [veh:%d]",PlayerName3(playerid),CharacterInfo[playerid][pUID],ItemInfo[uid][iName],uid,vehuid);
				
				new string[128];
				
				format(string, sizeof(string), "wk³ada przedmiot %s do baga¿nika.", ItemInfo[uid][iName]);
				cmd_me(playerid, string);
			}
			else
			{
				new vehid = GetPVarInt(playerid, "BagaznikID");
				DeletePVar(playerid, "BagaznikID");
				
				if(GetVehicleBootStatus(vehid))
					ChangeVehicleBootStatus(vehid, false);
				
				return 1;
			}
		}
		case D_DOOR_CHANGE_RADIO:
		{
			new doorid=PlayerDoor[playerid];
			if(response)
			{
				new audio_url[128];
				strmid( audio_url, inputtext, 0, strlen( inputtext ), 128 );
				if( strlen( audio_url ) > 128 )
					return msg_error(playerid,"Wprowadzony adres URL jest za d³ugi");
				strmid( DoorsInfo[doorid][dRadio], audio_url, 0, strlen( audio_url ), 128 );
				ForeachPlayer(i)
				{
					if(CharacterInfo[i][pUID] && PlayerDoor[i] == doorid && !(CharacterInfo[i][pStatus] & STATUS_MP3) && !(IsPlayerInAnyVehicle(i) && VehicleInfo[GetVehicleUID(GetPlayerVehicleID(i))][vRadio]))
					{
						StopAudioStreamForPlayer(i);
						PlayAudioStreamForPlayer(i, DoorsInfo[doorid][dRadio]);
					}
				}
			}
			else
			{
				strmid(DoorsInfo[doorid][dRadio], ".", 0, 0);
				ForeachPlayer(i)
					if( CharacterInfo[i][pUID] && PlayerDoor[i] == doorid && !(CharacterInfo[playerid][pStatus] & STATUS_MP3) )
						StopAudioStreamForPlayer( i );
				
				msg_info(playerid,"Radio w drzwiach zosta³o wy³¹czone.");
			}
			SaveDoors(doorid,SAVE_DOORS_BASIC);
			return 1;
		}
		case D_VEH_RADIO_LINK:
		{
			new vehid = GetVehicleUID(GetPlayerVehicleID(playerid));
			if(!vehid) return 1;
			if(response)
			{
				if(strlen(inputtext) < 2 || strlen(inputtext) >= 128)
					return msg_error(playerid, "Wprowadzony adres URL jest za d³ugi");
				
				if(!ValidateDesc(inputtext))
					return msg_error(playerid, "Wprowadzony adres nie jest prawid³owy.");
				
				mysql_real_escape_string(inputtext, inputtext);
				SaveVehRadio(vehid, inputtext);
				ForeachPlayer(i)
				{
					if(CharacterInfo[i][pUID] && GetPlayerVehicleID(i)==VehicleInfo[vehid][vSAMPID] && !(CharacterInfo[playerid][pStatus] & STATUS_MP3))
					{
						StopAudioStreamForPlayer(i);
						PlayAudioStreamForPlayer(i, inputtext);
					}
				}
			}
			else
			{
				SaveVehRadio(vehid, ".");
				msg_info(playerid, "Radio w pojeŸdzie zosta³o wy³¹czone.");
			}
			
			SaveVehicle(vehid,SAVE_VEH_BASIC);
		}
		case D_VEH_RADIO:
		{
			new veh_sampid=GetPlayerVehicleID(playerid);
			new vehid=GetVehicleUID(veh_sampid);
			if(response)
			{
				new audio_url[128];
				new radioCount = sizeof(RadioStations);
				if(0 <= listitem < radioCount)
				{
					strins(audio_url,RadioStations[listitem][radioURL], 0);
				} 
				else if(listitem == radioCount)
				{
					ShowPlayerDialog(playerid,D_VEH_RADIO_LINK,DIALOG_STYLE_INPUT,DEF_NAME" » radio","Podaj adres URL:","Wybierz","Anuluj");
					return 1;
				}
				else
				{
					SaveVehRadio(vehid,".");
					VehicleInfo[vehid][vRadio]=0;
					msg_info(playerid,"Radio w pojeŸdzie zosta³o wy³¹czone.");
					ForeachPlayer(i)
						if( CharacterInfo[i][pUID] && GetPlayerVehicleID(i)==veh_sampid && !(CharacterInfo[playerid][pStatus] & STATUS_MP3) )
							StopAudioStreamForPlayer( i );
					SaveVehicle(vehid,SAVE_VEH_BASIC);
					return 1;
				}
				
				SaveVehRadio(vehid,audio_url);
				VehicleInfo[vehid][vRadio]=1;
				SaveVehicle(vehid,SAVE_VEH_BASIC);
				ForeachPlayer(i)
				{
					if( CharacterInfo[i][pUID] )
					{
						if( GetPlayerVehicleID(i)==veh_sampid && !(CharacterInfo[playerid][pStatus] & STATUS_MP3) )
						{
							StopAudioStreamForPlayer( i );
							PlayAudioStreamForPlayer( i, audio_url);
						}
					}
				}
			}
			SaveVehicle(vehid,SAVE_VEH_BASIC);
		}
		case D_BOOMBOX:
		{
			if( !response ) return 1;
			new radioCount = sizeof(RadioStations);
			if(0 <= listitem < radioCount)
			{
				cmd_boombox(playerid,RadioStations[listitem][radioURL]);
			}
			else
			{
				msg_usage(playerid,"U¿yj: /boombox [url]");
			}
			
			
			return 1;
		}
		case D_DOCS:
		{
			if(!response) return 1;
			switch(listitem)
			{
				case 0:
				{
					if(CharacterInfo[playerid][pDocs] & DOC_ID)
						return msg_error(playerid,"Masz ju¿ dowód osobisty");
					if(CharacterInfo[playerid][pCash] < SettingInfo[sDocID])
						return msg_error(playerid,"Nie posiadasz wystarczaj¹cej iloœci gotówki na wyrobienie dokumentu.");
					CharacterInfo[playerid][pDocs] += DOC_ID;
					GivePlayerCash(playerid,-SettingInfo[sDocID]);
					GiveOfficialGroupCash(GROUP_GOV,SettingInfo[sDocID]);
					msg_info(playerid,"Pomyœlnie wyrobi³eœ dowód osobisty.");
					SavePlayerStats(playerid,SAVE_PLAYER_OPTION);
				}
				case 1:
				{
					if(CharacterInfo[playerid][pDocs] & DOC_DRIVER)
						return msg_error(playerid,"Masz ju¿ prawo jazdy");
					if(CharacterInfo[playerid][pCash] < SettingInfo[sDocDriver])
						return msg_error(playerid,"Nie posiadasz wystarczaj¹cej iloœci gotówki na wyrobienie dokumentu.");
					CharacterInfo[playerid][pDocs] += DOC_DRIVER;
					GivePlayerCash(playerid,-SettingInfo[sDocDriver]);
					GiveOfficialGroupCash(GROUP_GOV,SettingInfo[sDocDriver]);
					msg_info(playerid,"Pomyslnie wyrobi³eœ prawo jazdy.");
					SavePlayerStats(playerid,SAVE_PLAYER_OPTION);
				}
				case 2:
				{
					if(CharacterInfo[playerid][pDocs] & DOC_PILOT)
						return msg_error(playerid,"Masz ju¿ licencjê pilota");
					if(CharacterInfo[playerid][pCash] < SettingInfo[sDocPilot])
						return msg_error(playerid,"Nie posiadasz wystarczaj¹cej iloœci gotówki na wyrobienie dokumentu.");
					CharacterInfo[playerid][pDocs] += DOC_PILOT;
					GivePlayerCash(playerid,-SettingInfo[sDocPilot]);
					GiveOfficialGroupCash(GROUP_GOV,SettingInfo[sDocPilot]);
					msg_info(playerid,"Pomyslnie wyrobi³eœ licencjê pilota.");
				}
				case 3:
				{
					if(CharacterInfo[playerid][pCash] < SettingInfo[sPlateCharge])
						return msg_error(playerid,"Nie posiadasz wystarczaj¹cej iloœci gotówki na wyrobienie rejestracji.");
					
					ShowPlayerDialog(playerid, D_REGISTER_VEHICLE_BOT, DIALOG_STYLE_INPUT, DEF_NAME" » rejestracja", "Wpisz UID pojazdu jaki chcesz zarejestrowaæ:", "Zarejestruj", "Anuluj");
				}
				case 4:
				{
					if(CharacterInfo[playerid][pCash] < SettingInfo[sGroupRegisterCharge])
						return msg_error(playerid,"Nie posiadasz wystarczaj¹cej iloœci gotówki na wyrobienie rejestracji.");
					
					new list[256];
					
					format(list, sizeof(list), "#\tUID\tNazwa\tRanga");
					
					for(new i=1;i < MAX_PLAYER_GROUPS; i++)
						if(MemberGroup[playerid][i][GroupID])
							format(list, sizeof(list), "%s\n%d\t%d\t%s\t%s", list, i, MemberGroup[playerid][i][GroupID], GroupInfo[MemberGroup[playerid][i][GroupID]][gName], MemberGroup[playerid][i][GroupRankName]);
					
					ShowPlayerDialog(playerid, D_REGISTER_GROUP_BOT, DIALOG_STYLE_TABLIST, DEF_NAME" » rejestracja", list, "Zarejestruj", "Anuluj");
				}
			}
			SavePlayerStats(playerid,SAVE_PLAYER_OPTION);
			return 1;
		}
		case D_LSPD:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
					{
						new list[2048];
						
						format(list, sizeof(list), "UID\tMODEL\tKWOTA");
						
						ForeachEx(uid, _VEH_COUNT)
							if(VehicleInfo[uid][vUID] && VehicleInfo[uid][vBlokada])
								format(list, sizeof(list), "%s\n%d\t%s\t$%d", list, VehicleInfo[uid][vUID], GetVehicleModelName(VehicleInfo[uid][vModel]), VehicleInfo[uid][vBlokada]);
						
						if(strlen(list) > 18) ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » blokady pojazdów", list, "Zamknij", "");
						else msg_info(playerid, "Brak pojazdów z blokad¹.");
					}
					case 1:
						ShowPlayerDialog(playerid, D_KARTOTEKI, DIALOG_STYLE_LIST, DEF_NAME" » kartoteki", "1. Przegl¹daj kartoteki\n2. Dodaj kartotekê", "Wybierz", "Zamknij");
					case 2:
						ShowPlayerDialog(playerid, D_POSZUKIWANI, DIALOG_STYLE_LIST, DEF_NAME" » poszukiwani", "1. Przegl¹daj poszukiwane osoby\n2. Dodaj now¹ osobê", "Wybierz", "Zamknij");
					case 3:
					{
						new vehid = GetPlayerVehicleID(playerid);
						new vehuid = GetVehicleUID(vehid);
						
						if(IsPlayerInAnyVehicle(playerid) && (VehicleInfo[vehuid][vOwnerTyp] == OWNER_GROUP && VehicleInfo[vehuid][vOwner] == DutyGroup[playerid]))
						{
							new string[1024];
							
							ForeachPlayer(i)
								if(PlayerToPlayer(10.0, playerid, i) && i != playerid)
									format(string, sizeof(string), "%s\n%d\t%s", string, i, PlayerName2(i));
							
							if(strlen(string)<4)
								return msg_error(playerid,"Brak graczy w pobli¿u");
								
							ShowPlayerDialog(playerid, D_COMP, DIALOG_STYLE_LIST, DEF_NAME" » Mobile Data Terminal", string, "Wybierz", "Zamknij");
						}
						else
							msg_error(playerid, "Nie znajdujesz siê w odpowiednim pojezdzie.");
					}
				}
			}
			return 1;
		}
		case D_KARTOTEKI:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
						ShowPlayerDialog(playerid, D_KARTOTEKI_SEARCH, DIALOG_STYLE_LIST, DEF_NAME" » kartoteki", "1. Wyszukaj poprzez UID postaci\n2. Wyszukaj poprzez ID gracza", "Wybierz", "Zamknij");
					case 1:
					{
						new string[1024];
						
						ForeachPlayer(i)
							if(PlayerToPlayer(5.0, playerid, i) && i != playerid)
								format(string, sizeof(string), "%s\n%d\t%s", string, i, PlayerName2(i));
						
						if(strlen(string)<4)
							return msg_error(playerid,"Brak graczy w pobli¿u.");
						ShowPlayerDialog(playerid, D_KARTOTEKI_NEW, DIALOG_STYLE_LIST, DEF_NAME" » kartoteki", string, "Wybierz", "Zamknij");
					}
				}
			}
			return 1;
		}
		case D_KARTOTEKI_SEARCH:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
						ShowPlayerDialog(playerid, D_KARTOTEKI_SEARCH_UID, DIALOG_STYLE_INPUT, DEF_NAME" » kartoteki", "Wpisz UID szukanej osoby:", "Szukaj", "Zamknij");
					case 1:
						ShowPlayerDialog(playerid, D_KARTOTEKI_SEARCH_ID, DIALOG_STYLE_INPUT, DEF_NAME" » kartoteki", "Wpisz ID szukanej osoby:", "Szukaj", "Zamknij");
				}
			}
			return 1;
		}
		case D_KARTOTEKI_NEW:
		{
			if(response)
			{
				new playerid2 = strval(inputtext);
				
				if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
					return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
				
				new puid = CharacterInfo[playerid2][pUID];
				
				mysql_query_format("SELECT * FROM `srv_kartoteki` WHERE `player_uid` = '%d'", puid);
				mysql_store_result();
				
				if(mysql_num_rows())
					return msg_info(playerid,"Wybrany gracz posiada ju¿ kartotekê.");
				
				mysql_free_result();
				
				mysql_query_format("INSERT INTO `srv_kartoteki` VALUES (NULL, '%d')", puid);
				
				new uid = mysql_insert_id();
				
				msg_infoFormat(playerid, 64, "Stworzy³eœ now¹ kartotekê o ID: %d.", uid);
			}
			return 1;
		}
		case D_KARTOTEKI_SEARCH_UID:
		{
			if(response)
			{
				new puid = strval(inputtext);
				
				new data[512];
				new uid;
				
				mysql_query_format("SELECT `UID` FROM `srv_kartoteki` WHERE `player_uid` = '%d' LIMIT 1", puid);
				mysql_store_result();
				
				if(!mysql_num_rows())
				{
					msg_info(playerid, "Wybrany gracz nie posiada kartoteki.");
					mysql_free_result();
					return 1;
				}
				else
				{
					new string[1024];
					new age, sex, jail_time;
					mysql_fetch_row_format(data, "|");
					sscanf(data, "p<|>d", uid);
					
					mysql_free_result();
					mysql_query_format("SELECT `age`, `sex`, `jail_time` FROM `srv_characters` WHERE `player_uid` = '%d' LIMIT 1", puid);
					mysql_store_result();
					
					mysql_fetch_row_format(data, "|");
					sscanf(data, "p<|>ddd", age, sex, jail_time);
					
					mysql_free_result();
					
					if(jail_time) format(string, sizeof(string), "ID kartoteki: {878A87}%d\nImiê i nazwisko: {878A87}%s\nWiek: {878A87}%d\nP³eæ: {878A87}%s\nAktualnie w areszcie: {C90000}TAK (%d)\n{878A87}Zobacz wpisy w kartotece", uid, LoadPlayerName(puid), age, GetSexName(sex), jail_time);
					else format(string, sizeof(string), "ID kartoteki: {878A87}%d\nImiê i nazwisko: {878A87}%s\nWiek: {878A87}%d\nP³eæ: {878A87}%s\nAktualnie w areszcie: {02AD38}NIE\n{878A87}Zobacz wpisy w kartotece", uid, LoadPlayerName(puid), age, GetSexName(sex));
					
					SetPVarInt(playerid, "kartoid", uid);
					
					ShowPlayerDialog(playerid, D_KARTOTEKI_RECORDS, DIALOG_STYLE_LIST, DEF_NAME" » kartoteki", string, "Wybierz", "Zamknij");
				}
			}
			return 1;
		}
		case D_KARTOTEKI_SEARCH_ID:
		{
			if(response)
			{
				new playerid2 = strval(inputtext);
				
				if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
					return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
				
				new puid = CharacterInfo[playerid2][pUID];
				
				new data[512];
				new uid;
				
				mysql_query_format("SELECT `UID` FROM `srv_kartoteki` WHERE `player_uid` = '%d' LIMIT 1", puid);
				mysql_store_result();
				
				if(!mysql_num_rows())
				{
					msg_info(playerid, "Wybrany gracz nie posiada kartoteki.");
					mysql_free_result();
				}
				else
				{
					new string[1024];
					mysql_fetch_row_format(data, "|");
					sscanf(data, "p<|>d", uid);
					
					mysql_free_result();
					
					if(CharacterInfo[playerid2][pJailTime] > gettime()) format(string, sizeof(string), "ID kartoteki: {878A87}%d\nImiê i nazwisko: {878A87}%s\nWiek: {878A87}%d\nP³eæ: {878A87}%s\nAktualnie w areszcie: {C90000}TAK (%d godzin/y)\n{878A87}Zobacz wpisy w kartotece", uid, PlayerName3(playerid2), CharacterInfo[playerid2][pAge], GetSexName(CharacterInfo[playerid2][pSex]), (CharacterInfo[playerid2][pJailTime]-gettime())/60/60);
					else format(string, sizeof(string), "ID kartoteki: {878A87}%d\nImiê i nazwisko: {878A87}%s\nWiek: {878A87}%d\nP³eæ: {878A87}%s\nAktualnie w areszcie: {02AD38}NIE\n{878A87}Zobacz wpisy w kartotece", uid, PlayerName3(playerid2), CharacterInfo[playerid2][pAge], GetSexName(CharacterInfo[playerid2][pSex]));
					
					SetPVarInt(playerid, "kartoid", uid);
					
					ShowPlayerDialog(playerid, D_KARTOTEKI_RECORDS, DIALOG_STYLE_LIST, DEF_NAME" » kartoteki", string, "Wybierz", "Zamknij");
				}
			}
			return 1;
		}
		case D_KARTOTEKI_RECORDS:
		{
			if(response)
			{
				if(listitem == 5)
				{
					new list[1024];
					new data[1024];
					
					format(list, sizeof(list), "{878A87}Dodaj nowy wpis\n{878A87}----------\n");
					
					new uid = GetPVarInt(playerid, "kartoid");
					
					mysql_query_format("SELECT `ID`, `date` FROM `srv_kartoteki_records` WHERE `UID` = '%d'", uid);
					mysql_store_result();
					
					if(!mysql_num_rows())
						format(list, sizeof(list), "%s\nBrak wpisów w kartotece.", list);
					else
					{
						new id, date[16];
						
						while(mysql_fetch_row_format(data, "|"))
						{
							sscanf(data, "p<|>ds[16]", id, date);
							
							format(list, sizeof(list), "%s\n%d\t%s", list, id, date);
						}
						
						mysql_free_result();
					}
					
					ShowPlayerDialog(playerid, D_KARTOTEKI_RECORDS_NEXT, DIALOG_STYLE_LIST, DEF_NAME" » kartoteki", list, "Wybierz", "Zamknij");
				}
			}
			return 1;
		}
		case D_KARTOTEKI_RECORDS_NEXT:
		{
			if(response)
			{
				if(listitem == 0)
					ShowPlayerDialog(playerid, D_KARTOTEKI_ADD_RECORD, DIALOG_STYLE_INPUT, DEF_NAME" » kartoteki", "Wpisz powód (max 32 znaki):", "Dalej", "Anuluj");
				else if(listitem > 1)
				{
					new id = strval(inputtext);
					
					if(id == 0) return 1;
					
					SetPVarInt(playerid, "recordid", id);
					
					new record[32], date[16], data[64];
					
					mysql_query_format("SELECT `record`, `date` FROM `srv_kartoteki_records` WHERE `ID`='%d' LIMIT 1", id);
					mysql_store_result();
					
					mysql_fetch_row_format(data, "|");
					sscanf(data, "p<|>s[32]s[16]", record, date);
					
					new string[256];
					
					if(DutyGroup[playerid] && GroupInfo[DutyGroup[playerid]][gLeader] == CharacterInfo[playerid][pUID] && GroupInfo[DutyGroup[playerid]][gType] == GROUP_PD)
					{
						format(string, sizeof(string), "ID wpisu: {878A87}%d\nData wpisu: {878A87}%s\nTreœæ wpisu: {878A87}%s\n{878A87}----------\n{C90000}Edytuj wpis\n{C90000}Usuñ wpis", id, date, record);
						ShowPlayerDialog(playerid, D_KARTOTEKI_RECORD_INFO, DIALOG_STYLE_LIST, DEF_NAME" » kartoteki", string, "Wybierz", "Zamknij");
					}
					else
					{
						format(string, sizeof(string), "ID wpisu: {878A87}%d\nData wpisu: {878A87}%s\nTreœæ wpisu: {878A87}%s", id, date, record);
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, DEF_NAME" » kartoteki", string, "Zamknij", "");
					}
				}
			}
			return 1;
		}
		case D_KARTOTEKI_ADD_RECORD:
		{
			if(response)
			{
				new string[32];
				mysql_real_escape_string(inputtext,inputtext);
				format(string, sizeof(string), "%s", inputtext);
				
				new kuid = GetPVarInt(playerid, "kartoid");
				DeletePVar(playerid, "kartoid");
				
				new year, day, mo, date[16];
				getdate(year, mo, day);
				format(date, sizeof(date), "%02d/%02d/%02d", day, mo, year);

				mysql_query_format("INSERT INTO `srv_kartoteki_records` VALUES (NULL, '%d', '%s', '%s')", kuid, date, string);
				
				msg_info(playerid, "Doda³eœ nowy wpis do kartoteki.");
			}
			return 1;
		}
		case D_KARTOTEKI_RECORD_INFO:
		{
			if(response)
			{
				if(listitem == 4)
					ShowPlayerDialog(playerid, D_KARTOTEKI_EDIT, DIALOG_STYLE_INPUT, DEF_NAME" » kartoteki", "Wpisz nowy powód (wpis - max 32 znaki):", "Dalej", "Anuluj");
				else if(listitem == 5)
					ShowPlayerDialog(playerid, D_KARTOTEKI_REMOVE_CONF, DIALOG_STYLE_MSGBOX, DEF_NAME" » kartoteki", "Jesteœ pewny, ¿e chcesz usun¹æ ten wpis z kartotek?", "Tak", "Nie");
			}
			return 1;
		}
		case D_POSZUKIWANI:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
						ShowPlayerDialog(playerid, D_POSZUKIWANI_SEARCH, DIALOG_STYLE_LIST, DEF_NAME" » poszukiwani", "1. Wyszukaj poprzez UID postaci\n2. Wyszukaj poprzez ID gracza", "Wybierz", "Zamknij");
					case 1:
						ShowPlayerDialog(playerid, D_POSZUKIWANI_NEW, DIALOG_STYLE_INPUT, DEF_NAME" » kartoteki", "Wpisz ID gracza, którego chcesz dodaæ do listy poszukiwanych:", "Dalej", "Zamknij");
				}
			}
			return 1;
		}
		case D_ADD_AMMO:
		{
			if(response)
			{
				new ammouid = GetPVarInt(playerid, "ammouid");
				DeletePVar(playerid, "ammouid");
				new weaponuid = strval(inputtext);
				
				ItemInfo[weaponuid][iValue2] += ItemInfo[ammouid][iValue2];
				
				mysql_query_format("UPDATE `srv_items` SET `value2` = '%d' WHERE `uid` = '%d' LIMIT 1", ItemInfo[weaponuid][iValue2], weaponuid);
				
				DeleteItem(ammouid);
				
				msg_info(playerid,"Amunicja w broni zosta³a uzupe³niona.");
			}
			return 1;
		}
		case D_CHOOSE_SPAWN_GROUPS:
		{
			if(response)
			{
				new groupid = strval(inputtext);
				
				CharacterInfo[playerid][pSpawnOption] = SPAWN_TYPE_GROUP;
				
				CharacterInfo[playerid][pSpawnOptionHouseID] = groupid;
				
				SavePlayerStats(playerid, SAVE_PLAYER_SPAWN);
				
				msg_info(playerid, "Pomyœlnie zmieni³eœ spawn.");
			}
			return 1;
		}
		case D_AG_DELETE:
		{
			if(response)
			{
				new uid = GetPVarInt(playerid, "GroupDeleteID");
				DeletePVar(playerid, "GroupDeleteID");
				if(!uid)
					SendClientMessage(playerid, COLOR_RED, "B³¹d usuwania grupy!");
				else
				{
					new string[128];
					format(string,sizeof(string),"[AI] Usun¹³eœ grupê %d: %s.",uid,GroupInfo[uid][gName]);
					SendClientMessage(playerid, COLOR_GREEN, string);
					format(string,sizeof(string),"Usunal grupe %d: %s.",uid,GroupInfo[uid][gName]);
					DeleteGroup(uid);
					AdminLog(playerid,string);
				}
			}
			return 1;
		}
		case D_PRZESZUKAJ:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
					{
						new vehid = GetPVarInt(playerid, "przeszukajid");
						DeletePVar(playerid, "przeszukajid");
						new vehuid = GetVehicleUID(vehid);
						
						new list[2048];
						
						format(list, sizeof(list), "UID\tVALUE1\tVALUE2\tNAZWA");
						
						ForeachEx(i,_ITEM_COUNT)
							if(ItemInfo[i][iOwnerTyp] == OWNER_VEHICLE && ItemInfo[i][iOwner] == vehuid)
								format(list, sizeof(list), "%s\n%d\t%d\t%d\t{878A87}%s", list, ItemInfo[i][iUID], ItemInfo[i][iValue1], ItemInfo[i][iValue2], ItemInfo[i][iName]);
						
						new string[64];
						format(string, sizeof(string), "przeszukuje pojazd %s.", GetVehicleModelName(GetVehicleModel(vehid)));
						cmd_me(playerid, string);
						
						if(strlen(list) > 27) ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » przedmioty w pojezdzie", list, "Zamknij", "");
						else msg_info(playerid,"Nie znaleziono przedmiotów w pojezdzie.");
					}
					case 1:
					{
						new vehid = GetPVarInt(playerid, "przeszukajid");
						DeletePVar(playerid, "przeszukajid");
						new vehuid = GetVehicleUID(vehid);
						
						new list[2048];
						
						format(list, sizeof(list), "UID\tVALUE1\tVALUE2\tNAZWA");
						
						ForeachEx(i,_ITEM_COUNT)
							if(ItemInfo[i][iOwnerTyp] == OWNER_BAGAZNIK && ItemInfo[i][iOwner] == vehuid)
								format(list, sizeof(list), "%s\n%d\t%d\t%d\t{878A87}%s", list, ItemInfo[i][iUID], ItemInfo[i][iValue1], ItemInfo[i][iValue2], ItemInfo[i][iName]);
						
						new string[64];
						format(string, sizeof(string), "przeszukuje bagaznik pojazdu %s.", GetVehicleModelName(GetVehicleModel(vehid)));
						cmd_me(playerid, string);
						
						if(strlen(list) > 27) ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » przedmioty w bagazniku", list, "Zamknij", "");
						else msg_info(playerid,"Nie znaleziono przedmiotów w bagazniku.");
					}
				}
			}
			return 1;
		}
		case D_APRZESZUKAJ:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
					{
						new vehid = GetPVarInt(playerid, "przeszukajid");
						DeletePVar(playerid, "przeszukajid");
						new vehuid = GetVehicleUID(vehid);
						
						new list[2048];
						
						format(list, sizeof(list), "UID\tVALUE1\tVALUE2\tNAZWA");
						
						ForeachEx(i,_ITEM_COUNT)
							if(ItemInfo[i][iOwnerTyp] == OWNER_VEHICLE && ItemInfo[i][iOwner] == vehuid)
								format(list, sizeof(list), "%s\n%d\t%d\t%d\t{878A87}%s", list, ItemInfo[i][iUID], ItemInfo[i][iValue1], ItemInfo[i][iValue2], ItemInfo[i][iName]);
						
						if(strlen(list) > 27) ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » przedmioty w pojezdzie", list, "Zamknij", "");
						else Tip(playerid,3,"Nic nie znalazles");
					}
					case 1:
					{
						new vehid = GetPVarInt(playerid, "przeszukajid");
						DeletePVar(playerid, "przeszukajid");
						new vehuid = GetVehicleUID(vehid);
						
						new list[2048];
						
						format(list, sizeof(list), "UID\tVALUE1\tVALUE2\tNAZWA");
						
						ForeachEx(i,_ITEM_COUNT)
							if(ItemInfo[i][iOwnerTyp] == OWNER_BAGAZNIK && ItemInfo[i][iOwner] == vehuid)
								format(list, sizeof(list), "%s\n%d\t%d\t%d\t{878A87}%s", list, ItemInfo[i][iUID], ItemInfo[i][iValue1], ItemInfo[i][iValue2], ItemInfo[i][iName]);
						
						if(strlen(list) > 27) ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » przedmioty w bagazniku", list, "Zamknij", "");
						else Tip(playerid,3,"Nic nie znalazles");
					}
				}
			}
			return 1;
		}
		case D_GROUP_MAGAZINE_LAST:
		{
			if(response)
			{
				new uid = GetPVarInt(playerid, "maggid");
				DeletePVar(playerid, "maggid");
				new ilosc = strval(inputtext);
				
				if(ilosc < 1)
					return msg_error(playerid, "Wpisana iloœæ nie jest prawid³owa.");
				
				if(ItemInfo[uid][iIlosc] < ilosc)
					return msg_error(playerid, "Nie ma tylu przedmiotów w magazynie.");
				else if(ItemInfo[uid][iIlosc] < 1)
					return msg_error(playerid, "Zle podana wartoœæ (musi byæ równa lub wiêksza od 1).");

				if(ilosc ==1 && ItemInfo[uid][iIlosc]==1)
				{
					ItemInfo[uid][iOwnerTyp]=OWNER_PLAYER;
					ItemInfo[uid][iOwner]=CharacterInfo[playerid][pUID];
					mysql_query_format("UPDATE `srv_items` SET `owner` = '%d', `ownertyp`='%d' WHERE `uid` = '%d' LIMIT 1",ItemInfo[uid][iOwner],OWNER_PLAYER, uid);
				}
				else
				{
					new name[32];
					format(name, sizeof(name), "%s", ItemInfo[uid][iName]);
					
					for(new i = 1; i<=ilosc; i++)
						StworzPrzedmiot(OWNER_PLAYER, CharacterInfo[playerid][pUID], name, ItemInfo[uid][iType], ItemInfo[uid][iValue1], ItemInfo[uid][iValue2], 1);

					if(ItemInfo[uid][iIlosc] == ilosc)
						DeleteItem(uid);
					else
					{
						ItemInfo[uid][iIlosc] -= ilosc;
						mysql_query_format("UPDATE `srv_items` SET `ilosc` = '%d' WHERE `UID`='%d' LIMIT 1", ItemInfo[uid][iIlosc], uid);
					}
				}
				
				msg_infoFormat(playerid, 128, "Wyci¹gn¹³eœ przedmiot %s z magazynu grupy.", ItemInfo[uid][iName]);
			}
			return 1;
		}
		case D_SPLIT:
		{
			if(response)
			{
				new val1 = strval(inputtext);
				new uid = GetPVarInt(playerid, "ItemUID");
				DeletePVar(playerid, "ItemUID");
				
				if(val1 < 1 || ItemInfo[uid][iValue1] < val1 || !val1)
					return msg_error(playerid, "Wpisana wartoœæ nie jest prawid³owa.");
				
				new name[32];
				format(name, sizeof(name), "%s", ItemInfo[uid][iName]);
				
				StworzPrzedmiot(OWNER_PLAYER, CharacterInfo[playerid][pUID], name, ItemInfo[uid][iType], ItemInfo[uid][iValue1]-val1, 1, 1);
				ItemInfo[uid][iValue1] = val1;
				mysql_query_format("UPDATE `srv_items` SET `value1` = '%d' WHERE `uid` = '%d' LIMIT 1", val1, uid);
				
				msg_info(playerid, "Podzieli³eœ przedmiot na dwa nowe, sprawdŸ /przedmiot!");
			}
			return 1;
		}
		case D_PLAY_ANIM:
		{
			if(response)
			{
				new anim_id = listitem + 1;
				
				if(AnimInfo[anim_id][aAction] != 2)
					ApplyAnimation( playerid, AnimInfo[anim_id][aLib], AnimInfo[anim_id][aName], AnimInfo[anim_id][aSpeed], AnimInfo[anim_id][aOpt1], AnimInfo[anim_id][aOpt2], AnimInfo[anim_id][aOpt3], AnimInfo[anim_id][aOpt4], AnimInfo[anim_id][aOpt5], 1 );
				else
					SetPlayerSpecialAction(playerid, AnimInfo[anim_id][aOpt1]);

				Tip( playerid, 2, "Aby przerwac animacje uzyj ~g~PPM~w~." );
				if(! (CharacterInfo[playerid][pStatus] & STATUS_PLAY_ANIM))
					CharacterInfo[playerid][pStatus] += STATUS_PLAY_ANIM;
			}
			return 1;
		}
		case D_ITEM_BUY:
		{
			if(response)
			{
				new itemid = strval(inputtext);
				new groupid = GetPVarInt(playerid, "ItemBuyGroupID");
				DeletePVar(playerid, "ItemBuyGroupID");
				
				if(ItemInfo[itemid][iPrice]<=0)
					return msg_error(playerid,"Przedmiot posiada nieprawid³ow¹ cenê.");
				
				if(CharacterInfo[playerid][pCash] < ItemInfo[itemid][iPrice])
					return msg_error(playerid,"Nie posiadasz wystarczaj¹cej iloœci gotówki na zakup tego przedmiotu.");
				
				GivePlayerCash(playerid,-ItemInfo[itemid][iPrice]);
				GiveGroupCash(groupid, ItemInfo[itemid][iPrice]);
				
				new name[32];
				format(name, sizeof(name), "%s", ItemInfo[itemid][iName]);
				
				new msg[128];
				format(msg, sizeof(msg), "Kupi³eœ przedmiot %s za $%d.", name, ItemInfo[itemid][iPrice]);
				SendClientMessage(playerid, COLOR_GREEN, msg);
				
				StworzPrzedmiot(OWNER_PLAYER, CharacterInfo[playerid][pUID], name, ItemInfo[itemid][iType], ItemInfo[itemid][iValue1], ItemInfo[itemid][iValue2], 1);
				
				ItemInfo[itemid][iIlosc]--;
				if(!ItemInfo[itemid][iIlosc])
					DeleteItem(itemid);
				else
					mysql_query_format("UPDATE `srv_items` SET `ilosc`=`ilosc`-1 WHERE `UID`='%d'",itemid);
			}
			return 1;
		}
		case D_ITEM_PRICE:
		{
			if(response)
			{	
				new itemid = strval(inputtext);
				SetPVarInt(playerid, "ItemSetPriceID", itemid);

				new string[128];
				format(string,sizeof(string),"Ustal cenê dla przedmiotu %s:",ItemInfo[itemid][iName]);
				ShowPlayerDialog(playerid, D_ITEM_PRICE_SET, DIALOG_STYLE_INPUT, DEF_NAME" » cennik", string, "Akceptuj", "Anuluj");
			}
			return 1;
		}
		case D_ITEM_PRICE_SET:
		{
			if(response)
			{
				new itemid=GetPVarInt(playerid, "ItemSetPriceID");
				DeletePVar(playerid, "ItemSetPriceID");
				new price = strval(inputtext);
				if(price < 0 || price > 50000)
					return msg_error(playerid,"Wprowadzona cena produktu jest nieprawid³owa.");
				ItemInfo[itemid][iPrice]=price;
				mysql_query_format("UPDATE `srv_items` SET `price` = '%d' WHERE `UID`='%d' LIMIT 1",price, itemid);
				new string[128];
				format(string,sizeof(string),"Pomyslnie zmieni³eœ cenê przedmiotu %s na $%d.",ItemInfo[itemid][iName],price);
				SendClientMessage(playerid, COLOR_GREEN, string);
			}
			return 1;

		}
		case D_STATION_DELETE:
		{
			new uid = GetPVarInt(playerid, "DeleteStationID");
			DeletePVar(playerid, "DeleteStationID");
			if(response)
			{
				DeleteFuelStation(uid);
				msg_info(playerid,"Stacja paliw zosta³a usuniêta");
			}
			return 1;
		}
		case D_FUEL_TRANSPORT:
		{
			if(response)
			{
				new uid=strval(inputtext);
				SetPVarInt(playerid,"TransportFuel",uid);
				msg_info(playerid, "Udaj siê w miejsce oznaczone na mapie i odbierz paliwo, nastepnie przywieŸ je na stacjê paliw.");
				new rand=random(2);
				mysql_query_format("UPDATE `srv_fuel_orders` SET `driver`='%d' WHERE `uid`='%d'",CharacterInfo[playerid][pUID],uid);
				SetPlayerCheckpoint(playerid,FuelTransportCP[rand][TransportX],FuelTransportCP[rand][TransportY],FuelTransportCP[rand][TransportZ],8.0);
			}
			return 1;
		}
		case D_911:
		{
			if(response)
			{
				new guid=strval(inputtext);
				SetPVarInt(playerid, "911GroupID",guid);
				new string[32];
				format(string, sizeof(string), DEF_NAME" » %s", GroupInfo[guid][gName]);
				ShowPlayerDialog(playerid, D_911_TEXT, DIALOG_STYLE_INPUT, string, "WprowadŸ treœæ zg³oszenia. Lokalizacja zostanie zapisana.", "Wybierz", "WyjdŸ");
			}
			return 1;
		}
		case D_911_TEXT:
		{
			if(response)
			{
				if(strlen(inputtext) >= 128)
					 return msg_error(playerid, "Treœæ zg³oszenia jest za d³uga.");
				if(strlen(inputtext) < 5)
					return msg_error(playerid, "Treœæ zg³oszenia jest za krótka.");
					
				new uid = GetPVarInt(playerid, "911GroupID");
				
				if(!uid) return 1;
				
				new id = -1;
				ForeachEx(i, MAX_911CALLS)
				{
					if(!CallInfo[i][cID])
					{
						CallInfo[i][cID] = i+1;
						id = i;
						break;
					}
				}
				
				if(id < 0) return 1;
				
				new string[128];
				new cTime[3];
				format(string, sizeof(string), "%s", inputtext);
				CallInfo[id][cCaller] = CharacterInfo[playerid][pUID];
				CallInfo[id][cGroup] = uid;
				CallInfo[id][cReason] = string;
				
				new godzina, minuta;
				gettime(godzina, minuta);
				
				if(godzina < 10)
					format(cTime, sizeof(cTime), "0%d", godzina);
				else
					format(cTime, sizeof(cTime), "%d", godzina);
				
				CallInfo[id][cTimeH] = cTime;
				
				if(minuta < 10)
					format(cTime, sizeof(cTime), "0%d", minuta);
				else
					format(cTime, sizeof(cTime), "%d", minuta);
				
				CallInfo[id][cTimeM] = cTime;
				
				GetPlayerPos(playerid, CallInfo[id][cPos][0], CallInfo[id][cPos][1], CallInfo[id][cPos][2]);
				
				new color = GetGroupColor(uid);
				ForeachPlayer(i)
				{
					if(DutyGroup[i] == uid && Logged[i])
						SendClientMessage(i, color, "Nadesz³o nowe zg³oszenie do centrali. Wpisz /zgloszenia aby zareagowac.");
				}
			}
			
			DeletePVar(playerid, "911GroupID");
			return 1;
		}
		case D_FUEL_ORDER:
		{
			if(response)
			{
				new fuel=strval(inputtext);
				if(fuel < 500 || fuel > 1000)
					return msg_error(playerid,"Wprowadzona iloœc paliwa jest nieprawid³owa. (500-1000)");

				new fuel_price = SettingInfo[sFuelCost] * fuel;
				new transport_price = fuel_price/5;
				
				if(transport_price > 400)
					transport_price = 400;
				
				new stationid=GetPlayerStationID(playerid);
				new string[128];
				if(GroupInfo[StationInfo[stationid][sOwner]][gCash] < fuel_price+transport_price)
				{
					format(string, sizeof(string), "Na koncie grupy nie ma wystarczaj¹cej iloœci pieniêdzy. Koszt zamówienia wynosi $%d.", fuel_price + transport_price);
					return msg_error(playerid, string);
				}
				format(string,sizeof(string),"Iloœæ:\t\t\t%dl\nKoszt paliwa:\t\t$%d\nKoszt transportu:\t$%d\n\nSuma: $%d",fuel,fuel_price,transport_price,fuel_price + transport_price);
				SetPVarInt(playerid,"FuelVal",fuel);
				SetPVarInt(playerid,"FuelPrice",fuel_price+transport_price);

				ShowPlayerDialog(playerid,D_FUEL_CONFIRM,DIALOG_STYLE_MSGBOX,DEF_NAME" » potwierdzenie",string,"PotwierdŸ","Anuluj");
			}
			return 1;
		}
		case D_FUEL_CONFIRM:
		{
			if(response)
			{
				new fuel = GetPVarInt(playerid,"FuelVal");
				new price = GetPVarInt(playerid,"FuelPrice");
				new query[256], stationid=GetPlayerStationID(playerid);
				
				if(!fuel || !price || !stationid) return 0;
				
				format(query,sizeof(query),"INSERT INTO `srv_fuel_orders` VALUES (NULL,'%d','%d','%d',0,0)",stationid,fuel,gettime());
				mysql_query(query);
				GiveGroupCash(StationInfo[stationid][sOwner], -price);
				msg_infoFormat(playerid,128,"Zamówienie z³o¿one pomyœlnie. Koszt: $%d",price);
			}
			DeletePVar(playerid,"FuelVal");
			DeletePVar(playerid,"FuelPrice");
			return 1;
		}
		case D_CORNER:
		{
			if(response)
			{
				new itemid = GetPVarInt(playerid, "DrugID");
				new price = GetPVarInt(playerid, "DrugPrice");
				new ilosc = GetPVarInt(playerid, "DrugCount");
				
				new string[196];
				format(string, sizeof(string), "Pomyœlnie sprzeda³eœ %s (iloœæ: %d) za $%d.", ItemInfo[itemid][iName], ilosc, price);
				msg_info(playerid, string);
				if(ItemInfo[itemid][iValue1]-ilosc > 0)
				{
					ItemInfo[itemid][iValue1] -= ilosc;
					format(string,sizeof(string),"UPDATE `srv_items` SET `value1` = '%d' WHERE `uid` = '%d' LIMIT 1", ItemInfo[itemid][iValue1], itemid);
					mysql_query(string);
				}
				else
					DeleteItem(itemid);
				
				GivePlayerCash(playerid, price);
			}
			DeletePVar(playerid, "DrugID");
			DeletePVar(playerid, "DrugPrice");
			DeletePVar(playerid, "DrugCount");
			CharacterInfo[playerid][pCornerTimer] = SetTimerEx("SellDrugs", 60000+random(10)*30000, false, "i", playerid);
			
			return 1;
		}
		case D_CORPSE_SEARCH:
		{
			if(response)
			{
				new corpse=GetPVarInt(playerid, "CorpseSearchID");
				SetPVarInt(playerid, "CorpseSearchItem", strval(inputtext));
				new string[256];
				format(string,sizeof(string),"Zabierz wybrany przedmiot\nZabierz wszystkie przedmioty\nZabierz gotówkê ($%d)\nZabierz przedmioty i gotówkê",CorpseInfo[corpse][corpseMoney]);
				ShowPlayerDialog(playerid, D_CORPSE_SEARCH_MEN, DIALOG_STYLE_LIST,DEF_NAME" » zw³oki", string, "OK", "WyjdŸ");
			}
			else
				DeletePVar(playerid, "CorpseSearchID");
			return 1;
		}
		case D_CORPSE_MONEY:
		{
			if(response)
			{
				new uid=GetPVarInt(playerid, "CorpseSearchID");
				GivePlayerCash(playerid,CorpseInfo[uid][corpseMoney]);
				CorpseInfo[uid][corpseMoney]=0;
				new string[128];
				format(string,sizeof(string),"UPDATE `srv_corpse` SET `money`='0' WHERE `uid`='%d'",uid);
				mysql_query(string);
				cmd_me(playerid,"zabiera gotówkê znalezion¹ przy zw³okach");
			}
			DeletePVar(playerid, "CorpseSearchID");
			return 1;
		}
		case D_CORPSE_SEARCH_MEN:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
					{
						new itemid=GetPVarInt(playerid, "CorpseSearchItem");
						ItemInfo[itemid][iOwner]=CharacterInfo[playerid][pUID];
						ItemInfo[itemid][iOwnerTyp]=OWNER_PLAYER;
						new string[128];
						format(string,sizeof(string),"UPDATE `srv_items` SET `owner`='%d', `ownertyp`='%d' WHERE `UID`='%d' LIMIT 1",ItemInfo[itemid][iOwner],ItemInfo[itemid][iOwnerTyp],ItemInfo[itemid][iUID]);
						mysql_query(string);
						format(string,sizeof(string),"zabiera ze zw³ok przedmiot %s.",ItemInfo[itemid][iName]);
						cmd_me(playerid,string);
					}
					case 1:
					{
						new uid = GetPVarInt(playerid, "CorpseSearchID");
						new string[128];
						ForeachEx(itemid, _ITEM_COUNT)
						{
							if(ItemInfo[itemid][iOwnerTyp]==OWNER_CORPSE && ItemInfo[itemid][iOwner]==uid)
							{
								ItemInfo[itemid][iOwner]=CharacterInfo[playerid][pUID];
								ItemInfo[itemid][iOwnerTyp]=OWNER_PLAYER;
								format(string,sizeof(string),"UPDATE `srv_items` SET `owner`='%d', `ownertyp`='%d' WHERE `UID`='%d' LIMIT 1",ItemInfo[itemid][iOwner],ItemInfo[itemid][iOwnerTyp],ItemInfo[itemid][iUID]);
								mysql_query(string);
							}
						}
						cmd_me(playerid,"zabiera wszystkie przdmioty znalezione przy zw³okach");
					}
					case 2:
					{
						new uid=GetPVarInt(playerid, "CorpseSearchID");
						if(CorpseInfo[uid][corpseMoney])
						{
							GivePlayerCash(playerid,CorpseInfo[uid][corpseMoney]);
							CorpseInfo[uid][corpseMoney]=0;
							new string[128];
							format(string,sizeof(string),"UPDATE `srv_corpse` SET `money`='0' WHERE `uid`='%d'",uid);
							mysql_query(string);
							cmd_me(playerid,"zabiera gotówkê znalezion¹ przy zw³okach.");
						}
						else
							msg_error(playerid,"Przy wybranych zw³okach nie ma gotówki");
					}
					case 3:
					{
						new uid = GetPVarInt(playerid, "CorpseSearchID");
						new string[128];
						ForeachEx(itemid, _ITEM_COUNT)
						{
							if(ItemInfo[itemid][iOwnerTyp]==OWNER_CORPSE && ItemInfo[itemid][iOwner]==uid)
							{
								ItemInfo[itemid][iOwner]=CharacterInfo[playerid][pUID];
								ItemInfo[itemid][iOwnerTyp]=OWNER_PLAYER;
								format(string,sizeof(string),"UPDATE `srv_items` SET `owner`='%d', `ownertyp`='%d' WHERE `UID`='%d' LIMIT 1",ItemInfo[itemid][iOwner],ItemInfo[itemid][iOwnerTyp],ItemInfo[itemid][iUID]);
								mysql_query(string);
							}
						}
						GivePlayerCash(playerid,CorpseInfo[uid][corpseMoney]);
						CorpseInfo[uid][corpseMoney]=0;
						format(string,sizeof(string),"UPDATE `srv_corpse` SET `money`='0' WHERE `uid`='%d'",uid);
						mysql_query(string);
						cmd_me(playerid,"zabiera gotówkê i przedmioty znalezione przy zw³okach.");
					}
				}
			}
			DeletePVar(playerid, "CorpseSearchID");
			DeletePVar(playerid, "CorpseSearchItem");
			return 1;
		}
		case D_REPAIR:
		{
			if(response)
			{
				new vehid=GetPVarInt(playerid,"pRepairCarID");
				new job_price= GetPVarInt(playerid,"pRepairJobPrice");
				new customer=GetPVarInt(playerid,"pRepairCustomer");
				new type,price;
				switch(listitem)
				{
					case 0: //silnik
					{
						price += GetVehicleMaxHP(VehicleInfo[vehid][vModel]) -floatround(VehicleInfo[vehid][vHP]);
						type=OFFER_REPAIR_ENG;
					}
					case 1: //karo
					{
						new panels, doors, lights, tires;
						new parts[10];
						GetVehicleDamageStatus(VehicleInfo[vehid][vSAMPID], panels, doors, lights, tires);
						decode_panels(panels,parts[0],parts[1]);
						decode_doors(doors,parts[2],parts[3],parts[4],parts[5]);
						decode_lights(lights,parts[6],parts[7],parts[8],parts[9]);
						if(parts[0]) price += 50;
						if(parts[1]) price += 50;
						for(new p=2;p<6;p++)
							if(parts[p]>1)
								price +=50;
						for(new p=6;p<10;p++)
							if(parts[p])
								price +=50;
						type=OFFER_REPAIR_BODY;
					}
					case 2: //opony
					{
						new tire[4],tires,tmp;
						GetVehicleDamageStatus(VehicleInfo[vehid][vSAMPID], tmp, tmp, tmp, tires);
						decode_tires(tires,tire[0],tire[1],tire[2],tire[3]);
						for(new p=1;p<4;p++)
							if(tire[p])
								price +=50;
						type=OFFER_REPAIR_TIRES;
					}
					case 3: //all
					{
						price += GetVehicleMaxHP(VehicleInfo[vehid][vModel]) -floatround(VehicleInfo[vehid][vHP]);
						new panels, doors, lights, tires,parts[10],tire[4];
						GetVehicleDamageStatus(VehicleInfo[vehid][vSAMPID], panels, doors, lights, tires);
						decode_panels(panels,parts[0],parts[1]);
						decode_doors(doors,parts[2],parts[3],parts[4],parts[5]);
						decode_lights(lights,parts[6],parts[7],parts[8],parts[9]);
						decode_tires(tires,tire[0],tire[1],tire[2],tire[3]);
						if(parts[0]) price += 50;
						if(parts[1]) price += 50;
						for(new p=2;p<6;p++)
							if(parts[p]>1)
								price +=50;
						for(new p=6;p<10;p++)
							if(parts[p])
								price +=50;
						for(new p=1;p<4;p++)
							if(tire[p])
								price +=50;
						type=OFFER_REPAIR_ALL;
					}
				}
				price /= 3;
				Oferta(type,playerid,customer,price+job_price,vehid);
			}
			DeletePVar(playerid, "pRepairCarID");
			//DeletePVar(playerid, "pRepairPrice");
			DeletePVar(playerid, "pRepairCustomer");
			return 1;
		}
		case D_KARTOTEKI_EDIT:
		{
			if(response)
			{
				new string[32];
				mysql_real_escape_string(inputtext,inputtext);
				format(string, sizeof(string), "%s", inputtext);
				
				new recordid = GetPVarInt(playerid, "recordid");
				DeletePVar(playerid, "recordid");
				
				mysql_query_format("UPDATE `srv_kartoteki_records` SET `record`='%s' WHERE `ID`='%d' LIMIT 1", string, recordid);
				
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » kartoteki", "Edycja zakoñczona, zmieniono wpis w kartotece.", "Zamknij", "");
			}
			return 1;
		}
		case D_KARTOTEKI_REMOVE_CONF:
		{
			if(response)
			{
				new recordid = GetPVarInt(playerid, "recordid");
				DeletePVar(playerid, "recordid");
				
				mysql_query_format("DELETE FROM `srv_kartoteki_records` WHERE `ID`='%d' LIMIT 1", recordid);
				
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » kartoteki", "Usun¹³eœ wpis z kartoteki.", "Zamknij", "");
			}
			return 1;
		}
		case D_POSZUKIWANI_NEW:
		{
			if(response)
			{
				new playerid2 = strval(inputtext);
				
				if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
					return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
				
				new puid = CharacterInfo[playerid2][pUID];
				SetPVarInt(playerid, "poszuid", puid);
				
				mysql_query_format("SELECT * FROM `srv_mostwanted` WHERE `player_uid` = '%d'", puid);
				mysql_store_result();
				
				if(mysql_num_rows())
				{
					mysql_free_result();
					return msg_info(playerid,"Wybrany gracz jest ju¿ poszukiwany.");
				}
				
				mysql_free_result();
				
				ShowPlayerDialog(playerid, D_POSZUKIWANI_NEW2, DIALOG_STYLE_INPUT, DEF_NAME" » dodaj kartoteke", "Wpisz powód poszukiwañ:", "Dalej", "Anuluj");
			}
			return 1;
		}
		case D_POSZUKIWANI_NEW2:
		{
			if(response)
			{
				new puid = GetPVarInt(playerid, "poszuid");
				DeletePVar(playerid, "poszuid");
				
				new reason[32];
				mysql_real_escape_string(inputtext,inputtext);
				
				format(reason, sizeof(reason), "%s", inputtext);
				
				mysql_query_format("INSERT INTO `srv_mostwanted` VALUES (NULL, '%d', '%s')", puid, reason);
				
				msg_info(playerid, "Doda³eœ do listy poszukiwanych now¹ osobê.");
			}
			return 1;
		}
		case D_POSZUKIWANI_SEARCH:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
						ShowPlayerDialog(playerid, D_POSZUKIWANI_SEARCH_UID, DIALOG_STYLE_INPUT, DEF_NAME" » poszukiwani", "Wpisz UID szukanej osoby:", "Szukaj", "Zamknij");
					case 1:
						ShowPlayerDialog(playerid, D_POSZUKIWANI_SEARCH_ID, DIALOG_STYLE_INPUT, DEF_NAME" » poszukiwani", "Wpisz ID szukanej osoby:", "Szukaj", "Zamknij");
				}
			}
			return 1;
		}
		case D_POSZUKIWANI_SEARCH_UID:
		{
			if(response)
			{
				new puid = strval(inputtext);
				
				new data[512];
				new uid, reason[32];
				
				mysql_query_format("SELECT `ID`, `reason` FROM `srv_mostwanted` WHERE `player_uid` = '%d' LIMIT 1", puid);
				mysql_store_result();
				
				if(!mysql_num_rows())
				{
					msg_info(playerid, "Wybrany gracz nie jest poszukiwany.");
					mysql_free_result();
				}
				else
				{
					new string[1024];
					new age, sex, jail_time;
					mysql_fetch_row_format(data, "|");
					sscanf(data, "p<|>ds[32]", uid, reason);
					
					mysql_free_result();
					
					mysql_query_format("SELECT `age`, `sex`, `jail_time` FROM `srv_characters` WHERE `player_uid` = '%d' LIMIT 1", puid);
					mysql_store_result();
					
					mysql_fetch_row_format(data, "|");
					sscanf(data, "p<|>ddd", age, sex, jail_time);
					
					mysql_free_result();
					
					SetPVarInt(playerid, "poszukiwanyuid", uid);
					
					if(DutyGroup[playerid] && GroupInfo[DutyGroup[playerid]][gLeader] == CharacterInfo[playerid][pUID] && GroupInfo[DutyGroup[playerid]][gType] == GROUP_PD)
					{
						if(jail_time) format(string, sizeof(string), "Imiê i nazwisko: {878A87}%s\nWiek: {878A87}%d\nP³eæ: {878A87}%s\nAktualnie w areszcie: {C90000}TAK (%d)\n{878A87}Powód poszukiwania: %s\n{878A87}----------\n{C90000}Usuñ z listy poszukiwanych", LoadPlayerName(puid), age, GetSexName(sex), jail_time, reason);
						else format(string, sizeof(string), "Imiê i nazwisko: {878A87}%s\nWiek: {878A87}%d\nP³eæ: {878A87}%s\nAktualnie w areszcie: {02AD38}NIE\n{878A87}Powód poszukiwania: %s\n{878A87}----------\n{C90000}Usuñ z listy poszukiwanych", LoadPlayerName(puid), age, GetSexName(sex), reason);
						
						ShowPlayerDialog(playerid, D_POSZUKIWANY_REMOVE, DIALOG_STYLE_LIST, DEF_NAME" » poszukiwani", string, "Wybierz", "Zamknij");
					}
					else
					{
						if(jail_time) format(string, sizeof(string), "Imiê i nazwisko: {878A87}%s\nWiek: {878A87}%d\nP³eæ: {878A87}%s\nAktualnie w areszcie: {C90000}TAK (%d)\n{878A87}Powód poszukiwania: %s", LoadPlayerName(puid), age, GetSexName(sex), jail_time, reason);
						else format(string, sizeof(string), "Imiê i nazwisko: {878A87}%s\nWiek: {878A87}%d\nP³eæ: {878A87}%s\nAktualnie w areszcie: {02AD38}NIE\n{878A87}Powód poszukiwania: %s", LoadPlayerName(puid), age, GetSexName(sex), reason);
						
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, DEF_NAME" » poszukiwani", string, "Zamknij", "");
					}
				}
			}
			return 1;
		}
		case D_POSZUKIWANI_SEARCH_ID:
		{
			if(response)
			{
				new playerid2 = strval(inputtext);
				
				if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
					return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
				
				new puid = CharacterInfo[playerid2][pUID];
				
				new data[512];
				new uid, reason[32];
				
				mysql_query_format("SELECT `ID`, `reason` FROM `srv_mostwanted` WHERE `player_uid` = '%d' LIMIT 1", puid);
				mysql_store_result();
				
				if(!mysql_num_rows())
				{
					msg_info(playerid, "Wybrany gracz nie jest poszukiwany.");
					mysql_free_result();
				}
				else
				{
					new string[1024];
					mysql_fetch_row_format(data, "|");
					sscanf(data, "p<|>ds[32]", uid, reason);
					
					mysql_free_result();
					
					SetPVarInt(playerid, "poszukiwanyuid", uid);
					
					if(DutyGroup[playerid] && GroupInfo[DutyGroup[playerid]][gLeader] == CharacterInfo[playerid][pUID] && GroupInfo[DutyGroup[playerid]][gType] == GROUP_PD)
					{
						if(CharacterInfo[playerid2][pJailTime] > gettime()) format(string, sizeof(string), "Imiê i nazwisko: {878A87}%s\nWiek: {878A87}%d\nP³eæ: {878A87}%s\nAktualnie w areszcie: {C90000}TAK (%d){878A87}\nPowód poszukiwania: %s\n{878A87}----------\n{C90000}Usuñ z listy poszukiwanych", PlayerName3(playerid2), CharacterInfo[playerid2][pAge], GetSexName(CharacterInfo[playerid2][pSex]), (CharacterInfo[playerid2][pJailTime]-gettime())/60/60, reason);
						else format(string, sizeof(string), "Imiê i nazwisko: {878A87}%s\nWiek: {878A87}%d\nP³eæ: {878A87}%s\nAktualnie w areszcie: {02AD38}NIE{878A87}\nPowód poszukiwania: %s\n{878A87}----------\n{C90000}Usuñ z listy poszukiwanych", PlayerName3(playerid2), CharacterInfo[playerid2][pAge], GetSexName(CharacterInfo[playerid2][pSex]), reason);
						
						ShowPlayerDialog(playerid, D_POSZUKIWANY_REMOVE, DIALOG_STYLE_LIST, DEF_NAME" » poszukiwani", string, "Wybierz", "Zamknij");
					}
					else
					{
						if(CharacterInfo[playerid2][pJailTime] > gettime()) format(string, sizeof(string), "Imiê i nazwisko: {878A87}%s\nWiek: {878A87}%d\nP³eæ: {878A87}%s\nAktualnie w areszcie: {C90000}TAK (%d)\n{878A87}Powód poszukiwania: %s", PlayerName3(playerid2), CharacterInfo[playerid2][pAge], GetSexName(CharacterInfo[playerid2][pSex]), (CharacterInfo[playerid2][pJailTime]-gettime())/60/60, reason);
						else format(string, sizeof(string), "Imiê i nazwisko: {878A87}%s\nWiek: {878A87}%d\nP³eæ: {878A87}%s\nAktualnie w areszcie: {02AD38}NIE\n{878A87}Powód poszukiwania: %s", PlayerName3(playerid2), CharacterInfo[playerid2][pAge], GetSexName(CharacterInfo[playerid2][pSex]), reason);
						
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, DEF_NAME" » poszukiwani", string, "Zamknij", "");
					}
				}
			}
			return 1;
		}
		case D_POSZUKIWANY_REMOVE:
		{
			if(response)
				if(listitem == 6)
					ShowPlayerDialog(playerid, D_POSZUKIWANY_REMOVE_CONF, DIALOG_STYLE_MSGBOX, DEF_NAME" » poszukiwani", "Jesteœ pewny, ¿e chcesz usun¹æ t¹ osobê z listy poszukiwanych?", "Tak", "Nie");
			return 1;
		}
		case D_POSZUKIWANY_REMOVE_CONF:
		{
			if(response)
			{
				new uid = GetPVarInt(playerid, "poszukiwanyuid");
				DeletePVar(playerid, "poszukiwanyuid");
				
				mysql_query_format("DELETE FROM `srv_mostwanted` WHERE `ID`='%d' LIMIT 1", uid);
				
				msg_info(playerid, "Usun¹³eœ z listy poszukiwanych wybran¹ osobê.");
			}
			return 1;
		}
		case D_BUS:
		{
			if(response)
			{
				new to=strval(inputtext);
				new from=GetPlayerBusStop(playerid);
				new dist=GetDistance(BusInfo[from][bPosX],  BusInfo[from][bPosY],  BusInfo[from][bPosZ],  BusInfo[to][bPosX],BusInfo[to][bPosY],BusInfo[to][bPosZ]);

				new string[180];
				new price;
				if(CharacterInfo[playerid][pHours] > 5)
					price = dist/100 *4;
				format(string,sizeof(string),"Czy na pewno chcesz siê udac na przystanek %s?\nCena: $%d\nCzas podró¿y: %d sekund",BusInfo[to][bName],price,dist/100*4);

				SetPVarInt(playerid,"pBusDist",dist/100);
				SetPVarInt(playerid,"pBusTo",to);
				SetPVarInt(playerid,"pBusFrom",from);
				ShowPlayerDialog(playerid,D_BUS_CONFIRM,DIALOG_STYLE_MSGBOX,DEF_NAME" » bus",string,"Tak","Nie");
			}
			return 1;
		}
		case D_BUS_CONFIRM:
		{
			if(response)
			{
				new dist=GetPVarInt(playerid, "pBusDist");
				if(CharacterInfo[playerid][pHours] > 5 && CharacterInfo[playerid][pCash]<dist*4)
					return msg_error(playerid,"Nie posiadasz wystarczaj¹cej iloœci gotówki.");
				SetTimerEx("GetIntoBus", 5000, false, "iiiii", playerid,CharacterInfo[playerid][pUID],GetPVarInt(playerid,"pBusFrom"),GetPVarInt(playerid,"pBusTo"),GetPVarInt(playerid,"pBusDist"));
				Tip(playerid,5,"Poczekaj na autobus.");
				if(CharacterInfo[playerid][pHaveWeapon])
					HidePlayerWeapons(playerid);
			}

			DeletePVar(playerid,"pBusDist");
			DeletePVar(playerid,"pBusTo");
			DeletePVar(playerid,"pBusFrom");
		}
		case D_TUNING:
		{
			if(response)
			{
				new itemid=strval(inputtext);
				new vehid=GetPVarInt(playerid,"pRepairCarID");
				if(!islegalcarmod(GetVehicleModel(VehicleInfo[vehid][vSAMPID]),ItemInfo[itemid][iValue1]) && ItemInfo[itemid][iType] != ITEM_TYPE_GLASS)
				{
					DeletePVar(playerid, "pRepairCarID");
					DeletePVar(playerid, "pRepairJobPrice");
					DeletePVar(playerid, "pRepairCustomer");
					return msg_error(playerid,"W tym pojeŸdzie nie mo¿na zamonotowaæ wybranej czêœci.");
				}
				else if(ItemInfo[itemid][iType] == ITEM_TYPE_GLASS && VehicleInfo[vehid][vGlass])
					return msg_error(playerid, "Wybrany pojazd ma ju¿ przyciemniane szyby.");
				
				SetPVarInt(playerid,"pRepairPart",itemid);
				new price=ItemInfo[itemid][iPrice];
				if(price<=0)
					msg_error(playerid,"Wyst¹pi³ b³¹d pobierania ceny komponentu. Skontaktuj siê z administracj¹.");
				else
					Oferta(OFFER_TUNING,playerid,GetPVarInt(playerid,"pRepairCustomer"), price + GetPVarInt(playerid,"pRepairJobPrice"),GetPVarInt(playerid, "pRepairCarID"));
			}
			else
			{
				DeletePVar(playerid, "pRepairCarID");
				DeletePVar(playerid, "pRepairJobPrice");
				DeletePVar(playerid, "pRepairCustomer");
			}
			return 1;
		}
		case D_GROUP_MAGAZINE:
		{
			if(response)
			{
				if(listitem == 0)
				{
					new groupid = GetPVarInt(playerid, "magguid");
					new list[2560];
					
					ForeachEx(i, _ITEM_COUNT)
						if(ItemInfo[i][iUID])
							if(ItemInfo[i][iOwnerTyp] == OWNER_GROUP && ItemInfo[i][iOwner] == GroupInfo[groupid][gUID])
								format(list, sizeof(list), "%s\n%d\t{878A87}%s\t%d %d\t(%d sztuk)", list, i, ItemInfo[i][iName], ItemInfo[i][iValue1], ItemInfo[i][iValue2], ItemInfo[i][iIlosc]);
					if(strlen(list)>5)
					{
						ShowPlayerDialog(playerid, D_GROUP_MAGAZINE_OUT, DIALOG_STYLE_LIST, DEF_NAME" » magazyn", list, "Wybierz", "WyjdŸ");
						return 1;
					}
					else
						return msg_error(playerid,"Brak przedmiotów w magazynie.");
				}
				else if(listitem == 1)
				{
					new list[2560];
	
					format(list, sizeof(list), "UID\tNazwa\tWartoœæ 1\tWartoœæ 2");
					
					ForeachEx(i, _ITEM_COUNT)
						if(ItemInfo[i][iUID])
							if(ItemInfo[i][iOwnerTyp] == OWNER_PLAYER && ItemInfo[i][iOwner] == CharacterInfo[playerid][pUID] && !ItemInfo[i][iUsed])
								format(list, sizeof(list), "%s\n%d\t{878A87}%s\t%d\t%d", list, ItemInfo[i][iUID], ItemInfo[i][iName], ItemInfo[i][iValue1], ItemInfo[i][iValue2]);
					
					if(strlen(list)<30)
						return msg_error(playerid,"Brak przedmiotów mo¿liwych do umieszczenia w magazynie.");
					ShowPlayerDialog(playerid, D_GROUP_MAGAZINE_PUT, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » przedmioty", list, "Wybierz", "WyjdŸ");
				}
				else
				{
					new groupid = GetPVarInt(playerid, "magguid");
					new list[2560];
					
					ForeachEx(i, _ITEM_COUNT)
						if(ItemInfo[i][iUID])
							if(ItemInfo[i][iOwnerTyp] == OWNER_GROUP && ItemInfo[i][iOwner] == GroupInfo[groupid][gUID])
								format(list, sizeof(list), "%s\n%d\t{878A87}%s\t%d %d\t(%d sztuk)", list, i, ItemInfo[i][iName], ItemInfo[i][iValue1], ItemInfo[i][iValue2], ItemInfo[i][iIlosc]);
					if(strlen(list)>5)
					{
						ShowPlayerDialog(playerid, D_GROUP_MAGAZINE_STACK, DIALOG_STYLE_LIST, DEF_NAME" » magazyn", list, "Wybierz", "WyjdŸ");
						return 1;
					}
					else
						return msg_error(playerid,"Brak przedmiotów w magazynie.");
				}
			}
			return 1;
		}
		case D_GROUP_MAGAZINE_PUT:
		{
			if(response)
			{
				new itemid = strval(inputtext);
				ItemInfo[itemid][iOwnerTyp] = OWNER_GROUP;
				ItemInfo[itemid][iOwner] = GetPVarInt(playerid, "magguid");
				DeletePVar(playerid, "magguid");
				new string[196];
				format(string, sizeof(string), "UPDATE `srv_items` SET `owner`='%d', `ownertyp`='%d' WHERE `UID`='%d'", ItemInfo[itemid][iOwner], ItemInfo[itemid][iOwnerTyp], itemid);
				mysql_query(string);
				format(string, sizeof(string), "Umieœci³es przedmiot %s w magazynie grupy.", ItemInfo[itemid][iName]);
				msg_info(playerid, string);
			}
			return 1;
		}
		case D_TUNING_DISMOUNT:
		{
			if(response)
			{
				new tuneid=strval(inputtext);
				SetPVarInt(playerid,"pRepairPart",tuneid);
				Oferta(OFFER_DISMOUNT,playerid,GetPVarInt(playerid,"pRepairCustomer"),GetPVarInt(playerid,"pRepairJobPrice"),GetPVarInt(playerid, "pRepairCarID"));
			}
			else
			{
				DeletePVar(playerid, "pRepairCarID");
				DeletePVar(playerid, "pRepairJobPrice");
				DeletePVar(playerid, "pRepairCustomer");
			}
			return 1;
		}
		case D_COMP:
		{
			if(response)
			{
				new playerid2 = strval(inputtext);
				
				new string[1024];
				
				format(string, sizeof(string), DEF_COLOR"# PODSTAWOWE INFORMACJE{A9C4E4}");
				format(string, sizeof(string), "%s\n\tImiê i Nazwisko:\t\t%s", string, PlayerName3(playerid2));
				format(string, sizeof(string), "%s\n\tP³eæ:\t\t\t\t%s", string, GetSexName(CharacterInfo[playerid2][pSex]));
				format(string, sizeof(string), "%s\n\tWiek:\t\t\t\t%d", string, CharacterInfo[playerid2][pAge]);
				
				format(string, sizeof(string), "%s\n\n"DEF_COLOR"# DOKUMENTY{A9C4E4}", string);
				format(string, sizeof(string), "%s\n\tDowód osobisty:\t\t", string);
				if(CharacterInfo[playerid2][pDocs] & DOC_ID) format(string, sizeof(string), "%s{02AD38}POSIADA{A9C4E4}", string);
				else format(string, sizeof(string), "%s{C90000}BRAK{A9C4E4}", string);
				format(string, sizeof(string), "%s\n\tPrawo jazdy:\t\t\t", string);
				if(CharacterInfo[playerid2][pDocs] & DOC_DRIVER) format(string, sizeof(string), "%s{02AD38}POSIADA{A9C4E4}", string);
				else format(string, sizeof(string), "%s{C90000}BRAK{A9C4E4}", string);
				format(string, sizeof(string), "%s\n\tLicencja pilota:\t\t\t", string);
				if(CharacterInfo[playerid2][pDocs] & DOC_PILOT) format(string, sizeof(string), "%s{02AD38}POSIADA{A9C4E4}", string);
				else format(string, sizeof(string), "%s{C90000}BRAK{A9C4E4}", string);
				format(string, sizeof(string), "%s\n\tPozwolenie na broñ:\t\t", string);
				if(CharacterInfo[playerid2][pDocs] & DOC_WEAPONS) format(string, sizeof(string), "%s{02AD38}POSIADA{A9C4E4}", string);
				else format(string, sizeof(string), "%s{C90000}BRAK{A9C4E4}", string);
				
				format(string, sizeof(string), "%s\n\n"DEF_COLOR"# INNE{A9C4E4}", string);
				format(string, sizeof(string), "%s\n\tPunkty karne:\t\t\t%d/24", string, CharacterInfo[playerid2][pPenaltyPoints]);
				
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, DEF_NAME" » Mobile Data Terminal", string, "Zamknij", "");
			}
			return 1;
		}
		case D_GROUP_MAGAZINE_OUT:
		{
			if(response)
			{
				new uid = strval(inputtext);
				SetPVarInt(playerid, "maggid", uid);
				
				ShowPlayerDialog(playerid,D_GROUP_MAGAZINE_LAST, DIALOG_STYLE_INPUT, DEF_NAME" » przedmioty", "Wpisz iloœæ sztuk jak¹ chcesz wyci¹gn¹æ:", "Dalej", "Zamknij");
			}
			return 1;
		}
		case D_VEH_DESC:
		{
			if(response)
			{
				if(listitem==0)
					ShowPlayerDialog(playerid, D_VEH_DESC_ADD, DIALOG_STYLE_INPUT, DEF_NAME" » opis pojazdu", "WprowadŸ opis pojazdu:", "Ustaw", "WyjdŸ");
				else
				{
					new vehid=GetVehicleUID(GetPlayerVehicleID(playerid));
					VehicleInfo[vehid][vDesc]=false;
					if(VehicleInfo[vehid][vDesc3D] != Text3D:INVALID_3DTEXT_ID)
					{
						DestroyDynamic3DTextLabel(VehicleInfo[vehid][vDesc3D]);
						VehicleInfo[vehid][vDesc3D] = Text3D:INVALID_3DTEXT_ID;
					}
					new query[128];
					format(query,sizeof(query),"UPDATE `srv_vehicles` SET `description`='-' WHERE `UID`='%d'",vehid);
					mysql_query(query);
					msg_info(playerid,"Opis pojazdu zosta³ usuniêty.");
				}
			}
			return 1;
		}
		case D_VEH_DESC_ADD:
		{
			if(response)
			{
				new vehid=GetVehicleUID(GetPlayerVehicleID(playerid));
				if(!vehid) return 1;
				if(strlen(inputtext) < 2 || strlen(inputtext) > 127)
					return msg_error(playerid,"Niepoprawna d³ugoœæ opisu. Dozwolony zakres: 2-128");
				if(!ValidateDesc(inputtext, IsPlayerPremium(playerid)))
					return msg_error(playerid, "Opis zawiera niepoprawny znak.");
				if(VehicleInfo[vehid][vDesc3D] != Text3D:INVALID_3DTEXT_ID)
					DestroyDynamic3DTextLabel(VehicleInfo[vehid][vDesc3D]);
				VehicleInfo[vehid][vDesc]=true;
				new Float:x,Float:y,Float:z,query[256];
				GetVehiclePos(VehicleInfo[vehid][vSAMPID], x,y,z);
				if(VehicleInfo[vehid][vDesc])
					VehicleInfo[vehid][vDesc3D]=CreateDynamic3DTextLabel(WordWrap(inputtext,5), COLOR_VEH_DESC, x,y,z,10.0, INVALID_PLAYER_ID, VehicleInfo[vehid][vSAMPID]);
				
				mysql_real_escape_string(inputtext, inputtext);
				format(query, sizeof(query), "UPDATE `srv_vehicles` SET `description`='%s' WHERE `UID`='%d'", inputtext, vehid);
				mysql_query(query);
				msg_info(playerid, "Opis pojazdu zosta³ pomyœlnie ustawiony.");
			}
		}
		case D_CALL_TAXI:
		{
			if(response)
			{
				SetPVarInt(playerid, "pTaxiGroup", strval(inputtext));
				ShowPlayerDialog(playerid,D_CALL_TAXI_MSG,DIALOG_STYLE_INPUT,DEF_NAME" » taxi",
				"Podaj treœæ zg³oszenia oraz dok³adn¹ lokalizacjê:","Wybierz","WyjdŸ");
			}
			return 1;
		}
		case D_CALL_TAXI_MSG:
		{
			if(response)
			{
				new groupid=GetPVarInt(playerid, "pTaxiGroup");
				new number[24],title[24];
				format(number,sizeof(number),"Numer: %d",ItemInfo[CharacterInfo[playerid][pPhone]][iValue1]);
				format(title,sizeof(title),"[%s]  *Nowe zg³oszenie *",GroupInfo[groupid][gTag]);
				ForeachPlayer(i)
				{
					if(DutyGroup[i]==groupid)
					{
						SendClientMessage(i, GetGroupColor(groupid),title);
						SendClientMessage(i, 0xFFFFFFFF, inputtext);
						SendClientMessage(i, GetGroupColor(groupid), number);
					}
				}
			}
			DeletePVar(playerid,"pTaxiGroup");
			return 1;
		}
		case D_CALL_ASSISTANCE:
		{
			if(response)
			{
				SetPVarInt(playerid, "pAssistGroup", strval(inputtext));
				ShowPlayerDialog(playerid,D_CALL_ASSISTANCE_MSG,DIALOG_STYLE_INPUT,DEF_NAME" » pomoc drogowa","Podaj treœæ zg³oszenia oraz dok³adn¹ lokalizacjê:","Dalej","Anuluj");
			}
			return 1;
		}
		case D_CALL_ASSISTANCE_MSG:
		{
			if(response)
			{
				new groupid=GetPVarInt(playerid, "pAssistGroup");
				new number[24],title[24];
				format(number,sizeof(number),"Numer: %d",ItemInfo[CharacterInfo[playerid][pPhone]][iValue1]);
				format(title,sizeof(title),"[%s]   *Nowe zg³oszenie*",GroupInfo[groupid][gTag]);
				ForeachPlayer(i)
				{
					if(DutyGroup[i]==groupid)
					{
						SendClientMessage(i, GetGroupColor(groupid), title);
						SendClientMessage(i, 0xFFFFFFFF, inputtext);
						SendClientMessage(i, GetGroupColor(groupid), number);
					}
				}
			}
			DeletePVar(playerid,"pAssistGroup");
			return 1;
		}
		case D_PHONE_MP3:
		{
			if(response)
			{
				new audio_url[128];
				new radioCount = sizeof(RadioStations);
				if(0 <= listitem < radioCount)
				{
					strins(audio_url,RadioStations[listitem][radioURL], 0);
					if(!(CharacterInfo[playerid][pStatus] & STATUS_MP3))
							CharacterInfo[playerid][pStatus] += STATUS_MP3;
					PlayAudioStreamForPlayer(playerid, audio_url);
					Tip(playerid, 3, "MP3 wlaczone.");

				} 
				else if(listitem == radioCount)
				{
						ShowPlayerDialog(playerid,D_PHONE_MP3_LINK,DIALOG_STYLE_INPUT,DEF_NAME" » MP3","Podaj adres URL:","Wybierz","Anuluj");
				}
				else
				{
					if(CharacterInfo[playerid][pStatus] & STATUS_MP3)
					{
						StopAudioStreamForPlayer(playerid);
						CharacterInfo[playerid][pStatus]-=STATUS_MP3;
						Tip(playerid,3,"MP3 wylaczone.");
					}
				}
			}
			return 1;
		}
		case D_PHONE_MP3_LINK:
		{
			if(response && strlen(inputtext)>2)
			{
				if(!(CharacterInfo[playerid][pStatus] & STATUS_MP3))
					CharacterInfo[playerid][pStatus]+=STATUS_MP3;
				PlayAudioStreamForPlayer(playerid, inputtext);
				Tip(playerid,3,"MP3 wlaczone.");
			}
		}
		case D_PHONE_ADD_CONT:
		{
			if(response)
			{
				new number=strval(inputtext);
				if(number<100 || number>999999)
					return msg_error(playerid,"Wprowadzony numer jest nieprawid³owy");
				SetPVarInt(playerid,"pContNumber",number);
				ShowPlayerDialog(playerid,D_PHONE_ADD_CONT2,DIALOG_STYLE_INPUT,DEF_NAME" » dodaj kontakt","WprowadŸ nazwê kontaktu:","OK","WyjdŸ");
			}
			return 1;
		}
		case D_PHONE_ADD_CONT2:
		{
			if(response)
			{
				if(strlen(inputtext)>0 && strlen(inputtext)<32)
				{
					mysql_real_escape_string(inputtext,inputtext);
					new query[128];
					format(query,sizeof(query),"INSERT INTO `srv_vcards`(`phone_uid`, `number`, `name`) VALUES ('%d','%d','%s')",CharacterInfo[playerid][pPhone],GetPVarInt(playerid,"pContNumber"),inputtext);
					mysql_query(query);
					msg_info(playerid,"Kontakt zosta³ dodany.");
				}
				else
					msg_error(playerid,"Nieprawid³owa d³ugoœæ nazwy kontaktu. [Max. 32 znaki]");
			}
			DeletePVar(playerid,"pContNumber");
			return 1;
		}
		case D_GROUP_PRICES:
		{
			if(response)
			{
				SetPVarInt(playerid,"GroupPriceItem",listitem);
				ShowPlayerDialog(playerid, D_GROUP_PRICES_SET, DIALOG_STYLE_INPUT, DEF_NAME" » cennik us³ug", "Podaj now¹ cene dla wybranej us³ugi:", "Wybierz", "WyjdŸ");
			}
			return 1;
		}
		case D_GROUP_PRICES_SET:
		{
			if(response)
			{
				if(GroupInfo[DutyGroup[playerid]][gType] == GROUP_MC)
				{
					new price = strval(inputtext);
					
					SettingInfo[sHealPrice] = price;
					
					mysql_query_format("UPDATE `srv_settings` SET `HealPrice` = '%d'", price);
					
					msg_info(playerid, "Ustawi³eœ now¹ cenê za komendê /uleczsie.");
				}
				else if(GroupInfo[DutyGroup[playerid]][gType] == GROUP_NEWS)
				{
					new price = strval(inputtext);
					new item = GetPVarInt(playerid,"GroupPriceItem");
					
					switch(item)
					{
						case 0:
						{
							SettingInfo[sLSNPrice] = price;
							mysql_query_format("UPDATE `srv_settings` SET `lsnprice` = '%d'", price);
							msg_info(playerid, "Ustawi³eœ now¹ cenê za minutê reklamy.");
						}
						case 1:
						{
							SettingInfo[sSANNPay] = price;
							mysql_query_format("UPDATE `srv_settings` SET `sannpay` = '%d'", price);
							msg_info(playerid, "Ustawi³eœ now¹ cenê za SMS.");
						}
					}
				}
				else if(GroupInfo[DutyGroup[playerid]][gType] == GROUP_FUELSTATION)
				{
					new price = strval(inputtext);
					new stationid = GetPlayerStationID(playerid);
					
					if(!price || !stationid) return 0;
					
					if(price < 5 || price > 7)
						return msg_error(playerid, "Koszt paliwa nie mo¿e byæ mniejszy ni¿ $5 oraz wiêkszy od $7!");
					
					StationInfo[stationid][sFuelCost] = price;
					
					new query[128];
					format(query, sizeof(query), "UPDATE `srv_fuel_stations` SET `fuelcost`='%d' WHERE `uid`='%d'", price, stationid);
					mysql_query(query);
					format(query, sizeof(query), "Cena us³ugi zosta³a zmieniona na $%d.", price);
					msg_info(playerid, query);
				}
				else
				{
					new item = GetPVarInt(playerid,"GroupPriceItem");
					new prices[][7] = {"price1","price2","price3","price4","price5"};
					new string[128];
					new price = strval(inputtext);
					if(price < 0 || price > 5000)
						return msg_error(playerid, "Podana cena us³ugi jest nieprawid³owa.");
					if(item < 0 || item > 4)
						return 0;
					format(string, sizeof(string), "UPDATE `srv_group_offer_prices` SET `%s`='%d' WHERE `groupid`='%d'",prices[item], price, DutyGroup[playerid]);
					mysql_query(string);
					format(string, sizeof(string), "Cena us³ugi zosta³a zmieniona na $%d.", price);
					msg_info(playerid, string);
				}
			}
			
			DeletePVar(playerid,"GroupPriceItem");
			return 1;
		}
		case D_WALKIE_CREATE:
		{
			if(response)
			{
				new channel=strval(inputtext);
				if(channel < 1 || channel > 2000)
					return msg_error(playerid,"Niepoprawny numer kana³u. Dozwolony zakres 1-2000");

				new query[128],bool:found;
				format(query,sizeof(query),"SELECT * FROM `srv_walkie_channels` WHERE channel='%d'",channel);
				mysql_query(query);
				mysql_store_result();
				if(mysql_num_rows())
					found=true;
				mysql_free_result();

				if(found)
					return msg_error(playerid,"Istnieje ju¿ kana³ radiowy o podanym numerze.");
				SetPVarInt(playerid,"pWalkieChannel",channel);
				ShowPlayerDialog(playerid, D_WALKIE_CREATE_PASSWD, DIALOG_STYLE_INPUT, DEF_NAME" » kana³ radiowy", "Ustaw has³o kana³u, maksymalnie 12 znaków.\nAby stworzyc kana³ bez has³a pozostaw puste pole.", "Wybierz", "WyjdŸ");
			}
			return 1;
		}
		case D_WALKIE_CREATE_PASSWD:
		{
			if(response)
			{
				if(strlen(inputtext) > 12)
					return msg_error(playerid,"Wprowadzone has³o jest zbyt d³ugie. Maksymalnie 12 znaków.");
				for(new i=0;i<strlen(inputtext);i++)
					if(inputtext[i]==90) // backslash
						return msg_error(playerid,"Has³o zawiera nieprawid³owy znak");
				mysql_real_escape_string(inputtext,inputtext);
				new query[128];
				new channel=GetPVarInt(playerid,"pWalkieChannel");
				format(query,sizeof(query),"INSERT INTO `srv_walkie_channels` VALUES ('%d','%d','%s')",channel,CharacterInfo[playerid][pUID],inputtext);
				mysql_query(query);
				msg_infoFormat(playerid,128,"Stworzy³eœ kana³ radiowy o numerze: %d. Has³o: %s",channel,inputtext);
				CharacterInfo[playerid][pKanal] = channel;
				SavePlayerStats(playerid,SAVE_PLAYER_OPTION);

			}
			DeletePVar(playerid,"pWalkieChannel");
			return 1;
		}
		case D_WALKIE_CHANGE_PASSWD:
		{
			if(response)
			{
				new kanal=GetPVarInt(playerid,"pWalkieChannel");
				new query[128],password[12];
				format(query,sizeof(query),"SELECT `password` FROM `srv_walkie_channels` WHERE `channel`='%d'",kanal);
				mysql_query(query);
				mysql_store_result();
				mysql_fetch_row_format(query);
				if(mysql_num_rows())
					sscanf(query, "p<|>s[12]",password);
				mysql_free_result();
				if(!strcmp(password, inputtext) && !isnull(inputtext))
				{
					CharacterInfo[playerid][pKanal] = kanal;
					SavePlayerStats(playerid,SAVE_PLAYER_OPTION);
					
					msg_info(playerid, "Kana³ radiowy zosta³ zmieniony.");
				}
				else
					msg_error(playerid,"Wprowadzone has³o jest niepoprawne");
			}
			DeletePVar(playerid,"pWalkieChannel");
			return 1;
		}
		case D_WALKIE_OPT:
		{
			if(response)
			{
				if(listitem==0)
					ShowPlayerDialog(playerid,D_WALKIE_PASSWD_CHANGE,DIALOG_STYLE_INPUT,DEF_NAME" » radio","WprowadŸ nowe has³o. Maksymalnie 12 znaków.","Wybierz","WyjdŸ");
				else
				{
					new channel=GetPVarInt(playerid, "pWalkieChannel");
					new query[128];
					ForeachPlayer(i)
					{
						if(CharacterInfo[i][pKanal]==channel)
						{
							SendClientMessage(playerid, COLOR_ORANGE, "Kana³ radiowy, z którym by³eœ po³¹czony zosta³ usuniêty.");
							CharacterInfo[i][pKanal]=0;
							SavePlayerStats(i,SAVE_PLAYER_OPTION);
						}
					}
					format(query,sizeof(query),"UPDATE `srv_characters` SET `radio_channel`=0 WHERE `logged`=1 AND `radio_channel`='%d'",channel);
					mysql_query(query);
					format(query,sizeof(query),"DELETE FROM `srv_walkie_channels` WHERE `channel`='%d'",channel);
					mysql_query(query);
					msg_info(playerid,"Kana³ radiowy zosta³ usuniety.");
					DeletePVar(playerid, "pWalkieChannel");
				}
			}
			else
				DeletePVar(playerid, "pWalkieChannel");	
		}
		case D_WALKIE_PASSWD_CHANGE:
		{
			if(response)
			{
				if(strlen(inputtext)>12)
					return msg_error(playerid,"Wprowadzone has³o jest za d³ugie. Maksymalnie 12 znaków");
				new channel=GetPVarInt(playerid, "pWalkieChannel");

				for(new i=0;i<strlen(inputtext);i++)
					if(inputtext[i]==90) // backslash
						return msg_error(playerid,"Has³o zawiera nieprawid³owy znak");

				ForeachPlayer(i)
				{
					if(CharacterInfo[i][pKanal]==channel && i!=playerid)
					{
						SendClientMessage(playerid, COLOR_ORANGE, "Has³o kana³u radiowego zosta³o zmienione. Po³¹cz siê ponownie u¿ywaj¹c nowego has³a.");
						CharacterInfo[i][pKanal]=0;
						SavePlayerStats(i,SAVE_PLAYER_OPTION);
					}
				}
				mysql_real_escape_string(inputtext,inputtext);
				new query[128];
				format(query,sizeof(query),"UPDATE `srv_characters` SET `radio_channel`=0 WHERE `logged`=0 AND `radio_channel`='%d'",channel);
				mysql_query(query);
				format(query,sizeof(query),"UPDATE `srv_walkie_channels` SET `password`='%s' WHERE `channel`='%d'",inputtext,channel);
				mysql_query(query);

				msg_infoFormat(playerid,128,"Has³o kana³u %d zosta³o zmienione na %s.\nWszystkie osoby zosta³y roz³¹czone.",channel,inputtext);
			}
			DeletePVar(playerid, "pWalkieChannel");	
			return 1;
		}
		case D_PLATESCHANGE:
		{
			if(response)
			{
				new vehuid = GetPVarInt(playerid, "vehuidplates");
				DeletePVar(playerid, "vehuidplates");
				
				if(strlen(inputtext) > 7)
					return msg_error(playerid, "Wprowadzony tekst jest za d³ugi, maksymalnie 7 znaków.");
				
				if(!ValidateDesc(inputtext))
					return msg_error(playerid, "Wprowadzony tekst nie jest poprawny!");
				
				mysql_real_escape_string(inputtext, inputtext);
				new register[8];
				format(register, sizeof(register), "%s", inputtext);
				
				VehicleInfo[vehuid][vRegister] = register;
				
				SaveVehicle(vehuid, SAVE_VEH_BASIC);
			}
			return 1;
		}
		case D_SILENCER:
		{
			if(response)
			{
				new uid = GetPVarInt(playerid, "siluid");
				DeletePVar(playerid, "siluid");
				new iuid = strval(inputtext);				
				DeleteItem(uid);
				ItemInfo[iuid][iValue1] = 23;			
				mysql_query_format("UPDATE `srv_items` SET `value1` = '%d' WHERE `uid` = '%d' LIMIT 1", ItemInfo[iuid][iValue1], iuid);
				
				msg_info(playerid, "Zamontowa³eœ t³umik do broni.");
			}
			return 1;
		}
		case D_RESTAURANT_GIVE:
		{
			if(response)
			{
				new playerid2=GetPVarInt(playerid, "dRestaurantGive");
				new uid=strval(inputtext);
				
				if(ItemInfo[uid][iType] == 1 && ItemInfo[uid][iValue1] >= 22 && ItemInfo[uid][iValue1] != 41 && !(CharacterInfo[playerid2][pDocs] & DOC_WEAPONS))
					return msg_error(playerid, "Wybrany gracz nie posiada licencji na broñ.");

				Oferta(OFFER_RESTAURANT_ITEM, playerid, playerid2, ItemInfo[uid][iPrice], uid);
			}
			DeletePVar(playerid, "dRestaurantGive");
			return 1;
		}
		case D_A3D_CREATE:
		{
			if(response)
			{
				if(strlen(inputtext)>96)
					return msg_error(playerid,"Tekst jest za d³ugi. (max 96 znaków)");

				for(new i=0;i<strlen(inputtext);i++)
					if(inputtext[i]=='\\' || inputtext[i]=='\"' || inputtext[i]=='\'')
						return msg_error(playerid,"Tekst zawiera niedozwolony znak. (\\, \", \')");

				new uid;
				for(new i=1;i<MAX_A3D;i++)
				{
					if(Text3DInfo[i][tUID]==0)
					{
						uid=i;
						break;
					}
				}
				if(!uid)
					return msg_error(playerid,"Osi¹gniêto limit 3DTextów.");

				new Float:x,Float:y,Float:z, string[96];
				GetPlayerPos(playerid,x,y,z);

				format(string,sizeof(string),"%s",inputtext);

				Text3DInfo[uid][tUID]= uid;
				Text3DInfo[uid][tString] = string;
				Text3DInfo[uid][tPosX]= x;
				Text3DInfo[uid][tPosY]= y;
				Text3DInfo[uid][tPosZ]= z;
				Text3DInfo[uid][tVW]= GetPlayerVirtualWorld(playerid);
				Text3DInfo[uid][tInt]= GetPlayerInterior(playerid);

				Text3DInfo[uid][t3D] = CreateDynamic3DTextLabel(WordWrap(string,5), 0x9A9CCDFF, x, y, z, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, Text3DInfo[uid][tVW], Text3DInfo[uid][tInt]);
				
				new query[256];
				format(query,sizeof(query),"INSERT INTO `srv_3dtext` VALUES ('%d', '%s', '%.4f', '%.4f', '%.4f', '%d', '%d')", uid, string, x, y, z, Text3DInfo[uid][tInt], Text3DInfo[uid][tVW]);
				mysql_query(query);

				format(string,sizeof(string),"Pomyœlnie stworzy³eœ 3DText. UID: %d.",uid);
				SendClientMessage(playerid, COLOR_GREEN, string);
			}
			return 1;
		}
		case D_SAFEKEEP:
		{
			if(response)
			{
				new dooruid = GetClosestDoor(playerid);
				
				if(!dooruid || DoorsInfo[dooruid][dOwnerTyp] != OWNER_SAFEKEEP) return 1;
				
				switch(listitem)
				{
					case 0:
					{
						new list[2048];
						
						format(list, sizeof(list), "UID\tNazwa\tWartoœæ 1\tWartoœæ 2");
						
						ForeachEx(i,_ITEM_COUNT)
							if(ItemInfo[i][iUID])
								if(ItemInfo[i][iOwnerTyp] == OWNER_PLAYER && ItemInfo[i][iOwner] == CharacterInfo[playerid][pUID] && ItemInfo[i][iType] == ITEM_TYPE_KEEPKEY && ItemInfo[i][iValue2] == dooruid)
									format(list, sizeof(list), "%s\n%d\t{878A87}%s\t%d\t%d", list, ItemInfo[i][iUID], ItemInfo[i][iName], ItemInfo[i][iValue1], ItemInfo[i][iValue2]);
						
						if(strlen(list)>40) ShowPlayerDialog(playerid, D_SAFEKEEP_OPEN, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » wybierz klucz do skrytki", list, "Wybierz", "Anuluj");
						else msg_error(playerid, "Nie posiadasz kluczyka do tej skrytki.");
					}
					case 1:
					{
						if(CharacterInfo[playerid][pCash] < 150)
							return msg_error(playerid, "Nie posiadasz odpowiedniej iloœci pieniêdzy aby zakupiæ skrytke ($150).");
						
						new uid;
						ForeachEx(i, MAX_SAFEKEEPS)
						{
							if(SafeKeep[i][sUID] == 0 && i != 0)
							{
								uid = i;
								break;
							}
						}
						
						if(!uid)
							return msg_error(playerid, "Osi¹gniêto maksymaln¹ iloœæ skrytek na serwerze.");
						
						GivePlayerCash(playerid, -150);
						SafeKeep[uid][sUID] = uid;
						SafeKeep[uid][sInactive] = 0;
						
						mysql_query_format("INSERT INTO `srv_safekeeps` VALUES('%d', '0')", uid);
						
						new name[32];
						format(name, sizeof(name), "Klucz do skrytki [%d]", uid);
						
						StworzPrzedmiot(OWNER_PLAYER, CharacterInfo[playerid][pUID], name, ITEM_TYPE_KEEPKEY, uid, dooruid, 1);
						
						msg_infoFormat(playerid, 256, "Zakupi³eœ klucz o UID: %d pod skrytkê UID: %d, który znajdziesz pod /p.\n\nPamiêtaj, ¿e skrytki s¹ automatycznie usuwane po tygodniu braku aktywnoœci (jednorazowe otwarcie skrytki resetuje ten czas).", uid, dooruid);
					}
				}
			}
			return 1;
		}
		case D_GOV_JOBS:
		{
			if(response)
			{
				CharacterInfo[playerid][pJob]=listitem+1;
				SavePlayerStats(playerid,SAVE_PLAYER_JOBS);
				if(listitem == 0)
					msg_info(playerid,"Podj¹³eœ pracê jako magazynier.\nAby rozpocz¹æ pracê udaj siê do doków i u¿yj komendy /praca.");
			}
			return 1;
		}
		case D_SAFEKEEP_OPEN:
		{
			if(response)
			{
				new dooruid = GetClosestDoor(playerid);
				
				if(!dooruid || DoorsInfo[dooruid][dOwnerTyp] != OWNER_SAFEKEEP) return 1;
			
				new iuid = strval(inputtext);
				SetPVarInt(playerid, "keepkey", iuid);
				
				ShowPlayerDialog(playerid, D_SAFEKEEP_OPEN_LIST, DIALOG_STYLE_LIST, DEF_NAME" » wybierz opcje", "1. Wrzuæ przedmiot do skrytki\n2. Wyci¹gnij przedmiot ze skrytki", "Wybierz", "Anuluj");
			}
			return 1;
		}
		case D_SAFEKEEP_OPEN_LIST:
		{
			if(response)
			{
				new dooruid = GetClosestDoor(playerid);
				
				if(!dooruid || DoorsInfo[dooruid][dOwnerTyp] != OWNER_SAFEKEEP) return 1;
			
				new iuid = GetPVarInt(playerid, "keepkey");
				new safeuid = ItemInfo[iuid][iValue1];
				new list[2048];
				
				if(!SafeKeep[safeuid][sUID])
				{
					DeleteItem(iuid);
					return msg_error(playerid, "Wybrana skrytka nie istnieje.");
				}
				
				SafeKeep[safeuid][sInactive] = 0;
				
				mysql_query_format("UPDATE `srv_safekeeps` SET `inactive`='0' WHERE `UID`='%d'", safeuid);
				
				switch(listitem)
				{
					case 0:
					{
						format(list, sizeof(list), "UID\tNazwa\tWartoœæ 1\tWartoœæ 2");
						mysql_query_format("SELECT * FROM `srv_items` WHERE `ownertyp` = '%d' AND `owner` = '%d'", OWNER_SAFEKEEP_ITEM, safeuid);
						mysql_store_result();
		
						if(mysql_num_rows() > 9)
						{
							msg_error(playerid, "Nie mo¿esz od³o¿yæ w skrytce wiêcej przedmiotów (max 10).");
							mysql_free_result();
							return 1;
						}
					
						ForeachEx(i,_ITEM_COUNT)
							if(ItemInfo[i][iUID])
								if(ItemInfo[i][iOwnerTyp] == OWNER_PLAYER && ItemInfo[i][iOwner] == CharacterInfo[playerid][pUID] && !ItemInfo[i][iUsed] && ItemInfo[i][iType] != ITEM_TYPE_KEEPKEY)
									format(list, sizeof(list), "%s\n%d\t{878A87}%s\t%d\t%d", list, ItemInfo[i][iUID], ItemInfo[i][iName], ItemInfo[i][iValue1], ItemInfo[i][iValue2]);
						
						if(strlen(list)>40) ShowPlayerDialog(playerid, D_SAFEKEEP_DEPOSIT, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » wrzuæ przedmiot do skrytki", list, "Wybierz", "Anuluj");
						else msg_error(playerid, "Nie posiadasz odpowiednich przedmiotów.");
					}
					case 1:
					{
						format(list, sizeof(list), "UID\tNazwa\tWartoœæ 1\tWartoœæ 2");
						ForeachEx(i,_ITEM_COUNT)
							if(ItemInfo[i][iUID])
								if(ItemInfo[i][iOwnerTyp] == OWNER_SAFEKEEP_ITEM && ItemInfo[i][iOwner] == safeuid)
									format(list, sizeof(list), "%s\n%d\t{878A87}%s\t%d\t%d", list, ItemInfo[i][iUID], ItemInfo[i][iName], ItemInfo[i][iValue1], ItemInfo[i][iValue2]);
						
						if(strlen(list)>40) ShowPlayerDialog(playerid, D_SAFEKEEP_WITHDRAW, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » przedmioty w skrytce", list, "Wyci¹gnij", "Anuluj");
						else msg_error(playerid, "Brak przedmiotów w skrytce.");
					}
				}
			}
			return 1;
		}
		case D_SAFEKEEP_DEPOSIT:
		{
			if(response)
			{
				new iuid = strval(inputtext);
				new iuid2 = GetPVarInt(playerid, "keepkey");
				DeletePVar(playerid, "keepkey");
				
				ItemInfo[iuid][iOwnerTyp] = OWNER_SAFEKEEP_ITEM;
				ItemInfo[iuid][iOwner] = ItemInfo[iuid2][iValue1];
				
				mysql_query_format("UPDATE `srv_items` SET `ownertyp` = '%d', `owner` = '%d' WHERE `UID` = '%d' LIMIT 1", OWNER_SAFEKEEP_ITEM, ItemInfo[iuid2][iValue1], iuid);
				
				msg_infoFormat(playerid, 128, "Doda³eœ przedmiot %s do skrytki numer: %d.", ItemInfo[iuid][iName], ItemInfo[iuid2][iValue1]);
			}
			return 1;
		}
		case D_SAFEKEEP_WITHDRAW:
		{
			if(response)
			{
				new iuid = strval(inputtext);
				new iuid2 = GetPVarInt(playerid, "keepkey");
				DeletePVar(playerid, "keepkey");
				
				ItemInfo[iuid][iOwnerTyp] = OWNER_PLAYER;
				ItemInfo[iuid][iOwner] = CharacterInfo[playerid][pUID];
				
				mysql_query_format("UPDATE `srv_items` SET `ownertyp` = '%d', `owner` = '%d' WHERE `UID` = '%d' LIMIT 1", OWNER_PLAYER, CharacterInfo[playerid][pUID], iuid);
				
				msg_infoFormat(playerid, 128, "Wyci¹gn¹³eœ przedmiot %s ze skrytki numer: %d.", ItemInfo[iuid][iName], ItemInfo[iuid2][iValue1]);
			}
			return 1;
		}
		case D_WEAPON_MAGAZINE_CATEGORY:
		{
			if(response)
			{
				new string[512],uid,price,name[32],tmp[64];
				format(string,sizeof(string),"SELECT `uid`, `price`, `name` FROM `srv_weapons_magazine` WHERE `category`='%d'",listitem);
				mysql_query(string);
				mysql_store_result();
				format(string,sizeof(string),"UID\tNazwa\tCena");
				while(mysql_fetch_row_format(tmp))
				{
					sscanf(tmp,"p<|>dds[32]",uid,price,name);
					format(string,sizeof(string),"%s\n%2d\t%s\t$%d",string,uid,name,price);
				}
				mysql_free_result();

				if(strlen(string)>16)
					ShowPlayerDialog(playerid,D_WEAPON_MAGAZINE_BUY,DIALOG_STYLE_TABLIST_HEADERS,DEF_NAME" » wybierz przedmiot",string,"Wybierz","WyjdŸ");
				else
					msg_error(playerid,"Brak produktów z danej kategorii");
			}
			return 1;
		}
		case D_WEAPON_MAGAZINE_BUY:
		{
			if(response)
			{
				new uid=strval(inputtext);
				new query[128],type, value1, value2, name[32],price;
				format(query,sizeof(query),"SELECT `price`, `type`, `value1`, `value2`, `name` FROM `srv_weapons_magazine` WHERE `uid`='%d'",uid);
				mysql_query(query);
				mysql_store_result();
				mysql_fetch_row_format(query);
				sscanf(query,"p<|>dddds[32]",price,type,value1,value2,name);
				mysql_free_result();

				if(price <= 0 || !type)
					return msg_error(playerid,"B³¹d. Skontaktuj siê z administracj¹.");

				if(CharacterInfo[playerid][pCash] < price)
					return msg_error(playerid,"Nie posiadasz wystarczaj¹cej iloœci gotówki.");

				GivePlayerCash(playerid,-price);
				StworzPrzedmiot(OWNER_PLAYER, CharacterInfo[playerid][pUID], name, type, value1, value2, 1);
				format(query,sizeof(query),"Kupi³eœ %s za $%d.",name,price);
				SendClientMessage(playerid, COLOR_GREEN, query);

			}
			return 1;
		}
		case D_DOTACJA:
		{
			if(response)
			{
				if(!DutyGroup[playerid] || GroupInfo[DutyGroup[playerid]][gType] != GROUP_GOV)
					return msg_error(playerid, "Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
				
				if(!PlayerDoor[playerid] || DoorsInfo[PlayerDoor[playerid]][dOwner] != DutyGroup[playerid])
					return msg_error(playerid, "Nie znajdujesz siê w budynku GOV.");
				
				if(IsPlayerPermInGroup(playerid, DutyGroup[playerid], PERM_CASH))
				{
					new uid = GetPVarInt(playerid, "DotacjaUID");
					new cash = GetPVarInt(playerid, "DotacjaCASH");
					DeletePVar(playerid, "DotacjaUID");
					DeletePVar(playerid, "DotacjaCASH");
					
					GiveGroupCash(DutyGroup[playerid], -cash);
					GiveGroupCash(uid, cash);
					new string[32];
					format(string,sizeof(string),"Dostacja %d:%s",uid,GroupInfo[uid][gName]);
					LogGroupOffer(playerid, DutyGroup[playerid], string, -cash, playerid);
					LogGroupOffer(playerid, uid, "[GOV] Dotacja", cash, playerid);
					
					msg_info(playerid, "Dotacja zosta³a przelana na konto grupy.");
				}
			}
			return 1;
		}
		case D_GROUP_CHANGE_TYPE:
		{
			if(response)
			{
				new guid = GetPVarInt(playerid, "agrupatyp");
				DeletePVar(playerid, "agrupatyp");
				new type = listitem;
				
				GroupInfo[guid][gType] = type;
				SaveGroup(guid, SAVE_GROUP_BASIC);
			}
			return 1;
		}
		case D_REGISTER_VEHICLE_BOT:
		{
			if(response)
			{
				new uid = strval(inputtext);
				
				if(CharacterInfo[playerid][pCash] < SettingInfo[sPlateCharge])
					return msg_error(playerid,"Nie posiadasz wystarczaj¹cej iloœci gotówki na wyrobienie rejestracji.");
				
				if(!VehicleInfo[uid][vUID])
					return msg_error(playerid,"Nie znaleziono pojazdu o podanym UID.");
				
				if(VehicleInfo[uid][vRegistered])
					return msg_error(playerid,"Wpisany pojazd jest ju¿ zarejestrowany");
				
				if((VehicleInfo[uid][vOwnerTyp] == OWNER_PLAYER && VehicleInfo[uid][vOwner] == CharacterInfo[playerid][pUID]) || (VehicleInfo[uid][vOwnerTyp] == OWNER_GROUP && GroupInfo[VehicleInfo[uid][vOwner]][gLeader] == CharacterInfo[playerid][pUID]))
				{
					VehicleInfo[uid][vRegistered] = 1;
					
					new tablica[8];
					format(tablica, sizeof(tablica), "LS-%04d", uid);
					VehicleInfo[uid][vRegister] = tablica;
					
					SaveVehicle(uid, SAVE_VEH_BASIC);
					
					new gid = -1;
					ForeachEx(guid, MAX_GROUPS)
					{
						if(GroupInfo[guid][gType] == GROUP_GOV)
						{
							gid = guid;
							break;
						}
					}
					
					if(gid != -1)
						GiveGroupCash(gid, SettingInfo[sPlateCharge]);
					
					GivePlayerCash(playerid,-SettingInfo[sPlateCharge]);
					
					msg_info(playerid, "Pojazd zosta³ zarejestrowany.");
				}
				else
					return msg_error(playerid, "Nie mo¿esz zarejestrowaæ tego pojazdu.");
			}
			return 1;
		}
		case D_DESCRIPTION_OPT:
		{
			if(response)
			{
				new uid = strval(inputtext);
				SetPVarInt(playerid, "DescriptionUID", uid);
				
				ShowPlayerDialog(playerid, D_DESCRIPTION_END, DIALOG_STYLE_LIST, DEF_NAME" » opis postaci", "1. Ustaw opis jako aktywny\n2. Usuñ opis z listy", "Wybierz", "Anuluj");
			}
			return 1;
		}
		case D_DESCRIPTION_END:
		{
			if(response)
			{
				new uid = GetPVarInt(playerid, "DescriptionUID");
				DeletePVar(playerid, "DescriptionUID");
				
				switch(listitem)
				{
					case 0:
					{
						new text[128];
						new data[256];
						
						mysql_query_format("SELECT `text` FROM `srv_descriptions_text` WHERE `UID` = '%d'", uid);
						mysql_store_result();
						
						if(mysql_num_rows())
						{
							mysql_fetch_row_format(data);
							
							sscanf(data, "p<|>s[128]", text);
							
							if(!ValidateDesc(text, IsPlayerPremium(playerid)))
								return msg_error(playerid, "Opis postaci zawiera niedozwolony znak lub znaki!");
							
							if(Description[playerid] != Text3D:INVALID_3DTEXT_ID)
							{
								DestroyDynamic3DTextLabel(Description[playerid]);
								Description[playerid] = CreateDynamic3DTextLabel(WordWrap(text, 5), COLOR_VEH_DESC, 0.0, 0.0, -0.6, 7.0, playerid, -1, 1);
							}
							else
								Description[playerid] = CreateDynamic3DTextLabel(WordWrap(text, 5), COLOR_VEH_DESC, 0.0, 0.0, -0.6, 7.0, playerid, -1, 1);
							
							msg_infoFormat(playerid, 256, "Ustawi³eœ sobie nowy opis: \n\n%s", text);
							CharacterInfo[playerid][pCurrentDescription] = text;
						}
						mysql_free_result();
					}
					case 1:
					{
						mysql_query_format("DELETE FROM `srv_descriptions` WHERE `UID`='%d' LIMIT 1", uid);
						mysql_query_format("DELETE FROM `srv_descriptions_text` WHERE `UID`='%d' LIMIT 1", uid);
						
						DescriptionInfo[uid][descUID] = 0;
						DescriptionInfo[uid][descOwner] = 0;
						
						msg_info(playerid, "Usun¹³eœ opis ze swojej listy.");
					}
				}
			}
			return 1;
		}
		case 	D_GYM_PUNCH_BAG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_GRABKICK);
					case 1:
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_BOXING);
					case 2:
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_KUNGFU);
					case 3:
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_KNEEHEAD);
				}
				OnPlayerGymTrainStarted(playerid, TRAIN_PUNCH_BAG, CharacterInfo[playerid][pGymObject]);
			}
			else
				CharacterInfo[playerid][pGymObject]=0;
			return 1;
		}
		case D_DOOR_CHANGE_PRICE:
		{
			if(response)
			{
				new val = strval(inputtext);
				
				if(val > 100 || val < 0)
					return msg_error(playerid, "Wpisana kwota nie jest prawidlowa.");
				
				DoorsInfo[PlayerDoor[playerid]][dPriceForEntry] = val;
				SaveDoors(PlayerDoor[playerid], SAVE_DOORS_BASIC);
				
				msg_info(playerid, "Zmieni³es cene za wejœcie.");
			}
			return 1;
		}
		case D_OFFER_VEHICLE_END_KOMIS:
		{
			if(!response) return 1;

			Oferta(OFFER_VEHICLE_KOMIS, playerid, GetPVarInt(playerid,"OfferBuyer"), GetPVarInt(playerid, "OfferPrice"), GetPVarInt(playerid, "OfferVehicleUID"));
			return 1;
		}
		case D_CHANGE_VEH_OWNER_V:
		{
			if(response)
			{
				new vehuid = GetPVarInt(playerid, "changevehowner");
				DeletePVar(playerid, "changevehowner");
				new slot = strval(inputtext);
				new guid = MemberGroup[playerid][slot][GroupID];

				new string[128];
				format(string,sizeof(string),"INSERT INTO `srv_veh_logs` VALUES ('%d','%d','%d','%d','%d','%d','%d','3','%d')", CharacterInfo[playerid][pUID], CharacterInfo[playerid][pGID], 0, guid, 0, vehuid, VehicleInfo[vehuid][vModel], gettime());
				mysql_query(string);		
				
				VehicleInfo[vehuid][vOwnerTyp] = OWNER_GROUP;
				VehicleInfo[vehuid][vOwner] = guid;
				SaveVehicle(vehuid, SAVE_VEH_OWNER);
				
				msg_info(playerid, "Przepisa³eœ pojazd pod wybran¹ grupê.");
			}
			return 1;
		}
		case D_MANDAT_ACCEPT:
		{
			if(response)
			{
				new seller = GetPVarInt(playerid, "OfferSeller");
				new uid = GetPVarInt(playerid, "OfferUID");
				new price = GetPVarInt(playerid, "OfferPrice");
				
				DeletePVar(playerid,"OfferUID");
				DeletePVar(playerid,"OfferPrice");
				DeletePVar(playerid,"OfferSeller");
				
				if(GroupInfo[DutyGroup[seller]][gType] != GROUP_PD)
					return msg_error(playerid,"Wybrany gracz nie jest na s³u¿bie odpowiedniej grupy.");
				
				switch(listitem)
				{
					case 0:
					{
						if(CharacterInfo[playerid][pCash] < price)
						{
							msg_error(seller, "Wybrany gracz nie ma przy sobie odpowiedniej kwoty.");
							return msg_error(playerid, "Nie masz przy sobie odpowiedniej kwoty.");
						}
						GivePlayerCash(playerid, -price);
					}
					case 1:
					{
						if(CharacterInfo[playerid][pCredit] < price)
						{
							msg_error(seller, "Wybrany gracz nie ma w banku odpowiedniej kwoty.");
							return msg_error(playerid, "Nie masz w banku odpowiedniej kwoty.");
						}
						CharacterInfo[playerid][pCredit] -= price;
					}
				}
				
				GiveGroupCash(DutyGroup[seller], price);
				
				SendClientMessageFormat(seller,COLOR_GREEN,"Mandat zaakceptowany. Kwota: $%d, punkty: %d.", price, uid);
				
				if(seller != playerid)
					SendClientMessageFormat(playerid,COLOR_GREEN,"Mandat zaakceptowany. Kwota: $%d, punkty: %d.", price, uid);
				
				CharacterInfo[playerid][pPenaltyPoints] += uid;
				
				if(CharacterInfo[playerid][pPenaltyPoints] >= 24)
				{
					msg_info(playerid, "Twoje prawo jazdy zosta³o zabrane z powodu uzyskanych 24 punktów karnych.");
					CharacterInfo[playerid][pPenaltyPoints] = 0;
					CharacterInfo[playerid][pDriverPenalty] = 1200;
					if(CharacterInfo[playerid][pDocs] & DOC_DRIVER)
						CharacterInfo[playerid][pDocs] -= DOC_DRIVER;
				}
				LogGroupOffer(seller,DutyGroup[seller],"Mandat",price,playerid);
				SavePlayerStats(playerid, SAVE_PLAYER_OPTION);
				SavePlayerStats(playerid, SAVE_PLAYER_BASIC);
			}
			return 1;
		}
		case D_WORKSHOP_ACCEPT:
		{
			if(response)
			{
				new seller = GetPVarInt(playerid, "OfferSeller");
				new uid = GetPVarInt(playerid, "OfferUID");
				new price = GetPVarInt(playerid, "OfferPrice");
				new type = GetPVarInt(playerid, "WorkshopTypeOfWork");
				
				DeletePVar(playerid,"OfferUID");
				DeletePVar(playerid,"OfferPrice");
				DeletePVar(playerid,"OfferSeller");
				
				if(GroupInfo[DutyGroup[seller]][gType] != GROUP_WORKSHOP)
					return msg_error(playerid,"Wybrany gracz nie jest na s³u¿bie odpowiedniej grupy.");
				
				switch(listitem)
				{
					case 0:
					{
						if(CharacterInfo[playerid][pCash] < price)
						{
							msg_error(seller, "Gracz nie posiada odpowiedniej kwoty.");
							return msg_error(playerid, "Nie posiadasz odpowiedniej kwoty.");
						}
						SetPVarInt(playerid, "WorkshopPayOption", 0);
					}
					case 1:
					{
						if(CharacterInfo[playerid][pCredit] < price)
						{
							msg_error(seller, "Gracz nie posiada odpowiedniej kwoty.");
							return msg_error(playerid, "Nie posiadasz odpowiedniej kwoty.");
						}
						SetPVarInt(playerid, "WorkshopPayOption", 1);
					}
				}
				
				SendClientMessage(seller, COLOR_GREEN, "Gracz zaakceptowa³ twoj¹ ofertê, rozpocznij pracê.");
				CharacterInfo[seller][pRepairTime]=120;
				CharacterInfo[seller][pRepairVeh]=uid;
				if(VehicleInfo[uid][vEngine])
				{
					VehicleInfo[uid][vEngine] = false;	
					ChangeVehicleEngineStatus(VehicleInfo[uid][vSAMPID], false);
				}
				SetPVarInt(seller,"pRepairCustomer",playerid);
				SetPVarInt(seller,"pRepairPrice",price);
				if(seller)
					SetPVarInt(playerid,"pRepairMechanic",seller);
				else
					SetPVarInt(playerid,"pRepairMechanic",-1);

				new string[64];
				//SetPVarInt(seller,"pRepairJobPrice", price - floatround(1000.0 - VehicleInfo[uid][vHP]));
				CharacterInfo[seller][pRepairType]=type;
				if(type==OFFER_PAINT || type==OFFER_PAINTJOB)
				{
					GameTextForPlayer(playerid,"~g~Malowanie rozpoczete.",3000,5);
					format(string, sizeof(string), "Malowanie pojazdu: %d sekund", CharacterInfo[seller][pRepairTime]);
					CharacterInfo[seller][pRepair3DText] = CreateDynamic3DTextLabel(string, 0x2836FFFF, VehicleInfo[uid][vposx], VehicleInfo[uid][vposy], VehicleInfo[uid][vposz]+2, 5.0, INVALID_PLAYER_ID, VehicleInfo[uid][vSAMPID], 1, GetPlayerVirtualWorld(seller), GetPlayerInterior(seller));
				}
				else if(type==OFFER_REPAIR_ENG || type==OFFER_REPAIR_BODY ||type==OFFER_REPAIR_TIRES || type==OFFER_REPAIR_ALL)
				{
					GameTextForPlayer(playerid,"~g~Naprawa rozpoczeta.",3000,5);
					format(string, sizeof(string), "Naprawa pojazdu: %d sekund", CharacterInfo[seller][pRepairTime]);
					CharacterInfo[seller][pRepair3DText] = CreateDynamic3DTextLabel(string, 0x2836FFFF, VehicleInfo[uid][vposx], VehicleInfo[uid][vposy], VehicleInfo[uid][vposz]+2, 5.0, INVALID_PLAYER_ID, VehicleInfo[uid][vSAMPID], 1, GetPlayerVirtualWorld(seller), GetPlayerInterior(seller));
				}
				else if(type==OFFER_TUNING || type==OFFER_DISMOUNT)
				{
					GameTextForPlayer(playerid,"~g~Tuning rozpoczety.",3000,5);
					format(string, sizeof(string), "Tuning pojazdu: %d sekund", CharacterInfo[seller][pRepairTime]);
					CharacterInfo[seller][pRepair3DText] = CreateDynamic3DTextLabel(string, 0x2836FFFF, VehicleInfo[uid][vposx], VehicleInfo[uid][vposy], VehicleInfo[uid][vposz]+2, 5.0, INVALID_PLAYER_ID, VehicleInfo[uid][vSAMPID], 1, GetPlayerVirtualWorld(seller), GetPlayerInterior(seller));
				}
			}
			return 1;
		}
		case D_GROUP_CLEAR:
		{
			if(response)
			{
				new uid = GetPVarInt(playerid,"clearGroupID");
				DeletePVar(playerid,"clearGroupID");

				ForeachPlayer(i)
				{
					if(Logged[i] && IsPlayerInGroup(i,uid))
					{
						DeleteMember(i,uid);
						SendClientMessage(i, COLOR_GREEN, "Jedna z Twoich grup zosta³a wyczyszczona.");
					}
				}
				new string[96];
				format(string,sizeof(string),"DELETE FROM `srv_groups_members` WHERE `group_uid`='%d'",uid);
				mysql_query(string);
				format(string,sizeof(string),"[AI] Grupa %s[UID:%d] zosta³a wyczyszczona.",GroupInfo[uid][gName],uid);
				SendClientMessage(playerid, COLOR_GREEN, string);

			}
			DeletePVar(playerid, "clearGroupID");
			return 1;
		}
		case D_DOOR_CHANGE_TIME:
		{
			if(response)
			{
				new time = strval(inputtext);
				if(time > 24 || time < 1)
					return msg_error(playerid, "Wprowadzony czas nie jest prawid³owy (miêdzy 1 a 24).");
				
				SetPlayerTime(playerid, time, 0);
				DoorsInfo[PlayerDoor[playerid]][dTime] = time;
				new string[256];
				format(string, sizeof(string), "UPDATE `srv_doors` SET `time` = '%d' WHERE `UID` = '%d' LIMIT 1", time, PlayerDoor[playerid]);
				mysql_query(string);
			}
			return 1;
		}
		case D_DOOR_CHANGE_WEATHER:
		{
			if(response)
			{
				new weather = strval(inputtext);
				if(weather < 0)
					return msg_error(playerid, "Wprowadzona pogoda nie jest prawid³owy (miêdzy 1 a 24).");
				
				SetPlayerWeather(playerid, weather);
				DoorsInfo[PlayerDoor[playerid]][dWeather] = weather;
				new string[256];
				format(string, sizeof(string), "UPDATE `srv_doors` SET `weather` = '%d' WHERE `UID` = '%d' LIMIT 1", weather, PlayerDoor[playerid]);
				mysql_query(string);
			}
			return 1;
		}
		case D_GASTRO_BUY:
		{
			if(response)
			{
				new jedzenie;
				
				if(CharacterInfo[playerid][pGlod] == 100)
					return msg_error(playerid,"Nie jesteœ g³odny.");
				
				switch(listitem)
				{
					case 0:
					{
						if(CharacterInfo[playerid][pCash] < 30)
							return msg_error(playerid, "Nie masz przy sobie odpowiednich œrodków aby to zakupiæ ($30).");
						
						GivePlayerCash(playerid, -30);
						jedzenie = 10;
					}
					case 1:
					{
						if(CharacterInfo[playerid][pCash] < 60)
							return msg_error(playerid, "Nie masz przy sobie odpowiednich œrodków aby to zakupiæ ($60).");
						
						GivePlayerCash(playerid, -60);
						jedzenie = 20;
					}
					case 2:
					{
						if(CharacterInfo[playerid][pCash] < 80)
							return msg_error(playerid, "Nie masz przy sobie odpowiednich œrodków aby to zakupiæ ($80).");
						
						GivePlayerCash(playerid, -80);
						jedzenie = 30;
					}
				}
				
				if(jedzenie)
				{
					if(CharacterInfo[playerid][pGlod]+jedzenie > 100) CharacterInfo[playerid][pGlod] = 100;
					else CharacterInfo[playerid][pGlod] += jedzenie;
					
					if(CharacterInfo[playerid][pGlod] > 10) SetPlayerDrunkLevel(playerid, 0);
					
					SavePlayerStats(playerid, SAVE_PLAYER_BASIC);
					
					SetPlayerProgressBarValue(playerid, FoodBar[playerid], CharacterInfo[playerid][pGlod]);
					UpdatePlayerProgressBar(playerid, FoodBar[playerid]);
				}
			}
			return 1;
		}
		case D_ORDER_END:
		{
			if(response)
			{
				if(strlen(inputtext) >= 32)
					return msg_error(playerid, "Wprowadzi³eœ zbyt d³ug¹ nazwê (max 32 znaki)!");
				
				if(strlen(inputtext) < 3)
					return msg_error(playerid, "Wprowadzi³eœ zbyt krótk¹ nazwê (min 3 znaki)!");
				
				new string[512], data[64], product_value1, product_value2, product_cash, product_kind, product_name[32];
				mysql_real_escape_string(inputtext,inputtext);
				format(product_name, sizeof(product_name), "%s", inputtext);
				
				new amount = GetPVarInt(playerid, "ProductValue");
				new product_id = GetPVarInt(playerid, "ProductID");
				new doorid = GetPVarInt(playerid, "ProductDoor");
				DeletePVar(playerid, "ProductValue");
				DeletePVar(playerid, "ProductID");
				DeletePVar(playerid, "ProductDoor");
				
				format(string,sizeof(string),"SELECT `value1`, `value2`, `price`, `type` FROM `srv_order_products` WHERE `uid` = '%d'", product_id);
				
				mysql_query(string);
				mysql_store_result();			
				mysql_fetch_row_format(data, "|");
				sscanf(data, "p<|>dddd", product_value1, product_value2, product_cash, product_kind);
				mysql_free_result();

				new price=product_cash * amount;
				
				new shippment = 20 + price/10;
				
				if(shippment > 400)
					shippment = 400;
				
				if(GroupInfo[DoorsInfo[doorid][dOwner]][gCash] < (price + shippment))
					return msg_error(playerid,"Na koncie grupowym nie znajduje siê odpowiednia kwota na zakup produktu.");
				
				GiveGroupCash(DoorsInfo[doorid][dOwner], -(price+shippment));
				
				mysql_query_format("INSERT INTO `srv_orders` (`door_uid`, `value1`, `value2`, `name`, `count`, `driver`, `kind`, `shippment_cost`) VALUES ('%d', '%d', '%d', '%s', '%d', '%d', '%d', '%d')", DoorsInfo[doorid][dUID], product_value1, product_value2, product_name, amount, 0, product_kind, shippment);
				
				new uid = mysql_insert_id();
				
				format(string, sizeof(string), "{008000}Produkt zamówiony!");
				format(string, sizeof(string), "%s\n\n{FFFFFF}Numer przesy³ki: %d", string, uid);
				format(string, sizeof(string), "%s\nNazwa: %s", string, product_name);
				format(string, sizeof(string), "%s\nIloœæ: %d", string, amount);
				format(string, sizeof(string), "%s\nCena za szt.: $%d\n", string, product_cash);
				format(string, sizeof(string), "%s\nTransport: $%d\n£¹cznie: $%d\n\n", string, shippment, shippment + price);
				
				new bool:logistics = false;
				
				ForeachPlayer(i)
				{
					if(IsPlayerOnDutyInGroup(i, GROUP_LOGISTIC) && !(CharacterInfo[i][pStatus] & STATUS_AFK))
					{
						SendClientMessage(i, COLOR_YELLOW, "Do firmy logistycznej trafi³o nowe zamówienie, udaj siê do magazynu aby je odebraæ i zrealizowaæ!");
						if(!logistics)
							logistics = true;
					}
				}
				
				if(!logistics)
					SendClientMessage(playerid, COLOR_YELLOW, "Aktualnie ¿adna firma logistyczna nie pracuje, wiêc twoje zamówienie mo¿e przyjechaæ z opóŸnieniem.");
				
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » produkt zamówiony!", string, "Zamknij", "");
			}
			return 1;
		}
		case D_ATTACHED_BUY:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
						ShowModelSelectionMenu(playerid, doczepialne_0, "Nakrycia glowy");
					case 1:
						ShowModelSelectionMenu(playerid, doczepialne_1, "Okulary");
					case 2:
						ShowModelSelectionMenu(playerid, doczepialne_2, "Zegarki");
					case 3:
						ShowModelSelectionMenu(playerid, doczepialne_3, "Maski");
					case 4:
						ShowModelSelectionMenu(playerid, doczepialne_4, "Pozostale");
				}
			}
			return 1;
		}
		case D_MASKA_OBJ:
		{
			new uid = GetPVarInt(playerid, "MaskaUID");
			DeletePVar(playerid, "MaskaUID");
			if(response)
			{
				new query[196],Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ;
				format(query, sizeof(query), "SELECT `x`, `y`, `z`, `rx`, `ry`, `rz`, `sx`, `sy`, `sz` FROM `srv_attached` WHERE `UID`='%d'", uid);
				fScaleX=fScaleY=fScaleZ=1.0;
				mysql_query(query);
				mysql_store_result();
				if(mysql_num_rows())
				{
					mysql_fetch_row_format(query);
					sscanf(query,"p<|>fffffffff", fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
				}
				else
				{
					mysql_free_result();
					format(query,sizeof(query),"INSERT INTO `srv_attached` VALUES ('%d', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f')", uid, SLOT_MASK, ItemInfo[uid][iValue1], ItemInfo[uid][iValue2], 
					fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);	
					mysql_query(query);
				}
				
				mysql_free_result();
				
				CharacterInfo[playerid][pMaskObj] = true;
				CharacterInfo[playerid][pAttached][SLOT_MASK] = uid;
				SetPlayerAttachedObject(playerid, SLOT_MASK, ItemInfo[uid][iValue1], ItemInfo[uid][iValue2], fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
				EditAttachedObject(playerid, SLOT_MASK);
			}
			
			ItemInfo[uid][iUsed] = 1;
			CharacterInfo[playerid][pMask] = true;
			SendClientMessage(playerid, COLOR_RED, "Za³o¿y³eœ maskê, od teraz Twój nick nie jest widoczny.");
			new name[MAX_PLAYER_NAME];
			switch(CharacterInfo[playerid][pSex])
			{
				case 0:
					format(name,sizeof(name),"Nieznajoma_%s",CharCode(playerid));
				case 1:
					format(name,sizeof(name),"Nieznajomy_%s",CharCode(playerid));
			}
			SetPlayerName(playerid, name);
			
			return 1;
		}
		case D_SANN_PHONE:
		{
			if(response)
			{
				new groupid;
				ForeachEx(i, MAX_GROUPS)
				{
					if(GroupInfo[i][gUID] && GroupInfo[i][gType] == GROUP_NEWS)
					{
						groupid = i;
						break;
					}
				}
				
				if(groupid)
				{
					if(CharacterInfo[playerid][pCash] < SettingInfo[sSANNPay] && SettingInfo[sSANNPay])
						return msg_error(playerid, "Nie masz odpowiedniej kwoty przy sobie aby wys³aæ tego SMSa.");
					else if(SettingInfo[sSANNPay])
						GivePlayerCash(playerid, -SettingInfo[sSANNPay]);
					
					new number[24],title[24];
					format(number, sizeof(number),"Numer: %d", ItemInfo[CharacterInfo[playerid][pPhone]][iValue1]);
					format(title, sizeof(title), "[%s] *Nowe zg³oszenie*", GroupInfo[groupid][gTag]);
					ForeachPlayer(i)
					{
						if(DutyGroup[i]==groupid)
						{
							SendClientMessage(i, GetGroupColor(groupid), title);
							SendClientMessage(i, 0xFFFFFFFF, inputtext);
							SendClientMessage(i, GetGroupColor(groupid), number);
						}
					}
				}
				else
					return msg_error(playerid, "Wyst¹pi³ b³¹d, skontaktuj siê z administracj¹.");
			}
			
			return 1;
		}
		case D_CALL_RESTAURANT:
		{
			if(response)
			{
				SetPVarInt(playerid, "pRestGroup", strval(inputtext));
				ShowPlayerDialog(playerid,D_RESTAURANT_MSG,DIALOG_STYLE_INPUT,DEF_NAME" » zamówienie","Podaj treœæ zamówienia oraz dok³adn¹ lokalizacjê:","Dalej","Anuluj");
			}
			return 1;
		}
		case D_RESTAURANT_MSG:
		{
			if(response)
			{
				new groupid = GetPVarInt(playerid, "pRestGroup");
				new number[24], title[24];
				format(number, sizeof(number), "Numer: %d", ItemInfo[CharacterInfo[playerid][pPhone]][iValue1]);
				format(title, sizeof(title), "[%s] *Nowe zg³oszenie*", GroupInfo[groupid][gTag]);
				ForeachPlayer(i)
				{
					if(DutyGroup[i] == groupid)
					{
						SendClientMessage(i, GetGroupColor(groupid), title);
						SendClientMessage(i, 0xFFFFFFFF, inputtext);
						SendClientMessage(i, GetGroupColor(groupid), number);
					}
				}
			}
			DeletePVar(playerid,"pRestGroup");
			return 1;
		}
		case D_REGISTER_GROUP_BOT:
		{
			if(response)
			{
				new slot = strval(inputtext);
				new uid = MemberGroup[playerid][slot][GroupID];
				
				if(CharacterInfo[playerid][pCash] < SettingInfo[sGroupRegisterCharge])
					return msg_error(playerid, "Nie posiadasz wystarczaj¹cej iloœci gotówki na zarejestrowanie biznesu.");
				
				if(GroupInfo[uid][gRegistered])
					return msg_error(playerid, "Wybrana grupa jest ju¿ zarejestrowana.");
				
				if(GroupInfo[uid][gLeader] == CharacterInfo[playerid][pUID])
				{
					GroupInfo[uid][gRegistered] = 1;
					SaveGroup(uid, SAVE_GROUP_BASIC);
					
					new gid = -1;
					ForeachEx(guid, MAX_GROUPS)
					{
						if(GroupInfo[guid][gType] == GROUP_GOV)
						{
							gid = guid;
							break;
						}
					}
					
					if(gid != -1)
						GiveGroupCash(gid, SettingInfo[sGroupRegisterCharge]);
					
					GivePlayerCash(playerid, -SettingInfo[sGroupRegisterCharge]);
					
					msg_info(playerid, "Biznes zosta³ zarejestrowany.");
				}
				else
					return msg_error(playerid, "Nie jesteœ liderem tej grupy!");
			}
			return 1;
		}
		case D_GROUP_MAGAZINE_STACK:
		{
			if(response)
			{
				new uid = strval(inputtext);
				new groupid = GetPVarInt(playerid, "magguid");
				
				if(ItemInfo[uid][iType] == 1)
					return msg_error(playerid, "Nie mo¿esz ³¹czyæ broni!");
				
				ForeachEx(i, _ITEM_COUNT)
				{
					if(i != uid && ItemInfo[i][iUID] && ItemInfo[i][iOwnerTyp] == OWNER_GROUP && ItemInfo[i][iOwner] == GroupInfo[groupid][gUID])
					{
						if(ItemInfo[i][iType] == ItemInfo[uid][iType] && ItemInfo[i][iValue1] == ItemInfo[uid][iValue1] && ItemInfo[i][iValue2] == ItemInfo[uid][iValue2] && !strcmp(ItemInfo[i][iName], ItemInfo[uid][iName], true))
						{
							ItemInfo[uid][iIlosc] += ItemInfo[i][iIlosc];
							DeleteItem(i);
						}
					}
				}
				
				new query[128];
				format(query,sizeof(query),"UPDATE `srv_items` SET `ilosc` = '%d' WHERE `UID` = '%d'",ItemInfo[uid][iIlosc], uid);
				mysql_query(query);
			}
			DeletePVar(playerid, "magguid");
			return 1;
		}
		case D_FUELSTATION_TANK:
		{
			if(response)
			{
				new price = GetPVarInt(playerid, "sFuelPrice");
				new title[64];
				format(title, sizeof(title), DEF_NAME" » tankowanie ($%d)", price);
				
				new string[256];
				format(string, sizeof(string), "1. Portfel ($%d)\n2. Konto bankowe ($%d)", CharacterInfo[playerid][pCash], CharacterInfo[playerid][pCredit]);
				
				ShowPlayerDialog(playerid, D_FUELSTATION_TANK_END, DIALOG_STYLE_LIST, title, string, "Wybierz", "Zamknij");
			}
			return 1;
		}
		case D_FUELSTATION_TANK_END:
		{
			if(response)
			{
				new price = GetPVarInt(playerid, "sFuelPrice");
				new stationid = GetPVarInt(playerid, "sFuelStat");
				new vehuid = GetPVarInt(playerid, "sFuelVeh");
				new value = GetPVarInt(playerid, "sFuelVal");
				
				switch(listitem)
				{
					case 0:
					{
						if(CharacterInfo[playerid][pCash] < price)
							return msg_error(playerid, "Nie masz odpowiednich funduszy przy sobie aby zakupiæ paliwo.");
						
						GivePlayerCash(playerid, -price);
					}
					case 1:
					{
						if(CharacterInfo[playerid][pCredit] < price)
							return msg_error(playerid, "Nie masz odpowiednich funduszy na koncie bankowym aby zakupiæ paliwo.");
						
						CharacterInfo[playerid][pCredit] -= price;
						SavePlayerStats(playerid, SAVE_PLAYER_BASIC);
					}
				}
				
				if(GetPlayerStationID(playerid) != stationid || GetVehicleUID(GetPlayerVehicleID(playerid)) != vehuid)
					return msg_error(playerid, "Wyst¹pi³ b³¹d podczas procesu tankowania - spróbuj ponownie.");
				
				AddStationFuel(stationid,-value);
				VehicleInfo[vehuid][vFuel]+=float(value);
				GiveGroupCash(StationInfo[stationid][sOwner], price);
				SaveVehicle(vehuid, SAVE_VEH_BASIC);
				new string[128];
				format(string,sizeof(string),"tankuje pojazd %s.",GetVehicleModelName(VehicleInfo[vehuid][vModel]));
				cmd_me(playerid, string);
				format(string,sizeof(string),"Pomyslnie zatankowa³eœ %d litrów paliwa. Koszt: $%d.",value,price);
				msg_info(playerid,string);
			}
			DeletePVar(playerid, "sFuelPrice");
			DeletePVar(playerid, "sFuelStat");
			DeletePVar(playerid, "sFuelVeh");
			DeletePVar(playerid, "sFuelVal");
			
			return 1;
		}
        case D_WALKSTYLE:
        {
			if(response)
			{
				new style = listitem;
				CharacterInfo[playerid][pWalkStyle] = style;
				mysql_query_format("UPDATE `srv_characters` SET `walk_style` = '%d' WHERE `player_uid` = '%d'",style,CharacterInfo[playerid][pUID]);
				msg_info(playerid,"Styl chodzenia zmieniony pomyœlnie.");
			}
			
			return 1;
		}
		case D_SKIN_CHANGE:
		{
			if(response)
			{
				new id=strval(inputtext);
				
				CharacterInfo[playerid][pSkin] = SkinInfo[id][sModel];
				SetPlayerSkin(playerid, SkinInfo[id][sModel]);
				
				new sql[256];
				format(sql, sizeof(sql), "UPDATE `srv_characters` SET `skin` = '%d' WHERE `player_uid` = '%d' LIMIT 1", CharacterInfo[playerid][pSkin], CharacterInfo[playerid][pUID]);
				mysql_query(sql);
			}
			
			return 1;
		}
		case D_LOGIN_GLOBAL_2:
		{
			if(response)
			{
				mysql_real_escape_string(inputtext, inputtext);
				
				mysql_query_format("SELECT c.player_uid, c.nickname, c.block FROM `members` m, `srv_characters` c WHERE m.`members_pass_hash` = MD5(CONCAT(MD5(m.members_pass_salt),'', MD5('%s'))) AND m.`member_id` = c.`global_id` AND m.`members_display_name` = '%s'", inputtext, PlayerName(playerid));
				mysql_store_result();
				
				new data[1024], uid, nickname[32], list[1024], block;
				
				format(list, sizeof(list), "UID\tNazwa postaci");
				if(mysql_num_rows())
				{
					while(mysql_fetch_row_format(data, "|"))
					{
						sscanf(data, "p<|>ds[32]d", uid, nickname, block);
						
						UnderscoreToSpace(nickname);
						if(!((block & 1) || (block & 2) || (block & 4)))
							format(list, sizeof(list), "%s\n%d\t%s", list, uid, nickname);
					}
					
					if(strlen(list)<19)
					{
						msg_error(playerid,"Nie masz ¿adnej postaci na któr¹ mo¿esz wejœæ, stwórz j¹ w panelu gracza na forum.");
						KickWithWait(playerid);
					}
					else
						ShowPlayerDialog(playerid, D_LOGIN_GLOBAL_2_END, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » wybierz postaæ", list, "Wybierz", "Zamknij");
				}
				else
				{
					new string[32];
					
					format(string, sizeof(string), "Poda³eœ nieprawid³owe has³o.");
					ShowPlayerDialog(playerid, D_LOGIN_GLOBAL_2, DIALOG_STYLE_PASSWORD, DEF_NAME" » logowanie", string, "Zaloguj", "Zamknij");
				}
				
				mysql_free_result();
			}
			else
				KickWithWait(playerid);
			
			return 1;
		}
		case D_LOGIN_GLOBAL_2_END:
		{
			if(response)
			{
				new uid=strval(inputtext);
				OnPlayerLogin(playerid, uid);
			}
			else
				KickWithWait(playerid);
			
			return 1;
		}
		case D_ZGLOSZENIA:
		{
			if(response)
			{
				new id=strval(inputtext)-1;
				SetPVarInt(playerid, "911CallID", id);
				
				SendClientMessageFormat(playerid, COLOR_YELLOW, "Treœæ: %s", CallInfo[id][cReason]);
				
				ShowPlayerDialog(playerid, D_ZGLOSZENIA_2, DIALOG_STYLE_LIST, DEF_NAME" » opcje zg³oszenia", "Poka¿ na mapie\nOznacz jako zakoñczone", "Wybierz", "Zamknij");
			}
			
			return 1;
		}
		case D_ZGLOSZENIA_2:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
					{
						new id = GetPVarInt(playerid, "911CallID");
						
						if(CharacterInfo[playerid][p911Icon])
							DestroyDynamicMapIcon(CharacterInfo[playerid][p911Icon]);
						
						CharacterInfo[playerid][p911] = id;
						
						CharacterInfo[playerid][p911Icon] = CreateDynamicMapIcon(CallInfo[id][cPos][0], CallInfo[id][cPos][1], CallInfo[id][cPos][2], 0, COLOR_YELLOW, -1, -1, playerid, -1, MAPICON_GLOBAL);
						
						SendClientMessage(playerid, COLOR_YELLOW, "Zaznaczy³eœ miejsce zg³oszenia na swojej mapie.");
					}
					case 1:
					{
						new id = GetPVarInt(playerid, "911CallID");
						CallInfo[id][cID] = 0;
						
						if(CharacterInfo[playerid][p911Icon])
							DestroyDynamicMapIcon(CharacterInfo[playerid][p911Icon]);
						
						ForeachPlayer(i)
						{
							if(CharacterInfo[i][p911] >= 0 && CharacterInfo[i][p911Icon])
							{
								CharacterInfo[i][p911] = -1;
								DestroyDynamicMapIcon(CharacterInfo[i][p911Icon]);
							}
						}
						
						SendClientMessage(playerid, COLOR_YELLOW, "Oznaczy³eœ wybrane zg³oszenie jako zakoñczone.");
					}
				}
				
				DeletePVar(playerid, "911CallID");
			}
			
			return 1;
		}
		case D_SKIN_CHANGE_GROUP:
		{
			if(response)
			{
				new id=strval(inputtext);
				
				new giveplayer_id = GetPVarInt(playerid, "giveplayer_id");
				new giveplayer_slot = GetPVarInt(playerid, "giveplayer_slot");
				new groupid = GetPVarInt(playerid, "groupid");
				
				MemberGroup[giveplayer_id][giveplayer_slot][GroupSkin] = SkinInfo[id][sModel];
				SaveMember(giveplayer_id, groupid);
				
				msg_infoFormat(playerid, 128, "Ustawi³eœ skin grupowy (%d) dla gracza o ID: %d.", SkinInfo[id][sModel], giveplayer_id);
				msg_infoFormat(giveplayer_id, 128, "Zosta³ ci ustawiony grupowy roboczy (%d) w grupie (UID: %d).", SkinInfo[id][sModel], groupid);
			}
			
			return 1;
		}
	}
	return 1;
}