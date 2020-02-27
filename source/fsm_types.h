/**
 * @file
 * @brief Struct and enums for the finite state machine
 */
#ifndef FSM_TYPES_H
#define FSM_TYPES_H


/**
 * @brief Elevator states used in @c fsm.c.
 */
typedef enum {
    FSM_INITIALIZE,
    FSM_IDLE,
    FSM_MOVING,
    FSM_OPEN,
    FSM_STOP
} FSMState;

/**
 * @brief Elevator position used in @c fsm.c
 * 
 * @c above is 1 if the elevator is above the current @c floor; 0 if the elevator is at the floor.
 */
typedef struct {
    int floor;
    int above;
} FSMPosition;

/**
 * @brief Elevator direction used in @c fsm.c 
 * and @c orders.c
 */
typedef enum {
    FSM_DIRECTION_UP,
    FSM_DIRECTION_DOWN
} FSMDirection;

#endif