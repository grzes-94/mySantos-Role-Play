CMD:grupa(playerid,params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new slot, option[16], varchar[64];
	if(sscanf(params,"ds[16]S()[64]", slot, option, varchar))
	{
		new list[256];
		
		format(list, sizeof(list), "#\tUID\tNazwa\tRanga");
		
		for(new i=1;i < MAX_PLAYER_GROUPS; i++)
			if(MemberGroup[playerid][i][GroupID])
				format(list, sizeof(list), "%s\n%d\t%d\t%s\t%s", list, i, MemberGroup[playerid][i][GroupID], GroupInfo[MemberGroup[playerid][i][GroupID]][gName], MemberGroup[playerid][i][GroupRankName]);
		
		SendClientMessage(playerid, COLOR_GREY, "U¿yj: /g(rupa) {slot (1-5)} [info | przebierz | online | duty | pojazdy | opusc | magazyn | pomoc]");

		//SendClientMessage(playerid, COLOR_GREY, "U¿yj: /g(rupa) {slot (1-3)} [info | przebierz | online | duty | pojazdy | opusc | pojazdranga | ranga | pomoc | skin]");
		//SendClientMessage(playerid, COLOR_GREY, "U¿yj: /g(rupa) {slot (1-3)} [zapros | wypros | magazyn | spawn | wplac | wyplac | uprawnienia | ogloszenie | kolor]");
		
		if(strlen(list) > 21) ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » lista grup", list, "Zamknij", "");
		else msg_error(playerid, "Nie nale¿ysz do ¿adnej grupy.");
		
		return 1;
	}
	else if(slot<1 || slot>5)
		return msg_error(playerid,"Wprowadzono niepoprawny slot grupy.");
	else if(!MemberGroup[playerid][slot][GroupID])
		return msg_error(playerid,"Na tym slocie nie posiadasz ¿adnej grupy.");
	else if(!strcmp(option, "info", true))
	{
		new string[512];
		new hours, minutes, second;
		new groupid = MemberGroup[playerid][slot][GroupID];
		
		ConvertSecondsToTime(MemberGroup[playerid][slot][GroupTime], hours, minutes, second);
		
		format(string, sizeof(string), DEF_COLOR"UID:{FFFFFF}\t\t\t\t%d", GroupInfo[groupid][gUID]);
		format(string, sizeof(string), "%s\n"DEF_COLOR"Nazwa grupy:{FFFFFF}\t\t\t%s", string, GroupInfo[groupid][gName]);
		format(string, sizeof(string), "%s\n"DEF_COLOR"Tag grupy:{FFFFFF}\t\t\t%s", string, GroupInfo[groupid][gTag]);
		//format(string, sizeof(string), "%s\n{88CC54}Typ grupy:{FFFFFF}\t\t\t%s", string, GroupInfo[GroupData[groupid][Kind]][gName]);
		if(MemberGroup[playerid][slot][GroupPerm] & PERM_CASH)
			format(string, sizeof(string), "%s\n"DEF_COLOR"Stan konta:{FFFFFF}\t\t\t{008000}${FFFFFF} %d", string, GroupInfo[groupid][gCash]);
		format(string, sizeof(string), "%s\n"DEF_COLOR"Stanowisko:{FFFFFF}\t\t\t%s", string, MemberGroup[playerid][slot][GroupRankName]);
		format(string, sizeof(string), "%s\n"DEF_COLOR"Wyp³ata:{FFFFFF}\t\t\t{008000}${FFFFFF} %d", string, MemberGroup[playerid][slot][GroupSalary]);
		format(string, sizeof(string), "%s\n"DEF_COLOR"Czas s³u¿by:{FFFFFF}\t\t\t%dh, %dmin", string, hours, minutes, second);
		msg_info(playerid, string);
	}
	else if(!strcmp(option, "pomoc", true))
	{
		new string[512];
		
		if(GroupInfo[MemberGroup[playerid][slot][GroupID]][gType] == GROUP_GOV)
			format(string, sizeof(string), "/o dokument, /o rejestracja, /dotacja, /przeszukaj, /kajdanki, /bariera, /bot, /ws, /taser");
		else if(GroupInfo[MemberGroup[playerid][slot][GroupID]][gType] == GROUP_PD)
			format(string, sizeof(string), "/zbadaj, /przeszukaj, /namierz, /zabierz, /kajdanki, /zwloki, /blokada, /lspd, /o mandat, /o licencja \n/zbierz, /wepchnij, /wyrzuc, /(m)egafon, /taser, /ws, /d, @");
		else if(GroupInfo[MemberGroup[playerid][slot][GroupID]][gType] == GROUP_MC)
			format(string, sizeof(string), "/o leczenie, /reanimuj, /zbadaj, /zwloki, /(m)egafon, /d, /o poczytalnosc, /ws, @");
		else if(GroupInfo[MemberGroup[playerid][slot][GroupID]][gType] == GROUP_NEWS)
			format(string, sizeof(string), "/o reklama, /news, /reklamausun, /newsusun, /cenyuslug, @");
		else if(GroupInfo[MemberGroup[playerid][slot][GroupID]][gType] == GROUP_FBI)
			format(string, sizeof(string), "/przeszukaj, /namierz, /zabierz, /kajdanki, /zwloki, /knebel, /ciagnij, /wepchnij, /wyrzuc, /zwiaz, /ws, /taser, /nick, @");
		else if(GroupInfo[MemberGroup[playerid][slot][GroupID]][gType] == GROUP_MILITARY)
			format(string, sizeof(string), "/przeszukaj, /zabierz, /kajdanki, /zwloki, /zbadaj, /zwiaz, @");
		else if(GroupInfo[MemberGroup[playerid][slot][GroupID]][gType] == GROUP_GANG)
			format(string, sizeof(string), "/knebel, /ciagnij, /wepchnij, /wyrzuc, /corner, /przeszukaj, /zabierz, /zwiaz, @");
		else if(GroupInfo[MemberGroup[playerid][slot][GroupID]][gType] == GROUP_MAFIA)
			format(string, sizeof(string), "/knebel, /ciagnij, /wepchnij, /wyrzuc, /przeszukaj, /zabierz, /zwiaz, @");
		else if(GroupInfo[MemberGroup[playerid][slot][GroupID]][gType] == GROUP_DRIVERS)
			format(string, sizeof(string), "/przeszukaj, /zabierz, /knebel, /ciagnij, /wepchnij, /wyrzuc, /zwiaz, @");
		else if(GroupInfo[MemberGroup[playerid][slot][GroupID]][gType] == GROUP_SHOP)
			format(string, sizeof(string), "/cennik, @");
		else if(GroupInfo[MemberGroup[playerid][slot][GroupID]][gType] == GROUP_WORKSHOP)
			format(string, sizeof(string), "/o [paintjob, malowanie, naprawa, tuning, demontaz], /cenyuslug, @");
		else if(GroupInfo[MemberGroup[playerid][slot][GroupID]][gType] == GROUP_TAXI)
			format(string, sizeof(string), "/o przejazd, /cenyuslug, @");
		else if(GroupInfo[MemberGroup[playerid][slot][GroupID]][gType] == GROUP_LOGISTIC)
			format(string, sizeof(string), "/paczka, /transport, @");
		else if(GroupInfo[MemberGroup[playerid][slot][GroupID]][gType] == GROUP_GYM)
			format(string, sizeof(string), "/o karnet, /cenyuslug, @, /cennik");
		else if(GroupInfo[MemberGroup[playerid][slot][GroupID]][gType] == GROUP_RESTAURANT)
			format(string, sizeof(string), "/podaj, @, /cennik");
		else if(GroupInfo[MemberGroup[playerid][slot][GroupID]][gType] == GROUP_CARDEALER)
			format(string, sizeof(string), "/sprzedajpojazd, @");
		else if(GroupInfo[MemberGroup[playerid][slot][GroupID]][gType] == GROUP_SYNDICATE)
			format(string, sizeof(string), "/magazyn, /knebel, /ciagnij, /wepchnij, /wyrzuc, /przeszukaj, /zabierz, /zwiaz, @");
		else if(GroupInfo[MemberGroup[playerid][slot][GroupID]][gType] == GROUP_CARTEL)
			format(string, sizeof(string), "/knebel, /ciagnij, /wepchnij, /wyrzuc, /przeszukaj, /zabierz, /zwiaz, @");
		else if(GroupInfo[MemberGroup[playerid][slot][GroupID]][gType] == GROUP_KASYNO)
			format(string, sizeof(string), "/ruletka, /fortuna, @");
		else if(GroupInfo[MemberGroup[playerid][slot][GroupID]][gType] == GROUP_FUELSTATION)
			format(string, sizeof(string), "/cenyuslug, @");
		
		if(GroupInfo[MemberGroup[playerid][slot][GroupID]][gFlags] & FLAG_JAIL)
			format(string, sizeof(string), "%s, /przetrzymanie, /wypusc", string);
		
		if(MemberGroup[playerid][slot][GroupPerm] & PERM_PERSONEL)
			format(string,sizeof(string),"%s\n\nKomendy lidera:\n/g [slot] [zapros | wypros | uprawnienia | skin | ranga | prowizja | wyplata | pojazdranga | kolor | ogloszenie | spawn | respawn | ooc]",string);

		if(strlen(string))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » komendy grupy", string, "Zamknij", "");
		else
			msg_error(playerid, "Brak komend danej grupy.");
	}
	else if(!strcmp(option, "przebierz", true))
	{
		if(!MemberGroup[playerid][slot][GroupSkin])
			return msg_error(playerid,"Lider grupy nie ustawi³ Ci ubrania pracowniczego.");
		if(GetPlayerState(playerid) == 4 || GetPlayerState(playerid) == 5 || GetPlayerState(playerid) == 6)
			return 1;
		
		if(GetPlayerSkin(playerid) == MemberGroup[playerid][slot][GroupSkin])
		{
			SetPlayerSkin(playerid, CharacterInfo[playerid][pSkin]);
			msg_info(playerid, "Pomyœlnie za³o¿y³eœ swoje ubranie codzienne.");
		}
		else
		{
			SetPlayerSkin(playerid, MemberGroup[playerid][slot][GroupSkin]);
			msg_info(playerid, "Pomyœlnie za³o¿y³eœ na siebie ubranie pracownicze.");
		}
	}
	else if(!strcmp(option, "online", true))
	{
		new groupid = MemberGroup[playerid][slot][GroupID];
		new string[1024];
		
		format(string, sizeof(string), "ID\tRANGA\tImiê i Nazwisko");
		
		ForeachPlayer(i)
		{
			for(new x = 1; x<MAX_PLAYER_GROUPS; x++)
			{
				if(MemberGroup[i][x][GroupID] == groupid)
				{
					if(DutyGroup[i] == groupid) format(string, sizeof(string), "%s\n%d\t%s\t%s {FFC675}(na s³u¿bie){FFFFFF}", string, i, MemberGroup[i][x][GroupRankName], PlayerName2(i));
					else format(string, sizeof(string), "%s\n%d\t%s\t%s{FFFFFF}", string, i, MemberGroup[i][x][GroupRankName], PlayerName2(i));
					break;
				}
			}
		}
		
		if(strlen(string) > 28)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » pracownicy online", string, "Zamknij", "");
		else
			msg_error(playerid, "Brak pracowników online.");
	}
	else if(!strcmp(option, "duty", true) || !strcmp(option, "slu¿ba", true) || !strcmp(option, "sluzba", true))
	{
		if(CharacterInfo[playerid][pAdminDuty])
			return msg_error(playerid,"Aby wejœæ na s³u¿bê w grupie musisz zakoñczyæ swoj¹ s³u¿bê administracyjn¹.");
		
		new groupid = MemberGroup[playerid][slot][GroupID];
		if(IsCriminalGroup(groupid))
			return msg_error(playerid,"Nie mo¿esz wejœæ na s³u¿bê grupy przestêpczej.");
		
		if(MemberGroup[playerid][slot][GroupID] == DutyGroup[playerid])
		{
			new hours, minutes, second;
			//DutyGroupTime[playerid]=CharacterInfo[playerid][pOnlineToday]-DutyGroupTime[playerid];
			MemberGroup[playerid][slot][GroupTime]=DutyGroupTime[playerid];
			ConvertSecondsToTime(MemberGroup[playerid][slot][GroupTime], hours, minutes, second);
			SendClientMessageFormat(playerid, GroupInfo[groupid][gColor], " » Zszed³eœ ze s³u¿by w grupie %s (%d). Przepracowa³eœ dziœ %dh, %dmin.", GroupInfo[groupid][gName], groupid, hours, minutes);
			
			SaveMember(playerid, groupid);

			if(CharacterInfo[playerid][pTaxiPassenger] != INVALID_PLAYER_ID)
			{
				msg_info(CharacterInfo[playerid][pTaxiPassenger], "Kierowca zszed³ ze s³u¿by w grupie. Przejazd anulowany.");
				DeletePVar(CharacterInfo[playerid][pTaxiPassenger], "pTaxiDriver");
				CharacterInfo[playerid][pTaxiDistance] = 0;
				CharacterInfo[playerid][pTaxiPassenger] = INVALID_PLAYER_ID;
			}
			
			if(IsPlayerPremium(playerid)) CharacterInfo[playerid][pNickColor] = COLOR_PREMIUM;
			else CharacterInfo[playerid][pNickColor] = COLOR_USER;
			
			if(CharacterInfo[playerid][pGPS] && DutyGroup[playerid] == CharacterInfo[playerid][pGPS])
			{
				CharacterInfo[playerid][pGPS] = 0;
				
				ForeachPlayer(g)
				{
					for(new d = 0; d<MAX_WS_MAPICONS; d++)
					{
						if(WS_MAPICONS[g][d] != -1)
							DestroyDynamicMapIcon(WS_MAPICONS[g][d]);
						
						WS_MAPICONS[g][d] = -1;
					}
				}
				
				GameTextForPlayer(playerid, "~y~~>~ Wylaczyles namierzanie GPS. ~<~", 3000, 3);
				
				if(CharacterInfo[playerid][pTog] & TOG_STATUS)
				{
					PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][0]);
					
					PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][1]);
					PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][2]);
				}
			}
			
			DutyGroup[playerid] = 0;
			DutyGroupTime[playerid] = 0;
			
			if(CharacterInfo[playerid][pTog] & TOG_STATUS)
			{
				PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][6]);
				
				PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][7]);
				PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][8]);
			}
		}
		else if(DutyGroup[playerid] != 0 && MemberGroup[playerid][slot][GroupID] != DutyGroup[playerid])
            return msg_error(playerid,"Aktualnie jesteœ na s³u¿bie w innej grupie.");
		else if(!DutyGroup[playerid])
		{
			if(GroupInfo[groupid][gType] == GROUP_RESTAURANT && (!PlayerDoor[playerid] || !(DoorsInfo[PlayerDoor[playerid]][dOwnerTyp] == OWNER_GROUP && DoorsInfo[PlayerDoor[playerid]][dOwner] == groupid)))
				return msg_error(playerid, "Nie mo¿esz wejœæ na s³u¿be tej grupy, nie bêd¹c w interiorze grupy.");
			
			DutyGroup[playerid] = groupid;
			DutyGroupTime[playerid] = MemberGroup[playerid][slot][GroupTime];
			
			SendClientMessageFormat(playerid, GroupInfo[groupid][gColor], " » Wszed³eœ na s³u¿bê grupy %s (%d). Aby zejœæ ze s³u¿by wpisz /g %d duty.", GroupInfo[groupid][gName], groupid, slot);
			
			if(CharacterInfo[playerid][pTog] & TOG_STATUS)
			{
				PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][6]);
				
				PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][7]);
				PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][8]);
			}
		}
	}
	else if(!strcmp(option, "pojazdy", true) || !strcmp(option, "v", true))
	{
		if(!(MemberGroup[playerid][slot][GroupPerm] & PERM_VEHICLES_MAN))
			return msg_error(playerid,"Nie posiadasz uprawnieñ do zarz¹dzania pojazdami tej grupy.");
		
		new groupid = MemberGroup[playerid][slot][GroupID];
		
		new list[2048];
		
		format(list, sizeof(list), "UID\tModel\tHP\tStan");
		
		ForeachEx(i,_VEH_COUNT)
		{
			if(VehicleInfo[i][vOwnerTyp] == OWNER_GROUP && VehicleInfo[i][vOwner] == groupid)
			{
				if(VehicleInfo[i][vSpawned])
					format(list, sizeof(list), "%s\n%d\t%s\t%0.1f\tZespawnowany", list, i, GetVehicleModelName(VehicleInfo[i][vModel]), VehicleInfo[i][vHP]/10);
				else
					format(list, sizeof(list), "%s\n%d\t%s\t%0.1f\tOdspawnowany", list, i, GetVehicleModelName(VehicleInfo[i][vModel]), VehicleInfo[i][vHP]/10);
			}
		}
		
		if(strlen(list) > 21)
			ShowPlayerDialog(playerid, D_GROUP_VEH_OPTIONS, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » pojazdy grupowe", list, "Opcje", "Zamknij");
		else
			msg_error(playerid,"Grupa nie posiada ¿adnych pojazdów.");
	}
	else if(!strcmp(option, "zaproœ", true) || !strcmp(option, "zapros", true) || !strcmp(option, "zatrudnij", true) || !strcmp(option, "dodaj", true))
	{
		new groupid = MemberGroup[playerid][slot][GroupID];
		new giveplayer_id, string[256];
		if(!(MemberGroup[playerid][slot][GroupPerm] & PERM_PERSONEL))
			return msg_error(playerid, "Nie posiadasz uprawnieñ do zarz¹dzania pracownikami.");
		if(sscanf(varchar, "i", giveplayer_id))
			return msg_usage(playerid,"U¿yj: /g {slot (1-3)} zaproœ [ID gracza]");
		else
		{
			if(!Logged[giveplayer_id])
				return msg_error(playerid,"Gracz o wybranym 'id' nie jest zalogowany.");
			if(IsPlayerInGroup(giveplayer_id, groupid))
				return msg_error(playerid,"Gracz o wybranym 'id' znajduje siê ju¿ w Twojej grupie.");
			if(!HaveFreeSlotGroup(giveplayer_id))
				return msg_error(playerid,"Gracz o wybranym 'id' nie posiada wolnego slotu grupowego.");
			
			new bool:have[2] = false;
			if(IsPlayerGroupPerm(giveplayer_id, FLAG_GPS))
				have[0] = true;
			if(IsPlayerInOfficialGroup(giveplayer_id) || IsPlayerInBuisnessGroup(giveplayer_id))
				have[1] = true;
			
			AddMember(giveplayer_id, groupid, 0);
			
			format(string, sizeof(string), "Zaprosi³eœ gracza %s do grupy %s (UID: %d).\nPamiêtaj o ustawieniu mu odpowiednich uprawnieñ.", PlayerName2(giveplayer_id), GroupInfo[groupid][gName], groupid);
			msg_info(playerid, string);
			
			format(string, sizeof(string), "Zosta³eœ zaproszony do grupy %s (UID: %d) przez gracza %s.\n", GroupInfo[groupid][gName], groupid, PlayerName2(playerid));
			msg_info(giveplayer_id, string);
			
			if(IsPlayerGroupPerm(giveplayer_id, FLAG_GPS) && !have[0])
			{
				if(CharacterInfo[giveplayer_id][pTog] & TOG_STATUS)
				{
					PlayerTextDrawShow(giveplayer_id, TDEditor_PTD[giveplayer_id][0]);
					
					PlayerTextDrawHide(giveplayer_id, TDEditor_PTD[giveplayer_id][1]);
					PlayerTextDrawShow(giveplayer_id, TDEditor_PTD[giveplayer_id][2]);
				}
			}
			
			if(IsPlayerInOfficialGroup(giveplayer_id) || IsPlayerInBuisnessGroup(giveplayer_id) && !have[1])
			{
				if(CharacterInfo[giveplayer_id][pTog] & TOG_STATUS)
				{
					PlayerTextDrawShow(giveplayer_id, TDEditor_PTD[giveplayer_id][6]);
					
					PlayerTextDrawHide(giveplayer_id, TDEditor_PTD[giveplayer_id][7]);
					PlayerTextDrawShow(giveplayer_id, TDEditor_PTD[giveplayer_id][8]);
				}
			}
		}
	}
	else if(!strcmp(option, "wyproœ", true) || !strcmp(option, "wypros", true) || !strcmp(option, "wyrzuc", true))
	{
		new groupid = MemberGroup[playerid][slot][GroupID];
		new giveplayer_id, string[256];
		if(!(MemberGroup[playerid][slot][GroupPerm] & PERM_PERSONEL))
			return msg_error(playerid, "Nie posiadasz uprawnieñ do zarz¹dzania pracownikami.");
		
		if(sscanf(varchar, "i", giveplayer_id))
			return msg_usage(playerid,"U¿yj: /g {slot (1-3)} wyproœ [ID gracza]");
		else
		{
			if(!Logged[giveplayer_id])
				return msg_error(playerid,"Gracz o wybranym 'id' nie jest zalogowany.");
			if(!IsPlayerInGroup(giveplayer_id, groupid))
				return msg_error(playerid,"Gracz o wybranym 'id' nie znajduje siê w Twojej grupie.");
			if(CharacterInfo[giveplayer_id][pAdmin] && CharacterInfo[giveplayer_id][pAdminDuty])
				return msg_error(playerid,"Nie mo¿esz usuwaæ administratorów z grupy!");
			if(GroupInfo[groupid][gLeader] == CharacterInfo[giveplayer_id][pUID])
				return msg_error(playerid,"Nie mo¿esz wyrzuciæ lidera grupy!");
			
			if(CharacterInfo[giveplayer_id][pGPS] && DutyGroup[giveplayer_id] == CharacterInfo[giveplayer_id][pGPS] && DutyGroup[giveplayer_id])
			{
				CharacterInfo[giveplayer_id][pGPS] = 0;
				
				for(new d = 0; d<MAX_WS_MAPICONS; d++)
				{
					if(WS_MAPICONS[giveplayer_id][d] != -1)
						DestroyDynamicMapIcon(WS_MAPICONS[giveplayer_id][d]);
					
					WS_MAPICONS[giveplayer_id][d] = -1;
				}
				
				GameTextForPlayer(giveplayer_id, "~y~~>~ Wylaczyles namierzanie GPS. ~<~", 3000, 3);
				
				if(CharacterInfo[giveplayer_id][pTog] & TOG_STATUS)
				{
					PlayerTextDrawShow(giveplayer_id, TDEditor_PTD[giveplayer_id][0]);
					
					PlayerTextDrawHide(giveplayer_id, TDEditor_PTD[giveplayer_id][1]);
					PlayerTextDrawShow(giveplayer_id, TDEditor_PTD[giveplayer_id][2]);
				}
			}
			
			if(DutyGroup[giveplayer_id])
			{
				for(new i=1;i<MAX_PLAYER_GROUPS;i++)
				{
					if(MemberGroup[giveplayer_id][i][GroupID] == DutyGroup[giveplayer_id])
					{
						new hours, minutes, second,guid;
						guid=DutyGroup[giveplayer_id];
						ConvertSecondsToTime(MemberGroup[giveplayer_id][i][GroupTime], hours, minutes, second);
						SendClientMessageFormat(giveplayer_id, GroupInfo[guid][gColor], " » Zakoñczy³eœ s³u¿bê w grupie %s (%d). Przepracowa³eœ dziœ %dh, %dmin, %dsek.", GroupInfo[guid][gName], guid, hours, minutes, second);
						
						SaveMember(giveplayer_id, guid);
						
						if(IsPlayerPremium(giveplayer_id)) CharacterInfo[giveplayer_id][pNickColor] = COLOR_PREMIUM;
						else CharacterInfo[giveplayer_id][pNickColor] = COLOR_USER;
						
						DutyGroup[giveplayer_id] = 0;
						DutyGroupTime[giveplayer_id] = 0;
						
						if(!(IsPlayerInOfficialGroup(giveplayer_id) || IsPlayerInBuisnessGroup(giveplayer_id)))
						{
							if(CharacterInfo[giveplayer_id][pTog] & TOG_STATUS)
							{
								PlayerTextDrawHide(giveplayer_id, TDEditor_PTD[giveplayer_id][6]);
								
								PlayerTextDrawHide(giveplayer_id, TDEditor_PTD[giveplayer_id][7]);
								PlayerTextDrawHide(giveplayer_id, TDEditor_PTD[giveplayer_id][8]);
							}
						}else if(IsPlayerInOfficialGroup(giveplayer_id) || IsPlayerInBuisnessGroup(giveplayer_id))
						{
							if(CharacterInfo[giveplayer_id][pTog] & TOG_STATUS)
							{
								PlayerTextDrawShow(giveplayer_id, TDEditor_PTD[giveplayer_id][6]);
								
								PlayerTextDrawHide(giveplayer_id, TDEditor_PTD[giveplayer_id][7]);
								PlayerTextDrawShow(giveplayer_id, TDEditor_PTD[giveplayer_id][8]);
							}
						}
						
						break;
					}
				}
			}
			
			DeleteMember(giveplayer_id, groupid);
			
			format(string, sizeof(string), "Wyprosi³eœ gracza %s z grupy %s (UID: %d).\nJego uprawnienia zosta³y zabrane.", PlayerName2(giveplayer_id), GroupInfo[groupid][gName], groupid);
			msg_info(playerid, string);
			
			format(string, sizeof(string), "Zosta³eœ wyproszony z grupy %s (UID: %d) przez gracza %s.\nUprawnienia dotycz¹ce grupy zosta³y zabrane.", GroupInfo[groupid][gName], groupid, PlayerName2(playerid));
			msg_info(giveplayer_id, string);
			
			if(!IsPlayerGroupPerm(playerid, FLAG_GPS))
			{
				if(CharacterInfo[playerid][pTog] & TOG_STATUS)
				{
					PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][0]);
					
					PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][1]);
					PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][2]);
				}
			}
			
			if(!(IsPlayerInOfficialGroup(playerid) || IsPlayerInBuisnessGroup(playerid)))
			{
				if(CharacterInfo[playerid][pTog] & TOG_STATUS)
				{
					PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][6]);
					
					PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][7]);
					PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][8]);
				}
			}
		}
	}
	else if(!strcmp(option, "ranga", true))
	{
		new groupid = MemberGroup[playerid][slot][GroupID];
		new giveplayer_id, rank_id,rank_name[32];
		if(!(MemberGroup[playerid][slot][GroupPerm] & PERM_PERSONEL))
			return msg_error(playerid, "Nie posiadasz uprawnieñ do zarz¹dzania pracownikami.");
		if(sscanf(varchar, "iis[32]", giveplayer_id,rank_id,rank_name))
			return msg_usage(playerid,"U¿yj: /g {slot (1-3)} ranga [ID gracza] [ID rangi] [nazwa rangi]");
		else
		{
			if(!Logged[giveplayer_id])
				return msg_error(playerid,"Gracz o wybranym 'id' nie jest zalogowany.");
			if(!IsPlayerInGroup(giveplayer_id, groupid))
				return msg_error(playerid,"Gracz o wybranym 'id' nie znajduje siê w Twojej grupie.");
			if(rank_id < 0 || rank_id > 255)
				return msg_error(playerid,"Niepoprawne id rangi. (0-255)");
			
			new giveplayer_slot = GetPlayerGroupSlot(giveplayer_id,groupid);
			MemberGroup[giveplayer_id][giveplayer_slot][GroupRank]=rank_id;
			MemberGroup[giveplayer_id][giveplayer_slot][GroupRankName]=rank_name;
			SaveMember(giveplayer_id,MemberGroup[giveplayer_id][giveplayer_slot][GroupID]);
			msg_infoFormat(playerid, 128, "Ranga gracza %s zosta³a zmieniona na %s [%d]", PlayerName3(giveplayer_id),rank_name,rank_id);
			msg_infoFormat(giveplayer_id, 128, "%s zmieni³ twoja rangê w grupie %s na %s [%d].",PlayerName3(playerid),GroupInfo[groupid][gName],rank_name,rank_id);
		}
	}
	else if(!strcmp(option, "pojazdranga", true) || !strcmp(option, "vranga", true))
	{
		new groupid = MemberGroup[playerid][slot][GroupID];
		if(!(MemberGroup[playerid][slot][GroupPerm] & PERM_VEHICLES_MAN))
			return msg_error(playerid,"Nie posiadasz uprawnieñ do zarz¹dzania pojazdami tej grupy.");
		new vehid,rank;
		if(sscanf(varchar, "dd", vehid, rank))
			return msg_usage(playerid,"U¿yj: /g {slot (1-3)} pojazdranga [UID pojazdu] [ID rangi]\n\nRanga 0 umo¿liwia dostêp dla wszystkich pracowników z uprawnieniami do prowadzenia pojazdów.");
		if(!VehicleInfo[vehid][vUID] || !(VehicleInfo[vehid][vOwnerTyp]==OWNER_GROUP && VehicleInfo[vehid][vOwner]==groupid))
			return msg_error(playerid,"Pojazd o wybranym UID nie nale¿y do tej grupy.");
		if(rank<0 || rank > 255)
			return msg_error(playerid,"Podane ID rangi jest nieprawid³owe. Dozwolony zakres 0-255");

		VehicleInfo[vehid][vRank]=rank;
		SaveVehicle(vehid,SAVE_VEH_BASIC);
		msg_infoFormat(playerid, 128, "Ranga pojazdu %s[UID:%d] zosta³a zmieniona na: %d.", GetVehicleModelName(VehicleInfo[vehid][vModel]), vehid, rank);
	}
	else if(!strcmp(option, "opusc", true))
	{
		new groupid = MemberGroup[playerid][slot][GroupID];
		if(!(GroupInfo[groupid][gFlags] & FLAG_OUT) && !CharacterInfo[playerid][pAdmin])
			return msg_error(playerid,"Wybrana grupa nie posiada uprawnieñ do opuszczania jej przez cz³onków.\n");
		
		if(GroupInfo[groupid][gLeader] == CharacterInfo[playerid][pUID] && !CharacterInfo[playerid][pAdmin])
			return msg_error(playerid, "Bêd¹c liderem nie mo¿esz opuœciæ swojej grupy.");
		
		if(CharacterInfo[playerid][pGPS] && DutyGroup[playerid] == CharacterInfo[playerid][pGPS] && DutyGroup[playerid])
		{
			CharacterInfo[playerid][pGPS] = 0;
			
			for(new d = 0; d<MAX_WS_MAPICONS; d++)
			{
				if(WS_MAPICONS[playerid][d] != -1)
					DestroyDynamicMapIcon(WS_MAPICONS[playerid][d]);
				
				WS_MAPICONS[playerid][d] = -1;
			}
			
			GameTextForPlayer(playerid, "~y~~>~ Wylaczyles namierzanie GPS. ~<~", 3000, 3);
			
			if(CharacterInfo[playerid][pTog] & TOG_STATUS)
			{
				PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][0]);
				
				PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][1]);
				PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][2]);
			}
		}
		
		if(DutyGroup[playerid])
		{
			for(new i=1;i<MAX_PLAYER_GROUPS;i++)
			{
				if(MemberGroup[playerid][i][GroupID] == DutyGroup[playerid])
				{
					new hours, minutes, second,guid;
					guid=DutyGroup[playerid];
					ConvertSecondsToTime(MemberGroup[playerid][i][GroupTime], hours, minutes, second);
					SendClientMessageFormat(playerid, GroupInfo[guid][gColor], " » Zakoñczy³eœ s³u¿bê w grupie %s (%d). Przepracowa³eœ dziœ %dh, %dmin, %dsek.", GroupInfo[guid][gName], guid, hours, minutes, second);
					
					SaveMember(playerid, guid);
					
					if(IsPlayerPremium(playerid)) CharacterInfo[playerid][pNickColor] = COLOR_PREMIUM;
					else CharacterInfo[playerid][pNickColor] = COLOR_USER;
					
					DutyGroup[playerid] = 0;
					DutyGroupTime[playerid] = 0;
					
					if(!(IsPlayerInOfficialGroup(playerid) || IsPlayerInBuisnessGroup(playerid)))
					{
						if(CharacterInfo[playerid][pTog] & TOG_STATUS)
						{
							PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][6]);
							
							PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][7]);
							PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][8]);
						}
					}else if(IsPlayerInOfficialGroup(playerid) || IsPlayerInBuisnessGroup(playerid))
					{
						if(CharacterInfo[playerid][pTog] & TOG_STATUS)
						{
							PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][6]);
							
							PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][7]);
							PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][8]);
						}
					}
					
					break;
					
					//ReloadGroupIcons();
				}
			}
		}
		
		DeleteMember(playerid,groupid);
		msg_infoFormat(playerid,64,"Opuœci³eœ grupê %s.",GroupInfo[groupid][gName]);
		
		if(!IsPlayerGroupPerm(playerid, FLAG_GPS))
		{
			if(CharacterInfo[playerid][pTog] & TOG_STATUS)
			{
				PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][0]);
				
				PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][1]);
				PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][2]);
			}
		}
		
		if(!(IsPlayerInOfficialGroup(playerid) || IsPlayerInBuisnessGroup(playerid)))
		{
			if(CharacterInfo[playerid][pTog] & TOG_STATUS)
			{
				PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][6]);
				
				PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][7]);
				PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][8]);
			}
		}
		
		return 1;
	}
	else if(!strcmp(option, "magazyn", true))
	{
		if(!(MemberGroup[playerid][slot][GroupPerm] & PERM_MAGAZINE))
			return msg_error(playerid, "Nie posiadasz dostêpu do magazynu tej grupy!");
		
		new groupid = MemberGroup[playerid][slot][GroupID];
		new doorid=PlayerDoor[playerid];
		if(!doorid || !(DoorsInfo[doorid][dOwner]==groupid && DoorsInfo[doorid][dOwnerTyp]==OWNER_GROUP))
			return msg_error(playerid,"Aby skorzystaæ z magazynu musisz znajdowaæ siê w pomieszczeniu grupy.");
		
		SetPVarInt(playerid, "magguid", groupid);
		
		ShowPlayerDialog(playerid, D_GROUP_MAGAZINE, DIALOG_STYLE_LIST, DEF_NAME" » magazyn grupy", "Wyci¹gnij przedmiot\nW³óŸ przedmiot do magazynu\nPo³¹cz przedmioty w magazynie", "Dalej", "Zamknij");
	}
	else if(!strcmp(option, "spawn", true))
	{
		if(!(MemberGroup[playerid][slot][GroupPerm] & PERM_PERSONEL))
			return msg_error(playerid,"Nie posiadasz uprawnieñ do ustawiania spawnu tej grupy.");
		
		new groupid = MemberGroup[playerid][slot][GroupID];
		
		if(DoorsInfo[PlayerDoor[playerid]][dOwnerTyp] == OWNER_GROUP && DoorsInfo[PlayerDoor[playerid]][dOwner] == groupid)
		{
			GetPlayerPos(playerid, GroupInfo[groupid][gSpawnX], GroupInfo[groupid][gSpawnY], GroupInfo[groupid][gSpawnZ]);
			
			GroupInfo[groupid][gSpawnInt] = GetPlayerInterior(playerid);
			GroupInfo[groupid][gSpawnVW] = GetPlayerVirtualWorld(playerid);
			GetPlayerFacingAngle(playerid, GroupInfo[groupid][gSpawnAngle]);
			
			SaveGroup(groupid, SAVE_GROUP_SPAWN);
			
			msg_info(playerid,"Spawn grupy zosta³ ustawiony w miejscu Twojego po³o¿enia.");
		}
		else
			msg_error(playerid,"Musisz znajdowaæ siê w budynku grupy.");
	}
	else if(!strcmp(option, "wyplac", true) || !strcmp(option, "wyp³aæ", true))
	{
		new groupid = MemberGroup[playerid][slot][GroupID];
		
		if(!( MemberGroup[playerid][slot][GroupPerm] & PERM_CASH))
			return msg_error(playerid," Nie posiadasz uprawnieñ do wyp³acania gotówki.");
		
		new doorid = PlayerDoor[playerid];
		new doorgroupid = DoorsInfo[doorid][dOwner];
		if(!doorid || DoorsInfo[doorid][dOwnerTyp] != OWNER_GROUP || GroupInfo[doorgroupid][gType] != GROUP_BANK)
			return msg_error(playerid, "Nie znajdujesz siê w banku.");
		new money;
		if(sscanf(varchar,"d",money))
			return msg_usage(playerid,"U¿yj: /g {slot (1-3)} wyplac [kwota]");
		if(money < 1)
			return msg_error(playerid, "Nie mo¿esz wyp³aciæ takiej kwoty.");
		else if(GroupInfo[groupid][gCash] < money)
			return msg_error(playerid, "Na koncie grupy nie ma tylu pieniêdzy!");
		
		GroupInfo[groupid][gCash] -= money;
		GivePlayerCash(playerid, money);
		SaveGroup(groupid,SAVE_GROUP_BASIC);
		new string[128];
		format(string,sizeof(string),"[BANK] Pomyœlnie wyp³aci³eœ $%d z konta grupy %s.",money,GroupInfo[groupid][gName]);
		SendClientMessage(playerid, COLOR_GREEN,string);
		format(string,sizeof(string),"INSERT INTO `srv_cash_logs` VALUES ('%d',0,'%d','%d','%d',3,'%d')",groupid, CharacterInfo[playerid][pUID], CharacterInfo[playerid][pGID], money, gettime());
		mysql_query(string);
		LogGroupOffer(playerid, groupid, "Wyplata srodkow z konta", money);
	}
	else if(!strcmp(option, "wplac", true) || !strcmp(option, "wp³aæ", true))
	{
		new groupid = MemberGroup[playerid][slot][GroupID];
		new doorid = PlayerDoor[playerid];
		new doorgroupid = DoorsInfo[doorid][dOwner];
		if(!doorid || DoorsInfo[doorid][dOwnerTyp] != OWNER_GROUP || GroupInfo[doorgroupid][gType] != GROUP_BANK)
			return msg_error(playerid, "Nie znajdujesz siê w banku.");
		new money;
		if(sscanf(varchar,"d",money))
			return msg_usage(playerid,"U¿yj: /g {slot (1-3)} wplac [kwota]");
		
		if(money < 1)
			return msg_error(playerid, "Nie mo¿esz wp³aciæ takiej kwoty.");
		else if(CharacterInfo[playerid][pCash] < money)
			return msg_error(playerid," Nie masz tylu pieniêdzy!");
		
		GroupInfo[groupid][gCash] += money;
		GivePlayerCash(playerid, -money);
		SaveGroup(groupid,SAVE_GROUP_BASIC);
		new string[128];
		format(string,sizeof(string),"[BANK] Pomyœlnie wp³aci³eœ $%d na konto grupy %s.",money,GroupInfo[groupid][gName]);
		SendClientMessage(playerid, COLOR_GREEN, string);
		format(string,sizeof(string),"INSERT INTO `srv_cash_logs` VALUES ('%d','%d','%d',0,'%d',2,'%d')",CharacterInfo[playerid][pUID],CharacterInfo[playerid][pGID],groupid,money,gettime());
		mysql_query(string);
		LogGroupOffer(playerid, groupid, "Wplata srodkow na konto", money);
	}
	else if(!strcmp(option, "uprawnienia", true))
	{
		if(!(MemberGroup[playerid][slot][GroupPerm] & PERM_PERSONEL))
			return msg_error(playerid,"Nie posiadasz uprawnieñ do ustalania uprawnieñ pracowników.");
		new groupid = MemberGroup[playerid][slot][GroupID];
		new giveplayer_id;
		if(sscanf(varchar,"d",giveplayer_id))
			return msg_usage(playerid,"U¿yj: /g {slot (1-3)} uprawnienia [ID pracownika]");
		if(!Logged[giveplayer_id])
			return msg_error(playerid,"Gracz o wybranym 'id' nie jest zalogowany.");
		if(!IsPlayerInGroup(giveplayer_id, groupid))
			return msg_error(playerid,"Gracz o wybranym 'id' nie znajduje siê w Twojej grupie");
		new giveplayer_slot = GetPlayerGroupSlot(giveplayer_id,groupid);
		
		new string[512];
		
		if(MemberGroup[giveplayer_id][giveplayer_slot][GroupPerm] & PERM_PERSONEL) format(string, sizeof(string), "%s\nZarz¹dzanie personelem\t\t{99FF00}TAK", string);
		else format(string, sizeof(string), "%s\nZarz¹dzanie personelem\t\t{990000}NIE", string);

		if(MemberGroup[giveplayer_id][giveplayer_slot][GroupPerm] & PERM_CASH) format(string, sizeof(string), "%s\nZarz¹dzanie finansami\t\t\t{99FF00}TAK", string);
		else format(string, sizeof(string), "%s\nZarz¹dzanie finansami\t\t\t{990000}NIE", string);

		if(MemberGroup[giveplayer_id][giveplayer_slot][GroupPerm] & PERM_VEHICLES) format(string, sizeof(string), "%s\nDostêp do pojazdów\t\t\t{99FF00}TAK", string);
		else format(string, sizeof(string), "%s\nDostêp do pojazdów\t\t\t{990000}NIE", string);

		if(MemberGroup[giveplayer_id][giveplayer_slot][GroupPerm] & PERM_VEHICLES_MAN) format(string, sizeof(string), "%s\nZarz¹dzanie pojazdami\t\t\t{99FF00}TAK", string);
		else format(string, sizeof(string), "%s\nZarz¹dzanie pojazdami\t\t\t{990000}NIE", string);

		if(MemberGroup[giveplayer_id][giveplayer_slot][GroupPerm] & PERM_DOOR) format(string, sizeof(string), "%s\nZarz¹dzanie drzwiami\t\t\t{99FF00}TAK", string);
		else format(string, sizeof(string), "%s\nZarz¹dzanie drzwiami\t\t\t{990000}NIE", string);

		if(MemberGroup[giveplayer_id][giveplayer_slot][GroupPerm] & PERM_OBJECT) format(string, sizeof(string), "%s\nZarz¹dzanie obiektami\t\t\t{99FF00}TAK", string);
		else format(string, sizeof(string), "%s\nZarz¹dzanie obiektami\t\t\t{990000}NIE", string);

		if(MemberGroup[giveplayer_id][giveplayer_slot][GroupPerm] & PERM_MAGAZINE) format(string, sizeof(string), "%s\nDostêp do magazynu\t\t\t{99FF00}TAK", string);
		else format(string, sizeof(string), "%s\nDostêp do magazynu{990000}\t\t\tNIE", string);

		if(MemberGroup[giveplayer_id][giveplayer_slot][GroupPerm] & PERM_PRODUCT) format(string, sizeof(string), "%s\nZarz¹dzanie produktami\t\t{99FF00}TAK", string);
		else format(string, sizeof(string), "%s\nZarz¹dzanie produktami\t\t{990000}NIE", string);
		
		if(MemberGroup[giveplayer_id][giveplayer_slot][GroupPerm] & PERM_SPECIAL_LEADER) format(string, sizeof(string), "%s\nUprawnienia lidera\t\t\t{99FF00}TAK", string);
		else format(string, sizeof(string), "%s\nUprawnienia lidera\t\t\t{990000}NIE", string);
		
		if(GroupInfo[groupid][gType] == GROUP_PD)
		{
			if(MemberGroup[giveplayer_id][giveplayer_slot][GroupPerm] & PERM_EXTRA) format(string, sizeof(string), "%s\nZdejmowanie blokad z pojazdów\t{99FF00}TAK", string);
			else format(string, sizeof(string), "%s\nZdejmowanie blokad z pojazdów\t{990000}NIE", string);
		}

		SetPVarInt(playerid,"GroupPermGiveplayer",giveplayer_id);
		SetPVarInt(playerid,"GroupPermGiveplayerSlot",giveplayer_slot);
		SetPVarInt(playerid,"GroupPermPlayerSlot",slot);

		new header[64];
		format(header,sizeof(header),DEF_NAME" » %s", PlayerName3(giveplayer_id));

		ShowPlayerDialog(playerid, D_GROUP_CHANGE_PERM, DIALOG_STYLE_LIST, header, string, "Zmieñ", "Zamknij");
	}
	else if(!strcmp(option, "wyplata", true) || !strcmp(option, "wyp³ata", true))	
	{
		if(!(MemberGroup[playerid][slot][GroupPerm] & PERM_PERSONEL))
			return msg_error(playerid,"Nie posiadasz uprawnieñ do zarz¹dzania pracownikami.");
		new giveplayer_id, salary;
		if(sscanf(varchar,"dd",giveplayer_id,salary))
			return msg_usage(playerid,"U¿yj: /g {slot (1-3)} wyplata [ID pracownika] [kwota]");
		new groupid = MemberGroup[playerid][slot][GroupID];
		if(!Logged[giveplayer_id])
			return msg_error(playerid,"Gracz o wybranym 'id' nie jest zalogowany.");
		if(!IsPlayerInGroup(giveplayer_id, groupid))
			return msg_error(playerid,"Gracz o wybranym 'id' nie znajduje siê w Twojej grupie");
		if(salary < 0 || salary > 1500)
			return msg_error(playerid,"Niepoprawna kwota wyp³aty. (0-1500)");

		new giveplayer_slot = GetPlayerGroupSlot(giveplayer_id,groupid);
		MemberGroup[giveplayer_id][giveplayer_slot][GroupSalary]=salary;
		SaveMember(giveplayer_id,groupid);
		
		msg_infoFormat(playerid, 128, "Ustawi³eœ pensjê pracownika %s(%d) na $%d.", PlayerName3(giveplayer_id), giveplayer_id,salary);
		msg_infoFormat(giveplayer_id, 128, "Lider grupy %s ustali³ Twoj¹ wyp³atê na $%d.", GroupInfo[groupid][gName], salary);
	}
	else if(!strcmp(option, "prowizja", true))
	{
		if(!(MemberGroup[playerid][slot][GroupPerm] & PERM_PERSONEL))
			return msg_error(playerid,"Nie posiadasz uprawnieñ do zarz¹dzania pracownikami.");
		new groupid = MemberGroup[playerid][slot][GroupID];
		if(IsCriminalGroup(groupid))
			return 1;
		new giveplayer_id,commission;
		if(sscanf(varchar,"dd",giveplayer_id,commission))
			return msg_usage(playerid,"U¿yj: /g {slot (1-3)} prowizja [ID pracownika] [prowizja]");
		if(!Logged[giveplayer_id])
			return msg_error(playerid,"Gracz o wybranym 'id' nie jest zalogowany.");
		if(!IsPlayerInGroup(giveplayer_id, groupid))
			return msg_error(playerid,"Gracz o wybranym 'id' nie znajduje siê w Twojej grupie.");
		
		if(GroupInfo[groupid][gType] != GROUP_LOGISTIC && (commission < 0 || commission > 90))
			return msg_error(playerid,"Niepoprawna wartoœæ prowizji. Dozwolone 0-90%");
		else if(commission < 30 || commission > 90)
			return msg_error(playerid,"Niepoprawna wartoœæ prowizji. Dozwolone 30-90%");

		new giveplayer_slot = GetPlayerGroupSlot(giveplayer_id,groupid);
		MemberGroup[giveplayer_id][giveplayer_slot][GroupCommission]=commission;
		SaveMember(giveplayer_id,groupid);
		
		msg_infoFormat(playerid, 128, "Ustawi³eœ prowizjê w wysokoœci %d%% dla %s(%d).", commission, PlayerName3(giveplayer_id),giveplayer_id);
		msg_infoFormat(giveplayer_id, 128, "Twoja prowizja w grupie %s zosta³a ustawiona na %d%%.", GroupInfo[groupid][gName],commission);
	}
	else if(!strcmp(option, "skin", true))
	{
		if(!(MemberGroup[playerid][slot][GroupPerm] & PERM_PERSONEL))
			return msg_error(playerid,"Nie posiadasz uprawnieñ do ustalania skinów pracowników.");
		
		new groupid = MemberGroup[playerid][slot][GroupID];
		new giveplayer_id, skin;
		if(sscanf(varchar,"dd",giveplayer_id,skin))
			return msg_usage(playerid,"U¿yj: /g {slot (1-3)} skin [ID pracownika] [ID skina]");
		if(!Logged[giveplayer_id])
			return msg_error(playerid,"Gracz o wybranym 'id' nie jest zalogowany.");
		if(!IsPlayerInGroup(giveplayer_id, groupid))
			return msg_error(playerid,"Gracz o wybranym 'id' nie znajduje siê w Twojej grupie");
		if(skin<1 || skin>311 || skin==74)
			return msg_error(playerid,"Niepoprawne id skina");
		
		if(!(GroupInfo[groupid][gType] == GROUP_PD || GroupInfo[groupid][gType] == GROUP_MC || GroupInfo[groupid][gType] == GROUP_FBI || GroupInfo[groupid][gType] == GROUP_MILITARY))
			if(264 < skin < 268 || 273 < skin < 287 || skin == 288 || 299 < skin < 312)
				return msg_error(playerid, "Nie mo¿na ustawiæ tego skina (tylko dla publicznych).");
		
		new giveplayer_slot = GetPlayerGroupSlot(giveplayer_id,groupid);
		MemberGroup[giveplayer_id][giveplayer_slot][GroupSkin]=skin;
		SaveMember(giveplayer_id,groupid);
		
		msg_infoFormat(playerid, 128, "Ustawi³eœ skin grupowy (%d) dla gracza o ID: %d.", skin, giveplayer_id);
		msg_infoFormat(giveplayer_id, 128, "Zosta³ ci ustawiony grupowy roboczy (%d) w grupie (UID: %d).", skin, groupid);
		
		return 1;
	}
	else if(!strcmp(option, "uskin", true))
	{
		if(!(MemberGroup[playerid][slot][GroupPerm] & PERM_PERSONEL))
			return msg_error(playerid,"Nie posiadasz uprawnieñ do ustalania skinów pracowników.");
		
		new groupid = MemberGroup[playerid][slot][GroupID];
		new giveplayer_id;
		if(sscanf(varchar,"d",giveplayer_id))
			return msg_usage(playerid,"U¿yj: /g {slot (1-3)} uskin [ID pracownika]");
		if(!Logged[giveplayer_id])
			return msg_error(playerid,"Gracz o wybranym 'id' nie jest zalogowany.");
		if(!IsPlayerInGroup(giveplayer_id, groupid))
			return msg_error(playerid,"Gracz o wybranym 'id' nie znajduje siê w Twojej grupie");
		
		new list[1024];
		format(list, sizeof(list), "ID\tModel ID");
		
		ForeachEx(i, MAX_SKINS)
		{
			if(SkinInfo[i][sID] && SkinInfo[i][sType] == SKIN_TYPE_GROUP && SkinInfo[i][sUID] == groupid)
				format(list, sizeof(list), "%s\n%d\t%d", list, SkinInfo[i][sID], SkinInfo[i][sModel]);
		}
		
		new giveplayer_slot = GetPlayerGroupSlot(giveplayer_id,groupid);
		SetPVarInt(playerid, "giveplayer_slot", giveplayer_slot);
		SetPVarInt(playerid, "giveplayer_id", giveplayer_id);
		SetPVarInt(playerid, "groupid", groupid);
		
		if(strlen(list) > 12) ShowPlayerDialog(playerid, D_SKIN_CHANGE_GROUP, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » dostêpne skiny", list, "U¿yj", "Anuluj");
		else Tip(playerid, 3, "Nie masz dostêpu do unikalnego skina.");
		
		return 1;
	}
	else if(!strcmp(option, "kolor", true))
	{
		if(GroupInfo[MemberGroup[playerid][slot][GroupID]][gLeader] != CharacterInfo[playerid][pUID])
			return msg_error(playerid,"Tylko lider mo¿e zmieniaæ kolor grupy.");
		new color[8];
		if(sscanf(varchar,"s[8]",color))
			return msg_usage(playerid,"U¿yj: /g {slot (1-3)} kolor [RRGGBB]");
		if(strlen(color)!=6)
			return msg_error(playerid,"Niepoprawna wartoœæ koloru.");

		for(new i=0;i<6;i++)
		{
			color[i]=toupper(color[i]);
			if(color[i]< '0' || (color[i]>'9' && color[i] < 'A') || color[i] > 'F')
				return msg_error(playerid,"Niepoprawna wartoœæ koloru.");
			if(color[i]>60)
  				color[i]-=55;
  			else
  				color[i]-=48;
		}
		
		new rgba = color[0] * 268435456 + color[1] * 16777216 + color[2] * 1048576 + color[3] *65536 + color[4] * 4096 + color[5] * 256 + 255;
		new groupid = MemberGroup[playerid][slot][GroupID];
		GroupInfo[groupid][gColor]=rgba;
		SaveGroup(groupid,SAVE_GROUP_BASIC);
		msg_infoFormat(playerid, 64, "Ustawi³eœ nowy kolor grupy %s.",GroupInfo[groupid][gName]);

		return 1;
	}
	else if(!strcmp(option, "ogloszenie", true))
	{
		if(!(MemberGroup[playerid][slot][GroupPerm] & PERM_PERSONEL))
			return msg_error(playerid,"Nie posiadasz uprawnieñ do og³oszenia grupy.");
		
		new ogloszenie[64];
		if(sscanf(varchar, "s[64]", ogloszenie))
			return msg_usage(playerid,"U¿yj: /g {slot (1-3)} ogloszenie [tekst]");
		else
		{
			new groupid = MemberGroup[playerid][slot][GroupID];
			if(strfind(ogloszenie,"|") != -1)
				return msg_error(playerid,"Og³oszenie zawiera niedozwolony znak: \"|\"");
			
			new query[256];
			mysql_real_escape_string(ogloszenie,ogloszenie);
			format(query, sizeof(query), "UPDATE `srv_groups` SET `notice`='%s' WHERE `UID`='%d' LIMIT 1", ogloszenie, groupid);
			mysql_query(query);
			
			GroupInfo[groupid][gNotice] = ogloszenie;
			
			if(strcmp(ogloszenie, "0", true))
				ForeachPlayer(i)
			{
					if(IsPlayerInGroup(i, groupid))
						SendClientMessageFormat(i, GetGroupColor(groupid), "[GRUPA][%s] Og³oszenie: %s", GroupInfo[groupid][gTag], ogloszenie);
			}
			else
				msg_info(playerid, "Usun¹³eœ og³oszenie grupy.");
		}
	}
	else if(!strcmp(option, "respawn", true))
	{
		if(!(MemberGroup[playerid][slot][GroupPerm] & PERM_PERSONEL))
			return msg_error(playerid,"Nie posiadasz uprawnieñ do respawny w grupie.");
		
		ForeachEx(uid, _VEH_COUNT)
		{
			if(VehicleInfo[uid][vSpawned] && !IsVehicleOccupied(VehicleInfo[uid][vSAMPID]) && VehicleInfo[uid][vOwnerTyp] == OWNER_GROUP && VehicleInfo[uid][vOwner] == MemberGroup[playerid][slot][GroupID])
			{
				UnspawnVehicle(uid);
				LoadVehicle(uid);
			}
		}
		msg_info(playerid, "Wykona³eœ respawn pojazdów grupowych.");
	}
	else if(!strcmp(option, "ooc", true))
	{
		if(!(MemberGroup[playerid][slot][GroupPerm] & PERM_PERSONEL))
			return msg_error(playerid,"Nie posiadasz uprawnieñ do wy³¹czenia/w³¹czenia OOC.");
		
		if(!GroupInfo[MemberGroup[playerid][slot][GroupID]][gOOCBlock])
		{
			GroupInfo[MemberGroup[playerid][slot][GroupID]][gOOCBlock] = 1;
			msg_info(playerid, "Wy³¹czy³eœ czat OOC w grupie.");
		}
		else
		{
			GroupInfo[MemberGroup[playerid][slot][GroupID]][gOOCBlock] = 0;
			msg_info(playerid, "W³¹czy³eœ czat OOC w grupie.");
		}
	}

 	return 1;
}
CMD:g(playerid,params[]) return cmd_grupa(playerid,params);

