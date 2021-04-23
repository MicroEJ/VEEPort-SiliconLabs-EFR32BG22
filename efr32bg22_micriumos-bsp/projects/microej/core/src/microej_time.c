/*
 * C
 *
 * Copyright 2020 MicroEJ Corp. All rights reserved.
 * This library is provided in source code for use, modification and test, subject to license terms.
 * Any modification of the source code will break MicroEJ Corp. warranties on the whole library.
 */

#include <stdint.h>
#include "microej.h"
#include "microej_time.h"
#include "os.h"

// Simple time implementation that uses OS ticks to compute time.

/*
 *********************************************************************************************************
 *                                             DEFINES
 *********************************************************************************************************
 */

#if (OS_CFG_TICK_EN != DEF_ENABLED)

// This implementation is based on the MicriumOS tick
#error "MicriumOS tick has to be enabled"

#endif

/*
 *********************************************************************************************************
 * 	                                      INTERNAL FUNCTIONS
 *********************************************************************************************************
 */

/** Offset in ms from system time to application time */
static uint64_t microej_application_time_offset = 0;

/*
 *********************************************************************************************************
 * 	                                      PUBLIC FUNCTIONS
 *********************************************************************************************************
 */

/*
 * Convert a nb of ticks in milliseconds.
 * Result is round up to the next millisecond (ie. converting back the resulting ms
 * to ticks results in a value greater than or equals to given time).
 */
int64_t microej_time_tickToTime(OS_TICK ticks) {
    RTOS_ERR err;
    OS_RATE_HZ tick_rate_hz = OSTimeTickRateHzGet(&err);
    EFM_ASSERT((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE));

    int64_t timems = (ticks * 1000ULL) / tick_rate_hz;

    return timems;
}

/*
 * Convert a time from milliseconds to ticks.
 * Result is round up to the next tick (ie. converting back the resulting ticks
 * to milliseconds results in a value greater than or equals to given time).
 */
int64_t microej_time_timeToTick(int64_t time) {
    if (time < microej_time_tickToTime(OSDelayMaxTick)) {
        int64_t timeus = time * 1000ULL;
        int64_t os_tick = 1000000ULL / OSCfg_TmrTaskRate_Hz; // tick in microseconds
        return (timeus + (os_tick - 1)) / os_tick;
    } else {
        return OSDelayMaxTick;
    }
}

int64_t microej_time_getcurrenttime(uint8_t isPlatformTime) {
    /*
     * /!\
     * isPlatformTime == true when ej.bon.Util.platformTimeMillis
     * isPlatformTime == false when java.lang.System.currentTimeMillis
     * /!\
     */

    RTOS_ERR err;
    OS_TICK ticks = OSTimeGet(&err);
    EFM_ASSERT((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE));

    int64_t time = microej_time_tickToTime(ticks);

    if (isPlatformTime == MICROEJ_TRUE) {
        return time;
    } else {
        int64_t applicationTime = time + microej_application_time_offset;
        return applicationTime;
    }
}

int64_t microej_time_gettimenanos() {
    return microej_time_getcurrenttime(MICROEJ_TRUE) * 1000000ULL;
}

void microej_time_setapplicationtime(int64_t t) {
    int64_t currentTime = microej_time_getcurrenttime(MICROEJ_TRUE);
    microej_application_time_offset = t - currentTime;
}
