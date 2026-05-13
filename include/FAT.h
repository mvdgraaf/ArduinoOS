//
// Created by merij on 13-5-2026.
//

#ifndef ARDUINOOS_FAT_H
#define ARDUINOOS_FAT_H

#include <Arduino.h>
#include <EEPROM.h>

struct FATEntry {
    char filename[12];
    uint32_t fileSize;
    uint32_t startPos;
};

constexpr int MAX_FILES = 10;
constexpr int FAT_START_ADDR = 0;
constexpr int NO_OF_FILES_ADDR = 160;
constexpr int DATA_START_ADDR = 161;

void initFileSystem();
int findFileIndex(const char* name);
void readFATEntry(int entryIndex, FATEntry &entry);
void writeFATEntry(int entryIndex, const FATEntry &entry);
void printFileList();
int getFreeSpace();

extern EERef noOfFiles;

#endif //ARDUINOOS_FAT_H
