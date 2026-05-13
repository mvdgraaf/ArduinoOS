#include <Arduino.h>
#include "cli.h"
#include <commands.h>

#include "FAT.h"

commandType commands[] = {
    {"print", "Print a message to the console", printCommand},
    {"help", "Show this help message", helpCommand},
    {"files", "Shows all files", filesCommand}
};

int numCommands = sizeof(commands) / sizeof(commandType);

CLI shell(commands, numCommands);

void setup() {
    initFileSystem();
    Serial.begin(9600);
    Serial.println("--- Arduino OS ---");
    Serial.println("Type 'help' for a list of commands");
    Serial.println("---");
    Serial.print("ArduinoOS > ");
}

void loop() {
    shell.loop();
}
