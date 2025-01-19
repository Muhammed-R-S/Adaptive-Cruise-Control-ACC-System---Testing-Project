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
void run_test(const char* testCaseID, bool initialActivation, bool sensorError, bool expectedActivation) {
    // Reset ACC system state
    acc = (ACC_System){initialActivation, 80, 100, 60, false, sensorError, false};

    // Monitor Distance (handles sensor errors)
    monitorDistance(&acc);

    // Check the activation status
    if (acc.isActive == expectedActivation) {
        printf("%s: Passed\n", testCaseID);
        passed++;
    } else {
        printf("%s: Failed (Initial Activation: %s, Sensor Error: %s, Expected Activation: %s, Observed Activation: %s)\n",
               testCaseID,
               initialActivation ? "TRUE" : "FALSE",
               sensorError ? "TRUE" : "FALSE",
               expectedActivation ? "TRUE" : "FALSE",
               acc.isActive ? "TRUE" : "FALSE");
        failed++;
    }
}

// Test Suite for R-ACC-009
void testRequirementR_ACC_009() {
    printf("Running Tests for R-ACC-009...\n");

    // TC-029: Deactivation when sensorError = true
    run_test("TC-029", true, true, false);

    // TC-030: No deactivation when sensorError = false
    run_test("TC-030", true, false, true);
}

// CUnit Setup
int main() {
    // Initialize CUnit
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Add Suite and Test Cases
    CU_pSuite suite = CU_add_suite("ACC_Test_Suite_R-ACC-009", NULL, NULL);
    if (!suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(suite, "Test R-ACC-009", testRequirementR_ACC_009)) {
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
