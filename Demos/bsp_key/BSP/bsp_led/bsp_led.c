/**
 ******************************************************************************
 * @file: bsp_led.c
 * @brief:  Source for bsp_led.c file.
 *
 ******************************************************************************
 * @attention
 */
#include "bsp_led.h"

#include <string.h>

#include "gpio.h"

#include "bsp_config.h"

/*******************************  函数声明 ********************************/
static int bsp_ledInit(void);
static int bsp_ledRead(struct bsp_led _led);
static int bsp_ledWrite(struct bsp_led _led, const bool _state);
// LED初始化结构体
typedef struct bsp_led_init
{
    GPIO_TypeDef *port;
    uint16_t pin;
    // uint8_t id;
    int (*init)(void);
} BspLedPrivateData;

BspLedPrivateData bspLedInit1 = {
    .port = LED_GPIO_Port,
    .pin = LED_Pin,
};
// LED对象数组
static BspLed bspLed[LED_NUM] = {
    {
        .name = "LED1",
        .init = bsp_ledInit,
        .read = bsp_ledRead,
        .write = bsp_ledWrite,
        .privateData = &bspLedInit1,
    },
};

static int bsp_ledInit(void)
{
    // BspLedPrivateData *ledPrivateData = bspLed[0].privateData;
    return 0;
}

static int bsp_ledRead(struct bsp_led _led)
{
    BspLedPrivateData *ledPrivateData = _led.privateData;
    if (HAL_GPIO_ReadPin(ledPrivateData->port, ledPrivateData->pin))
    {
        return 0;
    }
    return 1;
}

static int bsp_ledWrite(struct bsp_led _led, const bool _state)
{
    BspLedPrivateData *ledPrivateData = _led.privateData;
    _state ? HAL_GPIO_WritePin(ledPrivateData->port, ledPrivateData->pin, GPIO_PIN_RESET) : HAL_GPIO_WritePin(ledPrivateData->port, ledPrivateData->pin, GPIO_PIN_SET);
    return SUCCESS;
}

/**
 * @brief Get the Led object 暴露方法
 *
 * @param _name
 * @return BspLed*
 */
BspLed *getLed(char *_name)
{
    for (int i = 0; i < LED_NUM; i++)
    {
        /**
         * @brief 该函数比较两个字符串 str1 和 str2，并根据比较结果返回一个整数：
                    如果 str1 小于 str2，则返回一个负数。
                    如果 str1 大于 str2，则返回一个正数。
                    如果 str1 和 str2 相等，则返回 0。
         */
        if (strcmp(_name, bspLed[i].name) == 0)
        {
            return &bspLed[i];
        }
    }
    return NULL;
}
