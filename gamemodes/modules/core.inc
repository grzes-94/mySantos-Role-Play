enum skinInfos
{
	sID,
	sType,
	sUID,
	sModel
}
new SkinInfo[MAX_SKINS][skinInfos];

enum callsInfos
{
	cID,
	cCaller,
	cGroup,
	cReason[128],
	cTimeH[3],
	cTimeM[3],
	Float:cPos[3]
}
new CallInfo[MAX_911CALLS][callsInfos];

enum settingInfos 
{
	sStatus,
	Float:sSpawnX,
	Float:sSpawnY,
	Float:sSpawnZ,
	Float:sSpawnAngle,
	Float:sMagazineX,
	Float:sMagazineY,
	Float:sMagazineZ,
	sPremiumEventDays,
	sLSNPrice,
	sDocID,
	sDocDriver,
	sDocPilot,
	sFuelCost,
	sHotelPrice,
	sInsurance,
	sTaxes,
	sPlateCharge,
	sGroupRegisterCharge,
	sDocWeapons,
	sDocMed,
	sHealPrice,
	sSANNPay,
	bool:sGovBots
}
new SettingInfo[settingInfos];

enum characterInfo
{
	pUID,
	pGID,
	pNick[32],
	pAge,
	pSex,
	pSkin,
	pCash,
	pHours,
	pMinutes,
	Float:pHealth,
	Float:pArmor,
	bool:pHaveArmor,
	pAdmin,
	pHide,
	pCredit,
	pDeathTimer,
	pWoundedTimer,
	pWounded,
	pBW,
	pAJ,
	pGlod,
	
	Float:pPos[3],
	pVW,
	pInt,
	
	pTog,
	
	pBlock,
	pWarn,
	pCurse,
	
	pBlockNoGun,
	pBlockNoCar,
	pBlockNoOOC,
	pBlockNoRun,
	
	bool:pCiagnij,
	bool:pWorek,
	pCelebrity,
	
	pLastW,
	
	pPhone,
	
	pStatus,
	
	pStrength,
	pStrengthToday,
	
	bool:pAFK,
	pAFKg,
	pAFKm,

	Float:pPrevPos[3],
	pAFKWarn,
	pWeaponCheatWarn,
	pAimBotWarn,
	
	pLastUpdate,
	
	pKajdankiID,
	
	pNickColor,
	
	bool:pAdminDuty,
	
	bool:pSpec,
	
	bool:pHaveWeapon,
	pWeaponAmmo,
	pWeaponID,
	pWeaponUID,
	
	pEngineTime,
	
	pHouseCheck,
	pHouseCheckID,
	
	pShowDoors,
	
	pReanimation,
	pReanimationID,
	
	pJail,
	pJailTime,

	pRepairVeh,
	pRepairTime,
	pRepairType,
	Text3D:pRepair3DText,

	pJob,
	pJobCount,
	pJobPhase,
	
	pDrugs,
	pDrugsTime,

	pCorner,
	pCornerTimer,
	
	pPytanie,
	pReport,
	
	pSpawnOption,
	pSpawnOptionHouseID,
	
	pGlobalNick[32],
	pPremium,
	pGlobalScore,
	
	pOnlineToday,
	
	bool:pMask,
	bool:pMaskObj,
	
	pKanal,
	
	pDamageTook,
	bool:pDamaged,

	pDocs,
	
	pAnimacja,

	pTaxiPassenger,
	pTaxiDistance,
	
	pMsgspy,
	pHotel,
	bool:pHotelUnlocked,

	pCheckpoint,
	pAttached[10],

	pGymPass,
	pGymType,
	pGymObject,
	pGymPhase,
	pGymValue,
	
	pLastMsg,
	pAntiFloodWarn,
	
	pWalkStyle,

	pPenaltyPoints,
	pDriverPenalty,
	
	pGPS,
	p911Icon,
	p911,
	pIgnore,
	pFightStyle,
	bool:pAlreadyHidedNick,
	pHidedNick[32],
	pSuplement,
	pCurrentDescription[128],
	Float:pLastDMG,
	pLastHB,
	pLastWEAP,
	
	bool:pHaveTaser,
	pTaserSlot,
	
	pLastNumberCalled,
	
	bool:pNickDamageTook,
	
	pFakeKill,
	pCarWarp,
	pCarSwing,
	
	bool:pAdminMessageTog,
	
	bool:pPenalty,
	bool:pDoorEnter,
	//pACWarn,
	pACTimer,
	pACLastJustification
}
new CharacterInfo[MAX_PLAYERS][characterInfo];
new ClearInfo[characterInfo];

enum groupinfo
{
	gUID,
	gName[32],
	gTag[8],
	gType,
	gCash,
	gFlags,
	gLeader,
	Float:gSpawnX,
	Float:gSpawnY,
	Float:gSpawnZ,
	Float:gSpawnAngle,
	gSpawnInt,
	gSpawnVW,
	gColor,
	gObjects,
	gNotice[64],
	gRegistered,
	gGrant,
	gSalaryAccount,
	gOOCBlock,
	gTransportTowary
}
new GroupInfo[MAX_GROUPS][groupinfo];

