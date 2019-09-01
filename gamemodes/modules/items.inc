forward StworzPrzedmiot(ownertyp, owner, nazwa[], type, value1, value2, ilosc);
forward ListPlayerItemsForPlayer(playerid, playerid2);
forward ListNearItems(playerid);
forward OnPlayerUseItem(playerid, uid);
forward OnPlayerDropItem(playerid, uid);
forward OnPlayerPickItem(playerid, uid);
forward DeleteItem(uid);
forward PlayerHaveItemType(playerid, type);
forward PlantSeed(playerid);

public PlayerHaveItemType(playerid, type)
{
	ForeachEx(i,_ITEM_COUNT)
		if(ItemInfo[i][iOwnerTyp] == OWNER_PLAYER && ItemInfo[i][iOwner] == CharacterInfo[playerid][pUID] && ItemInfo[i][iType] == type)
			return i;
	
	return false;
}

public StworzPrzedmiot(ownertyp, owner, nazwa[], type, value1, value2, ilosc)
{
	new uid;
	
	ForeachEx(i, MAX_ITEMS)
	{
		if(ItemInfo[i][iUID] == 0 && i != 0)
		{
			uid = i;
			break;
		}
	}
	if(uid + 1 > _ITEM_COUNT)
		_ITEM_COUNT = uid + 1;
	if(type == ITEM_TYPE_TELEFON)
	{
		if(value1 > 99 && value1 < 1000)
		{
			if(IsPhoneNumberUsed(value1))
			{
				new number;
				do{
					number = random(899998)+100001;
				}while(IsPhoneNumberUsed(number));

				value1 = number;
			}
		}
		else
		{
			new number;
			do{
				number = random(899998)+100001;
			}while(IsPhoneNumberUsed(number));

			value1 = number;
		}
	}
	
	new query[512];
	format(query, sizeof(query), "INSERT INTO `srv_items` (`UID`, `name`, `type`, `value1`, `value2`, `ownertyp`, `owner`, `ilosc`) VALUES ('%d', '%s', '%d', '%d', '%d', '%d', '%d', '%d')", uid, nazwa, type, value1, value2, ownertyp, owner, ilosc);
	mysql_query(query);
	
	ItemInfo[uid][iUID] = uid;
	format(ItemInfo[uid][iName],32,"%s",nazwa);
	ItemInfo[uid][iType] = type;
	ItemInfo[uid][iValue1] = value1;
	ItemInfo[uid][iValue2] = value2;
	ItemInfo[uid][iUsed] = 0;
	ItemInfo[uid][iOwnerTyp] = ownertyp;
	ItemInfo[uid][iOwner] = owner;
	ItemInfo[uid][iIlosc] = ilosc;
	ItemInfo[uid][iPrice] = 0;
	ItemInfo[uid][iPosx] = 
	ItemInfo[uid][iPosy] = 
	ItemInfo[uid][iPosz] = 0.0;
	ItemInfo[uid][iVW] = 0;
	
	return uid;
}

