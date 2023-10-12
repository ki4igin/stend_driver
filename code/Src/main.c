#include "main.h"
#include "tim.h"
#include "uart.h"
#include "gpio.h"
#include "driver.h"

void SystemClock_Config(void);

enum cmd_id {
    CMD_RESET = 1,
    CMD_TEST = 2,
    CMD_LED_TOGGLE,
    CMD_X_SET_K,
    CMD_Y_SET_K,
    CMD_SET_ORIGIN,
    CMD_STOP,
    CMD_X_STOP,
    CMD_Y_STOP,
    CMD_X_OFFSET,
    CMD_Y_OFFSET,
    CMD_X_GET_POS,
    CMD_Y_GET_POS,
    CMD_GET_POS,
    CMD_X_GET_OFFSET,
    CMD_Y_GET_OFFSET,
    CMD_GET_OFFSET,
    CMD_X_SET_VEL,
    CMD_Y_SET_VEL,
};

struct cmd {
    uint16_t id;
    int16_t arg;
};

struct cmd_ex {
    uint16_t id;
    int16_t arg[2];
};

static void cmd_work(struct cmd cmd)
{
    switch (cmd.id) {
    case CMD_RESET: {
        NVIC_SystemReset();
    } break;
    case CMD_TEST: {
        cmd.arg = 0x0C0C;
        UART_Send_Array(&cmd, sizeof(cmd));
    } break;
    case CMD_STOP: {
        driver_stop();
    } break;
    case CMD_X_STOP: {
        driver_x_stop();
    } break;
    case CMD_Y_STOP: {
        driver_y_stop();
    } break;
    case CMD_LED_TOGGLE: {
        gpio_led_toggle();
    } break;
    case CMD_X_OFFSET: {
        driver_x_offset(cmd.arg);
    } break;
    case CMD_Y_OFFSET: {
        driver_y_offset(cmd.arg);
    } break;
    case CMD_X_SET_K: {
        driver_x_set_k(cmd.arg);
    } break;
    case CMD_Y_SET_K: {
        driver_y_set_k(cmd.arg);
    } break;
    case CMD_X_GET_POS: {
        cmd.arg = driver_get_pos().x;
        UART_Send_Array(&cmd, sizeof(cmd));
    } break;
    case CMD_Y_GET_POS: {
        cmd.arg = driver_get_pos().y;
        UART_Send_Array(&cmd, sizeof(cmd));
    } break;
    case CMD_GET_POS: {
        struct cmd_ex cmd_ex = {
            .id = CMD_GET_POS,
            .arg[0] = driver_get_pos().x,
            .arg[1] = driver_get_pos().y,
        };
        UART_Send_Array(&cmd_ex, sizeof(cmd_ex));
    } break;
    case CMD_X_GET_OFFSET: {
        cmd.arg = driver_get_offset().x;
        UART_Send_Array(&cmd, sizeof(cmd));
    } break;
    case CMD_Y_GET_OFFSET: {
        cmd.arg = driver_get_offset().y;
        UART_Send_Array(&cmd, sizeof(cmd));
    } break;
    case CMD_GET_OFFSET: {
        struct cmd_ex cmd_ex = {
            .id = CMD_GET_OFFSET,
            .arg[0] = driver_get_offset().x,
            .arg[1] = driver_get_offset().y,
        };
        UART_Send_Array(&cmd_ex, sizeof(cmd_ex));
    } break;
    case CMD_X_SET_VEL: {
        driver_x_set_vel(cmd.arg);
    } break;
    case CMD_Y_SET_VEL: {
        driver_y_set_vel(cmd.arg);
    } break;
    case CMD_SET_ORIGIN: {
        driver_origin();
    } break;

    default:
        break;
    }
}

int main(void)
{
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

    NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    NVIC_SetPriority(SysTick_IRQn,
                     NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 15, 0));

    SystemClock_Config();

    MX_GPIO_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();
    MX_TIM10_Init();
    MX_TIM11_Init();
    UART_Init();

    LL_TIM_EnableCounter(TIM10);

    while (1) {
        static uint32_t led_cnt = 0;
        if (led_cnt++ > 0x7FFFFF) {
            led_cnt = 0;
            gpio_led_toggle();
        }

        if (uart_rx.is_new_data) {
            uart_rx.is_new_data = 0;
            struct cmd cmd = *(struct cmd *)&uart_rx.data;
            cmd_work(cmd);
        }
    }
}

void SystemClock_Config(void)
{
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
    while (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2) {
    }
    LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE2);
    LL_RCC_HSE_Enable();

    /* Wait till HSE is ready */
    while (LL_RCC_HSE_IsReady() != 1) {
    }
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 336,
                                LL_RCC_PLLP_DIV_4);
    LL_RCC_PLL_Enable();

    /* Wait till PLL is ready */
    while (LL_RCC_PLL_IsReady() != 1) {
    }
    while (LL_PWR_IsActiveFlag_VOS() == 0) {
    }
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

    /* Wait till System clock is ready */
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) {
    }
    LL_Init1msTick(84000000);
    LL_SetSystemCoreClock(84000000);
    LL_RCC_SetTIMPrescaler(LL_RCC_TIM_PRESCALER_TWICE);
}

void Error_Handler(void)
{
    __disable_irq();
    while (1) {
    }
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */
