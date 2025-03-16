#ifndef CROSSROADS_VEHICLE_H
#define CROSSROADS_VEHICLE_H

enum Direction {
    N, //0
    W, //1
    S, //2
    E  //3
};

typedef struct {
    char* vehicleId;
    enum Direction startRoad;
    enum Direction endRoad;
} Vehicle;

typedef struct {
    Vehicle* vehicle0;
    Vehicle* vehicle1;
    int numVehicles;
} VehiclePair;

Vehicle createVehicle(const char* vehicleId, const char* startRoad, const char* endRoad);
VehiclePair createVehiclePair();
void addToVehiclePair(VehiclePair* vehiclePair, Vehicle* vehicle);
Vehicle* vehiclePairGet(VehiclePair* vehiclePair, int index);

#endif
