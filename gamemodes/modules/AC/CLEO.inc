/*
*
*              "fuckCleo.inc" - #1 Anti-cleo mod include
*                      Created/Debugged most by Lorenc_
*
*      Thanks to:
*                      Cessil, Infamous and [FeK]Drakins
*
*/

/* ** Stop Duplicating Code! ** */
#if defined _fcleo_included
#endinput
#endif
#define _fcleo_included

/* ** Configuration ** */
#define FILE_VERSION                            "0.1.5"

#define CLEO_FAKEKILL                           ( 1 )
#define CLEO_CARWARP                            ( 2 )
#define CLEO_PLAYERBUGGER                       ( 3 ) // This number will never be called from OnPlayerCleoDetected
#define CLEO_CARSWING                           ( 4 )

/* ** Variables ** */
enum E_CLEO_DATA
{
	E_FK_LASTDEATH,                                 E_FK_DEATHSPAM,
	E_CW_TIME,                                              E_CW_VEHID,
	Float: E_PB_X,                                  Float: E_PB_Y,                          Float: E_PB_Z
};

new stock g_cleoData                                              [ MAX_PLAYERS ] [ E_CLEO_DATA ],

bool: RL_OPU,
bool: RL_OPD,
bool: RL_OPSC,
bool: RL_OPDC
;

/* ** Forwards ** */
forward OnPlayerCleoDetected            ( playerid, cleoid );

public OnPlayerStateChange( playerid, newstate, oldstate )
{
	if( newstate == PLAYER_STATE_DRIVER )
	{
		if( GetPlayerVehicleID( playerid ) != g_cleoData[ playerid ] [ E_CW_VEHID ] )
		{
			if( g_cleoData[ playerid ] [ E_CW_TIME ] > gettime( ) )
			{
				CallLocalFunction( "OnPlayerCleoDetected", "dd", playerid, CLEO_CARWARP );
				return 1;
			}
			g_cleoData[ playerid ] [ E_CW_TIME ] = gettime( ) + 1;
			g_cleoData[ playerid ] [ E_CW_VEHID ] = GetPlayerVehicleID( playerid );
		}
	}
	return ( RL_OPSC ) ? CallLocalFunction( "RL_OnPlayerStateChange", "ddd", playerid, newstate, oldstate ) : 1;
}

#if defined _ALS_OnPlayerStateChange
#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif
#define OnPlayerStateChange RL_OnPlayerStateChange
forward RL_OnPlayerStateChange( playerid, newstate, oldstate );

public OnPlayerDeath( playerid, killerid, reason )
{
	new time = gettime( );
	switch( time - g_cleoData[ playerid ] [ E_FK_LASTDEATH ] )
	{
		case 0 .. 3:
		{
			g_cleoData[ playerid ] [ E_FK_DEATHSPAM ] ++;
			if( g_cleoData[ playerid ] [ E_FK_DEATHSPAM ] >= 3 )
			{
				CallLocalFunction( "OnPlayerCleoDetected", "dd", playerid, CLEO_FAKEKILL );
				return 1;
			}
		}
		default: g_cleoData[ playerid ] [ E_FK_DEATHSPAM ] = 0;
	}
	g_cleoData[ playerid ] [ E_FK_LASTDEATH ] = time;
	return ( RL_OPD ) ? CallLocalFunction( "RL_OnPlayerDeath", "ddd", playerid, killerid, reason ) : 1;
}

#if defined _ALS_OnPlayerDeath
#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath RL_OnPlayerDeath
forward RL_OnPlayerDeath( playerid, killerid, reason );

