#undef MAX_PLAYERS
#undef MAX_VEHICLES
#undef MAX_ACTORS
#undef MAX_OBJECTS
#define MAX_PLAYERS			200
#define MAX_VEHICLES		3000
#define MAX_SPAWNED_VEH		1000
#define MAX_OBJECTS			30000
#define MAX_DOORS			1000
#define MAX_GROUPS			200
#define MAX_PLANTS			2000
#define MAX_ITEMS			15000
#define MAX_CORPSE			1000
#define MAX_ANIMS			165
#define MAX_STATIONS		30
#define MAX_CORNERS			30
#define MAX_BUS_STOPS		30
#define MAX_ROADBLOCKS		20
#define MAX_A3D				50
#define MAX_SAFEKEEPS		50
#define MAX_WS_MAPICONS		15
#define MAX_DOORS_MAPICONS	100
#define MAX_DESCRIPTIONS	2000
#define MAX_ACTORS	100
#define MAX_SKINS	100
#define MAX_911CALLS		100

#define MAX_GROUP_OBJS 50
#define MAX_GROUP_OBJECTS_PREM 100
#define MAX_HOUSE_OBJECTS 10
#define MAX_HOUSE_OBJECTS_PREM 20
#define MAX_HOUSE_INT_OBJECT 200
#define MAX_HOUSE_INT_OBJECT_PREM 350

#define TIME_TO_SALARY 30
#define MAX_SALARY_PRE_DAY 2

#define DEF_COLOR "{02AD38}"
#define DEF_NAME DEF_COLOR"mySantos v2.2{FFFFFF}"

#define FORUM_GROUP_USER 3
#define FORUM_GROUP_PREMIUM 9

#define COL_MSGBOX "{A9C4E4}"

//"{443CD6}"
#define COLOR_FADE1		0xE6E6E6E6
#define COLOR_FADE2		0xC8C8C8C8
#define COLOR_FADE3		0xAAAAAAAA
#define COLOR_FADE4		0x8C8C8C8C
#define COLOR_FADE5		0x6E6E6E6E

//#define COLOR_GREEN		0x33AA33FF
#define COLOR_GREEN	 0x02AD38FF
#define COLOR_ORANGE		0xFF9900FF
#define COLOR_YELLOW		0xFCDF1EFF
#define COLOR_RED		0xC90000FF
#define COLOR_DARKRED		0xB00000FF
#define COLOR_WHITE		0xFFFFFFFF
#define COLOR_GREY		0xAFAFAFAA
#define COLOR_PURPLE		0xC2A2DAFF
#define COLOR_DO		0x9A9CCDFF
#define COLOR_GM		0x8B00B0FF
#define COLOR_BLUE		0x3232CDFF
#define COLOR_SEND_PW		0x00D11FFF
#define COLOR_GOT_PW		0xF2DE00FF
#define COLOR_MTEXT     0xFFFF00FF

#define COLOR_USER		0x808080CC
#define COLOR_PREMIUM		0xFFFFFFCC

#define COLOR_VEH_DESC 0xD3D3D3FF

#define OWNER_NONE		0
#define OWNER_PLAYER		1
#define OWNER_GROUP	 2
#define OWNER_HOUSE		3
#define OWNER_HOUSE_BUY		4
#define OWNER_SVEHICLE		5
#define OWNER_BANKOMAT	  6
#define OWNER_JAIL		7
#define OWNER_CLOTHESSHOP 8
#define OWNER_JOB   9
#define OWNER_AREA 10
#define OWNER_DOOR 11
#define OWNER_ADMIN 12
#define OWNER_CORPSE	13
#define OWNER_HOTEL 14

#define OWNER_HOUSE_ITEM		15

#define OWNER_VEHICLE		20
#define OWNER_BAGAZNIK		21
#define OWNER_SAFEKEEP	22
#define OWNER_SAFEKEEP_ITEM	23
#define OWNER_ULECZSIE 24

