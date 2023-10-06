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

    struct {
        TIM_TypeDef *inst;
        volatile uint32_t *const ccr;
    } tim;

    struct {
        uint16_t req_change;
        uint16_t value;
    } velocity;
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
    LL_TIM_EnableCounter(s->tim.inst);
}

inline static int32_t motor_get_pos(struct motor *s)
{
    return s->pos_step / s->k_mov2step;
}

inline static int32_t motor_get_offset(struct motor *s)
{
    return s->offset_step / s->k_mov2step;
}

inline static void motor_set_velocity(struct motor *s, uint32_t vel_papugay)
{
    if (vel_papugay < 1000) {
        vel_papugay = 1000;
    }
    if (LL_TIM_IsEnabledCounter(s->tim.inst)) {
        s->velocity.req_change = 1;
        s->velocity.value = vel_papugay;
        return;
    }

    *s->tim.ccr = vel_papugay / 2;
    LL_TIM_SetAutoReload(s->tim.inst, vel_papugay);
}

inline static void motor_set_origin(struct motor *s)
{
    s->pos_step = 0;
}

inline static void motor_mov_process(struct motor *s)
{
    if (s->velocity.req_change) {
        s->velocity.req_change = 0;
        *s->tim.ccr = s->velocity.value / 2;
        LL_TIM_SetAutoReload(s->tim.inst, s->velocity.value);
    }

    if (s->offset_step > 0) {
        LL_GPIO_SetOutputPin(s->gpio_dir.port, s->gpio_dir.pin);
        s->offset_step--;
        s->pos_step++;
    } else if (s->offset_step < 0) {
        LL_GPIO_ResetOutputPin(s->gpio_dir.port, s->gpio_dir.pin);
        s->offset_step++;
        s->pos_step--;
    } else {
        LL_TIM_DisableCounter(s->tim.inst);
    }
}

inline static void motor_stop(struct motor *s)
{
    s->offset_step = 0;
}

#endif