CMD:reanimuj(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!IsPlayerOnDutyInGroup(playerid, GROUP_MC))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
	
	new playerid2;
	if(sscanf(params, "i", playerid2))
		return msg_usage(playerid,"U¿yj: /reanimuj [ID gracza]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		if(!PlayerToPlayer(5.0, playerid, playerid2))
			return msg_error(playerid,"Znajdujesz siê zbyt daleko od gracza.");
		if(!CharacterInfo[playerid2][pBW] || CharacterInfo[playerid2][pWounded])
			return msg_error(playerid,"Gracz nie jest w stanie nieprzytomnoœci.");
		if(!CanMove(playerid))
			return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
		if(playerid == playerid2)
			return msg_error(playerid,"Nie mo¿esz zreanimowaæ samego siebie.");
		
		GameTextForPlayer(playerid,"~g~Trwa reanimacja...",10000,4);
		GameTextForPlayer(playerid2,"~g~Trwa reanimacja...",10000,4);
		CharacterInfo[playerid2][pReanimation] = 10;
		CharacterInfo[playerid2][pReanimationID] = playerid;
	}
	
	return 1;
}

CMD:d(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	new groupid = DutyGroup[playerid];
	if(!groupid || !(GroupInfo[groupid][gFlags] & FLAG_DEPARTMENT))
		return msg_error(playerid, "Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
	if(!PlayerHaveItemType(playerid, ITEM_TYPE_RADIO))
		return msg_error(playerid,"Nie posiadasz krótkofalówki.");
	if(!CanMove(playerid) || !CanSpeak(playerid))
		return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");

	new text[145];
	if(sscanf(params, "s[145]", text))
		return msg_usage(playerid,"U¿yj: /d [tekst]");
	else
	{
		new str[170],tmp,string1[144],text2[96];
		format(str, sizeof(str), "%s (radio): %s", PlayerName2(playerid), text);
		text[0] = chrtoupper(text[0]);
		new slot=GetPlayerGroupSlot(playerid,groupid);
		new rankname[32];
		if(strlen(MemberGroup[playerid][slot][GroupRankName]))
			format(rankname,sizeof(rankname),"%s ",MemberGroup[playerid][slot][GroupRankName]);
		
		if(strlen(text) > 76)
		{
			tmp=1;
			new pos = strfind(text, " ", true, strlen(text) / 2);
			if(pos != -1)
			{
				strmid(text2, text, pos + 1, strlen(text));
				strdel(text, pos, strlen(text));
			}
			format(string1,sizeof(string1),"** [%s] %s%s(%d): %s ...", GroupInfo[groupid][gTag], rankname,PlayerName2(playerid), playerid, text);
			strins(text2, "...", 0);
		}
		else
			format(string1,sizeof(string1),"** [%s] %s%s(%d): %s", GroupInfo[groupid][gTag], rankname,PlayerName2(playerid), playerid, text);
		
		ForeachPlayer(i)
		{
			if(IsPlayerGroupPerm(i, FLAG_DEPARTMENT) && PlayerHaveItemType(i, ITEM_TYPE_RADIO))
			{
				if(!tmp)
				{
					SendClientMessage(i, 0xCC666AA, string1);
					playerLog(i,"DEPT",string1);
				}
				else
				{
					SendClientMessage(i, 0xCC666AA, string1);
					playerLog(i,"DEPT",string1);
					SendClientMessage(i, 0xCC666AA, text2);		
					playerLog(i,"DEPT",text2);
				}
			}
		}
		
		SendWrappedMessageToPlayerRange(playerid, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, str, 10, false, true);
	}
	
	return 1;
}

CMD:zbadaj(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!IsPlayerOnDutyInGroup(playerid, GROUP_MC) && !IsPlayerOnDutyInGroup(playerid, GROUP_PD) && !IsPlayerOnDutyInGroup(playerid, GROUP_MILITARY))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
	
	new playerid2;
	if(sscanf(params, "i", playerid2))
		return msg_usage(playerid,"U¿yj: /zbadaj [ID gracza]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		if(!PlayerToPlayer(5.0, playerid, playerid2))
			return msg_error(playerid,"Znajdujesz siê zbyt daleko od gracza.");
		if(!CanMove(playerid))
			return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
		
		new string[512];
		
		format(string, sizeof(string), "Badany:\t\t\t%s\n\n", PlayerName2(playerid2));
		
		if(CharacterInfo[playerid2][pDrugs] && (CharacterInfo[playerid2][pDrugs])<5) format(string, sizeof(string), "%sNaæpany:\t\t\tTak", string);
		else format(string, sizeof(string), "%sNaæpany:\t\t\tNie", string);
		
		if(CharacterInfo[playerid][pDrugs] == 6)
			format(string, sizeof(string), "%s\nNietrzeŸwoœæ:\t\t\tTak", string);
		else
			format(string, sizeof(string), "%s\nNietrzeŸwoœæ:\t\t\tNie", string);
		
		msg_info(playerid,string);
	}
	
	return 1;
}