enum memberInfo
{
	GroupID,
	GroupRankName[32],
	GroupRank,
	GroupPerm,
	GroupSkin,
	GroupTime,
	GroupSalary,
	GroupPayment,
	GroupCommission
}
new MemberGroup[MAX_PLAYERS][MAX_PLAYER_GROUPS][memberInfo];

new DutyGroup[MAX_PLAYERS];
new DutyGroupTime[MAX_PLAYERS];

enum safekeepInfo
{
	sUID,
	sInactive
}
new SafeKeep[MAX_SAFEKEEPS][safekeepInfo];

new WS_MAPICONS[MAX_PLAYERS][MAX_WS_MAPICONS];

new DOORS_MAPICONS[MAX_PLAYERS][MAX_DOORS_MAPICONS];

enum descriptionInfo
{
	descUID,
	descOwner
}
new DescriptionInfo[MAX_DESCRIPTIONS][descriptionInfo];

enum stationInfo
{
	sUID,
	sOwner,
	sFuel,
	Float:sPosX,
	Float:sPosY,
	Float:sPosZ,
	sFuelCost
}
new StationInfo[MAX_STATIONS][stationInfo];

enum busInfo
{
	bUID,
	bName[32],
	Float:bPosX,
	Float:bPosY,
	Float:bPosZ,
	Float:bAngle,
	Text3D:b3Dtext
}
new BusInfo[MAX_BUS_STOPS][busInfo];

enum grouptype
{
	gTypeName[32]
}
new GroupTypeInfo[GROUP_COUNT+1][grouptype] =
{
	"Nieokreœlona",
	"Government",
	"Police",
	"Medic",
	"News",
	"FBI",
	"Military",
	"Gang",
	"Mafia",
	"Szajka zmotoryzowana",
	"Sklep",
	"Warsztat",
	"Taxi",
	"Ochrona",
	"Komis samochodowy",
	"Logistyka",
	"Bank",
	"Si³ownia",
	"Restauracja",
	"Stacja benzynowa",
	"Syndykat",
	"Kasyno",
	"Kartel",
	"Klub",
	"Sklep z broni¹"
};

enum sItemTypeInfo
{
	iTypeName[24]
}
new ItemTypeInfo[TYPE_COUNT+1][sItemTypeInfo] =
{
	"Brak",
	"Broñ",
	"Telefon",
	"Maska",
	"Jedzenie",
	"Kostka do gry",
	"Karty",
	"Lekarstwo",
	"Kamizelka",
	"Zegarek",
	"Kanister",
	"Papierosy",
	"Alkohol",
	"Nasionko marihuany",
	"Marihuana",
	"Kokaina",
	"Heroina",
	"LSD",
	"Krótkofalówka",
	"Megafon",
	"Suplementy",
	"Boombox",
	"Amunicja",
	"Tuning",
	"T³umik do 9mm",
	"Kluczyki",
	"Przedmiot doczepiany",
	"Zestaw naprawczy",
	"Kluczyk do skrytki",
	"Przyciemniane szyby",
	"Ubranie"
};

enum iteminfo
{
	iUID,
	iName[32],
	iType,
	iValue1,
	iValue2,
	iUsed,
	iOwnerTyp,
	iOwner,
	iIlosc,
	iPrice,
	Float:iPosx,
	Float:iPosy,
	Float:iPosz,
	iVW,
	Text3D:iDroppedInfo
}
new ItemInfo[MAX_ITEMS][iteminfo];

enum plantsInfo
{
	plantUID,
	plantTime,
	plantOwner,
	Float:plantx,
	Float:planty,
	Float:plantz,
	plantVW,
	plantInt,
	plantObject,
	Text3D:planttext
}
new PlantInfo[MAX_PLANTS][plantsInfo];

enum corpseInfo
{
	corpseID,
	corpsePlayerUID,
	corpsePlayerName[MAX_PLAYER_NAME],
	corpseReason[128],
	corpseGun[32],
	corpseGunVal,
	corpseDate[16],
	corpseMoney,
	Float:corpseX,
	Float:corpseY,
	Float:corpseZ,
	corpseInt,
	corpseVW,
	corpseObject,
	Text3D:corpseText
}
new CorpseInfo[MAX_CORPSE][corpseInfo];

enum cornerInfo
{
	cUID,
	cName[32],
	cOwner,
	Float:cPosX,
	Float:cPosY,
	Float:cPosZ,
	cIcon
}
new CornerInfo[MAX_CORNERS][cornerInfo];

enum VehicleInfos
{
	vSAMPID,
	vUID,
	vModel,
	vColor1,
	vColor2,
	Float:vHP,
	vVisual[4],
	vOwner,
	vOwnerTyp,
	Float:vposx,
	Float:vposy,
	Float:vposz,
	Float:vAngle,
	vVW,
	vInt,
	vRegister[8],
	vRadio,
	bool:vEngine,
	bool:vLocked,
	vTuning,
	vLastDriver,
	
	vBlokada,
	vRank,
	bool:vDesc,
	Text3D:vDesc3D,

