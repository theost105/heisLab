#pragma once
#include "states_and_variables.h"
#include "driver/elevio.h"

typedef struct elevator elevator;

void calculate_lights_data(elevator *elevator);

void send_lights_data(elevator *elevator);