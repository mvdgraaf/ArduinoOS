#ifndef ARDUINOOS_COMMANDS_H
#define ARDUINOOS_COMMANDS_H

#include "cli.h"

extern commandType commands[];
extern int numCommands;

void helpCommand(char *args);
void printCommand(char *args);
void filesCommand(char *args);

#endif //ARDUINOOS_COMMANDS_H