CMD:przeszukaj(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!IsPlayerOnDutyInGroup(playerid, GROUP_PD) && !IsPlayerOnDutyInGroup(playerid, GROUP_FBI) && !IsPlayerOnDutyInGroup(playerid, GROUP_GOV) && !IsPlayerOnDutyInGroup(playerid, GROUP_MILITARY) && !IsPlayerInCriminalGroup(playerid))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");

	new type[32], comm2[32];
	if(sscanf(params, "s[32]S()[32]", type, comm2))
		return msg_usage(playerid,"U¿yj: /przeszukaj [gracz, pojazd]");
	else if(!strcmp(type, "gracz", true))
	{
		new playerid2;
		if(sscanf(comm2, "i", playerid2))
			return msg_usage(playerid,"U¿yj: /przeszukaj gracz [ID gracza]");
		else
		{
			if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
				return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
			if(!PlayerToPlayer(5.0, playerid, playerid2))
				return msg_error(playerid,"Znajdujesz siê zbyt daleko od gracza.");
			if(playerid == playerid2)
				return msg_error(playerid,"Nie mo¿esz przeszukaæ samego siebie.");
			if(!CanMove(playerid))
				return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
			
			new string[64];
			format(string, sizeof(string), "przeszukuje %s.", PlayerName2(playerid2));
			cmd_me(playerid, string);
			GameTextForPlayer(playerid, "~g~Trwa przeszukanie", 5000, 4);
			SetTimerEx("ListPlayerItemsForPlayer",5000,false,"ii",playerid,playerid2);
			SendClientMessageFormat(playerid, COLOR_GREEN, "Gracz ma przy sobie: $%d.", CharacterInfo[playerid2][pCash]);
		}
	}
	else if(!strcmp(type, "pojazd", true))
	{
		new vehid = GetClosestVehicle(playerid);
		
		if(!vehid || vehid==INVALID_VEHICLE_ID) return 1;
		if(VehicleInfo[GetVehicleUID(vehid)][vLocked])
			return msg_error(playerid,"Wybrany pojazd jest zamkniêty.");
		
		SetPVarInt(playerid, "przeszukajid", vehid);
		
		ShowPlayerDialog(playerid, D_PRZESZUKAJ, DIALOG_STYLE_LIST, DEF_NAME" » przeszukiwanie", "1. Pojazd\n2. Baga¿nik", "Wybierz", "Zamknij");
	}
	
	return 1;
}

