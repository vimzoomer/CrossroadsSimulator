#ifndef CROSSROADS_LIGHTS_H
#define CROSSROADS_LIGHTS_H

#include <stdbool.h>
#include "queue.h"

#define BASE_GREEN_TIME 2
#define VEHICLE_INCREMENT_TIME 1

enum LightColor { RED, GREEN, YELLOW };

typedef struct {
    Queue* NQueue;
    Queue* SQueue;
    Queue* WQueue;
    Queue* EQueue;
    enum LightColor NSLight;
    enum LightColor WELight;
    int NSGreenTimeLeft;
    int WEGreenTimeLeft;
} Lights;

Lights createLights();
void adjustLightTimes(Lights* lights);
void switchState(Lights* lights);
void getLeftVehicles(Lights* lights, VehiclePair* vehicles);
void timeStep(Lights* lights);
bool handleLightChange(Lights* lights, enum LightColor light, int* greenTimeLeft);
void deleteLights(Lights* lights);

#endif
