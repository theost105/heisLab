
void update_button_variables(elevator *elevator){
    elevator->sensor_obstruction = elevio_obstruction();
    elevator->sensor_stop_button = elevio_stopButton();
    
}






void recieve_elevator_variables(elevator *elevator){
    update_button_variables();

    int detected_floor = elevio_floorSensor();
    if (floor != -1){
        elevator->last_floor_detected = enum floor(detected_floor)
    }


}

