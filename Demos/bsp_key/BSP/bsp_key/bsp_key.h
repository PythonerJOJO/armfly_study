/**
 ******************************************************************************
 * @file:  key.h
 * @brief: Header for key.c file.
 *
 ******************************************************************************
 * @attention
 */

#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "bsp_config.h"

typedef struct bsp_key
{
    char *name;
    int (*init)(struct bsp_key _key);
    int (*read)(struct bsp_key _key);
    void *privateData;
} BspKey;

BspKey *getKey(char *_name);

#endif /* __BSP_KEY_H */