CMD:przetrzymanie(playerid, params[])
{
	if(!CanMove(playerid))
		return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
	
	new playerid2, time;
	if(sscanf(params, "id", playerid2, time))
		return msg_usage(playerid,"U¿yj: /przetrzymanie [ID gracza] [czas w godzinach (max 72)]");
	else
	{
		new dooruid = GetClosestDoor(playerid);
		
		if(!dooruid)
			return msg_error(playerid,"Nie znajdujesz siê przy wejœciu do celi.");
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		if(!PlayerToPlayer(5.0, playerid, playerid2))
			return msg_error(playerid,"Znajdujesz siê zbyt daleko od gracza.");
		if(time > 72 || time < 1)
			return msg_error(playerid,"Czas przetrzymania nie jest poprawny (1-72).");
		if(CharacterInfo[playerid2][pJailTime] > gettime())
			return msg_error(playerid,"Wybrany gracz jest ju¿ przetrzymywany.");
		
		new groupid = 0;
		for(new i=1; i<MAX_PLAYER_GROUPS; i++)
		{
			if(MemberGroup[playerid][i][GroupID] && GroupInfo[MemberGroup[playerid][i][GroupID]][gFlags] & FLAG_JAIL)
			{
				if(DoorsInfo[dooruid][dOwnerTyp] == OWNER_JAIL && DoorsInfo[dooruid][dOwner] == MemberGroup[playerid][i][GroupID])
				{
					groupid = MemberGroup[playerid][i][GroupID];
					break;
				}
			}
		}
		
		if(!groupid)
			return msg_error(playerid,"Nie znajdujesz siê przy wejœciu do celi (aresztu, odpowiedniego pomieszczenia) lub nie masz uprawnieñ do u¿ycia tej komendy.");
		
		CharacterInfo[playerid2][pJail] = dooruid;
		CharacterInfo[playerid2][pJailTime] = gettime()+(60*60*time);
		
		SavePlayerStats(playerid2, SAVE_PLAYER_JAIL);
		
		PlayerEnterDoor(playerid2, dooruid);
		
		LogJail(playerid, playerid2, time, groupid, 1);
		
		if(GroupInfo[groupid][gType] == GROUP_PD || GroupInfo[groupid][gType] == GROUP_FBI)
		{
			mysql_query_format("SELECT * FROM `srv_mostwanted` WHERE `player_uid` = '%d' LIMIT 1", CharacterInfo[playerid2][pUID]);
			mysql_store_result();
			
			if(mysql_num_rows())
				mysql_query_format("DELETE FROM `srv_mostwanted` WHERE `player_uid` = '%d' LIMIT 1", CharacterInfo[playerid2][pUID]);
			
			mysql_free_result();
		}
		
		SendClientMessageFormat(playerid, COLOR_RED, "[PRZETRZYMANIE] %s (ID: %d) - %d godzin [OOC].", PlayerName2(playerid2), playerid2, time);
		msg_infoFormat(playerid2, 128, "Jesteœ od teraz przetrzymywany.\n\nPrzez: %s (ID: %d)\nD³ugoœæ: %d godzin [OOC].", PlayerName2(playerid), playerid, time);
	}
	
	return 1;
}

CMD:wypusc(playerid, params[])
{
	if(!CanMove(playerid))
		return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
	
	new playerid2;
	if(sscanf(params, "i", playerid2))
		return msg_usage(playerid,"U¿yj: /wypusc [ID gracza]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Gracz o podanym ID nie jest zalogowany.");
		if(!PlayerToPlayer(5.0, playerid, playerid2))
			return msg_error(playerid,"Znajdujesz siê zbyt daleko od gracza.");
		if(CharacterInfo[playerid2][pJailTime] <= gettime())
			return msg_error(playerid,"Wybrany gracz nie jest przetrzymywany.");
		
		new dooruid = CharacterInfo[playerid2][pJail];
		
		if(CharacterInfo[playerid][pAdmin] < 2)
		{
			new groupid = 0;
			for(new i=1; i<MAX_PLAYER_GROUPS; i++)
			{
				if(MemberGroup[playerid][i][GroupID] && GroupInfo[MemberGroup[playerid][i][GroupID]][gFlags] & FLAG_JAIL)
				{
					if(DoorsInfo[dooruid][dOwnerTyp] == OWNER_JAIL && DoorsInfo[dooruid][dOwner] == MemberGroup[playerid][i][GroupID])
					{
						groupid = MemberGroup[playerid][i][GroupID];
						break;
					}
				}
			}
			
			if(!groupid)
				return msg_error(playerid,"Nie znajdujesz siê przy wejœciu do celi (aresztu, odpowiedniego pomieszczenia) lub nie masz uprawnieñ do u¿ycia tej komendy.");
		}
		
		SetPlayerPos(playerid2, DoorsInfo[dooruid][dEnterX], DoorsInfo[dooruid][dEnterY], DoorsInfo[dooruid][dEnterZ]);
		SetPlayerVirtualWorld(playerid, DoorsInfo[dooruid][dEnterVW]);
		
		LogJail(playerid, playerid2, 0, DoorsInfo[CharacterInfo[playerid2][pJail]][dOwner], 2);
		
		CharacterInfo[playerid2][pJail] = 0;
		CharacterInfo[playerid2][pJailTime] = 0;
		
		SavePlayerStats(playerid2, SAVE_PLAYER_JAIL);
		
		msg_infoFormat(playerid, 128, "Wypuœci³eœ gracza %s (ID: %d).", PlayerName2(playerid2), playerid2);
		msg_infoFormat(playerid, 128, "Zosta³eœ wypuszczony przez gracza %s (ID: %d).", PlayerName2(playerid), playerid);
		
		SendAdminMessageFormat(COLOR_RED, "[PRZETRZYMANIE] Gracz %s zostal wypuszczony przez %s.", PlayerName3(playerid2), PlayerName3(playerid));
	}
	
	return 1;
}

CMD:paczka(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!IsPlayerOnDutyInGroup(playerid, GROUP_LOGISTIC))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");

	if(GetPVarInt(playerid,"Transport") || GetPVarInt(playerid,"TransportFuel"))
		return msg_error(playerid,"Aktualnie wykonujesz inne zlecenie.");
	
	if(IsPlayerInRangeOfPoint(playerid, 30.0, SettingInfo[sMagazineX], SettingInfo[sMagazineY], SettingInfo[sMagazineZ]))
	{
		if(GetPVarInt(playerid,"pPackage"))
		{
			new doorid = GetPVarInt(playerid,"pPackageDoor");
			SetPlayerCheckpoint(playerid, DoorsInfo[doorid][dEnterX], DoorsInfo[doorid][dEnterY], DoorsInfo[doorid][dEnterZ], 5.0);
			return msg_error(playerid,"Nie znajdujesz siê w drzwiach dostarczenia paczki.\nPunkt zosta³ ukazany Ci na mapie.");
		}
		new data[32], list[2048], uid, doorid;
		
		mysql_query("SELECT `uid`, `door_uid` FROM `srv_orders` WHERE `status` = 0 AND `driver` = 0");
		mysql_store_result();
		
		format(list, sizeof(list), "UID\tNAZWA GRUPY");
		
		while(mysql_fetch_row_format(data, "|"))
		{
			sscanf(data, "p<|>dd", uid, doorid);
			
			format(list, sizeof(list), "%s\n%d\t%s", list, uid, GroupInfo[DoorsInfo[doorid][dOwner]][gName]);
		}
		
		mysql_free_result();
		
		if(strlen(list) > 17) ShowPlayerDialog(playerid, D_LOGISTIC_ORDERS, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » lista paczek", list, "Wybierz", "Zamknij");
		else msg_info(playerid, "Brak paczek na magazynie.");
	}
	else
	{
		if(GetPVarInt(playerid,"pPackage") && !GetPVarInt(playerid,"Transport")) // && !Sweeper[playerid] && !Transport[playerid] && !Newspaper[playerid])
		{
			new doorid = GetPVarInt(playerid,"pPackageDoor");
			new pack_id = GetPVarInt(playerid,"pPackageID");
			
			if(!IsPlayerInRangeOfPoint(playerid, 5.0, DoorsInfo[doorid][dEnterX], DoorsInfo[doorid][dEnterY], DoorsInfo[doorid][dEnterZ]))
			{
				SetPlayerCheckpoint(playerid, DoorsInfo[doorid][dEnterX], DoorsInfo[doorid][dEnterY], DoorsInfo[doorid][dEnterZ], 5.0);
				
				return msg_error(playerid,"Nie znajdujesz siê w drzwiach dostarczenia paczki.\nPunkt zosta³ ukazany Ci na mapie.");
			}
			
			new data[64], value1, value2, name[32], value, kind,shippment;
			new query[256];
			format(query, sizeof(query), "SELECT `value1`, `value2`, `name`, `count`, `kind`, `shippment_cost` FROM `srv_orders` WHERE `uid` = '%d' AND `driver` = '%d'", pack_id, CharacterInfo[playerid][pUID]);
			mysql_query(query);
			
			mysql_store_result();
			
			while(mysql_fetch_row_format(data,"|")==1)
				sscanf(data, "p<|>dds[32]ddd", value1, value2, name, value, kind, shippment);
			
			mysql_free_result();
			
			StworzPrzedmiot(OWNER_GROUP, DoorsInfo[doorid][dOwner], name, kind, value1, value2, value);
			format(query, sizeof(query), "UPDATE `srv_orders` SET `status` = 1 WHERE `uid` = '%d'", pack_id);
			mysql_query(query);
			
			DisablePlayerCheckpoint(playerid);
			
			new groupid=GetPVarInt(playerid,"pPackegeCourierGroup");
			new commission=GetMemberCommission(playerid,groupid);
			if(commission > 0)
			{
				commission= floatround( (float(shippment)/100.0) * float(commission));
				shippment-=commission;
				CharacterInfo[playerid][pCredit] += commission;
				SavePlayerStats(playerid,SAVE_PLAYER_BASIC);
				SendClientMessageFormat(playerid, COLOR_GREEN, "Paczka dostarczona. Na konto grupy wp³ynie %d$. Twoja prowizja: $%d.", shippment,commission);
			}
			else
				SendClientMessageFormat(playerid, COLOR_GREEN, "Paczka dostarczona. Na konto grupy wp³ynie %d$", shippment);
			
			GiveGroupCash(groupid,shippment);
			
			DeletePVar(playerid,"pPackageID");
			DeletePVar(playerid,"pPackageDoor");
			DeletePVar(playerid,"pPackage");
			
			msg_info(playerid,"Paczka zosta³a pomyœlnie dostarczona.");
			LogGroupOffer(playerid,groupid,"Dostawa paczki",shippment);
			
			ForeachPlayer(i)
			{
				if(IsPlayerOnDutyInCertGroup(i, DoorsInfo[doorid][dOwner]) && !(CharacterInfo[i][pStatus] & STATUS_AFK))
				{
					SendClientMessage(i, COLOR_YELLOW, "Firma logistyczna w³aœnie dostarczy³a zamówienie do twojej grupy.");
				}
			}
		}
		else
		{
			SetPlayerMapIcon(playerid, 1, SettingInfo[sMagazineX], SettingInfo[sMagazineY], SettingInfo[sMagazineZ], 51, 0, MAPICON_GLOBAL);
			return msg_error(playerid, "Nie znajdujesz siê na terenie magazynu.\nMiejsce magazynu ukazane jest na mapie za pomoc¹ ikony.");
		}
	}
	
	return 1;
}
CMD:transport(playerid,params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!IsPlayerOnDutyInGroup(playerid, GROUP_LOGISTIC))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
	if(GetPVarInt(playerid,"Transport") || GetPVarInt(playerid,"pPackage") || GetPVarInt(playerid,"TransportFuel"))
		return msg_error(playerid,"Aktualnie wykonujesz inne zlecenie.");
	
	new comm1[8];
	if(sscanf(params,"s[8]",comm1))
		return msg_usage(playerid,"U¿yj: /transport [towar | paliwo]");
	if(!strcmp(comm1,"towar", true))
	{
		if(GroupInfo[DutyGroup[playerid]][gTransportTowary] < 1)
			return msg_error(playerid,"Brak towaru do transportu");
		new model=GetVehicleModel(GetPlayerVehicleID(playerid));
		new trailer=GetVehicleModel(GetVehicleTrailer(GetPlayerVehicleID(playerid)));
		if(!(model==514 || model==515 || model==403) && !(trailer==435 || trailer == 591 || trailer==450))
			return msg_error(playerid,"Aby skorzystac z tej komendy musisz znajdowac siê w trucku z podczepiona naczep¹.");
		SetPVarInt(playerid, "Transport", 1);
		SetPVarInt(playerid, "TransportGroup", DutyGroup[playerid]);
		msg_info(playerid, "Udaj siê w miejsce oznaczone na mapie i odbierz towar, nastepnie przywieŸ go do magazynu.");
		new rand=random(15);
		SetPlayerCheckpoint(playerid,TransportCP[rand][TransportX],TransportCP[rand][TransportY],TransportCP[rand][TransportZ],8.0);
		GroupInfo[DutyGroup[playerid]][gTransportTowary]--;

		return 1;
	}
	else if(!strcmp(comm1,"paliwo",true))
	{
		new string[256],result[32],uid,station_id,value;
		mysql_query("SELECT `uid`, `station_id`, `value` FROM `srv_fuel_orders` WHERE `driver`='0' AND `status`='0'");
		mysql_store_result();
		format(string,sizeof(string),"Uid\tID Stacji\tIloœæ");

		while(mysql_fetch_row_format(result, "|") == 1)
		{
			sscanf(result,"p<|>ddd",uid, station_id,value);
			format(string,sizeof(string),"%s\n%d\t%d\t%d",string,uid,station_id,value);
		}
		mysql_free_result();
		if(strlen(string)<21)
		{
			Tip(playerid,5,"Brak zamowien");
			return 1;
		}
		new model=GetVehicleModel(GetPlayerVehicleID(playerid));
		new trailer=GetVehicleModel(GetVehicleTrailer(GetPlayerVehicleID(playerid)));
		if(!(model==514 || model==515 || model==403) && trailer!=584 )
			return msg_error(playerid,"Aby skorzystac z tej komendy musisz znajdowac siê w trucku z podczepion¹ cystern¹.");
		
		ShowPlayerDialog(playerid,D_FUEL_TRANSPORT,DIALOG_STYLE_TABLIST_HEADERS,DEF_NAME" » paliwo",string,"OK","");
	}
	
	return 1;
}

