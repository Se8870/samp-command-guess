#include <a_samp>

#define YSI_NO_HEAP_MALLOC
#define YSI_NO_MODE_CACHE
#define YSI_NO_OPTIMISATION_MESSAGE
#define YSI_NO_VERSION_CHECK

#define USE_DEBUG

//#include <YSI_Coding\y_va>
//#include <YSI_Visual\y_commands>

#include <izcmd>
#include "command-guess.inc"

main() 
{
	print("Testing...");
}

public OnPlayerConnect(playerid)
{
	GameTextForPlayer(playerid,"~w~SA-MP: ~r~Bare Script",5000,5);
	return 1;
}

public OnPlayerSpawn(playerid)
{
	SetPlayerInterior(playerid,0);
	TogglePlayerClock(playerid,0);
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
   	return 1;
}

SetupPlayerForClassSelection(playerid)
{
 	SetPlayerInterior(playerid,14);
	SetPlayerPos(playerid,258.4893,-41.4008,1002.0234);
	SetPlayerFacingAngle(playerid, 270.0);
	SetPlayerCameraPos(playerid,256.0815,-43.0475,1004.0234);
	SetPlayerCameraLookAt(playerid,258.4893,-41.4008,1002.0234);
}

public OnPlayerRequestClass(playerid, classid)
{
	SetupPlayerForClassSelection(playerid);
	return 1;
}

public OnGameModeInit()
{
	SetGameModeText("Bare Script");
	ShowPlayerMarkers(1);
	ShowNameTags(1);
	AllowAdminTeleport(1);

	AddPlayerClass(265,1958.3783,1343.1572,15.3746,270.1425,0,0,0,0,-1,-1);
	
	// do i need to enable/disable this?!
	//Command_SetDeniedReturn(false);
	return 1;
}

#if defined _INC_y_va
SendClientMessageEx(playerid, color, const message[], GLOBAL_TAG_TYPES:...) {
	new 
		str[144];
	
	format(str, sizeof str, message, ___(3));
	SendClientMessage(playerid, color, str);
	return 1;
}
#endif

#if defined _INC_y_commands
public e_COMMAND_ERRORS:OnPlayerCommandReceived(playerid, cmdtext[], e_COMMAND_ERRORS:success) {
	if (success == COMMAND_UNDEFINED) {
		new 
			guessCmd[32];
		
		Command_Guess(guessCmd, cmdtext);

		//SendClientMessageEx(playerid, -1, "{FF0000}ERROR:{FFFFFF} \"%s\" is not found, did you mean \"%s\"?", cmdtext, guessCmd);
		return COMMAND_OK;
	}
	return COMMAND_OK;
}

YCMD:help(playerid, cmdtext[], help)
{
	return 1;
}

YCMD:cmds(playerid, cmdtext[], help)
{
	return 1;
}

YCMD:cmd(playerid, cmdtext[], help)
{
	return 1;
}

YCMD:cd(playerid, cmdtext[])
{
	return 1;
}
#else
public OnPlayerCommandPerformed(playerid, cmdtext[], success) {
	if (!success) {
		new 
			guessCmd[32];
		
		Command_Guess(guessCmd, cmdtext);

		//SendClientMessageEx(playerid, -1, "{FF0000}ERROR:{FFFFFF} \"%s\" is not found, did you mean \"%s\"?", cmdtext, guessCmd);
		return 1;
	}
	return 1;
}

CMD:help(playerid, cmdtext[])
{
	return 1;
}

CMD:cmds(playerid, cmdtext[])
{
	return 1;
}

CMD:cmd(playerid, cmdtext[])
{
	return 1;
}

CMD:cd(playerid, cmdtext[])
{
	return 1;
}
#endif