public ListPlayerItemsForPlayer(playerid, playerid2)
{
	new list[2048];
	
	format(list, sizeof(list), "UID\tNazwa\tWartoœæ 1\tWartoœæ 2");
	
	ForeachEx(i, _ITEM_COUNT)
	{
		if(ItemInfo[i][iUID])
		{
			if(ItemInfo[i][iOwnerTyp] == OWNER_PLAYER && ItemInfo[i][iOwner] == CharacterInfo[playerid2][pUID])
			{
				if(ItemInfo[i][iUsed]) format(list, sizeof(list), "%s\n%d\t{02AD38}%s\t%d\t%d", list, ItemInfo[i][iUID], ItemInfo[i][iName], ItemInfo[i][iValue1], ItemInfo[i][iValue2]);
				else format(list, sizeof(list), "%s\n%d\t{878A87}%s\t%d\t%d", list, ItemInfo[i][iUID], ItemInfo[i][iName], ItemInfo[i][iValue1], ItemInfo[i][iValue2]);
			}
		}
	}
	
	if(playerid == playerid2)
	{
		if(strlen(list) > 40) ShowPlayerDialog(playerid, D_ITEM, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » lista przedmiotów", list, "Opcje", "Zamknij");
		else Tip(playerid, 3, "Nie posiadasz przedmiotow.");
	}
	else
	{
		if(strlen(list) > 40) ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » lista przedmiotów", list, "Zamknij", "");
		else SendClientMessage(playerid, COLOR_RED, "[INFO] Gracz nie posiada przedmiotów.");
	}
	
	return 1;
}

public OnPlayerUseItem(playerid, uid)
{
	if(ItemInfo[uid][iOwner] != CharacterInfo[playerid][pUID])
		return msg_error(playerid,"Wybrany przedmiot nie jest Twoj¹ w³asnoœci¹.");
	if(CharacterInfo[playerid][pBW] || CharacterInfo[playerid][pWounded])
		return msg_error(playerid,"Nie mo¿esz u¿ywaæ przedmiotów podczas BW.");
	
	if(GetPlayerState(playerid)==PLAYER_STATE_SPECTATING)
		return msg_error(playerid,"Nie mo¿esz teraz tego zrobiæ");
	
	new type = ItemInfo[uid][iType];
	
	if(type == ITEM_TYPE_BRON)
	{
		new ammo = ItemInfo[uid][iValue2];
		
		if(!ItemInfo[uid][iUsed])
		{
			if(CharacterInfo[playerid][pHaveWeapon])
				return msg_error(playerid,"Masz ju¿ aktywn¹ jedn¹ broñ.");
			
			if(CharacterInfo[playerid][pStatus] & STATUS_KAJDANKI || CharacterInfo[playerid][pStatus] & STATUS_KNEBEL || CharacterInfo[playerid][pStatus] & STATUS_ZWIAZANY || CharacterInfo[playerid][pStatus] & STATUS_CIAGNIETY || CharacterInfo[playerid][pBW] || CharacterInfo[playerid][pWounded])
				return msg_error(playerid,"Nie mo¿esz teraz tego zrobiæ.");
			
			if(CharacterInfo[playerid][pBlock] & BLOCK_NOGUN)
				return msg_error(playerid,"Nie mo¿esz wyci¹gn¹æ broni posiadaj¹c aktywn¹ blokadê.");
			
			new weapon = ItemInfo[uid][iValue1];
			
			if(!(IsPlayerInGroupType(playerid, GROUP_PD) || IsPlayerInGroupType(playerid, GROUP_FBI) || IsPlayerInGroupType(playerid, GROUP_MILITARY) || IsPlayerInCriminalGroup(playerid)))
			{
				if(!(weapon < 16 || weapon == 22 || weapon == 23 || weapon == 25 || weapon == 24 || weapon == 28 || weapon == 32 || weapon == 41 || weapon == 42 || weapon == 43))
					return msg_error(playerid, "Nie posiadasz skryptu pozwalaj¹cego na u¿ywanie takowej broni.");
			}
			
			if(ammo <= 0 && weapon > 18)
				return msg_error(playerid,"W wybranej broni nie znajduje siê odpowiednia iloœæ amunicji.");
			
			ResetPlayerWeapons(playerid);
			
			CharacterInfo[playerid][pHaveWeapon] = true;
			
			GivePlayerWeapon(playerid, weapon, ammo);
			
			new query[128];
			format(query, sizeof(query), "UPDATE `srv_items` SET `used` = 1 WHERE `uid` = '%d' LIMIT 1", uid);
			mysql_query(query);
			
			ItemInfo[uid][iUsed] = 1;
			
			CharacterInfo[playerid][pWeaponAmmo] = ammo;
			CharacterInfo[playerid][pWeaponID] = weapon;
			CharacterInfo[playerid][pWeaponUID] = uid;
		}
		else
			HidePlayerWeapons(playerid);
	}
	else if(type == ITEM_TYPE_TELEFON)
	{
		if(!CharacterInfo[playerid][pPhone])
		{
			CharacterInfo[playerid][pPhone] = uid;
			
			new query[128];
			format(query, sizeof(query), "UPDATE `srv_items` SET `used` = 1 WHERE `uid` = '%d' LIMIT 1", uid);
			mysql_query(query);
			
			ItemInfo[uid][iUsed] = 1;
			
			msg_infoFormat(playerid, 64, "W³¹czy³eœ telefon o numerze: %d", ItemInfo[uid][iValue1]);
		}
		else if(CharacterInfo[playerid][pPhone] == uid)
		{
			if(Rozmawia[playerid] || RozmawiaZ[playerid] != INVALID_PLAYER_ID) return 1;
		
			CharacterInfo[playerid][pPhone] = 0;
			
			new query[128];
			format(query, sizeof(query), "UPDATE `srv_items` SET `used` = 0 WHERE `uid` = '%d' LIMIT 1", uid);
			mysql_query(query);
			
			ItemInfo[uid][iUsed] = 0;
			
			msg_infoFormat(playerid, 64, "Wy³¹czy³eœ telefon o numerze: %d", ItemInfo[uid][iValue1]);
		}
		else
			msg_error(playerid,"Masz ju¿ aktywny jeden telefon.");
		
		SavePlayerStats(playerid,SAVE_PLAYER_OPTION);
	}
	else if(type == ITEM_TYPE_MASKA)
	{
		if(CharacterInfo[playerid][pMask])
		{
			if(ItemInfo[uid][iUsed])
				ItemInfo[uid][iUsed] = 0;
			else
				return msg_error(playerid, "Masz ju¿ za³o¿on¹ inn¹ maskê.");
			
			if(CharacterInfo[playerid][pMaskObj])
			{
				RemovePlayerAttachedObject(playerid, SLOT_MASK);
				CharacterInfo[playerid][pAttached][SLOT_MASK] = 0;
				
				CharacterInfo[playerid][pMaskObj] = false;
			}
			
			CharacterInfo[playerid][pMask] = false;
			SendClientMessage(playerid, COLOR_RED, "Zdj¹³eœ maskê, Twój nick jest widoczny.");
			SetPlayerName(playerid, LoadPlayerName(CharacterInfo[playerid][pUID], true));
		}
		else
		{
			if(ItemInfo[uid][iValue1])
			{
				SetPVarInt(playerid, "MaskaUID", uid);
				ShowPlayerDialog(playerid, D_MASKA_OBJ, DIALOG_STYLE_MSGBOX, DEF_NAME" » obiekt maski", "Czy chcesz na³o¿yæ na siebie obiekt maski?", "Tak", "Nie");
			}
			else
			{
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
			}
		}
	}
	else if(type == ITEM_TYPE_JEDZENIE)
	{
		new food = ItemInfo[uid][iValue1];
		
		if(CharacterInfo[playerid][pGlod] == 100 && food > 0)
			return msg_error(playerid,"Nie jesteœ g³odny.");
		else if(CharacterInfo[playerid][pGlod]+food > 100) CharacterInfo[playerid][pGlod] = 100;
		else CharacterInfo[playerid][pGlod] += food;
		
		if(CharacterInfo[playerid][pGlod] > 10) SetPlayerDrunkLevel(playerid, 0);
		
		SavePlayerStats(playerid, SAVE_PLAYER_BASIC);
		
		SetPlayerProgressBarValue(playerid, FoodBar[playerid], CharacterInfo[playerid][pGlod]);
		UpdatePlayerProgressBar(playerid, FoodBar[playerid]);
		
		DeleteItem(uid);
	}
	else if(type == ITEM_TYPE_KOSTKA)
		cmd_kostka(playerid, "");
	else if(type == ITEM_TYPE_KARTY)
		cmd_karty(playerid, "");
	else if(type == ITEM_TYPE_LEKARSTWO)
	{
		new Float:lek = float(ItemInfo[uid][iValue1]);
		new string[64];
		
		if(CharacterInfo[playerid][pDamageTook])
			return msg_info(playerid, "Musi min¹æ minimum 5 minut od otrzymania obra¿en aby móc u¿yæ lekarstwa.");
		
		if(CharacterInfo[playerid][pHealth] < 50.0)
			return msg_error(playerid,"Twój stan jest zbyt powa¿ny, udaj siê do szpitala.");
		
		else if(CharacterInfo[playerid][pHealth] == 100.0)
			return msg_error(playerid,"Masz pe³ne ¿ycie, nie mo¿esz u¿yæ lekarstwa.");
		
		else if(CharacterInfo[playerid][pHealth]+lek >= 100.0) SetPlayerHP(playerid, 100.0);
		else SetPlayerHP(playerid, CharacterInfo[playerid][pHealth]+lek);
		
		format(string, sizeof(string), "za¿ywa lek %s.", ItemInfo[uid][iName]);
		cmd_me(playerid, string);
		
		DeleteItem(uid);
	}
	else if(type == ITEM_TYPE_KAMIZELKA)
	{
		if(ItemInfo[uid][iUsed])
		{
			if(!CharacterInfo[playerid][pHaveArmor])
			{
				ItemInfo[uid][iUsed] = 0;
				return msg_error(playerid, "Nie posiadasz za³o¿onej kamizelki!");
			}
			
			new value = floatround(CharacterInfo[playerid][pArmor]);
			ItemInfo[uid][iValue1] = value;
			
			CharacterInfo[playerid][pArmor] = 0;
			SetPlayerArmour(playerid, 0);
			
			cmd_me(playerid, "œci¹ga kamizelkê kuloodporn¹.");
			CharacterInfo[playerid][pHaveArmor] = false;
			
			ItemInfo[uid][iUsed] = 0;
		}
		else
		{
			if(CharacterInfo[playerid][pHaveArmor])
				return msg_error(playerid, "Masz ju¿ za³o¿on¹ kamizelkê!");
			
			new value = ItemInfo[uid][iValue1];
			
			if(value < 16)
				return msg_error(playerid, "Nie mo¿esz ubraæ uszkodzonej kamizelki.");
			
			CharacterInfo[playerid][pArmor] = value;
			SetPlayerArmour(playerid, value);
			
			cmd_me(playerid, "zak³ada kamizelkê kuloodporn¹.");
			CharacterInfo[playerid][pHaveArmor] = true;
			
			ItemInfo[uid][iUsed] = 1;
		}
	}
	else if(type == ITEM_TYPE_ZEGAREK)
	{
		new hours, minutes;
		gettime(hours, minutes);
		
		cmd_me(playerid, "spogl¹da na zegarek.");
		new string[16];
		format(string,sizeof(string),"~w~%02d~r~:~w~%02d",hours,minutes);
		
		GameTextForPlayer(playerid, string, 5000, 1);
	}
	else if(type == ITEM_TYPE_PALIWO)
	{
		if(IsPlayerInAnyVehicle(playerid))
		{
			new paliwo = ItemInfo[uid][iValue1];
			new vehid = GetPlayerVehicleID(playerid);
			new vehuid = GetVehicleUID(vehid);
			
			if(VehicleInfo[vehuid][vEngine])
				return msg_error(playerid,"Silnik pojazdu nie mo¿e byæ uruchomiony.");
			
			if(VehicleInfo[vehuid][vFuel]+paliwo > GetVehicleMaxFuel(VehicleInfo[vehuid][vModel]))
				msg_error(playerid,"Zawartoœæ kanistra nie zmieœci siê w baku pojazdu.");
			else
			{
				VehicleInfo[vehuid][vFuel] += float(paliwo);
				SaveVehicle(vehuid, SAVE_VEH_BASIC);
				
				new string[256];
				format(string, sizeof(string), "dolewa paliwo za pomoc¹ kanistra.");
				cmd_me(playerid, string);
				
				DeleteItem(uid);
			}
		}
		else msg_info(playerid, "Aby u¿yc kanistra musisz znajdowaæ siê w pojeŸdzie.");
	}
	else if(type == ITEM_TYPE_PAPIEROSY)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
		if(ItemInfo[uid][iValue1] < 2)
			DeleteItem(uid);
		else
		{
			ItemInfo[uid][iValue1]--;
			new query[128];
			format(query, sizeof(query), "UPDATE `srv_items` SET `value1` = '%d' WHERE `uid` = '%d' LIMIT 1", ItemInfo[uid][iValue1], uid);
			mysql_query(query);
		}
	}
	else if(type == ITEM_TYPE_PIWO)
	{
		if(!CharacterInfo[playerid][pDrugs])
		{
			CharacterInfo[playerid][pDrugs] = DRUG_ALKO;
			
			PlayerOnDrug(playerid);
			SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DRINK_BEER);
			
			DeleteItem(uid);
		}
		else msg_info(playerid, "Jesteœ ju¿ pod wp³ywem narkotyku/alkoholu.");
	}
	else if(type == ITEM_TYPE_SEED)
	{
		new ilosc = ItemInfo[uid][iValue1];
		
		new plantid = PlantSeed(playerid);
		
		if(plantid == 0) 
		{
			return msg_error(playerid,"Osi¹gniêto limit roœlinek na serwerze");
		}
		
		if(ilosc-1 <= 0)
			return DeleteItem(uid);
		else
		{
			new query[128];
			format(query, sizeof(query), "UPDATE `srv_items` SET `value1` = '%d' WHERE `uid` = '%d' LIMIT 1", ilosc-1, uid);
			mysql_query(query);
			
			ItemInfo[uid][iValue1]--;
		}
	}
	else if(type == ITEM_TYPE_MARIHUANA)
	{
		if(!CharacterInfo[playerid][pDrugs])
		{
			new ilosc = ItemInfo[uid][iValue1];
			
			CharacterInfo[playerid][pDrugs] = DRUG_MARIHUANA;
			
			PlayerOnDrug(playerid);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
			
			if(ilosc-1 <= 0)
				return DeleteItem(uid);
			else
			{
				new query[128];
				format(query, sizeof(query), "UPDATE `srv_items` SET `value1` = '%d' WHERE `uid` = '%d' LIMIT 1", ilosc-1, uid);
				mysql_query(query);
				
				ItemInfo[uid][iValue1]--;
			}
		}
		else msg_info(playerid, "Jesteœ ju¿ pod wp³ywem narkotyku/alkoholu.");
	}
	else if(type == ITEM_TYPE_KOKAINA)
	{
		if(!CharacterInfo[playerid][pDrugs])
		{
			new ilosc = ItemInfo[uid][iValue1];
			
			CharacterInfo[playerid][pDrugs] = DRUG_KOKAINA;
			
			PlayerOnDrug(playerid);
			
			if(ilosc-1 <= 0)
				return DeleteItem(uid);
			else
			{
				new query[128];
				format(query, sizeof(query), "UPDATE `srv_items` SET `value1` = '%d' WHERE `uid` = '%d' LIMIT 1", ilosc-1, uid);
				mysql_query(query);
				
				ItemInfo[uid][iValue1]--;
			}
		}
		else msg_info(playerid, "Jesteœ ju¿ pod wp³ywem narkotyku/alkoholu.");
	}
	else if(type == ITEM_TYPE_HEROINA)
	{
		if(!CharacterInfo[playerid][pDrugs])
		{
			new ilosc = ItemInfo[uid][iValue1];
			
			CharacterInfo[playerid][pDrugs] = DRUG_HEROINA;
			
			PlayerOnDrug(playerid);
			
			if(ilosc-1 <= 0)
				return DeleteItem(uid);
			else
			{
				new query[128];
				format(query, sizeof(query), "UPDATE `srv_items` SET `value1` = '%d' WHERE `uid` = '%d' LIMIT 1", ilosc-1, uid);
				mysql_query(query);
				
				ItemInfo[uid][iValue1]--;
			}
		}
		else msg_info(playerid, "Jesteœ ju¿ pod wp³ywem narkotyku/alkoholu.");
	}
	else if(type == ITEM_TYPE_LSD)
	{
		if(!CharacterInfo[playerid][pDrugs])
		{
			new ilosc = ItemInfo[uid][iValue1];
			
			CharacterInfo[playerid][pDrugs] = DRUG_LSD;
			
			PlayerOnDrug(playerid);
			
			if(ilosc-1 <= 0)
				return DeleteItem(uid);
			else
			{
				new query[128];
				format(query, sizeof(query), "UPDATE `srv_items` SET `value1` = '%d' WHERE `uid` = '%d' LIMIT 1", ilosc-1, uid);
				mysql_query(query);
				
				ItemInfo[uid][iValue1]--;
			}
		}
		else msg_info(playerid, "Jesteœ ju¿ pod wp³ywem narkotyku/alkoholu.");
	}
	else if(type == ITEM_TYPE_SUPLEMENTY)
	{
		new val1 = ItemInfo[uid][iValue1];
		if(val1 > 0 && val1 < 4)
		{
			if(!CharacterInfo[playerid][pSuplement])
			{
				CharacterInfo[playerid][pSuplement] = val1;
				SavePlayerStats(playerid, SAVE_PLAYER_OPTION);
				msg_info(playerid, "U¿y³eœ suplement, jego efekt utrzymywaæ siê bêdzie do nocnego restartu (4 rano).");
				DeleteItem(uid);
			}
			else
				return msg_error(playerid, "U¿y³eœ ju¿ dzisiaj suplement, kolejny mo¿esz dopiero jutro.");
		}
		else
			return msg_error(playerid, "Przedmiot posiada b³êdn¹ wartoœæ.");
	}
	else if(type == ITEM_TYPE_BOOMBOX)
		cmd_boombox(playerid,"");
	else if(type == ITEM_TYPE_AMMO)
	{
		new val1 = ItemInfo[uid][iValue1];
		
		new list[128];
	
		format(list, sizeof(list), "UID\tNazwa\tWartoœæ 1\tWartoœæ 2");
	
		ForeachEx(i,_ITEM_COUNT)
			if(ItemInfo[i][iUID])
				if(ItemInfo[i][iOwnerTyp] == OWNER_PLAYER && ItemInfo[i][iOwner] == CharacterInfo[playerid][pUID] && ItemInfo[i][iType] == ITEM_TYPE_BRON && ItemInfo[i][iValue1] == val1 && !ItemInfo[i][iUsed])
					format(list, sizeof(list), "%s\n%d\t{878A87}%s\t%d\t%d", list, ItemInfo[i][iUID], ItemInfo[i][iName], ItemInfo[i][iValue1], ItemInfo[i][iValue2]);
		
		SetPVarInt(playerid, "ammouid", uid);
		
		if(strlen(list) > 37) ShowPlayerDialog(playerid, D_ADD_AMMO, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » uzupe³nianie amunicji", list, "Wybierz", "Zamknij");
		else SendClientMessage(playerid, COLOR_RED, "[INFO] Nie posiadasz odpowiedniej broni.");
	}
	else if(type == ITEM_TYPE_SILENCER)
	{
		new list[256];
		
		format(list, sizeof(list), "UID\tNazwa\tWartoœæ 1\tWartoœæ 2");
		
		ForeachEx(i,_ITEM_COUNT)
			if(ItemInfo[i][iUID])
				if(ItemInfo[i][iOwnerTyp] == OWNER_PLAYER && ItemInfo[i][iOwner] == CharacterInfo[playerid][pUID] && ItemInfo[i][iType] == ITEM_TYPE_BRON && ItemInfo[i][iValue1] == 22 && !ItemInfo[i][iUsed])
					format(list, sizeof(list), "%s\n%d\t{878A87}%s\t%d\t%d", list, ItemInfo[i][iUID], ItemInfo[i][iName], ItemInfo[i][iValue1], ItemInfo[i][iValue2]);
		
		SetPVarInt(playerid, "siluid", uid);
		
		if(strlen(list) > 37) ShowPlayerDialog(playerid, D_SILENCER, DIALOG_STYLE_TABLIST_HEADERS, DEF_NAME" » montowanie t³umika", list, "Wybierz", "Zamknij");
		else msg_error(playerid, "Nie posiadasz odpowiedniej broni.");
	}
	else if(type == ITEM_TYPE_ATTACHED)
	{
		if(ItemInfo[uid][iUsed])
		{
			new query[128], index;
			format(query, sizeof(query), "SELECT `ind` FROM `srv_attached` WHERE `UID`='%d'", ItemInfo[uid][iUID]);
			mysql_query(query);
			mysql_store_result();
			if(mysql_num_rows())
			{
				mysql_fetch_row_format(query);
				index=strval(query);
				RemovePlayerAttachedObject(playerid, index);
				CharacterInfo[playerid][pAttached][index] = 0;
				Tip(playerid, 3, "Obiekt zdjety.");
			}
			
			ItemInfo[uid][iUsed] = 0;

			mysql_free_result();
		}
		else
		{
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
				return msg_error(playerid, "Nie mo¿esz za³o¿yæ wiêcej obiektów doczepianych.");

			new query[192], Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ;
			format(query, sizeof(query), "SELECT `x`, `y`, `z`, `rx`, `ry`, `rz`, `sx`, `sy`, `sz` FROM `srv_attached` WHERE `UID`='%d'", uid);
			fScaleX=fScaleY=fScaleZ=1.0;
			mysql_query(query);
			mysql_store_result();
			if(mysql_num_rows())
			{
				mysql_fetch_row_format(query);
				sscanf(query,"p<|>fffffffff", fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
				mysql_free_result();
				format(query, sizeof(query), "UPDATE `srv_attached` SET `ind` = '%d' WHERE `UID` = '%d'", index, uid);
				mysql_query(query);
			}
			else
			{
				mysql_free_result();
				format(query,sizeof(query),"INSERT INTO `srv_attached` VALUES ('%d', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f')", uid, index, ItemInfo[uid][iValue1], ItemInfo[uid][iValue2], 
				fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);	
				mysql_query(query);
			}

			CharacterInfo[playerid][pAttached][index] = uid;
			ItemInfo[uid][iUsed] = 1;
			SetPlayerAttachedObject(playerid, index, ItemInfo[uid][iValue1], ItemInfo[uid][iValue2], fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
			EditAttachedObject(playerid, index);
			return 1;
		}
	}
	else if(type == ITEM_TYPE_REPAIRKIT)
	{
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			return msg_error(playerid, "Nie jesteœ kierowc¹ w pojezdzie.");
		
		new vehid = GetPlayerVehicleID(playerid);
		new vehuid = GetVehicleUID(vehid);
		
		if(VehicleInfo[vehuid][vEngine])
			return msg_error(playerid,"Silnik pojazdu nie mo¿e byæ uruchomiony.");
		
		if(VehicleInfo[vehuid][vHP] >= ((float(GetVehicleMaxHP(VehicleInfo[vehuid][vModel])))/10)*4)
			return msg_error(playerid, "Nie mo¿esz naprawiæ swojego pojazdu (zestaw dzia³a tylko na pojazdy < 40% HP. JedŸ do warsztatu!");
		
		if(float(ItemInfo[uid][iValue1])+VehicleInfo[vehuid][vHP] >= float(GetVehicleMaxHP(VehicleInfo[vehuid][vModel])))
		{
			VehicleInfo[vehuid][vHP] = float(GetVehicleMaxHP(VehicleInfo[vehuid][vModel]));
			SetVehicleHealth(VehicleInfo[vehuid][vSAMPID], VehicleInfo[vehuid][vHP]);
		}
		else
		{
			VehicleInfo[vehuid][vHP] += float(ItemInfo[uid][iValue1]);
			SetVehicleHealth(VehicleInfo[vehuid][vSAMPID], VehicleInfo[vehuid][vHP]);
		}
		
		DeleteItem(uid);
		
		cmd_me(playerid, "naprawi³ swój pojazd za pomoc¹ zestawu naprawczego.");
	}
    else if(type == ITEM_TYPE_CLOTH)
    {
        new skin = CharacterInfo[playerid][pSkin];
        CharacterInfo[playerid][pSkin] = ItemInfo[uid][iValue1];
        SetPlayerSkin(playerid, ItemInfo[uid][iValue1]);
        
        new sql[256];
        format(sql, sizeof(sql), "UPDATE `srv_characters` SET `skin` = '%d' WHERE `player_uid` = '%d' LIMIT 1", CharacterInfo[playerid][pSkin], CharacterInfo[playerid][pUID]);
        mysql_query(sql);
		
		if(skin > 0 && skin < 320)
		{
			ItemInfo[uid][iValue1] = skin;
			new name[32];
			format(name, sizeof(name), "Ubranie (%d)", skin);
			
			ItemInfo[uid][iName] = name;
			
			format(sql, sizeof(sql), "UPDATE `srv_items` SET `name` = '%s', `value1` = '%d' WHERE `uid` = '%d' LIMIT 1", ItemInfo[uid][iName], ItemInfo[uid][iValue1], uid);
			mysql_query(sql);
		}
        
        cmd_me(playerid, "przebiera siê.");
    }

	return 1;
}

public OnPlayerDropItem(playerid, uid)
{
	new string[170];
	if(ItemInfo[uid][iOwner]!=CharacterInfo[playerid][pUID])
		return 1;
	
	if(ItemInfo[uid][iUsed])
		return msg_error(playerid,"Nie mo¿esz od³o¿yæ przedmiotu, którego u¿ywasz.");
	
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		new vehid = GetPlayerVehicleID(playerid);
		new vehuid = GetVehicleUID(vehid);
		
		if(!hasModelEngine(VehicleInfo[vehuid][vModel]))
			return msg_error(playerid, "Nie mo¿esz odk³adaæ przedmiotów w tym pojeŸdzie.");
		
		if(!CanMove(playerid))
			return msg_error(playerid, "Nie mo¿esz aktualnie u¿yæ tej komendy");
		
		new query[128];
		format(query, sizeof(query), "SELECT * FROM `srv_items` WHERE `ownertyp` = '%d' AND `owner` = '%d'", OWNER_VEHICLE, vehuid);
		mysql_query(query);
		mysql_store_result();
		
		if(mysql_num_rows() > 4)
		{
			SendClientMessage(playerid, COLOR_RED, "Nie mo¿esz od³o¿yæ w pojezdzie wiêcej przedmiotów (max 5). SprawdŸ /bagaznik.");
			mysql_free_result();
			return 1;
		}
		
		mysql_free_result();
		
		cmd_me(playerid, "odk³ada przedmiot w pojezdzie.");
		
		format(query, sizeof(query), "UPDATE `srv_items` SET `ownertyp` = '%d', `owner` = '%d' WHERE `UID` = '%d' LIMIT 1", OWNER_VEHICLE, vehuid, uid);
		mysql_query(query);
		
		ItemInfo[uid][iOwnerTyp] = OWNER_VEHICLE;
		ItemInfo[uid][iOwner] = vehuid;
		log("%s[player:%d] odklada %s[item:%d] w [veh:%d]",PlayerName3(playerid),CharacterInfo[playerid][pUID],ItemInfo[uid][iName],uid,vehuid);
	}
	else
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_PASSENGER)
			return msg_error(playerid, "Nie mo¿esz aktualnie odk³adaæ ani podnosiæ ¿adnych przedmiotów (jesteœ pasa¿erem).");
	
		new Float:Pos[3], vw;
		
		GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
		vw = GetPlayerVirtualWorld(playerid);

		format(string, sizeof(string), "* %s odk³ada przedmiot %s na ziemie.",PlayerName2(playerid), ItemInfo[uid][iName]);
		SendWrappedMessageToPlayerRange(playerid, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, string, 10);
		
		ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 1);
		
		new query[256];
		format(query, sizeof(query), "UPDATE `srv_items` SET `posx` = '%f', `posy` = '%f', `posz` = '%f', `ownertyp` = '%d', `owner` = '0', `world` = '%d' WHERE `UID` = '%d' LIMIT 1", Pos[0], Pos[1], Pos[2], OWNER_NONE, vw, uid);
		mysql_query(query);
		
		log("%s[player:%d] odklada %s[item:%d]",PlayerName3(playerid),CharacterInfo[playerid][pUID],ItemInfo[uid][iName],uid);
		
		ItemInfo[uid][iPosx] = Pos[0];
		ItemInfo[uid][iPosy] = Pos[1];
		ItemInfo[uid][iPosz] = Pos[2];
		ItemInfo[uid][iOwnerTyp] = OWNER_NONE;
		ItemInfo[uid][iOwner] = 0;
		ItemInfo[uid][iVW] = vw;
		
		format(string, sizeof(string), "%s (UID: %d)", ItemInfo[uid][iName], ItemInfo[uid][iUID]);
		
		ItemInfo[uid][iDroppedInfo] = Create3DTextLabel(string, COLOR_WHITE, ItemInfo[uid][iPosx], ItemInfo[uid][iPosy], ItemInfo[uid][iPosz]-0.8, 7.0, ItemInfo[uid][iVW], 1);
	}
	return 1;
}