	vPolice,
	
	Float:vFuel,
	Float:vDistance,
	
	bool:vSpawned,
	vRegistered,
	
	bool:vGlass,
	bool:vRecentlyLocked,
	bool:vHandBrake,
	Float:vHB[4]
}
new VehicleInfo[MAX_VEHICLES][VehicleInfos];
new VehicleUIDs[MAX_SPAWNED_VEH];

enum dInfo
{
	dUID,
	
	dName[31],
	dOwnerTyp,
	dOwner,

	Float:dEnterX,
	Float:dEnterY,
	Float:dEnterZ,
	Float:dEnterAngle,

	dEnterInt,
	dEnterVW,

	Float:dExitX,
	Float:dExitY,
	Float:dExitZ,
	Float:dExitAngle,

	dExitInt,
	dExitVW,

	dLock,
	dPickupID,
	dPickup,
	dRadio[128],
	dGarage,
	dIconID,
	dPriceForEntry,
	dTime,
	dWeather,
	dObj0,
	dObj
}
new DoorsInfo[MAX_DOORS][dInfo];
new PlayerDoor[MAX_PLAYERS];

enum animGameInfo
{
	/* BAZOWE */
	aUID,
	aCommand[12],
	aLib[16],
	aName[24],
	Float:aSpeed,
	aOpt1,
	aOpt2,
	aOpt3,
	aOpt4,
	aOpt5,
	aAction
	
	/* POZOSTA£E */
}
new AnimInfo[MAX_ANIMS][animGameInfo];

enum oInfo
{
	oObject,
	oUID,
	oModel,
	Float:oX,
	Float:oY,
	Float:oZ,
	Float:oRX,
	Float:oRY,
	Float:oRZ,
	oInt,
	oVW,
	
	oOwnerType,
	oOwner,
	
	oGate,
	bool:oGateOpen,
	
	Float:oGateX,
	Float:oGateY,
	Float:oGateZ,
	
	Float:oGateRX,
	Float:oGateRY,
	Float:oGateRZ,
	
	oMMAT,
	oCreator,
	oLastEditor,
	Text3D:o3dText,
	o3dTextPlayer
}
new ObjectInfo[MAX_OBJECTS][oInfo];
new PlayerEditObject[MAX_PLAYERS];
new PlayerEditGate[MAX_PLAYERS];

enum T3dInfo
{
	tUID,
	Text3D: t3D,
	tString[96],
	Float: tPosX,
	Float: tPosY,
	Float: tPosZ,
	tInt,
	tVW
}
new Text3DInfo[MAX_A3D][T3dInfo];


enum ROADBLOCK_INFO
{
	rObject,
	Float:rPosX,
	Float:rPosY,
	Float:rPosZ,
	Text3D:r3DText
}
new RoadBlock[MAX_ROADBLOCKS][ROADBLOCK_INFO];

enum SALON_INFO
{
	Float:SX,
	Float:SY,
	Float:SZ,
	Float:SA
}
new SalonInfo[][SALON_INFO] = {
		{ 1702.0, -1120.0, 24.07, 180.0 },
		{ 1710.0, -1120.0, 24.07, 180.0 },
		{ 1718.0, -1120.0, 24.07, 180.0 },
		{ 1726.0, -1120.0, 24.07, 180.0 },
		{ 1734.0, -1120.0, 24.07, 180.0 },
		{ 1742.0, -1120.0, 24.07, 180.0 },
		{ 1750.0, -1120.0, 24.07, 180.0 }
};

