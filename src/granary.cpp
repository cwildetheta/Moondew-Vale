#include "../include/granary.h"

granary::granary(int int_input, int store_input, int current_store_input, std::string string_input_array[], int int_input_array[], int cost_input, int upkeep_input, bool is_working_input)
{
    num_store_types = int_input;
    storage_space = store_input;
    current_total = current_store_input;
    for(int i = 0; i < num_store_types; i++){
        store_types[i] = string_input_array[i];
        store_totals[i] = int_input_array[i];
    }
    interact_cost(cost_input);
    interact_upkeep(upkeep_input);
    interact_is_working(is_working_input);
}
void granary::calculate_total()
{
    current_total = 0;
    for(int i = 0; i < num_store_types; i++){
        current_total = current_total + store_totals[i];
    }
}
void granary::increase_size(int int_input)
{
    storage_space = storage_space + int_input;
}
void granary::add_to_store(std::string string_input, int int_input)
{
    for(int i = 0; i < num_store_types; i++){
        if(store_types[i] == string_input){
            store_totals[i] = store_totals[i] + int_input;
        }
    }
}
int sell_from_store(std::string, int);

//INPUTS AND OUTPUTS//
int granary::interact_storage_space()
{
    return storage_space;
}
void granary::interact_storage_space(int int_input)
{
    storage_space = int_input;
}
int granary::interact_current_total()
{
    return current_total;
}
void granary::interact_current_total(int int_input)
{
    current_total = int_input;
}
int granary::interact_store_totals(std::string string_input)
{
    int return_value = 0; //If this function outputs zero, it may be due to this.
    for(int i = 0; i < num_store_types; i++){
        if(store_types[i] == string_input){
            return_value = store_totals[i];
        }
    }
    return return_value;
}
void granary::interact_store_totals(std::string string_input, int int_input)
{
    for(int i = 0; i < num_store_types; i++){
        if(store_types[i] == string_input){
            store_totals[i] = int_input;
        }
    }
}