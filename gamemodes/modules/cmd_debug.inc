#if defined DEBUG_MODE

CMD:ustawadm(playerid,params[])
{
	if(CharacterInfo[playerid][pUID] > 2) return 1;
	new level;
	if(sscanf(params, "i", level))
		return 1;
	else
	{
		if(level < 0 || level > 5)
			return msg_error(playerid,"Dozwolony poziom 0-5");
		CharacterInfo[playerid][pAdmin]=level;
		SendClientMessage(playerid, -1, "Zmieni³eœ poziom @");
		if(!level && CharacterInfo[playerid][pAdminDuty])
		{
			CharacterInfo[playerid][pAdminDuty] = false;
			
			if(IsPlayerPremium(playerid)) CharacterInfo[playerid][pNickColor] = COLOR_PREMIUM;
			else CharacterInfo[playerid][pNickColor] = COLOR_USER;
		}
	}

	return 1;
}

CMD:sprawdzkierowca(playerid,params)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		SendClientMessage(playerid, COLOR_RED, "[DEBUG] Jesteœ kierowc¹.");
		if(GetPlayerVehicleID(playerid))
			SendClientMessage(playerid, COLOR_RED, "[DEBUG] Posiadasz pojazd.");
		else
			SendClientMessage(playerid, COLOR_RED, "[DEBUG] Nie posiadasz pojazdu.");
	}
	else
	{
		SendClientMessage(playerid, COLOR_RED, "[DEBUG] Nie jesteœ kierowc¹.");
		if(GetPlayerVehicleID(playerid))
			SendClientMessage(playerid, COLOR_RED, "[DEBUG] Posiadasz pojazd.");
		else
			SendClientMessage(playerid, COLOR_RED, "[DEBUG] Nie posiadasz pojazdu.");
	}
	
	return 1;
}

CMD:zamknijwchuj(playerid,params)
{
	if(CharacterInfo[playerid][pUID] > 2) return 1;
	SendRconCommand("exit");
	return 1;
}
CMD:dmg(playerid,params[])
{
	new vehid=GetPlayerVehicleID(playerid);
	if(vehid)
	{
		new panels, doors, lights, tires;
		GetVehicleDamageStatus(vehid, panels, doors, lights, tires);
		SendClientMessage(playerid, COLOR_GREEN, "---------------------------------------");
		SendClientMessageFormat(playerid, -1,"panels: %d, doors: %d, lights:%d, tires:%d",panels, doors, lights, tires);
		new bonnet,boot,driver_door,passenger_door,panel1,panel2,light1,light2,light3,light4;
		new tire1,tire2,tire3,tire4;
		decode_doors(doors, bonnet, boot, driver_door, passenger_door);
		decode_panels(panels,panel1,panel2);
		decode_lights(lights,light1,light2,light3,light4);
		decode_tires(tires,tire1,tire2,tire3,tire4);
		SendClientMessageFormat(playerid,-1,"bonnet %d boot %d driver %d passenger %d = %d", bonnet, boot, driver_door, passenger_door,bonnet+boot+driver_door+passenger_door);
		SendClientMessageFormat(playerid,-1,"Panels: %d %d = %d ",panel1,panel2,panel1+panel2);
		SendClientMessageFormat(playerid,-1,"Lights: %d %d %d %d = %d ",light1,light2,light3,light4,light1+light2+light3+light4);
		SendClientMessageFormat(playerid,-1,"Tires: %d %d %d %d = %d",tire1,tire2,tire3,tire4,tire1+tire2+tire3+tire4);
	}
	return 1;
}
CMD:jebnijbasemsynu(playerid,params[])
{
	if(strlen(params))
	{
		new sound=strval(params);
		PlayerPlaySound(playerid, sound, 0, 0, 0);
	}
	return 1;
}
CMD:staty(playerid,params)
{
	new string[128];
	format(string,sizeof(string),"VEH: %d",_VEH_COUNT);
	SendClientMessage(playerid, -1, string);
	format(string,sizeof(string),"ITEMS: %d",_ITEM_COUNT);
	SendClientMessage(playerid, -1, string);
	format(string,sizeof(string),"OBJECTS: %d",_OBJ_COUNT);
	SendClientMessage(playerid, -1, string);
	return 1;
}