public OnPlayerPickItem(playerid, uid)
{
	if(CharacterInfo[playerid][pStatus] & STATUS_AFK)
		return msg_error(playerid,"Nie mo¿esz skorzystaæ z tej komendy gdy jesteœ AFK.");
	
	if(ItemInfo[uid][iOwnerTyp] == OWNER_NONE || ItemInfo[uid][iOwnerTyp] == OWNER_VEHICLE)
	{
		new string[128];
		
		if(ItemInfo[uid][iOwnerTyp] == OWNER_VEHICLE)
		{
			format(string, sizeof(string), "wyci¹ga przedmiot z pojazdu.", ItemInfo[uid][iName]);
			log("%s[player:%d][gid:%d] podnosi %s[item:%d] z [veh:%d]",PlayerName3(playerid),CharacterInfo[playerid][pUID],CharacterInfo[playerid][pGID],ItemInfo[uid][iName],uid,ItemInfo[uid][iOwner]);
		}
		else
		{
			format(string, sizeof(string), "podnosi przedmiot %s.", ItemInfo[uid][iName]);
			log("%s[player:%d][gid:%d] podnosi %s[item:%d]",PlayerName3(playerid),CharacterInfo[playerid][pUID],CharacterInfo[playerid][pGID],ItemInfo[uid][iName],uid);
		}
		
		cmd_me(playerid, string);
		
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 1);
		
		new query[128];
		format(query, sizeof(query), "UPDATE `srv_items` SET `ownertyp` = '%d', `owner` = '%d' WHERE `UID` = '%d' LIMIT 1", OWNER_PLAYER, CharacterInfo[playerid][pUID], uid);
		mysql_query(query);
		
		ItemInfo[uid][iOwnerTyp] = OWNER_PLAYER;
		ItemInfo[uid][iOwner] = CharacterInfo[playerid][pUID];
		
		Delete3DTextLabel(ItemInfo[uid][iDroppedInfo]);
	}
	
	return 1;
}

