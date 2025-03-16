#include <stdio.h>
#include <stdbool.h>
#include "lights.h"

Lights createLights(void) {
    Lights lights;
    lights.NQueue = createQueue();
    lights.SQueue = createQueue();
    lights.EQueue = createQueue();
    lights.WQueue = createQueue();
    lights.NSGreenTimeLeft = BASE_GREEN_TIME;
    lights.WEGreenTimeLeft = BASE_GREEN_TIME;
    lights.NSLight = GREEN;
    lights.WELight = RED;

    return lights;
}

void switchState(Lights* lights) {
    switch (lights->NSLight) {
        case GREEN:
            lights->NSLight = YELLOW;
            break;
        case YELLOW:
            lights->NSLight = RED;
            lights->WELight = GREEN;
            break;
        case RED:
            if (lights->WELight == GREEN) {
                lights->WELight = YELLOW;
            } else {
                lights->NSLight = GREEN;
                lights->WELight = RED;
            }
    }

    if ((lights->NSGreenTimeLeft == 0) && (lights->WEGreenTimeLeft == 0)) {
        adjustLightTimes(lights);
    }
}

void adjustLightTimes(Lights* lights) {
    int NSVehicleCount = lights->NQueue->length + lights->SQueue->length;
    int WEVehicleCount = lights->WQueue->length + lights->EQueue->length;

    lights->NSGreenTimeLeft = BASE_GREEN_TIME + (NSVehicleCount * VEHICLE_INCREMENT_TIME);
    lights->WEGreenTimeLeft = BASE_GREEN_TIME + (WEVehicleCount * VEHICLE_INCREMENT_TIME);
}

bool handleLightChange(Lights* lights, enum LightColor light, int* greenTimeLeft) {
    if (light == GREEN) {
        (*greenTimeLeft) -= 1;
        if (*greenTimeLeft == 0) {
            switchState(lights);
        }
        return true;
    } else if (light == YELLOW) {
        switchState(lights);
        return true;
    }
    return false;
}

void timeStep(Lights* lights) {
    if (!handleLightChange(lights, lights->NSLight, &lights->NSGreenTimeLeft)) {
        handleLightChange(lights, lights->WELight, &lights->WEGreenTimeLeft);
    }
}

//for math-like modulo operator
int modulo(int a, int b) {
    int r = a % b;
    if (r < 0) {
        r += (b > 0) ? b : -b;
    }
    return r;
}

bool leftTurnConflict(Vehicle* vehicle1, Vehicle* vehicle2) {
    if ((modulo((int)vehicle1->startRoad - 1, 4) == (int)vehicle1->endRoad) &&
       ((modulo((int)vehicle2->startRoad + 2, 4) == (int)vehicle2->endRoad) ||
       (vehicle1->endRoad == vehicle2->endRoad)))
        return true;

    return false;
}

void handleDirection(Queue* firstQueue, Queue* secondQueue, VehiclePair* vehicles) {
    Vehicle * firstVehicle = isEmpty(firstQueue) ? NULL : peek(firstQueue);
    Vehicle * secondVehicle = isEmpty(secondQueue) ? NULL : peek(secondQueue);

    if (firstVehicle && (!secondVehicle || !leftTurnConflict(firstVehicle, secondVehicle))) {
        addToVehiclePair(vehicles, dequeue(firstQueue));
    }
    if (secondVehicle && (!firstVehicle || !leftTurnConflict(secondVehicle, firstVehicle))) {
        addToVehiclePair(vehicles, dequeue(secondQueue));
    }
}

void getLeftVehicles(Lights* lights, VehiclePair* vehicles) {
    if (lights->NSLight == GREEN) {
        handleDirection(lights->NQueue, lights->SQueue, vehicles);
    }

    if (lights->WELight == GREEN) {
        handleDirection(lights->WQueue, lights->EQueue, vehicles);
    }
}

void deleteLights(Lights* lights) {
    if (lights != NULL) {
        if (lights->NQueue != NULL) {
            deleteQueue(lights->NQueue);
        }
        if (lights->SQueue != NULL) {
            deleteQueue(lights->SQueue);
        }
        if (lights->WQueue != NULL) {
            deleteQueue(lights->WQueue);
        }
        if (lights->EQueue != NULL) {
            deleteQueue(lights->EQueue);
        }
    }
}

