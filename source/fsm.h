#ifndef FSM_H
#define FSM_H
#include "hardware.h"
#include "orders.h"
#include "fsm_types.h"
#include "timer.h"

void fsm_initialize();
void fsm_floor_reached();
void fsm_new_order(int floor, HardwareOrder order_type);
void fsm_timeout();
void fsm_obstruction_detected();
void fsm_stop_pressed();
void fsm_stop_released();

#endif