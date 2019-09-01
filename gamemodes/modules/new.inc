new bool:Logged[MAX_PLAYERS];

//new grzes;

new restart;
new bool:gmx = false;

new Text:TextPenalty;
new Text:TD_HeadBag;

new Text:TD_LSN;
new Text:TD_LSN2;

new PlayerText:DoorsTD[MAX_PLAYERS];
new PlayerText:Speedometer[MAX_PLAYERS][10];

new PlayerText:TDEditor_PTD[MAX_PLAYERS][9];
new Text:TDEditor_TD[2];
new PlayerText:PlayerLoadingInfo[MAX_PLAYERS];

new PlayerText:EditObjectText[MAX_PLAYERS];
new PlayerText:OFFER[MAX_PLAYERS];
new PlayerText:ACCEPT[MAX_PLAYERS];
new PlayerText:REJECT[MAX_PLAYERS];
new PlayerText:TipText[MAX_PLAYERS];

new OfferTimer[MAX_PLAYERS];
new VehSpawned[MAX_PLAYERS];

new bool:IsChecked[MAX_PLAYERS] = false;
new Spawned[MAX_PLAYERS];

new advreklama[128];
new advnews[128];
new ON_AIR;

new SERVER_TIME;
new SERVER_WEATHER;

new SERVER_LAST_RESTART;
new SERVER_LAST_TIMER_HOUR;

new PlayerBar:FoodBar[MAX_PLAYERS];

new Text3D:NameTags[MAX_PLAYERS];
new Text3D:Description[MAX_PLAYERS] = Text3D:INVALID_3DTEXT_ID;

new Rozmawia[MAX_PLAYERS] = INVALID_PLAYER_ID;
new RozmawiaZ[MAX_PLAYERS] = INVALID_PLAYER_ID;

new PickupID[22] = {0, 1240, 1242, 1239, 1272, 1273, 1212, 1241, 1247, 1248, 1252, 1253, 1254, 1274, 1275, 1277, 1313, 1314, 1276, 1310, 1318, 1279};
new WeaponModel[47] = {0, 331, 333, 334, 335, 336, 337, 338, 339, 341, 321, 322, 323, 324, 325, 326, 342, 343, 344, 0, 0, 0, 346, 347, 348, 349, 350, 351, 352, 353, 355, 356, 372, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 371};

new wheelmodels[17] = {1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,1082,1083,1084,1085,1096,1097,1098};

new forbidden[] ={955, 956, 1755, 1302, 1209, 1775, 1776, 1531, 1530, 1529, 1528, 1527, 1526, 1525, 1524, 1490, 11313, 18659, 18660, 18661, 18662, 18663, 18664, 18665, 18666, 18667};

new Tick[MAX_VEHICLES];
new Float:VehiclePos[MAX_VEHICLES][3];

new Kierunki_V[MAX_VEHICLES][6];

new AREA_GOV_DOCS;
new PICKUP_GOV_DOCS;
new AREA_GOV_JOBS;
new PICKUP_GOV_JOBS;

new _ITEM_COUNT;
new _VEH_COUNT;
new _OBJ_COUNT;
new _DOOR_COUNT;
new _DESC_COUNT;

stock ConvertSecondsToTime(zmienna, &hours, &minutes, &second)
{
	hours 	= zmienna / 3600;
	minutes = (zmienna - hours * 3600) / 60;
	second 	= ((zmienna - (hours * 3600)) - (minutes * 60));
	return 1;
}

stock ShiftRGBAToABGR(&color)
{
	new r, g, b, a;
	r = (color >>> 24);
	g = (color >>> 16 & 0xFF);
	b = (color >>> 8 & 0xFF);
	a = (color  & 0xFF);
	color = (a & 0xFF) | ((b & 0xFF) << 8) | ((g & 0xFF) << 16) | (r << 24);
	return color;
}

stock EscapeMMAT(name[])
{
	for(new i = 0; name[i] != 0; i++)
		if(name[i] == '|') name[i] = '\n';
}

stock GetWeaponType(weaponid)
{
	new type = WEAPON_TYPE_NONE;

	switch(weaponid)
	{
		case 26, 28, 32:
			type = WEAPON_TYPE_LIGHT;

		case 3, 16, 17, 18, 39, 10, 11, 12, 13, 14, 40, 41:
			type = WEAPON_TYPE_MELEE;

		case 9, 25, 27, 29, 30, 31, 33, 34, 35, 36, 37, 38:
			type = WEAPON_TYPE_HEAVY;
		
		case 2, 5, 6, 7, 8:
			type = WEAPON_TYPE_MELEE_BIG;
	}

	return type;
}

stock GetDistance( Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2 )
{
	return floatround( floatsqroot( ( ( x1 - x2 ) * ( x1 - x2 ) ) + ( ( y1 - y2 ) * ( y1 - y2 ) ) + ( ( z1 - z2 ) * ( z1 - z2 ) ) ) ) ;
}