CMD:namierz(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");

	if(!IsPlayerOnDutyInGroup(playerid, GROUP_PD) && !IsPlayerOnDutyInGroup(playerid, GROUP_FBI))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
	
	new comm1[16], comm2[32];
	if(sscanf(params, "s[16]S()[32]", comm1, comm2))
		return msg_usage(playerid,"U¿yj: /namierz [numer | pojazd | wylacz]");
	else
	{
		if(!strcmp(comm1, "numer", true))
		{
			new numer;
			if(sscanf(comm2, "d", numer))
				return msg_usage(playerid,"U¿yj: /namierz numer [numer telefonu]");
			else
			{
				
				
				if(!PlayerDoor[playerid])
					return msg_error(playerid,"Nie znajdujesz siê w pomieszczeniu komisariatu policji / budynku FBI.");
				
				if(!(DoorsInfo[PlayerDoor[playerid]][dOwnerTyp] == OWNER_GROUP && GroupInfo[DoorsInfo[PlayerDoor[playerid]][dOwner]][gType] == GROUP_PD) && !(DoorsInfo[PlayerDoor[playerid]][dOwnerTyp] == OWNER_GROUP && GroupInfo[DoorsInfo[PlayerDoor[playerid]][dOwner]][gType] == GROUP_FBI))
					return msg_error(playerid,"Nie znajdujesz siê w pomieszczeniu komisariatu policji / budynku FBI.");
				
				new string[64];
				format(string, sizeof(string), "zainicjowa³ procedurê namierzania telefonu o numerze %d.", numer);
				cmd_me(playerid, string);
				
				new playerid2 = GetPhoneID(numer);
				
				if(playerid2 < 0 || !Logged[playerid2])
					return cmd_do(playerid, "Wybrany abonent jest poza zasiêgiem, procedura namierzania przerwana.");
				else if(!CharacterInfo[playerid2][pPhone])
					return cmd_do(playerid, "Wybrany abonent jest poza zasiêgiem, procedura namierzania przerwana.");
				
				cmd_do(playerid, "Numer zosta³ znaleziony, trwa namierzanie ..");
				
				SetTimerEx("PlayerTrackNumber", 10000, false, "iii", playerid, playerid2, numer);
			}
		}
		else if(!strcmp(comm1, "pojazd", true))
		{
			new vehuid;
			if(sscanf(comm2, "d", vehuid))
				return msg_usage(playerid,"U¿yj: /namierz pojazd [uid pojazdu]");
			else
			{
				if(!PlayerDoor[playerid])
					return msg_error(playerid,"Nie znajdujesz siê w pomieszczeniu komisariatu policji.");
				else if(!(DoorsInfo[PlayerDoor[playerid]][dOwnerTyp] == OWNER_GROUP && GroupInfo[DoorsInfo[PlayerDoor[playerid]][dOwner]][gType] == GROUP_PD))
					return msg_error(playerid,"Nie znajdujesz siê w pomieszczeniu komisariatu policji.");
				
				if(!VehicleInfo[vehuid][vUID])
					return msg_error(playerid, "Wpisany pojazd nie istnieje.");
				
				if(VehicleInfo[vehuid][vOwnerTyp] == OWNER_GROUP && VehicleInfo[vehuid][vOwner] == DutyGroup[playerid])
				{
					
				}
				else
					msg_error(playerid, "Pojazd nie jest w³asnoœci¹ grupy - nie mo¿na go namierzyæ.");
			}
		}
		else if(!strcmp(comm1, "wylacz", true))
		{
			RemovePlayerMapIcon(playerid, 99);
		}
	}
	
	return 1;
}

CMD:zabierz(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(CharacterInfo[playerid][pBW] || CharacterInfo[playerid][pWounded])
		return 1;
	if(!IsPlayerOnDutyInGroup(playerid, GROUP_PD) && !IsPlayerOnDutyInGroup(playerid, GROUP_FBI) && !IsPlayerOnDutyInGroup(playerid, GROUP_MILITARY) && !IsPlayerInCriminalGroup(playerid))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
	
	new comm1[32], comm2[32];
	if(sscanf(params, "s[32]S()[32]", comm1, comm2))
		return msg_usage(playerid,"U¿yj: /zabierz [przedmiot | pieniadze]");
	else
	{
		if(!strcmp(comm1, "przedmiot", true))
		{
			new playerid2;
			if(sscanf(comm2, "i", playerid2))
				return msg_usage(playerid,"U¿yj: /zabierz przedmiot [ID gracza]");
			else
			{
				if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
					return msg_error(playerid,"Wybrany gracz nie jest zalogowany.");
				if(!PlayerToPlayer(5.0, playerid, playerid2))
					return msg_error(playerid,"Wybrany gracz znajduje siê zbyt daleko Ciebie.");
				if(!CharacterInfo[playerid2][pBW] && !CharacterInfo[playerid2][pWounded])
					return msg_error(playerid,"Gracz nie posiada BW - nie mo¿esz mu zabraæ przedmiotu.");
				if(!CanMove(playerid))
					return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
				if(CharacterInfo[playerid2][pHours] < 2)
					return msg_error(playerid,"Nie mo¿na zabieraæ przedmiotów postaciom, które nie przegra³y 2h.");

				SetTimerEx("TakeItemFormPlayer",5000,false,"ii",playerid,playerid2);
				ApplyAnimation(playerid,"COP_AMBIENT", "Copbrowse_loop", 4.1, 0, 0, 0, 0, 5000, 1);
				GameTextForPlayer(playerid, "~g~Trwa przeszukanie", 5000, 4);
			}
		}
		else if(!strcmp(comm1, "pieniadze", true) || !strcmp(comm1, "kasa", true) || !strcmp(comm1, "pieni¹dze", true))
		{
			new playerid2;
			if(sscanf(comm2, "i", playerid2))
				return msg_usage(playerid,"U¿yj: /zabierz pieniadze [ID gracza]");

			if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
				return msg_error(playerid,"Wybrany gracz nie jest zalogowany.");
			if(!PlayerToPlayer(5.0, playerid, playerid2))
				return msg_error(playerid,"Wybrany gracz znajduje siê zbyt daleko Ciebie.");
			if(!CharacterInfo[playerid2][pBW] && !CharacterInfo[playerid2][pWounded])
				return msg_error(playerid,"Gracz nie posiada BW - nie mo¿esz mu zabraæ przedmiotu.");
			if(!CanMove(playerid))
				return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
			if(CharacterInfo[playerid2][pHours] < 2)
					return msg_error(playerid,"Nie mo¿na zabieraæ pieniêdzy postaciom, które nie przegra³y 2h.");
			
			SetTimerEx("TakeMoneyFormPlayer",5000,false,"ii",playerid,playerid2);
			ApplyAnimation(playerid,"COP_AMBIENT", "Copbrowse_loop", 4.1, 0, 0, 0, 0, 5000, 1);
			GameTextForPlayer(playerid, "~g~Trwa przeszukanie", 5000, 4);
		}
	}
	
	return 1;
}

CMD:kajdanki(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!IsPlayerOnDutyInGroup(playerid, GROUP_PD) && !IsPlayerOnDutyInGroup(playerid, GROUP_FBI) && !IsPlayerOnDutyInGroup(playerid, GROUP_GOV) && !IsPlayerOnDutyInGroup(playerid, GROUP_MILITARY))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
	
	new playerid2;
	if(sscanf(params, "i", playerid2))
		return msg_usage(playerid,"U¿yj: /kajdanki [ID]");
	else
	{
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid,"Wybrany gracz nie jest zalogowany w grze.");
		if(!PlayerToPlayer(5.0, playerid, playerid2))
			return msg_error(playerid,"Wybrany gracz nie znajduje siê obok Ciebie.");
		if(!CanMove(playerid))
			return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
		if(playerid == playerid2)
			return msg_error(playerid,"Nie mo¿esz skuæ samego siebie!");
		
		if(CharacterInfo[playerid2][pStatus] & STATUS_KAJDANKI)
		{
			new string[64];
			
			format(string, sizeof(string), "zdejmuje kajdanki osobie %s.", PlayerName2(playerid2));
			cmd_me(playerid, string);
			
			CharacterInfo[playerid2][pStatus] -= STATUS_KAJDANKI;
			
			CharacterInfo[playerid2][pKajdankiID] = 0;
			
			SetPlayerSpecialAction(playerid2, SPECIAL_ACTION_NONE);
			
			UnfreezePlayer(playerid2);
		}
		else if(CanMove(playerid2))
		{
			if(CharacterInfo[playerid2][pStatus] & STATUS_CIAGNIETY)
			{
				CharacterInfo[playerid2][pStatus] -= STATUS_CIAGNIETY;
				CharacterInfo[playerid2][pKajdankiID] = 0;
				UnfreezePlayer(playerid2);
			}
			if(CharacterInfo[playerid2][pStatus] & STATUS_ZWIAZANY)
			{
				CharacterInfo[playerid2][pStatus] -= STATUS_ZWIAZANY;
				UnfreezePlayer(playerid2);
			}
			
			new string[64];
			
			format(string, sizeof(string), "zak³ada kajdanki osobie %s.", PlayerName2(playerid2));
			cmd_me(playerid, string);
			
			CharacterInfo[playerid2][pStatus] += STATUS_KAJDANKI;
			
			CharacterInfo[playerid2][pKajdankiID] = playerid;
			
			SetPlayerSpecialAction(playerid2, SPECIAL_ACTION_CUFFED);
			
			FreezePlayer(playerid2);
		}
	}
	
	return 1;
}

CMD:zwloki(playerid,params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	
	new comm1[16],comm2[16];
	if(sscanf(params, "s[16]S()[16]",comm1,comm2))
		return msg_usage(playerid,"U¿yj: /zwloki [podnies | od³ó¿ | przeszukaj | zbadaj | usun]");
	else if(!strcmp(comm1,"zbadaj",true))
	{
		if(!CharacterInfo[playerid][pAdmin] && !IsPlayerOnDutyInGroup(playerid,GROUP_PD) && !IsPlayerOnDutyInGroup(playerid,GROUP_MC) && !IsPlayerOnDutyInGroup(playerid,GROUP_FBI) && !IsPlayerOnDutyInGroup(playerid, GROUP_MILITARY))
			return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy.");
		
		new uid;
		if(sscanf(comm2,"i",uid))
			return msg_usage(playerid,"U¿yj: /zwloki zbadaj [id zw³ok]");
		else
		{
			if(uid >= MAX_CORPSE || uid < 1)
				return msg_error(playerid, "Wpisz poprawne UID zw³ok!");
			
			if(!CorpseInfo[uid][corpseID])
				return msg_error(playerid, "Wpisz poprawne UID zw³ok!");
			
			if(! (IsPlayerInRangeOfPoint(playerid,5.0,CorpseInfo[uid][corpseX],CorpseInfo[uid][corpseY],CorpseInfo[uid][corpseZ]) && CorpseInfo[uid][corpseVW] == GetPlayerVirtualWorld(playerid)))
				return msg_error(playerid,"Nie znajdujesz siê w pobli¿u zw³ok o podanym ID.");

			new string[1024];
			format(string,sizeof(string),"Imiê i nazwisko:\t\t%s\nData zgonu:\t\t%s\nBroñ:\t\t\t%s (%d)\nPowód:\t\t\t%s",CorpseInfo[uid][corpsePlayerName],CorpseInfo[uid][corpseDate],CorpseInfo[uid][corpseGun],CorpseInfo[uid][corpseGunVal],CorpseInfo[uid][corpseReason]);
			ShowPlayerDialog(playerid,D_INFO,DIALOG_STYLE_MSGBOX,DEF_NAME" » zw³oki",string,"OK","");
		}
	}
	else if(!strcmp(comm1,"podnieœ",true) || !strcmp(comm1,"podnies",true))
	{
		new uid;
		if(sscanf(comm2,"i",uid))
			return msg_usage(playerid,"U¿yj: /zwloki podnieœ [id zw³ok]");
		else
		{
			if(uid >= MAX_CORPSE || uid < 1)
				return msg_error(playerid, "Wpisz poprawne UID zw³ok!");
			
			if(!CorpseInfo[uid][corpseID])
				return msg_error(playerid, "Wpisz poprawne UID zw³ok!");
			
			if(!(IsPlayerInRangeOfPoint(playerid,5.0,CorpseInfo[uid][corpseX],CorpseInfo[uid][corpseY],CorpseInfo[uid][corpseZ]) && CorpseInfo[uid][corpseVW] == GetPlayerVirtualWorld(playerid)))
				return msg_error(playerid,"Nie znajdujesz siê w pobli¿u zw³ok o podanym ID.");
			
			if(!GetPVarInt(playerid, "CarryCorpse"))
			{
				SetPVarInt(playerid,"CarryCorpse",uid);
				DestroyDynamic3DTextLabel(CorpseInfo[uid][corpseText]);
				DestroyDynamicObject(CorpseInfo[uid][corpseObject]);
				CorpseInfo[uid][corpseX]=CorpseInfo[uid][corpseY]=CorpseInfo[uid][corpseZ]=-2000.0;
				SetPlayerAttachedObject(playerid, 9, 19944, 5, 0.092999,-0.033999,0.000000, 58.700012, 0.0,0.0);
			}
		}
	}
	else if(!strcmp(comm1,"odloz",true) || !strcmp(comm1,"od³ó¿",true))
	{
		new uid=GetPVarInt(playerid,"CarryCorpse");
		if(!uid)
			return msg_error(playerid,"Nie przenosisz ¿adnych zw³ok.");
		
		if(IsPlayerInAnyVehicle(playerid))
			return msg_error(playerid,"Nie mo¿esz od³o¿yæ zw³ok w pojezdzie.");
		
		RemovePlayerAttachedObject(playerid,9);
		DeletePVar(playerid,"CarryCorpse");
		new Float:x,Float:y,Float:z,interior,vw;
		GetPlayerPos(playerid,x,y,z);
		vw=GetPlayerVirtualWorld(playerid);
		interior=GetPlayerInterior(playerid);
		CorpseInfo[uid][corpseX]=x;
		CorpseInfo[uid][corpseY]=y;
		CorpseInfo[uid][corpseZ]=z-1.0;
		CorpseInfo[uid][corpseInt]=interior;
		CorpseInfo[uid][corpseVW]=vw;
		CorpseInfo[uid][corpseObject] = CreateDynamicObject(19944, CorpseInfo[uid][corpseX], CorpseInfo[uid][corpseY], CorpseInfo[uid][corpseZ], 0, 0, 0, CorpseInfo[uid][corpseVW], CorpseInfo[uid][corpseInt], -1);
		new string[32];
		format(string, sizeof(string), "Zw³oki {636363}(%d)",uid);
		CorpseInfo[uid][corpseText] = CreateDynamic3DTextLabel(string, COLOR_RED, CorpseInfo[uid][corpseX], CorpseInfo[uid][corpseY], CorpseInfo[uid][corpseZ]+0.75, 7.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,1, CorpseInfo[uid][corpseVW]);
		new query[256];
		format(query, sizeof(query), "UPDATE `srv_corpse` SET `pos_x`='%f', `pos_y`='%f', `pos_z`='%f', `int`='%d', `vw`='%d' WHERE `uid`='%d'", x, y, CorpseInfo[uid][corpseZ], interior, vw, uid);
		mysql_query(query);
	}
	else if(!strcmp(comm1,"przeszukaj",true))
	{
		new uid;
		if(sscanf(comm2,"i",uid))
			return msg_usage(playerid,"U¿yj: /zwloki przeszukaj [id zw³ok]");
		else
		{
			if(uid >= MAX_CORPSE || uid < 1)
				return msg_error(playerid, "Wpisz poprawne UID zw³ok!");
			
			if(!CorpseInfo[uid][corpseID])
				return msg_error(playerid, "Wpisz poprawne UID zw³ok!");
			
			if(! (IsPlayerInRangeOfPoint(playerid,5.0,CorpseInfo[uid][corpseX],CorpseInfo[uid][corpseY],CorpseInfo[uid][corpseZ]) && CorpseInfo[uid][corpseVW] == GetPlayerVirtualWorld(playerid)))
				return msg_error(playerid,"Nie znajdujesz siê w pobli¿u zw³ok o podanym ID.");
			new string[512];
			ForeachEx(i,_ITEM_COUNT)
				if(ItemInfo[i][iOwnerTyp]==OWNER_CORPSE && ItemInfo[i][iOwner]==uid)
					format(string,sizeof(string),"%s%d\t%s\t%d\t%d\n",string,ItemInfo[i][iUID],ItemInfo[i][iName],ItemInfo[i][iValue1],ItemInfo[i][iValue2]);
			if(strlen(string)>4)
			{
				ShowPlayerDialog(playerid, D_CORPSE_SEARCH, DIALOG_STYLE_TABLIST, DEF_NAME" » zw³oki", string, "Opcje", "WyjdŸ");
				SetPVarInt(playerid, "CorpseSearchID", uid);
			}
			else if(CorpseInfo[uid][corpseMoney] > 0)
			{
				format(string,sizeof(string),"Przy zw³okach znalaz³eœ {02AD38}$"COL_MSGBOX"%d. Czy chcesz zabraæ pieni¹dze?");
				ShowPlayerDialog(playerid, D_CORPSE_MONEY, DIALOG_STYLE_MSGBOX, DEF_NAME" » zw³oki", string, "Tak", "Nie");
				SetPVarInt(playerid, "CorpseSearchID", uid);
			}
			else
				Tip(playerid,3,"Nic nie znalazles.");
		}	
	}
	else if(!strcmp(comm1,"usun",true))
	{
		if(CharacterInfo[playerid][pAdmin] < 1)
			return msg_error(playerid,"Nie posiadasz uprawnien do u¿ycia tej komendy");
		new uid;
		if(sscanf(comm2,"i",uid))
			return msg_usage(playerid,"U¿yj: /zwloki usuñ [id zw³ok]");
		
		if(uid >= MAX_CORPSE || uid < 1)
			return msg_error(playerid, "Wpisz poprawne UID zw³ok!");
		
		if(!CorpseInfo[uid][corpseID])
			return msg_error(playerid, "Wpisz poprawne UID zw³ok!");

		ForeachPlayer(i)
			if(GetPVarInt(i,"CarryCorpse") == uid)
				return msg_error(playerid,"Zw³oki o podanym UID s¹ aktualnie przenoszone przez gracza.");
		
		DestroyDynamic3DTextLabel(CorpseInfo[uid][corpseText]);
		DestroyDynamicObject(CorpseInfo[uid][corpseObject]);
		ForeachEx(i,_ITEM_COUNT)
			if(ItemInfo[i][iOwnerTyp]==OWNER_CORPSE && ItemInfo[i][iOwner]==uid)
				DeleteItem(uid);
		
		CorpseInfo[uid][corpseID] =
		CorpseInfo[uid][corpsePlayerUID] = 
		CorpseInfo[uid][corpseGun] =
		CorpseInfo[uid][corpseGunVal] =
		CorpseInfo[uid][corpseDate] =
		CorpseInfo[uid][corpseInt] = 
		CorpseInfo[uid][corpseObject] =
		CorpseInfo[uid][corpseVW] = 0;
		CorpseInfo[uid][corpseX] =
		CorpseInfo[uid][corpseY] =
		CorpseInfo[uid][corpseZ] = 0.0;
		//CorpseInfo[uid][corpsePlayerName];
		//CorpseInfo[uid][corpseReason]
		new query[64];
		format(query, sizeof(query), "DELETE FROM `srv_corpse` WHERE `uid` = %d",uid);
		mysql_query(query);
		msg_infoFormat(playerid, 64, "Pomyœlnie usun¹³es zw³oki o uid %d.", uid);
	}
	else if(!strcmp(comm1, "goto", true))
	{
		if(CharacterInfo[playerid][pAdmin] < 1)
			return msg_error(playerid,"Nie posiadasz uprawnien do u¿ycia tej komendy");
		new uid;
		if(sscanf(comm2,"i",uid))
			return msg_usage(playerid, "U¿yj: /zwloki usuñ [id zw³ok]");
		
		if(uid >= MAX_CORPSE || uid < 1)
			return msg_error(playerid, "Wpisz poprawne UID zw³ok!");
		
		if(!CorpseInfo[uid][corpseID])
			return msg_error(playerid, "Wpisz poprawne UID zw³ok!");

		ForeachPlayer(i)
			if(GetPVarInt(i, "CarryCorpse") == uid)
				return msg_error(playerid, "Zw³oki o podanym UID s¹ aktualnie przenoszone przez gracza.");

		SetPlayerPos(playerid, CorpseInfo[uid][corpseX], CorpseInfo[uid][corpseY], CorpseInfo[uid][corpseZ]);
		SetPlayerInterior(playerid, CorpseInfo[uid][corpseInt]);
		SetPlayerVirtualWorld(playerid, CorpseInfo[uid][corpseVW]);
	}
	
	return 1;
}