public OnPlayerUpdate( playerid )
{
	static
	Float: X,       Float: Y,       Float: Z,
	Float: vX,      Float: vY,      Float: vZ
	;
	GetPlayerPos( playerid, X, Y, Z );
	
	if( X >= 99999.0 || Y >= 99999.0 || Z >= 99999.0 || X <= -99999.0 || Y <= -99999.0 || Z <= -99999.0 ) {
		SetPlayerPos( playerid, g_cleoData[ playerid ] [ E_PB_X ], g_cleoData[ playerid ] [ E_PB_Y ], g_cleoData[ playerid ] [ E_PB_Z ] );
	}
	else
	{
		g_cleoData[ playerid ] [ E_PB_X ] = X;
		g_cleoData[ playerid ] [ E_PB_Y ] = Y;
		g_cleoData[ playerid ] [ E_PB_Z ] = Z;
	}
	
	if( IsPlayerInAnyVehicle( playerid ) )
	{
		GetPlayerPos( playerid, X, Y, Z );
		GetVehicleVelocity( GetPlayerVehicleID( playerid ), vX, vY, vZ );
		if( ( vX > 3.0 || vY > 3.0 || vZ > 3.0 || vX < -3.0 || vY < -3.0 || vZ < -3.0 ) && ( vX != X && vY != Y && vZ != Z ) )
		{
			CallLocalFunction( "OnPlayerCleoDetected", "dd", playerid, CLEO_CARSWING );
		}
	}
	return ( RL_OPU ) ? CallLocalFunction( "RL_OnPlayerUpdate", "d", playerid ) : 1;
}

#if defined _ALS_OnPlayerUpdate
#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate RL_OnPlayerUpdate
forward RL_OnPlayerUpdate( playerid );

public OnPlayerDisconnect(playerid, reason)
{
	// Pointless reseting, but just incase!
	g_cleoData[ playerid ] [ E_FK_LASTDEATH ] = 0;
	g_cleoData[ playerid ] [ E_FK_DEATHSPAM ] = 0;
	g_cleoData[ playerid ] [ E_CW_TIME ] = 0;
	g_cleoData[ playerid ] [ E_CW_VEHID ] = INVALID_VEHICLE_ID;
	g_cleoData[ playerid ] [ E_PB_X ] = -1;
	g_cleoData[ playerid ] [ E_PB_Y ] = -1;
	g_cleoData[ playerid ] [ E_PB_Z ] = -1;
	return ( RL_OPDC ) ? CallLocalFunction( "RL_OnPlayerDisconnect", "dd", playerid, reason ) : 1;
}

#if defined _ALS_OnPlayerDisconnect
#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect RL_OnPlayerDisconnect
forward RL_OnPlayerDisconnect( playerid, reason );

#if !defined FILTERSCRIPT
public OnGameModeInit()
{
	RL_OPU = ( funcidx( "RL_OnPlayerUpdate" ) != -1 );
	RL_OPD = ( funcidx( "RL_OnPlayerDeath" ) != -1 );
	RL_OPSC = ( funcidx( "RL_OnPlayerStateChange" ) != -1 );
	RL_OPDC = ( funcidx( "RL_OnPlayerDisconnect" ) != -1 );
	return ( funcidx( "RL_OnGameModeInit" ) != -1 ) ? CallLocalFunction( "RL_OnGameModeInit", "" ) : 1;
}
#if defined _ALS_OnGameModeInit
#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit RL_OnGameModeInit
forward RL_OnGameModeInit();
#else
	public OnFilterScriptInit()
{
	RL_OPU = ( funcidx( "RL_OnPlayerUpdate" ) != -1 );
	RL_OPD = ( funcidx( "RL_OnPlayerDeath" ) != -1 );
	RL_OPSC = ( funcidx( "RL_OnPlayerStateChange" ) != -1 );
	RL_OPDC = ( funcidx( "RL_OnPlayerDisconnect" ) != -1 );
	return ( funcidx( "RL_OnFilterScriptInit" ) != -1 ) ? CallLocalFunction( "RL_OnFilterScriptInit", "" ) : 1;
}
#if defined _ALS_OnFilterScriptInit
#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit RL_OnFilterScriptInit
forward RL_OnFilterScriptInit();
#endif