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

bool Heater_shouldHeatStayOff()
{
    return Heater_gtLowerHystThresh() || !BSP_isFloatClosed();
}

bool Heater_shouldHeatStayOn()
{
    return Heater_ltUpperHystThresh() && BSP_isFloatClosed();
}