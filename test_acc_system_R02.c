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
void run_test(const char* testCaseID, int currentSpeed, bool brakePressed, bool systemError, bool expectedActivation) {
    // Reset ACC system state
    acc = (ACC_System){true, currentSpeed, 0, 0, brakePressed, false, systemError};

    // Adjust Speed (deactivation logic is within this function)
    adjustSpeed(&acc);

    // Check the activation status
    if (acc.isActive == expectedActivation) {
        printf("%s: Passed\n", testCaseID);
        passed++;
    } else {
        printf("%s: Failed (Current Speed: %d, Brake Pressed: %s, System Error: %s, Expected Activation: %s, Observed Activation: %s)\n",
               testCaseID,
               currentSpeed,
               brakePressed ? "TRUE" : "FALSE",
               systemError ? "TRUE" : "FALSE",
               expectedActivation ? "TRUE" : "FALSE",
               acc.isActive ? "TRUE" : "FALSE");
        failed++;
    }
}

// Test Suite for R-ACC-002
void testRequirementR_ACC_002() {
    printf("Running Tests for R-ACC-002...\n");

    // TC-008
    run_test("TC-008", 25, false, false, true);

    // TC-009
    run_test("TC-009", 25, false, true, false);

    // TC-010
    run_test("TC-010-A", 25, true, false, false); // Brake pressed
    run_test("TC-010-B", 25, true, true, false);  // Brake pressed with system error

    // TC-011
    run_test("TC-011-A", 24, false, false, false); // Speed < 25, no brake, no error
    run_test("TC-011-B", 24, true, false, false);  // Speed < 25, brake pressed
    run_test("TC-011-C", 24, false, true, false);  // Speed < 25, system error
    run_test("TC-011-D", 24, true, true, false);   // Speed < 25, brake pressed and system error
}

// CUnit Setup
int main() {
    // Initialize CUnit
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Add Suite and Test Cases
    CU_pSuite suite = CU_add_suite("ACC_Test_Suite_R-ACC-002", NULL, NULL);
    if (!suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(suite, "Test R-ACC-002", testRequirementR_ACC_002)) {
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
