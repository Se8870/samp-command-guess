/*
    command-guess.inc 
    By: Kirima

    Credits:
        - Southclaws for Levenshtein Distance function
        - Y_Less for y_hooks
        - Zeex for amx_assembly
*/

#if defined _INC_guess_command
    #endinput
#endif 

#define _INC_guess_command

#tryinclude <YSI_Coding\y_hooks>
#tryinclude <amx_header>

#if !defined AMX_HEADER_INC && _INC_y_hooks
    #error Please install both YSI and amx_assembly first before include this.
#endif

#if defined USE_DEBUG
    #define Debug(%0) printf("[CGuess debug]: "%0)
#else 
    #define Debug(%0);
#endif

#if !defined MAX_COMMANDS
    #define MAX_COMMANDS 500
#endif 

new 
    g_RegisteredCommands,
    g_CommandNames[MAX_COMMANDS][32 + 1];

hook OnScriptInit() {
    #if defined _INC_y_commands
        for (new i = 0; i != MAX_COMMANDS; i ++) {
            if (Command_IsValid(i)) {
                strcat(g_CommandNames[i], Command_GetName(i));
                g_RegisteredCommands ++;
            }
        }
    #else
        new 
            hdr[AMX_HDR];

        GetAmxHeader(hdr);

        for (new i = 0, j = GetNumPublics(hdr); i < j; i ++)
        {
            new tmp_name[32 + 1];
            GetPublicNameFromIndex(i, tmp_name);
            
            if (!strfind(tmp_name, "cmd_", false)) {
                if (i < MAX_COMMANDS) {
                    format(g_CommandNames[i], 32, tmp_name[4]);

                    Debug("%s", g_CommandNames[i]);
                    Debug("%d", g_RegisteredCommands);
                    g_RegisteredCommands ++;
                }
            }
        }
    #endif
    Debug("Loaded %d Commands", g_RegisteredCommands);
}

static stock __getDistance(const a[], const b[]) {
    new 
        a_len = strlen(a),
        b_len = strlen(b),
        cache[256],
        a_idx,
        b_idx,
        a_dist,
        b_dist,
        result,
        code
    ;

    if (!strcmp(a, b)) return 0;
    if (a_len == 0) return b_len;
    if (b_len == 0) return a_len;

    while(a_idx < a_len) {

        cache[a_idx] = a_idx + 1;
        a_idx ++;
    }

    while(b_idx < b_len) {
		code = b[b_idx];
		result = a_dist = b_idx++;
		a_idx = -1;

		while (++a_idx < a_len) {
			b_dist = code == a[a_idx] ? a_dist : a_dist + 1;
			a_dist = cache[a_idx];

			cache[a_idx] = result = a_dist > result
			? b_dist > result
				? result + 1
				: b_dist
			: b_dist > a_dist
				? a_dist + 1
				: b_dist;
        }
    } 
    return result;
}

stock Command_Guess(dest[], const cmdtext[], len = sizeof dest) {
    new 
        dist,
        min_dist = 0x7FFFFFFF, 
        min_idx = -1
    ;
    
    // WARNING: Please don't edit ANYTHING on this code
    // OR else it will cause chaos in your code
    for (new i = 0; i <= g_RegisteredCommands + 1; i ++) {
        Debug("Start looping at index %d", i);

        if (g_CommandNames[i][0] != EOS) {
            dist = __getDistance(cmdtext[1], g_CommandNames[i]);

            Debug("Get some distance and checking if %s is closests to %s",cmdtext[1], g_CommandNames[i]);

            if (dist < min_dist) {
                min_dist = dist;
                min_idx = i;

                Debug("Found it!\n%d, %d, %d", dist, min_dist, min_idx);
                Debug("%s", g_CommandNames[i]);
            }
        }
    }
    Debug("Showing results:\n%s, %s, %d", g_CommandNames[min_idx], cmdtext, min_idx);
   
    if (('A' <= cmdtext[0] <= 'Z') || ('a' <= cmdtext[0] <= 'z') || ('0' <= cmdtext[0] <= '9')) {
        format(dest, len, g_CommandNames[min_idx]);
    }
    else {
        format(dest, len, "%c%s", cmdtext[0], g_CommandNames[min_idx]);
    }
    return 1;
}
