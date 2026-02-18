#include "buttons_and_sensors.h"


void recieve_button_data(elevator *elevator){
    
    elevator->sensor_stop_button = elevio_stopButton();

    /////
    // TO DO: update these variables
    /*
    int sensor_indoor_order_floor_button[N_FLOORS + 1]; //sensor_indoor_order_floor_button[1] is floor 1

    int sensor_outdoor_button[N_FLOORS + 1][2];
    */
}

void recieve_sensor_data(elevator *elevator){
    elevator->sensor_obstruction = elevio_obstruction();
    
    int detected_floor = elevio_floorSensor();

    elevator->sensor_floor_detected = detected_floor;

    if (detected_floor != -1){
        elevator->last_floor_detected = detected_floor;
    }
    
    
}