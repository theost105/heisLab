#include "motor.h"

void calculate_motor_data(elevator *elevator){
    switch (elevator->elevator_state)
    {
    case WAIT:
        elevator->motor_direction = DIRN_STOP;
        break;

    case TRANSIT:

        //EDGE CASE HANDELING. If an elevator is emergency stopped over/under the floor you want to go to
        if (elevator->queue_next_floor_target == elevator->queue_next_floor_target){
            switch (elevator->stop_between_floors)
            {
            case UNDER:
                elevator->motor_direction = DIRN_UP;
                break;
            
            case OVER:
                elevator->motor_direction = DIRN_DOWN;
                break;
            }
        }
        // ^^ EDGE CASE HANDELING ^^

        else{
            if (elevator->queue_next_floor_target - elevator->last_floor_detected > 0){
                elevator->motor_direction = DIRN_UP;
            }else{
                elevator->motor_direction = DIRN_DOWN;
            }
        }
        break;
    
    case IDLE:
        elevator->motor_direction = DIRN_STOP;    
        break;

    case INITIALIZING:
        elevator->motor_direction = DIRN_UP;
        break;    
    
    case STOP:
        elevator->motor_direction = DIRN_STOP;
        break;
    }
    
}



void send_motor_data(elevator *elevator){
    elevio_motorDirection(elevator->motor_direction);
}