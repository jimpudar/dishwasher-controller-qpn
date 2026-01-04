#ifndef DISHWASHERCONTROLLER_BSP_H
#define DISHWASHERCONTROLLER_BSP_H

#ifdef __cplusplus
extern "C"
{
#endif

    void BSP_init(void);
    int16_t BSP_readTemperature(void);

#ifdef __cplusplus
}
#endif

#endif // DISHWASHERCONTROLLER_BSP_H
