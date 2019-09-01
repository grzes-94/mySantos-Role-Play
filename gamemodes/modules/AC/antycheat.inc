public OnPlayerCleoDetected(playerid, cleoid)
{
	if(!isACDetectionJustified(playerid))
	{
		switch(cleoid)
		{
			case CLEO_FAKEKILL:
			{
				//CharacterInfo[playerid][pFakeKill]++;
				SendAdminMessageFormat(COLOR_RED, "[AC] %s(%d) [%s] prawdopodobnie cheatuje (FakeKill), obserwuj go!", PlayerName3(playerid), playerid, CharacterInfo[playerid][pGlobalNick]);
				
				/*if(CharacterInfo[playerid][pFakeKill] >= 3)
				{
					SendClientMessage(playerid,COLOR_RED,"[AC] Wykryto cheaty. Twoje konto zostanie zbanowane.");
					SendAdminMessageFormat(COLOR_RED,"[AC] %s(%d) [%s] zosta? zbanowany za cheaty (FakeKill).", PlayerName3(playerid), playerid, CharacterInfo[playerid][pGlobalNick]);
					
					GivePenalty(playerid, -1, gettime(), PENALTY_BAN, 0, "FakeKill");
					
					CharacterInfo[playerid][pBlock] += BLOCK_BAN;
					AddBan(playerid);
					
					KickWithWait(playerid);
				}*/
			}
			case CLEO_CARWARP:
			{
				//CharacterInfo[playerid][pCarWarp]++;
				SendAdminMessageFormat(COLOR_RED, "[AC] %s(%d) [%s] prawdopodobnie cheatuje (CarWarp), obserwuj go!", PlayerName3(playerid), playerid, CharacterInfo[playerid][pGlobalNick]);
				
				/*if(CharacterInfo[playerid][pCarWarp] >= 3)
				{
					SendClientMessage(playerid,COLOR_RED,"[AC] Wykryto cheaty. Twoje konto zostanie zbanowane.");
					SendAdminMessageFormat(COLOR_RED,"[AC] %s(%d) [%s] zosta? zbanowany za cheaty (CarWarp).", PlayerName3(playerid), playerid, CharacterInfo[playerid][pGlobalNick]);
					
					GivePenalty(playerid, -1, gettime(), PENALTY_BAN, 0, "CarWarp");
					
					CharacterInfo[playerid][pBlock] += BLOCK_BAN;
					AddBan(playerid);
					
					KickWithWait(playerid);
				}*/
			}
			case CLEO_CARSWING:
			{
				//CharacterInfo[playerid][pCarSwing]++;
				SendAdminMessageFormat(COLOR_RED, "[AC] %s(%d) [%s] prawdopodobnie cheatuje (CarSwing), obserwuj go!", PlayerName3(playerid), playerid, CharacterInfo[playerid][pGlobalNick]);
				
				/*if(CharacterInfo[playerid][pCarSwing] >= 3)
				{
					SendClientMessage(playerid,COLOR_RED,"[AC] Wykryto cheaty. Twoje konto zostanie zbanowane.");
					SendAdminMessageFormat(COLOR_RED,"[AC] %s(%d) [%s] zosta? zbanowany za cheaty (CarSwing).", PlayerName3(playerid), playerid, CharacterInfo[playerid][pGlobalNick]);
					
					GivePenalty(playerid, -1, gettime(), PENALTY_BAN, 0, "CarSwing");
					
					CharacterInfo[playerid][pBlock] += BLOCK_BAN;
					AddBan(playerid);
					
					KickWithWait(playerid);
				}*/
			}
		}
	}
}

public OnPlayerFakeConnect(playerid)//AntiFC.inc
{
	if(!isACDetectionJustified(playerid))
		SendAdminMessageFormat(COLOR_RED, "[AC] %s(%d) [%s] prawdopodobnie cheatuje (FakeConnect), obserwuj go!", PlayerName3(playerid), playerid, CharacterInfo[playerid][pGlobalNick]);
}

public OnPlayerSlide(playerid, weaponid, Float:speed)//AntiSba.inc
{
	if(!isACDetectionJustified(playerid))
		SendAdminMessageFormat(COLOR_RED, "[AC] %s(%d) [%s] prawdopodobnie cheatuje (PlayerSlide), obserwuj go!", PlayerName3(playerid), playerid, CharacterInfo[playerid][pGlobalNick]);
}

public OnPlayerSpamCars(playerid, number)//rAcs.inc
{
	if(!isACDetectionJustified(playerid))
		SendAdminMessageFormat(COLOR_RED, "[AC] %s(%d) [%s] prawdopodobnie cheatuje (SpamCars), obserwuj go!", PlayerName3(playerid), playerid, CharacterInfo[playerid][pGlobalNick]);
}

public OnPlayerSpeedCheat(playerid, speedtype)//rAsc.inc
{
	if(!isACDetectionJustified(playerid))
	{
		/* PRZETESTOWANE, WORKING
		if(!CharacterInfo[i][pPenalty] && !CharacterInfo[i][pAdmin])
		{
			GivePenalty(i, -1, gettime(), PENALTY_KICK, 0, "SpeedHack");
			CharacterInfo[i][pPenalty] = true;
			KickWithWait(i);
		}*/
		
		SendAdminMessageFormat(COLOR_RED, "[AC] %s(%d) [%s] prawdopodobnie cheatuje (SpeedHack), obserwuj go!", PlayerName3(playerid), playerid, CharacterInfo[playerid][pGlobalNick]);
	}
}

stock isACDetectionJustified(playerid)
{
	return gettime() - CharacterInfo[playerid][pACLastJustification] < 5 || CharacterInfo[playerid][pAdmin] > 0 ;
}
