/**
 ******************************************************************************
 * @file:  bsp_led.h
 * @brief: Header for bsp_led.c file.
 *
 ******************************************************************************
 * @attention
 */
#ifndef __BSP_LED_H
#define __BSP_LED_H

#include <stdbool.h>
#include "error.h"

// LED对象结构体
typedef struct bsp_led
{
    char *name;

    int (*init)(void);
    int (*read)(struct bsp_led _led);
    int (*write)(struct bsp_led _led, const bool _state);
    // int (*toggle)(struct bsp_led _led);

    void *privateData; // void* 是一种通用指针类型，可以用来存储任何类型的指针
} BspLed;

// LED对象数组
BspLed *getLed(char *_name);
#endif /* __BSP_LED_H */