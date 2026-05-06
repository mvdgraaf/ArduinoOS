#ifndef UNTITLED_CLI_H
#define UNTITLED_CLI_H

#include <Arduino.h>

#define CMD_NAME_SIZE 12
#define INPUT_BUF_SIZE 64

typedef struct {
    char name[CMD_NAME_SIZE];
    const char *description;
    void (*func)(char*);
} commandType;

class CLI {
public:
    CLI(commandType *commands, int numCommands);
    void loop();
    void parseInput(char *input);
private:
    commandType *_commands;
    int _numCommands;
    char _inputBuffer[INPUT_BUF_SIZE];
    int _inputBufferIndex;
};

#endif //UNTITLED_CLI_H