public ListNearItems(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		new vehid = GetPlayerVehicleID(playerid);
		new vehuid = GetVehicleUID(vehid);
		
		if(!IsOwnerVehicle(playerid, vehuid) && (VehicleInfo[vehuid][vLocked] || VehicleInfo[vehuid][vOwnerTyp] != OWNER_PLAYER))
			return msg_error(playerid, "Pojazd jest zamkniêty a ty nie jesteœ jego w³aœcicielem - nie mo¿esz wyci¹gaæ przedmiotów.");
		
		new list[2048];
		
		ForeachEx(i,_ITEM_COUNT)
			if(ItemInfo[i][iOwnerTyp] == OWNER_VEHICLE && ItemInfo[i][iOwner] == vehuid)
				format(list, sizeof(list), "%s\n{c8c8c8}%3d:\t{878A87}%s", list, ItemInfo[i][iUID], ItemInfo[i][iName]);
		
		if(strlen(list) > 2) ShowPlayerDialog(playerid, D_ITEM_PICK, DIALOG_STYLE_LIST, DEF_NAME" » przedmioty w pojezdzie", list, "Podnieœ", "Zamknij");
		else Tip(playerid, 3, "Nic nie znalazles.");
	}
	else
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_PASSENGER)
			return msg_error(playerid, "Nie mo¿esz aktualnie odk³adaæ ani podnosiæ ¿adnych przedmiotów (jesteœ pasa¿erem).");
		
		new Float:Pos[3];
		new list[1024];
		
		GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
		
		ForeachEx(i,_ITEM_COUNT)
			if(ItemInfo[i][iUID] && ItemInfo[i][iOwnerTyp] == OWNER_NONE && ItemInfo[i][iVW] == GetPlayerVirtualWorld(playerid))
				if(ItemInfo[i][iPosx] < Pos[0]+2 && ItemInfo[i][iPosx] > Pos[0]-2)
					if(ItemInfo[i][iPosy] < Pos[1]+2 && ItemInfo[i][iPosy] > Pos[1]-2)
						if(ItemInfo[i][iPosz] < Pos[2]+2 && ItemInfo[i][iPosz] > Pos[2]-2)
							format(list, sizeof(list), "%s\n%d: {878A87}%s", list, ItemInfo[i][iUID], ItemInfo[i][iName]);
		
		if(strlen(list) > 3) ShowPlayerDialog(playerid, D_ITEM_PICK, DIALOG_STYLE_LIST, DEF_NAME" » przedmioty w pobli¿u", list, "Podnieœ", "Zamknij");
		else Tip(playerid, 3, "Nic nie znalazles.");
	}
	
	return 1;
}

