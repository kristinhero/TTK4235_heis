/**
 * @file
 * @brief Functions to handle events in finite state machine, based on current state.
 */
#ifndef FSM_H
#define FSM_H
#include "hardware.h"
#include "orders.h"
#include "fsm_types.h"
#include "timer.h"


/**
 * @brief Initialize elevator and change state to @c FSM_Initialize
 */
void fsm_initialize();

/**
 * @brief A @p floor has been reached. Update current floor and check if state should be changed.
 * 
 * @param[in] floor
 */
void fsm_floor_reached(int floor);

/**
 * @brief A new order at @p floor of type @p order_type has been registered. 
 * Check if order should be handled and if state should be changed.
 * 
 * @param[in] floor
 * @param[in] order_type 
 */
void fsm_new_order(int floor, HardwareOrder order_type);

/**
 * @brief The timer has timed out. 
 * If current state is @c FSM_OPEN, close door and change state.
 */
void fsm_timeout();

/**
 * @brief An obstruction has been detected. 
 * If current state is @c FSM_OPEN, keep door open.
 */
void fsm_obstruction_detected();

/**
 * @brief The stop button has been pressed. 
 * Stop all motion, delete orders and change state. If elevator is at a floor, open door.
 */
void fsm_stop_pressed();

/**
 * @brief The stop button has been released.
 * If current state is @c FSM_STOP, change state.
 */
void fsm_stop_released();

#endif