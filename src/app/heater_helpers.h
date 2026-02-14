#ifndef DISHWASHERCONTROLLER_HEATER_HELPERS_H
#define DISHWASHERCONTROLLER_HEATER_HELPERS_H

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief True if the current water temperature is less than the upper hysteresis threshold.
     */
    bool Heater_ltUpperHystThresh(void);
    /**
     * @brief True if the current water temperature is greater than the lower hysteresis threshold.
     */
    bool Heater_gtLowerHystThresh(void);
    /**
     * @brief Turn off the heater. Timeouts are handled in QM, this just handles the outputs.
     */
    void Heater_stopHeating(void);
    /**
     * @brief Turn on the heater. Timeouts are handled in QM, this just handles the outputs.
     */
    void Heater_startHeating(void);

    bool Heater_shouldHeatStayOn(void);

    bool Heater_shouldHeatStayOff(void);
#ifdef __cplusplus
}
#endif

#endif // DISHWASHERCONTROLLER_HEATER_HELPERS_H
