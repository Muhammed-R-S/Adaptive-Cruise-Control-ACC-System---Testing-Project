#ifndef ACC_SYSTEM_H
#define ACC_SYSTEM_H

#include <stdbool.h>

// Constants
#define MIN_SPEED 30
#define MAX_SPEED 150
#define SAFE_DISTANCE_MIN 50
#define SAFE_DISTANCE_MAX 100
#define DEACTIVATION_SPEED 25

// ACC System State
typedef struct {
    bool isActive;
    int currentSpeed;
    int desiredSpeed;
    int distanceToVehicleAhead;
    bool brakePressed;
    bool sensorError;
    bool systemError;
} ACC_System;

// Function Prototypes
void activateACC(ACC_System *acc, int initialSpeed);
void deactivateACC(ACC_System *acc);
void adjustSpeed(ACC_System *acc);
void monitorDistance(ACC_System *acc);
void performSelfTest(ACC_System *acc);

#endif // ACC_SYSTEM_H