CMD:waliduj(playerid,params[])
{
	return ValidateDesc(params);
}
CMD:xd(playerid,params[])
{
	new string[256];
	sscanf(params,"s[256]",string);
	new xd,search;
	while((xd=strfind(string, " xd", true,search))!=-1)
	{
		strdel(string, xd+1, xd+3);
		strins(string, " {C2A2DA}*wybucha œmiechem*{ffffff}", xd+1,sizeof(string));
		search=xd+2;
	}
	cmd_l(playerid,string);


	return 1;
}
CMD:special(playerid,params[])
{
	new action=strval(params);
	SetPlayerSpecialAction(playerid, action);
	return 1;
}
CMD:tajnyszyfr(playerid,params[])
{
	new n=strval(params);
	new prefix,temp,hex[5],i,code[10];
	new sufix=random(10);
	if(n<100)
	{
		prefix='A'+random(10);
		n+=5371+prefix+18*sufix;
	}
	else if(n<5000)
	{
		prefix='K'+random(10);
		n+=4357+prefix+18*sufix;
	}
	else
	{
		prefix='W'+random(4);
		n+=23+prefix+18*sufix;
	}
	while(n!=0)
	{
		temp = n % 17;
		if( temp < 10)
			temp =temp + 48;
	  	else
		 	temp = temp + 55;

	  	hex[i++]= temp;
	  	n = n / 17;
  	}
  	format(code,sizeof(code),"%s%s%d",prefix,hex,sufix);	


  	new pref=code[0];
  	new suf=strval(code[5]);
  	new dec[5];
  	strmid(dec, code, 1, 5);

  	for(new j=0;j<4;j++)
  	{
  		if(dec[j]>60)
  			dec[j]-=55;
  		else
  			dec[j]-=48;
  	}
  	new number=dec[0]+ dec[1]*17 + dec[2]*289 + dec[3]*4913;
  	if(prefix<'K')
  		number=number-pref-5371-18*suf;
  	else if(prefix>='W')
  		number=number-pref-23-18*suf;
  	else
  		number=number-pref-4357-18*suf;

  	SendClientMessageFormat(playerid,-1, "Przed: %d, po: %s, zdekodowane: %d",strval(params),code,number);


	return 1;
}
CMD:kolorek(playerid,params[])
{
	new color[10];
	if(!sscanf(params,"s[10]",color))
	{
		new string[256];
		format(string,sizeof(string),"Kolor chuje muje dzikie wê¿e");
		format(string,sizeof(string),"%s\n{%s}Kolor wybrany i jakiœ tekst kalafior",string,color);
		format(string,sizeof(string),"%s\nKolor{ffffff} bia³y dzike ¿mije",string);
		ShowPlayerDialog(playerid,D_INFO,DIALOG_STYLE_LIST,"Test koloru",string,"Penis","");
	}
	return 1;
}

CMD:przypakuj(playerid,params[])
{
	new val=strval(params);
	if(val < 0 || val >1000)
		return msg_error(playerid,"Te, z³a wartoœæ kolego. 0-1000 ma byæ");

	CharacterInfo[playerid][pStrength]=val;
	SavePlayerStats(playerid,SAVE_PLAYER_BASIC);
	SendClientMessageFormat(playerid, -1, "Przypakowa³eœ %dj",val);

	return 1;
}

CMD:xardas(playerid,params[])
{
	SendClientMessageFormat(playerid,-1,"Xardas mówi ¿e kl¹twa wynosi %d.",CharacterInfo[playerid][pCurse]);
	return 1;
}

//-------------------------------------------------------
CMD:me2(playerid,params[])
{
	new text[144];
	if(sscanf(params,"s[144]",text))
	{
		SendClientMessage(playerid, 0xFF0F3B, "[INFO] {ffffff}Prawid³owe u¿ycie komendy: /me [tekst]");
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		return 1;
	}

	//oblsuga blêdów

	new name[MAX_PLAYER_NAME], Float:x, Float:y, Float:z,vw;
	GetPlayerName(playerid, name, sizeof(name));
	for(new i = 0, len=strlen(name); i < len; i++)
	{
		if(name[i] == '_') name[i] = ' ';
	}

	text[0] = chrtolower(text[0]);
	if(text[strlen(text)-1] != '.')
		strins(text, ".", strlen(text));

	GetPlayerPos(playerid,x,y,z);
	vw=GetPlayerVirtualWorld(playerid);

	format(text, sizeof(text), "* %s %s", name, text);

	for(new i=0,pool=GetPlayerPoolSize();i<=pool;i++)
	{
		if(IsPlayerConnected(i) && GetPlayerVirtualWorld(i)==vw && IsPlayerInRangeOfPoint(i, 20.0, x, y, z))
		{
			SendClientMessage(playerid, 0xC2A2DAFF, text);

		}
	}
	return 1;
}



#endif