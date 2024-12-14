/**
 ******************************************************************************
 * @file:  key.h
 * @brief: Header for key.c file.
 *
 ******************************************************************************
 * @attention
 */
#ifndef __KEY_H
#define __KEY_H

#include "bsp_key/bsp_key.h"

typedef struct
{
    int (*init)(void);
    int (*read)(char *_name);
} Key;

Key *createKeyObject(void);

#endif /* __KEY_H */