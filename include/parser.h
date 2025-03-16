#ifndef CROSSROADS_PARSER_H
#define CROSSROADS_PARSER_H

#include "vehicle.h"
#include <cjson/cJSON.h>

#define MAX_COMMANDS 100

enum TypeOfCommand {
    addVehicle,
    step,
    invalidCommand
};

typedef struct {
    enum TypeOfCommand type;
    Vehicle vehicle;
} Command;

Command* parseJSONFromFile(const char* filename, int* commandCount);
Command parseCommand(cJSON* command);
void saveToJSONFile(const char* filename, VehiclePair* stepStatuses, int numSteps);

#endif //CROSSROADS_PARSER_H
