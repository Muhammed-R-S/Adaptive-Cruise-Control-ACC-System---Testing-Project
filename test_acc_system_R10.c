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
void run_test(const char* testCaseID, bool initialActivation, bool systemError, bool expectedActivation) {
    // Reset ACC system state
    acc = (ACC_System){initialActivation, 80, 100, 60, false, false, systemError};

    // Adjust Speed (handles system errors)
    adjustSpeed(&acc);

    // Check the activation status
    if (acc.isActive == expectedActivation) {
        printf("%s: Passed\n", testCaseID);
        passed++;
    } else {
        printf("%s: Failed (Initial Activation: %s, System Error: %s, Expected Activation: %s, Observed Activation: %s)\n",
               testCaseID,
               initialActivation ? "TRUE" : "FALSE",
               systemError ? "TRUE" : "FALSE",
               expectedActivation ? "TRUE" : "FALSE",
               acc.isActive ? "TRUE" : "FALSE");
        failed++;
    }
}

// Test Suite for R-ACC-010
void testRequirementR_ACC_010() {
    printf("Running Tests for R-ACC-010...\n");

    // TC-031: Deactivation when systemError = true
    run_test("TC-031", true, true, false);

    // TC-032: No deactivation when systemError = false
    run_test("TC-032", true, false, true);
}

// CUnit Setup
int main() {
    // Initialize CUnit
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Add Suite and Test Cases
    CU_pSuite suite = CU_add_suite("ACC_Test_Suite_R-ACC-010", NULL, NULL);
    if (!suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(suite, "Test R-ACC-010", testRequirementR_ACC_010)) {
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
