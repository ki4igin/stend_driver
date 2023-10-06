#include "driver.h"
#include "main.h"
#include "motor.h"
#include "stm32f4xx_ll_gpio.h"

static struct motor x = {
    .gpio_dir = {DR_GPIO_Port, DR1_DIR_Pin},
    .tim.inst = TIM3,
    .tim.ccr = &TIM3->CCR1,
    .k_mov2step = 20,
};

static struct motor y = {
    .gpio_dir = {DR_GPIO_Port, DR2_DIR_Pin},
    .tim.inst = TIM4,
    .tim.ccr = &TIM4->CCR2,
    .k_mov2step = 20,
};

void driver_x_offset(int32_t offset_deg)
{
    motor_offset(&x, offset_deg);
}

void driver_y_offset(int32_t offset_deg)
{
    motor_offset(&y, offset_deg);
}

void driver_x_stop(void)
{
    motor_stop(&x);
}

void driver_y_stop(void)
{
    motor_stop(&y);
}

void driver_stop(void)
{
    motor_stop(&x);
    motor_stop(&y);
}

void driver_x_set_k(uint32_t k_mov2step)
{
    x.k_mov2step = k_mov2step;
}

void driver_y_set_k(uint32_t k_mov2step)
{
    y.k_mov2step = k_mov2step;
}

void driver_x_set_vel(uint32_t velocity)
{
    motor_set_velocity(&x, velocity);
}

void driver_y_set_vel(uint32_t velocity)
{
    motor_set_velocity(&y, velocity);
}

struct coords driver_get_pos(void)
{
    return (struct coords){
        .x = motor_get_pos(&x),
        .y = motor_get_pos(&y),
    };
}

struct coords driver_get_offset(void)
{
    return (struct coords){
        .x = motor_get_offset(&x),
        .y = motor_get_offset(&y),
    };
}

void driver_origin(void)
{
    motor_set_origin(&x);
    motor_set_origin(&y);
}

void driver_x_tick(void)
{
    motor_mov_process(&x);
}

void driver_y_tick(void)
{
    motor_mov_process(&y);
}
