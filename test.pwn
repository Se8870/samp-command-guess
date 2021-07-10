#include <a_samp>

#include "izcmd.inc"
#include "command-guess.inc"

main() 
{
	new 
		guessedCmd[32];

	print("Testing...");

	Command_Guess(guessedCmd, "/hlpe", sizeof(guessedCmd));
	printf("Result: %s", guessedCmd);

	Command_Guess(guessedCmd, "/dd", sizeof(guessedCmd));
	printf("Result: %s", guessedCmd);

	Command_Guess(guessedCmd, "/cccs", sizeof(guessedCmd));
	printf("Result: %s", guessedCmd);

	Command_Guess(guessedCmd, "/cm", sizeof(guessedCmd));
	printf("Result: %s", guessedCmd);

	Command_Guess(guessedCmd, "/cmmd", sizeof(guessedCmd));
	printf("Result: %s", guessedCmd);
}

// Testing cmd
CMD:help(playerid, cmdtext[]) return 1;
CMD:cmds(playerid, cmdtext[]) return 1;
CMD:cmd(playerid, cmdtext[]) return 1;
CMD:cd(playerid, cmdtext[])	return 1;
