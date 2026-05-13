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
        Serial.println("print: No arguments provided");
    }
}

void storeCommand(char *args) {

}

void RetrievalCommand(char *args) {

}

void eraseCommand(char *args) {

}

void filesCommand(char *args) {
    if (noOfFiles == 0) {
        Serial.println("No files in the filesystem");
    } else {
        printFileList();
    }
}

void runCommand(char *args) {

}
