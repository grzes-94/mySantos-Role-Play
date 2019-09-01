forward OnPlayerGymTrainStarted(playerid,type,object);
forward OnPlayerGymTrainStopped(playerid);
forward OnPlayerTrainRep(playerid);

public OnPlayerGymTrainStarted(playerid,type,object)
{
	CharacterInfo[playerid][pGymType] = type;
	new string[256];
	if(CharacterInfo[playerid][pGymType] == TRAIN_BENCH)
	{
		SetPlayerAttachedObject(playerid, SLOT_TRAIN_ITEM, 2913, 6, 0.0, 0.0, -0.2);
		
		CharacterInfo[playerid][pGymObject] = object;
		new Float:x, Float:y;
		x = ObjectInfo[object][oX] - floatsin(-ObjectInfo[object][oRZ], degrees);
		y = ObjectInfo[object][oY] - floatcos(-ObjectInfo[object][oRZ], degrees);

		SetPlayerPos(playerid, x, y, ObjectInfo[object][oZ]+1.0);
		SetPlayerFacingAngle(playerid, ObjectInfo[object][oRZ]);
		
		CharacterInfo[playerid][pGymPhase] = 1;
		
		switch(CharacterInfo[playerid][pSuplement])
		{
			case 0:
				format(string, sizeof(string), "~w~Aby uniesc sztange wcisnij:~n~~g~~h~~k~~CONVERSATION_YES~~n~~n~~w~Suplement:~n~~b~Brak~w~~n~Powtorzenia: ~b~%d~w~.~n~Sila: ~b~%d~w~.", CharacterInfo[playerid][pGymValue], CharacterInfo[playerid][pStrength]);
			case 1:
				format(string, sizeof(string), "~w~Aby uniesc sztange wcisnij:~n~~g~~h~~k~~CONVERSATION_YES~~n~~n~~w~Suplement:~n~~b~Wiecej otrzymywanej sily~w~~n~Powtorzenia: ~b~%d~w~.~n~Sila: ~b~%d~w~.", CharacterInfo[playerid][pGymValue], CharacterInfo[playerid][pStrength]);
			case 2:
				format(string, sizeof(string), "~w~Aby uniesc sztange wcisnij:~n~~g~~h~~k~~CONVERSATION_YES~~n~~n~~w~Suplement:~n~~b~Wiekszy limit dzienny - 70~w~~n~Powtorzenia: ~b~%d~w~.~n~Sila: ~b~%d~w~.", CharacterInfo[playerid][pGymValue], CharacterInfo[playerid][pStrength]);
			case 3:
				format(string, sizeof(string), "~w~Aby uniesc sztange wcisnij:~n~~g~~h~~k~~CONVERSATION_YES~~n~~n~~w~Suplement:~n~~b~Brak spadku dziennego sily~w~~n~Powtorzenia: ~b~%d~w~.~n~Sila: ~b~%d~w~.", CharacterInfo[playerid][pGymValue], CharacterInfo[playerid][pStrength]);
		}
		
		PlayerTextDrawSetString(playerid, DoorsTD[playerid], string);
		ApplyAnimation(playerid, "BENCHPRESS", "gym_bp_geton", 4.0, 0, 0, 0, 1, 0, 1);
		
		PlayerTextDrawShow(playerid,DoorsTD[playerid]);
	}
	else if(CharacterInfo[playerid][pGymType] == TRAIN_BARBELL)
	{
		CharacterInfo[playerid][pGymObject] = object;
		DestroyDynamicObject(ObjectInfo[object][oObject]);
	 	SetPlayerAttachedObject(playerid, SLOT_TRAIN_ITEM, 2915, 6, 0.06, 0.0, -0.45, 0.0, 90.0, 0.0);
		CharacterInfo[playerid][pGymPhase] = 1;
		ApplyAnimation(playerid, "FREEWEIGHTS", "gym_free_pickup", 4.0, 0, 0, 0, 1, 0, 1);
		
		switch(CharacterInfo[playerid][pSuplement])
		{
			case 0:
				format(string, sizeof(string), "~w~Aby wyciskac wcisnij:~n~~g~~h~~k~~PED_SPRINT~~n~~n~~w~Suplement:~n~~b~Brak~w~~n~Powtorzenia: ~b~%d~w~.~n~Sila: ~b~%d~w~.", CharacterInfo[playerid][pGymValue], CharacterInfo[playerid][pStrength]);
			case 1:
				format(string, sizeof(string), "~w~Aby wyciskac wcisnij:~n~~g~~h~~k~~PED_SPRINT~~n~~n~~w~Suplement:~n~~b~Wiecej otrzymywanej sily~w~~n~Powtorzenia: ~b~%d~w~.~n~Sila: ~b~%d~w~.", CharacterInfo[playerid][pGymValue], CharacterInfo[playerid][pStrength]);
			case 2:
				format(string, sizeof(string), "~w~Aby wyciskac wcisnij:~n~~g~~h~~k~~PED_SPRINT~~n~~n~~w~Suplement:~n~~b~Wiekszy limit dzienny - 70~w~~n~Powtorzenia: ~b~%d~w~.~n~Sila: ~b~%d~w~.", CharacterInfo[playerid][pGymValue], CharacterInfo[playerid][pStrength]);
			case 3:
				format(string, sizeof(string), "~w~Aby wyciskac wcisnij:~n~~g~~h~~k~~PED_SPRINT~~n~~n~~w~Suplement:~n~~b~Brak spadku dziennego sily~w~~n~Powtorzenia: ~b~%d~w~.~n~Sila: ~b~%d~w~.", CharacterInfo[playerid][pGymValue], CharacterInfo[playerid][pStrength]);
		}
		
		PlayerTextDrawSetString(playerid, DoorsTD[playerid], string);
		ApplyAnimation(playerid, "FREEWEIGHTS", "gym_free_pickup", 4.0, 0, 0, 0, 1, 0, 1);
		
		PlayerTextDrawShow(playerid, DoorsTD[playerid]);
	}
	else if(CharacterInfo[playerid][pGymType] == TRAIN_PUNCH_BAG)
	{
		format(string, sizeof(string), "Uderzaj w worek przy pomocy:~n~~g~~h~~k~~PED_LOCK_TARGET~ + ~k~~VEHICLE_ENTER_EXIT~~n~~n~~w~Trafienia: ~b~%d~w~/75.", CharacterInfo[playerid][pGymValue]);
		PlayerTextDrawSetString(playerid, DoorsTD[playerid], string);
		Tip(playerid,5,"Aby przerwac uzyj /cwiczenia");
		
		PlayerTextDrawShow(playerid, DoorsTD[playerid]);
	}
	
	return 1;
}

