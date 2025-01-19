#include "acc_system.h"
#include <stdio.h>

// Activate ACC
void activateACC(ACC_System *acc, int initialSpeed) {
    if (initialSpeed >= MIN_SPEED && initialSpeed <= MAX_SPEED) {
        performSelfTest(acc);
        if (!acc->systemError) {
            acc->isActive = true;
            acc->desiredSpeed = initialSpeed;
            printf("ACC Activated at Speed: %d km/h\n", initialSpeed);
        }
    } else {
        printf("Cannot activate ACC. Invalid speed: %d km/h\n", initialSpeed);
    }
}

// Deactivate ACC
void deactivateACC(ACC_System *acc) {
    acc->isActive = false;
    printf("ACC Deactivated\n");
}

// Adjust Speed
void adjustSpeed(ACC_System *acc) {
    if (!acc->isActive) return;

    if (acc->brakePressed || acc->systemError || acc->sensorError || acc->currentSpeed < DEACTIVATION_SPEED) {
        deactivateACC(acc);
        return;
    }

    if (acc->currentSpeed < acc->desiredSpeed) {
        acc->currentSpeed += 5;
        printf("Speed Increased to: %d km/h\n", acc->currentSpeed);
    } else if (acc->currentSpeed > acc->desiredSpeed) {
        acc->currentSpeed -= 5;
        printf("Speed Decreased to: %d km/h\n", acc->currentSpeed);
    }
}

// Monitor Distance
void monitorDistance(ACC_System *acc) {
    if (!acc->isActive) return;

    if (acc->sensorError) {
        deactivateACC(acc);
        return;
    }

    if (acc->distanceToVehicleAhead < SAFE_DISTANCE_MIN) {
        acc->currentSpeed -= 5;
        printf("Distance too close! Reducing speed to: %d km/h\n", acc->currentSpeed);
    } else if (acc->distanceToVehicleAhead > SAFE_DISTANCE_MAX && acc->currentSpeed < acc->desiredSpeed) {
        acc->currentSpeed += 5;
        printf("Safe distance! Increasing speed to: %d km/h\n", acc->currentSpeed);
    }
}

// Perform Self-Test
void performSelfTest(ACC_System *acc) {
    if (acc->sensorError) {
        acc->systemError = true;
        printf("Self-Test Failed: Sensor Error\n");
    } else {
        acc->systemError = false;
        printf("Self-Test Passed\n");
    }
}
