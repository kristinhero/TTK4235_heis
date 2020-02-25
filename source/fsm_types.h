#ifndef FSM_TYPES_H
#define FSM_TYPES_H

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

typedef enum {
    FSM_DIRECTION_UP,
    FSM_DIRECTION_DOWN
} FSMDirection;

#endif