public DeleteItem(uid)
{
	new query[64];
	format(query, sizeof(query), "DELETE FROM `srv_items` WHERE `UID` = '%d' LIMIT 1", uid);
	mysql_query(query);
	
	ItemInfo[uid][iUID] = 
	ItemInfo[uid][iName] = 
	ItemInfo[uid][iType] = 
	ItemInfo[uid][iValue1] = 
	ItemInfo[uid][iValue2] = 
	ItemInfo[uid][iUsed] = 
	ItemInfo[uid][iOwnerTyp] = 
	ItemInfo[uid][iOwner] = 
	ItemInfo[uid][iIlosc] = 
	ItemInfo[uid][iPrice] = 0;
	ItemInfo[uid][iPosx] = 
	ItemInfo[uid][iPosy] = 
	ItemInfo[uid][iPosz] = 0.0;
	ItemInfo[uid][iVW] = 0;
	
	return 1;
}

stock GetPhoneID(numer)
{
	new tele = -1;

	ForeachEx(i,_ITEM_COUNT)
	{
		if(ItemInfo[i][iType] == ITEM_TYPE_TELEFON && ItemInfo[i][iValue1] == numer)
		{
			tele = GetPlayerID(ItemInfo[i][iOwner]);
			break;
		}
	}
	
	return tele;
}

