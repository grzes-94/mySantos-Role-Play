forward LoadSettings();
forward LoadTD(playerid);
forward LoadItems();
forward LoadDoors();
forward LoadGroups();
forward LoadPlants();
forward LoadCorpse();
forward LoadPlayerGroups(playerid);
forward RemoveCustomObjects(playerid);
forward LoadObjects();
forward LoadTexture();
forward LoadMaterialText();
forward LoadVehicles();
forward LoadAnimations();
forward LoadFuelStations();
forward LoadCorners();
forward LoadBusStops();
forward Load3DTexts();
forward LoadSafeKeeps();
forward LoadDescriptions();
forward LoadActors();
forward LoadCustomSkins();

public LoadSettings()
{
	new result[512];
	mysql_query("SELECT * FROM `srv_settings`");
	mysql_store_result();
	while(mysql_fetch_row_format(result, "|") == 1)
	{
		sscanf(result,  "p<|>dfffffffddddddddddddddd",
		
		SettingInfo[sStatus],
		SettingInfo[sSpawnX],
		SettingInfo[sSpawnY],
		SettingInfo[sSpawnZ],
		SettingInfo[sSpawnAngle],
		SettingInfo[sMagazineX],
		SettingInfo[sMagazineY],
		SettingInfo[sMagazineZ],
		SettingInfo[sPremiumEventDays],
		SettingInfo[sLSNPrice],
		SettingInfo[sDocID],
		SettingInfo[sDocDriver],
		SettingInfo[sDocPilot],
		SettingInfo[sFuelCost],
		SettingInfo[sHotelPrice],
		SettingInfo[sInsurance],
		SettingInfo[sTaxes],
		SettingInfo[sPlateCharge],
		SettingInfo[sGroupRegisterCharge],
		SettingInfo[sDocWeapons],
		SettingInfo[sDocMed],
		SettingInfo[sHealPrice],
		SettingInfo[sSANNPay]);
	}
	
	SettingInfo[sGovBots] = false;
	
	mysql_free_result();
	print("[LOAD] Wczytano podstawowe ustawienia (status, spawn, magazyn, event premium, etc.).");
	return 1;
}

