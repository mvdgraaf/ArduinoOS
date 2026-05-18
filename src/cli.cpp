#include "../include/cli.h"

CLI::CLI(commandType *commands, int numCommands) {
    _commands = commands;
    _numCommands = numCommands;
    _inputBufferIndex = 0;
}

void CLI::loop() {
    while (Serial.available()) {
        char c = Serial.read();
        if (c == '\n' || c == '\r') {
            Serial.println();
            if (_inputBufferIndex > 0) {
                _inputBuffer[_inputBufferIndex] = '\0';
                parseInput(_inputBuffer);
                _inputBufferIndex = 0;
            }
            while (Serial.available()) {
                int p = Serial.peek();
                if (p == '\n' || p == '\r') {
                    Serial.read();
                } else {
                    break;
                }
            }
            Serial.print(F("ArduinoOS > "));
        }
        else if (_inputBufferIndex < INPUT_BUF_SIZE - 1) {
            _inputBuffer[_inputBufferIndex++] = c;
            Serial.write(c);
        }
    }
}

void CLI::parseInput(char *input) {
    char *args = nullptr;
    char *space = strchr(input, ' ');
    if (space != nullptr) {
        *space = '\0';
        args = space + 1;
        if (*args == '\0') {
            args = nullptr;
        }
    }
    for (int i = 0; i < _numCommands; i++) {
        if (strcmp(_commands[i].name, input) == 0) {
            _commands[i].func(args);
            return;
        }
    }
    Serial.println(F("Unknown command"));
}
