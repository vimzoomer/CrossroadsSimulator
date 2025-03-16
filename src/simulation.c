#include <stdlib.h>
#include "simulation.h"
#include "parser.h"
#include "lights.h"

void simulate(const char* input_filename, const char* output_filename) {
    int commandCount = 0;
    Command* commands = parseJSONFromFile(input_filename, &commandCount);
    Lights lights = createLights();
    VehiclePair stepStatuses[MAX_COMMANDS];
    int stepCount = 0;

    for (int i = 0; i < commandCount; i++) {
        if (commands[i].type == addVehicle) {
            switch (commands[i].vehicle.startRoad) {
                case N:
                    enqueue(lights.NQueue, &commands[i].vehicle);
                    break;
                case S:
                    enqueue(lights.SQueue, &commands[i].vehicle);
                    break;
                case W:
                    enqueue(lights.WQueue, &commands[i].vehicle);
                    break;
                case E:
                    enqueue(lights.EQueue, &commands[i].vehicle);
                    break;
            }
        } else if (commands[i].type == step) {
            stepStatuses[stepCount++] = createVehiclePair();
            getLeftVehicles(&lights, &stepStatuses[stepCount-1]);
            timeStep(&lights);
        }
    }

    free(commands);
    saveToJSONFile(output_filename, stepStatuses, stepCount);
    deleteLights(&lights);
}
