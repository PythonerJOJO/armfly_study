/**
 ******************************************************************************
 * @file: bsp_key.c
 * @brief:  Source for bsp_key.c file.
 *
 ******************************************************************************
 * @attention
 */
#include "bsp_key.h"

#include <stdint.h>
#include <string.h>

#include "gpio.h"

static int KeyInit(struct bsp_key _key);
static int KeyRead(struct bsp_key _key);

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
    uint8_t activate;
} PrivateData;

static PrivateData key1 = {
    .port = KEY1_GPIO_Port,
    .pin = KEY1_Pin,
    .activate = 0,
};

static PrivateData key2 = {
    .port = KEY2_GPIO_Port,
    .pin = KEY2_Pin,
    .activate = 0,
};

BspKey bspKey[KEY_NUM] = {
    {
        .name = "Key1",
        .init = KeyInit,
        .read = KeyRead,
        .privateData = &key1,
    },
    {
        .name = "Key2",
        .init = KeyInit,
        .read = KeyRead,
        .privateData = &key2,
    },
};

// int (*init)(struct bsp_key _key);
static int KeyInit(struct bsp_key _key)
{
    // PrivateData *privateData = _key.privateData;
    return SUCCESS;
}

static int KeyRead(struct bsp_key _key)
{
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    PrivateData *privateData = _key.privateData;
    if (privateData->activate != HAL_GPIO_ReadPin(privateData->port, privateData->pin))
        return 0;
    return 1;
}

BspKey *getKey(char *_name)
{
    for (int i = 0; i < KEY_NUM; i++)
    {
        if (strcmp(bspKey[i].name, _name) == 0)
        {
            return &bspKey[i];
        }
    }
    return NULL;
}
