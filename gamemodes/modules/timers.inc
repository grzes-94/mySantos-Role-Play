forward TimerSecond();
forward TimerMinute();
forward TimerHour();

public TimerSecond()
{
	if(restart > 0)
	{
		if(restart%5 == 0)
			ForeachPlayer(i)
				SendClientMessageFormat(i, COLOR_RED, "[RESTART] Restart serwera za %d sekund!", restart);
		
		restart --;
		
		if(!restart)
		{
			ForeachPlayer(i)
				if(!CharacterInfo[i][pAdmin]) KickWithWait(i);
			
			SetTimer("RestartGMX", 1000, false);
		}
	}
	
	if(ON_AIR)
	{
		ON_AIR--;
		if(!ON_AIR)
		{
			format(advreklama, sizeof(advreklama), "~y~~h~SANN ~w~~>~ Aktualnie nikt nie nadaje.");
			TextDrawSetString(TD_LSN, advreklama);
		}
	}
	
	new tick = GetTickCount() - 2500;
	ForeachPlayer(i)
	{
		if(Logged[i])
		{
			if(!(CharacterInfo[i][pStatus] & STATUS_AFK))
			{	
				if(tick >= CharacterInfo[i][pLastUpdate])
				{
					new model;
					if(IsPlayerInAnyVehicle(i))
						model=GetVehicleModel(GetPlayerVehicleID(i));
					if(model != 403 && model != 514 && model != 515) //afk w tirach wbija, bugi sampa
					{
						CharacterInfo[i][pStatus] += STATUS_AFK;
						playerLog(i,"AFK","%s jest AFK",PlayerName(i));
						SetPVarInt(i,"ESC",1);
						
					
						new hour, minute;
						gettime(hour, minute);
						
						CharacterInfo[i][pAFKg] = hour;
						CharacterInfo[i][pAFKm] = minute;
					}
				}
				else
					CharacterInfo[i][pOnlineToday]++;
			}
			
			if(CharacterInfo[i][pAntiFloodWarn] > 0)
				CharacterInfo[i][pAntiFloodWarn]--;
			
			if(CharacterInfo[i][pStatus] & STATUS_PASY && !IsPlayerInAnyVehicle(i))
			{
				CharacterInfo[i][pStatus] -= STATUS_PASY;
				
				if(CharacterInfo[i][pTog] & TOG_STATUS)
				{
					PlayerTextDrawHide(i, TDEditor_PTD[i][3]);
					
					PlayerTextDrawHide(i, TDEditor_PTD[i][4]);
					PlayerTextDrawHide(i, TDEditor_PTD[i][5]);
				}
			}else if(!IsPlayerInAnyVehicle(i))
			{
				if(CharacterInfo[i][pTog] & TOG_STATUS)
				{
					PlayerTextDrawHide(i, TDEditor_PTD[i][3]);
					
					PlayerTextDrawHide(i, TDEditor_PTD[i][4]);
					PlayerTextDrawHide(i, TDEditor_PTD[i][5]);
				}
			}
			
			if(CharacterInfo[i][pACTimer])
				CharacterInfo[i][pACTimer]--;
			
			// Animacja BW, odliczanie
			if(CharacterInfo[i][pDeathTimer])
				CharacterInfo[i][pDeathTimer]--;
			
			if(CharacterInfo[i][pWoundedTimer])
				CharacterInfo[i][pWoundedTimer]--;
			
			if(CharacterInfo[i][pBW])
			{
				if(GetPlayerAnimationIndex(i) != 1206)
					ApplyAnimation(i, "PED", "KO_shot_front", 4.0, 0, 1, 1, 1, 0, 1);
				
				new string[128];
				CharacterInfo[i][pBW] --;

				if(CharacterInfo[i][pBW] > 60)
					format(string, sizeof(string), "~r~Status BW:~n~ ~y~%d min.", CharacterInfo[i][pBW]/60);
				else
					format(string, sizeof(string), "~r~Status BW:~n~ ~y~%d sek.", CharacterInfo[i][pBW]);
				
				GameTextForPlayer(i, string, 1000, 1);
				
				SetPlayerHP(i, 20);
				
				if(CharacterInfo[i][pBW] <= 0)
				{
					CharacterInfo[i][pBW] = 0;
					
					ApplyAnimation(i, "Attractors", "Stepsit_out", 4.0, 0, 0, 0, 0, 0, 1);
					TogglePlayerControllable(i, 1);
					
					SetCameraBehindPlayer(i);
					
					msg_info(i, "Ockn¹³eœ siê, jednak nie jesteœ wystarczaj¹co na si³ach.\nTwój stan zdrowia nie jest idealny - mo¿e udaj siê do szpitala?");
					SavePlayerStats(i, SAVE_PLAYER_BASIC);
				}
			}
			else if(CharacterInfo[i][pWounded])
			{
				if(GetPlayerAnimationIndex(i) != 389)
					ApplyAnimation(i, "CRACK", "crckidle1", 4.1, 0, 1, 1, 1, 0, 1);
				
				new string[128];
				CharacterInfo[i][pWounded] --;

				if(CharacterInfo[i][pWounded] > 60)
					format(string, sizeof(string), "~r~Status powalenia:~n~ ~y~%d min.", CharacterInfo[i][pWounded]/60);
				else
					format(string, sizeof(string), "~r~Status powalenia:~n~ ~y~%d sek.", CharacterInfo[i][pWounded]);
				
				GameTextForPlayer(i, string, 1000, 1);
				
				SetPlayerHP(i, 20);
				
				if(CharacterInfo[i][pWounded] <= 0)
				{
					CharacterInfo[i][pWounded] = 0;
					CharacterInfo[i][pBW] = 5 * 60;
					
					TogglePlayerControllable(i, 0);
					
					msg_info(i, "Niestety nikt ci nie pomóg³, dlatego to otrzymujesz w³aœciwe BW - pomóc ci teraz mo¿e tylko medyk. Ockniesz siê tak¿e sam po up³ywie odpowiedniego czasu.");
					SavePlayerStats(i, SAVE_PLAYER_BASIC);
				}
			}
			
			if(CharacterInfo[i][pShowDoors])
			{
				CharacterInfo[i][pShowDoors] --;
			
				if(!CharacterInfo[i][pShowDoors])
					PlayerTextDrawHide(i, DoorsTD[i]);
			}
			
			for(new d = 0; d<MAX_WS_MAPICONS; d++)
			{
				if(WS_MAPICONS[i][d] != -1)
					DestroyDynamicMapIcon(WS_MAPICONS[i][d]);
				
				WS_MAPICONS[i][d] = -1;
			}
			
			if(GroupInfo[DutyGroup[i]][gType] > 0 && GroupInfo[DutyGroup[i]][gType] < 7 && GroupInfo[DutyGroup[i]][gType] != 4 && GroupInfo[DutyGroup[i]][gFlags] & FLAG_GPS)
			{
				if(!Streamer_IsToggleIdleUpdate(i))
					Streamer_ToggleIdleUpdate(i, 1);
				
				for(new x = 0, pool2=GetPlayerPoolSize(); x<=pool2; x++)
				{
					if(CharacterInfo[x][pGPS] && DutyGroup[x] == CharacterInfo[x][pGPS] && DutyGroup[i])
					{
						new icon = -1;
						for(new s = 0; s<MAX_WS_MAPICONS; s++)
						{
							if(WS_MAPICONS[i][s] == -1)
							{
								icon = s;
								break;
							}
						}
						
						new Float:pos[3];
						
						if(icon != -1)
						{
							new error = 0;
							
							if(GetPlayerVirtualWorld(x) == 0)
								GetPlayerPos(x, pos[0], pos[1], pos[2]);
							else if(PlayerDoor[x])
							{
								pos[0] = DoorsInfo[PlayerDoor[x]][dEnterX];
								pos[1] = DoorsInfo[PlayerDoor[x]][dEnterY];
								pos[2] = DoorsInfo[PlayerDoor[x]][dEnterZ];
							}
							else
							{
								CharacterInfo[x][pGPS] = 0;
								SendClientMessage(x, COLOR_RED, "[GPS] W aktualnym miejscu nie mozesz uzyc namierzania GPS.");
								
								if(CharacterInfo[x][pTog] & TOG_STATUS)
								{
									PlayerTextDrawShow(x, TDEditor_PTD[x][0]);
									
									PlayerTextDrawHide(x, TDEditor_PTD[x][1]);
									PlayerTextDrawShow(x, TDEditor_PTD[x][2]);
								}
								
								error = 1;
							}
							
							if(!error)
							{
								new icon2 = -1;
								for(new s = 0; s<MAX_WS_MAPICONS; s++)
								{
									if(WS_MAPICONS[i][s] == -1)
									{
										icon2 = s;
										break;
									}
								}
								
								if(icon2 != -1)
									WS_MAPICONS[i][icon2] = CreateDynamicMapIcon(pos[0], pos[1], pos[2], 0, GetGroupColor(GroupInfo[DutyGroup[x]][gUID]), -1, -1, i, -1, MAPICON_GLOBAL);
							}
						}
					}
				}
			}
			
			if(CharacterInfo[i][pRepairTime] > 0)
			{
				new string[36];
				static Float:x,Float:y,Float:z;
				GetVehiclePos(VehicleInfo[CharacterInfo[i][pRepairVeh]][vSAMPID], x, y, z);
				if(!IsPlayerInRangeOfPoint(i, 10.0, x, y, z) || DoorsInfo[PlayerDoor[i]][dOwner]!=DutyGroup[i])
				{
					msg_info(i,"Oddali³eœ siê od pojazdu. Naprawa anulowana");
					msg_info(GetPVarInt(i,"pRepairCustomer"),"Mechanik oddali³ siê od pojazdu. Naprawa anulowana");
					DeletePVar(i,"pRepairJobPrice");
					DeletePVar(GetPVarInt(i,"pRepairCustomer"),"pRepairMechanic");
					DeletePVar(i,"pRepairCustomer");					
					DeletePVar(i,"pRepairType");					
					DeletePVar(i,"pRepairPrice");
					CharacterInfo[i][pRepairTime]=0;
					CharacterInfo[i][pRepairVeh]=0;
					DestroyDynamic3DTextLabel(CharacterInfo[i][pRepair3DText]);
				}
				else
				{
					CharacterInfo[i][pRepairTime]--;
					
					if(CharacterInfo[i][pRepairType]==OFFER_PAINT || CharacterInfo[i][pRepairType]==OFFER_PAINTJOB)
						format(string,sizeof(string),"Malowanie pojazdu: %d sekund", CharacterInfo[i][pRepairTime]);
					else if(CharacterInfo[i][pRepairType]==OFFER_REPAIR_ENG || CharacterInfo[i][pRepairType]==OFFER_REPAIR_BODY || CharacterInfo[i][pRepairType]==OFFER_REPAIR_TIRES || CharacterInfo[i][pRepairType]==OFFER_REPAIR_ALL)
						format(string,sizeof(string),"Naprawa pojazdu: %d sekund", CharacterInfo[i][pRepairTime]);
					else if(CharacterInfo[i][pRepairType]==OFFER_TUNING || CharacterInfo[i][pRepairType]==OFFER_DISMOUNT)
						format(string,sizeof(string),"Tuning pojazdu: %d sekund", CharacterInfo[i][pRepairTime]);
						
					UpdateDynamic3DTextLabelText(CharacterInfo[i][pRepair3DText], 0x2836FFFF, string);

					if(CharacterInfo[i][pRepairTime] <= 0)
					{
						new customer = GetPVarInt(i,"pRepairCustomer");
						new uid= CharacterInfo[i][pRepairVeh];
						new repair_type[32];			
						new type=CharacterInfo[i][pRepairType];
						new job_price = GetPVarInt(i,"pRepairJobPrice");
						new price = GetPVarInt(i,"pRepairPrice") - job_price;
						if(!VehicleInfo[uid][vSpawned])
						{
							msg_info(i,"Pojazd nie jest zespawnowany. Us³uga anulowana.");
							msg_info(customer,"Pojazd nie jest zespawnowany. Us³uga anulowana.");
						}
						else if(GetPVarInt(customer, "WorkshopPayOption") == 0 && CharacterInfo[customer][pCash]<price + job_price)
						{
							msg_info(i,"Klient nie posiada odpowiedniej iloœci gotówki przy sobie. Us³uga anulowana.");
							msg_info(customer,"Nie posiadasz odpowiedniej iloœci gotówki przy sobie. Us³uga anulowana.");
						}
						else if(GetPVarInt(customer, "WorkshopPayOption") == 1 && CharacterInfo[customer][pCredit]<price + job_price)
						{
							msg_info(i,"Klient nie posiada odpowiedniej iloœci gotówki w banku. Us³uga anulowana.");
							msg_info(customer,"Nie posiadasz odpowiedniej iloœci gotówki w banku. Us³uga anulowana.");
						}
						else
						{
							if(type==OFFER_REPAIR_ENG)
							{
								new Float:hp=float(GetVehicleMaxHP(VehicleInfo[uid][vModel]));
								VehicleInfo[uid][vHP]=hp;
								SetVehicleHealth(VehicleInfo[uid][vSAMPID], hp);
								PlayerPlaySound(i, 1133, 0.0,0.0,0.0);
								PlayerPlaySound(customer, 1133, 0.0,0.0,0.0);
								GameTextForPlayer(customer, "~g~Pojazd naprawiony", 3000, 4);
								format(repair_type,sizeof(repair_type),"Naprawa pojazdu");
							}
							else if(type==OFFER_REPAIR_BODY)
							{
								VehicleInfo[uid][vVisual][0]=0;
								VehicleInfo[uid][vVisual][1]=0;
								VehicleInfo[uid][vVisual][2]=0;
								UpdateVehicleDamageStatus(VehicleInfo[uid][vSAMPID], 0, 0, 0, VehicleInfo[uid][vVisual][3]);
								PlayerPlaySound(i, 1133, 0.0,0.0,0.0);
								PlayerPlaySound(customer, 1133, 0.0,0.0,0.0);
								GameTextForPlayer(customer, "~g~Pojazd naprawiony", 3000, 4);
								format(repair_type,sizeof(repair_type),"Naprawa pojazdu");
							}
							else if(type==OFFER_REPAIR_TIRES)
							{
								VehicleInfo[uid][vVisual][3]=0;
								UpdateVehicleDamageStatus(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vVisual][0], VehicleInfo[uid][vVisual][1], VehicleInfo[uid][vVisual][2], VehicleInfo[uid][vVisual][3]);
								PlayerPlaySound(i, 1133, 0.0,0.0,0.0);
								PlayerPlaySound(customer, 1133, 0.0,0.0,0.0);
								GameTextForPlayer(customer, "~g~Pojazd naprawiony", 3000, 4);
								format(repair_type,sizeof(repair_type),"Naprawa pojazdu");
							}
							else if(type==OFFER_REPAIR_ALL)
							{
								VehicleInfo[uid][vVisual][0]=0;
								VehicleInfo[uid][vVisual][1]=0;
								VehicleInfo[uid][vVisual][2]=0;
								VehicleInfo[uid][vVisual][3]=0;
								UpdateVehicleDamageStatus(VehicleInfo[uid][vSAMPID],0,0,0,0);
								new Float:hp=float(GetVehicleMaxHP(VehicleInfo[uid][vModel]));
								VehicleInfo[uid][vHP]=hp;
								SetVehicleHealth(VehicleInfo[uid][vSAMPID], hp);
								PlayerPlaySound(i, 1133, 0.0,0.0,0.0);
								PlayerPlaySound(customer, 1133, 0.0,0.0,0.0);
								GameTextForPlayer(customer, "~g~Pojazd naprawiony", 3000, 4);
								format(repair_type,sizeof(repair_type),"Naprawa pojazdu");
							}
							else if(type==OFFER_PAINT)
							{
								VehicleInfo[uid][vColor1]=GetPVarInt(i,"pRepairColor1");
								VehicleInfo[uid][vColor2]=GetPVarInt(i,"pRepairColor2");
								ChangeVehicleColor(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vColor1], VehicleInfo[uid][vColor2]);
								PlayerPlaySound(i, 1134, 0.0,0.0,0.0);
								PlayerPlaySound(customer, 1134, 0.0,0.0,0.0);
								GameTextForPlayer(customer, "~g~Pojazd przemalowany", 3000, 4);
								DeletePVar(i,"pRepairColor1");
								DeletePVar(i,"pRepairColor2");
								format(repair_type,sizeof(repair_type),"Malowanie pojazdu");
							}
							else if(type==OFFER_PAINTJOB)
							{
								new paint = GetPVarInt(i,"pRepairPaint");
								ChangeVehiclePaintjob(VehicleInfo[uid][vSAMPID],paint);

								VehicleInfo[uid][vTuning] &= TUNING_VISUAL;
								if(paint != 3)
								{
									VehicleInfo[uid][vTuning] += TUNING_PAINTJOB;
									if(paint == 0)
										VehicleInfo[uid][vTuning] += TUNING_PAINTJOB_0;
									else if(paint == 1)
										VehicleInfo[uid][vTuning] += TUNING_PAINTJOB_1;
									else if(paint == 2)
										VehicleInfo[uid][vTuning] += TUNING_PAINTJOB_2;

								}
								DeletePVar(i,"pRepairPaint");
								PlayerPlaySound(i, 1134, 0.0,0.0,0.0);
								PlayerPlaySound(customer, 1134, 0.0,0.0,0.0);
								GameTextForPlayer(customer, "~g~Pojazd przemalowany", 3000, 4);
								format(repair_type,sizeof(repair_type),"Paintjob");
							}
							else if(type==OFFER_TUNING)
							{
								new itemid=GetPVarInt(i, "pRepairPart");
								new query[128];
								if(ItemInfo[itemid][iType] != ITEM_TYPE_GLASS)
								{
									AddVehicleComponent(VehicleInfo[uid][vSAMPID],ItemInfo[itemid][iValue1]);
									format(query,sizeof(query),"INSERT INTO `srv_tuning` VALUES (NULL,'%d','%d','%s')",uid,ItemInfo[itemid][iValue1],ItemInfo[itemid][iName]);
									mysql_query(query);
									
									if(!(VehicleInfo[uid][vTuning] & TUNING_VISUAL))
										VehicleInfo[uid][vTuning] += TUNING_VISUAL;
								}
								else
									VehicleInfo[uid][vGlass] = true;
								
								ItemInfo[itemid][iIlosc]--;
								if(ItemInfo[itemid][iIlosc] <= 0)
									DeleteItem(itemid);
								else
								{
									format(query,sizeof(query),"UPDATE `srv_items` SET `ilosc` = '%d' WHERE `uid` = '%d' LIMIT 1",ItemInfo[itemid][iIlosc],itemid);
									mysql_query(query);
								}
								PlayerPlaySound(i, 1133, 0.0,0.0,0.0);
								PlayerPlaySound(customer, 1133, 0.0,0.0,0.0);
								GameTextForPlayer(customer, "~g~Komponent zamontowany", 3000, 4);
								format(repair_type,sizeof(repair_type),"Tuning pojazdu");
							}
							else if(type==OFFER_DISMOUNT)
							{
								new partid=GetPVarInt(i, "pRepairPart");
								new query[128],name[32],component_id;
								format(query,sizeof(query),"SELECT `component_id`, `name` FROM `srv_tuning` WHERE `id`='%d'",partid);
								mysql_query(query);
								mysql_store_result();
								mysql_fetch_row_format(query,"|");
								sscanf(query,"p<|>ds[32]",component_id,name);
								mysql_free_result();
								RemoveVehicleComponent(VehicleInfo[uid][vSAMPID], component_id);
								format(query,sizeof(query),"DELETE FROM `srv_tuning` WHERE `id`='%d' LIMIT 1",partid);
								mysql_query(query);
								format(repair_type,sizeof(repair_type),"Demontaz tuningu");
								StworzPrzedmiot(OWNER_PLAYER, CharacterInfo[customer][pUID], name, ITEM_TYPE_TUNING, component_id, 0, 1);
								msg_info(customer,"Demonta¿ zakoñczony. Komponent zosta³ dodany do Twojego ekwipunku");
							}

							DestroyDynamic3DTextLabel(CharacterInfo[i][pRepair3DText]);
							
							switch(GetPVarInt(customer, "WorkshopPayOption"))
							{
								case 0:
								{
									if(CharacterInfo[customer][pCash] < price)
									{
										msg_error(i, "Gracz nie posiada odpowiedniej kwoty.");
										msg_error(customer, "Nie posiadasz odpowiedniej kwoty.");
									}
									else
									{
										GivePlayerCash(customer,-price-job_price);
										
										DeletePVar(customer, "WorkshopPayOption");
										
										new commission = GetMemberCommission(i,DutyGroup[i]);
										if(commission)
										{
											commission=floatround( (float(job_price)/100.0) * float(commission));
											job_price-=commission;
											CharacterInfo[i][pCredit] += commission;
											SavePlayerStats(i,SAVE_PLAYER_BASIC);
											msg_infoFormat(i,128,"Us³uga zakoñczona. Na konto grupy wp³ynê³o $%d.\nOtrzyma³eœ prowizjê w wysokoœci $%d",price + job_price,commission);
										}
										else
											msg_infoFormat(i,128,"Us³uga zakoñczona. Na konto grupy wp³ynê³o $%d.",price + job_price);
										
										GiveGroupCash(DutyGroup[i],price + job_price);
										
										LogGroupOffer(i,DutyGroup[i],repair_type,job_price+price,customer);
										SaveVehicle(uid,SAVE_VEH_BASIC);
									}
								}
								case 1:
								{
									if(CharacterInfo[customer][pCredit] < price)
									{
										msg_error(i, "Gracz nie posiada odpowiedniej kwoty.");
										msg_error(customer, "Nie posiadasz odpowiedniej kwoty.");
									}
									else
									{
										CharacterInfo[customer][pCredit] -= price+job_price;
										SavePlayerStats(customer, SAVE_PLAYER_BASIC);
										
										DeletePVar(customer, "WorkshopPayOption");
										
										new commission = GetMemberCommission(i,DutyGroup[i]);
										if(commission)
										{
											commission=floatround( (float(job_price)/100.0) * float(commission));
											job_price-=commission;
											CharacterInfo[i][pCredit] += commission;
											SavePlayerStats(i,SAVE_PLAYER_BASIC);
											msg_infoFormat(i,128,"Us³uga zakoñczona. Na konto grupy wp³ynê³o $%d.\nOtrzyma³eœ prowizjê w wysokoœci $%d",price + job_price,commission);
										}
										else
											msg_infoFormat(i,128,"Us³uga zakoñczona. Na konto grupy wp³ynê³o $%d.",price + job_price);
										
										GiveGroupCash(DutyGroup[i],price + job_price);
										
										LogGroupOffer(i,DutyGroup[i],repair_type,job_price,customer);
										SaveVehicle(uid,SAVE_VEH_BASIC);
									}
								}
							}
						}

						DeletePVar(i,"pRepairJobPrice");
						DeletePVar(i,"pRepairCustomer");		
						DeletePVar(i,"pRepairPrice");	
						DeletePVar(customer,"pRepairMechanic");
						CharacterInfo[i][pRepairType]=0;
						CharacterInfo[i][pRepairVeh]=0;
					}
				}
			}
			
			if(CharacterInfo[i][pHouseCheck])
			{
				CharacterInfo[i][pHouseCheck] --;

				if(CharacterInfo[i][pHouseCheck] == 5)
					SendClientMessage(i, COLOR_GREEN, "Przejœcie do interioru nast¹pi za 5 sekund.");
				else if(!CharacterInfo[i][pHouseCheck])
				{
					new dooruid = GetClosestDoor(i);
					
					SetPlayerVirtualWorld(i, DoorsInfo[dooruid][dExitVW]);
					SetPlayerInterior(i, DoorsInfo[dooruid][dExitInt]);
					SetPlayerPos(i, DoorsInfo[dooruid][dExitX], DoorsInfo[dooruid][dExitY], DoorsInfo[dooruid][dExitZ]);
					SetPlayerFacingAngle(i, DoorsInfo[dooruid][dExitAngle]);
					
					PlayerTextDrawHide(i, DoorsTD[i]);
					
					CharacterInfo[i][pHouseCheckID] = dooruid;
					
					SendClientMessage(i, COLOR_GREEN, "Aby wyjœæ z interioru wpisz /sprawdzdom wyjdz.");
				}
				
				new dooruid = GetClosestDoor(i);
				if(!dooruid || DoorsInfo[dooruid][dOwnerTyp] != OWNER_HOUSE_BUY)
					CharacterInfo[i][pHouseCheck] = 0;
			}
			
			if(CharacterInfo[i][pStatus] & STATUS_KAJDANKI || CharacterInfo[i][pStatus] & STATUS_CIAGNIETY)
			{
				static Float:Pos[3],playerid2;
				playerid2 = CharacterInfo[i][pKajdankiID];
				
				GetPlayerPos(playerid2, Pos[0], Pos[1], Pos[2]);
				
				if(!PlayerToPlayer(2.0, i, playerid2))
				{
					SetPlayerPos(i, Pos[0]+1, Pos[1], Pos[2]);
					SetPlayerInterior(i, GetPlayerInterior(playerid2));
					SetPlayerVirtualWorld(i, GetPlayerVirtualWorld(playerid2));
				}
			}
			
			if(CharacterInfo[i][pDamageTook])
				CharacterInfo[i][pDamageTook] --;
			
			if(CharacterInfo[i][pCorner] && !IsPlayerInRangeOfPoint(i, 5.0, CornerInfo[CharacterInfo[i][pCorner]][cPosX],CornerInfo[CharacterInfo[i][pCorner]][cPosY],CornerInfo[CharacterInfo[i][pCorner]][cPosZ]))
			{
				KillTimer(CharacterInfo[i][pCornerTimer]);
				CharacterInfo[i][pCorner]=0;
				msg_error(i, "Opusci³eœ corner. Sprzeda¿ zosta³a anulowana");
			}
			
			if(CharacterInfo[i][pAnimacja] > 0)
			{
				CharacterInfo[i][pAnimacja] --;
				
				if(GetPlayerAnimationIndex(i) != 402)
					ApplyAnimation(i, "SWEET", "Sweet_injuredloop", 4.0, 0, 0, 0, 1, 0, 1);
				
				if(CharacterInfo[i][pAnimacja] <= 0)
				{
					ApplyAnimation(i, "CARRY", "crry_prtial", 4.1, 0, 0, 0, 0, 0);
					CharacterInfo[i][pAnimacja] = 0;
				}
			}
			
			static Float:HP, Float:armor;

			GetPlayerHealth(i, HP);
			GetPlayerArmour(i, armor);
			
			if(HP != CharacterInfo[i][pHealth])
				SetPlayerHealth(i, CharacterInfo[i][pHealth]);
			
			if(armor != CharacterInfo[i][pArmor])
				SetPlayerArmour(i, CharacterInfo[i][pArmor]);
			
			if(CharacterInfo[i][pReanimation])
			{
				if(Logged[i] && Logged[CharacterInfo[i][pReanimationID]])
				{
					if(PlayerToPlayer(5.0, i, CharacterInfo[i][pReanimationID]))
					{
						CharacterInfo[i][pReanimation] --;
						
						if(CharacterInfo[i][pReanimation] <= 0)
						{
							msg_info(i,"Zosta³eœ podniesiony/zreanimowany.");
							
							if(CharacterInfo[i][pBW])
								CharacterInfo[i][pBW] = 0;
							else if(CharacterInfo[i][pWounded])
								CharacterInfo[i][pWounded] = 0;
				
							ApplyAnimation(i, "Attractors", "Stepsit_out", 4.0, 0, 0, 0, 0, 0, 1);
							TogglePlayerControllable(i, 1);
				
							SetCameraBehindPlayer(i);
							SetPlayerHP(i, 20.0);
							
							CharacterInfo[i][pReanimationID] = 0;
						}
					}
					else
					{
						CharacterInfo[i][pReanimation] = 0;
						CharacterInfo[i][pReanimationID] = 0;
					}
				}
			}
			
			if(CharacterInfo[i][pGlod] <= 15)
				SetPlayerDrunkLevel(i, 8000);
			
			if(CharacterInfo[i][pCash] != GetPlayerMoney(i))
			{
				ResetPlayerMoney(i);
				GivePlayerMoney(i, CharacterInfo[i][pCash]);
			}
			
			if(CharacterInfo[i][pDrugsTime])
			{
				CharacterInfo[i][pDrugsTime] --;
				
				switch(CharacterInfo[i][pDrugs])
				{
					case DRUG_MARIHUANA:
					{
						SetPlayerWeather(i, 65);
						if(CharacterInfo[i][pGlod] > 15)
							SetPlayerDrunkLevel(i, 3000);
						
						if(CharacterInfo[i][pDrugsTime] == 120 || CharacterInfo[i][pDrugsTime] == 240 || CharacterInfo[i][pDrugsTime] == 360 || CharacterInfo[i][pDrugsTime] == 480)
						{
							if(CharacterInfo[i][pHealth]+10 > 100) SetPlayerHP(i, 100.0);
							else SetPlayerHP(i, CharacterInfo[i][pHealth]+10);
						}
					}
					case DRUG_KOKAINA:
						SetPlayerWeather(i, -53);
					case DRUG_HEROINA:
					{
						SetPlayerWeather(i, -66);
						if(CharacterInfo[i][pGlod] > 15)
							SetPlayerDrunkLevel(i, 5000);
					}
					case DRUG_LSD:
					{
						SetPlayerWeather(i, -107);
						if(CharacterInfo[i][pGlod] > 15)
							SetPlayerDrunkLevel(i, 5000);
					}
					case DRUG_ALKO:
						if(CharacterInfo[i][pGlod] > 15)
							SetPlayerDrunkLevel(i, 7000);
				}
				
				if(!CharacterInfo[i][pDrugsTime])
				{
					SetPlayerWeather(i, 2);
					CharacterInfo[i][pDrugs] = 0;
					if(CharacterInfo[i][pGlod] > 15)
						SetPlayerDrunkLevel(i, 0);
				}
			}
			
			if(CharacterInfo[i][pAJ])
			{
				new string[128];
				
				if(!IsPlayerInRangeOfPoint(i, 5.0, 154.1221, -1951.9156, 47.8750))
				{
					SetPlayerPos(i, 154.1221, -1951.9156, 47.8750);
					SetPlayerInterior(i, 0);
					SetPlayerVirtualWorld(i, 1000 + i);
				}
				
				CharacterInfo[i][pAJ] --;
				
				if(CharacterInfo[i][pAJ] > 60)
				{
					format(string, sizeof(string), "~r~AJ~w~: ~g~%d ~w~min.", CharacterInfo[i][pAJ]/60);
					GameTextForPlayer(i, string, 1000, 1);
				}
				else
				{
					format(string, sizeof(string), "~r~AJ~w~: ~g~%d ~w~sek.", CharacterInfo[i][pAJ]);
					GameTextForPlayer(i, string, 1000, 1);
				}
				if(CharacterInfo[i][pAJ] <= 0)
				{
					CharacterInfo[i][pAJ] = 0;
					SendClientMessage(i, COLOR_GREEN, "[AI] Czas AJ dobieg³ koñca. Popraw swoje zachowanie!");
					SavePlayerStats(i, SAVE_PLAYER_PENALTY);
					OnPlayerSpawn(i);
				}
			}
			
			if(CharacterInfo[i][pBlockNoGun])
			{
				CharacterInfo[i][pBlockNoGun] --;
				if(CharacterInfo[i][pBlockNoGun] <= 0)
				{
					CharacterInfo[i][pBlock] -= BLOCK_NOGUN;
					CharacterInfo[i][pBlockNoGun] = 0;
					SendClientMessage(i, COLOR_GREEN, "[AI] Czas blokady broni dobieg³ koñca. Popraw swoje zachowanie!");
					SavePlayerStats(i, SAVE_PLAYER_PENALTY);
				}
			}
			
			if(CharacterInfo[i][pDriverPenalty])
				CharacterInfo[i][pDriverPenalty] --;
			
			if(CharacterInfo[i][pBlockNoCar])
			{
				CharacterInfo[i][pBlockNoCar] --;
				if(CharacterInfo[i][pBlockNoCar] <= 0)
				{
					CharacterInfo[i][pBlock] -= BLOCK_NOCAR;
					CharacterInfo[i][pBlockNoCar] = 0;
					SendClientMessage(i, COLOR_GREEN, "[AI] Czas blokady prowadzenia pojazdow dobieg³ koñca. Popraw swoje zachowanie!");
					SavePlayerStats(i, SAVE_PLAYER_PENALTY);
				}
			}
			
			if(CharacterInfo[i][pBlockNoOOC])
			{
				CharacterInfo[i][pBlockNoOOC] --;
				if(CharacterInfo[i][pBlockNoOOC] <= 0)
				{
					CharacterInfo[i][pBlock] -= BLOCK_NOOOC;
					CharacterInfo[i][pBlockNoOOC] = 0;
					SendClientMessage(i, COLOR_GREEN, "[AI] Czas blokady czatów OOC dobieg³ koñca. Popraw swoje zachowanie!");
					SavePlayerStats(i, SAVE_PLAYER_PENALTY);
				}
			}
			
			if(CharacterInfo[i][pBlockNoRun])
			{
				CharacterInfo[i][pBlockNoRun] --;
				if(CharacterInfo[i][pBlockNoRun] <= 0)
				{
					CharacterInfo[i][pBlock] -= BLOCK_NORUN;
					CharacterInfo[i][pBlockNoRun] = 0;
					SendClientMessage(i, COLOR_GREEN, "[AI] Czas blokady biegania dobieg³ koñca. Popraw swoje zachowanie!");
					SavePlayerStats(i, SAVE_PLAYER_PENALTY);
				}
			}
			
			if(GetPlayerSpecialAction(i) == SPECIAL_ACTION_USEJETPACK && !CharacterInfo[i][pPenalty])
			{
				GivePenalty(i, -1, gettime(), PENALTY_KICK, 0, "Jetpack");
				CharacterInfo[i][pPenalty] = true;
				KickWithWait(i);
			}
			
			if(GetPlayerWeapon(i) && (!CharacterInfo[i][pHaveWeapon] || CharacterInfo[i][pWeaponID] != GetPlayerWeapon(i)) && GetPlayerWeapon(i) != 2 && GetPlayerWeapon(i) != 46 && !CharacterInfo[i][pBW] && !CharacterInfo[i][pWounded] && !CharacterInfo[i][pSpec] && !IsPlayerInAnyVehicle(i))
			{
				if(CharacterInfo[i][pWeaponCheatWarn])
				{
					if(!CharacterInfo[i][pPenalty])
					{
						new string[64],weapon[16];
						GetWeaponName(GetPlayerWeapon(i), weapon, sizeof(weapon));
						format(string,sizeof(string),"Weapon cheat: %s",weapon);
						
						GivePenalty(i, -1, gettime(), PENALTY_KICK, 0, string);
						CharacterInfo[i][pPenalty] = true;
						
						KickWithWait(i);
					}
				}
				else
					CharacterInfo[i][pWeaponCheatWarn]++;
			}
			else if(CharacterInfo[i][pWeaponCheatWarn] > 0)
				CharacterInfo[i][pWeaponCheatWarn]--;
			
			if(GetPlayerState(i) == PLAYER_STATE_DRIVER)
			{
				new vehid, vehuid, speed, Float:zuzycie, Float:hp, Float:x, Float:y, Float:z, Float:distance;
				vehid = GetPlayerVehicleID(i);
				vehuid = GetVehicleUID(vehid);
				speed = VehicleSpeed(vehid);
				
				if(VehicleInfo[vehuid][vEngine] && hasModelEngine(VehicleInfo[vehuid][vModel]))
				{
					if(VehicleInfo[vehuid][vFuel] > 0.0)
					{
						if(speed < 10)
							zuzycie += 0.002;
						else if(speed <= 30)
							zuzycie += 0.0025;
						else if(speed <= 60)
							zuzycie += 0.005;
						else if(speed <= 100)
							zuzycie += 0.0075;
						else if(speed <= 120)
							zuzycie += 0.01;
						else
							zuzycie += 0.0125;
						
						if(VehicleInfo[vehuid][vDistance] > 2000.0)
							zuzycie = zuzycie*1.2;
						
						if(IsSportVehicle(vehuid)) 
							VehicleInfo[vehuid][vFuel] -= zuzycie*1.5;
						else 
							VehicleInfo[vehuid][vFuel] -= zuzycie;
						
						zuzycie = 0;
					}
					
					GetVehicleHealth(vehid, hp);
					if(hp < 300.0)
					{
						VehicleInfo[vehuid][vHP]= 300.0;
						SetVehicleHealth(vehid, 300.0);
						hp = 300.0;
					}
					
					if(VehicleInfo[vehuid][vHP] > hp)
						VehicleInfo[vehuid][vHP] = hp;
					else
						SetVehicleHealth(vehid, VehicleInfo[vehuid][vHP]);
					
					GetVehiclePos(vehid, x, y, z);
					
					distance = floatsqroot(floatpower(floatabs(floatsub(x, VehiclePos[vehuid][0])), 2) + floatpower(floatabs(floatsub(y, VehiclePos[vehuid][1])),2) + floatpower(floatabs(floatsub(z, VehiclePos[vehuid][2])), 2));
					Tick[vehuid] += floatround(distance);
					
					if(Tick[vehuid] >= 110)
					{
						if(CharacterInfo[i][pTaxiPassenger] != INVALID_PLAYER_ID)
						{
							CharacterInfo[i][pTaxiDistance]++;
							new price= floatround(float(CharacterInfo[i][pTaxiDistance])*GetPVarFloat(i,"pTaxiPrice"));
							if(price>CharacterInfo[CharacterInfo[i][pTaxiPassenger]][pCash])
							{
								GameTextForPlayer(i, "~w~Gracz nie ma tylu pieniezdy.", 4000, 4);
								GameTextForPlayer(CharacterInfo[i][pTaxiPassenger], "~w~Nie masz tylu pieniezdy.", 4000, 4);
							}
							else
							{
								new string[48];
								
								format(string,sizeof(string),"~w~Koszt: %d~g~$",price);
								GameTextForPlayer(i, string, 4000, 4);
								GameTextForPlayer(CharacterInfo[i][pTaxiPassenger], string, 4000, 4);
							}
						}
						Tick[vehuid] = 0;
						VehicleInfo[vehuid][vDistance] += 0.1;
					}
					
					VehiclePos[vehuid][0] = x;
					VehiclePos[vehuid][1] = y;
					VehiclePos[vehuid][2] = z;

					if(hasModelEngine(VehicleInfo[vehuid][vModel]))
					{
						if(VehicleInfo[vehuid][vFuel] <= 0)
						{
							VehicleInfo[vehuid][vEngine] = false;
							ChangeVehicleEngineStatus(vehid, VehicleInfo[vehuid][vEngine]);
							VehicleInfo[vehuid][vFuel] = 0.0;
							
							SaveVehicle(vehuid, SAVE_VEH_BASIC);
						}
						else if((VehicleInfo[vehuid][vHP] < 600 && random(150) == 25) || VehicleInfo[vehuid][vHP]<320)
						{
							VehicleInfo[vehuid][vEngine] = false;
							ChangeVehicleEngineStatus(vehid, VehicleInfo[vehuid][vEngine]);
							
							new string[128];
							format(string, sizeof(string), "** Silnik w pojeŸdzie %s przesta³ pracowaæ z powodu uszkodzeñ.", GetVehicleModelName(VehicleInfo[vehuid][vModel]));
							
							cmd_do(i, string);
						}
					}
				}
			}
			
			/*if(CharacterInfo[i][pHaveWeapon])
			{
				if(GetPlayerWeapon(i) == 0 && !IsPlayerAttachedObjectSlotUsed(i, SLOT_WEAPON))
				{
					new weapon_id = CharacterInfo[i][pWeaponID];
					switch(GetWeaponType(weapon_id))
					{
						case WEAPON_TYPE_LIGHT:
							SetPlayerAttachedObject(i, SLOT_WEAPON, WeaponModel[weapon_id], 8, 0.0, -0.1, 0.15, -100.0, 0.0, 0.0);
						case WEAPON_TYPE_MELEE:
							SetPlayerAttachedObject(i, SLOT_WEAPON, WeaponModel[weapon_id], 7, 0.0, 0.0, -0.18, 100.0, 45.0, 0.0);
						case WEAPON_TYPE_HEAVY:
							SetPlayerAttachedObject(i, SLOT_WEAPON, WeaponModel[weapon_id], 1, 0.08, 0.23, -0.158, -5.2, 18.6, 180.0);
						case WEAPON_TYPE_MELEE_BIG:
							SetPlayerAttachedObject(i, SLOT_WEAPON, WeaponModel[weapon_id], 1, 0.429, -0.131, -0.131, 0.0, -53.5, 180.0);
					}
				}
				else if(IsPlayerAttachedObjectSlotUsed(i, SLOT_WEAPON) && GetPlayerWeapon(i))
					RemovePlayerAttachedObject(i, SLOT_WEAPON);
			}*/

			if((CharacterInfo[i][pBlock] & BLOCK_NORUN || CharacterInfo[i][pHealth] <= 30) && !IsPlayerInAnyVehicle(i) && GetPlayerSpeed(i) >= 10.0)
			{
				if(GetPlayerAnimationIndex(i) != 1206)
				{
					ApplyAnimation(i, "PED", "KO_shot_front", 4.0, 0, 1, 1, 1, 0, 1);
					SetTimerEx("GetUpAfterFall", 1500, false, "i", i);
				}
			}
			
			UpdatePlayer3DTextNick(i);
			f_OnPlayerUpdate(i);
		}
	}
}

