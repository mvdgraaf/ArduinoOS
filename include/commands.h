//
// Created by merij on 6-5-2026.
//

#ifndef ARDUINOOS_COMMANDS_H
#define ARDUINOOS_COMMANDS_H

#include <Arduino.h>
#include "cli.h"

extern commandType commands[];
extern int numCommands;

void helpCommand(char *args);
void printCommand(char *args);

#endif //ARDUINOOS_COMMANDS_H