public OnPlayerGymTrainStopped(playerid)
{
	if(CharacterInfo[playerid][pGymType] == TRAIN_BARBELL)
	{
		new uid = CharacterInfo[playerid][pGymObject];
		ObjectInfo[uid][oObject]=CreateDynamicObject(ObjectInfo[uid][oModel], ObjectInfo[uid][oX], ObjectInfo[uid][oY], ObjectInfo[uid][oZ], ObjectInfo[uid][oRX],ObjectInfo[uid][oRY],ObjectInfo[uid][oRZ], ObjectInfo[uid][oVW],ObjectInfo[uid][oInt]);
	}
	else if(CharacterInfo[playerid][pGymType] == TRAIN_PUNCH_BAG)
		SetPlayerFightingStyle(playerid, CharacterInfo[playerid][pFightStyle]);

	SavePlayerStats(playerid, SAVE_PLAYER_OPTION);
 	CharacterInfo[playerid][pGymObject] = INVALID_OBJECT_ID;
	CharacterInfo[playerid][pGymValue] = 0;
	CharacterInfo[playerid][pGymType] = TRAIN_NONE;

	RemovePlayerAttachedObject(playerid, SLOT_TRAIN_ITEM);
	ClearAnimations(playerid);

	PlayerTextDrawHide(playerid, DoorsTD[playerid]);
	return 1;
}

