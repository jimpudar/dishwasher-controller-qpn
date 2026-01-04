#include "dishwasher_helpers.h"
#include "constants.h"

void Dishwasher_armTimeout(QActive* me)
{
    QActive_armX(me,
                 0U,
                 BSP_TICKS_PER_SEC / 2U,
                 BSP_TICKS_PER_SEC / 2U);
}
