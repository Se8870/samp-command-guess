# SA:MP Command Guess

[![sampctl](https://img.shields.io/badge/sampctl-command--guess-2f2f2f.svg?style=for-the-badge)](https://github.com/Kirima2nd/samp-command-guess)

It's just simple command guesser for SA-MP using Levenshtein Distance function
and with tricks too!

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
Command_Guess(dest[], const cmdtext[], len = sizeof dest);
```

## Usage

### With Y_CMD
```pawn
#include <a_samp>
#include <YSI_Visual\y_commands>
#include <command-guess>

main() {
    print("Script loaded");
}

public e_COMMAND_ERRORS:OnPlayerCommandReceived(playerid, cmdtext[], e_COMMAND_ERRORS:success) {
	if (success == COMMAND_UNDEFINED) {
		new 
			guessCmd[32];
		
		Command_Guess(guessCmd, cmdtext);

		SendClientMessageEx(playerid, -1, "{FF0000}ERROR:{FFFFFF} \"%s\" is not found, did you mean \"%s\"?", cmdtext, guessCmd);
		return COMMAND_OK;
	}
	return COMMAND_OK;
}
```

### With ZCMD (And other commands that have cmd__ prefixes)
```pawn
#include <a_samp>
#include <command-guess>

main() {
    print("Script loaded");
}
public OnPlayerCommandPerformed(playerid, cmdtext[], success) {
	if (!success) {
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
sampctl package ensure
sampctl package run --forceBuild
```
