/**
 ******************************************************************************
 * @file:  bsp_uart.h
 * @brief: Header for bsp_uart.c file.
 *
 ******************************************************************************
 * @attention
 */
#ifndef __BSP_UART_H
#define __BSP_UART_H

#include <stdint.h>
#include "bsp_config.h"

#include "usart.h"

typedef struct bsp_uart
{
    char *name;

    int (*init)(struct bsp_uart _uart);
    int (*write)(struct bsp_uart _uart, uint8_t *_txData, uint16_t _len);

    // uint16_t (*setSendBefore)(void (*_callback)(uint8_t *, uint16_t *));

    /***********  这些函数在dev层的init再定义 *********************/
    // 发送前回调函数指针(用于发送前，处理数据格式)
    uint16_t (*setSendBefore)(void (*_callback)(void));
    // 发送后回调函数指针(用于发送完成后回调)
    uint16_t (*setSendAfter)(void (*_callback)(uint8_t *, uint16_t *));

    // 接收新字节回调函数指针(用于接收后，处理接收到的命令)
    uint16_t (*setReciveCallBack)(void (*_callback)(uint8_t *, uint16_t *));

    void *privateData;
} BspUart;

BspUart getUart(char *_name);

// 给stm32f4xx_it.c使用的函数
void USER_UART1_IRQHandler(UART_HandleTypeDef *huart);

#endif /* __BSP_UART_H */