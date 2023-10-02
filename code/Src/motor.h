#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "stm32f4xx.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_tim.h"

struct gpio {
    GPIO_TypeDef *port;
    uint32_t pin;
};

struct motor {
    struct gpio gpio_dir;
    int32_t pos_step;
    int32_t offset_step;
    uint32_t k_mov2step;
    TIM_TypeDef *tim_inst;
    volatile uint32_t *const ccr;
};

inline static void motor_offset(struct motor *s, int32_t offset_mm)
{
    s->offset_step += offset_mm * s->k_mov2step;
    if (s->offset_step == 0) {
        return;
    } else if (s->offset_step > 0) {
        LL_GPIO_SetOutputPin(s->gpio_dir.port, s->gpio_dir.pin);
    } else {
        LL_GPIO_ResetOutputPin(s->gpio_dir.port, s->gpio_dir.pin);
    }
    LL_TIM_EnableCounter(s->tim_inst);
}

inline static int32_t motor_get_pos(struct motor *s)
{
    return s->pos_step / s->k_mov2step;
}

inline static void motor_set_velocity(struct motor *s, uint32_t vel_papugay)
{
    if (LL_TIM_IsEnabledCounter(s->tim_inst)) {
        return;
    }
    if (vel_papugay < 1000) {
        vel_papugay = 1000;
    }

    *s->ccr = vel_papugay / 2;
    LL_TIM_SetAutoReload(s->tim_inst, vel_papugay);
}

inline static void motor_set_origin(struct motor *s)
{
    s->pos_step = 0;
}

inline static void motor_mov_process(struct motor *s)
{
    if (s->offset_step > 0) {
        LL_GPIO_SetOutputPin(s->gpio_dir.port, s->gpio_dir.pin);
        s->offset_step--;
        s->pos_step++;
    } else if (s->offset_step < 0) {
        LL_GPIO_ResetOutputPin(s->gpio_dir.port, s->gpio_dir.pin);
        s->offset_step++;
        s->pos_step--;
    } else {
        LL_TIM_DisableCounter(s->tim_inst);
    }
}

inline static void motor_stop(struct motor *s)
{
    s->offset_step = 0;
}

#endif
