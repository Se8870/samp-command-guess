/*
    command-guess.inc 
    By: Kirima

    Credits:
        - Southclaws for Levenshtein Distance function
        - Zeex for amx_assembly
*/

#if defined _INC_guess_command
    #endinput
#endif 

#define _INC_guess_command

#include <string>
#include <amx_header>

#if !defined MAX_COMMANDS
    #define MAX_COMMANDS 500
#endif 

static stock
    g_sRegisteredCommands = -1,
    g_sCommandName[MAX_COMMANDS][32 + 1];


stock Command_Guess(output[], const cmdtext[], len = sizeof output)
{
    new 
        dist,
        min_dist = 0x7FFFFFFF, 
        min_idx = -1
    ;

    for (new i = 0; i <= g_sRegisteredCommands; i ++)
    {
        dist = getDistance(cmdtext[1], g_sCommandName[i]);

        if (dist < min_dist)
        {
            min_dist = dist;
            min_idx = i;
        }
    }

    if (('A' <= cmdtext[0] <= 'Z') || ('a' <= cmdtext[0] <= 'z') || ('0' <= cmdtext[0] <= '9')) 
    {
        format(output, len, g_sCommandName[min_idx]);
    }
    else 
    {
        format(output, len, "%c%s", cmdtext[0], g_sCommandName[min_idx]);
    }
    return 1;
}

static CGuess_Init()
{
    #if defined _INC_y_commands
        for (new i = 0; i < MAX_COMMANDS; i ++)
        {
            if (Command_IsValid(i))
            {
                g_sRegisteredCommands ++;
                format(g_sCommandName[g_sRegisteredCommands], 32, "%s", Command_GetName(i)));
            }
        }
    #else
        new 
            hdr[AMX_HDR];
        
        GetAmxHeader(hdr);

        for (new i = 0, j = GetNumPublics(hdr); i < j; i ++)
        {
            new 
                trimmedPos,
                tmpName[32 + 1];

            GetPublicNameFromIndex(i, tmpName);
            
            if ((trimmedPos = IsValidCommandName(tmpName)) == -1)
            {
                continue;
            }
            else
            {
                if (i < MAX_COMMANDS)
                {
                    g_sRegisteredCommands ++;
                    format(g_sCommandName[g_sRegisteredCommands], 32, "%s", tmpName[trimmedPos]);
                }
            }
        }
    #endif
    return 1;
}

// using 130000 BC method, will give you correct starting index of cmds
static IsValidCommandName(const commandName[])
{
    if (strfind(commandName, "cmd", true) != -1)
        return 4;

    if (strfind(commandName, "cmd_", true) != -1)
        return 5;

    if (strfind(commandName, "dc_cmd", true) != -1)
        return 7;

    if (strfnd(commandName, "dcmd", true) != -1)
        return 5;

    if (strfind(commandName, "dcmd_", true) != -1)
        return 6;

    if (strfind(commandName, "_dcmd@", true) != -1)
        return 7;

    return -1;
}

static getDistance(const a[], const b[]) {
	new
		aLength = strlen(a),
		bLength = strlen(b),
		cache[256],
		index = 0,
		bIndex = 0,
		distance,
		bDistance,
		result,
		code;

	if (!strcmp(a, b)) {
		return 0;
	}

	if (aLength == 0) {
		return bLength;
	}

	if (bLength == 0) {
		return aLength;
	}

	while (index < aLength) {
		cache[index] = index + 1;
		index++;
	}

	while (bIndex < bLength) {
		code = b[bIndex];
		result = distance = bIndex++;
		index = -1;

		while (++index < aLength) {
			bDistance = code == a[index] ? distance : distance + 1;
			distance = cache[index];

			cache[index] = result = distance > result
			? bDistance > result
				? result + 1
				: bDistance
			: bDistance > distance
				? distance + 1
				: bDistance;
		}
	}

	return result;
}

static stock 
    g_sScriptIndicator = false;

public OnGameModeInit()
{
    if (!g_sScriptIndicator)
    {
        CGuess_Init();
        g_sScriptIndicator = true;
    }
    #if defined CGuess_OnGameModeInit
        return CGuess_OnGameModeInit();
    #else
        return 1;
    #endif
}

public OnFilterScriptInit()
{
    if (!g_sScriptIndicator)
    {
        CGuess_Init();
        g_sScriptIndicator = true;
    }
    #if defined CGuess_OnFilterScriptInit
        return CGuess_OnFilterScriptInit();
    #else
        return 1;
    #endif
}

#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif

#define OnGameModeInit CGuess_OnGameModeInit
#if defined CGuess_OnGameModeInit
    forward CGuess_OnGameModeInit();
#endif

#if defined _ALS_OnFilterScriptInit
    #undef OnFilterScriptInit
#else
    #define _ALS_OnFilterScriptInit
#endif

#define OnFilterScriptInit CGuess_OnFilterScriptInit
#if defined CGuess_OnFilterScriptInit
    forward CGuess_OnFilterScriptInit();
#endif