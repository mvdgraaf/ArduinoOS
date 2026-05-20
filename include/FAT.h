//
// Created by merij on 13-5-2026.
//

#ifndef ARDUINOOS_FAT_H
#define ARDUINOOS_FAT_H

#include <Arduino.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <EEPROM.h>
#pragma GCC diagnostic pop

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
bool writeFile(const char* filename, const char* data, uint32_t size);
bool readFile(const char* filename);
void deleteFile(const char* filename);
int findFreeBlock(uint32_t size);
int getFreeSpace();

extern EERef noOfFiles;

#endif //ARDUINOOS_FAT_H
