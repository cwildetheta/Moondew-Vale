#include "../include/granary.h"
#include <iostream>

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
int granary::set_up(std::vector<std::vector<crop>> crop_fields, std::vector<std::vector<orchard>> orchard_fields, std::vector<std::vector<multicrop>> multicrop_fields, farmhouse home_house, brewery ale_house, workhouse dormitory, int size)
{
    int return_int = -1;
    std::cout << "Would you like to build one? Y/N: ";
    char char_input;
    std::cin >> char_input;
    switch(char_input){
        case 'y':
        case 'Y':{
            std::cout << "Please enter x coordinate: ";
            int x_coord, y_coord;
            std::cin >> x_coord;
            std::cout << "Please enter y coordinate: ";
            std::cin >> y_coord;
            if((x_coord < 1) || (x_coord > size)){
                std::cout << "x coordinate out of bounds, please try again." << std::endl;
            }
            else if((y_coord < 1) || (y_coord > size)){
                std::cout << "y coordinate out of bounds, please try again." << std::endl;
            }
            else if(crop_fields[y_coord-1][x_coord-1].interact_is_active() == true || orchard_fields[y_coord-1][x_coord-1].interact_is_active() == true || multicrop_fields[y_coord-1][x_coord-1].interact_is_active() == true){
                std::cout << "There is a field planted here. You need to clear it before a storehouse can be built here." << std::endl;
            }
            else if((home_house.interact_x_location() == x_coord) && (home_house.interact_y_location() == y_coord)){
                std::cout << "That's the farmhouse, you can't build a storehouse here." << std::endl;
            }
            else if((ale_house.interact_is_working() == true) && (ale_house.interact_x_location() == x_coord) && (ale_house.interact_y_location() == y_coord)){
                std::cout << "That's the brewery, you can't build a storehouse here." << std::endl;
            }
            else if((dormitory.interact_is_working() == true) && (dormitory.interact_x_location() == x_coord) && (dormitory.interact_y_location() == y_coord)){
                std::cout << "That's the dormitory, you can't build a storehouse here." << std::endl;
            }
            else{
                build(x_coord, y_coord);
                return_int = 1;
            }
            break;
        }
        case 'n':
        case 'N':{
            return_int = 0;
            break;
        }
        default:{
            std::cout << "Invalid entry." << std::endl;
            return_int = 0;
            break;
        }
    }
    return return_int;
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