#ifndef DISHWASHERCONTROLLER_CONSTANTS_H
#define DISHWASHERCONTROLLER_CONSTANTS_H

//============================================================================
// various constants for the application...
enum
{
    TICKS_PER_SEC = 100, // number of system clock ticks in one second
    TICKS_PER_MIN = 60U * TICKS_PER_SEC,

    // TODO: Time how long filling actually takes
    TIMEDFILL_TIMEOUT_TICKS = 15U * TICKS_PER_SEC,
    WASHCYCLE_TIMEOUT_TICKS = 60 * TICKS_PER_SEC,
    DWELL_TIMEOUT_TICKS = 10 * TICKS_PER_SEC,
    RINSECYCLE_TIMEOUT_TICKS = 20 * TICKS_PER_SEC,
    HEAT_LOOP_TIMEOUT_TICKS = 5U * TICKS_PER_SEC,

    MINIMUM_WASH_TEMP = 66, // 150 F
    MAXIMUM_SAFE_TEMP = 95, // 203 F - something has gone wrong if water is this hot
    HEAT_UPPER_HYSTERESIS_TEMP = 75, // 167 F
    HEAT_LOWER_HYSTERESIS_TEMP = 70, // 158 F
};

typedef enum
{
    INACTIVE = 0x0,
    ACTIVE = 0x1,
} LogicalState;

typedef enum
{
    RELAY_MOTOR = 0,
    RELAY_HEATER = 1,
    RELAY_FILL = 2,
    RELAY_DETERGENT = 3,
    RELAY_RINSEAID = 4,
    INDICATOR_FILL = 5,
    INDICATOR_RINSE = 6,
    INDICATOR_READY = 7,
} Output;

typedef enum
{
    SWITCH_DOOR = 0,
    SWITCH_FLOAT = 1,
    SWITCH_MANUALRINSE = 2,
    SWITCH_MANUALWASH = 3,
    SWITCH_TIMEDFILL = 4,
    SWITCH_STOP = 5
} Input;

//............................................................................
#endif // DISHWASHERCONTROLLER_CONSTANTS_H
