/**
 ******************************************************************************
 * @file: callback.c
 * @brief:  Header for callback.c file.
 *
 ******************************************************************************
 * @attention
 */
#include "common_inc.h"

// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
// {
//     if (huart->Instance == USART1)
//     {
//         printf("USART1_RxCpltCallback\r\n");
//     }
// }

/**
 * @brief 串口命令自定义函数
 *          使用 dev_uart 设置回调函数为这个
 *
 */
void OnUartCmd(uint8_t *_data, uint16_t _len)
{
    switch (_data[0])
    {
    case 'a':
        /* code */
        break;
    case 'b':
        break;
    default:
        // 发送存在一些什么命令
        break;
    }
}