enum INTERIOR_INFO
{
	INTERIOR_ID,
	Float:INTERIOR_X,
	Float:INTERIOR_Y,
	Float:INTERIOR_Z,
	Float:INTERIOR_A,
	INTERIOR_NAME[32]
}
new Interior[][INTERIOR_INFO] = {
		{ 11, 2003.1178, 1015.1948, 33.008, 351.5789, "Four Dragons' Managerial" },
		{ 5, 770.8033, -0.7033, 1000.7267, 22.8599, "Ganton Gym" },
		{ 3, 974.0177, -9.5937, 1001.1484, 22.6045, "Brothel" },
		{ 3, 961.9308, -51.9071, 1001.1172, 95.5381, "Brothel2" },
		{ 3, 830.6016, 5.9404, 1004.1797, 125.8149, "Inside Track Betting" },
		{ 3, 1037.8276, 0.397, 1001.2845, 353.9335, "Blastin' Fools Records" },
		{ 3, 1212.1489, -28.5388, 1000.9531, 170.5692, "The Big Spread Ranch" },
		{ 18, 1290.4106, 1.9512, 1001.0201, 179.9419, "Warehouse 1" },
		{ 1, 1412.1472, -2.2836, 1000.9241, 114.661, "Warehouse 2" },
		{ 3, 1527.0468, -12.0236, 1002.0971, 350.0013, "B Dup's Apartment" },
		{ 2, 1523.5098, -47.8211, 1002.2699, 262.7038, "B Dup's Crack Palace" },
		{ 3, 612.2191, -123.9028, 997.9922, 266.5704, "Wheel Arch Angels" },
		{ 3, 512.9291, -11.6929, 1001.5653, 198.7669, "OG Loc's House" },
		{ 3, 418.4666, -80.4595, 1001.8047, 343.2358, "Barber Shop" },
		{ 3, 386.5259, 173.6381, 1008.3828, 63.7399, "Planning Department" },
		{ 3, 288.4723, 170.0647, 1007.1794, 22.0477, "Las Venturas Police Department" },
		{ 3, 206.4627, -137.7076, 1003.0938, 10.9347, "Pro-Laps" },
		{ 3, -100.2674, -22.9376, 1000.7188, 17.285, "Sex Shop" },
		{ 3, -201.2236, -43.2465, 1002.2734, 45.8613, "Las Venturas Tattoo parlor" },
		{ 17, -202.9381, -6.7006, 1002.2734, 204.2693, "Lost San Fierro Tattoo parlor" },
		{ 17, -25.7220, -187.8216, 1003.5469, 5.0760, "24/7 (version 1)" },
		{ 5, 454.9853, -107.2548, 999.4376, 309.0195, "Diner 1" },
		{ 5, 372.5565, -131.3607, 1001.4922, 354.2285, "Pizza Stack" },
		{ 17, 378.026, -190.5155, 1000.6328, 141.0245, "Rusty Brown's Donuts" },
		{ 7, 315.244, -140.8858, 999.6016, 7.4226, "Ammu-nation" },
		{ 5, 225.0306, -9.1838, 1002.218, 85.5322, "Victim" },
		{ 2, 611.3536, -77.5574, 997.9995, 320.9263, "Loco Low Co" },
		{ 10, 246.0688, 108.9703, 1003.2188, 0.2922, "San Fierro Police Department" },
		{ 10, 6.0856, -28.8966, 1003.5494, 5.0365, "24/7 (version 2 - large)" },
		{ 7, 773.7318, -74.6957, 1000.6542, 5.2304, "Below The Belt Gymr" },
		{ 1, 621.4528, -23.7289, 1000.9219, 15.6789, "Transfenders" },
		{ 1, 445.6003, -6.9823, 1000.7344, 172.2105, "World of Coq" },
		{ 1, 285.8361, -39.0166, 1001.5156, 0.7529, "Ammu-nation (version 2)" },
		{ 1, 204.1174, -46.8047, 1001.8047, 357.5777, "SubUrban" },
		{ 1, 245.2307, 304.7632, 999.1484, 273.4364, "Denise's Bedroom" },
		{ 3, 290.623, 309.0622, 999.1484, 89.9164, "Helena's Barn" },
		{ 5, 322.5014, 303.6906, 999.1484, 8.1747, "Barbara's Love nest" },
		{ 1, -2041.2334, 178.3969, 28.8465, 156.2153, "San Fierro Garage" },
		{ 1, -1402.6613, 106.3897, 1032.2734, 105.1356, "Oval Stadium" },
		{ 7, -1403.0116, -250.4526, 1043.5341, 355.8576, "8-Track Stadium" },
		{ 2, 1204.6689, -13.5429, 1000.9219, 350.0204, "The Pig Pen (strip club 2)" },
		{ 10, 2016.1156, 1017.1541, 996.875, 88.0055, "Four Dragons" },
		{ 1, -741.8495, 493.0036, 1371.9766, 71.7782, "Liberty City" },
		{ 2, 2447.8704, -1704.4509, 1013.5078, 314.5253, "Ryder's house" },
		{ 1, 2527.0176, -1679.2076, 1015.4986, 260.9709, "Sweet's House" },
		{ 10, -1129.8909, 1057.5424, 1346.4141, 274.5268, "RC Battlefield" },
		{ 3, 2496.0549, -1695.1749, 1014.7422, 179.2174, "The Johnson House" },
		{ 10, 366.0248, -73.3478, 1001.5078, 292.0084, "Burger shot" },
		{ 1, 2233.9363, 1711.8038, 1011.6312, 184.3891, "Caligula's Casino" },
		{ 2, 269.6405, 305.9512, 999.1484, 215.6625, "Katie's Lovenest" },
		{ 2, 414.2987, -18.8044, 1001.8047, 41.4265, "Barber Shop 2 (Reece's)" },
		{ 2, 1.1853, -3.2387, 999.4284, 87.5718, "Angel \"Pine Trailer\"" },
		{ 18, -30.9875, -89.6806, 1003.5469, 359.8401, "24/7 (version 3)" },
		{ 18, 161.4048, -94.2416, 1001.8047, 0.7938, "Zip" },
		{ 3, -2638.8232, 1407.3395, 906.4609, 94.6794, "The Pleasure Domes" },
		{ 5, 1267.8407, -776.9587, 1091.9063, 231.3418, "Madd Dogg's Mansion" },
		{ 2, 2536.5322, -1294.8425, 1044.125, 254.9548, "Big Smoke's Crack Palace" },
		{ 5, 2350.1597, -1181.0658, 1027.9766, 99.1864, "Burning Desire Building" },
		{ 1, -2158.6731, 642.09, 1052.375, 86.5402, "Wu-Zi Mu's" },
		{ 10, 419.8936, 2537.1155, 10.0, 67.6537, "Abandoned AC tower" },
		{ 14, 256.9047, -41.6537, 1002.0234, 85.8774, "Wardrobe/Changing room" },
		{ 14, 204.1658, -165.7678, 1000.5234, 181.7583, "Didier Sachs" },
		{ 12, 1133.35, -7.8462, 1000.6797, 165.8482, "Casino (Redsands West)" },
		{ 14, -1420.4277, 1616.9221, 1052.5313, 159.1255, "Kickstart Stadium" },
		{ 17, 493.1443, -24.2607, 1000.6797, 356.9864, "Club" },
		{ 18, 1727.2853, -1642.9451, 20.2254, 172.4193, "Atrium" },
		{ 16, -202.842, -24.0325, 1002.2734, 252.8154, "Los Santos Tattoo Parlor" },
		{ 5, 2233.6919, -1112.8107, 1050.8828, 8.6483, "Safe House group 1" },
		{ 6, 1211.2484, 1049.0234, 359.941, 170.9341, "Safe House group 2" },
		{ 9, 2319.1272, -1023.9562, 1050.2109, 167.3959, "Safe House group 3" },
		{ 10, 2261.0977, -1137.8833, 1050.6328, 266.88, "Safe House group 4" },
		{ 17, -944.2402, 1886.1536, 5.0051, 179.8548, "Sherman Dam" },
		{ 16, -26.1856, -140.9164, 1003.5469, 2.9087, "24/7 (version 4)" },
		{ 15, 2217.281, -1150.5349, 1025.7969, 273.7328, "Jefferson Motel" },
		{ 1, 1.5491, 23.3183, 1199.5938, 359.9054, "Jet Interior" },
		{ 1, 681.6216, -451.8933, -25.6172, 166.166, "The Welcome Pump" },
		{ 3, 234.6087, 1187.8195, 1080.2578, 349.4844, "Burglary House X1" },
		{ 2, 225.5707, 1240.0643, 1082.1406, 96.2852, "Burglary House X2" },
		{ 1, 224.288, 1289.1907, 1082.1406, 359.868, "Burglary House X3" },
		{ 5, 239.2819, 1114.1991, 1080.9922, 270.2654, "Burglary House X4" },
		{ 15, 207.5219, -109.7448, 1005.1328, 358.62, "Binco" },
		{ 15, 295.1391, 1473.3719, 1080.2578, 352.9526, "4 Burglary houses" },
		{ 15, -1417.8927, 932.4482, 1041.5313, 0.7013, "Blood Bowl Stadium" },
		{ 12, 446.3247, 509.9662, 1001.4195, 330.5671, "Budget Inn Motel Room" },
		{ 0, 2306.3826, -15.2365, 26.7496, 274.49, "Palamino Bank" },
		{ 0, 2331.8984, 6.7816, 26.5032, 100.2357, "Palamino Diner" },
		{ 0, 663.0588, -573.6274, 16.3359, 264.9829, "Dillimore Gas Station" },
		{ 18, -227.5703, 1401.5544, 27.7656, 269.2978, "Lil' Probe Inn" },
		{ 0, -688.1496, 942.0826, 13.6328, 177.6574, "Torreno's Ranch" },
		{ 0, -1916.1268, 714.8617, 46.5625, 152.2839, "Zombotech - lobby area" },
		{ 0, 818.7714, -1102.8689, 25.794, 91.1439, "Crypt in LS cemetery (temple)" },
		{ 0, 255.2083, -59.6753, 1.5703, 1.4645, "Blueberry Liquor Store" },
		{ 2, 446.626, 1397.738, 1084.3047, 343.9647, "Pair of Burglary Houses" },
		{ 5, 318.564971, 1118.209960, 1083.882812, 0.0, "Crack Den" },
		{ 5, 227.7559, 1114.3844, 1080.9922, 266.2624, "Burglary House X11" },
		{ 4, 261.1165, 1287.2197, 1080.2578, 178.9149, "Burglary House X12" },
		{ 4, 291.7626, -80.1306, 1001.5156, 290.2195, "Ammu-nation (version 3)" },
		{ 4, 449.0172, -88.9894, 999.5547, 89.6608, "Jay's Diner" },
		{ 4, -27.844, -26.6737, 1003.5573, 184.3118, "24/7 (version 5)" },
		{ 0, 2135.2004, -2276.2815, 20.6719, 318.59, "Warehouse 3" },
		{ 4, 306.1966, 307.819, 1003.3047, 203.1354, "Michelle's Love Nest*" },
		{ 10, 24.3769, 1341.1829, 1084.375, 8.3305, "Burglary House X14" },
		{ 1, 963.0586, 2159.7563, 1011.0303, 175.313, "Sindacco Abatoir" },
		{ 0, 2548.4807, 2823.7429, 10.8203, 270.6003, "K.A.C.C. Military Fuels Depot" },
		{ 0, 215.1515, 1874.0579, 13.1406, 177.5538, "Area 69" },
		{ 4, 221.6766, 1142.4962, 1082.6094, 184.9618, "Burglary House X13" },
		{ 12, 2323.7063, -1147.6509, 1050.7101, 206.5352, "Unused Safe House" },
		{ 6, 344.9984, 307.1824, 999.1557, 193.643, "Millie's Bedroom" },
		{ 12, 411.9707, -51.9217, 1001.8984, 173.3449, "Barber Shop" },
		{ 4, -1421.5618, -663.8262, 1059.5569, 170.9341, "Dirtbike Stadium" },
		{ 6, 773.8887, -47.7698, 1000.5859, 10.7161, "Cobra Gym" },
		{ 6, 246.6695, 65.8039, 1003.6406, 7.9562, "Los Santos Police Department" },
		{ 14, -1864.9434, 55.7325, 1055.5276, 85.8541, "Los Santos Airport" },
		{ 4, -262.1759, 1456.6158, 1084.3672, 82.459, "Burglary House X15" },
		{ 5, 22.861, 1404.9165, 1084.4297, 349.6158, "Burglary House X16" },
		{ 5, 140.3679, 1367.8837, 1083.8621, 349.2372, "Burglary House X17" },
		{ 3, 1494.8589, 1306.48, 1093.2953, 196.065, "Bike School" },
		{ 14, -1813.213, -58.012, 1058.9641, 335.3199, "Francis International Airport" },
		{ 16, -1401.067, 1265.3706, 1039.8672, 178.6483, "Vice Stadium" },
		{ 6, 234.2826, 1065.229, 1084.2101, 4.3864, "Burglary House X18" },
		{ 6, -68.5145, 1353.8485, 1080.2109, 3.5742, "Burglary House X19" },
		{ 6, -2240.1028, 136.973, 1035.4141, 269.0954, "Zero's RC Shop" },
		{ 6, 297.144, -109.8702, 1001.5156, 20.2254, "Ammu-nation (version 4)" },
		{ 6, 316.5025, -167.6272, 999.5938, 10.3031, "Ammu-nation (version 5)" },
		{ 15, -285.2511, 1471.197, 1084.375, 85.6547, "Burglary House X20" },
		{ 6, -26.8339, -55.5846, 1003.5469, 3.9528, "24/7 (version 6)" },
		{ 6, 442.1295, -52.4782, 999.7167, 177.9394, "Secret Valley Diner" },
		{ 2, 2182.2017, 1628.5848, 1043.8723, 224.8601, "Rosenberg's Office in Caligulas" },
		{ 6, 748.4623, 1438.2378, 1102.9531, 0.6069, "Fanny Batter's Whore House" },
		{ 8, 2807.3604, -1171.7048, 1025.5703, 193.7117, "Colonel Furhberger's" },
		{ 9, 366.0002, -9.4338, 1001.8516, 160.528, "Cluckin' Bell" },
		{ 1, 2216.1282, -1076.3052, 1050.4844, 86.428, "The Camel's Toe Safehouse" },
		{ 1, 2268.5156, 1647.7682, 1084.2344, 99.7331, "Caligula's Roof" },
		{ 2, 2236.6997, -1078.9478, 1049.0234, 2.5706, "Old Venturas Strip Casino" },
		{ 3, -2031.1196, -115.8287, 1035.1719, 190.1877, "Driving School" },
		{ 8, 2365.1089, -1133.0795, 1050.875, 177.3947, "Verdant Bluffs Safehouse" },
		{ 0, 1168.512, 1360.1145, 10.9293, 196.5933, "Bike School" },
		{ 9, 315.4544, 976.5972, 1960.8511, 359.6368, "Andromada" },
		{ 10, 1893.0731, 1017.8958, 31.8828, 86.1044, "Four Dragons' Janitor's Office" },
		{ 11, 501.9578, -70.5648, 998.7578, 171.5706, "Bar" },
		{ 8, -42.5267, 1408.23, 1084.4297, 172.068, "Burglary House X21" },
		{ 11, 2283.3118, 1139.307, 1050.8984, 19.7032, "Willowfield Safehouse" },
		{ 9, 84.9244, 1324.2983, 1083.8594, 159.5582, "Burglary House X22" },
		{ 9, 260.7421, 1238.2261, 1084.2578, 84.3084, "Burglary House X23" },
		{ 0, -1658.1656, 1215.0002, 7.25, 103.9074, "Otto's Autos" },
		{ 0, -1961.6281, 295.2378, 35.4688, 264.4891, "Wang Cars" }
};