#define OFFER_ITEM		1
#define OFFER_VEHICLE   2
#define OFFER_HOUSE		3
#define OFFER_VCARD	 4
#define OFFER_REPAIR_ENG 5
#define OFFER_REPAIR_BODY 6
#define OFFER_REPAIR_TIRES 7
#define OFFER_REPAIR_ALL 8
#define OFFER_PAINT 9
#define OFFER_PAINTJOB 10
#define OFFER_TUNING 11
#define OFFER_TAXI 12
#define OFFER_DISMOUNT 13
#define OFFER_MANDAT 14
#define OFFER_ADVERT 15
#define OFFER_DOCID 16
#define OFFER_DOCDRIVER 17
#define OFFER_DOCPILOT 18
#define OFFER_REGISTERCAR 19
#define OFFER_REGISTERGROUP 20
#define OFFER_GYM_SINGLE 21
#define OFFER_GYM_DAY 22
#define OFFER_GYM_WEEK 23
#define OFFER_DOCWEAPONS 24
#define OFFER_DOCMED 25
#define OFFER_RESTAURANT_ITEM 26
#define OFFER_MEDICINE 27
#define OFFER_VEHICLE_KOMIS 28
#define OFFER_YO 29

#define PERM_VEHICLES		1
#define PERM_DOOR			2
#define PERM_OBJECT			4
#define PERM_MAGAZINE		8
#define PERM_PRODUCT		16
#define PERM_VEHICLES_MAN	32
#define PERM_CASH			64
#define PERM_PERSONEL		128
#define PERM_EXTRA			256
#define PERM_SPECIAL_LEADER	512

#define GROUP_GOV	1
#define GROUP_PD	2
#define GROUP_MC	3
#define GROUP_NEWS	4
#define GROUP_FBI	5
#define GROUP_MILITARY	6
#define GROUP_GANG	7
#define GROUP_MAFIA	8
#define GROUP_DRIVERS	9
#define GROUP_SHOP	10
#define GROUP_WORKSHOP	11
#define GROUP_TAXI	12
#define GROUP_SECURITY	13
#define GROUP_CARDEALER	14
#define GROUP_LOGISTIC	15
#define GROUP_BANK	  16
#define GROUP_GYM	  17
#define GROUP_RESTAURANT	18
#define GROUP_FUELSTATION	19
#define GROUP_SYNDICATE 20
#define GROUP_KASYNO 21
#define GROUP_CARTEL 22
#define GROUP_KLUB 23
#define GROUP_GUNSHOP 24

#define GROUP_COUNT		24
#define MAX_PLAYER_GROUPS 6

#define FLAG_DEPARTMENT		1
#define FLAG_MEGAPHONE		2
#define FLAG_NICK		4
#define FLAG_OUT		8
#define FLAG_CASH		16
#define FLAG_JAIL		32
#define FLAG_ITEM		64
#define FLAG_911		128
#define FLAG_REPORTS		256
#define FLAG_GPS		512

#define TOG_PW		1
#define TOG_NAME		2
#define TOG_GLOD		4
#define TOG_LSN		8
#define TOG_QS	  16
#define TOG_SPEEDOMETER 32
#define TOG_SAY		64
#define TOG_KRZYK		128
#define TOG_TOKEN	   256
#define TOG_FREEZE		512
#define TOG_KIERUNKI	1024
#define TOG_SMIECH		2048
#define TOG_CHATOOC		4096
#define TOG_TELSOUND	8192
#define TOG_GUN_CARRY	16384
#define TOG_STATUS		32768

#define STATUS_AFK		1
#define STATUS_KAJDANKI	  2
#define STATUS_KNEBEL		4
#define STATUS_PLAY_ANIM	8
#define STATUS_PASY		16
#define STATUS_CIAGNIETY		32
#define STATUS_ZWIAZANY 64
#define STATUS_MP3  128
#define STATUS_BUS  256
#define STATUS_HEADBAG 512
#define STATUS_WALK_ANIM 1024

#define PENALTY_WARN		1
#define PENALTY_KICK		2
#define PENALTY_BAN		3
#define PENALTY_BLOCK		4
#define PENALTY_SCORE		5
#define PENALTY_AJ		6
#define PENALTY_UNWARN		7
#define PENALTY_NORUN		8
#define PENALTY_NOGUN		9
#define PENALTY_NOCAR		10
#define PENALTY_NOOOC	   11
#define PENALTY_BAN44	   12
#define PENALTY_CURSE	   13
#define PENALTY_BAN_CURSE		14

