/**
 ******************************************************************************
 * @file: led.c
 * @brief:  Source for led.c file.
 *
 ******************************************************************************
 * @attention
 */
#include "led.h"

#include <stdlib.h>

int ledInit(char *_ledName);
int ledDeviceList(void);
int ledOn(char *_ledName);
int ledOff(char *_ledName);
int ledToggle(char *_ledName);

static Led led = {
    .init = ledInit,
    .deviceList = ledDeviceList,
    .on = ledOn,
    .off = ledOff,
    .toggle = ledToggle,
};

int ledInit(char *_ledName)
{
    return SUCESS;
}

int ledDeviceList(void)
{
    // BspLed *bspLed = NULL;
    // int i = 0;
    // for (i = 0; i < LED_NUM; i++)
    // {
    //     bspLed = &bspLed[i];
    //     printf("%s\n", bspLed->name);
    // }
    return SUCESS;
}

int ledOn(char *_ledName)
{
    BspLed *bspLed = getLed(_ledName);
    if (bspLed == NULL)
        return NULLDEV;
    bspLed->write(*bspLed, true);
    return SUCESS;
}

int ledOff(char *_ledName)
{
    BspLed *bspLed = getLed(_ledName);
    if (bspLed == NULL)
        return NULLDEV;
    bspLed->write(*bspLed, false);
    return SUCESS;
}

int ledToggle(char *_ledName)
{
    BspLed *bspLed = getLed(_ledName);
    if (bspLed < 0)
        return NULLDEV;

    if (bspLed->read(*bspLed) == 1)
        bspLed->write(*bspLed, false);
    else
        bspLed->write(*bspLed, true);
    return 0;
}

/**
 * @brief Create a Led Object object
 *      将一个静态定义的 Led 结构体 led
 *          复制到一个动态分配的 Led 结构体指针 ledObject 所指向的内存区域。
 *      *ledObject = led;
 *          作用是将 led 结构体的内容复制到 ledObject 所指向的内存空间。
 *
 * @return Led*
 */
Led *createLedObject(void)
{
    Led *ledObject = (Led *)malloc(sizeof(Led));
    if (ledObject == NULL)
        return NULL;
    *ledObject = led;
    return ledObject;
}