CMD:reklamausun(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!IsPlayerOnDutyInGroup(playerid, GROUP_NEWS))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
	
	format(advreklama, sizeof(advreklama), "~b~~h~SANN ~w~~>~ Aktualnie nikt nie nadaje.");

	TextDrawSetString(TD_LSN, advreklama);
	
	ON_AIR = 0;
	
	return 1;
}

CMD:news(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!IsPlayerOnDutyInGroup(playerid, GROUP_NEWS))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
	
	if(!CanMove(playerid))
		return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
	if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 582 && !(DoorsInfo[PlayerDoor[playerid]][dOwner] == DutyGroup[playerid] && DoorsInfo[PlayerDoor[playerid]][dOwnerTyp]==OWNER_GROUP))
		return msg_error(playerid,"Aby nadaæ newsa musisz znajdowaæ siê w wozie transmisyjnym lub budynku radia.");
	
	new text[128];
	if(sscanf(params, "s[128]", text))
		return msg_usage(playerid,"U¿yj: /news [treœæ]");
	else
	{
		if(text[strlen(text)-1]==' ')
			return msg_error(playerid,"Treœæ newsa nie mo¿e koñczyæ siê spacj¹!");

		ReplacePolishLetters(text,strlen(text));
		format(advnews, sizeof(advnews), "~y~~h~SANN ~w~~>~ %s: %s", PlayerName3(playerid), text);
		
		TextDrawSetString(TD_LSN2, advnews);
	}
	
	return 1;
}

CMD:newsusun(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!IsPlayerOnDutyInGroup(playerid, GROUP_NEWS))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
	
	format(advnews, sizeof(advnews), "~b~~h~SANN ~w~~>~ Aktualnie nikt nie nadaje.");

	TextDrawSetString(TD_LSN2, advnews);
	
	return 1;
}

CMD:blokada(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	
	if(!CanMove(playerid))
		return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
	
	new comm1[32], comm2[32];
	if(sscanf(params, "s[32]S()[32]", comm1, comm2))
		return msg_usage(playerid,"U¿yj: /blokada [naloz | zdejmij | info]");
	else if(!strcmp(comm1, "naloz", true))
	{
		if(!IsPlayerOnDutyInGroup(playerid, GROUP_PD))
			return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
		new koszt;
		if(sscanf(comm2, "d", koszt))
			return msg_usage(playerid,"U¿yj: /blokada naloz [kwota]");
		else
		{
			if(koszt < 1)
				return msg_error(playerid,"Kwota musi byæ wiêksza od zera!");
		
			new vehid = GetClosestVehicle(playerid);
			new vehuid = GetVehicleUID(vehid);
			
			if(!vehuid) return 1;
			
			if(!VehicleInfo[vehuid][vBlokada])
			{
				VehicleInfo[vehuid][vBlokada] = koszt;
				
				GetVehiclePos(VehicleInfo[vehuid][vSAMPID], VehicleInfo[vehuid][vposx], VehicleInfo[vehuid][vposy], VehicleInfo[vehuid][vposz]);
				VehicleInfo[vehuid][vVW] = GetVehicleVirtualWorld(VehicleInfo[vehuid][vSAMPID]);
				VehicleInfo[vehuid][vInt] = GetPlayerInterior(playerid);
				GetVehicleZAngle(VehicleInfo[vehuid][vSAMPID], VehicleInfo[vehuid][vAngle]);
				
				SaveVehicle(vehuid, SAVE_VEH_BASIC);
				SaveVehicle(vehuid, SAVE_VEH_POS);
				
				UnspawnVehicle(vehuid);
				LoadVehicle(vehuid);
				
				msg_info(playerid, "Za³o¿y³eœ blokadê na ko³o pojazdu.");
				
				new string[64];
				format(string, sizeof(string), "zak³ada blokadê na pojazd %s.", GetVehicleModelName(VehicleInfo[vehuid][vModel]));
				cmd_me(playerid, string);
				new string2[32];
				format(string2, sizeof(string2), "Nalozenie blokady (UID: %d)", vehuid);
				LogGroupOffer(playerid, DutyGroup[playerid], string2, 0);
			}
			else
				msg_error(playerid,"Pojazd posiada ju¿ blokadê. U¿yj /blokada zdejmij lub /blokada info.");
		}
	}
	else if(!strcmp(comm1, "zdejmij", true))
	{
		if(!IsPlayerOnDutyInGroup(playerid, GROUP_PD) || !IsPlayerPermInGroup(playerid, DutyGroup[playerid], PERM_EXTRA))
			return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
		
		new vehid = GetClosestVehicle(playerid);
		new vehuid = GetVehicleUID(vehid);
		
		if(!vehuid) return 1;
	
		if(VehicleInfo[vehuid][vBlokada])
		{
			VehicleInfo[vehuid][vBlokada] = 0;
			
			SaveVehicle(vehuid, SAVE_VEH_BASIC);
			
			msg_info(playerid, "Zdj¹³eœ blokadê z ko³a pojazdu.");
			
			new string[64];
			format(string, sizeof(string), "zdejmuje blokadê z pojazdu %s.", GetVehicleModelName(VehicleInfo[vehuid][vModel]));
			cmd_me(playerid, string);
			new string2[32];
			format(string2, sizeof(string2), "Zdjecie blokady (UID: %d)", vehuid);
			LogGroupOffer(playerid, DutyGroup[playerid], string2, 0);
		}
		else
			msg_error(playerid,"Pojazd nie posiada blokady.");
	}
	else if(!strcmp(comm1, "info", true))
	{
		new vehid = GetClosestVehicle(playerid);
		new vehuid = GetVehicleUID(vehid);
		
		if(!vehuid) return 1;
		
		if(VehicleInfo[vehuid][vBlokada])
		{
			new string[64];
			
			format(string, sizeof(string), "UID: %d, MODEL: %s, KWOTA: $%d", VehicleInfo[vehuid][vUID], GetVehicleModelName(VehicleInfo[vehuid][vModel]), VehicleInfo[vehuid][vBlokada]);
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » blokada pojazdu", string, "Zamknij", "");
		}
		else
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, DEF_NAME" » blokada pojazdu", "Ten pojazd nie posiada blokady", "Zamknij", "");
	}
	
	return 1;
}

CMD:knebel(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!IsPlayerOnDutyInGroup(playerid, GROUP_FBI) && !IsPlayerInCriminalGroup(playerid))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
	
	new playerid2;
	if(sscanf(params, "i", playerid2))
		return msg_usage(playerid,"U¿yj: /knebel [ID gracza]");
	else
	{
		if(playerid == playerid2 && !CharacterInfo[playerid][pAdmin])
			return msg_error(playerid,"Nie mo¿esz u¿ywaæ knebla na samym sobie!");
		if(!CanMove(playerid))
			return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
		if(!PlayerToPlayer(5.0, playerid, playerid2))
			return msg_error(playerid,"Gracz o podanym ID nie znajduje siê obok Ciebie.");
		
		new string[64];
		if(CharacterInfo[playerid2][pStatus] & STATUS_KNEBEL)
		{
			CharacterInfo[playerid2][pStatus] -= STATUS_KNEBEL;

			format(string,sizeof(string),"zdejmuje knebel %s.", PlayerName2(playerid2));
			cmd_me(playerid,string);
		}
		else
		{
			CharacterInfo[playerid2][pStatus] += STATUS_KNEBEL;
			
			format(string,sizeof(string),"zak³ada knebel %s.",PlayerName2(playerid2));
			cmd_me(playerid,string);
		}
	}
	
	return 1;
}

CMD:lspd(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!IsPlayerOnDutyInGroup(playerid, GROUP_PD) && !IsPlayerOnDutyInGroup(playerid, GROUP_FBI))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
	
	ShowPlayerDialog(playerid, D_LSPD, DIALOG_STYLE_LIST, DEF_NAME" » centrala LSPD", "1. Lista pojazdów z blokad¹\n2. Kartoteki\n3. Poszukiwani\n4. Mobile Data Terminal", "Wybierz", "Zamknij");
	
	return 1;
}

CMD:megafon(playerid, params[])
{
	if(!PlayerHaveItemType(playerid, ITEM_TYPE_MEGAFON))
		return msg_error(playerid,"Nie posiadasz przy sobie megafonu.");
	
	if(!CanMove(playerid))
		return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
	
	new tmp;
	for(new i=1;i<MAX_PLAYER_GROUPS;i++)
	{
		if(GroupInfo[MemberGroup[playerid][i][GroupID]][gFlags] & FLAG_MEGAPHONE)
		{
			tmp=1;
			break;
		}
	}
	if(!tmp)
		return msg_error(playerid,"Nie nale¿ysz do grupy pozwalaj¹cej na u¿ywanie megafonu.");
	
	new text[124];
	if(sscanf(params, "s[124]", text))
		return msg_usage(playerid,"U¿yj: /megafon [treœæ]");
	else
	{
		new string[170];
		text[0] = chrtoupper(text[0]);
		
		format(string, sizeof(string), "<megafon> %s(%d): %s!!", PlayerName2(playerid), playerid, text);
		SendWrappedMessageToPlayerRange(playerid, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, string, 75);
	}
	
	return 1;
}
CMD:m(playerid,params[]) return cmd_megafon(playerid,params);

CMD:ciagnij(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!IsPlayerOnDutyInGroup(playerid, GROUP_FBI) && !IsPlayerInCriminalGroup(playerid))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
	
	new playerid2;
	if(sscanf(params, "i", playerid2))
		return msg_usage(playerid,"U¿yj: /ciagnij [ID gracza]");
	else if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
		return msg_error(playerid,"Wybrany gracz nie jest zalogowany w grze.");
	if(!PlayerToPlayer(5.0, playerid, playerid2))
		return msg_error(playerid,"Wybrany gracz nie znajduje siê obok Ciebie.");
	if(!CanMove(playerid))
		return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
	if(playerid == playerid2)
		return msg_error(playerid,"Nie mo¿esz ci¹gn¹æ samego siebie!");
	
	if(CharacterInfo[playerid2][pStatus] & STATUS_CIAGNIETY)
	{
		new string[64];
		
		format(string, sizeof(string), "przestaje ci¹gn¹æ %s.", PlayerName2(playerid2));
		cmd_me(playerid, string);
		
		CharacterInfo[playerid2][pStatus] -= STATUS_CIAGNIETY;
		
		CharacterInfo[playerid2][pKajdankiID] = 0;
		
		UnfreezePlayer(playerid2);
	}
	else
	{
		ForeachPlayer(i)
		{
			if(CharacterInfo[i][pKajdankiID]==playerid )
				return msg_error(playerid,"Ci¹gniesz ju¿ kogoœ innego.");
		}
		if(CharacterInfo[playerid2][pStatus] & STATUS_KAJDANKI)
		{
			CharacterInfo[playerid2][pStatus] -= STATUS_KAJDANKI;
			CharacterInfo[playerid2][pKajdankiID] = 0;
			UnfreezePlayer(playerid2);
		}
		if(CharacterInfo[playerid2][pStatus] & STATUS_ZWIAZANY)
		{
			CharacterInfo[playerid2][pStatus] -= STATUS_ZWIAZANY;
			UnfreezePlayer(playerid2);
		}

	
		new string[64];
		
		format(string, sizeof(string), "zaczyna ci¹gn¹æ %s.", PlayerName2(playerid2));
		cmd_me(playerid, string);
		
		CharacterInfo[playerid2][pStatus] += STATUS_CIAGNIETY;
		
		CharacterInfo[playerid2][pKajdankiID] = playerid;
		
		FreezePlayer(playerid2);
	}

	
	return 1;
}

