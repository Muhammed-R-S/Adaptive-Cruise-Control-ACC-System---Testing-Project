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
void run_test(const char* testCaseID, bool sensorError, bool systemError, bool expectedActivation) {
    // Reset ACC system state
    acc = (ACC_System){false, 0, 0, 0, false, sensorError, systemError};

    // Activate ACC
    activateACC(&acc, 50); // Assuming 50 km/h is within the valid speed range for activation.

    // Check the activation status
    if (acc.isActive == expectedActivation) {
        printf("%s: Passed\n", testCaseID);
        passed++;
    } else {
        printf("%s: Failed (Sensor Error: %s, System Error: %s, Expected Activation: %s, Observed Activation: %s)\n",
               testCaseID,
               sensorError ? "TRUE" : "FALSE",
               systemError ? "TRUE" : "FALSE",
               expectedActivation ? "TRUE" : "FALSE",
               acc.isActive ? "TRUE" : "FALSE");
        failed++;
    }
}

// Test Suite for R-ACC-011
void testRequirementR_ACC_011() {
    printf("Running Tests for R-ACC-011...\n");

    // TC-033: Self-test passes (no errors)
    run_test("TC-033", false, false, true);

    // TC-034: Self-test fails (sensor error)
    run_test("TC-034", true, false, false);

    // TC-035: Self-test fails (system error)
    run_test("TC-035", false, true, false);
}

// CUnit Setup
int main() {
    // Initialize CUnit
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Add Suite and Test Cases
    CU_pSuite suite = CU_add_suite("ACC_Test_Suite_R-ACC-011", NULL, NULL);
    if (!suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(suite, "Test R-ACC-011", testRequirementR_ACC_011)) {
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
