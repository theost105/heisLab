#include "lights.h"


void calculate_lights_data(elevator *elevator){
    



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
    for (int floor = 1; floor <= N_FLOORS, floor++;){
        elevio_buttonLamp(floor, BUTTON_CAB, elevator->lights_indoor_floor[floor]);        
    }
    //outdoor up button lights
    for (int floor = 1; floor < N_FLOORS, floor++;){
        elevio_buttonLamp(floor, BUTTON_HALL_UP, elevator->lights_outdoor_button[floor][0]);        
    }

    //outdoor down button lights
    for (int floor = 2; floor <= N_FLOORS, floor++;){
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

