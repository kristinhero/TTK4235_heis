#ifndef FSM_H
#define FSM_H
#include "hardware.h"
#include "orders.h"
#include "utilities.h"
#include "timer.h"

typedef enum {
    FSM_INITIALIZE,
    FSM_IDLE,
    FSM_MOVING,
    FSM_OPEN,
    FSM_STOP
} FSMState;

void fsm_move();
void fsm_initialize();
void fsm_floor_reached();
void fsm_timeout();
void fsm_new_order(int floor, HardwareOrder order_type);
void fsm_stop_pressed();
void fsm_stop_released();
void fsm_obstruction_detected();
void fsm_obstruction_removed();

#endif