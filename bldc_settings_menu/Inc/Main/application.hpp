#ifndef __APPLICATION_HPP
#define __APPLICATION_HPP

#include "main.h"
#include "stm32f3xx_hal.h"

#define SHORT_MS 2000
#define LONG_MS 4000
#define NA_MS 8000
#define POS_CONST 5

#ifdef __cplusplus
extern "C"
{
#endif

    void setup();
    void loop();

#ifdef __cplusplus
}
#endif

#endif
