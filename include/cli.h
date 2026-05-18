#ifndef UNTITLED_CLI_H
#define UNTITLED_CLI_H

#include <Arduino.h>

#define CMD_NAME_SIZE 12
#define INPUT_BUF_SIZE 32

/**
 * @brief Structure representing a command in the CLI.
 *
 * Each command has a name (up to CMD_NAME_SIZE characters), a description, and a function pointer that points to the function that implements the command's behavior. The function takes a single argument, which is a string containing any additional arguments passed to the command.
 */
typedef struct {
    const char *name;
    const char *description;
    void (*func)(char*);
} commandType;

/**
 * A simple command-line interface for Arduino. It reads input from the serial port, parses it, and executes registered commands. Commands are defined as an array of `commandType` structs, which include the command name, a description, and a function pointer to the command's implementation.
 */
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
