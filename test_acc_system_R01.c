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
void run_test(const char* testCaseID, int initialSpeed, bool expectedActivation, int expectedSpeed) {
    // Reset ACC system state
    acc = (ACC_System){false, 0, 0, 0, false, false, false};

    // Activate ACC
    activateACC(&acc, initialSpeed);

    // Check the activation status and desired speed
    if (acc.isActive == expectedActivation && acc.desiredSpeed == expectedSpeed) {
        printf("%s: Passed\n", testCaseID);
        passed++;
    } else {
        printf("%s: Failed (Initial Speed: %d, Expected Activation: %s, Observed Activation: %s, Expected Speed: %d, Observed Speed: %d)\n",
               testCaseID,
               initialSpeed,
               expectedActivation ? "TRUE" : "FALSE",
               acc.isActive ? "TRUE" : "FALSE",
               expectedSpeed,
               acc.desiredSpeed);
        failed++;
    }
}

// Test Suite for R-ACC-001
void testRequirementR_ACC_001() {
    printf("Running Tests for R-ACC-001...\n");

    run_test("TC-001", 30, true, 30);  // Minimum speed
    run_test("TC-002", 31, true, 31);  // Just above minimum speed
    run_test("TC-003", 85, true, 85);  // Mid-range speed
    run_test("TC-004", 149, true, 149); // Just below maximum speed
    run_test("TC-005", 150, true, 150); // Maximum speed
    run_test("TC-006", 29, false, 0);   // Below minimum speed
    run_test("TC-007", 151, false, 0);  // Above maximum speed
}

// CUnit Setup
int main() {
    // Initialize CUnit
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Add Suite and Test Cases
    CU_pSuite suite = CU_add_suite("ACC_Test_Suite_R-ACC-001", NULL, NULL);
    if (!suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(suite, "Test R-ACC-001", testRequirementR_ACC_001)) {
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
