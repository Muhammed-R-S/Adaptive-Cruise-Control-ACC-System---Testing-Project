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
void run_test(const char* testCaseID, int currentSpeed, int desiredSpeed, int expectedSpeed) {
    // Reset ACC system state
    acc = (ACC_System){true, currentSpeed, desiredSpeed, 0, false, false, false};

    // Adjust Speed
    adjustSpeed(&acc);

    // Check the current speed
    if (acc.currentSpeed == expectedSpeed) {
        printf("%s: Passed\n", testCaseID);
        passed++;
    } else {
        printf("%s: Failed (Current Speed: %d, Desired Speed: %d, Expected Speed: %d, Observed Speed: %d)\n",
               testCaseID, currentSpeed, desiredSpeed, expectedSpeed, acc.currentSpeed);
        failed++;
    }
}

// Test Suite for R-ACC-004
void testRequirementR_ACC_004() {
    printf("Running Tests for R-ACC-004...\n");

    // TC-015: Speed increment
    run_test("TC-015", 30, 35, 35);

    // TC-016: Speed decrement
    run_test("TC-016", 60, 55, 55);

    // TC-017: No change in speed
    run_test("TC-017", 100, 100, 100);
}

// CUnit Setup
int main() {
    // Initialize CUnit
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Add Suite and Test Cases
    CU_pSuite suite = CU_add_suite("ACC_Test_Suite_R-ACC-004", NULL, NULL);
    if (!suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(suite, "Test R-ACC-004", testRequirementR_ACC_004)) {
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