public OnPlayerTrainRep(playerid)
{
	new string[256];
	if(CharacterInfo[playerid][pGymType] == TRAIN_BARBELL)
	{
		if(CharacterInfo[playerid][pGymPhase] == 2)
		{
			CharacterInfo[playerid][pGymPhase] = 1;

			CharacterInfo[playerid][pGymValue] ++;
			if(!(CharacterInfo[playerid][pGymValue]%10) && CharacterInfo[playerid][pStrength] < 1000)
			{
				if(CharacterInfo[playerid][pSuplement] == 1)
				{
					if(CharacterInfo[playerid][pStrength] + 2 > 1000)
					{
						CharacterInfo[playerid][pStrength]++;
						CharacterInfo[playerid][pStrengthToday]++;
					}
					else
					{
						CharacterInfo[playerid][pStrength] += 2;
						CharacterInfo[playerid][pStrengthToday] += 2;
					}
				}
				else
				{
					CharacterInfo[playerid][pStrength]++;
					CharacterInfo[playerid][pStrengthToday]++;
				}
			}
			
			switch(CharacterInfo[playerid][pSuplement])
			{
				case 0:
					format(string, sizeof(string), "~w~Aby wyciskac wcisnij:~n~~g~~h~~k~~PED_SPRINT~~n~~n~~w~Suplement:~n~~b~Brak~w~~n~Powtorzenia: ~b~%d~w~.~n~Sila: ~b~%d~w~.", CharacterInfo[playerid][pGymValue], CharacterInfo[playerid][pStrength]);
				case 1:
					format(string, sizeof(string), "~w~Aby wyciskac wcisnij:~n~~g~~h~~k~~PED_SPRINT~~n~~n~~w~Suplement:~n~~b~Wiecej otrzymywanej sily~w~~n~Powtorzenia: ~b~%d~w~.~n~Sila: ~b~%d~w~.", CharacterInfo[playerid][pGymValue], CharacterInfo[playerid][pStrength]);
				case 2:
					format(string, sizeof(string), "~w~Aby wyciskac wcisnij:~n~~g~~h~~k~~PED_SPRINT~~n~~n~~w~Suplement:~n~~b~Wiekszy limit dzienny - 70~w~~n~Powtorzenia: ~b~%d~w~.~n~Sila: ~b~%d~w~.", CharacterInfo[playerid][pGymValue], CharacterInfo[playerid][pStrength]);
				case 3:
					format(string, sizeof(string), "~w~Aby wyciskac wcisnij:~n~~g~~h~~k~~PED_SPRINT~~n~~n~~w~Suplement:~n~~b~Brak spadku dziennego sily~w~~n~Powtorzenia: ~b~%d~w~.~n~Sila: ~b~%d~w~.", CharacterInfo[playerid][pGymValue], CharacterInfo[playerid][pStrength]);
			}
			
   			PlayerTextDrawSetString(playerid, DoorsTD[playerid], string);
   			
   			PlayerTextDrawShow(playerid, DoorsTD[playerid]);
			ApplyAnimation(playerid, "FREEWEIGHTS", "gym_free_down", 4.0, 0, 0, 0, 1, 0, 1);
		}	
		if(CharacterInfo[playerid][pSuplement] != 2 && CharacterInfo[playerid][pStrengthToday] >= 50)
		{
			SetTimerEx("OnPlayerGymTrainStopped", 1500, false, "i", playerid);
			msg_info(playerid, "Nie mo¿esz dziœ ju¿ æwiczyæ.");
		}
		else if(CharacterInfo[playerid][pSuplement] == 2 && CharacterInfo[playerid][pStrengthToday] >= 70)
		{
			SetTimerEx("OnPlayerGymTrainStopped", 1500, false, "i", playerid);
			msg_info(playerid, "Nie mo¿esz dziœ ju¿ æwiczyæ.");
		}
	}
	else if(CharacterInfo[playerid][pGymType] == TRAIN_BENCH)
	{
		if(CharacterInfo[playerid][pGymPhase] == 3)
		{
  			CharacterInfo[playerid][pGymPhase] = 2;
  			CharacterInfo[playerid][pGymValue]++;
  			if(!(CharacterInfo[playerid][pGymValue]%5) && CharacterInfo[playerid][pStrength] < 1000)
			{
				if(CharacterInfo[playerid][pSuplement] == 1)
				{
					if(CharacterInfo[playerid][pStrength] + 2 > 1000)
					{
						CharacterInfo[playerid][pStrength]++;
						CharacterInfo[playerid][pStrengthToday]++;
					}
					else
					{
						CharacterInfo[playerid][pStrength] += 2;
						CharacterInfo[playerid][pStrengthToday] += 2;
					}
				}
				else
				{
					CharacterInfo[playerid][pStrength]++;
					CharacterInfo[playerid][pStrengthToday]++;
				}
			}
			
			switch(CharacterInfo[playerid][pSuplement])
			{
				case 0:
					format(string, sizeof(string), "~w~Aby opuscic sztange wcisnij:~n~~g~~h~~k~~CONVERSATION_NO~~n~~n~~w~Suplement:~n~~b~Brak~w~~n~Powtorzenia: ~b~%d~w~.~n~Sila: ~b~%d~w~.", CharacterInfo[playerid][pGymValue], CharacterInfo[playerid][pStrength]);
				case 1:
					format(string, sizeof(string), "~w~Aby opuscic sztange wcisnij:~n~~g~~h~~k~~CONVERSATION_NO~~n~~n~~w~Suplement:~n~~b~Wiecej otrzymywanej sily~w~~n~Powtorzenia: ~b~%d~w~.~n~Sila: ~b~%d~w~.", CharacterInfo[playerid][pGymValue], CharacterInfo[playerid][pStrength]);
				case 2:
					format(string, sizeof(string), "~w~Aby opuscic sztange wcisnij:~n~~g~~h~~k~~CONVERSATION_NO~~n~~n~~w~Suplement:~n~~b~Wiekszy limit dzienny - 70~w~~n~Powtorzenia: ~b~%d~w~.~n~Sila: ~b~%d~w~.", CharacterInfo[playerid][pGymValue], CharacterInfo[playerid][pStrength]);
				case 3:
					format(string, sizeof(string), "~w~Aby opuscic sztange wcisnij:~n~~g~~h~~k~~CONVERSATION_NO~~n~~n~~w~Suplement:~n~~b~Brak spadku dziennego sily~w~~n~Powtorzenia: ~b~%d~w~.~n~Sila: ~b~%d~w~.", CharacterInfo[playerid][pGymValue], CharacterInfo[playerid][pStrength]);
			}
			
			PlayerTextDrawSetString(playerid,DoorsTD[playerid], string);
   			
   			PlayerTextDrawShow(playerid, DoorsTD[playerid]);
			if(CharacterInfo[playerid][pSuplement] != 2 && CharacterInfo[playerid][pStrengthToday] >= 50)
			{
				SetTimerEx("OnPlayerGymTrainStopped", 1500, false, "i", playerid);
				msg_info(playerid, "Nie mo¿esz dziœ ju¿ æwiczyæ.");
			}
			else if(CharacterInfo[playerid][pSuplement] == 2 && CharacterInfo[playerid][pStrengthToday] >= 70)
			{
				SetTimerEx("OnPlayerGymTrainStopped", 1500, false, "i", playerid);
				msg_info(playerid, "Nie mo¿esz dziœ ju¿ æwiczyæ.");
			}
		}
		else if(CharacterInfo[playerid][pGymPhase] == 4)
		{
			CharacterInfo[playerid][pGymPhase] = 1;
			
			switch(CharacterInfo[playerid][pSuplement])
			{
				case 0:
					format(string, sizeof(string), "~w~Aby uniesc sztange wcisnij:~n~~g~~h~~k~~CONVERSATION_YES~~n~~n~~w~Suplement:~n~~b~Brak~w~~n~Powtorzenia: ~b~%d~w~.~n~Sila: ~b~%d~w~.", CharacterInfo[playerid][pGymValue], CharacterInfo[playerid][pStrength]);
				case 1:
					format(string, sizeof(string), "~w~Aby uniesc sztange wcisnij:~n~~g~~h~~k~~CONVERSATION_YES~~n~~n~~w~Suplement:~n~~b~Wiecej otrzymywanej sily~w~~n~Powtorzenia: ~b~%d~w~.~n~Sila: ~b~%d~w~.", CharacterInfo[playerid][pGymValue], CharacterInfo[playerid][pStrength]);
				case 2:
					format(string, sizeof(string), "~w~Aby uniesc sztange wcisnij:~n~~g~~h~~k~~CONVERSATION_YES~~n~~n~~w~Suplement:~n~~b~Wiekszy limit dzienny - 70~w~~n~Powtorzenia: ~b~%d~w~.~n~Sila: ~b~%d~w~.", CharacterInfo[playerid][pGymValue], CharacterInfo[playerid][pStrength]);
				case 3:
					format(string, sizeof(string), "~w~Aby uniesc sztange wcisnij:~n~~g~~h~~k~~CONVERSATION_YES~~n~~n~~w~Suplement:~n~~b~Brak spadku dziennego sily~w~~n~Powtorzenia: ~b~%d~w~.~n~Sila: ~b~%d~w~.", CharacterInfo[playerid][pGymValue], CharacterInfo[playerid][pStrength]);
			}
			
			PlayerTextDrawSetString(playerid,DoorsTD[playerid], string);
   			
   			PlayerTextDrawShow(playerid, DoorsTD[playerid]);
		}
	}
	else if(CharacterInfo[playerid][pGymType] == TRAIN_PUNCH_BAG)
	{
		CharacterInfo[playerid][pGymValue]++;
		format(string, sizeof(string), "Uderzaj w worek przy pomocy:~n~~g~~h~~k~~PED_LOCK_TARGET~ + ~k~~VEHICLE_ENTER_EXIT~~n~~n~~w~Trafienia: ~b~%d~w~/75.", CharacterInfo[playerid][pGymValue]);
		PlayerTextDrawSetString(playerid, DoorsTD[playerid], string);
		PlayerTextDrawShow(playerid, DoorsTD[playerid]);

		if(CharacterInfo[playerid][pGymValue] > 74)
		{
			switch(GetPlayerFightingStyle(playerid))
			{
				case FIGHT_STYLE_NORMAL:
					CharacterInfo[playerid][pFightStyle] = 0;
				case FIGHT_STYLE_BOXING:
					CharacterInfo[playerid][pFightStyle] = 1;
				case FIGHT_STYLE_KUNGFU:
					CharacterInfo[playerid][pFightStyle] = 2;
				case FIGHT_STYLE_KNEEHEAD:
					CharacterInfo[playerid][pFightStyle] = 3;
				default:
					CharacterInfo[playerid][pFightStyle] = 0;
			}
			CharacterInfo[playerid][pStrengthToday] += 20;
			format(string, sizeof(string), "UPDATE `srv_characters` SET `fightstyle`='%d' WHERE `player_uid` = '%d'", CharacterInfo[playerid][pFightStyle], CharacterInfo[playerid][pUID]);
			mysql_query(string);
			OnPlayerGymTrainStopped(playerid);
			msg_info(playerid, "Pomyœlnie nauczy³eœ siê nowego stylu walki.");
		}	
		CharacterInfo[playerid][pGymPhase]=0;
	}

	return 1;
}
