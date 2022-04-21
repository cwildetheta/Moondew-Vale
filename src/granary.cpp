#include "../include/granary.h"
#include <iostream>
#include <iomanip>

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
void granary::interact(std::string seed_types[], int current_price[], int *money, int *in_storehouse)
{
    calculate_total();
    std::cout << "The current storage totals are:              Total storage: " << (storage_space - current_total) << "/" << storage_space << " available." << std::endl;
    std::cout << "1. Wheat       Current store: " << std::setw(6) << interact_store_totals(seed_types[0]) << std::endl;
    std::cout << "2. Barley      Current store: " << std::setw(6) << interact_store_totals(seed_types[1]) << std::endl;
    std::cout << "3. Apple       Current store: " << std::setw(6) << interact_store_totals(seed_types[2]) << std::endl;
    std::cout << "4. Orange      Current store: " << std::setw(6) << interact_store_totals(seed_types[3]) << std::endl;
    std::cout << "5. Courgette   Current store: " << std::setw(6) << interact_store_totals(seed_types[4]) << std::endl;
    std::cout << "6. Tomato      Current store: " << std::setw(6) << interact_store_totals(seed_types[5]) << std::endl;
    std::cout << "7. Expand the storehouse."<< std::endl << std::endl;
    int store_pick = int_inputter("Would you like to sell some of your stores? Pick a number, press 7 to expand the storehouse, or 0 to exit: ");
    if((store_pick > 0) && (store_pick < 7)){
        *in_storehouse = 2;
        if(interact_store_totals(seed_types[store_pick-1]) > 0){
            std::cout << "The current price of " << seed_types[store_pick-1] << " is \x9C" << current_price[store_pick-1] << ". ";
            int sell_amount = int_inputter("How much would you like to sell?: ");
            if(sell_amount >= interact_store_totals(seed_types[store_pick-1])){
                sell_amount = interact_store_totals(seed_types[store_pick-1]);
                std::cout << "Selling the entire store of " << seed_types[store_pick-1] << "." << std::endl;
            }
            else{
                std::cout << "Selling " << sell_amount << " units of " << seed_types[store_pick-1] << "." << std::endl;
            }
            add_to_store(seed_types[store_pick-1], -sell_amount);
            *money += (sell_amount*current_price[store_pick-1]);
        }
        else{
            std::cout << "You have no " << seed_types[store_pick-1] << " to sell." << std::endl;
        }
    }
    else if(store_pick == 7){
        *in_storehouse = 2;
        std::cout << "It costs \x9C" << "300 to expand the storehouse by 200. ";
        if(*money >= 300){
            std::cout << "Would you like to do so Y/N: ";
            char char_input;
            std::cin >> char_input;
            switch(char_input){
                case 'y':
                case 'Y':{
                    std::cout << "Expanding the storehouse." << std::endl;
                    storage_space += 200;
                    *money -= 300;
                    break;
                }
                case 'n':
                case 'N':{
                    break;
                }
                default:{
                    std::cout << "Invalid entry." << std::endl;
                    break;
                }
            }
        }
        else{
            std::cout << std::endl << "You do not have enough money to do that." << std::endl;
        }
    }
    else{
        *in_storehouse = 0;
    }
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
int granary::interact_num_store_types()
{
    return num_store_types;
}
void granary::interact_num_store_types(int int_input)
{
    num_store_types = int_input;
}
std::string granary::interact_store_types(int int_input)
{
    return store_types[int_input];
}
void granary::interact_store_types(std::string string_input, int int_input)
{
    store_types[int_input] = string_input;
}