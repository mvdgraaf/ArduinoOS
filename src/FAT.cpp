#include "../include/FAT.h"

EERef noOfFiles = EEPROM[NO_OF_FILES_ADDR];

void initFileSystem() {
    if (noOfFiles == 255) {
        noOfFiles = 0;
    }
}

void readDirectory(int entryIndex, FATEntry &entry) {
    if (entryIndex < 0 || entryIndex >= MAX_FILES) {
        Serial.println("Invalid FAT entry index");
        return;
    }
    const int address = FAT_START_ADDR + (entryIndex * sizeof(FATEntry));
    EEPROM.get(address, entry);
}

void writeFATEntry(int entryIndex, const FATEntry &entry) {
    if (entryIndex < 0 || entryIndex >= MAX_FILES) {
        Serial.println("Invalid FAT entry index");
        return;
    }
    const int address = FAT_START_ADDR + (entryIndex * sizeof(FATEntry));
    EEPROM.put(address, entry);
}

void printFileList() {
    for (int i = 0; i < noOfFiles; i++) {
        FATEntry tempEntry;
        readDirectory(i, tempEntry);
        Serial.print(tempEntry.filename);
        Serial.print(F("\t\t"));
        Serial.print(tempEntry.fileSize);
        Serial.print(F("\t"));
        Serial.print(tempEntry.startPos);
    }
}


