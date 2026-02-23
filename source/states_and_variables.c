#include "states_and_variables.h"


void recieve_elevator_data(elevator *elevator) {
    recieve_button_data(elevator);
    recieve_sensor_data(elevator);
}

void calculate_elevator_data(elevator *elevator){
    calculate_queue_data(elevator);
    calculate_primary_state(elevator);
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
    elevator->primary_state = INITIALIZING; //unsure about this.
}


void calculate_primary_elevator_state(elevator *elevator){

        //besttemer elevator_state

state_variables_lights_and_motor

-> send_motor_Data 
-> send_light_data 




switch 

switch elevator_state{

    case Wait:
    if timer == 3s and obstruction == 0:

    else:
        dooropen = true
        timer += 20 ms

    
    else:
        last_floor
        motor_dir = up 
}

}