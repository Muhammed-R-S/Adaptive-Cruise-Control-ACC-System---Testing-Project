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
void run_test(const char* testCaseID, int currentSpeed, int distanceToVehicleAhead, int expectedSpeed) {
    // Reset ACC system state
    acc = (ACC_System){true, currentSpeed, 100, distanceToVehicleAhead, false, false, false};

    // Monitor Distance
    monitorDistance(&acc);

    // Check the current speed
    if (acc.currentSpeed == expectedSpeed) {
        printf("%s: Passed\n", testCaseID);
        passed++;
    } else {
        printf("%s: Failed (Current Speed: %d, Distance: %d, Expected Speed: %d, Observed Speed: %d)\n",
               testCaseID, currentSpeed, distanceToVehicleAhead, expectedSpeed, acc.currentSpeed);
        failed++;
    }
}

// Test Suite for R-ACC-007
void testRequirementR_ACC_007() {
    printf("Running Tests for R-ACC-007...\n");

    // TC-025: Gradual speed reduction when distance < 50 meters
    run_test("TC-025", 80, 49, 75); // Expected speed reduced by 5 km/h

    // TC-026: No speed reduction when distance >= 50 meters
    run_test("TC-026", 80, 60, 80); // Speed maintained
}

// CUnit Setup
int main() {
    // Initialize CUnit
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Add Suite and Test Cases
    CU_pSuite suite = CU_add_suite("ACC_Test_Suite_R-ACC-007", NULL, NULL);
    if (!suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(suite, "Test R-ACC-007", testRequirementR_ACC_007)) {
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