new VehicleName[213][32] = {
"Landstalker","Bravura","Buffalo","Linerunner","Pereniel","Sentinel","Dumper","Firetruck","Trashmaster","Stretch","Manana",
"Infernus","Voodoo","Pony","Mule","Cheetah","Ambulance","Leviathan","Moonbeam","Esperanto","Taxi","Washington","Bobcat",
"Mr Whoopee","BF Injection","Hunter","Premier","Enforcer","Securicar","Banshee","Predator","Bus","Rhino","Barracks",
"Hotknife","Trailer","Previon","Coach","Cabbie","Stallion","Rumpo","RC Bandit","Romero","Packer","Monster","Admiral",
"Squalo","Seasparrow","Pizzaboy","Tram","Trailer","Turismo","Speeder","Reefer","Tropic","Flatbed","Yankee","Caddy",
"Solair","Berkley's RC Van","Skimmer","PCJ-600","Faggio","Freeway","RC Baron","RC Raider","Glendale","Oceanic",
"Sanchez","Sparrow","Patriot","Quad","Coastguard","Dinghy","Hermes","Sabre","Rustler","ZR-350","Walton","Regina",
"Comet","BMX","Burrito","Camper","Marquis","Baggage","Dozer","Maverick","News Chopper","Rancher","FBI Rancher",
"Virgo","Greenwood","Jetmax","Hotring","Sandking","Blista Compact","Police Maverick","Boxville","Benson","Mesa",
"RC Goblin","Hotring Racer","Hotring Racer","Bloodring Banger","Rancher","Super GT","Elegant","Journey","Bike",
"Mountain Bike","Beagle","Cropdust","Stunt","Tanker","RoadTrain","Nebula","Majestic","Buccaneer","Shamal","Hydra",
"FCR-900","NRG-500","HPV1000","Cement Truck","Tow Truck","Fortune","Cadrona","FBI Truck","Willard","Forklift","Tractor",
"Combine","Feltzer","Remington","Slamvan","Blade","Freight","Streak","Vortex","Vincent","Bullet","Clover","Sadler",
"Firetruck","Hustler","Intruder","Primo","Cargobob","Tampa","Sunrise","Merit","Utility","Nevada","Yosemite","Windsor",
"Monster","Monster","Uranus","Jester","Sultan","Stratum","Elegy","Raindance","RC Tiger","Flash","Tahoma","Savanna",
"Bandito","Freight","Trailer","Kart","Mower","Duneride","Sweeper","Broadway","Tornado","AT-400","DFT-30","Huntley",
"Stafford","BF-400","Newsvan","Tug","Trailer","Emperor","Wayfarer","Euros","Hotdog","Club","Trailer","Trailer",
"Andromeda","Dodo","RC Cam","Launch","Police Car","Police Car","Police Car","Police Ranger","Picador","S.W.A.T. Van",
"Alpha","Phoenix","Glendale","Sadler","Luggage Trailer","Luggage Trailer","Stair Trailer","Boxville","Farm Plow","Utility Trailer","ERROR"};

