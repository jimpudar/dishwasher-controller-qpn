#include "heater_helpers.h"
#include "bsp.h"
#include "debug.h"
void Heater_stopHeating()
{
    DEBUG_PRINTLN(F("HEAT OFF"));
    BSP_setOutputLogicalState(RELAY_HEATER, INACTIVE);
}
void Heater_startHeating()
{
    DEBUG_PRINTLN(F("HEAT ON"));
    BSP_setOutputLogicalState(RELAY_HEATER, ACTIVE);
}
bool Heater_ltUpperHystThresh() { return BSP_readTemperature() < HEAT_UPPER_HYSTERESIS_TEMP; }
bool Heater_gtLowerHystThresh() { return BSP_readTemperature() > HEAT_LOWER_HYSTERESIS_TEMP; }