public LoadTD(playerid)
{
	DoorsTD[playerid] = CreatePlayerTextDraw(playerid, 320.000000, 350.000000, "____");
	PlayerTextDrawAlignment(playerid, DoorsTD[playerid], 2);
	PlayerTextDrawLetterSize(playerid, DoorsTD[playerid], 0.300000, 1.000000);
	PlayerTextDrawSetShadow(playerid, DoorsTD[playerid], 1);
	PlayerTextDrawUseBox(playerid, DoorsTD[playerid], 1);
	PlayerTextDrawBoxColor(playerid, DoorsTD[playerid], 85);
	PlayerTextDrawTextSize(playerid, DoorsTD[playerid], 0.000000, 180.000000);

	EditObjectText[playerid] = CreatePlayerTextDraw(playerid, 360.000000, 300.000000, "____");
	PlayerTextDrawAlignment(playerid, EditObjectText[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, EditObjectText[playerid], 0x080808AA);
	PlayerTextDrawFont(playerid, EditObjectText[playerid], 1);
	PlayerTextDrawLetterSize(playerid, EditObjectText[playerid], 0.299999, 1.200000);
	PlayerTextDrawColor(playerid, EditObjectText[playerid], 0xffffffff);
	PlayerTextDrawSetOutline(playerid, EditObjectText[playerid], 1);
	PlayerTextDrawSetProportional(playerid, EditObjectText[playerid], 1);
	PlayerTextDrawSetShadow(playerid, EditObjectText[playerid], 1);
	
	OFFER[playerid] = CreatePlayerTextDraw(playerid, 460.000000, 280.000000, "~>~~n~~>~~n~~>~~n~~>~~n~~n~");
	PlayerTextDrawAlignment(playerid, OFFER[playerid], 0);
	PlayerTextDrawLetterSize(playerid, OFFER[playerid], 0.300000, 1.000000);
	PlayerTextDrawSetShadow(playerid, OFFER[playerid], 1);
	PlayerTextDrawSetProportional(playerid, OFFER[playerid], 1);
	PlayerTextDrawUseBox(playerid, OFFER[playerid], 1);
	PlayerTextDrawBoxColor(playerid, OFFER[playerid], 85);
	PlayerTextDrawSetOutline(playerid, OFFER[playerid], 1);
	PlayerTextDrawTextSize(playerid, OFFER[playerid], 620.000000, 180.000000);
	
	ACCEPT[playerid] = CreatePlayerTextDraw(playerid, 540.000000, 322.000000, "~g~AKCEPTUJ");
	PlayerTextDrawAlignment(playerid, ACCEPT[playerid], 2);
	PlayerTextDrawLetterSize(playerid, ACCEPT[playerid], 0.300000, 1.000000);
	PlayerTextDrawSetShadow(playerid, ACCEPT[playerid], 1);
	PlayerTextDrawUseBox(playerid, ACCEPT[playerid], 1);
	PlayerTextDrawBoxColor(playerid, ACCEPT[playerid], 85);
	PlayerTextDrawTextSize(playerid, ACCEPT[playerid], 10.000000, 50.000000);
	PlayerTextDrawSetSelectable(playerid, ACCEPT[playerid], 1);
	
	REJECT[playerid] = CreatePlayerTextDraw(playerid, 595.000000, 322.000000, "~r~ODRZUC");
	PlayerTextDrawAlignment(playerid, REJECT[playerid], 2);
	PlayerTextDrawLetterSize(playerid, REJECT[playerid], 0.300000, 1.000000);
	PlayerTextDrawSetShadow(playerid, REJECT[playerid], 1);
	PlayerTextDrawUseBox(playerid, REJECT[playerid], 1);
	PlayerTextDrawBoxColor(playerid, REJECT[playerid], 85);
	PlayerTextDrawTextSize(playerid, REJECT[playerid], 10.000000, 50.000000);
	PlayerTextDrawSetSelectable(playerid, REJECT[playerid], 1);

	TipText[playerid] = CreatePlayerTextDraw(playerid, 480.000000, 110.000000, "___");
	PlayerTextDrawUseBox(playerid, TipText[playerid], 1);
	PlayerTextDrawBoxColor(playerid, TipText[playerid], 85);
	PlayerTextDrawSetProportional(playerid, TipText[playerid], 1);
	PlayerTextDrawSetShadow(playerid, TipText[playerid], 0);
	PlayerTextDrawLetterSize(playerid, TipText[playerid], 0.300000, 1.000000);
	PlayerTextDrawTextSize(playerid, TipText[playerid], 610.000000, 250.000000);
	
	TDEditor_PTD[playerid][0] = CreatePlayerTextDraw(playerid, 436.624908, 409.014831, "GPS");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][0], 0.250000, 1.299998);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][0], 2);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][0], -1061109505);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][0], 255);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][0], 0);

	TDEditor_PTD[playerid][1] = CreatePlayerTextDraw(playerid, 436.624908, 421.511169, " ");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][1], 0.400000, 1.600000);
	PlayerTextDrawTextSize(playerid, TDEditor_PTD[playerid][1], 0.000000, 27.000000);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][1], 2);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][1], -1);
	PlayerTextDrawUseBox(playerid, TDEditor_PTD[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, TDEditor_PTD[playerid][1], 8388863);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][1], 255);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][1], 0);

	TDEditor_PTD[playerid][2] = CreatePlayerTextDraw(playerid, 436.624908, 421.511169, " ");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][2], 0.400000, 1.600000);
	PlayerTextDrawTextSize(playerid, TDEditor_PTD[playerid][2], 0.000000, 27.000000);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][2], 2);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][2], -1);
	PlayerTextDrawUseBox(playerid, TDEditor_PTD[playerid][2], 1);
	PlayerTextDrawBoxColor(playerid, TDEditor_PTD[playerid][2], -2147483393);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][2], 255);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][2], 0);

	TDEditor_PTD[playerid][3] = CreatePlayerTextDraw(playerid, 476.333282, 409.014831, "PASY");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][3], 0.250000, 1.299998);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][3], 2);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][3], -1061109505);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][3], 255);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][3], 0);

	TDEditor_PTD[playerid][4] = CreatePlayerTextDraw(playerid, 476.333282, 421.511169, " ");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][4], 0.400000, 1.600000);
	PlayerTextDrawTextSize(playerid, TDEditor_PTD[playerid][4], 0.000000, 27.000000);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][4], 2);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][4], -1);
	PlayerTextDrawUseBox(playerid, TDEditor_PTD[playerid][4], 1);
	PlayerTextDrawBoxColor(playerid, TDEditor_PTD[playerid][4], 8388863);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][4], 255);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][4], 0);

	TDEditor_PTD[playerid][5] = CreatePlayerTextDraw(playerid, 476.333282, 421.511169, " ");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][5], 0.400000, 1.600000);
	PlayerTextDrawTextSize(playerid, TDEditor_PTD[playerid][5], 0.000000, 27.000000);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][5], 2);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][5], -1);
	PlayerTextDrawUseBox(playerid, TDEditor_PTD[playerid][5], 1);
	PlayerTextDrawBoxColor(playerid, TDEditor_PTD[playerid][5], -2147483393);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][5], 255);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][5], 0);

	TDEditor_PTD[playerid][6] = CreatePlayerTextDraw(playerid, 515.666656, 409.014831, "DUTY");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][6], 0.250000, 1.299998);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][6], 2);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][6], -1061109505);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][6], 255);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][6], 2);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][6], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][6], 0);

	TDEditor_PTD[playerid][7] = CreatePlayerTextDraw(playerid, 515.666656, 421.511169, " ");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][7], 0.400000, 1.600000);
	PlayerTextDrawTextSize(playerid, TDEditor_PTD[playerid][7], 0.000000, 27.000000);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][7], 2);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][7], -1);
	PlayerTextDrawUseBox(playerid, TDEditor_PTD[playerid][7], 1);
	PlayerTextDrawBoxColor(playerid, TDEditor_PTD[playerid][7], 8388863);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][7], 255);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][7], 1);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][7], 0);

	TDEditor_PTD[playerid][8] = CreatePlayerTextDraw(playerid, 515.666656, 421.511169, " ");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][8], 0.400000, 1.600000);
	PlayerTextDrawTextSize(playerid, TDEditor_PTD[playerid][8], 0.000000, 27.000000);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][8], 2);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][8], -1);
	PlayerTextDrawUseBox(playerid, TDEditor_PTD[playerid][8], 1);
	PlayerTextDrawBoxColor(playerid, TDEditor_PTD[playerid][8], -2147483393);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][8], 255);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][8], 1);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][8], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][8], 0);
	
	Speedometer[playerid][0] = CreatePlayerTextDraw(playerid, 212.666748, 380.444366, "~n~~n~~n~");
	PlayerTextDrawLetterSize(playerid, Speedometer[playerid][0], 0.500000, 1.299998);
	PlayerTextDrawTextSize(playerid, Speedometer[playerid][0], 5.000000, 160.000000);
	PlayerTextDrawAlignment(playerid, Speedometer[playerid][0], 2);
	PlayerTextDrawColor(playerid, Speedometer[playerid][0], -1);
	PlayerTextDrawUseBox(playerid, Speedometer[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, Speedometer[playerid][0], 842150527);
	PlayerTextDrawSetShadow(playerid, Speedometer[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, Speedometer[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, Speedometer[playerid][0], 255);
	PlayerTextDrawFont(playerid, Speedometer[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, Speedometer[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, Speedometer[playerid][0], 0);

	Speedometer[playerid][1] = CreatePlayerTextDraw(playerid, 212.666656, 383.762969, "~n~~n~");
	PlayerTextDrawLetterSize(playerid, Speedometer[playerid][1], 0.400000, 1.600000);
	PlayerTextDrawTextSize(playerid, Speedometer[playerid][1], 0.000000, 154.000000);
	PlayerTextDrawAlignment(playerid, Speedometer[playerid][1], 2);
	PlayerTextDrawColor(playerid, Speedometer[playerid][1], -1);
	PlayerTextDrawUseBox(playerid, Speedometer[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, Speedometer[playerid][1], 757935500);
	PlayerTextDrawSetShadow(playerid, Speedometer[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, Speedometer[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, Speedometer[playerid][1], 255);
	PlayerTextDrawFont(playerid, Speedometer[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, Speedometer[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, Speedometer[playerid][1], 0);

	Speedometer[playerid][2] = CreatePlayerTextDraw(playerid, 147.666687, 389.155487, "KM/H");
	PlayerTextDrawLetterSize(playerid, Speedometer[playerid][2], 0.250000, 1.100000);
	PlayerTextDrawAlignment(playerid, Speedometer[playerid][2], 2);
	PlayerTextDrawColor(playerid, Speedometer[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, Speedometer[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, Speedometer[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, Speedometer[playerid][2], 255);
	PlayerTextDrawFont(playerid, Speedometer[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, Speedometer[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, Speedometer[playerid][2], 0);

	Speedometer[playerid][3] = CreatePlayerTextDraw(playerid, 186.666702, 389.155487, "Przebieg");
	PlayerTextDrawLetterSize(playerid, Speedometer[playerid][3], 0.250000, 1.100000);
	PlayerTextDrawAlignment(playerid, Speedometer[playerid][3], 2);
	PlayerTextDrawColor(playerid, Speedometer[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, Speedometer[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, Speedometer[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, Speedometer[playerid][3], 255);
	PlayerTextDrawFont(playerid, Speedometer[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, Speedometer[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, Speedometer[playerid][3], 0);

	Speedometer[playerid][4] = CreatePlayerTextDraw(playerid, 233.666717, 389.155487, "Paliwo");
	PlayerTextDrawLetterSize(playerid, Speedometer[playerid][4], 0.250000, 1.100000);
	PlayerTextDrawAlignment(playerid, Speedometer[playerid][4], 2);
	PlayerTextDrawColor(playerid, Speedometer[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, Speedometer[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, Speedometer[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, Speedometer[playerid][4], 255);
	PlayerTextDrawFont(playerid, Speedometer[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, Speedometer[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, Speedometer[playerid][4], 0);

	Speedometer[playerid][5] = CreatePlayerTextDraw(playerid, 273.333435, 389.155487, "HP");
	PlayerTextDrawLetterSize(playerid, Speedometer[playerid][5], 0.250000, 1.100000);
	PlayerTextDrawAlignment(playerid, Speedometer[playerid][5], 2);
	PlayerTextDrawColor(playerid, Speedometer[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, Speedometer[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, Speedometer[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, Speedometer[playerid][5], 255);
	PlayerTextDrawFont(playerid, Speedometer[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, Speedometer[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, Speedometer[playerid][5], 0);

	Speedometer[playerid][6] = CreatePlayerTextDraw(playerid, 147.666687, 397.866607, " ");
	PlayerTextDrawLetterSize(playerid, Speedometer[playerid][6], 0.250000, 1.100000);
	PlayerTextDrawAlignment(playerid, Speedometer[playerid][6], 2);
	PlayerTextDrawColor(playerid, Speedometer[playerid][6], -1061109505);
	PlayerTextDrawSetShadow(playerid, Speedometer[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, Speedometer[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, Speedometer[playerid][6], 255);
	PlayerTextDrawFont(playerid, Speedometer[playerid][6], 1);
	PlayerTextDrawSetProportional(playerid, Speedometer[playerid][6], 1);
	PlayerTextDrawSetShadow(playerid, Speedometer[playerid][6], 0);

	Speedometer[playerid][7] = CreatePlayerTextDraw(playerid, 186.666702, 397.866607, " ");
	PlayerTextDrawLetterSize(playerid, Speedometer[playerid][7], 0.250000, 1.100000);
	PlayerTextDrawAlignment(playerid, Speedometer[playerid][7], 2);
	PlayerTextDrawColor(playerid, Speedometer[playerid][7], -1061109505);
	PlayerTextDrawSetShadow(playerid, Speedometer[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, Speedometer[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, Speedometer[playerid][7], 255);
	PlayerTextDrawFont(playerid, Speedometer[playerid][7], 1);
	PlayerTextDrawSetProportional(playerid, Speedometer[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, Speedometer[playerid][7], 0);

	Speedometer[playerid][8] = CreatePlayerTextDraw(playerid, 233.666717, 397.866607, " ");
	PlayerTextDrawLetterSize(playerid, Speedometer[playerid][8], 0.250000, 1.100000);
	PlayerTextDrawAlignment(playerid, Speedometer[playerid][8], 2);
	PlayerTextDrawColor(playerid, Speedometer[playerid][8], -1061109505);
	PlayerTextDrawSetShadow(playerid, Speedometer[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, Speedometer[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, Speedometer[playerid][8], 255);
	PlayerTextDrawFont(playerid, Speedometer[playerid][8], 1);
	PlayerTextDrawSetProportional(playerid, Speedometer[playerid][8], 1);
	PlayerTextDrawSetShadow(playerid, Speedometer[playerid][8], 0);

	Speedometer[playerid][9] = CreatePlayerTextDraw(playerid, 273.333435, 397.866607, " ");
	PlayerTextDrawLetterSize(playerid, Speedometer[playerid][9], 0.250000, 1.100000);
	PlayerTextDrawAlignment(playerid, Speedometer[playerid][9], 2);
	PlayerTextDrawColor(playerid, Speedometer[playerid][9], -1061109505);
	PlayerTextDrawSetShadow(playerid, Speedometer[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, Speedometer[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, Speedometer[playerid][9], 255);
	PlayerTextDrawFont(playerid, Speedometer[playerid][9], 1);
	PlayerTextDrawSetProportional(playerid, Speedometer[playerid][9], 1);
	PlayerTextDrawSetShadow(playerid, Speedometer[playerid][9], 0);
	
	PlayerLoadingInfo[playerid] = CreatePlayerTextDraw(playerid, 320.000000, 350.000000, "Trwa pobieranie plikow potrzebnych do gry na serwerze, nie potrwa to dlugo ..");
	PlayerTextDrawLetterSize(playerid, PlayerLoadingInfo[playerid], 0.400000, 1.600000);
	PlayerTextDrawTextSize(playerid, PlayerLoadingInfo[playerid], 0.000000, 312.000000);
	PlayerTextDrawAlignment(playerid, PlayerLoadingInfo[playerid], 2);
	PlayerTextDrawColor(playerid, PlayerLoadingInfo[playerid], -1061109505);
	PlayerTextDrawUseBox(playerid, PlayerLoadingInfo[playerid], 1);
	PlayerTextDrawBoxColor(playerid, PlayerLoadingInfo[playerid], 757935510);
	PlayerTextDrawSetShadow(playerid, PlayerLoadingInfo[playerid], 0);
	PlayerTextDrawSetOutline(playerid, PlayerLoadingInfo[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, PlayerLoadingInfo[playerid], 255);
	PlayerTextDrawFont(playerid, PlayerLoadingInfo[playerid], 1);
	PlayerTextDrawSetProportional(playerid, PlayerLoadingInfo[playerid], 1);
	PlayerTextDrawSetShadow(playerid, PlayerLoadingInfo[playerid], 0);
}

public LoadItems()
{
	new query[2048], i, uid;
	new string[128];
	
	mysql_query_format("SELECT * FROM `srv_items`");
	mysql_store_result();
	
	if(mysql_num_rows())
	{
		if(mysql_num_rows() > MAX_ITEMS) print("[ERROR][ITEMS] Przedmiotów jest wiêcej ni¿ definicja GMA.");
		
		while(mysql_fetch_row_format(query, "|") == 1)
		{
			sscanf(query, "p<|>d", uid);
			
			sscanf(query, "p<|>ds[32]ddddddddfffd",  
			
			ItemInfo[uid][iUID],
			ItemInfo[uid][iName],
			ItemInfo[uid][iType],
			ItemInfo[uid][iValue1],
			ItemInfo[uid][iValue2],
			ItemInfo[uid][iUsed],
			ItemInfo[uid][iOwnerTyp],
			ItemInfo[uid][iOwner],
			ItemInfo[uid][iIlosc],
			ItemInfo[uid][iPrice],
			ItemInfo[uid][iPosx],
			ItemInfo[uid][iPosy],
			ItemInfo[uid][iPosz],
			ItemInfo[uid][iVW]);
			
			i++;
			_ITEM_COUNT=uid +1;
			if(ItemInfo[uid][iOwner] == OWNER_NONE)
			{
				format(string, sizeof(string), "%s (UID: %d).", ItemInfo[uid][iName], ItemInfo[uid][iUID]);
			
				ItemInfo[uid][iDroppedInfo] = Create3DTextLabel(string, COLOR_WHITE, ItemInfo[uid][iPosx], ItemInfo[uid][iPosy], ItemInfo[uid][iPosz]-0.8, 7.0, ItemInfo[uid][iVW], 1);
			}
		}
	}
	
	mysql_free_result();
	printf("[LOAD] Wczytano %d przedmiotów z bazy danych.", i);
	
	return 1;
}

public LoadDoors()
{
	new query[2048], i = 0, uid;

	mysql_query("SELECT * FROM `srv_doors`");
	mysql_store_result();
	
	if(mysql_num_rows())
	{
		if(mysql_num_rows() > MAX_DOORS) print("[ERROR][DOORS] Drzwi jest wiêcej ni¿ definicja GMA.");
		
		while(mysql_fetch_row_format(query, "|") == 1)
		{
			sscanf(query, "p<|>d", uid);
			
			sscanf(query, "p<|>ds[31]ddffffddffffddddds[128]dddd",
			
			DoorsInfo[uid][dUID],
			DoorsInfo[uid][dName],
			DoorsInfo[uid][dOwnerTyp],
			DoorsInfo[uid][dOwner],
			DoorsInfo[uid][dEnterX],
			DoorsInfo[uid][dEnterY],
			DoorsInfo[uid][dEnterZ],
			DoorsInfo[uid][dEnterAngle],
			DoorsInfo[uid][dEnterInt],
			DoorsInfo[uid][dEnterVW],
			DoorsInfo[uid][dExitX],
			DoorsInfo[uid][dExitY],
			DoorsInfo[uid][dExitZ],
			DoorsInfo[uid][dExitAngle],
			DoorsInfo[uid][dExitInt],
			DoorsInfo[uid][dExitVW],
			DoorsInfo[uid][dLock],
			DoorsInfo[uid][dPickupID],
			DoorsInfo[uid][dGarage],
			DoorsInfo[uid][dRadio],
			DoorsInfo[uid][dIconID],
			DoorsInfo[uid][dPriceForEntry],
			DoorsInfo[uid][dTime],
			DoorsInfo[uid][dWeather]);
			
			i++;
			
			_DOOR_COUNT = uid +1;
			
			DoorsInfo[uid][dPickup] = CreateDynamicPickup(DoorsInfo[uid][dPickupID], 1, DoorsInfo[uid][dEnterX], DoorsInfo[uid][dEnterY], DoorsInfo[uid][dEnterZ], DoorsInfo[uid][dEnterVW], DoorsInfo[uid][dEnterInt]);
		}
	}
	
	mysql_free_result();
	printf("[LOAD] Wczytano %d drzwi z bazy danych.", i);
	
	return 1;
}

public LoadGroups()
{
	new uid, query[2048], i = 0;
	
	mysql_query("SELECT * FROM `srv_groups`");
	mysql_store_result();
	
	if(mysql_num_rows())
	{
		if(mysql_num_rows() > MAX_GROUPS) print("[ERROR][GROUPS] Grup jest wiêcej ni¿ definicja GMA.");
		
		while(mysql_fetch_row_format(query, "|") == 1)
		{
			sscanf(query, "p<|>d", uid);
			
			sscanf(query, "p<|>ds[32]s[32]ddddffffddds[64]ddd",
			
			GroupInfo[uid][gUID],
			GroupInfo[uid][gName],
			GroupInfo[uid][gTag],
			GroupInfo[uid][gType],
			GroupInfo[uid][gCash],
			GroupInfo[uid][gFlags],
			GroupInfo[uid][gLeader],
			GroupInfo[uid][gSpawnX],
			GroupInfo[uid][gSpawnY],
			GroupInfo[uid][gSpawnZ],
			GroupInfo[uid][gSpawnAngle],
			GroupInfo[uid][gSpawnInt],
			GroupInfo[uid][gSpawnVW],
			GroupInfo[uid][gColor],
			GroupInfo[uid][gNotice],
			GroupInfo[uid][gRegistered],
			GroupInfo[uid][gGrant],
			GroupInfo[uid][gSalaryAccount]);
			
			i++;
			
			if(GroupInfo[uid][gType] == GROUP_LOGISTIC)
				GroupInfo[uid][gTransportTowary] = 4;
		}
	}
	
	mysql_free_result();
	printf("[LOAD] Wczytano %d grup z bazy danych.", i);
	
	return 1;
}

public LoadPlants()
{
	new uid, query[2048], i = 0;
	
	new string[128];
	
	mysql_query_format("SELECT * FROM `srv_plants`");
	mysql_store_result();
	
	if(mysql_num_rows())
	{
		if(mysql_num_rows() > MAX_PLANTS) print("[ERROR][PLANTS] Roœlinek jest wiêcej ni¿ definicja GMA.");
		
		while(mysql_fetch_row_format(query, "|") == 1)
		{
			sscanf(query, "p<|>d", uid);
			
			sscanf(query, "p<|>dddfffdd",
			
			PlantInfo[uid][plantUID],
			PlantInfo[uid][plantTime],
			PlantInfo[uid][plantOwner],
			PlantInfo[uid][plantx],
			PlantInfo[uid][planty],
			PlantInfo[uid][plantz],
			PlantInfo[uid][plantVW],
			PlantInfo[uid][plantInt]);
			
			PlantInfo[uid][plantObject] = CreateDynamicObject(19473, PlantInfo[uid][plantx], PlantInfo[uid][planty], PlantInfo[uid][plantz], 0, 0, 0, PlantInfo[uid][plantVW], PlantInfo[uid][plantInt]);
			
			if(PlantInfo[uid][plantTime] > 0)
			{
				format(string, sizeof(string), "Krzak marihuany:{636363} %d minut.", PlantInfo[uid][plantTime]);
			}
			else
			{
				format(string, sizeof(string), "Krzak marihuany:{636363} gotowy do zebrania.\n(/zbierz)");
			}
			
			PlantInfo[uid][planttext] = CreateDynamic3DTextLabel(string, 0x08A800FF, PlantInfo[uid][plantx], PlantInfo[uid][planty], PlantInfo[uid][plantz]+1.0, 5.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID, 1,PlantInfo[uid][plantVW]);

			i++;
		}
	}
	
	mysql_free_result();
	printf("[LOAD] Wczytano %d roœlinek z bazy danych.", i);
	
	return 1;
}
public LoadCorpse()
{
	new uid, query[2048], i = 0;
	mysql_query("UPDATE srv_corpse SET gun=\"-\" WHERE gun=\"\" ");
	mysql_query("UPDATE srv_corpse SET reason=\"-\" WHERE reason=\"\" ");
	new string[32];
	mysql_query("SELECT * from `srv_corpse`");
	mysql_store_result();
	if(mysql_num_rows())
	{
		if(mysql_num_rows() > MAX_CORPSE) print("[ERROR][CORPSE] Zw³ok jest wiêcej ni¿ definicja GMA.");
		
		while(mysql_fetch_row_format(query, "|") == 1)
		{
			sscanf(query, "p<|>d", uid);
			
			sscanf(query, "p<|>dds[32]s[128]s[32]ds[16]dfffdd",
			
			CorpseInfo[uid][corpseID],
			CorpseInfo[uid][corpsePlayerUID],
			CorpseInfo[uid][corpsePlayerName],
			CorpseInfo[uid][corpseReason],
			CorpseInfo[uid][corpseGun],
			CorpseInfo[uid][corpseGunVal],
			CorpseInfo[uid][corpseDate],
			CorpseInfo[uid][corpseMoney],
			CorpseInfo[uid][corpseX],
			CorpseInfo[uid][corpseY],
			CorpseInfo[uid][corpseZ],
			CorpseInfo[uid][corpseInt],
			CorpseInfo[uid][corpseVW]
			);
			
			CorpseInfo[uid][corpseObject] = CreateDynamicObject(19944, CorpseInfo[uid][corpseX], CorpseInfo[uid][corpseY], CorpseInfo[uid][corpseZ], 0, 0, 0, CorpseInfo[uid][corpseVW], CorpseInfo[uid][corpseInt]);
		
			format(string, sizeof(string), "Zw³oki {636363}(%d)",uid);

			
			CorpseInfo[uid][corpseText] = CreateDynamic3DTextLabel(string, COLOR_RED, CorpseInfo[uid][corpseX], CorpseInfo[uid][corpseY], CorpseInfo[uid][corpseZ]+0.75, 7.0,INVALID_PLAYER_ID, INVALID_VEHICLE_ID,1, CorpseInfo[uid][corpseVW]);
			
			i++;
		}
	}
	mysql_free_result();
	printf("[LOAD] Wczytano %d zw³ok z bazy danych.", i);
	return 1;
}

public LoadPlayerGroups(playerid)
{
	MemberGroup[playerid][1][GroupID]=0;
	MemberGroup[playerid][1][GroupRankName]=0;
	MemberGroup[playerid][1][GroupRank]=
	MemberGroup[playerid][1][GroupPerm]=
	MemberGroup[playerid][1][GroupSkin]=
	MemberGroup[playerid][1][GroupTime]=
	MemberGroup[playerid][1][GroupSalary]=
	MemberGroup[playerid][1][GroupCommission]=
	MemberGroup[playerid][1][GroupPayment]=0;

	MemberGroup[playerid][2][GroupID]=0;
	MemberGroup[playerid][2][GroupRankName]=0;
	MemberGroup[playerid][2][GroupRank]=
	MemberGroup[playerid][2][GroupPerm]=
	MemberGroup[playerid][2][GroupSkin]=
	MemberGroup[playerid][2][GroupTime]=
	MemberGroup[playerid][2][GroupSalary]=
	MemberGroup[playerid][2][GroupCommission]=
	MemberGroup[playerid][2][GroupPayment]=0;

	MemberGroup[playerid][3][GroupID]=0;
	MemberGroup[playerid][3][GroupRankName]=0;
	MemberGroup[playerid][3][GroupRank]=
	MemberGroup[playerid][3][GroupPerm]=
	MemberGroup[playerid][3][GroupSkin]=
	MemberGroup[playerid][3][GroupTime]=
	MemberGroup[playerid][3][GroupSalary]=
	MemberGroup[playerid][3][GroupCommission]=
	MemberGroup[playerid][3][GroupPayment]=0;

	MemberGroup[playerid][5][GroupID]=0;
	MemberGroup[playerid][5][GroupRankName]=0;
	MemberGroup[playerid][5][GroupRank]=
	MemberGroup[playerid][5][GroupPerm]=
	MemberGroup[playerid][5][GroupSkin]=
	MemberGroup[playerid][5][GroupTime]=
	MemberGroup[playerid][5][GroupSalary]=
	MemberGroup[playerid][5][GroupCommission]=
	MemberGroup[playerid][5][GroupPayment]=0;

	MemberGroup[playerid][4][GroupID]=0;
	MemberGroup[playerid][4][GroupRankName]=0;
	MemberGroup[playerid][4][GroupRank]=
	MemberGroup[playerid][4][GroupPerm]=
	MemberGroup[playerid][4][GroupSkin]=
	MemberGroup[playerid][4][GroupTime]=
	MemberGroup[playerid][4][GroupSalary]=
	MemberGroup[playerid][4][GroupCommission]=
	MemberGroup[playerid][4][GroupPayment]=0;
	
	new query[192];
	format(query,sizeof(query),"SELECT `group_uid`,`rank_name`,`rank`,`permission`,`time`,`skin`,`salary`,`payment`,`commission` FROM srv_groups_members WHERE `player_uid`='%d' ORDER BY `group_uid` LIMIT 5",CharacterInfo[playerid][pUID]);
	mysql_query(query);
	mysql_store_result();
	new i=1,result[128];
	while(mysql_fetch_row_format(result, "|") == 1)
	{
		sscanf(result, "p<|>ds[32]ddddddd",	  
		MemberGroup[playerid][i][GroupID],
		MemberGroup[playerid][i][GroupRankName],
		MemberGroup[playerid][i][GroupRank],
		MemberGroup[playerid][i][GroupPerm],
		MemberGroup[playerid][i][GroupTime],
		MemberGroup[playerid][i][GroupSkin],
		MemberGroup[playerid][i][GroupSalary],
		MemberGroup[playerid][i][GroupPayment],
		MemberGroup[playerid][i][GroupCommission]);
		i++;

	}
	
	return 1;
}

public RemoveCustomObjects(playerid)
{
	// Maszyny uzupe³niaj¹ce HP
	// Los Santos
	RemoveBuildingForPlayer(playerid, 956, 1634.1487,-2238.2810,13.5077, 20.0); //Snack vender @ LS Airport
	RemoveBuildingForPlayer(playerid, 956, 2480.9885,-1958.5117,13.5831, 20.0); //Snack vender @ Sushi Shop in Willowfield
	RemoveBuildingForPlayer(playerid, 955, 1729.7935,-1944.0087,13.5682, 20.0); //Sprunk machine @ Unity Station
	RemoveBuildingForPlayer(playerid, 955, 2060.1099,-1898.4543,13.5538, 20.0); //Sprunk machine opposite Tony's Liqour in Willowfield
	RemoveBuildingForPlayer(playerid, 955, 2325.8708,-1645.9584,14.8270, 20.0); //Sprunk machine @ Ten Green Bottles
	RemoveBuildingForPlayer(playerid, 955, 1153.9130,-1460.8893,15.7969, 20.0); //Sprunk machine @ Market
	RemoveBuildingForPlayer(playerid, 955,1788.3965,-1369.2336,15.7578, 20.0); //Sprunk machine in Downtown Los Santos
	RemoveBuildingForPlayer(playerid, 955, 2352.9939,-1357.1105,24.3984, 20.0); //Sprunk machine @ Liquour shop in East Los Santos
	RemoveBuildingForPlayer(playerid, 1775, 2224.3235,-1153.0692,1025.7969, 20.0); //Sprunk machine @ Jefferson Motel
	RemoveBuildingForPlayer(playerid, 956, 2140.2566,-1161.7568,23.9922, 20.0); //Snack machine @ pick'n'go market in Jefferson
	RemoveBuildingForPlayer(playerid, 956, 2154.1199,-1015.7635,62.8840, 20.0); //Snach machine @ Carniceria El Pueblo in Las Colinas
	RemoveBuildingForPlayer(playerid, 956, 662.5665,-551.4142,16.3359, 20.0); //Snack vender at Dillimore Gas Station
	RemoveBuildingForPlayer(playerid, 955, 200.2010,-107.6401,1.5513, 20.0); //Sprunk machine @ Blueberry Safe House
	RemoveBuildingForPlayer(playerid, 956, 2271.4666,-77.2104,26.5824, 20.0); //Snack machine @ Palomino Creek Library
	RemoveBuildingForPlayer(playerid, 955, 1278.5421,372.1057,19.5547, 20.0); //Sprunk machine @ Papercuts in Montgomery
	RemoveBuildingForPlayer(playerid, 955, 1929.5527,-1772.3136,13.5469, 20.0); //Sprunk machine @ Idlewood Gas Station
	
	//San Fierro
	RemoveBuildingForPlayer(playerid, 1302, -2419.5835,984.4185,45.2969, 20.0); //Soda machine 1 @ Juniper Hollow Gas Station
	RemoveBuildingForPlayer(playerid, 1209, -2419.5835,984.4185,45.2969, 20.0); //Soda machine 2 @ Juniper Hollow Gas Station
	RemoveBuildingForPlayer(playerid, 956, -2229.2075,287.2937,35.3203, 20.0); //Snack vender @ King's Car Park
	RemoveBuildingForPlayer(playerid, 955, -1349.3947,493.1277,11.1953, 20.0); //Sprunk machine @ SF Aircraft Carrier
	RemoveBuildingForPlayer(playerid, 956, -1349.3947,493.1277,11.1953, 20.0); //Snack vender @ SF Aircraft Carrier
	RemoveBuildingForPlayer(playerid, 955, -1981.6029,142.7232,27.6875, 20.0); //Sprunk machine @ Cranberry Station
	RemoveBuildingForPlayer(playerid, 955, -2119.6245,-422.9411,35.5313, 20.0); //Sprunk machine 1/2 @ SF Stadium
	RemoveBuildingForPlayer(playerid, 955, -2097.3696,-397.5220,35.5313, 20.0); //Sprunk machine 3 @ SF Stadium
	RemoveBuildingForPlayer(playerid, 955, -2068.5593,-397.5223,35.5313, 20.0); //Sprunk machine 3 @ SF Stadium
	RemoveBuildingForPlayer(playerid, 955, -2039.8802,-397.5214,35.5313, 20.0); //Sprunk machine 3 @ SF Stadium
	RemoveBuildingForPlayer(playerid, 955, -2011.1403,-397.5225,35.5313, 20.0); //Sprunk machine 3 @ SF Stadium
	RemoveBuildingForPlayer(playerid, 955, -2005.7861,-490.8688,35.5313, 20.0); //Sprunk machine 3 @ SF Stadium
	RemoveBuildingForPlayer(playerid, 955, -2034.5267,-490.8681,35.5313, 20.0); //Sprunk machine 3 @ SF Stadium
	RemoveBuildingForPlayer(playerid, 955, -2063.1875,-490.8687,35.5313, 20.0); //Sprunk machine 3 @ SF Stadium
	RemoveBuildingForPlayer(playerid, 955, -2091.9780,-490.8684,35.5313, 20.0); //Sprunk machine 3 @ SF Stadium
	
	//Las Venturas
	RemoveBuildingForPlayer(playerid, 956, -1455.1298,2592.4138,55.8359, 20.0); //Snack vender @ El Quebrados GONE
	RemoveBuildingForPlayer(playerid, 955, -252.9574,2598.9048,62.8582, 20.0); //Sprunk machine @ Las Payasadas GONE
	RemoveBuildingForPlayer(playerid, 956, -252.9574,2598.9048,62.8582, 20.0); //Snack vender @ Las Payasadas GONE
	RemoveBuildingForPlayer(playerid, 956, 1398.7617,2223.3606,11.0234, 20.0); //Snack vender @ Redsands West GONE
	RemoveBuildingForPlayer(playerid, 955, -862.9229,1537.4246,22.5870, 20.0); //Sprunk machine @ The Smokin' Beef Grill in Las Barrancas GONE
	RemoveBuildingForPlayer(playerid, 955, -14.6146,1176.1738,19.5634, 20.0); //Sprunk machine @ Fort Carson GONE
	RemoveBuildingForPlayer(playerid, 956, -75.2839,1227.5978,19.7360, 20.0); //Snack vender @ Fort Carson GONE
	RemoveBuildingForPlayer(playerid, 955, 1519.3328,1055.2075,10.8203, 20.0); //Sprunk machine @ LVA Freight Department GONE
	RemoveBuildingForPlayer(playerid, 956, 1659.5096,1722.1096,10.8281, 20.0); //Snack vender near Binco @ LV Airport GONE
	RemoveBuildingForPlayer(playerid, 955, 2086.5872,2071.4958,11.0579, 20.0); //Sprunk machine @ Sex Shop on The Strip
	RemoveBuildingForPlayer(playerid, 955, 2319.9001,2532.0376,10.8203, 20.0); //Sprunk machine @ Pizza co by Julius Thruway (North)
	RemoveBuildingForPlayer(playerid, 955, 2503.2061,1244.5095,10.8203, 20.0); //Sprunk machine @ Club in the Camels Toe
	RemoveBuildingForPlayer(playerid, 956, 2845.9919,1294.2975,11.3906, 20.0); //Snack vender @ Linden Station
	
	//Interiors: 24/7 and Clubs
	RemoveBuildingForPlayer(playerid, 1775, 496.0843,-23.5310,1000.6797, 20.0); //Sprunk machine 1 @ Club in Camels Toe
	RemoveBuildingForPlayer(playerid, 1775, 501.1219,-2.1968,1000.6797, 20.0); //Sprunk machine 2 @ Club in Camels Toe
	RemoveBuildingForPlayer(playerid, 1776, 501.1219,-2.1968,1000.6797, 20.0); //Snack vender @ Club in Camels Toe
	RemoveBuildingForPlayer(playerid, 1775, -19.2299,-57.0460,1003.5469, 20.0); //Sprunk machine @ Roboi's type 24/7 stores
	RemoveBuildingForPlayer(playerid, 1776, -35.9012,-57.1345,1003.5469, 20.0); //Snack vender @ Roboi's type 24/7 stores
	RemoveBuildingForPlayer(playerid, 1775, -17.0036,-90.9709,1003.5469, 20.0); //Sprunk machine @ Other 24/7 stores
	RemoveBuildingForPlayer(playerid, 1776, -17.0036,-90.9709,1003.5469, 20.0); //Snach vender @ Others 24/7 stores
	
	//Rampy lotnisko
	RemoveBuildingForPlayer(playerid, 3769, 1650.0, -2400.0, 14.9844, 800.0);
	RemoveBuildingForPlayer(playerid, 3744, 1650.0, -2400.0, 14.9844, 800.0);
	RemoveBuildingForPlayer(playerid, 3780, 1650.0, -2400.0, 14.9844, 800.0);
	RemoveBuildingForPlayer(playerid, 3780, 1650.0, -2400.0, 14.9844, 800.0);
	RemoveBuildingForPlayer(playerid, 3665, 1650.0, -2400.0, 14.9844, 800.0);
	RemoveBuildingForPlayer(playerid, 3663, 1650.0, -2400.0, 14.9844, 800.0);
	RemoveBuildingForPlayer(playerid, 3664, 1650.0, -2400.0, 14.9844, 800.0);
	RemoveBuildingForPlayer(playerid, 3625, 1650.0, -2400.0, 14.9844, 800.0);
	RemoveBuildingForPlayer(playerid, 1412, 1650.0, -2400.0, 14.9844, 800.0);
	RemoveBuildingForPlayer(playerid, 3574, 1650.0, -2400.0, 14.9844, 800.0);
	
	return 1;
}

public LoadObjects()
{
	new result[2048], i = 0;
	mysql_query("SELECT * FROM `srv_objects`");
	mysql_store_result();

	if(mysql_num_rows() > MAX_OBJECTS) printf("[ERROR][OBJECTS] Limit obiektow w gamemode jest zbyt maly.");

	while(mysql_fetch_row_format(result, "|") == 1)
	{
		new uid;
		sscanf(result, 	"p<|>d", uid);
		sscanf(result,  "p<|>ddffffffdddddffffffddd",	ObjectInfo[uid][oUID],
														ObjectInfo[uid][oModel],
														ObjectInfo[uid][oX],
														ObjectInfo[uid][oY],
														ObjectInfo[uid][oZ],
														ObjectInfo[uid][oRX],
														ObjectInfo[uid][oRY],
														ObjectInfo[uid][oRZ],
														ObjectInfo[uid][oVW],
														ObjectInfo[uid][oInt],
														ObjectInfo[uid][oOwner],
														ObjectInfo[uid][oOwnerType],
														ObjectInfo[uid][oGate],
														ObjectInfo[uid][oGateX],
														ObjectInfo[uid][oGateY],
														ObjectInfo[uid][oGateZ],
														ObjectInfo[uid][oGateRX],
														ObjectInfo[uid][oGateRY],
														ObjectInfo[uid][oGateRZ],
														ObjectInfo[uid][oMMAT],
														ObjectInfo[uid][oCreator],
														ObjectInfo[uid][oLastEditor]
														);

		ObjectInfo[uid][oObject] = CreateDynamicObject(ObjectInfo[uid][oModel], ObjectInfo[uid][oX], ObjectInfo[uid][oY], ObjectInfo[uid][oZ], ObjectInfo[uid][oRX], ObjectInfo[uid][oRY], ObjectInfo[uid][oRZ], ObjectInfo[uid][oVW], ObjectInfo[uid][oInt]);
		ObjectInfo[uid][o3dTextPlayer] = -1;
		ObjectInfo[uid][oGateOpen] = false;
		if(ObjectInfo[uid][oOwnerType] == OWNER_GROUP)
			GroupInfo[ObjectInfo[uid][oOwner]][gObjects]++;
		i++;
		_OBJ_COUNT=uid+1;
		
		if(ObjectInfo[uid][oOwnerType] == OWNER_HOUSE)
		{
			if(!ObjectInfo[uid][oVW])
				DoorsInfo[ObjectInfo[uid][oOwner]][dObj0]++;
			else
				DoorsInfo[ObjectInfo[uid][oOwner]][dObj]++;
		}
	}
	mysql_free_result();
	printf("[LOAD] Wczytano %d obiektów z bazy danych.", i);
	return 1;
}
public LoadTexture()
{
	new result[2048], i = 0;

	mysql_query("SELECT * FROM `srv_mmat_texture`");
	mysql_store_result();
	
	while(mysql_fetch_row_format(result, "|") == 1)
	{
		new object, index, materialcolor, modelid, txdname[32], texturename[32];

		sscanf(result,  "p<|>ddxds[32]s[32]",	object,
												index,
												materialcolor,
												modelid,
												txdname,
												texturename);

		new uid = object;

		if(ObjectInfo[uid][oUID] && ObjectInfo[uid][oMMAT] == 2)
			SetDynamicObjectMaterial(ObjectInfo[uid][oObject], index, modelid, txdname, texturename, ShiftRGBAToABGR(materialcolor));

		i++;
	}

	mysql_free_result();

	printf("[LOAD] Wczytano %d tekstur z bazy danych.", i);
	return 1;
}

public LoadMaterialText()
{
	new result[2048], i = 0;

	mysql_query("SELECT * FROM `srv_mmat_text`");
	mysql_store_result();

	while(mysql_fetch_row_format(result, "|") == 1)
	{
		new object, index, matsize, fontsize, bold, fontcolor, backcolor, align, fontface[32], text[64];

		sscanf(result,  "p<|>dddddxxds[32]s[64]",	object,
													index,
													matsize,
													fontsize,
													bold,
													fontcolor,
													backcolor,
													align,
													fontface,
													text);

		new uid = GetObjectID(object);

		if(ObjectInfo[uid][oUID] && ObjectInfo[uid][oMMAT] == 1)
		{
			new color_font = ShiftRGBAToABGR(fontcolor);
			new color_back = ShiftRGBAToABGR(backcolor);
			
			SetDynamicObjectMaterialText(ObjectInfo[object][oObject], index, text, matsize, fontface, fontsize, bold, color_font, color_back, align);
			//SetDynamicObjectMaterialText(ObjectInfo[object][oObject], index, text, matsize, fontface, fontsize, bold, color_font, color_back, align);
		}

		i++;
	}
	mysql_free_result();

	printf("[LOAD] Wczytano %d MMAT z bazy danych.", i);
	return 1;
}

public LoadVehicles()
{
	new query[2048], i = 0, uid, visual[32],radio_url[129],desc[128],siren,groupid;
	
	mysql_query("UPDATE `srv_vehicles` SET `radio_url`=\".\" WHERE `radio_url`=\"\"");
	mysql_query("UPDATE `srv_vehicles` SET `description`=\".\" WHERE `description`=\"\"");
	mysql_query("UPDATE `srv_vehicles` SET `register`=\".\" WHERE `register`=\"\"");
	mysql_query("SELECT * FROM `srv_vehicles`");
	mysql_store_result();
	
	if(mysql_num_rows())
	{
		if(mysql_num_rows() > MAX_VEHICLES) print("[ERROR][VEHICLES] Pojazdów jest wiêcej ni¿ definicja GMA.");
		
		while(mysql_fetch_row_format(query, "|") == 1)
		{
			sscanf(query, "p<|>d", uid);
			strmid(desc,"",0,0);
			sscanf(query, "p<|>ddfs[32]ddddffffddffs[32]s[129]dds[128]dddd",
			
			VehicleInfo[uid][vUID],
			VehicleInfo[uid][vModel],
			VehicleInfo[uid][vHP],
			visual,
			VehicleInfo[uid][vColor1],
			VehicleInfo[uid][vColor2],
			VehicleInfo[uid][vOwnerTyp],
			VehicleInfo[uid][vOwner],
			VehicleInfo[uid][vposx],
			VehicleInfo[uid][vposy],
			VehicleInfo[uid][vposz],
			VehicleInfo[uid][vAngle],
			VehicleInfo[uid][vVW],
			VehicleInfo[uid][vInt],
			VehicleInfo[uid][vFuel],
			VehicleInfo[uid][vDistance],
			VehicleInfo[uid][vRegister],
			radio_url,
			VehicleInfo[uid][vBlokada],
			VehicleInfo[uid][vRank],
			desc,
			VehicleInfo[uid][vTuning],
			VehicleInfo[uid][vRegistered],
			VehicleInfo[uid][vGlass],
			VehicleInfo[uid][vLastDriver]);
			
			sscanf(visual, "p<,>dddd",
			VehicleInfo[uid][vVisual][0],
			VehicleInfo[uid][vVisual][1],
			VehicleInfo[uid][vVisual][2],
			VehicleInfo[uid][vVisual][3]);
			
			i++;
			_VEH_COUNT = uid+1;

			if(VehicleInfo[uid][vUID] == 0) //jakby sie zjeba³o to blokujemy UID
			{
				VehicleInfo[uid][vUID]= -1;
				VehicleInfo[uid][vOwnerTyp]= -1;
				VehicleInfo[uid][vOwner] = -1;
				continue;
			}

			VehicleInfo[uid][vDesc3D] = Text3D:INVALID_3DTEXT_ID;
			
			if(VehicleInfo[uid][vOwnerTyp] == OWNER_GROUP)
			{
				groupid=VehicleInfo[uid][vOwner];
				siren = ( (GroupInfo[groupid][gType]==GROUP_PD || GroupInfo[groupid][gType]==GROUP_MC || GroupInfo[groupid][gType]==GROUP_FBI) && Siren(uid) );

				VehicleInfo[uid][vSAMPID] = CreateVehicle(VehicleInfo[uid][vModel], VehicleInfo[uid][vposx], VehicleInfo[uid][vposy], VehicleInfo[uid][vposz], VehicleInfo[uid][vAngle], VehicleInfo[uid][vColor1], VehicleInfo[uid][vColor2], -1, siren);

				VehicleUIDs[VehicleInfo[uid][vSAMPID]]=uid;
				if(VehicleInfo[uid][vTuning] & TUNING_PAINTJOB)
				{
					if(VehicleInfo[uid][vTuning] & TUNING_PAINTJOB_0)
						ChangeVehiclePaintjob(VehicleInfo[uid][vSAMPID],0);					
					if(VehicleInfo[uid][vTuning] & TUNING_PAINTJOB_1)
						ChangeVehiclePaintjob(VehicleInfo[uid][vSAMPID],1);
					if(VehicleInfo[uid][vTuning] & TUNING_PAINTJOB_2)
						ChangeVehiclePaintjob(VehicleInfo[uid][vSAMPID],2);
				}
				
				SetVehicleVirtualWorld(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vVW]);
				LinkVehicleToInterior(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vInt]);
				
				SetVehicleHealth(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vHP]);
				UpdateVehicleDamageStatus(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vVisual][0], VehicleInfo[uid][vVisual][1], VehicleInfo[uid][vVisual][2], VehicleInfo[uid][vVisual][3]);
				
				SetVehicleNumberPlate(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vRegister]);
				
				if(!hasModelEngine(VehicleInfo[uid][vModel]))
				{
					VehicleInfo[uid][vLocked] = false;
					VehicleInfo[uid][vEngine] = true;
				}
				else if(VehicleInfo[uid][vModel] == 448 || VehicleInfo[uid][vModel] == 461 || VehicleInfo[uid][vModel] == 462 || VehicleInfo[uid][vModel] == 463)
				{
					VehicleInfo[uid][vLocked] = false;
					VehicleInfo[uid][vEngine] = false;
				}
				else if(VehicleInfo[uid][vModel] == 468 || VehicleInfo[uid][vModel] == 471 || VehicleInfo[uid][vModel] == 521 || VehicleInfo[uid][vModel] == 522)
				{
					VehicleInfo[uid][vLocked] = false;
					VehicleInfo[uid][vEngine] = false;
				}
				else if(VehicleInfo[uid][vModel] == 523 || VehicleInfo[uid][vModel] == 581 || VehicleInfo[uid][vModel] == 586 || VehicleInfo[uid][vModel] == 574)
				{
					VehicleInfo[uid][vLocked] = false;
					VehicleInfo[uid][vEngine] = false;
				}
				else
				{
					VehicleInfo[uid][vLocked] = true;
					VehicleInfo[uid][vEngine] = false;
				}
				
				SetVehicleLock(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vLocked]);
				ChangeVehicleEngineStatus(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vEngine]);
				ChangeVehicleLightsStatus(VehicleInfo[uid][vSAMPID],false);
				
				VehicleInfo[uid][vSpawned] = true;
				VehicleInfo[uid][vRecentlyLocked] = false;
				ChangeVehicleColor(VehicleInfo[uid][vSAMPID], VehicleInfo[uid][vColor1], VehicleInfo[uid][vColor2]);
			}
		}
	}
	
	mysql_free_result();
	ForeachEx(j,_VEH_COUNT)
	{
		if(VehicleInfo[j][vUID])
		{
			radio_url=LoadVehRadio(j);
			if(strlen(radio_url)>4)
					VehicleInfo[j][vRadio]=1;
			desc=LoadVehDesc(j);	
			if(strlen(desc)>3)
					VehicleInfo[j][vDesc]=true;
			if(VehicleInfo[j][vSpawned])
			{
				if(VehicleInfo[j][vTuning] & TUNING_VISUAL)
				{
					new query2[64];
					format(query2,sizeof(query2),"SELECT `component_id` FROM `srv_tuning` WHERE `vehicle`='%d'",j);
					mysql_query(query2);
					mysql_store_result();
					while(mysql_fetch_row_format(query2, "|") == 1)
					{
						AddVehicleComponent(VehicleInfo[j][vSAMPID], strval(query2));
					}

					mysql_free_result();
				}
				
				if(VehicleInfo[j][vDesc])
				{
					VehicleInfo[j][vDesc3D]=CreateDynamic3DTextLabel(WordWrap(desc,5), COLOR_VEH_DESC, VehicleInfo[j][vposx], VehicleInfo[j][vposy], VehicleInfo[j][vposz],10.0, INVALID_PLAYER_ID, VehicleInfo[j][vSAMPID]);
				}
			}
		}
	}

	printf("[LOAD] Wczytano %d pojazdów z bazy danych.", i);
	
	return 1;
}

public LoadAnimations()
{
	new data[128], anim_id = 0;
	
	mysql_query("SELECT * FROM `srv_anims`");
	mysql_store_result();
	
	while( mysql_fetch_row_format( data ) )
	{
		anim_id ++;
		sscanf( data, "p<|>ds[12]s[16]s[24]fdddddd", 	AnimInfo[anim_id][aUID],
														AnimInfo[anim_id][aCommand],
														AnimInfo[anim_id][aLib],
														AnimInfo[anim_id][aName],
														AnimInfo[anim_id][aSpeed],
														AnimInfo[anim_id][aOpt1],
														AnimInfo[anim_id][aOpt2],
														AnimInfo[anim_id][aOpt3],
														AnimInfo[anim_id][aOpt4],
														AnimInfo[anim_id][aOpt5],
														AnimInfo[anim_id][aAction]);
	}
	
	mysql_free_result();
	
	printf("[LOAD] Wczytano %d animacji/e.", anim_id);
	return 1;
}
public LoadFuelStations()
{
	new result[128], i = 0;

	mysql_query("SELECT * FROM `srv_fuel_stations`");
	mysql_store_result();
	new uid;
	while(mysql_fetch_row_format(result, "|") == 1)
	{
		sscanf(result, "p<|>d", uid);

		sscanf(result,  "p<|>dddfffd",			StationInfo[uid][sUID],
												StationInfo[uid][sOwner],
												StationInfo[uid][sFuel],
												StationInfo[uid][sPosX],
												StationInfo[uid][sPosY],
												StationInfo[uid][sPosZ],
												StationInfo[uid][sFuelCost]);

		i++;
	}

	mysql_free_result();

	printf("[LOAD] Wczytano %d stacji paliw z bazy danych.", i);
	return 1;
}
public LoadCorners()
{
	new result[256],i;
	mysql_query("SELECT * FROM `srv_corners`");
	mysql_store_result();
	new uid;
	while(mysql_fetch_row_format(result, "|") == 1)
	{
		sscanf(result, "p<|>d", uid);

		sscanf(result,  "p<|>ds[32]dfff",			CornerInfo[uid][cUID],
												CornerInfo[uid][cName],
												CornerInfo[uid][cOwner],
												CornerInfo[uid][cPosX],
												CornerInfo[uid][cPosY],
												CornerInfo[uid][cPosZ]);

		i++;
	}
	printf("[LOAD] Wczytano %d cornerów z bazy danych.", i);

	mysql_free_result();
}
public LoadBusStops()
{
	new result[256],i,string[96];
	mysql_query("SELECT * FROM `srv_bus`");
	mysql_store_result();
	new uid=1;
	while(mysql_fetch_row_format(result, "|") == 1)
	{
		sscanf(result, "p<|>d", uid);

		sscanf(result,  "p<|>ds[32]ffff",		
												BusInfo[uid][bUID],
												BusInfo[uid][bName],
												BusInfo[uid][bPosX],
												BusInfo[uid][bPosY],
												BusInfo[uid][bPosZ],
												BusInfo[uid][bAngle]);

		format(string,sizeof(string),"Przystanek:{ffffff} %s ((/bus))", BusInfo[uid][bName]);
		BusInfo[uid][b3Dtext]=CreateDynamic3DTextLabel(string, 0x1231FFFF, BusInfo[uid][bPosX],  BusInfo[uid][bPosY], BusInfo[uid][bPosZ], 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);								

		i++;
	}
	printf("[LOAD] Wczytano %d przystanków z bazy danych.", i);

	mysql_free_result();
}

stock LoadTextDraws()
{
	TextPenalty = TextDrawCreate(20.000000, 280.000000, "_");
	TextDrawBackgroundColor( TextPenalty, 255);
	TextDrawFont(TextPenalty, 1);
	TextDrawLetterSize( TextPenalty, 0.300000, 1.000000);
	TextDrawColor( TextPenalty, -1);
	TextDrawSetOutline(TextPenalty, 1);
	TextDrawSetProportional(TextPenalty, 1);
	TextDrawSetShadow( TextPenalty, 1);
	TextDrawUseBox( TextPenalty, 1);
	TextDrawBoxColor( TextPenalty, 0);
	TextDrawTextSize(TextPenalty, 350.000000, 0.000000);

	TD_HeadBag = TextDrawCreate(-20.000000,2.000000,"|");
	TextDrawUseBox(TD_HeadBag,1);
	TextDrawBoxColor(TD_HeadBag,0x000000ff);
	TextDrawTextSize(TD_HeadBag,660.000000,22.000000);
	TextDrawAlignment(TD_HeadBag,0);
	TextDrawBackgroundColor(TD_HeadBag,0x000000ff);
	TextDrawFont(TD_HeadBag,3);
	TextDrawLetterSize(TD_HeadBag,1.000000,52.200000);
	TextDrawColor(TD_HeadBag,0x000000ff);
	TextDrawSetOutline(TD_HeadBag,1);
	TextDrawSetProportional(TD_HeadBag,1);
	TextDrawSetShadow(TD_HeadBag,1);
	
	TDEditor_TD[0] = TextDrawCreate(584.708679, 363.427795, "_");
	TextDrawLetterSize(TDEditor_TD[0], 0.000000, 0.000000);
	TextDrawTextSize(TDEditor_TD[0], 51.000000, 55.000000);
	TextDrawAlignment(TDEditor_TD[0], 1);
	TextDrawColor(TDEditor_TD[0], -1061109505);
	TextDrawSetShadow(TDEditor_TD[0], 0);
	TextDrawSetOutline(TDEditor_TD[0], 0);
	TextDrawBackgroundColor(TDEditor_TD[0], 255);
	TextDrawFont(TDEditor_TD[0], 4);
	TextDrawSetProportional(TDEditor_TD[0], 0);
	TextDrawSetShadow(TDEditor_TD[0], 0);

	new rok, mies, dzien;
	getdate(rok, mies, dzien);
	new string_name[32];
	
	format(string_name, sizeof(string_name), "%02d.%02d.%d", dzien, mies, rok);
	
	TDEditor_TD[1] = TextDrawCreate(609.000854, 413.266540, string_name);
	TextDrawLetterSize(TDEditor_TD[1], 0.300000, 1.200000);
	TextDrawAlignment(TDEditor_TD[1], 2);
	TextDrawColor(TDEditor_TD[1], -1061109505);
	TextDrawSetShadow(TDEditor_TD[1], 0);
	TextDrawSetOutline(TDEditor_TD[1], 0);
	TextDrawBackgroundColor(TDEditor_TD[1], 255);
	TextDrawFont(TDEditor_TD[1], 2);
	TextDrawSetProportional(TDEditor_TD[1], 1);
	TextDrawSetShadow(TDEditor_TD[1], 0);
	
	TD_LSN = TextDrawCreate(1.000000, 439.000000, advreklama);
	TextDrawBackgroundColor(TD_LSN, 17);
	TextDrawFont(TD_LSN, 1);
	TextDrawLetterSize(TD_LSN, 0.2, 0.8);
	TextDrawSetOutline(TD_LSN, 1);
	TextDrawSetProportional(TD_LSN, 1);
	TextDrawUseBox(TD_LSN, 1);
	TextDrawBoxColor(TD_LSN, 34);
	TextDrawTextSize(TD_LSN, 650.000000, 1.000000);
	
	TD_LSN2 = TextDrawCreate( 1.000000, 428.000000, advnews);
	TextDrawBackgroundColor(TD_LSN2, 17);
	TextDrawFont(TD_LSN2, 1);
	TextDrawLetterSize(TD_LSN2, 0.2, 0.8);
	TextDrawSetOutline(TD_LSN2, 1);
	TextDrawSetProportional(TD_LSN2, 1);
	TextDrawUseBox(TD_LSN2, 1);
	TextDrawBoxColor(TD_LSN2, 34);
	TextDrawTextSize(TD_LSN2, 650.000000, 1.000000);

	return 1;
}

public Load3DTexts()
{
	new result[128],i;
	mysql_query("SELECT * FROM `srv_3dtext`");
	mysql_store_result();
	new uid=1;
	while(mysql_fetch_row_format(result, "|") == 1)
	{
		sscanf(result, "p<|>d", uid);

		sscanf(result,  "p<|>ds[96]fffdd",		
												Text3DInfo[uid][tUID],
												Text3DInfo[uid][tString],
												Text3DInfo[uid][tPosX],
												Text3DInfo[uid][tPosY],
												Text3DInfo[uid][tPosZ],
												Text3DInfo[uid][tInt],
												Text3DInfo[uid][tVW]);
												
												

		Text3DInfo[uid][t3D]=CreateDynamic3DTextLabel(WordWrap(Text3DInfo[uid][tString],5), 0x9A9CCDFF, Text3DInfo[uid][tPosX], Text3DInfo[uid][tPosY], Text3DInfo[uid][tPosZ], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID,  0, Text3DInfo[uid][tVW], Text3DInfo[uid][tInt]);							

		i++;
	}
	printf("[LOAD] Wczytano %d 3DTextów z bazy danych.", i);

	mysql_free_result();
}

public LoadSafeKeeps()
{
	new data[512], safekeeps = 0;
	new uid;
	
	mysql_query("SELECT * FROM `srv_safekeeps`");
	mysql_store_result();
	
	while(mysql_fetch_row_format(data))
	{
		safekeeps++;
		
		sscanf(data, "p<|>d", uid);
		
		sscanf(data, "p<|>dd", 	SafeKeep[uid][sUID],
					SafeKeep[uid][sInactive]);
	}
	
	mysql_free_result();
	
	printf("[LOAD] Wczytano %d skrytek.", safekeeps);
	return 1;
}

public LoadDescriptions()
{
	new data[1024], descriptions = 0;
	new uid;
	
	mysql_query("SELECT * FROM `srv_descriptions`");
	mysql_store_result();
	
	while(mysql_fetch_row_format(data))
	{
		descriptions++;
		
		sscanf(data, "p<|>d", uid);
		
		sscanf(data, "p<|>dd", 	DescriptionInfo[uid][descUID],
					DescriptionInfo[uid][descOwner]);
		
		_DESC_COUNT = uid + 1;
	}
	
	mysql_free_result();
	
	printf("[LOAD] Wczytano %d opisów.", descriptions);
	return 1;
}

public LoadActors()
{
	new data[512], actors = 0;
	new uid;
	
	mysql_query("SELECT * FROM `srv_actors`");
	mysql_store_result();
	
	while(mysql_fetch_row_format(data))
	{
		
		sscanf(data, "p<|>d", uid);
		
		sscanf(data, "p<|>ds[32]dfffdfd", 	
			ActorInfo[uid][aUID],
			ActorInfo[uid][aName],
			ActorInfo[uid][aSkin],
			ActorInfo[uid][aPosX],
			ActorInfo[uid][aPosY],
			ActorInfo[uid][aPosZ],
			ActorInfo[uid][aVW],
			ActorInfo[uid][aAngle],
			ActorInfo[uid][aAnimId]);
			
		ActorInfo[uid][aActor] = INVALID_ACTOR_ID;
		SpawnActor(uid);
		
		actors++;
	}
	
	mysql_free_result();
	
	printf("[LOAD] Wczytano %d aktorów.", actors);
	return 1;
}

public LoadCustomSkins()
{
	new data[1024], skins = 0;
	new id;
	
	mysql_query("SELECT * FROM `srv_skins`");
	mysql_store_result();
	
	while(mysql_fetch_row_format(data))
	{
		
		sscanf(data, "p<|>d", id);
		
		sscanf(data, "p<|>dddd", 	
			SkinInfo[id][sID],
			SkinInfo[id][sType],
			SkinInfo[id][sUID],
			SkinInfo[id][sModel]);
		
		skins++;
	}
	
	mysql_free_result();
	
	printf("[LOAD] Wczytano %d customowych skinów.", skins);
	return 1;
}