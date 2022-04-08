#include "../include/farmhouse.h"

farmhouse::farmhouse(int int_input, std::string string_input_array[], int int_input_array[])
{
    num_seed_types = int_input;
    for(int i = 0; i < num_seed_types; i++){
        seed_totals[i] = int_input_array[i];
        seed_types[i] = string_input_array[i];
    }

}
void farmhouse::change_seed_totals(std::string string_input, int int_input)
{
    for(int i = 0; i < num_seed_types; i++){
        if(seed_types[i] == string_input){
            seed_totals[i] = seed_totals[i] + int_input;
        }
    }
}

//INPUTS AND OUTPUTS
int farmhouse::interact_current_total()
{
    return current_total;
}
void farmhouse::interact_current_total(int int_input)
{
    current_total = int_input;
}
int farmhouse::interact_fertiliser()
{
    return fertiliser;
}
void farmhouse::interact_fertiliser(int int_input)
{
    fertiliser = int_input;
}
int farmhouse::interact_seed_totals(std::string string_input)
{
    int return_value = 0; //If this function outputs zero, it may be due to this.
    for(int i = 0; i < num_seed_types; i++){
        if(seed_types[i] == string_input){
            return_value = seed_totals[i];
        }
    }
    return return_value;
}
void farmhouse::interact_seed_totals(std::string string_input, int int_input)
{
    for(int i = 0; i < num_seed_types; i++){
        if(seed_types[i] == string_input){
            seed_totals[i] = int_input;
        }
    }
}