new Checkpoint[MAX_PLAYERS];

new maleskinlist = mS_INVALID_LISTID;
new femaleskinlist = mS_INVALID_LISTID;
new doczepialne_0 = mS_INVALID_LISTID;
new doczepialne_1 = mS_INVALID_LISTID;
new doczepialne_2 = mS_INVALID_LISTID;
new doczepialne_3 = mS_INVALID_LISTID;
new doczepialne_4 = mS_INVALID_LISTID;

new Text3D:quit[MAX_PLAYERS];
new quited[MAX_PLAYERS];

enum Coords
{
	SPU,
	VehicleID,
	sObject,
	Float:sX,
	Float:sY,
	Float:sZ,
}
new SyrenaPos[][Coords] = {
	{0, 0 ,0, 0.0, 0.0, 0.0},
	{1, 599 ,19419, 0.0, 0.05, 1.1},
	{2, 415, 18646, 0.409729004, 0.526367188, 0.206963539},
	{3, 421, 18646, 0.421691895, 0.804931641, 0.256482124},
	{4, 426, 18646, 0.575378418, 0.786132812, 0.361483574},
	{5, 579, 18646, 0.454345703, 0.575683594, 0.645122528},
	{6, 402, 18646, 0.53515625, 0.562988281, 0.278743744},
	{7, 596, 19419, 0.0, -0.39, 0.89},
	{8, 597, 19419, 0.0, -0.39, 0.89},
	{9, 598, 19419, 0.0, -0.39, 0.89},
	{10, 544, 11701, 0.0, 2.9, 1.500000},
	{11, 409, 18646, -0.439941406, 0.824829102, 0.842817307},
	{12, 461, 18646, 0.00000000, -0.932861328, 0.494509697},
	{13, 521, 18646, 0.00000000, -0.928955078, 0.558652878},
	{14, 586, 18646, 0.00000000, -1.20178223, 0.671886444},
	{15, 506, 18646, 0.541137695, 0.282714844, 0.272130013},
	{16, 482, 18646, 0.493530273, 1.39465332, 0.442443848},
	{17, 424, 18646, -0.624511719, 0.139648438, 0.918135643},
	{18, 470, 18646, -0.617797851, 0.056640625, 1.10928631},
	{19, 433, 18646, -0.577392578, 1.23217773, 1.70311642},
	{20, 432, 18646, -1.21105957, -3.84765625, 1.17495251},
	{21, 560, 18646, 0.398071289, 0.75390625, 0.43879509},
	{22, 490, 18646, 0.4, 1.2, 0.6},
	{23, 561, 18646, 0.4, 1.0, 0.3},
	{24, 405, 18646, 0.4, 0.6, 0.3},
	{25, 445, 18646, 0.398071289, 0.75390625, 0.43879509},
	{26, 541, 18646, 0.409729004, 0.526367188, 0.206963539},
	{27, 400, 18646, 0.493530273, 1.39465332, 0.442443848},
	{28, 525, 18646, 0.493530273, 1.39465332, 0.442443848},
	{29, 552, 18646, 0.493530273, 1.39465332, 0.442443848}
};