CMD:cennik(playerid,params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	
	new doorid = PlayerDoor[playerid];
	if(!doorid || !(DoorsInfo[doorid][dOwnerTyp] == OWNER_GROUP && (GroupInfo[DoorsInfo[doorid][dOwner]][gType] == GROUP_SHOP || GroupInfo[DoorsInfo[doorid][dOwner]][gType] == GROUP_WORKSHOP || GroupInfo[DoorsInfo[doorid][dOwner]][gType] == GROUP_RESTAURANT || GroupInfo[DoorsInfo[doorid][dOwner]][gType]==GROUP_FUELSTATION || GroupInfo[DoorsInfo[doorid][dOwner]][gType] == GROUP_GYM || GroupInfo[DoorsInfo[doorid][dOwner]][gType] == GROUP_KLUB || GroupInfo[DoorsInfo[doorid][dOwner]][gType] == GROUP_GUNSHOP)))
		return msg_error(playerid,"Nie znajdujesz siê w pomieszczeniu odpowiedniej grupy!");
	if(!IsPlayerPermInGroup(playerid,DoorsInfo[doorid][dOwner],PERM_PRODUCT))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do zarz¹dzania produktami w tej grupie");
	
	new string[1024];
	new groupid = DoorsInfo[doorid][dOwner];
	format(string,sizeof(string),"UID\tNazwa\tCena\tIloœæ\n");
	ForeachEx(i,_ITEM_COUNT)
		if(ItemInfo[i][iOwnerTyp] == OWNER_GROUP && ItemInfo[i][iOwner] == groupid)
			format(string,sizeof(string),"%s\n%d\t%s\t$%d\t%d\n",string,i,ItemInfo[i][iName],ItemInfo[i][iPrice],ItemInfo[i][iIlosc]);
	
	if(strlen(string)>22)
		ShowPlayerDialog(playerid, D_ITEM_PRICE, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » ustal ceny", string, "Wybierz", "WyjdŸ");
	else
		msg_error(playerid,"Brak produktów w magazynie!");

	return 1;
}
CMD:cenyuslug(playerid,params[])
{
	new groupid=DutyGroup[playerid];
	if(!groupid)
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie odpowiedniej grupy.");
	if(GroupInfo[groupid][gLeader] != CharacterInfo[playerid][pUID])
		return msg_error(playerid,"Nie jesteœ liderem tej grupy.");

	new string[128];
	if(GroupInfo[groupid][gType] == GROUP_TAXI)
		format(string,sizeof(string),"Przejazd taxi (1km)\t$%d",GetOfferPrice(groupid,OFFER_TAXI));
	else if(GroupInfo[groupid][gType] == GROUP_WORKSHOP)
	{
		format(string,sizeof(string),"Naprawa\t$%d",GetOfferPrice(groupid,OFFER_REPAIR_ENG));
		format(string,sizeof(string),"%s\nMalowanie\t$%d",string, GetOfferPrice(groupid,OFFER_PAINT));
		format(string,sizeof(string),"%s\nPaintjob\t$%d",string, GetOfferPrice(groupid,OFFER_PAINTJOB));
		format(string,sizeof(string),"%s\nTuning\t$%d",string, GetOfferPrice(groupid,OFFER_TUNING));
		format(string,sizeof(string),"%s\nDemonta¿ tuningu\t$%d",string, GetOfferPrice(groupid,OFFER_DISMOUNT));
	}
	else if(GroupInfo[groupid][gType] == GROUP_GYM)
	{
		format(string,sizeof(string),"Karnet jednorazowy\t$%d",GetOfferPrice(groupid,OFFER_GYM_SINGLE));
		format(string,sizeof(string),"%s\nKarnet ca³odniowy\t$%d",string,GetOfferPrice(groupid,OFFER_GYM_DAY));
		format(string,sizeof(string),"%s\nKarnet tygodniowy\t$%d",string,GetOfferPrice(groupid,OFFER_GYM_WEEK));
	}
	else if(GroupInfo[groupid][gType] == GROUP_NEWS)
	{
		format(string, sizeof(string), "Cena reklamy (1min)\t$%d",GetOfferPrice(groupid,OFFER_ADVERT));
		format(string, sizeof(string), "%s\nCena SMS (/dzwon 444)\t$%d",string,SettingInfo[sSANNPay]);
	}
	else if(GroupInfo[groupid][gType] == GROUP_MC)
		format(string, sizeof(string), "/uleczsie\t$%d",GetOfferPrice(groupid,OFFER_MEDICINE));
	else if(GroupInfo[groupid][gType] == GROUP_FUELSTATION && GetPlayerStationID(playerid) && StationInfo[GetPlayerStationID(playerid)][sOwner] == groupid)
		format(string, sizeof(string), "Cena paliwa (1l)\t$%d", StationInfo[GetPlayerStationID(playerid)][sFuelCost]);
	if(strlen(string)>5)
		ShowPlayerDialog(playerid, D_GROUP_PRICES, DIALOG_STYLE_TABLIST, DEF_NAME" » cennik us³ug", string, "Wybierz", "WyjdŸ");
	else
		msg_error(playerid,"Wybrana grupa nie posiada cennika us³ug.");
	
	return 1;
}

CMD:stacja(playerid,params[])
{
	new stationid=GetPlayerStationID(playerid);
	if(!stationid || !StationInfo[stationid][sOwner])
		return msg_error(playerid,"Nie znajdujesz siê na stacji paliw bed¹cej w³asnoœci¹ grupy.");
	if(!IsPlayerPermInGroup(playerid,StationInfo[stationid][sOwner],PERM_PRODUCT))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do zarz¹dzania t¹ stacj¹ paliw.");

	new comm1[16];
	if(sscanf(params,"s[16]",comm1))
		return msg_usage(playerid,"U¿yj: /stacja [info | zamowpaliwo]");

	if(!strcmp(comm1,"info",true))
	{
		new string[128];
		format(string,sizeof(string),"W³aœciciel:\t%s\nPaliwo:\t%dl\nCena za litr:\n$%d",GroupInfo[StationInfo[stationid][sOwner]][gName],StationInfo[stationid][sFuel],SettingInfo[sFuelCost]);
		msg_info(playerid, string);
	}
	else if(!strcmp(comm1,"zamowpaliwo",true) || !strcmp(comm1,"zamówpaliwo",true))
		ShowPlayerDialog(playerid, D_FUEL_ORDER, DIALOG_STYLE_INPUT, DEF_NAME" » stacja paliw", "WprowadŸ ilosæ paliwa jak¹ chcesz zamówiæ:", "Zamów", "Anuluj");
	
	return 1;
}

CMD:wepchnij(playerid,params[])
{
	new playerid2,seat;
	if(sscanf(params,"dd",playerid2,seat))
		return msg_usage(playerid,"U¿yj: /wepchnij [ID gracza] [miejsce(1-3)]");
	new vehid=GetPlayerVehicleID(playerid);
	if(!vehid)
		return msg_error(playerid,"Nie znajdujesz siê w pojeŸdzie.");
	if(!Logged[playerid2] || !PlayerToPlayer(5.0,playerid,playerid2))
		return msg_error(playerid,"Wybrany gracz nie nzajduje siê obok Ciebie.");
	if(GetPlayerVehicleID(playerid2))
		return msg_error(playerid,"Wybrany gracz jest w pojeŸdzie.");
	if(!hasModelEngine(GetVehicleModel(vehid)))
		return msg_error(playerid, "Nie mo¿esz wepchaæ graczy do tego pojazdu.");
	if(seat < 0 || seat > 3)
		return msg_error(playerid, "Musisz wybraæ miejsce miêdzy 1-3.");
	if(VehicleInfo[GetVehicleUID(vehid)][vLocked])
		return msg_error(playerid, "Nie mo¿esz wepchaæ kogoœ do zamkniêtego pojazdu.");
	ForeachPlayer(i)
		if(GetPlayerVehicleID(i)==vehid && GetPlayerVehicleSeat(i)==seat)
			return msg_error(playerid,"Wybrane miejsce jest ju¿ zajête.");
	if(PutPlayerInVehicle(playerid2, vehid, seat))
	{
		SendClientMessageFormat(playerid, COLOR_GREEN, "%s zosta³ wepchniêty do pojazdu.",PlayerName2(playerid2));
		SendClientMessageFormat(playerid2, COLOR_GREEN, "%s wepchn¹³ Ciê do pojazdu.",PlayerName2(playerid));
	}

	return 1;
}

CMD:wyrzuc(playerid,params[])
{
	new vehid=GetPlayerVehicleID(playerid);
	if(!vehid)
		return msg_error(playerid,"Nie znajdujesz siê w pojeŸdzie.");
	new playerid2;
	if(sscanf(params,"d",playerid2))
		return msg_usage(playerid,"U¿yj: /wyrzuc [ID graza]");
	
	if(vehid != GetPlayerVehicleID(playerid2))
		return msg_error(playerid,"Wybrany gracz nie znajduje siê w tym pojeŸdzie.");
	if(GetPlayerState(playerid2)==PLAYER_STATE_DRIVER)
		return msg_error(playerid,"Nie mo¿esz wyrzuciæ kierowcy.");

	RemovePlayerFromVehicle(playerid2);
	if(VehicleInfo[GetVehicleUID(vehid)][vRadio])
		StopAudioStreamForPlayer(playerid2);
	SendClientMessageFormat(playerid, COLOR_GREEN, "%s zosta³ wyrzucony z pojazdu.",PlayerName2(playerid2));
	SendClientMessageFormat(playerid2, COLOR_GREEN, "%s wyrzuci³ Ciê z pojazdu.",PlayerName2(playerid));

	return 1;
}

CMD:corner(playerid,params[])
{
	if(CharacterInfo[playerid][pAdmin] > 4)
	{
		new comm1[16],comm2[32];
		if(sscanf(params,"s[16]S()[32]",comm1,comm2))
			return msg_usage(playerid,"U¿yj: /corner [ handel | stworz | usuñ | goto | lista | przepisz]");
		if(!strcmp(comm1,"stworz",true) || !strcmp(comm1,"stwórz",true))
		{
			new name[32],groupid;
			if(sscanf(comm2,"ds[32]",groupid,name))
				return msg_usage(playerid,"U¿yj: /corner stworz [ID grupy] [nazwa okolicy]");
			if(GroupInfo[groupid][gType] != GROUP_GANG)
				return msg_error(playerid,"Corner mozna przypisaæ tylko pod gang");
			new uid;
			for(new i=1;i<MAX_CORNERS;i++)
			{
				if(!CornerInfo[i][cUID])
				{
					uid=i;
					break;
				}
			}
			if(!uid)
				return msg_error(playerid,"Przekroczono maksymalna iloœc cornerów na serwerze.");

			new Float:x,Float:y,Float:z;
			GetPlayerPos(playerid,x,y,z);
			new query[256];
			format(query, sizeof(query), "INSERT INTO `srv_corners` VALUES ('%d','%s','%d','%f','%f','%f')", uid, name, groupid, x, y, z);
			mysql_query(query);
			CornerInfo[uid][cUID]=uid;
			CornerInfo[uid][cName]=name;
			CornerInfo[uid][cOwner]=groupid;
			CornerInfo[uid][cPosX]=x;
			CornerInfo[uid][cPosY]=y;
			CornerInfo[uid][cPosZ]=z;
			CornerInfo[uid][cIcon]=uid+10;
			ForeachPlayer(i)
				if(IsPlayerInGroup(i,groupid))
					SetPlayerMapIcon(i, CornerInfo[uid][cIcon], x, y, z, 23, 0, MAPICON_LOCAL_CHECKPOINT);
			
			format(query, sizeof(query), "[AI] Pomyslnie utworzy³eœ corner dla gangu %s.", GroupInfo[groupid][gName]);
			msg_info(playerid, query);
		}
		if(!strcmp(comm1,"usuñ",true) || !strcmp(comm1,"usun",true))
		{
			new uid;
			if(sscanf(comm2,"%d",uid))
				return msg_usage(playerid,"U¿yj /corner usun [ID]");
			if(!CornerInfo[uid][cUID])
				return msg_error(playerid,"Corner o podanym ID nie istnieje.");
			new query[64];
			format(query,sizeof(query),"DELETE FROM `srv_corners` WHERE `uid`='%d'",uid);
			mysql_query(query);
			
			ForeachPlayer(i)
				if(IsPlayerInGroup(i,CornerInfo[uid][cOwner]))
					RemovePlayerMapIcon(playerid, CornerInfo[uid][cIcon]);
			
			CornerInfo[uid][cUID]=
			CornerInfo[uid][cOwner]=0;
			CornerInfo[uid][cPosX]=
			CornerInfo[uid][cPosY]=
			CornerInfo[uid][cPosZ]=0.0;
			CornerInfo[uid][cIcon]=-1;
			msg_info(playerid, "Corner zosta³ usuniêty.");
		}
		if(!strcmp(comm1,"goto",true))
		{
			new uid;
			if(sscanf(comm2,"%d",uid))
				return msg_usage(playerid,"U¿yj /corner goto [ID]");
			if(!CornerInfo[uid][cUID])
				return msg_error(playerid,"Corner o podanym id nie istnieje.");
			SetPlayerPos(playerid, CornerInfo[uid][cPosX], CornerInfo[uid][cPosY], CornerInfo[uid][cPosZ]);
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
		}
		if(!strcmp(comm1,"lista",true))
		{
			new string[128];
			SendClientMessage(playerid, COLOR_GREEN, "\t* Lista cornerów *");
			for(new i=1;i<MAX_CORNERS;i++)
				if(CornerInfo[i][cUID])
				{
					format(string,sizeof(string),"%d:{ffffff} %s, W³aœciciel: %s",i,CornerInfo[i][cName],GroupInfo[CornerInfo[i][cOwner]][gName]);
					SendClientMessage(playerid, COLOR_GREEN, string);
				}

		}
		if(!strcmp(comm1,"przepisz",true))
		{
			new uid,groupid;
			if(sscanf(comm2,"%d%d",uid,groupid))
				return msg_usage(playerid,"U¿yj /corner przepisz [ID cornera] [ID gangu]");

			if(!CornerInfo[uid][cUID])
				return msg_error(playerid,"Niepoprawne ID cornera.");
			if(GroupInfo[groupid][gType] != GROUP_GANG)
				return msg_error(playerid,"Corner mozna przepisaæ tylko pod gang.");

			ForeachPlayer(i)
			{
				if(IsPlayerInGroup(i,CornerInfo[uid][cOwner]))
					RemovePlayerMapIcon(playerid, CornerInfo[uid][cIcon]);
				else if(IsPlayerInGroup(i,groupid))
					SetPlayerMapIcon(i, CornerInfo[uid][cIcon], CornerInfo[uid][cPosX], CornerInfo[uid][cPosY], CornerInfo[uid][cPosZ], 23, 0, MAPICON_LOCAL_CHECKPOINT);
			}
			CornerInfo[uid][cOwner] = groupid;
			new query[128];
			format(query,sizeof(query),"UPDATE `srv_corners` SET `owner`='%d' WHERE `uid`='%d'", groupid, uid);
			mysql_query(query);
			msg_info(playerid, "W³aœciciel cornera zosta³ zmieniony.");
		}
		if(strcmp(comm1,"handel",true))
		{
			return 1;
		}
		//nic tu nie dawaæ bo siê handel spierdoli
	}
	if(!IsPlayerInGroupType(playerid,GROUP_GANG))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy.");

	if(!CanMove(playerid))
		return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");

	if(CharacterInfo[playerid][pCorner])
		return msg_error(playerid,"Jesteœ ju¿ w trakcie handlu narkotykami.");
	
	new corner;
	for(new i=1;i<MAX_CORNERS;i++)
	{
		if(IsPlayerInRangeOfPoint(playerid, 3.0, CornerInfo[i][cPosX], CornerInfo[i][cPosY], CornerInfo[i][cPosZ]) && IsPlayerInGroup(playerid,CornerInfo[i][cOwner]))
		{
			corner = i;
			break;
		}
	}

	if(!corner)
		return msg_error(playerid,"Nie znajdujesz siê na cornerze.");

	new hour, minutes, cops = 0;
	gettime(hour, minutes);
	ForeachPlayer(i)
		if(IsPlayerOnDutyInGroup(i, GROUP_PD))
			cops++;
	
	if(hour < 16 && cops < 2)
		return SendClientMessage(playerid, COLOR_RED, "Handel nie jest aktualnie mo¿liwy.");

	new bool:found=false;
	ForeachEx(i,_ITEM_COUNT)
	{
		if( (ItemInfo[i][iType] == ITEM_TYPE_MARIHUANA || ItemInfo[i][iType] == ITEM_TYPE_LSD || ItemInfo[i][iType] == ITEM_TYPE_KOKAINA || ItemInfo[i][iType] == ITEM_TYPE_HEROINA) && ItemInfo[i][iOwnerTyp]==OWNER_PLAYER && ItemInfo[i][iOwner]==CharacterInfo[playerid][pUID])
		{
			found = true;
			break;
		}
	}
	if(!found)
		return msg_error(playerid,"Nie posiadasz narkotyków.");
	CharacterInfo[playerid][pCorner]=corner;
	msg_info(playerid,"Rozpocz¹³eœ handel narkotykami. Nie oddalaj siê od cornera i poczekaj na klientów.");
	CharacterInfo[playerid][pCornerTimer] = SetTimerEx("SellDrugs", 60000+random(10)*30000, false, "i", playerid);
	return 1;
}

CMD:zwiaz(playerid, params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	if(!IsPlayerOnDutyInGroup(playerid, GROUP_FBI) && !IsPlayerOnDutyInGroup(playerid, GROUP_MILITARY) && !IsPlayerInCriminalGroup(playerid) && CharacterInfo[playerid][pAdmin] < 2)
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
	
	new playerid2, string[64];
	if(sscanf(params, "i", playerid2))
		return msg_usage(playerid,"U¿yj: /zwiaz [ID]");
	else
	{
		if(playerid == playerid2 && !CharacterInfo[playerid][pAdmin])
			return msg_error(playerid,"Nie mo¿esz zwi¹zaæ/rozwi¹zaæ samego siebie!");
		if(!CanMove(playerid))
			return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");
		if(!PlayerToPlayer(5.0, playerid, playerid2))
			return msg_error(playerid,"Gracz o podanym ID nie znajduje siê obok Ciebie.");
		
		if(CharacterInfo[playerid2][pStatus] & STATUS_ZWIAZANY)
		{
			CharacterInfo[playerid2][pStatus] -= STATUS_ZWIAZANY;
			UnfreezePlayer(playerid2);

			format(string,sizeof(string),"rozwi¹zuje gracza %s.", PlayerName2(playerid2));
			cmd_me(playerid,string);
		}
		else if(CanMove(playerid2))
		{
			if(CharacterInfo[playerid2][pStatus] & STATUS_CIAGNIETY)
			{
				CharacterInfo[playerid2][pStatus] -= STATUS_CIAGNIETY;
				CharacterInfo[playerid2][pKajdankiID] = 0;
				UnfreezePlayer(playerid2);
			}
			if(CharacterInfo[playerid2][pStatus] & STATUS_KAJDANKI)
			{
				CharacterInfo[playerid2][pStatus] -= STATUS_KAJDANKI;
				CharacterInfo[playerid2][pKajdankiID] = 0;
				UnfreezePlayer(playerid2);
			}
		
			CharacterInfo[playerid2][pStatus] += STATUS_ZWIAZANY;
			FreezePlayer(playerid2);
			
			format(string,sizeof(string),"zwi¹zuje gracza %s.",PlayerName2(playerid2));
			cmd_me(playerid,string);
		}
	}
	return 1;
}
CMD:worek(playerid,params[])
{
	if(!(IsPlayerInCriminalGroup(playerid) || CharacterInfo[playerid][pAdmin]))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy");

	if(!CanMove(playerid))
		return msg_error(playerid,"Nie mo¿esz aktualnie u¿yæ tej komendy.");

	new playerid2;
	if(sscanf(params,"i",playerid2))
		return msg_usage(playerid,"U¿yj: /worek [id gracza]");

	if(!PlayerToPlayer(5.0,playerid,playerid2))
		return msg_error(playerid,"Wybrany gracz nie znajduje siê obok Ciebie");

	if(playerid == playerid2 && !CharacterInfo[playerid][pAdmin])
		return msg_error(playerid, "Nie mo¿esz na³o¿yæ/zdj¹æ worka z samego siebie !");
	
	new string[64];
	if(CharacterInfo[playerid2][pStatus] & STATUS_HEADBAG)
	{
		CharacterInfo[playerid2][pStatus]-=STATUS_HEADBAG;
		TextDrawHideForPlayer(playerid2, TD_HeadBag);
		format(string,sizeof(string),"zdejmuje %s worek z g³owy.",PlayerName2(playerid2));
		cmd_me(playerid,string);
	}
	else
	{
		CharacterInfo[playerid2][pStatus]+=STATUS_HEADBAG;
		TextDrawShowForPlayer(playerid2, TD_HeadBag);
		format(string,sizeof(string),"zak³ada worek na g³owê %s.",PlayerName2(playerid2));
		cmd_me(playerid,string);
		format(string,sizeof(string),"%s(%d) za³o¿y³ Ci worek na g³owê.",PlayerName2(playerid),playerid);
		SendClientMessage(playerid2, COLOR_RED, string);
	}

	return 1;
}
CMD:bariera(playerid,params[]) //1424 1459 1328 1434 19834
{
	if(!IsPlayerInGroupType(playerid,GROUP_PD) && !IsPlayerInGroupType(playerid,GROUP_MC) && !IsPlayerInGroupType(playerid,GROUP_GOV) && !IsPlayerInGroupType(playerid,GROUP_FBI))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy");
	new comm1[8],comm2[4];
	if(sscanf(params, "s[16]S()[4]", comm1,comm2))
		return msg_usage(playerid,"U¿yj: /bariera [stworz | usun]");

	if(!strcmp(comm1,"stworz",true) || !strcmp(comm1,"stwórz",true) )
	{
		new type;
		if(sscanf(comm2,"d",type))
			return msg_usage(playerid,"U¿yj: /bariera stworz [typ]\n\nTypy:\n1-3 bariera\n4. Pacho³ek\n5. Taœma");
		if(type < 1 || type > 5)
			return msg_error(playerid,"Wprowadzono niepoprawne id typu.");
		if(GetPlayerInterior(playerid) || GetPlayerVirtualWorld(playerid))
			return msg_error(playerid,"Bariery mo¿na tworzyæ tylko na vw0");
		new uid,object[]={0,1424,1459,1238,1434,19834};
		for(new i=1;i<MAX_ROADBLOCKS;i++)
		{
			if(!RoadBlock[i][rObject])
			{
				uid=i;
				break;
			}
		}
		if(!uid)
			return msg_error(playerid,"Nie mo¿na stworzyæ wiêcej barier.");

		new Float:x,Float:y,Float:z,Float:angle,string[32];
		GetPlayerPos(playerid,x,y,z);
		GetPlayerFacingAngle(playerid, angle);

		x-=floatsin(angle,degrees);
		y+=floatcos(angle,degrees);
		
		if(type == 3)
			z-=0.6;
		else if(type == 4)
			z-=0.85;
		else
			z-=0.4;
		
		RoadBlock[uid][rObject]=CreateDynamicObject(object[type], x,y, z, 0.0, 0.0, angle, 0);
		RoadBlock[uid][rPosX]=x;
		RoadBlock[uid][rPosY]=y;
		RoadBlock[uid][rPosZ]=z;

		format(string,sizeof(string),"Bariera {c8c8c8}(%d)",uid);
		RoadBlock[uid][r3DText]=CreateDynamic3DTextLabel(string, COLOR_ORANGE, x, y, z+0.5, 5.0);
	}
	else if(!strcmp(comm1,"usun",true) || !strcmp(comm1,"usuñ",true) )
	{
		new uid;
		if(sscanf(comm2,"d",uid))
			return msg_usage(playerid,"U¿yj: /bariera usun [id]");

		if(uid<1 || uid > 20)
			return msg_error(playerid,"Nieprawid³owe id bariery.");
		if(!RoadBlock[uid][rObject])
			return msg_error(playerid,"Nie znaleziono bariery o podanym id.");

		if(!IsPlayerInRangeOfPoint(playerid, 10.0, RoadBlock[uid][rPosX], RoadBlock[uid][rPosY], RoadBlock[uid][rPosZ]))
			return msg_error(playerid,"Nie znajdujesz siê w pobli¿u nariery o podanym id.");

		DestroyDynamicObject(RoadBlock[uid][rObject]);
		if(RoadBlock[uid][r3DText])
			DestroyDynamic3DTextLabel(RoadBlock[uid][r3DText]);

		RoadBlock[uid][r3DText]=Text3D:0;
		RoadBlock[uid][rObject]=0;
		return msg_info(playerid,"Bariera zosta³a usuniêta.");
	}

	return 1;
}
CMD:podaj(playerid,params[])
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	
	if(!IsPlayerOnDutyInGroup(playerid, GROUP_RESTAURANT) && !IsPlayerOnDutyInGroup(playerid, GROUP_GYM) && !IsPlayerOnDutyInGroup(playerid, GROUP_KLUB) && !IsPlayerOnDutyInGroup(playerid, GROUP_GUNSHOP))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie odpowiedniej grupy.");

	new playerid2;
	if(sscanf(params,"d",playerid2))
		return msg_usage(playerid,"U¿yj: /podaj [id gracza]");

	if(!PlayerToPlayer(5.0,playerid,playerid2))
		return msg_error(playerid,"Nie znajdujesz siê w pobli¿u gracza o podanym id.");

	new string[1024],groupid=DutyGroup[playerid];
	format(string,sizeof(string),"UID\tNazwa\tCena\tIloœæ");
	ForeachEx(i,_ITEM_COUNT)
		if(ItemInfo[i][iOwnerTyp]==OWNER_GROUP && ItemInfo[i][iOwner]==groupid && ItemInfo[i][iPrice] > 0)
			format(string,sizeof(string),"%s\n%d\t%s\t$%d\t%d",string,i,ItemInfo[i][iName],ItemInfo[i][iPrice],ItemInfo[i][iIlosc]);
	
	if(strlen(string)<24)
		return msg_error(playerid,"Brak produktów na sprzeda¿ w magazynie grupy.");

	SetPVarInt(playerid,"dRestaurantGiveGroup",DutyGroup[playerid]);
	SetPVarInt(playerid, "dRestaurantGive",playerid2);
	ShowPlayerDialog(playerid,D_RESTAURANT_GIVE,DIALOG_STYLE_TABLIST_HEADERS,DEF_NAME" » podaj produkt",string,"Wybierz","WyjdŸ");

	return 1;
}

