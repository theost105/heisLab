#pragma once
#include "states_and_variables.h"

void calculate_queue_data(elevator *elevator);

void add_queue_orders(elevator *elevator);
void clear_finished_queue_orders(elevator *elevator);

void calculate_direction_and_next_floor_target(elevator *elevator);

