/**
 ******************************************************************************
 * @file:  bsp_config.h
 * @brief: Header for bsp_config.c file.
 *
 ******************************************************************************
 * @attention
 */
#ifndef __BSP_CONFIG_H
#define __BSP_CONFIG_H

#include "error.h"

#define LED_NUM 1 // LED数量
#define KEY_NUM 2 // KEY数量

#define UART_NUM 1           // UART数量
#define UART_TX_BUF_SIZE 128 // UART发送缓冲区大小
#define UART_RX_BUF_SIZE 128 // UART接收缓冲区大小

#define USART_NUM 0 // USART数量

#define I2C_NUM 0 // I2C数量
#define SPI_NUM 0 // SPI数量

#endif /* __BSP_CONFIG_H */