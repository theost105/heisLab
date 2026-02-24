#include "lights.h"


void calculate_lights_data(elevator *elevator){
    //Defaults:
    elevator->lights_indoor_door_open = 0;
    elevator->lights_stop = 0;
    
    switch (elevator->elevator_state)
    {
    case WAIT:
        elevator->lights_indoor_door_open = 1;
        break;
    
    case TRANSIT:
        /* code */
        break;
    
    case IDLE:
        /* code */
        break;
    
    case INITIALIZING:
        /* code */
        break;
    
    case STOP:
        elevator->lights_stop = 1;
        break;
    }
    
    //queue light logic. Order buttons etc:

    // elevator->queue_list_1st_priority = elevator->lights_indoor_floor;
    for (int floor = 1; floor <= N_FLOORS; floor++){
        elevator->lights_indoor_floor[floor] = elevator->queue_list_1st_priority[floor];
        elevator->lights_outdoor_button[floor][0] = elevator->queue_list_2nd_priority[floor][0];
        elevator->lights_outdoor_button[floor][1] = elevator->queue_list_2nd_priority[floor][1];
    }

}

void send_lights_data(elevator *elevator){
    
    
    
    elevio_stopLamp(elevator->lights_stop);

    elevio_doorOpenLamp(elevator->lights_indoor_door_open);
    
    
    
    if (elevator->last_floor_detected != -1){
        /// lights_outdoor_floor is not in use. Test if this works.
        // TEST: Will only one outdoor floot indicator light be active at once?
        elevio_floorIndicator(elevator->last_floor_detected); 
    } else {
        elevio_floorIndicator(1); //Might be bad solution. If possible set to nothing
    }

    //indoor floor button lights
    for (int floor = 1; floor <= N_FLOORS; floor++){
        elevio_buttonLamp(floor, BUTTON_CAB, elevator->lights_indoor_floor[floor]);        
    }
    //outdoor up button lights
    for (int floor = 1; floor < N_FLOORS; floor++){
        elevio_buttonLamp(floor, BUTTON_HALL_UP, elevator->lights_outdoor_button[floor][0]);        
    }
    //outdoor down button lights
    for (int floor = 2; floor <= N_FLOORS; floor++){
        elevio_buttonLamp(floor, BUTTON_HALL_DOWN, elevator->lights_outdoor_button[floor][1]);        
    }

    



    /*
    
    void elevio_buttonLamp(int floor, ButtonType button, int value);
    void elevio_floorIndicator(int floor); // can not use floor = -1
    
    
    void elevio_doorOpenLamp(int value);
    void elevio_stopLamp(int value);
    */

    /*
    int lights_indoor_floor[N_FLOORS + 1]; // 1 = true, 0 = false
    int lights_indoor_door_open;
    int lights_stop;

    int lights_outdoor_floor[N_FLOORS + 1]; // only one of these should be active
    
    //outdoor light buttons
    int lights_outdoor_button[N_FLOORS + 1][2]; // floor, (up, down). 
        //lights_outdoor[1][0] = 1 says floor 1, up button light is active
        //lights_outdoor[4][1] = 1 says floor 4, down button light is active
        //invalid buttons should have the value -1
    
    */

}

