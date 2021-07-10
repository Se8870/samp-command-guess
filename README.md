# SA:MP Command Guess

[![sampctl](https://img.shields.io/badge/sampctl-command--guess-2f2f2f.svg?style=for-the-badge)](https://github.com/Kirima2nd/samp-command-guess)

It's just simple command guesser for SA-MP using Levenshtein Distance function.

It will work with most of command processor (including y_commands and also discord command)

## Installation

Simply install to your project:

```bash
sampctl package install Kirima2nd/samp-command-guess
```

Include in your code and begin using the library:

```pawn
#include <command-guess>
```

## Function Lists

```pawn
Command_Guess(output[], const cmdtext[], len = sizeof dest);
```

## Usage

### With Y_CMD
```pawn
#include <a_samp>
#include <YSI_Visual\y_commands>
#include <command-guess>

main() 
{
    print("Script loaded");
}

public e_COMMAND_ERRORS:OnPlayerCommandReceived(playerid, cmdtext[], e_COMMAND_ERRORS:success) 
{
	if (success == COMMAND_UNDEFINED) 
	{
		new 
			guessCmd[32];
		
		Command_Guess(guessCmd, cmdtext);

		SendClientMessageEx(playerid, -1, "{FF0000}ERROR:{FFFFFF} \"%s\" is not found, did you mean \"%s\"?", cmdtext, guessCmd);
		return COMMAND_OK;
	}
	return COMMAND_OK;
}
```

### With most command processor (In this example, i'll be using izcmd instead)
```pawn
#include <a_samp>
#include <izcmd>
#include <command-guess>

main() 
{
    print("Script loaded");
}
public OnPlayerCommandPerformed(playerid, cmdtext[], success) 
{
	if (!success) 
	{
		new 
			guessCmd[32];
		
		Command_Guess(guessCmd, cmdtext);

		SendClientMessageEx(playerid, -1, "{FF0000}ERROR:{FFFFFF} \"%s\" is not found, did you mean \"%s\"?", cmdtext, guessCmd);
		return 1;
	}
	return 1;
}
```

## Testing

To test, simply run the following commands:

```bash
sampctl package run
```
