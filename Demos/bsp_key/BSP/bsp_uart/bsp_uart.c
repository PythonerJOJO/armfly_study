/**
 ******************************************************************************
 * @file: bsp_uart.c
 * @brief:  Source for bsp_uart.c file.
 *
 ******************************************************************************
 * @attention
 */
#include "bsp_uart.h"

#include <string.h>

extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;

/****************** 私有函数定义区 **************/
static int bsp_uart1Init(struct bsp_uart _uart);
// int (*write)(struct bsp_uart _uart, uint8_t *_txData, uint16_t _len);
static int bsp_uart1Write(struct bsp_uart _uart, uint8_t *_txData, uint16_t _len);
typedef struct
{
    UART_HandleTypeDef *huart;
    DMA_HandleTypeDef *hdma_usart_rx;
    DMA_HandleTypeDef *hdma_usart_tx;

    uint8_t txBuf[UART_TX_BUF_SIZE]; // 发送FIFO
    uint8_t rxBuf[UART_RX_BUF_SIZE]; // 接收FIFO

    uint8_t *p_txBuf; // 发送缓冲区指针
    uint8_t *p_rxBuf; // 接收缓冲区指针
    uint16_t txSize;  // 发送缓冲区大小
    uint16_t rxSize;  // 接收缓冲区大小

    uint16_t fifoTxWrite; // 发送缓冲区写指针(FIFO模式下使用)
    uint16_t fifoTxRead;  // 发送缓冲区读指针(FIFO模式下使用)
    uint16_t fifoTxCount; // 等待发送的字节数(FIFO模式下使用)

    uint16_t fifoRxWrite; // 接收缓冲区写指针(FIFO模式下使用)
    uint16_t fifoRxRead;  // 接收缓冲区读指针(FIFO模式下使用)
    uint16_t fifoRxCount; // 等待接收的字节数(FIFO模式下使用)

    uint8_t sending; // 发送中标志位, 1 发送中, 0 空闲

} uartPrivateData;

static uartPrivateData uart1PrivateData = {
    .huart = &huart1,
    .hdma_usart_tx = &hdma_usart1_tx,
    .hdma_usart_rx = &hdma_usart1_rx,
    .txBuf = {0},
    .rxBuf = {0},
    // .p_rxBuf = rxBuf1,
    .txSize = UART_TX_BUF_SIZE,
    .rxSize = UART_RX_BUF_SIZE,

    .fifoTxWrite = 0,
    .fifoTxRead = 0,
    .fifoTxCount = 0,

    .fifoRxWrite = 0,
    .fifoRxRead = 0,
    .fifoRxCount = 0,

    .sending = 0,
};

BspUart bsp_uart[1] = {
    {
        .name = "uart1",
        .init = bsp_uart1Init,
        .write = bsp_uart1Write,
        .privateData = &uart1PrivateData,
    }};

/**************************** 结构体方法实现 ********************************/
static int bsp_uart1Init(struct bsp_uart _uart)
{
    uartPrivateData *privateData = _uart.privateData;
    __HAL_UART_ENABLE_IT(privateData->huart, UART_IT_IDLE); // 使能UART1的空闲(IDLE)中断
    HAL_UART_Receive_DMA(privateData->huart, privateData->rxBuf, sizeof(privateData->rxBuf) - 1);
    __HAL_UART_CLEAR_IDLEFLAG(&huart1);
    return 0;
}
static int bsp_uart1Write(struct bsp_uart _uart, uint8_t *_txData, uint16_t _len)
{
    uartPrivateData *privateData = _uart.privateData;
    // 先判断是否有空闲
    if (privateData->sending)
    {
        // privateData->txBuf[privateData->fifoTxWrite] = _txData;
        memcpy(privateData->txBuf + privateData->fifoTxWrite, _txData, _len);
        privateData->fifoTxCount += _len;
        privateData->fifoTxWrite += _len;
        return -1;
    }
    HAL_UART_Transmit_DMA(privateData->huart, _txData, _len);
    return 0;
}

/*********************** HAL库中断增配  ***********************/
static void USER_UART1_IDLECallback(UART_HandleTypeDef *huart);
/**
 * @brief Uart的全局触发中断.
 * @note    在void USART1_IRQHandler(void)中被调用
 */
void USER_UART1_IRQHandler(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        // 如果UART1处于空闲状态，则执行条件判断语句后面的代码块。
        if ((__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE) != RESET))
        {
            __HAL_UART_CLEAR_IDLEFLAG(&huart1);
            USER_UART1_IDLECallback(huart); // 调用用回调处理函数
        }
    }
}

/**
 * @brief Construct a new usar uart idlecallback object
 *
 */
static void USER_UART1_IDLECallback(UART_HandleTypeDef *huart)
{
    uartPrivateData *privateData = bsp_uart[0].privateData;
    privateData->fifoRxCount = UART_RX_BUF_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);
    /* 放执行命令的函数 */
    // privateData->sendAfter
    // 等有命令函数后删除这个发送函数
    HAL_UART_Transmit_DMA(&huart1, privateData->rxBuf, privateData->fifoRxCount);
    privateData->sending = 1;
}

/**
 * @brief 重写UART发送完成回调函数
 *
 * @param huart
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        uartPrivateData *privateData = bsp_uart[0].privateData;
        if (privateData->sending)
        {
            privateData->sending = 0;

            // 执行完后清除缓存区
            memset(privateData->rxBuf, 0, privateData->fifoRxCount);
            memset(privateData->txBuf, privateData->fifoTxWrite, privateData->fifoTxCount);
            privateData->fifoTxWrite -= privateData->fifoTxCount;
        }
    }
}
// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
// {
//     // uartPrivateData *p_uart = (uartPrivateData *)huart->Instance->pPrivate;
//     if (huart->Instance == USART1)
//     {
//         // if (p_uart->reciveNew)
//         // {
//         //     p_uart->reciveNew(huart->Instance->RDR);
//         // }
//     }
// }

/**************** get方法 ********************/
BspUart getUart(char *_name)
{
    for (int i = 0; i < sizeof(bsp_uart) / sizeof(bsp_uart[0]); i++)
    {
        if (strcmp(bsp_uart[i].name, _name) == 0)
        {
            // 能正确返回对象指针
            return bsp_uart[i];
        }
    }
    return bsp_uart[0];
}