#ifndef DISHWASHERCONTROLLER_HEATER_HELPERS_H
#define DISHWASHERCONTROLLER_HEATER_HELPERS_H

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * Check the current temperature and emit the appropriate event
     */
    void Heater_pollTemperature(void);

#ifdef __cplusplus
}
#endif

#endif // DISHWASHERCONTROLLER_HEATER_HELPERS_H
