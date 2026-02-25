#include "buttons_and_sensors.h"


void recieve_button_data(elevator *elevator){
    
    elevator->sensor_stop_button = elevio_stopButton();

    //up buttons
    for (int floor = 1; floor < N_FLOORS; floor++){        
        elevator->sensor_outdoor_button[floor][0] = elevio_callButton(floor-1, BUTTON_HALL_UP);
    }

    //down buttons
    for (int floor = 1; floor < N_FLOORS; floor++){        
        elevator->sensor_outdoor_button[floor][1] = elevio_callButton(floor-1, BUTTON_HALL_DOWN);
    }

    //order buttons
    for (int floor = 1; floor <= N_FLOORS; floor++){        
        elevator->sensor_indoor_order_floor_button[floor] = elevio_callButton(floor-1, BUTTON_CAB);
    }
    

}

void recieve_sensor_data(elevator *elevator){
    elevator->sensor_obstruction = elevio_obstruction();
    
    int detected_floor = elevio_floorSensor();

    elevator->sensor_floor_detected = detected_floor + 1;

    if (detected_floor != -1){//shift to account for index diffrences in elevator and drivers
        elevator->last_floor_detected = detected_floor;
    }
    
    
}
