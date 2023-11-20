/**
 *
 * Microvisor App Test Stub
 *
 * Copyright © 2023, KORE Wireless
 * Licence: MIT
 *
 */
#include "main.h"
#include "app_version.h"


/*
 * STATIC PROTOTYPES
 */
uint32_t perform_tests(void);


/**
 *  @brief The application entry point.
 */
int main(void) {

    // Reset of all peripherals, Initializes the Flash interface and the sys tick.
    HAL_Init();

    /*
        In a real application test, your code will proceed to test the hardware components
        used by your application. For example, you might check that sensors can be seen on
        the appropriate peripheral bus, and are able to return date and trigger interrupts
        under simulated conditions.

        When all your tests are complete, your code should call the Microvisor System Call
        `mvTestingComplete()` and pass in zero (`0`) to indicate that the tests passed, or
        any non-zero value to indicate that the one or more of the tests failed.
    */

   uint32_t test_result = perform_tests();
   mvTestingComplete(test_result);
}


/**
 * @brief Jumping off point for application tests.
 *
 * @returns An unsigned integer status code: `0` for success,
 *          any other value for failure.
 */
uint32_t perform_tests(void) {

    return APP_TESTS_TESTS_PASSED;
}