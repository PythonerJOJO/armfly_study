/**
 ******************************************************************************
 * @file:  common_inc.h
 * @brief: Header for common_inc.c file.
 *
 ******************************************************************************
 * @attention
 */
#ifndef __COMMON_INC_H
#define __COMMON_INC_H
/********************** std库 ******************/
#include <stdint.h>
#include <string.h>
// #include "bsp_key/bsp_key.h"
#include "gpio.h"
#include "usart.h"

// #include "bsp.h"
#include "led/led.h"

/*************** 测试 *****************/
#include "bsp_test.h"

/********* bsp层测试 ******/
#include "bsp_uart/bsp_uart.h"

void Main(void);

/********************* callback *******************/

void OnUartCmd(uint8_t *_data, uint16_t _len);

/*********** 调试数据 ****************/

#endif /* __COMMON_INC_H */