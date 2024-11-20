#our code in order to activate solenoids using an internal timer. 

#include "stm32f4xx_hal.h"

// Function prototypes
void SystemClock_Config(void);
void Error_Handler(void);
void GPIO_Init(void);

int main(void) {
    // Initialize the HAL Library
    HAL_Init();

    // Configure the system clock
    SystemClock_Config();

    // Initialize GPIO pins for solenoids
    GPIO_Init();

    // Main loop
    while (1) {
        // Example: Toggle solenoids on D2-D7 every second
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_10); // Toggle D2
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);  // Toggle D3
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);  // Toggle D4
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_4);  // Toggle D5
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10); // Toggle D6
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);  // Toggle D7

        HAL_Delay(1000); // Wait for 1 second
    }
}

// GPIO Initialization Function
void GPIO_Init(void) {
    // GPIO Initialization structure
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable GPIOA and GPIOB clocks
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // Configure D2 (PA10) as GPIO Output
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Configure D3, D4, D5, D6 (PB3, PB5, PB4, PB10) as GPIO Output
    GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_10;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Configure D7 (PA8) as GPIO Output
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// System Clock Configuration
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    // Configure the main internal regulator output voltage
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    // Initialize the RCC Oscillators
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    // Configure the clocks
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }
}

// Error Handler
void Error_Handler(void) {
    while (1) {
        // Stay here
    }
}
