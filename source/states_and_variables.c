#include "states_and_variables.h"


void recieve_elevator_data(elevator *elevator) {
    recieve_button_data(elevator);
    recieve_sensor_data(elevator);
}

void calculate_elevator_data(elevator *elevator){
    calculate_queue_data(elevator);
    calculate_primary_elevator_state(elevator);
    //maybe we need to add a calculate primary_state data. 
    //Or maybe that variable is directly calculated in calculate_motor_data(..)
    calculate_motor_data(elevator);
    calculate_lights_data(elevator);

}

void send_elevator_data(elevator *elevator){
    send_motor_data(elevator);
    send_lights_data(elevator);
}

void init_elevator(elevator *elevator){
    recieve_elevator_data(elevator);
    elevator->motor_direction = 0;
    elevator->timer = 0;
    elevator->queue_next_floor_target = -1; //set an invalid target
    elevator->elevator_state = INITIALIZING; 
    elevator->stop_between_floors = NOT_DETECTED;
    elevator->queue_is_headed_up = 1,
    init_queue(elevator); 
}

void detect_stop(elevator *elevator){
    if (elevator->elevator_state != INITIALIZING){

        if (elevator->sensor_stop_button == 1 && elevator->elevator_state != STOP){
            switch (elevator->motor_direction)
            {
            case DIRN_UP:
                elevator->stop_between_floors = OVER;
                break;
                
            case DIRN_DOWN:
                elevator->stop_between_floors = UNDER;
                break;
                
            case DIRN_STOP:
                elevator->stop_between_floors = NOT_DETECTED;
        
            }
            
            elevator->elevator_state = STOP;
        }        
    }
}


void calculate_primary_elevator_state(elevator *elevator){
    switch (elevator->elevator_state)
    {
    case WAIT:
        if (elevator->timer >= wait_time && elevator->sensor_obstruction == 0){
            elevator->timer = 0;
            elevator->elevator_state = IDLE;
        }else{
            elevator->timer += sleep_timestep;
        }
        break;

    case TRANSIT:
        if (elevator->sensor_floor_detected == elevator->queue_next_floor_target){
            elevator->stop_between_floors = NOT_DETECTED;
            elevator->elevator_state = WAIT;

        }
        break;

    case IDLE:
        if (elevator->queue_next_floor_target != -1){
            elevator->elevator_state = TRANSIT;
        }
        break;
    
    case INITIALIZING:
        if (elevator->sensor_floor_detected != -1){
            elevator->elevator_state = IDLE;
        }
        break;

    case STOP:
        if (elevator->sensor_stop_button == 0){
            switch (elevator->stop_between_floors)
            {
            case NOT_DETECTED:
                elevator->elevator_state = WAIT;
                break;
            
            default:
                elevator->elevator_state = IDLE;
                break;
            }
        }

        break;
    }
    
}