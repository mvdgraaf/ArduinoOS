#include <Arduino.h>
#include "cli.h"
#include <commands.h>
#include "FAT.h"
#include <avr/wdt.h>

const char cmd_name_print[]  PROGMEM = "print";
const char cmd_desc_print[]  PROGMEM = "Print a message to the console";
const char cmd_name_help[]   PROGMEM = "help";
const char cmd_desc_help[]   PROGMEM = "Show this help message";
const char cmd_name_files[]  PROGMEM = "files";
const char cmd_desc_files[]  PROGMEM = "Show all files";
const char cmd_name_free[]   PROGMEM = "freespace";
const char cmd_desc_free[]   PROGMEM = "Shows free space";
const char cmd_name_write[]  PROGMEM = "write";
const char cmd_desc_write[]  PROGMEM = "Writes a file. Usage: write <filename> <data>";
const char cmd_name_read[]   PROGMEM = "read";
const char cmd_desc_read[]   PROGMEM = "Reads a file. Usage: read <filename>";
const char cmd_name_remove[] PROGMEM = "remove";
const char cmd_desc_remove[] PROGMEM = "Deletes a file. Usage: remove <filename>";
const char cmd_name_reboot[] PROGMEM = "reboot";
const char cmd_desc_reboot[] PROGMEM = "Reboots the device";

commandType commands[] = {
    {cmd_name_print,  cmd_desc_print,  printCommand},
    {cmd_name_help,   cmd_desc_help,   helpCommand},
    {cmd_name_reboot, cmd_desc_reboot, reboot},
    {cmd_name_files,  cmd_desc_files,  filesCommand},
    {cmd_name_free,   cmd_desc_free,   freeSpaceCommand},
    {cmd_name_write,  cmd_desc_write,  writeFileCommand},
    {cmd_name_read,   cmd_desc_read,   readFileCommand},
    {cmd_name_remove, cmd_desc_remove, deleteFileCommand}
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

void wdt_first_action(void) {
    MCUSR = 0;             // Wis alle reset-vlaggen (cruciaal!)
    wdt_disable();         // Zet de timer uit
}

void wdt_first_action(void) __attribute__((naked)) __attribute__((section(".init3")));