#define BLOCK_CHAR		1
#define BLOCK_BAN		2
#define BLOCK_CK		4
#define BLOCK_NOCAR		8
#define BLOCK_NOOOC		16
#define BLOCK_NORUN		32
#define BLOCK_NOGUN	 64

#define JOB_NONE 0
#define JOB_WEARHOUSE 1

#define NAX_JOB_WEARHOUSE_REPS 40
#define CASH_WEARHOUSE 10

#define ITEM_TYPE_BRON	  1
#define ITEM_TYPE_TELEFON	   2
#define ITEM_TYPE_MASKA	 3
#define ITEM_TYPE_JEDZENIE	  4
#define ITEM_TYPE_KOSTKA		5
#define ITEM_TYPE_KARTY	 6
#define ITEM_TYPE_LEKARSTWO	 7
#define ITEM_TYPE_KAMIZELKA	 8
#define ITEM_TYPE_ZEGAREK	   9
#define ITEM_TYPE_PALIWO		10
#define ITEM_TYPE_PAPIEROSY	 11
#define ITEM_TYPE_PIWO	  12
#define ITEM_TYPE_SEED	  13
#define ITEM_TYPE_MARIHUANA	 14
#define ITEM_TYPE_KOKAINA	   15
#define ITEM_TYPE_HEROINA	   16
#define ITEM_TYPE_LSD	   17
#define ITEM_TYPE_RADIO	 18
#define ITEM_TYPE_MEGAFON	   19
#define ITEM_TYPE_SUPLEMENTY	   20
#define ITEM_TYPE_BOOMBOX	   21
#define ITEM_TYPE_AMMO		22
#define ITEM_TYPE_TUNING	23
#define ITEM_TYPE_SILENCER 24
#define ITEM_TYPE_CARKEYS 25
#define ITEM_TYPE_ATTACHED 26
#define ITEM_TYPE_REPAIRKIT	27
#define ITEM_TYPE_KEEPKEY	28
#define ITEM_TYPE_GLASS 29
#define ITEM_TYPE_CLOTH 30

#define TYPE_COUNT	30

#define DRUG_MARIHUANA		1
#define DRUG_KOKAINA		2
#define DRUG_HEROINA		3
#define DRUG_LSD		4
#define DRUG_ALKO		5

#define DOC_ID 1
#define DOC_DRIVER  2
#define DOC_PILOT 4
#define DOC_WEAPONS 8
#define DOC_MED 16

#define SAVE_PLAYER_BASIC		1
#define SAVE_PLAYER_PENALTY		2
#define SAVE_PLAYER_ADMIN		3
#define SAVE_PLAYER_GLOBAL		4
#define SAVE_PLAYER_POS			5
#define SAVE_PLAYER_OPTION		6
#define SAVE_PLAYER_SPAWN		7
#define SAVE_PLAYER_JAIL		8
#define SAVE_PLAYER_JOBS		9
#define SAVE_PLAYER_PREMIUM		10
#define SAVE_LAST_DAMAGE		11

#define SAVE_DOORS_BASIC		1
#define SAVE_DOORS_POS		2

#define SAVE_VEH_BASIC		1
#define SAVE_VEH_POS		2
#define SAVE_VEH_OWNER	  3

#define SAVE_GROUP_BASIC		1
#define SAVE_GROUP_FLAGS		2
#define SAVE_GROUP_SPAWN		3

#define SPAWN_TYPE_CENTRUM  0
#define SPAWN_TYPE_HOUSE	1
#define SPAWN_TYPE_LASTPOS  2
#define SPAWN_TYPE_GROUP	3
#define SPAWN_TYPE_HOTEL	4
#define SPAWN_TYPE_LMEXICO	5

#define WEAPON_TYPE_NONE	0
#define WEAPON_TYPE_LIGHT   1
#define WEAPON_TYPE_MELEE   2
#define WEAPON_TYPE_HEAVY   3
#define WEAPON_TYPE_MELEE_BIG   4

