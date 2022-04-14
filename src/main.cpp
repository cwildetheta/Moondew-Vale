#include "../include/crop.h"
#include "../include/orchard.h"
#include "../include/multicrop.h"
#include "../include/farmhouse.h"
#include "../include/granary.h"
#include "../include/brewery.h"
#include "../include/workhouse.h"
#include "../include/functions.h"
#include <iostream>
#include <iomanip>
#include <vector>

int main()
{
    system("cls");
    system("pause");
    bool simulation = true;
    while(simulation == true){
        int size = 7;
        std::vector<crop> row_crop(size);
        std::vector<orchard> row_orchard(size);
        std::vector<multicrop> row_multicrop(size);
        std::vector<std::vector<crop>> crop_fields(size, row_crop);
        std::vector<std::vector<orchard>> orchard_fields(size, row_orchard);
        std::vector<std::vector<multicrop>> multicrop_fields(size, row_multicrop);
        for(int i = 0; i < size; i++){
            for(int k = 0; k < size; k++){
                crop_fields[i][k].interact_is_active(false);
                crop_fields[i][k].interact_is_ripe(false);
                orchard_fields[i][k].interact_is_active(false);
                orchard_fields[i][k].interact_is_producing(false);
                multicrop_fields[i][k].interact_is_active(false);
                multicrop_fields[i][k].interact_is_producing(false);
            }
        }
        int number_of_plants = 6;
        std::string seed_types[number_of_plants] = {"Wheat", "Barley", "Apple", "Orange", "Courgette", "Tomato"};
        char plant_chars[number_of_plants] = {'W', 'B', 'A', 'O', 'C', 'T'};
        char small_plant_chars[number_of_plants] = {'w', 'b', 'a', 'o', 'c', 't'};
        int initial_seed_numbers[number_of_plants] = {10, 10, 5, 5, 2, 2};
        int seed_prices[number_of_plants] = {30, 45, 35, 35, 25, 20};
        int base_yields[number_of_plants] = {15, 15, 5, 5, 5, 5};
        int base_price[number_of_plants] = {5, 10, 6, 8, 3, 2}, current_price[number_of_plants] = {5, 10, 6, 8, 3, 2};
        int initial_store[number_of_plants] = {0, 0, 0, 0, 0, 0};
        farmhouse home_house(number_of_plants, seed_types, initial_seed_numbers, 0, 5, 4, 4, true);
        granary storehouse(number_of_plants, 200, 0, seed_types, initial_store, 150, 2, false);
        brewery ale_house(100, 10, 200, 3, false);
        workhouse dormitory(0, 10, 200, 5, false);
        bool sim_loop = true;
        int money = 1000, month = 1, harvestable = 0, upkeep = 0;
        while(sim_loop == true){
            system("cls");
            main_ui(crop_fields, orchard_fields, multicrop_fields, size, month, money, upkeep, harvestable, home_house, storehouse, ale_house, dormitory);
            char entry;
            std::cout << "Enter choice: ";
            std::cin >> entry;
            switch(entry){
                case 'q':
                case 'Q':{
                    sim_loop = false;
                    simulation = false;
                    break;
                }
                case 'p':
                case 'P':{
                    std::cout << "Which plant would you like to plant?" << std::endl; //Generalise this later, ie. seed_types[i]
                    std::cout << "1. Wheat      Seeds: " << home_house.interact_seed_totals(seed_types[0]) << std::endl;
                    std::cout << "2. Barley     Seeds: " << home_house.interact_seed_totals(seed_types[1]) << std::endl;
                    std::cout << "3. Apple      Seeds: " << home_house.interact_seed_totals(seed_types[2]) << std::endl;
                    std::cout << "4. Orange     Seeds: " << home_house.interact_seed_totals(seed_types[3]) << std::endl;
                    std::cout << "5. Courgette  Seeds: " << home_house.interact_seed_totals(seed_types[4]) << std::endl;
                    std::cout << "6. Tomato     Seeds: " << home_house.interact_seed_totals(seed_types[5]) << std::endl << std::endl;
                    int seed_pick;
                    std::cin >> seed_pick;
                    std::cout << "Please enter x coordinate: ";
                    int x_coord, y_coord;
                    std::cin >> x_coord;
                    std::cout << "Please enter y coordinate: ";
                    std::cin >> y_coord;
                    if((seed_pick < 1) || (seed_pick > 6)){
                        std::cout << "Not a valid seed choice, please try again." << std::endl;
                    }
                    else if((x_coord < 1) || (x_coord > size)){
                        std::cout << "x coordinate out of bounds, please try again." << std::endl;
                    }
                    else if((y_coord < 1) || (y_coord > size)){
                        std::cout << "y coordinate out of bounds, please try again." << std::endl;
                    }
                    else if((home_house.interact_x_location() == x_coord) && (home_house.interact_y_location() == y_coord)){
                        std::cout << "This location is already occupied by the farmhouse, please try again." << std::endl;
                    }
                    else if((storehouse.interact_is_working() == true) && (storehouse.interact_x_location() == x_coord) && (storehouse.interact_y_location() == y_coord)){
                        std::cout << "This location is already occupied by the storehouse, please try again." << std::endl;
                    }
                    else if((crop_fields[y_coord-1][x_coord-1].interact_is_active() == true) || (orchard_fields[y_coord-1][x_coord-1].interact_is_active() == true) || (multicrop_fields[y_coord-1][x_coord-1].interact_is_active() == true)){
                        std::cout << "This field is already in use. Clear it before planting something else." << std::endl;
                    }
                    else{
                        if(home_house.interact_seed_totals(seed_types[seed_pick-1]) > 0){
                            if((seed_pick == 1) || (seed_pick == 2)){ //Needs work on generalising which field subclass is used.
                                crop_fields[y_coord-1][x_coord-1].plant_field(seed_types[seed_pick-1], plant_chars[seed_pick-1], small_plant_chars[seed_pick-1]);
                                home_house.change_seed_totals(seed_types[seed_pick-1], -1);
                                crop_fields[y_coord-1][x_coord-1].interact_lifestage(0);
                                crop_fields[y_coord-1][x_coord-1].interact_is_ripe(false);
                                crop_fields[y_coord-1][x_coord-1].interact_is_overripe(false);
                                crop_fields[y_coord-1][x_coord-1].interact_yield(base_yields[seed_pick-1]);
                            }
                            if((seed_pick == 3) || (seed_pick == 4)){
                                orchard_fields[y_coord-1][x_coord-1].plant_field(seed_types[seed_pick-1], plant_chars[seed_pick-1], small_plant_chars[seed_pick-1]);
                                home_house.change_seed_totals(seed_types[seed_pick-1], -1);
                                orchard_fields[y_coord-1][x_coord-1].interact_age(0);
                                orchard_fields[y_coord-1][x_coord-1].interact_is_producing(false);
                                orchard_fields[y_coord-1][x_coord-1].interact_yield(base_yields[seed_pick-1]);
                            }
                            if((seed_pick == 5) || (seed_pick == 6)){
                                multicrop_fields[y_coord-1][x_coord-1].plant_field(seed_types[seed_pick-1], plant_chars[seed_pick-1], small_plant_chars[seed_pick-1]);
                                home_house.change_seed_totals(seed_types[seed_pick-1], -1);
                                multicrop_fields[y_coord-1][x_coord-1].interact_lifestage(0);
                                multicrop_fields[y_coord-1][x_coord-1].interact_is_producing(false);
                                multicrop_fields[y_coord-1][x_coord-1].interact_yield(base_yields[seed_pick-1]);
                            }
                        }
                    }
                    system("pause");
                    break;
                }
                case 'h':
                case 'H':{
                    std::cout << "Please enter x coordinate: ";
                    int x_coord, y_coord, index = -1, output;
                    std::cin >> x_coord;
                    std::cout << "Please enter y coordinate: ";
                    std::cin >> y_coord;
                    if((x_coord < 1) || (x_coord > size)){
                        std::cout << "x coordinate out of bounds, please try again." << std::endl;
                    }
                    else if((y_coord < 1) || (y_coord > size)){
                        std::cout << "y coordinate out of bounds, please try again." << std::endl;
                    }
                    if(crop_fields[y_coord-1][x_coord-1].interact_is_active() == true){
                        output = crop_fields[y_coord-1][x_coord-1].harvest_field();
                        if(output != -1){
                            for(int i = 0; i < 6; i++){ //Be careful with the limit here, make sure to change it if it needs it.
                                if(seed_types[i] == crop_fields[y_coord-1][x_coord-1].interact_name()){
                                    index = i;
                                }
                            }
                            std::cout << "You have harvested " << output << " units of " << crop_fields[y_coord-1][x_coord-1].interact_name() << ". ";
                            crop_fields[y_coord-1][x_coord-1].clear_field();
                        }
                    }
                    else if(orchard_fields[y_coord-1][x_coord-1].interact_is_active() == true){
                        output = orchard_fields[y_coord-1][x_coord-1].harvest_field();
                        if(output != -1){
                            for(int i = 0; i < 6; i++){ //Be careful with the limit here, make sure to change it if it needs it.
                                if(seed_types[i] == orchard_fields[y_coord-1][x_coord-1].interact_name()){
                                    index = i;
                                }
                            }
                            std::cout << "You have harvested " << output << " units of " << orchard_fields[y_coord-1][x_coord-1].interact_name() << ". ";
                            orchard_fields[y_coord-1][x_coord-1].interact_is_producing(false);
                        }
                    }
                    else if(multicrop_fields[y_coord-1][x_coord-1].interact_is_active() == true){
                        output = multicrop_fields[y_coord-1][x_coord-1].harvest_field();
                        if(output != -1){
                            for(int i = 0; i < 6; i++){ //Be careful with the limit here, make sure to change it if it needs it.
                                if(seed_types[i] == multicrop_fields[y_coord-1][x_coord-1].interact_name()){
                                    index = i;
                                }
                            }
                            std::cout << "You have harvested " << output << " units of " << multicrop_fields[y_coord-1][x_coord-1].interact_name() << ". ";
                            multicrop_fields[y_coord-1][x_coord-1].interact_is_producing(false);
                        }
                    }
                    else if((home_house.interact_x_location() == x_coord) && (home_house.interact_y_location() == y_coord)){
                        std::cout << "This is your farmhouse. You can't harvest a building." << std::endl;
                    }
                    else if((storehouse.interact_is_working() == true) && (storehouse.interact_x_location() == x_coord) && (storehouse.interact_y_location() == y_coord)){
                        std::cout << "This is your storehouse. You can't harvest a building." << std::endl;
                    }
                    else{
                        std::cout << "There is nothing in this field." << std::endl;
                    }
                    if(index != -1){
                        std::cout << "The current price of " << seed_types[index] << " is \x9C" << current_price[index];
                        storehouse.calculate_total();
                        ale_house.calculate_total();
                        if(((index == 1) && (ale_house.interact_is_working() == true) && ((ale_house.interact_storage_space() - ale_house.interact_current_total()) >= output)) && ((storehouse.interact_is_working() == true) && ((storehouse.interact_storage_space()-storehouse.interact_current_total()) >= output))){
                            std::cout << ", or there is " << (storehouse.interact_storage_space()-storehouse.interact_current_total()) << " units of space available in the storehouse, or " << (ale_house.interact_storage_space()-ale_house.interact_current_total()) << " units of space available in the brewery." << std::endl;
                            std::cout << "If you would like to store the harvest in the storehouse, press s, or in the brewery, press b, otherwise it will be sold: ";
                            char store_input;
                            std::cin >> store_input;
                            if(store_input == 's' || store_input == 'S'){
                                storehouse.add_to_store(seed_types[index], output);
                                std::cout << "The harvest has been stored in the storehouse." << std::endl;
                            }
                            if(store_input == 'b' || store_input == 'B'){
                                ale_house.transfer_barley(output);
                                std::cout << "The harvest has been stored in the brewery." << std::endl;
                            }
                            else{
                                std::cout << "You have made \x9C" << output*current_price[index] << "." << std::endl;
                                money = money + (output*current_price[index]);
                            }
                        }
                        else if((index == 1) && (ale_house.interact_is_working() == true) && ((ale_house.interact_storage_space()-ale_house.interact_current_total()) >= output)){
                            std::cout << ", or there is " << (ale_house.interact_storage_space()-ale_house.interact_current_total()) << " units of space available in the brewery." << std::endl;
                            std::cout << "If you would like to store the harvest, press s, otherwise it will be sold: ";
                            char store_input;
                            std::cin >> store_input;
                            if(store_input == 's' || store_input == 'S'){
                                ale_house.transfer_barley(output);
                                std::cout << "The harvest has been stored in the brewery." << std::endl;
                            }
                            else{
                                std::cout << "You have made \x9C" << output*current_price[index] << "." << std::endl;
                                money = money + (output*current_price[index]);
                            }
                        }
                        else if((storehouse.interact_is_working() == true) && ((storehouse.interact_storage_space()-storehouse.interact_current_total()) >= output)){
                            std::cout << ", or there is " << (storehouse.interact_storage_space()-storehouse.interact_current_total()) << " units of space available in the storehouse." << std::endl;
                            std::cout << "If you would like to store the harvest, press s, otherwise it will be sold: ";
                            char store_input;
                            std::cin >> store_input;
                            if(store_input == 's' || store_input == 'S'){
                                storehouse.add_to_store(seed_types[index], output);
                                std::cout << "The harvest has been stored in the storehouse." << std::endl;
                            }
                            else{
                                std::cout << "You have made \x9C" << output*current_price[index] << "." << std::endl;
                                money = money + (output*current_price[index]);
                            }
                        }
                        else{
                            std::cout << "." << std::endl;
                            std::cout << "You have made \x9C" << output*current_price[index] << "." << std::endl;
                            money = money + (output*current_price[index]);
                        }
                        harvestable--;
                    }
                    system("pause");
                    break;
                }
                case 'b':
                case 'B':{
                    std::cout << "Which type of seeds would you like to buy? Seeds are bought in packs of 5.    Current money: \x9C"<< money << "." << std::endl; //Generalise this later, ie. seed_types[i]
                    std::cout << "0. Fertiliser  Current ammount: " << std::setw(4) << home_house.interact_fertiliser() << "     Cost: \x9C" << "10." << std::endl;
                    std::cout << "1. Wheat       Current seeds: " << std::setw(6) << home_house.interact_seed_totals(seed_types[0]) << "     Cost: \x9C" << seed_prices[0] << "." << std::endl;
                    std::cout << "2. Barley      Current seeds: " << std::setw(6) << home_house.interact_seed_totals(seed_types[1]) << "     Cost: \x9C" << seed_prices[1] << "." << std::endl;
                    std::cout << "3. Apple       Current seeds: " << std::setw(6) << home_house.interact_seed_totals(seed_types[2]) << "     Cost: \x9C" << seed_prices[2] << "." << std::endl;
                    std::cout << "4. Orange      Current seeds: " << std::setw(6) << home_house.interact_seed_totals(seed_types[3]) << "     Cost: \x9C" << seed_prices[3] << "." << std::endl;
                    std::cout << "5. Courgette   Current seeds: " << std::setw(6) << home_house.interact_seed_totals(seed_types[4]) << "     Cost: \x9C" << seed_prices[4] << "." << std::endl;
                    std::cout << "6. Tomato      Current seeds: " << std::setw(6) << home_house.interact_seed_totals(seed_types[5]) << "     Cost: \x9C" << seed_prices[5] << "." << std::endl << std::endl;
                    int seed_pick;
                    std::cin >> seed_pick;
                    if((seed_pick > 0) && (seed_pick < 7)){
                        if(seed_prices[seed_pick-1] > money){
                            std::cout << "You do not have enough money for that." << std::endl;
                        }
                        else{
                            money = money - seed_prices[seed_pick-1];
                            //home_house.interact_seed_totals(seed_types[seed_pick-1], (home_house.interact_seed_totals(seed_types[seed_pick-1])+5));
                            home_house.change_seed_totals(seed_types[seed_pick-1], 5);
                            std::cout << "You have bought 5 " << seed_types[seed_pick-1] << " seeds." << std::endl;
                        }
                    }
                    else if(seed_pick == 0){
                        if(money > 9){
                            money = money - 10;
                            home_house.interact_fertiliser(home_house.interact_fertiliser()+5);
                            std::cout << "You have bought 5 units of fertiliser." << std::endl;
                        }
                        else{
                            std::cout << "You do not have enough money for that." << std::endl;
                        }
                    }
                    else{
                        std::cout << "Invalid entry." << std::endl;
                    }
                    system("pause");
                    break;
                }
                case 'c':
                case 'C':{
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
                    if(crop_fields[y_coord-1][x_coord-1].interact_is_active() == true){
                        crop_fields[y_coord-1][x_coord-1].clear_field();
                        std::cout << "Field at " << x_coord << "," << y_coord << " cleared." << std::endl;
                        if(crop_fields[y_coord-1][x_coord-1].interact_is_ripe() == true){
                            harvestable--;
                            crop_fields[y_coord-1][x_coord-1].interact_is_ripe(false);
                        }
                    }
                    else if(orchard_fields[y_coord-1][x_coord-1].interact_is_active() == true){
                        orchard_fields[y_coord-1][x_coord-1].clear_field();
                        std::cout << "Field at " << x_coord << "," << y_coord << " cleared." << std::endl;
                        if(orchard_fields[y_coord-1][x_coord-1].interact_is_producing() == true){
                            harvestable--;
                            orchard_fields[y_coord-1][x_coord-1].interact_is_producing(false);
                        }
                    }
                    else if(multicrop_fields[y_coord-1][x_coord-1].interact_is_active() == true){
                        multicrop_fields[y_coord-1][x_coord-1].clear_field();
                        std::cout << "Field at " << x_coord << "," << y_coord << " cleared." << std::endl;
                        if(multicrop_fields[y_coord-1][x_coord-1].interact_is_producing() == true){
                            harvestable--;
                            multicrop_fields[y_coord-1][x_coord-1].interact_is_producing();
                        }
                    }
                    else if((home_house.interact_x_location() == x_coord) && (home_house.interact_y_location() == y_coord)){
                        std::cout << "This is your farmhouse. You can't remove that: you live there." << std::endl;
                    }
                    else if((storehouse.interact_is_working() == true) && (storehouse.interact_x_location() == x_coord) && (storehouse.interact_y_location() == y_coord)){
                        std::cout << "This is your storehouse, you can't remove that right now." << std::endl;
                    }
                    else{
                        std::cout << "There's nothing in this field to clear." << std::endl;
                    }
                    system("pause");
                    break;
                }
                case 'f':
                case 'F':{
                    std::cout << "You have " << home_house.interact_fertiliser() << " units of fertiliser." << std::endl;
                    if(home_house.interact_fertiliser() > 0){
                        std::cout << "Pick a field to fertilise." << std::endl;
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
                        if(crop_fields[y_coord-1][x_coord-1].interact_is_active() == true){
                            if(crop_fields[y_coord-1][x_coord-1].interact_is_fertilised() == false){
                                crop_fields[y_coord-1][x_coord-1].interact_is_fertilised(true);
                                home_house.interact_fertiliser(home_house.interact_fertiliser()-1);
                                std::cout << "Field at " << x_coord << "," << y_coord << " fertilised." << std::endl;
                            }
                            else{
                                std::cout << "This field is already fertilised." << std::endl;
                            }
                        }
                        else if(orchard_fields[y_coord-1][x_coord-1].interact_is_active() == true){
                            if(orchard_fields[y_coord-1][x_coord-1].interact_is_fertilised() == false){
                                orchard_fields[y_coord-1][x_coord-1].interact_is_fertilised(true);
                                home_house.interact_fertiliser(home_house.interact_fertiliser()-1);
                                std::cout << "Field at " << x_coord << "," << y_coord << " fertilised." << std::endl;
                            }
                            else{
                                std::cout << "This field is already fertilised." << std::endl;
                            }
                        }
                        else if(multicrop_fields[y_coord-1][x_coord-1].interact_is_active() == true){
                            if(multicrop_fields[y_coord-1][x_coord-1].interact_is_fertilised() == false){
                                multicrop_fields[y_coord-1][x_coord-1].interact_is_fertilised(true);
                                home_house.interact_fertiliser(home_house.interact_fertiliser()-1);
                                std::cout << "Field at " << x_coord << "," << y_coord << " fertilised." << std::endl;
                            }
                            else{
                                std::cout << "This field is already fertilised." << std::endl;
                            }
                        }
                        else if((home_house.interact_x_location() == x_coord) && (home_house.interact_y_location() == y_coord)){
                            std::cout << "This is your farmhouse. You can't fertilise it." << std::endl;
                        }
                        else if((storehouse.interact_is_working() == true) && (storehouse.interact_x_location() == x_coord) && (storehouse.interact_y_location() == y_coord)){
                            std::cout << "This is you storehouse. You can't fertilise it." << std::endl;
                        }
                        else{
                            std::cout << "There is nothing in this field to fertilise." << std::endl;
                        }
                    }
                    system("pause");
                    break;
                }
                case 's':
                case 'S':{
                    if(storehouse.interact_is_working() == false){
                        std::cout << "It costs \x9C" << storehouse.interact_cost() << " to build a storehouse." << std::endl;
                        if(money >= storehouse.interact_cost()){
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
                                        storehouse.build(x_coord, y_coord);
                                        money = money - storehouse.interact_cost();
                                        upkeep = upkeep + storehouse.interact_upkeep();
                                    }
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
                            std::cout << "You do not have enough money currently." << std::endl;
                        }
                    }
                    else{
                        std::cout << "The current storage totals are:" << std::endl;
                        std::cout << "1. Wheat       Current store: " << std::setw(6) << storehouse.interact_store_totals(seed_types[0]) << std::endl;
                        std::cout << "2. Barley      Current store: " << std::setw(6) << storehouse.interact_store_totals(seed_types[1]) << std::endl;
                        std::cout << "3. Apple       Current store: " << std::setw(6) << storehouse.interact_store_totals(seed_types[2]) << std::endl;
                        std::cout << "4. Orange      Current store: " << std::setw(6) << storehouse.interact_store_totals(seed_types[3]) << std::endl;
                        std::cout << "5. Courgette   Current store: " << std::setw(6) << storehouse.interact_store_totals(seed_types[4]) << std::endl;
                        std::cout << "6. Tomato      Current store: " << std::setw(6) << storehouse.interact_store_totals(seed_types[5]) << std::endl << std::endl;
                        std::cout << "Would you like to sell some of your stores? 0 to exit or pick a number: ";
                        int store_pick;
                        std::cin >> store_pick;
                        if((store_pick > 0) && (store_pick < 7)){
                            if(storehouse.interact_store_totals(seed_types[store_pick-1]) > 0){
                                std::cout << "The current price of " << seed_types[store_pick-1] << " is \x9C" << current_price[store_pick-1] << ". How much would you like to sell?: ";
                                int sell_amount;
                                std::cin >> sell_amount;
                                if(sell_amount >= storehouse.interact_store_totals(seed_types[store_pick-1])){
                                    sell_amount = storehouse.interact_store_totals(seed_types[store_pick-1]);
                                    std::cout << "Selling the entire store of " << seed_types[store_pick-1] << "." << std::endl;
                                    storehouse.add_to_store(seed_types[store_pick-1], -sell_amount);
                                    money = money + (sell_amount*current_price[store_pick-1]);
                                }
                                else{
                                    std::cout << "Selling " << sell_amount << " units of " << seed_types[store_pick-1] << "." << std::endl;
                                    storehouse.add_to_store(seed_types[store_pick-1], -sell_amount);
                                    money = money + (sell_amount*current_price[store_pick-1]);
                                }
                            }
                            else{
                                std::cout << "You have no " << seed_types[store_pick-1] << " to sell." << std::endl;
                            }
                        }
                    }
                    system("pause");
                    break;
                }
                case 'a':
                case 'A':{
                    if(ale_house.interact_is_working() == false){
                        std::cout << "It costs \x9C" << ale_house.interact_cost() << " to build a brewery." << std::endl;
                        if(money >= ale_house.interact_cost()){
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
                                        std::cout << "There is a field planted here. You need to clear it before a brewery can be built here." << std::endl;
                                    }
                                    else if((home_house.interact_x_location() == x_coord) && (home_house.interact_y_location() == y_coord)){
                                        std::cout << "That's the farmhouse, you can't build a brewery here." << std::endl;
                                    }
                                    else if((storehouse.interact_is_working() == true) && (storehouse.interact_x_location() == x_coord) && (storehouse.interact_y_location() == y_coord)){
                                        std::cout << "That's the storehouse, you can't build a brewery here." << std::endl;
                                    }
                                    else if((dormitory.interact_is_working() == true) && (dormitory.interact_x_location() == x_coord) && (dormitory.interact_y_location() == y_coord)){
                                        std::cout << "That's the dormitory, you can't build a brewery here." << std::endl;
                                    }
                                    else{
                                        ale_house.build(x_coord, y_coord);
                                        money = money - ale_house.interact_cost();
                                        upkeep = upkeep + ale_house.interact_upkeep();
                                    }
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
                            std::cout << "You do not have enough money currently." << std::endl;
                        }
                    }
                    else{
                        std::cout << "The brewery currently contains " << ale_house.interact_stored_barley() << " units of Barley and " << ale_house.interact_stored_beer() << " units of Beer." << std::endl;
                        std::cout << "The brewery can convert " << ale_house.interact_brewing_cap() << " units of Barley into Beer on a bimonthly basis, and is currently converting " << ale_house.interact_current_brewing() << " units." << std::endl;
                        std::cout << "Would you like to move Barley into the brewery (i), move Barley out of the brewery (o), change the amount of beer being made (b), sell beer (s), or leave the brewery (any other key): ";
                        char brewery_input;
                        std::cin >> brewery_input;
                        switch(brewery_input){
                            case 'i':
                            case 'I':{
                                if(storehouse.interact_is_working() == true){
                                    if(storehouse.interact_store_totals("Barley") > 0){
                                        storehouse.calculate_total();
                                        std::cout << "How much Barley do you want to move into the brewery. There are " << storehouse.interact_store_totals("Barley") << " units in the storehouse and " << (ale_house.interact_storage_space() - ale_house.interact_current_total()) << " units of space in the brewery: ";
                                        if(ale_house.interact_current_total() == ale_house.interact_storage_space()){
                                            std::cout << "The brewery is full. Remove something if you wish to add more Barley to it." << std::endl;
                                        }
                                        else{
                                            int move_input;
                                            std::cin >> move_input;
                                            if(move_input >= storehouse.interact_store_totals("Barley")){
                                                move_input = storehouse.interact_store_totals("Barley");
                                                std::cout << "Moving the entire Barley store into the brewery." << std::endl;
                                                storehouse.add_to_store("Barley", -move_input);
                                                ale_house.transfer_barley(move_input);
                                            }
                                            else{
                                                std::cout << "Moving " << move_input << " units of Barley into the brewery." << std::endl;
                                                storehouse.add_to_store("Barley", -move_input);
                                                ale_house.transfer_barley(move_input);
                                            }
                                        }
                                    }
                                    else{
                                        std::cout << "There is currently no Barley stored in the storehouse." << std::endl;
                                    }
                                }
                                else{
                                    std::cout << "You currently don't have a storehouse, so there is nowhere to move Barley from." << std::endl;
                                }
                                break;
                            }
                            case 'o':
                            case 'O':{
                                if(storehouse.interact_is_working() == true){
                                    if(ale_house.interact_stored_barley() > 0){
                                        storehouse.calculate_total();
                                        std::cout << "How much Barley do you want to move into the storehouse. There are " << ale_house.interact_stored_barley() << " units in the brewery, and " << (storehouse.interact_storage_space() - storehouse.interact_current_total()) << " units of space free in the storehouse: ";
                                        if(storehouse.interact_current_total() == storehouse.interact_storage_space()){
                                            std::cout << "There storehouse is full, so no Barley can be move to there." << std::endl;
                                        }
                                        else{
                                            int move_input;
                                            std::cin >> move_input;
                                            if(move_input >= ale_house.interact_stored_barley()){
                                                move_input = ale_house.interact_stored_barley();
                                                std::cout << "Moving the entire Barley store into the storehouse." << std::endl;
                                                storehouse.add_to_store("Barley", move_input);
                                                ale_house.transfer_barley(-move_input);
                                            }
                                            else{
                                                std::cout << "Moving " << move_input << " units of Barley into the storehouse." << std::endl;
                                                storehouse.add_to_store("Barley", move_input);
                                                ale_house.transfer_barley(-move_input);
                                            }
                                        }
                                    }
                                    else{
                                        std::cout << "There is currently no Barley stored in the brewery." << std::endl;
                                    }
                                }
                                else{
                                    std::cout << "You currently don't have a storehouse, so there is nowhere to move Barley from." << std::endl;
                                }
                                break;
                            }
                            case 'b':
                            case 'B':{
                                bool in_brew_adding = true;
                                while(in_brew_adding == true){
                                    std::cout << "There are currently " << ale_house.interact_current_brewing() << " units of Barley waiting to be brewed, out of a potential total of " << ale_house.interact_brewing_cap() << " units." << std::endl;
                                    std::cout << "Would you like to add (a) or remove (r) Barley, or exit (e): ";
                                    char brew_input;
                                    int move_amount;
                                    std::cin >> brew_input;
                                    switch(brew_input){
                                        case 'a':
                                        case 'A':{
                                            if(ale_house.interact_current_brewing() == ale_house.interact_brewing_cap()){
                                                std::cout << "The brewing process is already at capacity, you can't add any more Barley." << std::endl;
                                            }
                                            else if(ale_house.interact_stored_barley() == 0){
                                                std::cout << "There is no Barley currently stored in the brewery to add to the process." << std::endl;
                                            }
                                            else{
                                                std::cout << "How much Barley would you like to add: ";
                                                std::cin >> move_amount;
                                                if(move_amount > ale_house.interact_stored_barley()){
                                                    move_amount = ale_house.interact_stored_barley();
                                                }
                                                if(move_amount > (ale_house.interact_brewing_cap() - ale_house.interact_current_brewing())){
                                                    move_amount = (ale_house.interact_brewing_cap() - ale_house.interact_current_brewing());
                                                }
                                                std::cout << "Adding " << move_amount << " units of Barley to the brewing process." << std::endl;
                                                ale_house.add_to_brewing(move_amount);
                                            }
                                            break;
                                        }
                                        case 'r':
                                        case 'R':{
                                            if(ale_house.interact_current_brewing() == 0){
                                                std::cout << "There is no Barley in the brewing process to be removed." << std::endl;
                                            }
                                            else{
                                                std::cout << "How much Barley would you like to remove: ";
                                                std::cin >> move_amount;
                                                if(move_amount > ale_house.interact_current_brewing()){
                                                    move_amount = ale_house.interact_current_brewing();
                                                }
                                                std::cout << "Removing " << move_amount << " units of Barley from the brewing process.";
                                                ale_house.add_to_brewing(-move_amount);
                                            }
                                            break;
                                        }
                                        case 'e':
                                        case 'E':{
                                            in_brew_adding = false;
                                            break;
                                        }
                                        default:{
                                            std::cout << "Invalid entry, please try again." << std::endl;
                                            break;
                                        }
                                    }
                                }
                                break;
                            }
                            case 's':
                            case 'S':{
                                if(ale_house.interact_stored_beer() > 0){
                                    std::cout << "There are currently " << ale_house.interact_stored_beer() << " units of beer in the brewery. It sells for \x9C" << "20 per unit. How many would you like to sell: ";
                                    int sell_amount;
                                    std::cin >> sell_amount;
                                    if(sell_amount >= ale_house.interact_stored_beer()){
                                        sell_amount = ale_house.interact_stored_beer();
                                        std::cout << "Selling the entire beer stock." << std::endl;
                                        ale_house.sell_beer(sell_amount);
                                        money += (sell_amount*20);
                                    }
                                    else{
                                        std::cout << "Selling " << sell_amount << " units of beer." << std::endl;
                                        ale_house.sell_beer(sell_amount);
                                        money += (sell_amount*20);
                                    }
                                }
                                else{
                                    std::cout << "There is currently no beer stored in the brewery to sell." << std::endl;
                                }
                                break;
                            }
                            default:{
                                break;
                            }
                        }
                    }
                    system("pause");
                    break;
                }
                case 'd':
                case 'D':{
                    if(dormitory.interact_is_working() == false){
                        std::cout << "It costs \x9C" << dormitory.interact_cost() << " to build a dormitory." << std::endl;
                        if(money >= dormitory.interact_cost()){
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
                                        std::cout << "There is a field planted here. You need to clear it before a dormitory can be built here." << std::endl;
                                    }
                                    else if((home_house.interact_x_location() == x_coord) && (home_house.interact_y_location() == y_coord)){
                                        std::cout << "That's the farmhouse, you can't build a dormitory here." << std::endl;
                                    }
                                    else if((storehouse.interact_is_working() == true) && (storehouse.interact_x_location() == x_coord) && (storehouse.interact_y_location() == y_coord)){
                                        std::cout << "That's the storehouse, you can't build a dormitory here." << std::endl;
                                    }
                                    else if((ale_house.interact_is_working() == true) && (ale_house.interact_x_location() == x_coord) && (ale_house.interact_y_location() == y_coord)){
                                        std::cout << "That's the brewery, you can't build a dormitory here." << std::endl;
                                    }
                                    else{
                                        dormitory.build(x_coord, y_coord);
                                        money = money - dormitory.interact_cost();
                                        upkeep = upkeep + dormitory.interact_upkeep();
                                    }
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
                            std::cout << "You do not have enough money currently." << std::endl;
                        }
                    }
                    else{
                        bool in_dormitory = true;
                        while(in_dormitory == true){
                            std::cout << "You currently have " << dormitory.interact_workers() << " workers out of a maximum of " << dormitory.interact_max_workers() << "." << std::endl;
                            if(dormitory.interact_workers() > 0){
                                std::cout << "of those, " << dormitory.interact_harvesters() << " workers are assigned to harvesting, " << dormitory.interact_fertilisers() << " workers are assigned to fertilising, with " << (dormitory.interact_workers() - dormitory.interact_harvesters() - dormitory.interact_fertilisers()) << " workers unassigned." << std::endl;
                            }
                            std::cout << "Would you like to change the number of workers assigned to harvesting (h), fertilising (f), hire new workers (n), or exit (any other key): ";
                            char dormitory_input;
                            std::cin >> dormitory_input;
                            switch(dormitory_input){
                                case 'h':
                                case 'H':{
                                    dormitory.automate_harvest();
                                    break;
                                }
                                case 'f':
                                case 'F':{
                                    dormitory.automate_fertilise();
                                    break;
                                }
                                case 'n':
                                case 'N':{
                                    int new_workers = dormitory.increase_workers(money);
                                    if(new_workers > 0){
                                        money -= (new_workers*25);
                                    }
                                    upkeep += (new_workers*2);
                                    break;
                                }
                                default:{
                                    in_dormitory = false;
                                    break;
                                }
                            }
                        }
                    }
                    system("pause");
                    break;
                }
                default:{
                    bool end_turn = true;
                    if(harvestable > 0){
                        std::cout << "There are still fields that can be harvested, are you sure you want to move on? Press y to confirm: ";
                        char end_turn_input;
                        std::cin >> end_turn_input;
                        if(end_turn_input == 'y' || end_turn_input == 'Y'){
                            end_turn = true;
                        }
                        else{
                            end_turn = false;
                        }
                    }
                    if(end_turn == true){
                        month += 2;
                        if(month >= 12){
                            month = month - 12;
                        }
                        for(int i = 0; i < size; i++){
                            for(int k = 0; k < size; k++){
                                if(crop_fields[i][k].interact_is_active() == true){
                                    if(crop_fields[i][k].interact_is_alive() == false){
                                        crop_fields[i][k].clear_field();
                                    }
                                    if(month == 8 || month == 9){
                                        if(crop_fields[i][k].interact_lifestage() == 4){
                                            crop_fields[i][k].interact_is_ripe(true);
                                        }
                                        else if(crop_fields[i][k].interact_lifestage() == 3){
                                            crop_fields[i][k].interact_is_ripe(true);
                                            crop_fields[i][k].interact_is_overripe(true);
                                        }
                                    }
                                    if(crop_fields[i][k].interact_lifestage() >= 5 || month == 10 || month == 11 || month == 0){
                                        crop_fields[i][k].die();
                                        crop_fields[i][k].interact_is_ripe(false);
                                    }
                                    else{
                                        crop_fields[i][k].grow();
                                    }
                                }
                                if(orchard_fields[i][k].interact_is_active() == true){
                                    if((month == 6 || month == 7 || month == 8 || month == 9) && (orchard_fields[i][k].interact_age() > 18)){
                                        orchard_fields[i][k].interact_is_producing(true);
                                    }
                                    if(month == 10 || month == 11){
                                        orchard_fields[i][k].interact_is_producing(false);
                                    }
                                    orchard_fields[i][k].grow();
                                }
                                if(multicrop_fields[i][k].interact_is_active() == true){
                                    if(multicrop_fields[i][k].interact_is_alive() == false){
                                        multicrop_fields[i][k].clear_field();
                                    }
                                    if((month > 4 && month < 10) && (multicrop_fields[i][k].interact_lifestage() > 1)){
                                        multicrop_fields[i][k].interact_is_producing(true);
                                    }
                                    if(multicrop_fields[i][k].interact_lifestage() >= 5 || month == 10 || month == 11 || month == 0){
                                        multicrop_fields[i][k].die();
                                        multicrop_fields[i][k].interact_is_producing(false);
                                    }
                                    else{
                                        multicrop_fields[i][k].grow();
                                    }
                                }
                            }
                        }
                        harvestable = 0;
                        for(int i = 0; i < size; i++){
                            for(int k = 0; k < size; k++){
                                if(crop_fields[i][k].interact_is_ripe() == true || orchard_fields[i][k].interact_is_producing() == true || multicrop_fields[i][k].interact_is_producing() == true){
                                    harvestable++;
                                }
                            }
                        }
                        money -= upkeep;
                        if(money < 0){
                            std::cout << "You have run out of money, so your farm is now bankrupt." << std::endl;
                            std::cout << "Simulation over." << std::endl;
                            sim_loop = false;
                            simulation = false;
                        }
                        if(ale_house.interact_is_working() == true){
                            if(ale_house.interact_current_brewing() > 0){
                                ale_house.make_beer(ale_house.interact_current_brewing());
                            }
                        }
                        if(dormitory.interact_is_working() == true){}
                    }
                    break;
                }
            }
        }
    }
    /*for(int i = 0; i < 256; i++){
        std::cout << i << " is " << char(i) << "   ";
    }*/
    system("pause");
    system("cls");
    return 0;
}