#include <assert.h>
#include <stdio.h>
#include "lights.h"

void testLightInitialization(void) {
    Lights lights = createLights();
    assert(lights.NSLight == GREEN);
    assert(lights.WELight == RED);
    assert(lights.NSGreenTimeLeft == BASE_GREEN_TIME);
    assert(lights.WEGreenTimeLeft == BASE_GREEN_TIME);
    assert(isEmpty(lights.NQueue));
    assert(isEmpty(lights.SQueue));
    assert(isEmpty(lights.WQueue));
    assert(isEmpty(lights.EQueue));

    deleteLights(&lights);
}

void testLightSwitch(void) {
    Lights lights = createLights();

    switchState(&lights);
    assert(lights.NSLight == YELLOW);
    switchState(&lights);
    assert(lights.NSLight == RED);
    assert(lights.WELight == GREEN);
    switchState(&lights);
    assert(lights.WELight == YELLOW);
    switchState(&lights);
    assert(lights.NSLight == GREEN);
    assert(lights.WELight == RED);

    deleteLights(&lights);
}

void testVehicleMovement(void) {
    Lights lights = createLights();

    Vehicle vehicle1 = createVehicle("v1", "north", "south");
    Vehicle vehicle2 = createVehicle("v2", "south", "north");
    enqueue(lights.NQueue, &vehicle1);
    enqueue(lights.SQueue, &vehicle2);

    VehiclePair pair = createVehiclePair();

    getLeftVehicles(&lights, &pair);

    assert(pair.numVehicles == 2);
    assert(pair.vehicle0 == &vehicle1);
    assert(pair.vehicle1 == &vehicle2);

    deleteLights(&lights);
}

void testLeftTurnConflict(void) {
    Lights lights = createLights();

    Vehicle vehicle1 = createVehicle("v1", "south", "west");
    Vehicle vehicle2 = createVehicle("v2", "north", "south");
    enqueue(lights.NQueue, &vehicle1);
    enqueue(lights.SQueue, &vehicle2);

    VehiclePair pair = createVehiclePair();
    getLeftVehicles(&lights, &pair);

    assert(pair.numVehicles == 1);
    assert(pair.vehicle0 == &vehicle2);

    deleteLights(&lights);
}


void testGreenTimeAdjustment(void) {
    Lights lights = createLights();

    Vehicle vehicle1 = createVehicle("v1", "north", "south");
    Vehicle vehicle2 = createVehicle("v2", "north", "south");
    enqueue(lights.NQueue, &vehicle1);
    enqueue(lights.NQueue, &vehicle2);

    adjustLightTimes(&lights);

    assert(lights.NSGreenTimeLeft == BASE_GREEN_TIME + 2 * VEHICLE_INCREMENT_TIME);

    deleteLights(&lights);
}

int main(void) {
    testLightInitialization();
    testLightSwitch();
    testVehicleMovement();
    testLeftTurnConflict();
    testGreenTimeAdjustment();

    printf("All tests passed successfully!\n");
    return 0;
}