new legalmods[48][22] = {
		{400, 1024,1021,1020,1019,1018,1013,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
		{401, 1145,1144,1143,1142,1020,1019,1017,1013,1007,1006,1005,1004,1003,1001,0000,0000,0000,0000},
		{404, 1021,1020,1019,1017,1016,1013,1007,1002,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
		{405, 1023,1021,1020,1019,1018,1014,1001,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
		{410, 1024,1023,1021,1020,1019,1017,1013,1007,1003,1001,0000,0000,0000,0000,0000,0000,0000,0000},
		{415, 1023,1019,1018,1017,1007,1003,1001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
		{418, 1021,1020,1016,1006,1002,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
		{420, 1021,1019,1005,1004,1003,1001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
		{421, 1023,1021,1020,1019,1018,1016,1014,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
		{422, 1021,1020,1019,1017,1013,1007,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
		{426, 1021,1019,1006,1005,1004,1003,1001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
		{436, 1022,1021,1020,1019,1017,1013,1007,1006,1003,1001,0000,0000,0000,0000,0000,0000,0000,0000},
		{439, 1145,1144,1143,1142,1023,1017,1013,1007,1003,1001,0000,0000,0000,0000,0000,0000,0000,0000},
		{477, 1021,1020,1019,1018,1017,1007,1006,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
		{478, 1024,1022,1021,1020,1013,1012,1005,1004,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
		{489, 1024,1020,1019,1018,1016,1013,1006,1005,1004,1002,1000,0000,0000,0000,0000,0000,0000,0000},
		{491, 1145,1144,1143,1142,1023,1021,1020,1019,1018,1017,1014,1007,1003,0000,0000,0000,0000,0000},
		{492, 1016,1006,1005,1004,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
		{496, 1143,1142,1023,1020,1019,1017,1011,1007,1006,1003,1002,1001,0000,0000,0000,0000,0000,0000},
		{500, 1024,1021,1020,1019,1013,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
		{516, 1021,1020,1019,1018,1017,1016,1015,1007,1004,1002,1000,0000,0000,0000,0000,0000,0000,0000},
		{517, 1145,1144,1143,1142,1023,1020,1019,1018,1017,1016,1007,1003,1002,0000,0000,0000,0000,0000},
		{518, 1145,1144,1143,1142,1023,1020,1018,1017,1013,1007,1006,1005,1003,1001,0000,0000,0000,0000},
		{527, 1021,1020,1018,1017,1015,1014,1007,1001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
		{529, 1023,1020,1019,1018,1017,1012,1011,1007,1006,1003,1001,0000,0000,0000,0000,0000,0000,0000},
		{534, 1185,1180,1179,1178,1127,1126,1125,1124,1123,1122,1106,1101,1100,0000,0000,0000,0000,0000},
		{535, 1121,1120,1119,1118,1117,1116,1115,1114,1113,1110,1109,0000,0000,0000,0000,0000,0000,0000},
		{536, 1184,1183,1182,1181,1128,1108,1107,1105,1104,1103,0000,0000,0000,0000,0000,0000,0000,0000},
		{540, 1145,1144,1143,1142,1024,1023,1020,1019,1018,1017,1007,1006,1004,1001,0000,0000,0000,0000},
		{542, 1145,1144,1021,1020,1019,1018,1015,1014,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
		{546, 1145,1144,1143,1142,1024,1023,1019,1018,1017,1007,1006,1004,1002,1001,0000,0000,0000,0000},
		{547, 1143,1142,1021,1020,1019,1018,1016,1003,1000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
		{549, 1145,1144,1143,1142,1023,1020,1019,1018,1017,1012,1011,1007,1003,1001,0000,0000,0000,0000},
		{550, 1145,1144,1143,1142,1023,1020,1019,1018,1006,1005,1004,1003,1001,0000,0000,0000,0000,0000},
		{551, 1023,1021,1020,1019,1018,1016,1006,1005,1003,1002,0000,0000,0000,0000,0000,0000,0000,0000},
		{558, 1168,1167,1166,1165,1164,1163,1095,1094,1093,1092,1091,1090,1089,1088,0000,0000,0000,0000},
		{559, 1173,1162,1161,1160,1159,1158,1072,1071,1070,1069,1068,1067,1066,1065,0000,0000,0000,0000},
		{560, 1170,1169,1141,1140,1139,1138,1033,1032,1031,1030,1029,1028,1027,1026,0000,0000,0000,0000},
		{561, 1157,1156,1155,1154,1064,1063,1062,1061,1060,1059,1058,1057,1056,1055,1031,1030,1027,1026},
		{562, 1172,1171,1149,1148,1147,1146,1041,1040,1039,1038,1037,1036,1035,1034,0000,0000,0000,0000},
		{565, 1153,1152,1151,1150,1054,1053,1052,1051,1050,1049,1048,1047,1046,1045,0000,0000,0000,0000},
		{567, 1189,1188,1187,1186,1133,1132,1131,1130,1129,1102,0000,0000,0000,0000,0000,0000,0000,0000},
		{575, 1177,1176,1175,1174,1099,1044,1043,1042,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
		{576, 1193,1192,1191,1190,1137,1136,1135,1134,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
		{580, 1023,1020,1018,1017,1007,1006,1001,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000},
		{589, 1145,1144,1024,1020,1018,1017,1016,1013,1007,1006,1005,1004,1000,0000,0000,0000,0000,0000},
		{600, 1022,1020,1018,1017,1013,1007,1006,1005,1004,0000,0000,0000,0000,0000,0000,0000,0000,0000},
		{603, 1145,1144,1143,1142,1024,1023,1020,1019,1018,1017,1007,1006,1001,0000,0000,0000,0000,0000}
};

stock iswheelmodel(modelid) {	
	
	for(new I=0;I<17;I++)
		if (modelid == wheelmodels[I])
			return true;
	
	return false;
}

stock IllegalCarNitroIde(carmodel) 
{	
	new illegalvehs[29] = { 581, 523, 462, 521, 463, 522, 461, 448, 468, 586, 509, 481, 510, 472, 473, 493, 595, 484, 430, 453, 452, 446, 454, 590, 569, 537, 538, 570, 449 };
	
	for(new i=0;i<29;i++)
		if (carmodel == illegalvehs[i])
			return true;
	
	return false;
}

stock islegalcarmod(vehicleide, componentid) 
{
	
	new modok = false;   
	// stereo, hydraulics & nos (1x 2x 3x) are special.
	if ( (iswheelmodel(componentid)) || (componentid == 1086) || (componentid == 1087) || ((componentid >= 1008) && (componentid <= 1010)))
	{
		new nosblocker = IllegalCarNitroIde(vehicleide);
		
		if (!nosblocker)
			modok = true;
	}
	else
	{		
		// check if the specified model CAN use this particular mod.
		for(new I=0;I<48;I++) 
			if (legalmods[I][0] == vehicleide)
				for(new J = 1; J < 22; J++)
					if (legalmods[I][J] == componentid)
						modok = true;
	}
	
	return modok;
}

ValidateDesc(desc[], premium=0)
{
	new size=strlen(desc);
	if(!premium)
	{
		for(new i=0; i<size;i++)
			if(desc[i]=='{' || desc[i]=='}' || desc[i]=='|' || desc[i]=='\\' || desc[i]=='\r' || desc[i]=='\n')
				return 0;
	}
    else
    {
		for(new i=0; i<size;i++)
			if(desc[i]=='|' || desc[i]=='\\' || desc[i]=='\r' || desc[i]=='\n')
				return 0; 
    }
	
	return 1;
}

ReplacePolishLetters(adv[],size)
{
	for(new i=0;i<size;i++)
	{
		if(adv[i]=='¹')
		{ 
			adv[i]='a';
			continue;
		}
		else if(adv[i]=='ê')
		{
			adv[i]='e';
			continue;
		}
		else if(adv[i]=='ó')
		{
			adv[i]='o';
			continue;
		}
		else if(adv[i]=='³')
		{
			adv[i]='l';
			continue;
		}
		else if(adv[i]=='æ')
		{
			adv[i]='c';
			continue;
		}
		else if(adv[i]=='œ')
		{
			adv[i]='s';
			continue;
		}
		else if(adv[i]=='¿')
		{
			adv[i]='z';
			continue;
		}
		else if(adv[i]=='Ÿ')
		{
			adv[i]='z';
			continue;
		}
		else if(adv[i]=='¥')
		{ 
			adv[i]='A';
			continue;
		}
		else if(adv[i]=='Ê')
		{
			adv[i]='E';
			continue;
		}
		else if(adv[i]=='Ó')
		{
			adv[i]='O';
			continue;
		}
		else if(adv[i]=='£')
		{
			adv[i]='L';
			continue;
		}
		else if(adv[i]=='Æ')
		{
			adv[i]='C';
			continue;
		}
		else if(adv[i]=='Œ')
		{
			adv[i]='S';
			continue;
		}
		else if(adv[i]=='¯')
		{
			adv[i]='Z';
			continue;
		}
		else if(adv[i]=='')
		{
			adv[i]='Z';
			continue;
		}

	}
	return 1;
}

stock GetTickDiff(newtick, oldtick)
{
	if (oldtick < 0 && newtick >= 0)
		return newtick - oldtick;
	else if (oldtick >= 0 && newtick < 0 || oldtick > newtick)
		return (cellmax - oldtick + 1) - (cellmin - newtick);
	
	return newtick - oldtick;
}