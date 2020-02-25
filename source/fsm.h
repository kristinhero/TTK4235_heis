#ifndef FSM_H
#define FSM_H
#include "hardware.h"
#include "orders.h"
#include "direction.h"
#include "timer.h"

typedef enum {
    FSM_INITIALIZE,
    FSM_IDLE,
    FSM_MOVING,
    FSM_OPEN,
    FSM_STOP
} FSMState;

typedef struct {
    int floor;
    int above;
} FSMPosition;

void fsm_initialize();
void fsm_floor_reached();
void fsm_new_order(int floor, HardwareOrder order_type);
void fsm_timeout();
void fsm_obstruction_detected();
void fsm_stop_pressed();
void fsm_stop_released();

#endif