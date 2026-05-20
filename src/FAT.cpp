#include "../include/FAT.h"

EERef noOfFiles = EEPROM[NO_OF_FILES_ADDR];

void initFileSystem() {
    if (noOfFiles == 255) {
        noOfFiles = 0;
    }
}

int findFileIndex(const char *filename) {
    for (int i = 0; i < noOfFiles; i++) {
        FATEntry entry{};
        readFATEntry(i, entry);
        if (strncmp(entry.filename, filename, sizeof(entry.filename)) == 0) {
            return i;
        }
    }
    return -1;
}

void readFATEntry(int entryIndex, FATEntry &entry) {
    if (entryIndex < 0 || entryIndex >= MAX_FILES) {
        Serial.println(F("Invalid FAT entry index"));
        return;
    }
    const int address = FAT_START_ADDR + (entryIndex * sizeof(FATEntry));
    EEPROM.get(address, entry);
}

void writeFATEntry(int entryIndex, const FATEntry &entry) {
    if (entryIndex < 0 || entryIndex >= MAX_FILES) {
        Serial.println(F("Invalid FAT entry index"));
        return;
    }
    const int address = FAT_START_ADDR + (entryIndex * sizeof(FATEntry));
    EEPROM.put(address, entry);
}

bool writeFile(const char* filename, const char* data, uint32_t size) {
    if (static_cast<int>(noOfFiles) >= MAX_FILES) {
        Serial.println(F("Maximum number of files reached"));
        return false;
    }

    int addr = findFreeBlock(size);
    if (addr == -1) {
        Serial.println(F("No free space"));
        return false;
    }

    for (uint32_t i = 0; i < size; i++) {
        EEPROM.update(addr + i, data[i]);
    }

    FATEntry entry{};
    strncpy(entry.filename, filename, sizeof(entry.filename) - 1);
    entry.filename[sizeof(entry.filename) - 1] = '\0';
    entry.fileSize = size;
    entry.startPos = static_cast<uint32_t>(addr);

    writeFATEntry(noOfFiles, entry);
    ++noOfFiles;

    return true;
}

bool readFile(const char *filename) {
    int index = findFileIndex(filename);
    if (index == -1) {
        Serial.println(F("File not found"));
        return false;
    }
    FATEntry entry{};
    readFATEntry(index, entry);

    for (uint32_t i = 0; i < entry.fileSize; i++) {
        char c = EEPROM.read(entry.startPos + i);
        Serial.write(c);
    }
    Serial.println();
    return true;
}

void deleteFile(const char *filename) {
    int index = findFileIndex(filename);
    if (index == -1) {
        Serial.println(F("File not found"));
        return;
    }

    FATEntry entry{};
    readFATEntry(index, entry);
    for (uint32_t i = 0; i < entry.fileSize; i++) {
        EEPROM.update(entry.startPos + i, 0);
    }

    for (int i = index; i < noOfFiles - 1; i++) {
        readFATEntry(i+1, entry);
        writeFATEntry(i, entry);
    }

    --noOfFiles;
}

void printFileList() {
    Serial.println(F("Filename     Size   Start"));
    Serial.println(F("--------     ----   -----"));
    FATEntry tempEntry{};
    for (int i = 0; i < noOfFiles; i++) {
        readFATEntry(i, tempEntry);
        Serial.print(tempEntry.filename);
        uint16_t len = strlen(tempEntry.filename);
        for (uint16_t j = len; j < 13; j++) Serial.print(' ');
        Serial.print(tempEntry.fileSize);
        Serial.print(F("      "));
        Serial.println(tempEntry.startPos);
    }
}

int findFreeBlock(uint32_t size) {
    if ((int)noOfFiles == 0) {
        return DATA_START_ADDR;
    }

    struct Region {
        uint32_t start;
        uint32_t end;
    } regions[MAX_FILES];

    FATEntry entry{};
    for (int i = 0; i < noOfFiles; i++) {
        readFATEntry(i, entry);
        regions[i] = { entry.startPos, entry.startPos + entry.fileSize };
    }

    for (int i = 0; i < noOfFiles - 1; i++) {
        for (int j = 0; j < noOfFiles - 1 - i; j++) {
            if (regions[j].start > regions[j + 1].start) {
                Region temp  = regions[j];
                regions[j]   = regions[j + 1];
                regions[j+1] = temp;
            }
        }
    }

    if (regions[0].start - static_cast<uint32_t>(DATA_START_ADDR) >= size) {
        return DATA_START_ADDR;
    }

    for (int i = 0; i < noOfFiles - 1; i++) {
        uint32_t gapStart = regions[i].end;
        uint32_t gapSize  = regions[i + 1].start - gapStart;
        if (gapSize >= size) {
            return static_cast<int>(gapStart);
        }
    }

    uint32_t afterLast = regions[noOfFiles - 1].end;
    if (static_cast<uint32_t>(EEPROM.length()) - afterLast >= size) {
        return static_cast<int>(afterLast);
    }

    return -1;
}

int getFreeSpace() {
    int marker = DATA_START_ADDR;
    FATEntry tempEntry;
    for (int i = 0; i < noOfFiles; i++) {
        readFATEntry(i, tempEntry);
        int entryEnd = tempEntry.startPos + tempEntry.fileSize;
        if (entryEnd > DATA_START_ADDR) {
            marker = entryEnd;
        }
    }
    return EEPROM.length() - marker;
}

