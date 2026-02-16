void recieve_elevator_variables(elevator *elevator){
    // update_button_variables();

    int detected_floor = elevio_floorSensor();
    if (floor != -1){
        elevator->last_floor_detected = enum floor(detected_floor)
    }
    

}

