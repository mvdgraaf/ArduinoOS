#include "cli.h"

CLI::CLI(commandType *commands, int numCommands) {
    _commands = commands;
    _numCommands = numCommands;
    _inputBufferIndex = 0;
}

void CLI::loop() {
    if (Serial.available()) {
        char c = Serial.read();
        if (c == '\n' || c == '\r') {
            if (_inputBufferIndex > 0) {
                _inputBuffer[_inputBufferIndex] = '\0';
                parseInput(_inputBuffer);
                _inputBufferIndex = 0;
            }
        } else if (_inputBufferIndex < INPUT_BUF_SIZE - 1) {
            _inputBuffer[_inputBufferIndex++] = c;
        }
    }
}

void CLI::parseInput(char *input) {
    char *token = strtok(input, " ");
    if (token != nullptr) {
        char *args = strtok(nullptr, "");
        Serial.print("ArduinoOS > ");
        Serial.print(token);
        Serial.print(" ");
        Serial.println(args);
        for (int i = 0; i < _numCommands; i++) {
            if (strcmp(_commands[i].name, token) == 0) {
                _commands[i].func(args);
                Serial.print("\nArduinoOS > ");
                return;
            }
        }
        Serial.println("Unknown command");
        Serial.print("ArduinoOS > ");
    }
}