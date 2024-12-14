/**
 ******************************************************************************
 * @file: bsp_test.c
 * @brief:  Source for bsp_test.c file.
 *
 ******************************************************************************
 * @attention
 */
#include "common_inc.h"
#include "bsp_test.h"
#include "led/led.h"
// #include "key/key.h"

Led *led = NULL;
// Key *key = NULL;

void led_test(void)
{
    led = createLedObject();

    while (1)
    {
        led->toggle("LED1");
        // led->on("LED1");
        HAL_Delay(2000);
        // led->off("LED1");
        // HAL_Delay(2000);
    }
}

// void key_test(void)
// {
//     key = createKeyObject();
//     led->on("LED1");
//     HAL_Delay(500);
//     led->toggle("LED1");
//     HAL_Delay(500);
//     led->toggle("LED1");
//     HAL_Delay(500);
//     led->toggle("LED1");
//     HAL_Delay(500);
//     led->toggle("LED1");
//     HAL_Delay(500);
//     while (1)
//     {

//         if (key->read("Key1") == 0)
//         {
//             // led->toggle("LED1");
//             led->off("LED1");
//         }
//         else
//         {
//             led->on("LED1");
//         }
//         HAL_Delay(100);
//     }
// }

void uart_test(void)
{
    // HAL_UART_Receive_IT(&huart1, rxBuffer, 5);
    while (1)
    {
    }
}