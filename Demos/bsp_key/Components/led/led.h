/**
 ******************************************************************************
 * @file:  led.h
 * @brief: Header for led.c file.
 *
 ******************************************************************************
 * @attention
 */
#ifndef __LED_H
#define __LED_H

#include "bsp_led/bsp_led.h"

typedef struct
{
    int (*init)(char *_ledName);
    int (*deviceList)(void);
    int (*on)(char *_ledName);
    int (*off)(char *_ledName);
    int (*toggle)(char *_ledName);
} Led;

// extern Led led;
Led *createLedObject(void);
#endif /* __LED_H */