CMD:wsparcie(playerid, params[])
{
	if(!DutyGroup[playerid] || !(GroupInfo[DutyGroup[playerid]][gType] > 0 && GroupInfo[DutyGroup[playerid]][gType] < 7 && GroupInfo[DutyGroup[playerid]][gType] != 4 && GroupInfo[DutyGroup[playerid]][gFlags] & FLAG_GPS))
		return msg_error(playerid, "Nie jesteœ na s³u¿bie w odpowiedniej grupie (z dostêpem do GPS).");
	
	if(!CharacterInfo[playerid][pGPS])
	{
		new liczba = 0;
		
		ForeachPlayer(i)
			if(CharacterInfo[i][pGPS] && DutyGroup[i] == CharacterInfo[i][pGPS])
				liczba++;
		
		if(liczba >= MAX_WS_MAPICONS)
			return SendClientMessage(playerid, COLOR_RED, "[GPS] Osi¹gniêto limit /ws na mapie!");
		
		CharacterInfo[playerid][pGPS] = DutyGroup[playerid];
		
		GameTextForPlayer(playerid, "~y~~>~ Wlaczyles namierzanie GPS. ~<~", 3000, 3);
		
		if(CharacterInfo[playerid][pTog] & TOG_STATUS)
		{
			PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][0]);
			
			PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][1]);
			PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][2]);
		}
	}
	else
	{
		CharacterInfo[playerid][pGPS] = 0;
		
		for(new d = 0; d<MAX_WS_MAPICONS; d++)
		{
			if(WS_MAPICONS[playerid][d] != -1)
				DestroyDynamicMapIcon(WS_MAPICONS[playerid][d]);
			
			WS_MAPICONS[playerid][d] = -1;
		}
		
		GameTextForPlayer(playerid, "~y~~>~ Wylaczyles namierzanie GPS. ~<~", 3000, 3);
		
		if(CharacterInfo[playerid][pTog] & TOG_STATUS)
		{
			PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][0]);
			
			PlayerTextDrawHide(playerid, TDEditor_PTD[playerid][1]);
			PlayerTextDrawShow(playerid, TDEditor_PTD[playerid][2]);
		}
	}
	
	return 1;
}
CMD:ws(playerid, params[]) return cmd_wsparcie(playerid, params);

CMD:magazyn(playerid,params[])
{
	new groupid = IsPlayerInGroupType(playerid,GROUP_SYNDICATE);
	if(!groupid)
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycie tej komendy.");
	if(!IsPlayerPermInGroup(playerid,groupid,PERM_MAGAZINE))
		return msg_error(playerid,"Nie posiadasz uprawnien do zarz¹dzania magazynem w tej grupie.");

	if(!((IsPlayerInRangeOfPoint(playerid, 3.0, 1386.125610, 5.463948, 1000.913269) && GetPlayerVirtualWorld(playerid) == 120) || (IsPlayerInRangeOfPoint(playerid, 3.0, 2601.9739, 2848.2932, 10.8203) && GetPlayerVirtualWorld(playerid) == 0)))
		return msg_error(playerid,"Nie znajdujesz siê na terenie magazynu broni.");

	ShowPlayerDialog(playerid,D_WEAPON_MAGAZINE_CATEGORY,DIALOG_STYLE_LIST,DEF_NAME" » wybierz kategoriê","Broñ palna\nAmunicja","Wybierz","WyjdŸ");

	return 1;
}

CMD:dotacja(playerid, params[])
{
	if(!DutyGroup[playerid] || GroupInfo[DutyGroup[playerid]][gType] != GROUP_GOV)
		return msg_error(playerid, "Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
	
	if(!PlayerDoor[playerid] || DoorsInfo[PlayerDoor[playerid]][dOwner] != DutyGroup[playerid])
		return msg_error(playerid, "Nie znajdujesz siê w budynku GOV.");
	
	if(IsPlayerPermInGroup(playerid, DutyGroup[playerid], PERM_CASH))
	{
		new uid, cash;
		if(sscanf(params, "dd", uid, cash))
			return msg_usage(playerid, "U¿yj: /dotacja [UID grupy] [kwota]");
		else
		{
			if(!GroupInfo[uid][gUID])
				return msg_error(playerid, "Wybrana grupa nie istnieje.");
			
			if(cash < 1)
				return msg_error(playerid, "Wpisana kwota nie jest poprawna.");
			
			if(cash > GroupInfo[DutyGroup[playerid]][gCash])
				return msg_error(playerid, "Twoja grupa nie posiada takich funduszy.");
			
			new string[128];
			format(string, sizeof(string), "Czy jesteœ pewny, ¿e chcesz wys³aæ poni¿sz¹ dotacjê?\n\nKwota: $%d\nUID grupy: %d\nNazwa grupy: %s", cash, uid, GroupInfo[uid][gName]);
			
			SetPVarInt(playerid, "DotacjaUID", uid);
			SetPVarInt(playerid, "DotacjaCASH", cash);
			
			ShowPlayerDialog(playerid, D_DOTACJA, DIALOG_STYLE_MSGBOX, DEF_NAME" » dotacja", string, "Potwierdz", "Anuluj");
		}
	}
	return 1;
}

CMD:sprzedajpojazd(playerid, params[])
{
	if(!IsPlayerOnDutyInGroup(playerid, GROUP_CARDEALER))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
	
	new playerid2, vehuid, cash;
	if(sscanf(params, "idd", playerid2, vehuid, cash))
		return msg_usage(playerid, "U¿yj: /sprzedajpojazd [ID gracza] [UID pojazdu] [kwota]");
	else
	{
		if(!VehicleInfo[vehuid][vUID])
			return msg_error(playerid, "Nie ma takiego pojazdu.");
		
		if(!(VehicleInfo[vehuid][vOwnerTyp] == OWNER_GROUP && VehicleInfo[vehuid][vOwner] == DutyGroup[playerid]))
			return msg_error(playerid, "Pojazd nie jest w³asnoœci¹ grupy.");
		
		if(!IsPlayerConnected(playerid2) || !Logged[playerid2])
			return msg_error(playerid, "Wybrany gracz nie jest zalogowany.");
		
		if(!PlayerToPlayer(5.0, playerid, playerid2))
			return msg_error(playerid,"Znajdujesz siê zbyt daleko od gracza.");
		
		if(cash < 1)
			return msg_error(playerid,"Podana cena nie jest poprawna.");
		
		SetPVarInt(playerid, "OfferBuyer", playerid2);
		SetPVarInt(playerid, "OfferVehicleUID", vehuid);
		SetPVarInt(playerid, "OfferPrice", cash);
		new string[128];
		format(string,sizeof(string),"Czy na pewno chcesz sprzedaæ %s(%d) pojazd %s [UID:%d] za $%d?", PlayerName2(playerid2), playerid2, GetVehicleModelName(VehicleInfo[vehuid][vModel]), vehuid, cash);
		ShowPlayerDialog(playerid, D_OFFER_VEHICLE_END_KOMIS, DIALOG_STYLE_MSGBOX, DEF_NAME" » sprzeda¿ pojazdu", string, "Tak", "Nie");
	}
	
	return 1;
}

CMD:ruletka(playerid, params)
{
	if(!IsPlayerOnDutyInGroup(playerid, GROUP_KASYNO))
		return msg_error(playerid, "Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
	
	if(!PlayerDoor[playerid] || !(DoorsInfo[PlayerDoor[playerid]][dOwnerTyp] == OWNER_GROUP && DoorsInfo[PlayerDoor[playerid]][dOwner] == DutyGroup[playerid]))
		return msg_error(playerid, "Nie znajdujesz siê w budynku grupy.");
	
	new ran = random(3);
	new string[64];
	
	switch(ran)
	{
		case 0:
			format(string, sizeof(string), "Ruletka wylosowa³a kolor: {C90000}RED{9A9CCD}.");
		case 1:
			format(string, sizeof(string), "Ruletka wylosowa³a kolor: {000000}BLACK{9A9CCD}.");
		case 2:
			format(string, sizeof(string), "Ruletka wylosowa³a kolor: {02AD38}GREEN{9A9CCD}.");
	}
	
	cmd_do(playerid, string);
	
	return 1;
}

CMD:fortuna(playerid, params)
{
	if(!IsPlayerOnDutyInGroup(playerid, GROUP_KASYNO))
		return msg_error(playerid, "Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
	
	if(!PlayerDoor[playerid] || !(DoorsInfo[PlayerDoor[playerid]][dOwnerTyp] == OWNER_GROUP && DoorsInfo[PlayerDoor[playerid]][dOwner] == DutyGroup[playerid]))
		return msg_error(playerid, "Nie znajdujesz siê w budynku grupy.");
	
	new string[64];
	
	format(string, sizeof(string), "Krupier losuje liczbê: {02AD38}%d{9A9CCD}.", random(100)+1);
	
	cmd_do(playerid, string);
	
	return 1;
}

CMD:bot(playerid, params[])
{
	if(!IsPlayerOnDutyInGroup(playerid, GROUP_GOV) || !IsPlayerPermInGroup(playerid, DutyGroup[playerid], PERM_DOOR))
		return msg_error(playerid, "Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
	
	new option;
	if(sscanf(params,"d", option))
		return msg_usage(playerid, "U¿ycie: /bot [1/0]");
	
	switch(option)
	{
		case 0:
		{
			SettingInfo[sGovBots] = false;
			msg_info(playerid, "Wy³¹czy³eœ automatyczne boty!");
		}
		case 1:
		{
			SettingInfo[sGovBots] = true;
			msg_info(playerid, "W³¹czy³eœ automatyczne boty!");
		}
	}
	
	return 1;
}

CMD:taser(playerid, params[])
{
	if(!IsPlayerOnDutyInGroup(playerid, GROUP_PD) && !IsPlayerOnDutyInGroup(playerid, GROUP_GOV) && !IsPlayerOnDutyInGroup(playerid, GROUP_FBI))
		return msg_error(playerid, "Nie posiadasz uprawnieñ do u¿ycia tej komendy b¹dŸ nie jesteœ na slu¿bie danej grupy.");
	
	switch(CharacterInfo[playerid][pHaveTaser])
	{
		case 0:
		{
			Tip(playerid, 3, "Wyciagnales taser.");
			CharacterInfo[playerid][pHaveTaser] = true;
			
			new index = 0;
			if(IsPlayerPremium(playerid))
			{
				for(new i=5;i<10;i++)
				{
					if(!IsPlayerAttachedObjectSlotUsed(playerid, i))
					{
						index=i;
						break;
					}
				}
			}
			else
			{
				for(new i=5;i<8;i++)
				{
					if(!IsPlayerAttachedObjectSlotUsed(playerid, i))
					{
						index=i;
						break;
					}
				}
			}
			
			if(!index)
				return SendClientMessage(playerid, COLOR_RED, "Nie mo¿na by³o dodaæ obiektu tasera do rêki - masz na sobie za du¿o doczepialnych obiektów.");
			
			SetPlayerAttachedObject(playerid, index, 18642, 6, 0.071997, 0.020997, 0.044998, -2.0, -178.7, 0.0, 1.0, 1.0, 1.0);
			CharacterInfo[playerid][pTaserSlot] = index;
		}
		case 1:
		{
			if(CharacterInfo[playerid][pTaserSlot])
			{
				RemovePlayerAttachedObject(playerid, CharacterInfo[playerid][pTaserSlot]);
				CharacterInfo[playerid][pTaserSlot] = 0;
			}
			
			CharacterInfo[playerid][pHaveTaser] = false;
			Tip(playerid, 3, "Schowales taser.");
		}
	}
	
	return 1;
}

CMD:zlomuj(playerid,params[])
{
	if(!IsPlayerInAnyVehicle(playerid))
		return msg_error(playerid,"Nie znajdujesz siê w pojeŸdzie");

	new vehuid=GetVehicleUID(GetPlayerVehicleID(playerid));
	if(!vehuid)
		return 0;
	if(!IsOwnerVehicle(playerid,true))
		return msg_error(playerid,"Nie posiadasz uprawnieñ do z³omowania tego pojazdu.");
	if(!IsPlayerInRangeOfPoint(playerid, 15.0, 1888.1,-1860.2,13.5))
		return msg_error(playerid,"Nie znajdujesz siê na z³omowisku.");
	
	//TODO
	return 1;
}

CMD:zgloszenia(playerid,params)
{
	if(!(DutyGroup[playerid] && GroupInfo[DutyGroup[playerid]][gFlags] & FLAG_911))
		return msg_error(playerid, "Nie jesteœ na s³u¿bie w odpowiedniej grupie.");
	
	new string[1024];
	format(string, sizeof(string), "ID\tGodzina\tZg³aszaj¹cy");
	ForeachEx(i, MAX_911CALLS)
	{
		if(CallInfo[i][cID] && CallInfo[i][cGroup] == DutyGroup[playerid])
			format(string, sizeof(string), "%s\n%d\t%s:%s\t%s", string, CallInfo[i][cID], CallInfo[i][cTimeH], CallInfo[i][cTimeM], LoadPlayerName(CallInfo[i][cCaller]));
	}
	
	if(strlen(string) > 24) ShowPlayerDialog(playerid, D_ZGLOSZENIA, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » lista zg³oszeñ", string, "Opcje", "Zamknij");
	else Tip(playerid, 3, "Brak aktywnych zgloszen dla twojej grupy.");
	
	return 1;
}