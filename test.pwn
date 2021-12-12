#include <a_samp>
#include <izcmd>

#include "command-guess.inc"

main() 
{
	new 
	    guessedCmd[32], ret;

	print("Testing...");

	ret = Command_Guess(guessedCmd, "/hlpe", sizeof(guessedCmd));
	printf("Result: %s | Ret: %d", guessedCmd, ret);

	ret = Command_Guess(guessedCmd, "/dd", sizeof(guessedCmd));
	printf("Result: %s | Ret: %d", guessedCmd, ret);

	ret = Command_Guess(guessedCmd, "/cixa", sizeof(guessedCmd));
	printf("Result: %s | Ret: %d", guessedCmd, ret);

	ret = Command_Guess(guessedCmd, "/cm", sizeof(guessedCmd));
	printf("Result: %s | Ret: %d", guessedCmd, ret);

	ret = Command_Guess(guessedCmd, "/cmmd", sizeof(guessedCmd));
	printf("Result: %s | Ret: %d", guessedCmd, ret);
}

// Testing cmd
CMD:help(playerid, cmdtext[]) return 1;
CMD:cmds(playerid, cmdtext[]) return 1;
CMD:cmd(playerid, cmdtext[]) return 1;
CMD:cd(playerid, cmdtext[]) return 1;
CMD:cc(playerid, cmdtext[]) return 1;
CMD:cica(playerid, cmdtext[]) return 1;
CMD:chalice(playerid, cmdtext[]) return 1;