#define TUNING_VISUAL 1
#define TUNING_PAINTJOB 2
#define TUNING_PAINTJOB_0 4
#define TUNING_PAINTJOB_1 8
#define TUNING_PAINTJOB_2 16

#define WALK_DEFAULT    0
#define WALK_NORMAL     1
#define WALK_PED        2
#define WALK_GANGSTA    3
#define WALK_GANGSTA2   4
#define WALK_OLD        5
#define WALK_FAT_OLD    6
#define WALK_FAT        7
#define WALK_LADY          8
#define WALK_LADY2      9
#define WALK_WHORE      10
#define WALK_WHORE2     11
#define WALK_DRUNK         12
#define WALK_BLIND         13

//sloty doczepianych
#define SLOT_MASK   0
#define SLOT_WEAPON 1
#define SLOT_JOB	2
#define SLOT_TRAIN_ITEM 3
#define SLOT_PHONE 4

//5-9 zarezerwowane na itemy

#define D_INFO	  1
#define D_LOGIN_GLOBAL	  2
#define D_HELP	  3
#define D_TOG	   4
#define D_BAN_LIST	  5
#define D_PRIV_MSG	  6
#define D_ITEM_CREATE	   7
#define D_ITEM_CREATE_TYPE	  8
#define D_ITEM_CREATE_VALUE1		9
#define D_ITEM_CREATE_VALUE2		10
#define D_ITEM	  11
#define D_ITEM_OPTIONS	  12
#define D_ITEM_PICK	 13
#define D_AP_USUN	   14
#define D_AP_NAME	   15
#define D_AP_TYPE	   16
#define D_AP_VALUE1	 17
#define D_AP_VALUE2	 18
#define D_LIST_VEH	  19
#define D_VEH_OPT	   20
#define D_VEH_MEN	   21
#define D_PHONE	 22
#define D_DOORS_REMOVE	  23
#define D_DOORS_NAME		24
#define D_BANKOMAT	  25
#define D_BANKOMAT_CASH	 26
#define D_HOUSE_BUY	 27
#define D_HOUSE_BUY_CHECK	   28
#define D_HOUSE_INFO		29
#define D_HOUSE_INFO_MENU	   30
#define D_HOUSE_MEMBERS_MEN	 31
#define D_HOUSE_PLACE	   32
#define D_HOUSE_PLACE_DROP	  33
#define D_HOUSE_PLACE_IN		34
#define D_SVEHICLE	  35
#define D_SVEHICLE_BUY	  36
#define D_SVEHICLE_BUY_P		37
#define D_SVEHICLE_BUY_P2	   38
#define D_CHOOSE_SPAWN	  39
#define D_CHOOSE_SPAWN_MAIN	 40
#define D_CHOOSE_SPAWN_HOUSE		41
#define D_GROUP_CREATE	  42
#define D_GROUP_CREATE_TAG	  43
#define D_GROUP_CREATE_TYPE	 44
#define D_GROUP_CHANGE_NAME	 45
#define D_GROUP_CHANGE_TAG	  46
#define D_GROUP_LIST_FLAGS	  47
#define D_GROUP_VEH_OPTIONS	 48
#define D_GROUP_VEH_OPTIONS_SELECT	  49
#define D_GROUP_MAGAZINE		50
#define D_GROUP_CHANGE_PERM	 51
#define D_LOGISTIC_ORDERS		52
#define D_ORDER_PRODUCT		 53
#define D_ORDER_VALUE		54
#define D_OUT_ITEM	  55
#define D_DEATH		 56
#define D_DESCRIPTION	   57
#define D_WALKIE_CHANGE	 58
#define D_DESCRIPTION_CREATE	   59
#define D_OFFER_ITEM		60
#define D_OFFER_ITEM_END		61
#define D_BAGAZNIK	  62
#define D_BAGAZNIK_OUT	  63
#define D_BAGAZNIK_IN	   64
#define D_DOOR_CHANGE_RADIO 65
#define D_VEH_RADIO 66
#define D_VEH_RADIO_LINK 67
#define D_BOOMBOX	   68
#define D_DOCS	  69
#define D_OFFER_VEHICLE	 70
#define D_OFFER_VEHICLE_END		71
#define D_LSPD	  72
#define D_KARTOTEKI	 73
#define D_POSZUKIWANI	   74
#define D_KARTOTEKI_SEARCH	  75
#define D_KARTOTEKI_NEW	 76
#define D_KARTOTEKI_SEARCH_UID	  77
#define D_KARTOTEKI_SEARCH_ID	   78
#define D_KARTOTEKI_RECORDS	 79
#define D_KARTOTEKI_RECORDS_NEXT		80
#define D_KARTOTEKI_ADD_RECORD	  81
#define D_KARTOTEKI_RECORD_INFO	 82
#define D_ADD_AMMO	  83
#define D_CHOOSE_SPAWN_GROUPS	   84
#define D_AG_DELETE 85
#define D_PRZESZUKAJ		86
#define D_APRZESZUKAJ	   87
#define D_GROUP_MAGAZINE_LAST	   88
#define D_SPLIT	 89
#define D_SKIN_CHANGE	   90
#define D_PLAY_ANIM 91
#define D_ITEM_BUY  92
#define D_ITEM_PRICE 93
#define D_ITEM_PRICE_SET 94
#define D_STATION_DELETE	95
#define D_FUEL_TRANSPORT	96
#define D_PHONE_CONTACTS	97
#define D_PHONE_CONTACTS_OPT	98
#define D_PHONE_SMS 99
#define D_PHONE_CHANGE_CONT_NAME 100
#define D_911 101
#define D_911_TEXT 102
#define D_FUEL_ORDER 103
#define D_FUEL_CONFIRM 104
#define D_CORNER	105
#define D_CORPSE_SEARCH	106
#define D_CORPSE_MONEY   107
#define D_CORPSE_SEARCH_MEN   108
#define D_REPAIR 109
#define D_KARTOTEKI_EDIT 110
#define D_KARTOTEKI_REMOVE_CONF 111
#define D_POSZUKIWANI_SEARCH 112
#define D_POSZUKIWANI_NEW 113
#define D_POSZUKIWANI_SEARCH_UID 114
#define D_POSZUKIWANI_SEARCH_ID 115
#define D_POSZUKIWANY_REMOVE 116
#define D_POSZUKIWANY_REMOVE_CONF 117
#define D_BUS  118
#define D_BUS_CONFIRM  119
#define D_TUNING	120
#define D_GROUP_MAGAZINE_PUT 121
#define D_TUNING_DISMOUNT   122
#define D_COMP 123
#define D_GROUP_MAGAZINE_OUT 124
#define D_VEH_DESC 125
#define D_VEH_DESC_ADD 126
#define D_CALL_TAXI 127
#define D_CALL_TAXI_MSG 128
#define D_CALL_ASSISTANCE 129
#define D_CALL_ASSISTANCE_MSG 130
#define D_PHONE_MP3 131
#define D_PHONE_MP3_LINK 132
#define D_PHONE_ADD_CONT 133
#define D_PHONE_ADD_CONT2 134
#define D_GROUP_PRICES  135
#define D_GROUP_PRICES_SET  136
#define D_ORDER_PRODUCT_CATEGORY 137
#define D_WALKIE_CREATE 138
#define D_WALKIE_CREATE_PASSWD 139
#define D_WALKIE_CHANGE_PASSWD 140
#define D_WALKIE_OPT 141
#define D_WALKIE_PASSWD_CHANGE 142
#define D_PLATESCHANGE 143
#define D_SILENCER 144
#define D_RESTAURANT_GIVE 145
#define D_A3D_CREATE 146
#define D_SAFEKEEP	147
#define D_SAFEKEEP_OPEN 148
#define D_GOV_JOBS 149
#define D_SAFEKEEP_WITHDRAW 150
#define D_SAFEKEEP_OPEN_LIST 151
#define D_SAFEKEEP_DEPOSIT 152
#define D_POSZUKIWANI_NEW2 153
#define D_WEAPON_MAGAZINE_CATEGORY 154
#define D_WEAPON_MAGAZINE_BUY 155
#define D_DOTACJA 156
#define D_GROUP_CHANGE_TYPE 157
#define D_REGISTER_VEHICLE_BOT 158
#define D_DESCRIPTION_OPT 159
#define D_DESCRIPTION_END 160
#define D_GYM_PUNCH_BAG 161
#define D_DOOR_CHANGE_PRICE 162
#define D_OFFER_VEHICLE_END_KOMIS 163
#define D_CHANGE_VEH_OWNER_V 164
#define D_MANDAT_ACCEPT 165
#define D_WORKSHOP_ACCEPT 166
#define D_GROUP_CLEAR 167
#define D_DOOR_CHANGE_TIME 168
#define D_DOOR_CHANGE_WEATHER 169
#define D_GASTRO_BUY 170
#define D_ORDER_END 171
#define D_ATTACHED_BUY 172
#define D_MASKA_OBJ 173
#define D_SANN_PHONE 174
#define D_CALL_RESTAURANT 175
#define D_RESTAURANT_MSG 176
#define D_REGISTER_GROUP_BOT 177
#define D_GROUP_MAGAZINE_STACK 178
#define D_FUELSTATION_TANK 179
#define D_FUELSTATION_TANK_END 180
#define D_WALKSTYLE	181
#define D_LOGIN_GLOBAL_2 182
#define D_LOGIN_GLOBAL_2_END 183
#define D_ZGLOSZENIA 184
#define D_ZGLOSZENIA_2 185
#define D_SKIN_CHANGE_GROUP 186

