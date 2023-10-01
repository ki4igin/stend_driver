
#include "tim.h"

void MX_TIM10_Init(void)
{
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM10);

    NVIC_SetPriority(TIM1_UP_TIM10_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);

    LL_TIM_InitTypeDef TIM_InitStruct = {
        .Prescaler = 2 - 1,
        .CounterMode = LL_TIM_COUNTERMODE_UP,
        .Autoreload = 42000 - 1,
        .ClockDivision = LL_TIM_CLOCKDIVISION_DIV1,
    };
    LL_TIM_Init(TIM10, &TIM_InitStruct);
    LL_TIM_EnableARRPreload(TIM10);
    LL_TIM_EnableIT_UPDATE(TIM10);
}

void MX_TIM3_Init(void)
{
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
    /**TIM3 GPIO Configuration
    PB4     ------> TIM3_CH1
    */
    LL_GPIO_Init(DR_GPIO_Port,
                 &(LL_GPIO_InitTypeDef){
                     .Pin = DR1_STEP_Pin,
                     .Mode = LL_GPIO_MODE_ALTERNATE,
                     .Speed = LL_GPIO_SPEED_FREQ_LOW,
                     .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
                     .Pull = LL_GPIO_PULL_NO,
                     .Alternate = LL_GPIO_AF_2,
                 });

    /* Peripheral clock enable */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
    /* TIM3 interrupt Init */
    NVIC_SetPriority(TIM3_IRQn,
                     NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(TIM3_IRQn);

    LL_TIM_Init(TIM3, &(LL_TIM_InitTypeDef){
                          .Prescaler = 0,
                          .CounterMode = LL_TIM_COUNTERMODE_UP,
                          .Autoreload = 65535,
                          .ClockDivision = LL_TIM_CLOCKDIVISION_DIV1,
                      });
    LL_TIM_DisableARRPreload(TIM3);
    LL_TIM_SetClockSource(TIM3, LL_TIM_CLOCKSOURCE_INTERNAL);
    LL_TIM_OC_EnablePreload(TIM3, LL_TIM_CHANNEL_CH1);

    LL_TIM_OC_Init(TIM3, LL_TIM_CHANNEL_CH1,
                   &(LL_TIM_OC_InitTypeDef){
                       .OCMode = LL_TIM_OCMODE_PWM2,
                       .OCState = LL_TIM_OCSTATE_DISABLE,
                       .OCNState = LL_TIM_OCSTATE_DISABLE,
                       .CompareValue = 65536 / 2 - 1,
                       .OCPolarity = LL_TIM_OCPOLARITY_HIGH,
                   });
    LL_TIM_OC_DisableFast(TIM3, LL_TIM_CHANNEL_CH1);
    LL_TIM_SetTriggerOutput(TIM3, LL_TIM_TRGO_RESET);
    LL_TIM_DisableMasterSlaveMode(TIM3);
    LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH1);
    LL_TIM_EnableIT_UPDATE(TIM3);    
}

void MX_TIM4_Init(void)
{
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
    /**TIM4 GPIO Configuration
     PB7     ------> TIM4_CH2
    */
    LL_GPIO_Init(DR_GPIO_Port,
                 &(LL_GPIO_InitTypeDef){
                     .Pin = DR2_STEP_Pin,
                     .Mode = LL_GPIO_MODE_ALTERNATE,
                     .Speed = LL_GPIO_SPEED_FREQ_LOW,
                     .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
                     .Pull = LL_GPIO_PULL_NO,
                     .Alternate = LL_GPIO_AF_2,
                 });

    /* Peripheral clock enable */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
    /* TIM4 interrupt Init */
    NVIC_SetPriority(TIM4_IRQn,
                     NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(TIM4_IRQn);

    LL_TIM_Init(TIM4, &(LL_TIM_InitTypeDef){
                          .Prescaler = 0,
                          .CounterMode = LL_TIM_COUNTERMODE_UP,
                          .Autoreload = 65535,
                          .ClockDivision = LL_TIM_CLOCKDIVISION_DIV1,
                      });
    LL_TIM_DisableARRPreload(TIM4);
    LL_TIM_SetClockSource(TIM4, LL_TIM_CLOCKSOURCE_INTERNAL);
    LL_TIM_OC_EnablePreload(TIM4, LL_TIM_CHANNEL_CH2);

    LL_TIM_OC_Init(TIM4, LL_TIM_CHANNEL_CH2,
                   &(LL_TIM_OC_InitTypeDef){
                       .OCMode = LL_TIM_OCMODE_PWM2,
                       .OCState = LL_TIM_OCSTATE_DISABLE,
                       .OCNState = LL_TIM_OCSTATE_DISABLE,
                       .CompareValue = 65536 / 2 - 1,
                       .OCPolarity = LL_TIM_OCPOLARITY_HIGH,
                   });
    LL_TIM_OC_DisableFast(TIM4, LL_TIM_CHANNEL_CH2);
    LL_TIM_SetTriggerOutput(TIM4, LL_TIM_TRGO_RESET);
    LL_TIM_DisableMasterSlaveMode(TIM4);    
    LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH2);
    LL_TIM_EnableIT_UPDATE(TIM4);
}

void MX_TIM11_Init(void)
{
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM11);

    NVIC_SetPriority(TIM1_TRG_COM_TIM11_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);

    LL_TIM_InitTypeDef TIM_InitStruct = {
        .Prescaler = 84 - 1,
        .CounterMode = LL_TIM_COUNTERMODE_UP,
        .Autoreload = 400 - 1,
        .ClockDivision = LL_TIM_CLOCKDIVISION_DIV1,
    };
    LL_TIM_Init(TIM11, &TIM_InitStruct);
    LL_TIM_EnableARRPreload(TIM11);
    LL_TIM_EnableIT_UPDATE(TIM11);
}
