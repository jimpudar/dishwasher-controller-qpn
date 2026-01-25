#include "dishwasher_helpers.h"

#include "active_objects.h"
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
    DEBUG_PRINTLN(F("DOOR OPENED"));
    BSP_setOutputLogicalState(RELAY_MOTOR, INACTIVE);
    BSP_setOutputLogicalState(RELAY_FILL, INACTIVE);
    BSP_setOutputLogicalState(RELAY_DETERGENT, INACTIVE);
    BSP_setOutputLogicalState(RELAY_RINSEAID, INACTIVE);
}

bool Dishwasher_isReadyToWash()
{
    DEBUG_PRINTLN(F("READY TO WASH?"));
    if (Dishwasher_isManualSwitchEngaged())
    {
        DEBUG_PRINTLN(F("NO - man sw"));
        return false;
    }

    if (!Dishwasher_waterInTankIsAtWashTemperature())
    {
        DEBUG_PRINTLN(F("NO - wash temp"));
        return false;
    }

    if (!BSP_isFloatClosed())
    {
        DEBUG_PRINTLN(F("NO - float open"));
        return false;
    }

    if (!BSP_isDoorClosed())
    {
        DEBUG_PRINTLN(F("NO - door open"));
        return false;
    }

    return true;
}

bool Dishwasher_isManualSwitchEngaged() { return BSP_isManualRinseClosed() || BSP_isManualWashClosed(); }

bool Dishwasher_waterInTankIsAtWashTemperature()
{
    const int16_t temp = BSP_readTemperature();

    return temp > MINIMUM_WASH_TEMP && temp < MAXIMUM_SAFE_TEMP;
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

void Dishwasher_startIdle()
{
    DEBUG_PRINTLN(F("START IDLE"));
    int16_t temp = BSP_readTemperature();
    if (!BSP_isFloatClosed() || temp < MINIMUM_WASH_TEMP)
    {
        BSP_setOutputLogicalState(INDICATOR_READY, INACTIVE);
    }
    else if (BSP_isFloatClosed() && temp >= MINIMUM_WASH_TEMP && temp <= MAXIMUM_SAFE_TEMP)
    {
        BSP_setOutputLogicalState(INDICATOR_READY, ACTIVE);
    }
    else if (temp > MAXIMUM_SAFE_TEMP)
    {
        QACTIVE_POST(AO_Heater, FAULT_SIG, 0U);
        QACTIVE_POST(AO_Dishwasher, OVER_TEMP_FAULT_SIG, 0U);
    }
}
void Dishwasher_stopIdle()
{
    BSP_setOutputLogicalState(INDICATOR_READY, INACTIVE);
}

void Dishwasher_startTimedFill()
{
    DEBUG_PRINTLN(F("START TIMED FILL"));
    BSP_setOutputLogicalState(INDICATOR_FILL, ACTIVE);
    BSP_setOutputLogicalState(RELAY_FILL, ACTIVE);
}

void Dishwasher_stopTimedFill()
{
    DEBUG_PRINTLN(F("STOP TIMED FILL"));
    BSP_setOutputLogicalState(INDICATOR_FILL, INACTIVE);
    BSP_setOutputLogicalState(RELAY_FILL, INACTIVE);
}

void Dishwasher_startWashCycle()
{
    DEBUG_PRINTLN(F("START WASH"));
    BSP_setOutputLogicalState(RELAY_MOTOR, ACTIVE);
    BSP_setOutputLogicalState(RELAY_DETERGENT, ACTIVE);
}

void Dishwasher_stopWashCycle()
{
    DEBUG_PRINTLN(F("STOP WASH"));
    BSP_setOutputLogicalState(RELAY_MOTOR, INACTIVE);
    BSP_setOutputLogicalState(RELAY_DETERGENT, INACTIVE);
}

void Dishwasher_startRinseCycle()
{
    DEBUG_PRINTLN(F("START RINSE"));
    BSP_setOutputLogicalState(INDICATOR_RINSE, ACTIVE);
    BSP_setOutputLogicalState(RELAY_FILL, ACTIVE);
    BSP_setOutputLogicalState(RELAY_RINSEAID, ACTIVE);
}

void Dishwasher_stopRinseCycle()
{
    DEBUG_PRINTLN(F("STOP RINSE"));
    BSP_setOutputLogicalState(INDICATOR_RINSE, INACTIVE);
    BSP_setOutputLogicalState(RELAY_FILL, INACTIVE);
    BSP_setOutputLogicalState(RELAY_RINSEAID, INACTIVE);
}

void Dishwasher_enterFaultMode()
{
    DEBUG_PRINTLN(F("FAULT"));
    QACTIVE_POST(AO_Heater, FAULT_SIG, 0U);
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