#define TRAIN_NONE		  0
#define TRAIN_BENCH  1
#define TRAIN_BARBELL	   2
#define TRAIN_PUNCH_BAG 3

#define SKIN_TYPE_PLAYER	1
#define SKIN_TYPE_GROUP		2
 
#define ForeachEx(%2,%1) for(new %2 = 0; %2 < %1; %2++)

#define ForeachPlayer(%1) for(new %1 = 0, pool=GetPlayerPoolSize(); %1<=pool; %1++)

#define chrtoupper(%1) \
		(((%1) > 0x60 && (%1) <= 0x7A) ? ((%1) ^ 0x20) : (%1))

#define chrtolower(%1) \
		(((%1) > 0x40 && (%1) <= 0x5A) ? ((%1) | 0x20) : (%1))

#define SendClientMessageFormat(%0,%1,%2,%3) \
do \
{ \
	if(strlen(%2) > 0) \
	{ \
		new stringtest[144]; \
		format(stringtest, sizeof(stringtest), %2, %3); \
		SendClientMessage(%0, %1, stringtest); \
	} \
} \
while(FALSE)

#define msg_infoFormat(%0,%1,%2,%3) \
do \
{ \
	new infostring[%1]; \
	format(infostring,sizeof(infostring),%2, %3); \
	ShowPlayerDialog(%0,D_INFO,DIALOG_STYLE_MSGBOX,DEF_NAME" » informacja",infostring,"OK",""); \
} \
while(FALSE)

#define msg_errorFormat(%0,%1,%2,%3) \
do \
{ \
	new infostring[%1]; \
	format(infostring,sizeof(infostring),%2, %3); \
	ShowPlayerDialog(%0,D_INFO,DIALOG_STYLE_MSGBOX,DEF_NAME" » b³¹d",infostring,"Zamknij",""); \
} \
while(FALSE)

#define SendAdminMessageFormat(%0,%1,%2) \
do \
{ \
	if(strlen(%1) > 0) \
	{ \
		new stringtest[128]; \
		format(stringtest, sizeof(stringtest), %1, %2); \
		SendAdminMessage(%0, stringtest); \
	} \
} \
while(FALSE)

#define GetVehicleUID(%0) ( %0>GetVehiclePoolSize() || %0 <= 0 ? 0 : VehicleUIDs[%0])

#define A_CHAR(%0) for(new i = strlen(%0) - 1; i >= 0; i--)\
if(%0[i] == '%')\
%0[i] = '#'