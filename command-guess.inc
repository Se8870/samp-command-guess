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

#if !defined _samp_included
    #error Please include a_samp before using this
#endif

#if !defined strcopy
    stock strcopy(dest[], const source[], maxlength=sizeof dest)
	    return strcat((dest[0] = EOS, dest), source, maxlength);
#endif

#if defined _INC_y_commands
    #if !defined _INC_y_iterate
        #tryinclude <YSI_Data\y_foreach>
    #endif
    #if !defined _INC_y_iterate
        #tryinclude <YSI\y_foreach>
    #endif
    #if !defined _INC_y_iterate
        #error "Cannot find y_iterate/y_foreach"
    #endif
#else
    #if !defined AMX_HEADER_INC
        #tryinclude <amx_header>
    #endif
    #if !defined AMX_HEADER_INC
        #tryinclude <amx_assembly/amx_header>
    #endif
    #if !defined AMX_HEADER_INC
        #tryinclude <amx/amx_header>
    #endif
    #if !defined AMX_HEADER_INC
        #error "Cannot find amx_header.inc, please download it from https://github.com/Zeex/amx_assembly"
    #endif
 
    /*
        CGUESS_CMD_FUNC
        -------------
        This pre-processor is used for finding the right length of one of these internal functions below
        You also can add another one using `#define CGUESS_CUSTOM_CMD_FUNC` before including `command_guess.inc`

        Example Code:

        ```pawn
        #define CGUESS_CUSTOM_CMD_FUNC "ahcmd_", "bonk_cmd", "loli_cmd@"
        #include <command_guess>
        ```
    */

    #if !defined CGUESS_CORE_CMD_FUNC
        #define CGUESS_CORE_CMD_FUNC "cmd", "cmd_", "dc_cmd", "dcmd", "dcmd_", "_dcmd@", "kcmd_", "_kcmd@"
    #endif

    #if !defined CGUESS_CUSTOM_CMD_FUNC
        #define CGUESS_CMD_FUNC CGUESS_CORE_CMD_FUNC
    #else
        #define CGUESS_CMD_FUNC CGUESS_CORE_CMD_FUNC, CGUESS_CUSTOM_CMD_FUNC
    #endif


    /*
        Command Internal Name
        ----------------------
        This variable can be used for holding the command internal name and adding it for looping stuff.
        Each command processor have it's own unique internal name, so that's why i'm using this instead of
        Trying to use dumb method from 3000 BC.
    */

    static stock g_arrCmdInternalName[][32 + 1] = {CGUESS_CMD_FUNC};
#endif

/*
    CGUESS_MAX_CACHE_COMMAND
    -------------
    This pre-processor will be used if there is no maximum commaands when using izcmd or simillar
    Because they're designed to bypass the limitation and decided to use the string that user
    input.
*/

#if !defined CGUESS_MAX_CACHE_COMMAND
    #if defined MAX_COMMANDS
        #define CGUESS_MAX_CACHE_COMMAND MAX_COMMANDS
    #else
        #define CGUESS_MAX_CACHE_COMMAND 500
    #endif
#endif

 /*
    Command Storage
    ----------------
    This variable can be used for holding the command names and adding it into index for looping stuff.
    Since i want to minimalize the usage of YSI and not everyone will use it, it is required to have
    `g_sRegisteredCommands`
*/

static stock
    g_sRegisteredCommands = -1,
    g_sCommandName[CGUESS_MAX_CACHE_COMMAND][32 + 1];

/**
 *   <summary>This function will try to search available command and make a prediction to guess the right command.</summary>
 *   <param name="output">Used for storing the results into your variable</param>
 *   <param name="cmdtext">The failed command that is used for guessing</param>
 *   <param name="len">Length of your output</param>
 *   <returns>Minimum distance between available command and the command from cmdtext</returns>
 */

 /*
    This function will try to search available command and make a prediction to guess the right command. 
    Returns: Minimum distance between available command and the command from cmdtext
 */
stock Command_Guess(output[], const cmdtext[], len = sizeof output)
{
    new 
        dist,
        min_dist = 0x7FFFFFFF, 
        min_idx = -1
    ;

    for (new i = 0; i <= g_sRegisteredCommands; i ++)
    {
        dist = CGuess_GetDistance(cmdtext[1], g_sCommandName[i]);

        if (dist < min_dist)
        {
            min_dist = dist;
            min_idx = i;
        }
    }

    if (('A' <= cmdtext[0] <= 'Z') || ('a' <= cmdtext[0] <= 'z') || ('0' <= cmdtext[0] <= '9')) 
    {
        strcopy(output, g_sCommandName[min_idx], len);
    }
    else 
    {
        format(output, len, "%c%s", cmdtext[0], g_sCommandName[min_idx]);
    }
    return min_dist;
}

/**
 *   <summary>This was used for getting the distance between two strings using Levenshtein Distance method</summary>
 *   <param name="a">The first string</param>
 *   <param name="b">The second string</param>
 *   <seealso name="CGuess_Init" />
 *   <returns>The distance between two strings</returns>
*/

static CGuess_GetDistance(const a[], const b[]) {
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

/*
    Script Init
    -------------
    This script init will try it's best to detect if the script using this was filterscript or gamemode
    for calling `CGuess_Init`.
*/

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

/**
 *   <summary>This internal function was used for checking the command internal function name.</summary>
 *   <param name="commandname">The command function name that is used for checking</param>
 *   <seealso name="CGuess_Init" />
 *   <returns>the size of internal function name length, or <b><c>-1</c></b> if it's not found</returns>
*/

static stock CGuess_CheckInternalFunc(const commandName[])
{
    // strcmp check is case sensitive, to catch any weird names.
    for (new i = 0, j = sizeof(g_arrCmdInternalName); i < j; i ++)
    {
        new 
	    cmdLen = strlen(g_arrCmdInternalName[i]);

        if (!strcmp(commandName, g_arrCmdInternalName[i], true, cmdLen))
        {
	    return cmdLen + 1;
        }
    }
    return -1;
}

/**
 *   <summary>This was used for caching the commands as many as possible</summary>
 *   <param name=""></param>
 *   <remarks>The code may get slower depending on how many command did you have.
 *   You can always increase `CGUESS_MAX_CACHE_COMMAND` by adding `#define CGUESS_MAX_CACHE_COMMAND (number)` 
 *   to cache more commands before including command-guess.inc</remarks>
 *   <returns>This function doesn't have any return types</returns>
*/

static CGuess_Init()
{
    #if defined _INC_y_commands
        foreach (new i : Command())
        {
            if (Command_IsValid(i))
            {
                // this ensures for loop to be broken
                // and, no need to continue the loop.
                if ((g_sRegisteredCommands + 1) >= CGUESS_MAX_CACHE_COMMAND)
                    break;

                strcopy(g_sCommandName[++g_sRegisteredCommands], Command_GetName(i), 32);
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

            if ((trimmedPos = CGuess_CheckInternalFunc(tmpName)) != -1)
            {
                // this ensures for loop to be broken
                // and, no need to continue the loop.
                if ((g_sRegisteredCommands + 1) >= CGUESS_MAX_CACHE_COMMAND)
                    break;
                
                format(g_sCommandName[++g_sRegisteredCommands], 32, "%s", tmpName[trimmedPos]);
            }
        }
    #endif
    return 1;
}
