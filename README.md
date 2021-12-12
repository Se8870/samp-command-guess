# SA:MP Command Guess

[![sampctl](https://img.shields.io/badge/sampctl-command--guess-2f2f2f.svg?style=for-the-badge)](https://github.com/Kirima2nd/samp-command-guess)

Just simple command guesser for SA-MP using Levenshtein Distance function.

Will working with most of command processor (including y_commands and also discord command)

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
    
    Command_SetDeniedReturn(true);
}

public e_COMMAND_ERRORS:OnPlayerCommandReceived(playerid, cmdtext[], e_COMMAND_ERRORS:success) 
{
    if (success == COMMAND_UNDEFINED) 
    {
        new 
            guessCmd[32], 
            dist = Command_Guess(guessCmd, cmdtext);
  
        if (dist < 3)
        {
            SendClientMessageEx(playerid, -1, "{FF0000}ERROR:{FFFFFF} \"%s\" is not found, did you mean \"%s\"?", cmdtext, guessCmd);
        }
        else
        {
            SendClientMessageEx(playerid, -1, "{FF0000}ERROR:{FFFFFF} \"%s\" is not found", cmdtext);
        }
        return COMMAND_SILENT;
    }
    return COMMAND_OK;
}
```

### With most command processor (I-ZCMD Example)
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
            guessCmd[32],
            dist = Command_Guess(guessCmd, cmdtext);

        if (dist < 3)
        {
            SendClientMessageEx(playerid, -1, "{FF0000}ERROR:{FFFFFF} \"%s\" is not found, did you mean \"%s\"?", cmdtext, guessCmd);
        }
        else
        {
            SendClientMessageEx(playerid, -1, "{FF0000}ERROR:{FFFFFF} \"%s\" is not found", cmdtext);
        }
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
