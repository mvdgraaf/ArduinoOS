#include <Arduino.h>

#define CMD_NAME_SIZE 12
#define INPUT_BUF_SIZE 64

typedef struct {
    char name[CMD_NAME_SIZE];
    const char *description;
    void (*func)(char*);
} commandType;

void printCommand(char *args) {
    if (args != nullptr) {
        Serial.println(args);
    } else {
        Serial.println("print: No arguments provided");
    }
}

void helpCommand(char *args);  // forward declaration

commandType commands[] = {
    {"print", "Print a message to the console", printCommand},
    {"help", "Show this help message", helpCommand}
};

int numCommands = sizeof(commands) / sizeof(commandType);

void helpCommand(char *args) {
    for (int i = 0; i < numCommands; i++) {
        Serial.print(commands[i].name);
        Serial.print(" - ");
        Serial.println(commands[i].description);
    }
}

char inputBuffer[INPUT_BUF_SIZE];
int inputBufferIndex = 0;

void parseInput(char *input) {
    char *token = strtok(input, " ");
    if (token != nullptr) {
        char *args = strtok(nullptr, "");
        Serial.print("ArduinoOS > ");
        Serial.print(token);
        Serial.print(" ");
        Serial.println(args);
        for (int i = 0; i < numCommands; i++) {
            if (strcmp(commands[i].name, token) == 0) {
                commands[i].func(args);
                Serial.print("\nArduinoOS > ");
                return;
            }
        }
        Serial.println("Unknown command");
        Serial.print("ArduinoOS > ");
    }
}

void setup() {
    Serial.begin(9600);
    Serial.println("--- Arduino OS ---");
    Serial.println("Type 'help' for a list of commands");
    Serial.println("---");
    Serial.println("ArduinoOS > ");
}

void loop() {
    if (Serial.available()) {
        char c = Serial.read();
        if (c == '\n' || c == '\r') {
            if (inputBufferIndex > 0) {
                inputBuffer[inputBufferIndex] = '\0';
                parseInput(inputBuffer);
                inputBufferIndex = 0;
            }
        } else if (inputBufferIndex < INPUT_BUF_SIZE - 1) {
            inputBuffer[inputBufferIndex++] = c;
        }
    }
}