public TimerMinute()
{
	new string[128],Float:x,Float:y,Float:z;
	ForeachPlayer(i)
	{
		if(Logged[i] && !(CharacterInfo[i][pStatus] & STATUS_AFK))
		{
			if(DutyGroup[i])
			{
				if(GroupInfo[DutyGroup[i]][gType] == GROUP_WORKSHOP || GroupInfo[DutyGroup[i]][gType] == GROUP_TAXI || GroupInfo[DutyGroup[i]][gType] == GROUP_LOGISTIC || GroupInfo[DutyGroup[i]][gType] == GROUP_GYM || GroupInfo[DutyGroup[i]][gType] == GROUP_RESTAURANT || GroupInfo[DutyGroup[i]][gType] == GROUP_KASYNO || GroupInfo[DutyGroup[i]][gType] == GROUP_KLUB)
				{
					if(IsPlayerInAnyVehicle(i) && GroupInfo[DutyGroup[i]][gType] != GROUP_RESTAURANT && GroupInfo[DutyGroup[i]][gType] != GROUP_GYM && GroupInfo[DutyGroup[i]][gType] != GROUP_KASYNO && GroupInfo[DutyGroup[i]][gType] != GROUP_KLUB)
					{
						new vehid = GetPlayerVehicleID(i);
						new vehuid = GetVehicleUID(vehid);
						
						if(VehicleInfo[vehuid][vOwnerTyp] == OWNER_GROUP && VehicleInfo[vehuid][vOwner] == DutyGroup[i])
						{
							DutyGroupTime[i] +=60;
							MemberGroup[i][GetPlayerGroupSlot(i,DutyGroup[i])][GroupTime] = DutyGroupTime[i];
							if((DutyGroupTime[i]/60)%TIME_TO_SALARY == 0)
								GiveSalary(i,DutyGroup[i]);
						}
					}
					else if(PlayerDoor[i] && DoorsInfo[PlayerDoor[i]][dOwnerTyp] == OWNER_GROUP && DoorsInfo[PlayerDoor[i]][dOwner] == DutyGroup[i])
					{
						DutyGroupTime[i] +=60;
						MemberGroup[i][GetPlayerGroupSlot(i,DutyGroup[i])][GroupTime] = DutyGroupTime[i];
						if((DutyGroupTime[i]/60)%TIME_TO_SALARY == 0)
							GiveSalary(i,DutyGroup[i]);
					}
					else if(GroupInfo[DutyGroup[i]][gType] == GROUP_RESTAURANT || GroupInfo[DutyGroup[i]][gType] == GROUP_GYM || GroupInfo[DutyGroup[i]][gType] == GROUP_KASYNO)
					{
						new hours, minutes, second;
						MemberGroup[i][GetPlayerGroupSlot(i, DutyGroup[i])][GroupTime]=DutyGroupTime[i];
						ConvertSecondsToTime(MemberGroup[i][GetPlayerGroupSlot(i, DutyGroup[i])][GroupTime], hours, minutes, second);
						SendClientMessageFormat(i, GroupInfo[DutyGroup[i]][gColor], " » Zszed³eœ ze s³u¿by w grupie %s (%d). Przepracowa³eœ dziœ %dh, %dmin.", GroupInfo[DutyGroup[i]][gName], DutyGroup[i], hours, minutes);
						
						SaveMember(i, DutyGroup[i]);
						
						if(IsPlayerPremium(i)) CharacterInfo[i][pNickColor] = COLOR_PREMIUM;
						else CharacterInfo[i][pNickColor] = COLOR_USER;
						
						DutyGroup[i] = 0;
						DutyGroupTime[i] = 0;
						
						if(CharacterInfo[i][pTog] & TOG_STATUS)
						{
							PlayerTextDrawShow(i, TDEditor_PTD[i][6]);
							
							PlayerTextDrawHide(i, TDEditor_PTD[i][7]);
							PlayerTextDrawShow(i, TDEditor_PTD[i][8]);
						}
					}
				}
				else if(GroupInfo[DutyGroup[i]][gType] == GROUP_FUELSTATION)
				{
					new doorid = PlayerDoor[i];
					new stationid = GetPlayerStationID(i);
					if((doorid && DoorsInfo[doorid][dOwnerTyp]==OWNER_GROUP && DoorsInfo[doorid][dOwner]==DutyGroup[i]) || (stationid && StationInfo[stationid][sOwner] == DutyGroup[i]))
					{
						DutyGroupTime[i] +=60;
						MemberGroup[i][GetPlayerGroupSlot(i,DutyGroup[i])][GroupTime] = DutyGroupTime[i];
						if((DutyGroupTime[i]/60)%TIME_TO_SALARY == 0)
							GiveSalary(i,DutyGroup[i]);
					}
				}
				else
				{
					DutyGroupTime[i] +=60;
					MemberGroup[i][GetPlayerGroupSlot(i,DutyGroup[i])][GroupTime] = DutyGroupTime[i];
					if((DutyGroupTime[i]/60)%TIME_TO_SALARY == 0)
						GiveSalary(i,DutyGroup[i]);
				}
			}
			CharacterInfo[i][pMinutes] ++;
			
			if(CharacterInfo[i][pMinutes] > 59)
			{
				CharacterInfo[i][pMinutes] = 0;
				CharacterInfo[i][pHours] ++;
				
				SendClientMessage(i, -1, "|__________*Wyp³ata*__________|");
				
				new godzina;
				gettime(godzina);
				
				new payday = 500;
				new dodatek = CharacterInfo[i][pGlobalScore]/10;
				
				if(dodatek > 500)
					dodatek = 500;
				
				payday += dodatek;
				
				if(IsPlayerPremium(i)) 
					CharacterInfo[i][pGlobalScore] += 15;
				else 
					CharacterInfo[i][pGlobalScore] += 10;
				
				if(IsPlayerPremium(i))
				{
					format(string, sizeof(string), "{3232CD}*{ffffff} GameScore: {c4c4c4}+15 (%d){02AD38}", CharacterInfo[i][pGlobalScore]);
					SendClientMessage(i, COLOR_WHITE, string);
				}
				else
				{
					format(string, sizeof(string), "{3232CD}*{ffffff} GameScore: {c4c4c4}+10 (%d){02AD38}", CharacterInfo[i][pGlobalScore]);
					SendClientMessage(i, COLOR_WHITE, string);
				}
				
				if(CharacterInfo[i][pHotel])
				{
					format(string,sizeof(string), "{3232CD}*{ffffff} Op³ata za hotel: {c4c4c4}-$%d{02AD38}", SettingInfo[sHotelPrice]);
					SendClientMessage(i, COLOR_WHITE, string);
				}
				
				format(string, sizeof(string), "{3232CD}*{ffffff} Podatek: {c4c4c4}-$%d{02AD38}", SettingInfo[sTaxes]);
				SendClientMessage(i, COLOR_WHITE, string);
				format(string, sizeof(string), "{3232CD}*{ffffff} Ubezpieczenie: {c4c4c4}-$%d{02AD38}", SettingInfo[sInsurance]);
				SendClientMessage(i, COLOR_WHITE, string);
				
				if(CharacterInfo[i][pHotel]) payday = payday-SettingInfo[sHotelPrice]-SettingInfo[sInsurance]-SettingInfo[sTaxes];
				else payday = payday-SettingInfo[sInsurance]-SettingInfo[sTaxes];
				
				format(string, sizeof(string), "{3232CD}*{ffffff} Podsumowanie: {c4c4c4}$%d{02AD38}", payday);
				SendClientMessage(i, COLOR_WHITE, string);
				
				CharacterInfo[i][pCredit] += payday;
				
				ForeachEx(gid, MAX_GROUPS)
				{
					if(GroupInfo[gid][gType] == GROUP_MC)
					{
						GiveGroupCash(gid, SettingInfo[sInsurance]);
						break;
					}
				}
				
				ForeachEx(gid, MAX_GROUPS)
				{
					if(GroupInfo[gid][gType] == GROUP_GOV)
					{
						GiveGroupCash(gid, SettingInfo[sTaxes]);
						break;
					}
				}
				
				new strength = CharacterInfo[i][pStrength];
				
				if(CharacterInfo[i][pStrengthToday] < 5)
				{
					if(strength && CharacterInfo[i][pSuplement] != 3)
					{
						if(strength <= 250)
							CharacterInfo[i][pStrength]--;
						else if(strength <= 500)
							CharacterInfo[i][pStrength] -=2;
						else if(strength <= 750)
							CharacterInfo[i][pStrength] -=3;
						else
							CharacterInfo[i][pStrength] -=4;
					}
				}
				
				if(strength < 0)
					CharacterInfo[i][pStrength] = 0;
				
				SetPlayerScore(i, CharacterInfo[i][pGlobalScore]);
				
				if(CharacterInfo[i][pGlod] > 15)
				{
					if(!CharacterInfo[i][pAdmin])
						CharacterInfo[i][pGlod] -= 20;
					
					if(!(CharacterInfo[i][pTog] & TOG_GLOD))
					{
						SetPlayerProgressBarValue(i, FoodBar[i], CharacterInfo[i][pGlod]);
						UpdatePlayerProgressBar(i, FoodBar[i]);
					}
				}
				else
				{
					if(!CharacterInfo[i][pAdmin])
						CharacterInfo[i][pGlod] = 0;
					
					if(!(CharacterInfo[i][pTog] & TOG_GLOD))
					{
						SetPlayerProgressBarValue(i, FoodBar[i], CharacterInfo[i][pGlod]);
						UpdatePlayerProgressBar(i, FoodBar[i]);
					}
				}
				
				SavePlayerStats(i, SAVE_PLAYER_BASIC);
				SavePlayerStats(i, SAVE_PLAYER_GLOBAL);
			}
			
			if(CharacterInfo[i][pJailTime] > gettime())
			{
				new dooruid = CharacterInfo[i][pJail];
				
				if(!IsPlayerInRangeOfPoint(i, 5.0, DoorsInfo[dooruid][dExitX], DoorsInfo[dooruid][dExitY], DoorsInfo[dooruid][dExitZ]))
				{
					SetPlayerPos(i, DoorsInfo[dooruid][dExitX], DoorsInfo[dooruid][dExitY], DoorsInfo[dooruid][dExitZ]);
					SetPlayerInterior(i, DoorsInfo[dooruid][dExitInt]);
					SetPlayerVirtualWorld(i, DoorsInfo[dooruid][dExitVW]);
				}
				
				if(CharacterInfo[i][pJailTime] > gettime())
				{
					if((CharacterInfo[i][pJailTime]-gettime())/60 < 60)
						format(string, sizeof(string), "~r~ARESZT~w~: ~g~%d ~w~min.", (CharacterInfo[i][pJailTime]-gettime())/60);
					else
						format(string, sizeof(string), "~r~ARESZT~w~: ~g~%d ~w~godzin/y.", (CharacterInfo[i][pJailTime]-gettime())/60/60);
					GameTextForPlayer(i, string, 1000, 1);
				}
				else
				{
					CharacterInfo[i][pJailTime] = 0;
					CharacterInfo[i][pJail] = 0;
					msg_info(i, "Czas przetrzymania dobieg³ koñca.");
					SavePlayerStats(i, SAVE_PLAYER_JAIL);
					OnPlayerSpawn(i);
				}
			}
			
			GetPlayerPos(i, x, y, z);
			if(CharacterInfo[i][pPrevPos][0] == x && CharacterInfo[i][pPrevPos][1] == y)
			{
				CharacterInfo[i][pAFKWarn]++;
				if(CharacterInfo[i][pAFKWarn] == 3 && !CharacterInfo[i][pGymType])
					SendClientMessage(i, COLOR_GREY, "Anty AFK: Jesteœ nieaktywny od 3 minut! Przy 5 minutach uruchomi siê automatycznie AFK.");
				else if(CharacterInfo[i][pAFKWarn] == 3 && CharacterInfo[i][pGymType])
					SendClientMessage(i, COLOR_GREY, "Anty AFK: Jesteœ nieaktywny od 3 minut! Przy 10 minutach uruchomi siê automatycznie AFK.");
				else if(CharacterInfo[i][pAFKWarn] == 5 && !CharacterInfo[i][pGymType])
				{
					if(!(CharacterInfo[i][pStatus] & STATUS_AFK))
					{
						CharacterInfo[i][pStatus] += STATUS_AFK;
						playerLog(i,"AFK","%s jest AFK",PlayerName(i));
					}
					new hour,minute;
					gettime(hour, minute);
					
					CharacterInfo[i][pAFKg] = hour;
					CharacterInfo[i][pAFKm] = minute;

					TogglePlayerControllable(i, 0);
					SendClientMessage(i, COLOR_GREY, "Jesteœ teraz AFK.");
				}
				else if(CharacterInfo[i][pAFKWarn] == 10)
				{
					if(!(CharacterInfo[i][pStatus] & STATUS_AFK))
					{
						CharacterInfo[i][pStatus] += STATUS_AFK;
						playerLog(i,"AFK","%s jest AFK",PlayerName(i));
					}
					TogglePlayerControllable(i, 0);
					SendClientMessage(i, COLOR_GREY,"Jesteœ teraz AFK. Aby wy³¹czyæ kliknij LPM lub wpisz /afk.");
				}
			}
			else
			{
				CharacterInfo[i][pPrevPos][0]=x;
				CharacterInfo[i][pPrevPos][1]=y;
				CharacterInfo[i][pPrevPos][2]=z;
				CharacterInfo[i][pAFKWarn]=0;
			}
		}
	}
	
	new vehid;
	for(new i=1, vPool=GetVehiclePoolSize(); i<=vPool; i++)
	{
		vehid = VehicleUIDs[i];
		if(vehid && VehicleInfo[vehid][vEngine] && hasModelEngine(VehicleInfo[vehid][vModel]))
		{
			if(VehicleInfo[vehid][vFuel] > 0.0)
			{
				if(IsSportVehicle(vehid)) VehicleInfo[vehid][vFuel] -= 0.3;
				else VehicleInfo[vehid][vFuel] -= 0.2;
				
				if(VehicleInfo[vehid][vFuel] <= 0.0)
				{
					VehicleInfo[vehid][vFuel] = 0.0;

					VehicleInfo[vehid][vEngine] = false;
					ChangeVehicleEngineStatus(i, VehicleInfo[vehid][vEngine]);				
					SaveVehicle(vehid, SAVE_VEH_BASIC);
				}
			}
		}
	}
	
	static godzina, minuta;
	gettime(godzina, minuta);
	
	if(minuta == 0 || (minuta <= 2 && gettime() - SERVER_LAST_TIMER_HOUR > 4000))
		TimerHour();
	
	ForeachEx(i, MAX_PLANTS)
	{
		if(PlantInfo[i][plantUID] && PlantInfo[i][plantTime])
		{
			PlantInfo[i][plantTime]--;
			
			if(PlantInfo[i][plantTime] > 0)
				format(string, sizeof(string), "Krzak marihuany:{636363} %d minut.", PlantInfo[i][plantTime]);
			else
				format(string, sizeof(string), "Krzak marihuany:{636363} gotowy do zebrania.\n(/zbierz)");
			
			UpdateDynamic3DTextLabelText(PlantInfo[i][planttext], 0x08A800FF, string);
		}
	}
}

public TimerHour()
{
	new godzina, minuta;
	gettime(godzina, minuta);
	SetWorldTime(godzina + 2);
	SERVER_TIME = godzina;
	SERVER_LAST_TIMER_HOUR = gettime();
	
	if(godzina == 4 || ((godzina==5 || godzina==6) && gettime()-SERVER_LAST_RESTART>10000))
	{
		SendClientMessageToAll(COLOR_RED, "[RESTART] Automatyczny restart serwera za 15 sekund!");
		SetTimer("DailyRestart", 15000, false);
	}
	LoadSettings();

	if(godzina >= 17 && godzina < 22 && !SettingInfo[sGovBots])
		SettingInfo[sGovBots] = true;
	
	ForeachEx(i, MAX_GROUPS)
		if(GroupInfo[i][gType] == GROUP_LOGISTIC && GroupInfo[i][gTransportTowary] < 4)
			GroupInfo[i][gTransportTowary] = 4;
	
	ForeachEx(i, MAX_PLANTS)
		if(PlantInfo[i][plantUID])
			mysql_query_format("UPDATE `srv_plants` SET `time` = '%d' WHERE `UID` = '%d' LIMIT 1", PlantInfo[i][plantTime], i);
}