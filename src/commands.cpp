//
// Created by merij on 6-5-2026.
//

#include "../include/commands.h"

void helpCommand(char *args) {
    for (int i = 0; i < numCommands; i++) {
        Serial.print(commands[i].name);
        Serial.print(" - ");
        Serial.println(commands[i].description);
    }
}

void printCommand(char *args) {
    if (args != nullptr) {
        Serial.println(args);
    } else {
        Serial.println("print: No arguments provided");
    }
}