/**
 *
 * Microvisor App Test Stub
 *
 * Copyright © 2024, KORE Wireless
 * Licence: MIT
 *
 */
#include "main.h"


/*
 * STATIC PROTOTYPES
 */
static uint32_t perform_tests(void);


/**
 *  @brief The application entry point.
 */
int main(void) {

    // Reset all peripherals, Initializes the Flash interface and the sys tick.
    HAL_Init();

    /*
        In a real application test, your code will proceed to test the hardware components
        used by your application. For example, you might check that sensors can be seen on
        the appropriate peripheral bus, and are able to return date and trigger interrupts
        under simulated conditions.

        When all your tests are complete, your code should call the Microvisor System Call
        `mvTestingComplete()` and pass in zero (`0`) to indicate that the tests passed, or
        any non-zero value to indicate that the one or more of the tests failed.

        **IMPORTANT**
        `mvTestingComplete()` will only operate in code running within a factory environment.
        In all other cases, it will throw.

    */

    uint32_t test_result = perform_tests();

    uint32_t now = HAL_GetTick();
    while (HAL_GetTick() - now < 10000) {
        __asm("nop");
    }

    enum MvStatus status = mvTestingComplete(test_result);
    assert (status != MV_STATUS_UNAVAILABLE);
}


/**
 * @brief Jumping off point for application tests.
 *
 * @returns An unsigned integer status code: `0` for success,
 *          any other value for failure.
 */
static uint32_t perform_tests(void) {

    return APP_TESTS_TESTS_PASSED;
}


/**
 * @brief Get the MV clock value.
 *
 * @retval The clock value.
 */
uint32_t SECURE_SystemCoreClockUpdate() {

    uint32_t clock = 0;
    mvGetHClk(&clock);
    return clock;
}
