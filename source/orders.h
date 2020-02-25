/**
 * @file
 * @brief Functions to collect, prioritize and delete orders.
 *  
 */
#ifndef ORDERS_H
#define ORDERS_H
#include "hardware.h"
#include "fsm_types.h"

/**
 * @brief Clear @c orders_matrix.
 * 
 */
void orders_clear_orders();

/**
 * @brief Check if @c orders_matrix is empty.
 * 
 * @return 1 if the order matrix is empty; 0 if it is not.
 */
int orders_empty();

/**
 * @brief Delete order at @p floor of type @p order_type from @c orders_matrix.
 * 
 * @param[in] floor
 * @param[in] order_type
 */
void orders_delete_order(int floor, HardwareOrder order_type);

/**
 * @brief Add order at @p floor of type @p order_type to @c orders_matrix.
 * 
 * @param[in] floor
 * @param[in] order_type
 */
void orders_add_order(int floor, HardwareOrder order_type);

/**
 * @brief Check @c orders_matrix for orders at @p floor matching the direction of the elevator.
 *
 * Matching orders are cab orders, orders of same direction or, if no matching orders at other floors, orders of opposite direction.
 * 
 * @param[in] floor Current floor of the elevator
 * @param[in] p_current_direction Current direction of the elevator
 * 
 * @return 1 if there are matching orders; 0 if there are none.
 */
int orders_to_handle(int floor, FSMDirection * p_current_direction);

/**
 * @brief Delete all orders at @p floor from @c orders_matrix.
 * 
 * @param[in] floor
 */
void orders_handled(int floor);

/**
 * @brief Change direction of elevator if there are no matching orders in @c orders_matrix.
 * 
 * Matching orders are orders above if current direction is up; orders below if current direction is down.
 * 
 * @param[in] floor Current floor of the elevator
 * @param[in, out] p_current_direction Current direction of the elevator
 */
void orders_get_direction(int floor, FSMDirection * p_current_direction);

#endif