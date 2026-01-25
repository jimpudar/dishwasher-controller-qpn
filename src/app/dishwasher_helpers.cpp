#include "dishwasher_helpers.h"

#include "bsp.h"
#include "constants.h"
#include "debug.h"
#include "signals.h"

void Dishwasher_startup(QActive *me)
{
    if (Dishwasher_isManualSwitchEngaged())
    {
        DEBUG_PRINTLN(F("startup with manual engaged"));
        QACTIVE_POST(me, STARTUP_FAULT_SIG, 0U);
        return;
    }

    QACTIVE_POST(me, STARTUP_SIG, 0U);
}

void Dishwasher_handleDoorOpening()
{
    BSP_setOutputLogicalState(RELAY_MOTOR, INACTIVE);
    BSP_setOutputLogicalState(RELAY_FILL, INACTIVE);
    BSP_setOutputLogicalState(RELAY_DETERGENT, INACTIVE);
    BSP_setOutputLogicalState(RELAY_RINSEAID, INACTIVE);
}

bool Dishwasher_isReadyToWash()
{
    DEBUG_PRINTLN(F("Check readytowash"));
    if (Dishwasher_isManualSwitchEngaged())
    {
        DEBUG_PRINTLN(F("no - man sw"));
        return false;
    }

    if (!Dishwasher_waterInTankIsAtWashTemperature())
    {
        DEBUG_PRINTLN(F("no - wash temp"));
        return false;
    }

    if (!BSP_isFloatClosed())
    {
        DEBUG_PRINTLN(F("no - float open"));
        return false;
    }

    if (!BSP_isDoorClosed())
    {
        DEBUG_PRINTLN(F("no - door open"));
        return false;
    }

    return true;
}

bool Dishwasher_isManualSwitchEngaged() { return BSP_isManualRinseClosed() || BSP_isManualWashClosed(); }

bool Dishwasher_waterInTankIsAtWashTemperature()
{
    const int16_t temp = BSP_readTemperature();

    return temp > 65 && temp < 88;
}

bool Dishwasher_waterInTankIsOverSafeTemperature()
{
    const int16_t temp = BSP_readTemperature();

    return temp > 90;
}

void Dishwasher_turnOnPumpMotor()
{
    if (BSP_isFloatClosed())
    {
        BSP_setOutputLogicalState(RELAY_MOTOR, ACTIVE);
    }
}

void Dishwasher_turnOffPumpMotor() { BSP_setOutputLogicalState(RELAY_MOTOR, INACTIVE); }

void Dishwasher_turnOnRinseValve() { BSP_setOutputLogicalState(RELAY_FILL, ACTIVE); }
void Dishwasher_turnOffRinseValve() { BSP_setOutputLogicalState(RELAY_FILL, INACTIVE); }

void Dishwasher_startTimedFill()
{
    BSP_setOutputLogicalState(INDICATOR_FILL, ACTIVE);
    BSP_setOutputLogicalState(RELAY_FILL, ACTIVE);
}

void Dishwasher_stopTimedFill()
{
    BSP_setOutputLogicalState(INDICATOR_FILL, INACTIVE);
    BSP_setOutputLogicalState(RELAY_FILL, INACTIVE);
}

void Dishwasher_startWashCycle()
{
    BSP_setOutputLogicalState(RELAY_MOTOR, ACTIVE);
    BSP_setOutputLogicalState(RELAY_DETERGENT, ACTIVE);
}

void Dishwasher_stopWashCycle()
{
    BSP_setOutputLogicalState(RELAY_MOTOR, INACTIVE);
    BSP_setOutputLogicalState(RELAY_DETERGENT, INACTIVE);
}

void Dishwasher_startRinseCycle()
{
    BSP_setOutputLogicalState(INDICATOR_RINSE, ACTIVE);
    BSP_setOutputLogicalState(RELAY_FILL, ACTIVE);
    BSP_setOutputLogicalState(RELAY_RINSEAID, ACTIVE);
}

void Dishwasher_stopRinseCycle()
{
    BSP_setOutputLogicalState(INDICATOR_RINSE, INACTIVE);
    BSP_setOutputLogicalState(RELAY_FILL, INACTIVE);
    BSP_setOutputLogicalState(RELAY_RINSEAID, INACTIVE);
}

void Dishwasher_enterFaultMode()
{
    DEBUG_PRINTLN(F("Enter fault"));
    BSP_setOutputLogicalState(RELAY_MOTOR, INACTIVE);
    BSP_setOutputLogicalState(RELAY_FILL, INACTIVE);
    BSP_setOutputLogicalState(RELAY_DETERGENT, INACTIVE);
    BSP_setOutputLogicalState(RELAY_RINSEAID, INACTIVE);
    BSP_setOutputLogicalState(RELAY_HEATER, INACTIVE);

    while (1) {
        BSP_setOutputLogicalState(INDICATOR_FILL, ACTIVE);
        BSP_setOutputLogicalState(INDICATOR_READY, ACTIVE);
        BSP_setOutputLogicalState(INDICATOR_RINSE, ACTIVE);
        _delay_ms(250);
        BSP_setOutputLogicalState(INDICATOR_FILL, INACTIVE);
        BSP_setOutputLogicalState(INDICATOR_READY, INACTIVE);
        BSP_setOutputLogicalState(INDICATOR_RINSE, INACTIVE);
        _delay_ms(250);
    }
}