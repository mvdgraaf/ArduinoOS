#include <Arduino.h>
#include "cli.h"
#include <commands.h>

#include "FAT.h"

commandType commands[] = {
    {"print", "Print a message to the console", printCommand},
    {"help", "Show this help message", helpCommand},
    {"files", "Show alsl files", filesCommand},
    { "freespace", "Shows free space", freeSpaceCommand },
    { "write", "Writes a file to the filesystem. Usage: write <filename> <data>", writeFileCommand },
    { "read", "Reads a file from the filesystem. Usage: read <filename>", readFileCommand }
};

int numCommands = sizeof(commands) / sizeof(commandType);

CLI shell(commands, numCommands);

void setup() {
    initFileSystem();
    Serial.begin(9600);
    Serial.println(F("--- Arduino OS ---"));
    Serial.println(F("Type 'help' for a list of commands"));
    Serial.println(F("---"));
    Serial.print(F("ArduinoOS > "));
}

void loop() {
    shell.loop();
}
