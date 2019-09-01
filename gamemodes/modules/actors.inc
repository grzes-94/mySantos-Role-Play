stock SpawnActor(uid)
{
  if(uid < 1 || uid >= MAX_ACTORS) return;
  if(ActorInfo[uid][aUID] == 0) return;
  
  if(ActorInfo[uid][aActor] != INVALID_ACTOR_ID)
  {
    UnspawnActor(uid);
  }
  
  ActorInfo[uid][aActor] = CreateActor(ActorInfo[uid][aSkin], ActorInfo[uid][aPosX], ActorInfo[uid][aPosY], ActorInfo[uid][aPosZ], ActorInfo[uid][aAngle]);
  SetActorVirtualWorld(ActorInfo[uid][aActor], ActorInfo[uid][aVW]);
  if(strlen(ActorInfo[uid][aName]) > 3)
  {
    ActorInfo[uid][aNick3D] = CreateDynamic3DTextLabel(ActorInfo[uid][aName], 0x808080CC,ActorInfo[uid][aPosX], ActorInfo[uid][aPosY], ActorInfo[uid][aPosZ] + 1.0, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, ActorInfo[uid][aVW]);
  } 
  else
  {
    ActorInfo[uid][aNick3D] = Text3D:INVALID_3DTEXT_ID;
  }
  if(0 < ActorInfo[uid][aAnimId] < MAX_ANIMS)
  {
    new anim_id = ActorInfo[uid][aAnimId];
    ApplyActorAnimation(ActorInfo[uid][aActor], AnimInfo[anim_id][aLib], AnimInfo[anim_id][aName], AnimInfo[anim_id][aSpeed], AnimInfo[anim_id][aOpt1], AnimInfo[anim_id][aOpt2], AnimInfo[anim_id][aOpt3], AnimInfo[anim_id][aOpt4], AnimInfo[anim_id][aOpt5]);
  }
  
}

stock UnspawnActor(uid)
{
  if(uid < 1 || uid >= MAX_ACTORS) return;
  if(ActorInfo[uid][aUID] == 0) return;
    
  DestroyActor(ActorInfo[uid][aActor]);
  ActorInfo[uid][aActor] = INVALID_ACTOR_ID;
  
  if(ActorInfo[uid][aNick3D] != Text3D:INVALID_3DTEXT_ID)
  {
    DestroyDynamic3DTextLabel(ActorInfo[uid][aNick3D]);
    ActorInfo[uid][aNick3D] = Text3D:INVALID_3DTEXT_ID;
  }
}
stock AddActor(nick[32], skin, Float:x, Float:y, Float:z, Float:angle, vw)
{
  new uid;
  ForeachEx(i, MAX_ACTORS)
  {
    if(ActorInfo[i][aUID] == 0 && i != 0)
    {
      uid = i;
      break;
    }
  }
  if(uid == 0)
    return 0;
  mysql_real_escape_string(nick,nick);
  
  ActorInfo[uid][aUID] = uid;
  ActorInfo[uid][aName] = nick;
  ActorInfo[uid][aSkin] = skin;
  ActorInfo[uid][aPosX] = x;
  ActorInfo[uid][aPosY] = y;
  ActorInfo[uid][aPosZ] = z;
  ActorInfo[uid][aAngle] = angle;
  ActorInfo[uid][aVW] = vw;
  ActorInfo[uid][aActor] = INVALID_ACTOR_ID;
  
  new query[256];
  format(query,sizeof(query),"INSERT INTO `srv_actors` VALUES ('%d', '%s','%d','%f','%f','%f','%d','%f',0)",uid,nick,skin,x,y,z,vw,angle);
  mysql_query(query);
  
  SpawnActor(uid);
  
  return uid;
}
stock DeleteActor(uid)
{
  if(uid < 0 || uid >= MAX_ACTORS || ActorInfo[uid][aUID] == 0 )
    return;
    
  new query[256];
  format(query,sizeof(query),"DELETE FROM `srv_actors` WHERE `uid` = '%d' ",uid);
  mysql_query(query);
  
  UnspawnActor(uid);
  ActorInfo[uid][aUID] = 0;
  ActorInfo[uid][aAnimId] = 0;
  ActorInfo[uid][aSkin] = 0;
  return;
}
