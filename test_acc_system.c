#include "acc_system.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>

// Test Variables
ACC_System acc;

// Helper Function to Reset ACC System State
void resetACC(ACC_System *acc) {
    *acc = (ACC_System){false, 0, 0, 0, false, false, false};
}

// Test Cases for R-ACC-001 (Activation Range)
void test_R_ACC_001() {
    resetACC(&acc);

    // Valid Speeds
    activateACC(&acc, 30); CU_ASSERT_TRUE(acc.isActive);
    activateACC(&acc, 150); CU_ASSERT_TRUE(acc.isActive);

    // Invalid Speeds
    resetACC(&acc);
    activateACC(&acc, 29); CU_ASSERT_FALSE(acc.isActive);
    activateACC(&acc, 151); CU_ASSERT_FALSE(acc.isActive);
}

// Test Cases for R-ACC-002 (Deactivation Conditions)
void test_R_ACC_002() {
    resetACC(&acc);

    // Brake Pressed
    acc.isActive = true;
    acc.brakePressed = true;
    adjustSpeed(&acc);
    CU_ASSERT_FALSE(acc.isActive);

    // System Error
    resetACC(&acc);
    acc.isActive = true;
    acc.systemError = true;
    adjustSpeed(&acc);
    CU_ASSERT_FALSE(acc.isActive);

    // Speed < DEACTIVATION_SPEED
    resetACC(&acc);
    acc.isActive = true;
    acc.currentSpeed = 24;
    adjustSpeed(&acc);
    CU_ASSERT_FALSE(acc.isActive);
}

// Test Cases for R-ACC-004 (Speed Adjustments)
void test_R_ACC_004() {
    resetACC(&acc);

    // Speed Increment
    acc.isActive = true;
    acc.currentSpeed = 30;
    acc.desiredSpeed = 35;
    adjustSpeed(&acc);
    CU_ASSERT_EQUAL(acc.currentSpeed, 35);

    // Speed Decrement
    resetACC(&acc);
    acc.isActive = true;
    acc.currentSpeed = 60;
    acc.desiredSpeed = 55;
    adjustSpeed(&acc);
    CU_ASSERT_EQUAL(acc.currentSpeed, 55);
}

// Test Cases for R-ACC-007 (Distance Reduction)
void test_R_ACC_007() {
    resetACC(&acc);

    // Reduce Speed if Distance < SAFE_DISTANCE_MIN
    acc.isActive = true;
    acc.currentSpeed = 80;
    acc.distanceToVehicleAhead = 49;
    monitorDistance(&acc);
    CU_ASSERT_EQUAL(acc.currentSpeed, 75);

    // Maintain Speed if Distance >= SAFE_DISTANCE_MIN
    resetACC(&acc);
    acc.isActive = true;
    acc.currentSpeed = 80;
    acc.distanceToVehicleAhead = 60;
    monitorDistance(&acc);
    CU_ASSERT_EQUAL(acc.currentSpeed, 80);
}

// Test Cases for R-ACC-008 (Distance Increase)
void test_R_ACC_008() {
    resetACC(&acc);

    // Increase Speed if Distance > SAFE_DISTANCE_MAX
    acc.isActive = true;
    acc.currentSpeed = 80;
    acc.desiredSpeed = 100;
    acc.distanceToVehicleAhead = 101;
    monitorDistance(&acc);
    CU_ASSERT_EQUAL(acc.currentSpeed, 85);

    // Maintain Speed if Distance <= SAFE_DISTANCE_MAX
    resetACC(&acc);
    acc.isActive = true;
    acc.currentSpeed = 80;
    acc.distanceToVehicleAhead = 90;
    monitorDistance(&acc);
    CU_ASSERT_EQUAL(acc.currentSpeed, 80);
}

// Test Cases for R-ACC-009 (Sensor Error)
void test_R_ACC_009() {
    resetACC(&acc);

    // Deactivate if Sensor Error
    acc.isActive = true;
    acc.sensorError = true;
    monitorDistance(&acc);
    CU_ASSERT_FALSE(acc.isActive);

    // Remain Active if No Sensor Error
    resetACC(&acc);
    acc.isActive = true;
    acc.sensorError = false;
    monitorDistance(&acc);
    CU_ASSERT_TRUE(acc.isActive);
}

// Test Cases for R-ACC-011 (Self-Test)
void test_R_ACC_011() {
    resetACC(&acc);

    // Pass Self-Test
    acc.sensorError = false;
    acc.systemError = false;
    activateACC(&acc, 50);
    CU_ASSERT_TRUE(acc.isActive);

    // Fail Self-Test (Sensor Error)
    resetACC(&acc);
    acc.sensorError = true;
    activateACC(&acc, 50);
    CU_ASSERT_FALSE(acc.isActive);

    // Fail Self-Test (System Error)
    resetACC(&acc);
    acc.systemError = true;
    activateACC(&acc, 50);
    CU_ASSERT_FALSE(acc.isActive);
}

// Main Function
int main() {
    // Initialize CUnit
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Add Suite
    CU_pSuite suite = CU_add_suite("ACC Unified Test Suite", NULL, NULL);
    if (!suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add Tests
    CU_add_test(suite, "Test R-ACC-001", test_R_ACC_001);
    CU_add_test(suite, "Test R-ACC-002", test_R_ACC_002);
    CU_add_test(suite, "Test R-ACC-004", test_R_ACC_004);
    CU_add_test(suite, "Test R-ACC-007", test_R_ACC_007);
    CU_add_test(suite, "Test R-ACC-008", test_R_ACC_008);
    CU_add_test(suite, "Test R-ACC-009", test_R_ACC_009);
    CU_add_test(suite, "Test R-ACC-011", test_R_ACC_011);

    // Run Tests
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    // Cleanup
    CU_cleanup_registry();
    return 0;
}