enum TRANSPORT_CORDS
{
	Float:TransportX,
	Float:TransportY,
	Float:TransportZ
};
new TransportCP[][TRANSPORT_CORDS]={
	{1238.0292,185.0746,19.5547},
	{1722.5802,724.5306,10.8203},
	{1415.0750,1050.0060,10.8130},
	{1069.7983,1293.0026,10.8203},
	{2399.1050,2804.6887,10.8203},
	{2822.3235,958.9893,10.7500},
	{-1737.3535,1411.8256,7.1875},
	{-1925.4897,267.9337,41.0469},
	{-1734.3585,-122.6703,3.5547},
	{-2137.5017,-440.7500,35.3359},
	{-2027.4816,-1006.7349,32.0234},
	{-2100.8616,-2244.3682,30.6250},
	{-543.9796,-493.4475,25.5234},
	{-190.5698,-218.5324,1.4219},
	{172.3785,-20.9787,1.5781}
};
new FuelTransportCP[][TRANSPORT_CORDS]={
	{276.9873,1465.9506,10.5859}, 
	{-1031.4675,-681.3223,32.0078,}
};

enum RADIO_STATIONS
{
	radioName[32],
	radioURL[128]
}
new RadioStations[][RADIO_STATIONS] = {
	{"ROCK","http://sc15.shoutcaststreaming.us:8140/stream/"},
	{"POP","http://stream01.iloveradio.de/iloveradio11.mp3"},
	{"RADIO MEXICO","http://149.56.195.94:8029/listen.pls"},
	{"ELECTRO","http://streaming.radionomy.com/ElectroPartyHits"},
	{"COUNTRY","http://dir.xiph.org/listen/1923/listen.m3u"},
	{"HIPHOP TURNUP"," http://stream01.iloveradio.de/iloveradio13.mp3"},
	{"HIPHOP Traditional","http://traditionalhiphop.zapto.org:7500/listen.pls"},
	{"HARDER MUSIC","http://stream01.iloveradio.de/iloveradio17.mp3"},
	{"DANCE","http://stream01.iloveradio.de/iloveradio2.mp3"},
	{"URBAN CLUB BEATS","http://streams.bigfm.de/urbanilr-128-mp3"},
	{"CHICANO","http://listen.radionomy.com/chicanorap-talkbox-funkradio.m3u"},
	{"LA CIBERNETICA","http://stream.radiojar.com/s2mxp0q390duv.m3u"},
	{"URBAN CLUB BEATS","http://streams.bigfm.de/urbanilr-128-mp3"}
};