public PlantSeed(playerid)
{
	new Float:Pos[3];
	
	new string[512];
	
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
	
	new time = 60*(20+random(5));

	new uid;
	
	ForeachEx(i, MAX_PLANTS)
	{
		if(PlantInfo[i][plantUID] == 0 && i != 0)
		{
			uid = i;
			break;
		}
	}
	if(uid==0)
		return 0;
	
	new query[256];
	format(query, sizeof(query), "INSERT INTO `srv_plants` VALUES ('%d', '%d', '%d', '%f', '%f', '%f', '%d', '%d')", uid, time, CharacterInfo[playerid][pUID], Pos[0], Pos[1], Pos[2]-1.1, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
	mysql_query(query);
	
	PlantInfo[uid][plantUID] = uid;
	PlantInfo[uid][plantTime] = time;
	PlantInfo[uid][plantOwner] = CharacterInfo[playerid][pUID];
	PlantInfo[uid][plantx] = Pos[0];
	PlantInfo[uid][planty] = Pos[1];
	PlantInfo[uid][plantz] = Pos[2]-1.1;
	PlantInfo[uid][plantVW] = GetPlayerVirtualWorld(playerid);
	PlantInfo[uid][plantInt] = GetPlayerInterior(playerid);
	
	PlantInfo[uid][plantObject] = CreateDynamicObject(19473, PlantInfo[uid][plantx], PlantInfo[uid][planty], PlantInfo[uid][plantz], 0, 0, 0, PlantInfo[uid][plantVW], PlantInfo[uid][plantInt], -1);

	format(string, sizeof(string), "Krzak marihuany:{636363} %d minut.", PlantInfo[uid][plantTime]);
	
	PlantInfo[uid][planttext] = CreateDynamic3DTextLabel(string, 0x08A800FF, PlantInfo[uid][plantx], PlantInfo[uid][planty], PlantInfo[uid][plantz]+1.0, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID,1, PlantInfo[uid][plantVW]);
	
	return uid;
}

stock GetClosestPlant(playerid, type)
{	
	if(!type)
	{
		ForeachEx(i, MAX_PLANTS)
			if(PlantInfo[i][plantUID])
				if(IsPlayerInRangeOfPoint(playerid, 3.0, PlantInfo[i][plantx], PlantInfo[i][planty], PlantInfo[i][plantz]) && GetPlayerVirtualWorld(playerid) == PlantInfo[i][plantVW])
					return i;
	}
	else
	{
		ForeachEx(i, MAX_PLANTS)
			if(PlantInfo[i][plantUID])
				if(IsPlayerInRangeOfPoint(playerid, 3.0, PlantInfo[i][plantx], PlantInfo[i][planty], PlantInfo[i][plantz]) && PlantInfo[i][plantTime] <= 0 && GetPlayerVirtualWorld(playerid) == PlantInfo[i][plantVW])
					return i;
	}
	
	return 0;
}

stock GetPlayerItemTypeID(playerid,type)
{
	ForeachEx(i,_ITEM_COUNT)
		if(ItemInfo[i][iType] == type && ItemInfo[i][iOwnerTyp] == OWNER_PLAYER && ItemInfo[i][iOwner] == CharacterInfo[playerid][pUID])
			return i;
	
	return 0;
}

stock IsPhoneNumberUsed(number)
{
	ForeachEx(i, _ITEM_COUNT)
		if(ItemInfo[i][iType]==ITEM_TYPE_TELEFON && ItemInfo[i][iValue1]==number)
			return 1;
	
	return 0;
}

stock GetWeaponSlot(weaponid)
{
	new slot;
	switch(weaponid)
	{
		case 0,1: slot = 0;
		case 2 .. 9: slot = 1;
		case 10 .. 15: slot = 10;
		case 16 .. 18, 39: slot = 8;
		case 22 .. 24: slot =2;
		case 25 .. 27: slot = 3;
		case 28, 29, 32: slot = 4;
		case 30, 31: slot = 5;
		case 33, 34: slot = 6;
		case 35 .. 38: slot = 7;
		case 40: slot = 12;
		case 41 .. 43: slot = 9;
		case 44 .. 46: slot = 11;
	}
	return slot;
}

stock ReattachObjectsToPlayer(playerid)
{
	new query[128],Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ,uid,index;
	for(new i=0; i<10; i++)
	{
		if(CharacterInfo[playerid][pAttached][i])
		{
			uid=CharacterInfo[playerid][pAttached][i];
			format(query,sizeof(query),"SELECT `ind`,`x`,`y`,`z`,`rx`,`ry`,`rz`,`sx`,`sy`,`sz` FROM `srv_attached` WHERE `UID`='%d'",uid);
			fScaleX=fScaleY=fScaleZ=1.0;
			mysql_query(query);
			mysql_store_result();
			if(mysql_num_rows())
			{
				mysql_fetch_row_format(query);
				sscanf(query,"p<|>dfffffffff",index,fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
				mysql_free_result();
			}
			else
			{
				mysql_free_result();
				continue;
			}
			ItemInfo[uid][iUsed]=1;
			SetPlayerAttachedObject(playerid, index, ItemInfo[uid][iValue1], ItemInfo[uid][iValue2],fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
		}
	}

	return 1;
}