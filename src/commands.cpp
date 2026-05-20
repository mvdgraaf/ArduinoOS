#include "../include/commands.h"
#include "../include/FAT.h"
#include <avr/wdt.h>

void helpCommand(char *args) {
    if (args == nullptr) {
        for (int i = 0; i < numCommands; i++) {
            Serial.print(reinterpret_cast<const __FlashStringHelper*>(commands[i].name));
            Serial.print(F(" - "));
            Serial.println(reinterpret_cast<const __FlashStringHelper*>(commands[i].description));
        }
    } else {
        for (int i = 0; i < numCommands; i++) {
            if (strcmp_P(args, commands[i].name) == 0) {
                Serial.print(reinterpret_cast<const __FlashStringHelper*>(commands[i].name));
                Serial.print(F(" - "));
                Serial.println(reinterpret_cast<const __FlashStringHelper*>(commands[i].description));
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

void reboot(char *args) {
    Serial.println(F("Rebooting..."));
    cli();
    wdt_enable(WDTO_15MS);
    while (1);
}

void filesCommand(char *args) {
    if (static_cast<int>(noOfFiles) == 0) {
        Serial.println(F("No files in the filesystem"));
    } else {
        printFileList();
    }
}

void freeSpaceCommand(char *args) {
    const int freeSpace = getFreeSpace();
    Serial.print(F("Free space: "));
    Serial.print(freeSpace);
    Serial.println(F(" bytes"));
}

void writeFileCommand(char *args) {
    if (args == nullptr) {
        Serial.println(F("Usage: write <filename> <data>"));
        return;
    }

    const char *filename = strtok(args, " ");
    const char *data     = strtok(nullptr, "");

    if (filename == nullptr || data == nullptr) {
        Serial.println(F("Usage: write <filename> <data>"));
        return;
    }

    if (strlen(filename) > 11) {
        Serial.println(F("Filename too long (max 11 chars)"));
        return;
    }

    const auto size = strlen(data) + 1;
    bool success = writeFile(filename, data, size);
    if (success) {
        Serial.print(F("Written "));
        Serial.print(size);
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

void deleteFileCommand(char *args) {
    if (args == nullptr) {
        Serial.println(F("Usage: delete 1234567890"));
        return;
    }
    deleteFile(args);
}