enum POS_CORDS
{
	Float:posX,
	Float:posY,
	Float:posZ
};
new DocksJob[][POS_CORDS]=
{
	{2773.9163,-2337.1418,13.6421}, 
	{2780.4023,-2336.7703,13.6521}, 
	{2787.6631,-2334.5779,13.6521},
	{2790.2947,-2341.8337,13.6521}, 
	{2790.2058,-2349.5381,13.6521},
	{2787.6433,-2356.0952,13.6521},
	{2780.0928,-2358.8381,13.6521},
	{2778.1267,-2354.5730,13.6521},
	{2780.8623,-2351.3989,13.6521},
	{2780.5923,-2346.9163,13.6521},
	{2778.6304,-2344.3225,13.6521}
};

// enum SMUGGLER_INFO
// {
// 	Float:checkpointX,
// 	Float:checkpointY,
// 	Float:checkpointZ,
// 	placeName[64],
// 	message[64],
// 	Float:smugglerX,
// 	Float:smugglerY,
// 	Float:smugglerZ,
// 	Float:smugglerAngle,
// }
// new SmugglerInfo[][SMUGGLER_INFO] =
// {
// 	{2813.4675,-1472.3374,16.2703, "Parking piêtrowy na East Beach", "Czekam na górze", 2819.8611,-1426.2295,40.0625,138.9295},
// 	{2813.4675,-1472.3374,16.2703, "Parking piêtrowy na East Beach", "Czekam na górze", 2819.8611,-1426.2295,40.0625,138.9295},
// 	{2813.4675,-1472.3374,16.2703, "Parking piêtrowy na East Beach", "Czekam na górze", 2819.8611,-1426.2295,40.0625,138.9295},
// 	{2813.4675,-1472.3374,16.2703, "Parking piêtrowy na East Beach", "Czekam na górze", 2819.8611,-1426.2295,40.0625,138.9295}
// };

enum ACTOR_INFO
{
	aUID,
	aSkin,
	Float:aPosX,
	Float:aPosY,
	Float:aPosZ,
	Float:aAngle,
	aVW,
	aName[32],
	aAnimId,
	aActor,
	Text3D:aNick3D
};
new ActorInfo[MAX_ACTORS][ACTOR_INFO];