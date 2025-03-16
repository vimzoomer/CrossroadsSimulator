#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vehicle.h"

Vehicle createVehicle(const char* vehicleId, const char* startRoad, const char* endRoad) {
   Vehicle newVehicle;

    newVehicle.vehicleId = (char*) malloc(strlen(vehicleId) + 1);
    if (newVehicle.vehicleId == NULL) {

    }
    strcpy(newVehicle.vehicleId, vehicleId);

    if (strcmp(startRoad, "south") == 0) {
        newVehicle.startRoad = S;
    } else if (strcmp(startRoad, "north") == 0) {
        newVehicle.startRoad = N;
    } else if (strcmp(startRoad, "east") == 0) {
        newVehicle.startRoad = E;
    } else if (strcmp(startRoad, "west") == 0) {
        newVehicle.startRoad = W;
    } else {
        printf("Invalid direction\n");
    }

    if (strcmp(endRoad, "south") == 0) {
        newVehicle.endRoad = S;
    } else if (strcmp(endRoad, "north") == 0) {
        newVehicle.endRoad = N;
    } else if (strcmp(endRoad, "east") == 0) {
        newVehicle.endRoad = E;
    } else if (strcmp(endRoad, "west") == 0) {
        newVehicle.endRoad = W;
    } else {
        printf("Invalid direction\n");
    }

    return newVehicle;
}

VehiclePair createVehiclePair(void) {
    VehiclePair pair;
    pair.vehicle0 = pair.vehicle1 = NULL;
    pair.numVehicles = 0;
    return pair;
}

void addToVehiclePair(VehiclePair* vehiclePair, Vehicle* vehicle) {
    if (vehiclePair->vehicle0 == NULL) {
        vehiclePair->numVehicles = 1;
        vehiclePair->vehicle0 = vehicle;
    } else if (vehiclePair->vehicle1 == NULL) {
        vehiclePair->numVehicles = 2;
        vehiclePair->vehicle1 = vehicle;
    } else {
        printf("You can't add more than 2 vehicles.\n");
    }
}

Vehicle* vehiclePairGet(VehiclePair* vehiclePair, int index) {
    switch (index) {
        case 0:
            return vehiclePair->vehicle0;
        case 1:
            return vehiclePair->vehicle1;
        default:
            printf("Index out of bounds.\n");
            return NULL;
    }
}



