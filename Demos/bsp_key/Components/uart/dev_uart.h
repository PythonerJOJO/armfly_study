/**
 ******************************************************************************
 * @file:  dev_uart.h
 * @brief: Header for dev_uart.c file.
 *
 ******************************************************************************
 * @attention
 */
#ifndef __DEV_UART_H
#define __DEV_UART_H

#include "bsp_uart/bsp_uart.h"

typedef struct
{
    int (*init)(void); // 在初始化时设置回调函数

    int (*sendMsgByString)(char *data);
    int (*sendMsgByUint32_t)(uint32_t data);
    int (*sendDataByArr)(uint8_t *, int len);

    void *privateData;
} D_Uart;

#endif /* __DEV_UART_H */