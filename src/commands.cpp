#include "../include/commands.h"
#include "../include/FAT.h"

void helpCommand(char *args) {
    if (args == nullptr) {
        for (int i = 0; i < numCommands; i++) {
            Serial.print(commands[i].name);
            Serial.print(" - ");
            Serial.println(commands[i].description);
        }
    } else {
        for (int i = 0; i < numCommands; i++) {
            if (strcmp(commands[i].name, args) == 0) {
                Serial.print(commands[i].name);
                Serial.print(" - ");
                Serial.println(commands[i].description);
                return;
            }
        }
    }
}

void printCommand(char *args) {
    if (args != nullptr) {
        Serial.println(args);
    } else {
        Serial.println(F("print: No arguments provided"));
    }
}


void filesCommand(char *args) {
    if (noOfFiles == 0) {
        Serial.println(F("No files in the filesystem"));
    } else {
        printFileList();
    }
}

void freeSpaceCommand(char *args) {
    int freeSpace = getFreeSpace();
    Serial.print(F("Free space: "));
    Serial.print(freeSpace);
    Serial.println(F(" bytes"));
}

void writeFileCommand(char *args) {
    if (args == nullptr) {
        Serial.println(F("Usage: write <filename> <data>"));
        return;
    }

    char *filename = strtok(args, " ");
    char *data     = strtok(nullptr, "");

    if (filename == nullptr || data == nullptr) {
        Serial.println(F("Usage: write <filename> <data>"));
        return;
    }

    if (strlen(filename) > 11) {
        Serial.println(F("Filename too long (max 11 chars)"));
        return;
    }

    bool success = writeFile(filename, data, strlen(data) + 1);
    if (success) {
        Serial.print(F("Written "));
        Serial.print(strlen(data) + 1);
        Serial.print(F(" bytes to '"));
        Serial.print(filename);
        Serial.println(F("'"));
    }
}

void readFileCommand(char *args) {
    if (args == nullptr) {
        Serial.println(F("Usage: read  1234567890"));
        return;
    }
    readFile(args);
}
