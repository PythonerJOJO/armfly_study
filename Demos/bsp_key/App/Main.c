#include "common_inc.h"

void Main(void)
{
    Led *led = NULL;
    BspUart uart = {0};

    // bsp_init();
    // led_test();
    led = createLedObject();

    uart = getUart("uart1");
    uart.init(uart);

    led->on("LED1");
    HAL_Delay(1000);
    led->toggle("LED1");
    HAL_Delay(1000);
    led->toggle("LED1");
    HAL_Delay(1000);
    led->toggle("LED1");
    HAL_Delay(1000);
    led->toggle("LED1");
    HAL_Delay(1000);

    // key_test();
    // char tx_arr[] = "Hello\n";
    while (1)
    {
        if (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == 0)
        {
            led->off("LED1");
        }
        else
        {
            led->on("LED1");
        }
        // HAL_UART_Transmit(&huart1, (uint8_t *)tx_arr, 8, 1000);
        HAL_Delay(10);
    }
}