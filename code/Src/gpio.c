#include "gpio.h"

void MX_GPIO_Init(void)
{
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOH);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

    LL_GPIO_ResetOutputPin(LED_GPIO_Port, LED_Pin);
    LL_GPIO_ResetOutputPin(USART1_DE_GPIO_Port, USART1_DE_Pin);
    LL_GPIO_ResetOutputPin(DR_GPIO_Port,
                           DR2_DIR_Pin | DR2_EN_Pin | DR1_DIR_Pin | DR1_EN_Pin);

    LL_GPIO_Init(LED_GPIO_Port,
                 &(LL_GPIO_InitTypeDef){
                     .Pin = LED_Pin,
                     .Mode = LL_GPIO_MODE_OUTPUT,
                     .Speed = LL_GPIO_SPEED_FREQ_LOW,
                     .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
                     .Pull = LL_GPIO_PULL_NO,
                 });
    LL_GPIO_Init(BTN_GPIO_Port,
                 &(LL_GPIO_InitTypeDef){
                     .Pin = BTN_Pin,
                     .Mode = LL_GPIO_MODE_INPUT,
                     .Pull = LL_GPIO_PULL_UP,
                 });
    LL_GPIO_Init(USART1_DE_GPIO_Port,
                 &(LL_GPIO_InitTypeDef){
                     .Pin = USART1_DE_Pin,
                     .Mode = LL_GPIO_MODE_OUTPUT,
                     .Speed = LL_GPIO_SPEED_FREQ_LOW,
                     .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
                     .Pull = LL_GPIO_PULL_NO,
                 });
    LL_GPIO_Init(DR_GPIO_Port,
                 &(LL_GPIO_InitTypeDef){
                     .Pin = DR2_DIR_Pin | DR2_EN_Pin | DR1_DIR_Pin | DR1_EN_Pin,
                     .Mode = LL_GPIO_MODE_OUTPUT,
                     .Speed = LL_GPIO_SPEED_FREQ_LOW,
                     .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
                     .Pull = LL_GPIO_PULL_NO,
                 });
    LL_GPIO_SetOutputPin(DR_GPIO_Port, DR1_EN_Pin | DR2_EN_Pin);
}
