#include "heater_helpers.h"

#include "active_objects.h"
#include "bsp.h"
#include "debug.h"
#include "qfn.h"
#include "signals.h"
void Heater_stopHeating()
{
    DEBUG_PRINTLN(F("HEAT OFF"));
    BSP_setOutputLogicalState(RELAY_HEATER, INACTIVE);
}
void Heater_startHeating()
{
    if (!BSP_isFloatClosed())
    {
        DEBUG_PRINTLN(F("NOT HEATING - NO WATER"));
        return;
    }
    DEBUG_PRINTLN(F("HEAT ON"));
    BSP_setOutputLogicalState(RELAY_HEATER, ACTIVE);
}
bool Heater_ltUpperHystThresh()
{
    int16_t temp = BSP_readTemperature();
    return temp < HEAT_UPPER_HYSTERESIS_TEMP;
}
bool Heater_gtLowerHystThresh()
{
    int16_t temp = BSP_readTemperature();
    return temp > HEAT_LOWER_HYSTERESIS_TEMP;
}

void Heater_setReadyIndicator(int16_t temp)
{
    if (temp <= MINIMUM_WASH_TEMP)
    {
        BSP_setOutputLogicalState(INDICATOR_READY, INACTIVE);
    }
    if (temp > MINIMUM_WASH_TEMP && temp <= MAXIMUM_SAFE_TEMP)
    {
        BSP_setOutputLogicalState(INDICATOR_READY, ACTIVE);
    }
    if (temp > MAXIMUM_SAFE_TEMP)
    {
        QACTIVE_POST(AO_Dishwasher, OVER_TEMP_FAULT_SIG, 0U);
    }
}