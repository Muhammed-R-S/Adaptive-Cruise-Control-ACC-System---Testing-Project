#include "acc_system.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>

// Test Results
int passed = 0;
int failed = 0;

// Test Variables
ACC_System acc;

// Helper function for a single test
void run_test(const char* testCaseID, int currentSpeed, int desiredSpeed, int distanceToVehicleAhead, int expectedSpeed) {
    // Reset ACC system state
    acc = (ACC_System){true, currentSpeed, desiredSpeed, distanceToVehicleAhead, false, false, false};

    // Monitor Distance
    monitorDistance(&acc);

    // Check the current speed
    if (acc.currentSpeed == expectedSpeed) {
        printf("%s: Passed\n", testCaseID);
        passed++;
    } else {
        printf("%s: Failed (Current Speed: %d, Desired Speed: %d, Distance: %d, Expected Speed: %d, Observed Speed: %d)\n",
               testCaseID, currentSpeed, desiredSpeed, distanceToVehicleAhead, expectedSpeed, acc.currentSpeed);
        failed++;
    }
}

// Test Suite for R-ACC-008
void testRequirementR_ACC_008() {
    printf("Running Tests for R-ACC-008...\n");

    // TC-027: Gradual speed increase when distance > 100 meters
    run_test("TC-027", 80, 100, 101, 85); // Expected speed increased by 5 km/h

    // TC-028: No speed increase when distance <= 100 meters
    run_test("TC-028", 80, 100, 90, 80); // Speed maintained
}

// CUnit Setup
int main() {
    // Initialize CUnit
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Add Suite and Test Cases
    CU_pSuite suite = CU_add_suite("ACC_Test_Suite_R-ACC-008", NULL, NULL);
    if (!suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(suite, "Test R-ACC-008", testRequirementR_ACC_008)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run Tests
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    // Cleanup
    CU_cleanup_registry();
    return CU_get_error();
}
