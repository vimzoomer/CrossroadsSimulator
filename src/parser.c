#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"


Command parseCommand(cJSON* command) {
    cJSON* type = cJSON_GetObjectItem(command, "type");
    Command cmd;

    if (strcmp(type->valuestring, "addVehicle") == 0) {
        cJSON* vehicleId = cJSON_GetObjectItem(command, "vehicleId");
        cJSON* startRoad = cJSON_GetObjectItem(command, "startRoad");
        cJSON* endRoad = cJSON_GetObjectItem(command, "endRoad");

        cmd.type = addVehicle;
        cmd.vehicle = createVehicle(vehicleId->valuestring, startRoad->valuestring, endRoad->valuestring);
    }
    else if (strcmp(type->valuestring, "step") == 0) {
        cmd.type = step;
    } else {
        cmd.type = invalidCommand;
        printf("Wrong command\n");
    }
    return cmd;
}

Command* parseJSONFromFile(const char* filename, int* commandCount) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char* jsonString = (char*)malloc(fileSize + 1);
    if (!jsonString) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    fread(jsonString, 1, fileSize, file);
    jsonString[fileSize] = '\0';

    fclose(file);

    cJSON* root = cJSON_Parse(jsonString);
    free(jsonString);

    if (!root) {
        printf("Error parsing JSON\n");
        return NULL;
    }

    cJSON* commands = cJSON_GetObjectItem(root, "commands");
    if (!cJSON_IsArray(commands)) {
        printf("Invalid JSON format\n");
        cJSON_Delete(root);
        return NULL;
    }

    Command* commandArray = (Command*)malloc(MAX_COMMANDS * sizeof(Command));
    if (commandArray == NULL) {
        printf("commandArray allocation failed.\n");
        return NULL;
    }
    int count = 0;

    cJSON* command = NULL;
    cJSON_ArrayForEach(command, commands) {
        if (count >= MAX_COMMANDS) {
            printf("Command limit exceeded\n");
            break;
        }
        commandArray[count++] = parseCommand(command);
    }

    cJSON_Delete(root);
    *commandCount = count;

    return commandArray;
}

void saveToJSONFile(const char* filename, VehiclePair* stepStatuses, int numSteps) {
    cJSON *root = cJSON_CreateObject();
    cJSON *stepsArray = cJSON_CreateArray();

    for (int i = 0; i < numSteps; i++) {
        cJSON *stepObj = cJSON_CreateObject();
        cJSON *leftVehiclesArray = cJSON_CreateArray();

        for (int j = 0; j < stepStatuses[i].numVehicles; j++) {
            cJSON_AddItemToArray(leftVehiclesArray, cJSON_CreateString(vehiclePairGet(&stepStatuses[i], j)->vehicleId));
        }

        cJSON_AddItemToObject(stepObj, "leftVehicles", leftVehiclesArray);
        cJSON_AddItemToArray(stepsArray, stepObj);
    }

    cJSON_AddItemToObject(root, "stepStatuses", stepsArray);

    FILE *file = fopen(filename, "w");
    if (file) {
        char *jsonStr = cJSON_Print(root);
        fprintf(file, "%s", jsonStr);
        fclose(file);
        free(jsonStr);
    } else {
        printf("Failed to open file for writing\n");
    }

    cJSON_Delete(root);
}



