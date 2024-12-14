/**
 ******************************************************************************
 * @file: key.c
 * @brief:  Source for key.c file.
 *
 ******************************************************************************
 * @attention
 */
#include "key.h"

#include <stdlib.h>

static int keyInit(void);
static int keyRead(char *_name);

static Key key = {
    .init = keyInit,
    .read = keyRead,
};

static int keyInit(void)
{
    return SUCESS;
}

static int keyRead(char *_name)
{
    BspKey *bspKey = getKey(_name);
    if (bspKey == NULL)
        return NULLDEV;
    if (bspKey->read(*bspKey) == 1)
        return 1;
    return 0;
}

Key *createKeyObject(void)
{
    Key *kedObject = (Key *)malloc(sizeof(Key));
    if (kedObject == NULL)
        return NULL;
    *kedObject = key;
    return kedObject;
    // return &key;
}
