#include "../include/farmhouse.h"
#include <iostream>
#include <iomanip>

farmhouse::farmhouse(int int_input, std::string string_input_array[], int int_input_array[], int upkeep_input, int fertiliser_input, int x_input, int y_input, bool is_working_input)
{
    num_seed_types = int_input;
    for(int i = 0; i < num_seed_types; i++){
        seed_totals[i] = int_input_array[i];
        seed_types[i] = string_input_array[i];
    }
    interact_upkeep(upkeep_input);
    fertiliser = fertiliser_input;
    interact_x_location(x_input);
    interact_y_location(y_input);
    interact_is_working(is_working_input);
}
void farmhouse::change_seed_totals(std::string string_input, int int_input)
{
    for(int i = 0; i < num_seed_types; i++){
        if(seed_types[i] == string_input){
            seed_totals[i] = seed_totals[i] + int_input;
        }
    }
}
int farmhouse::buy_menu(int money, int seed_prices[], int *in_farmhouse)
{
    std::cout << "Which type of seeds would you like to buy? Seeds are bought in packs of 5.    Current money: \x9C"<< money << "." << std::endl; //Generalise this later, ie. seed_types[i]
    std::cout << "0. Fertiliser  Current ammount: " << std::setw(4) << fertiliser << "     Cost: \x9C" << "10." << std::endl;
    std::cout << "1. Wheat       Current seeds: " << std::setw(6) << seed_totals[0] << "     Cost: \x9C" << seed_prices[0] << "." << std::endl;
    std::cout << "2. Barley      Current seeds: " << std::setw(6) << seed_totals[1] << "     Cost: \x9C" << seed_prices[1] << "." << std::endl;
    std::cout << "3. Apple       Current seeds: " << std::setw(6) << seed_totals[2] << "     Cost: \x9C" << seed_prices[2] << "." << std::endl;
    std::cout << "4. Orange      Current seeds: " << std::setw(6) << seed_totals[3] << "     Cost: \x9C" << seed_prices[3] << "." << std::endl;
    std::cout << "5. Courgette   Current seeds: " << std::setw(6) << seed_totals[4] << "     Cost: \x9C" << seed_prices[4] << "." << std::endl;
    std::cout << "6. Tomato      Current seeds: " << std::setw(6) << seed_totals[5] << "     Cost: \x9C" << seed_prices[5] << "." << std::endl << std::endl;
    int seed_pick = int_inputter("Seed type, or press another number to leave: ");
    if((seed_pick > 0) && (seed_pick < 7)){
        *in_farmhouse = 2;
        if(seed_prices[seed_pick-1] > money){
            std::cout << "You do not have enough money for that." << std::endl;
        }
        else{
            money = money - seed_prices[seed_pick-1];
            change_seed_totals(seed_types[seed_pick-1], 5);
            std::cout << "You have bought 5 " << seed_types[seed_pick-1] << " seeds." << std::endl;
        }
    }
    else if(seed_pick == 0){
        *in_farmhouse = 2;
        if(money > 9){
            money -= 10;
            fertiliser += 5;
            std::cout << "You have bought 5 units of fertiliser." << std::endl;
        }
        else{
            std::cout << "You do not have enough money for that." << std::endl;
        }
    }
    else{
        std::cout << "Leaving the storehouse." << std::endl;
        *in_farmhouse = 0;
    }
    return money;
}
void farmhouse::change_fertiliser(int int_input)
{
    fertiliser += int_input;
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