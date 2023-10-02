#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "stm32f4xx.h"

struct driver_pos {
    int16_t x;
    int16_t y;
};

void driver_x_offset(int32_t offset_mm);
void driver_y_offset(int32_t offset_mm);
void driver_x_stop(void);
void driver_y_stop(void);
void driver_stop(void);
void driver_x_set_k(uint32_t k_mov2step);
void driver_y_set_k(uint32_t k_mov2step);
void driver_x_set_vel(uint32_t velocity);
void driver_y_set_vel(uint32_t velocity);
void driver_x_tick(void);
void driver_y_tick(void);
struct driver_pos driver_get_pos(void);
void driver_origin(void);

#endif
