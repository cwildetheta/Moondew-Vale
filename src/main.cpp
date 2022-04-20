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
        std::vector<crop *> row_crop_point(size);
        std::vector<orchard *> row_orchard_point(size);
        std::vector<multicrop *> row_multicrop_point(size);
        std::vector<std::vector<crop *>> crop_fields_point(size, row_crop_point);
        std::vector<std::vector<orchard *>> orchard_fields_point(size, row_orchard_point);
        std::vector<std::vector<multicrop *>> multicrop_fields_point(size, row_multicrop_point);
        for(int i = 0; i < size; i++){
            for(int k = 0; k < size; k++){
                crop_fields[i][k].interact_is_active(false);
                crop_fields[i][k].interact_is_ripe(false);
                orchard_fields[i][k].interact_is_active(false);
                orchard_fields[i][k].interact_is_producing(false);
                multicrop_fields[i][k].interact_is_active(false);
                multicrop_fields[i][k].interact_is_producing(false);
                crop_fields_point[i][k] = &crop_fields[i][k];
                orchard_fields_point[i][k] = &orchard_fields[i][k];
                multicrop_fields_point[i][k] = &multicrop_fields[i][k];
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
        int price_variation[number_of_plants] = {3, 8, 4, 5, 2, 1};
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
            /*std::cout << "Current Prices: ";
            for(int i = 0; i < 6; i++){
                std::cout << "\x9C" << current_price[i] << "   ";
            }
            std::cout << std::endl;*/
            if((harvestable > 0) && (dormitory.interact_is_working() == true) && (dormitory.interact_harvesters() > 0)){
                int auto_harvest[number_of_plants], to_harvest = dormitory.interact_harvesters(), i = 0, k = 0;
                for(int i = 0; i < number_of_plants; i++){
                    auto_harvest[i] = 0;
                }
                while((harvestable > 0) && (to_harvest > 0) && (i < 7)){
                    int index = 0;
                    if((crop_fields[i][k].interact_is_active() == true) && (crop_fields[i][k].interact_is_alive() == true) && (crop_fields[i][k].interact_is_ripe() == true)){
                        for(int l = 0; l < number_of_plants; l++){
                            if(seed_types[l] == crop_fields[i][k].interact_name()){
                                index = l;
                            }
                        }
                        auto_harvest[index] += crop_fields[i][k].harvest_field();
                        crop_fields[i][k].clear_field();
                        to_harvest--;
                        harvestable--;
                    }
                    else if((orchard_fields[i][k].interact_is_active() == true) && (orchard_fields[i][k].interact_is_alive() == true) && (orchard_fields[i][k].interact_is_producing() == true)){
                        for(int l = 0; l < number_of_plants; l++){
                            if(seed_types[l] == orchard_fields[i][k].interact_name()){
                                index = l;
                            }
                        }
                        auto_harvest[index] += orchard_fields[i][k].harvest_field();
                        orchard_fields[i][k].clear_field();
                        to_harvest--;
                        harvestable--;
                    }
                    else if((multicrop_fields[i][k].interact_is_active() == true) && (multicrop_fields[i][k].interact_is_alive() == true) && (multicrop_fields[i][k].interact_is_producing() == true)){
                        for(int l = 0; l < number_of_plants; l++){
                            if(seed_types[l] == multicrop_fields[i][k].interact_name()){
                                index = l;
                            }
                        }
                        auto_harvest[index] += multicrop_fields[i][k].harvest_field();
                        multicrop_fields[i][k].clear_field();
                        to_harvest--;
                        harvestable--;
                    }
                    k++;
                    if(k > 6){
                        k = 0, i++;
                    }
                }
                std::cout << "Your workers have automatically harvested:";
                for(int l = 0; l < number_of_plants; l++){
                    if(auto_harvest[l] > 0){
                        std::cout << "   " << auto_harvest[l] << " units of " << seed_types[l];
                    }
                }
                std::cout << "." << std::endl;
                for(int l = 0; l < number_of_plants; l++){
                    if(auto_harvest[l] > 0){
                        harvest(seed_types[l], current_price[l], &storehouse, &ale_house, auto_harvest[l], &money);
                    }
                }
                system("cls");
                main_ui(crop_fields, orchard_fields, multicrop_fields, size, month, money, upkeep, harvestable, home_house, storehouse, ale_house, dormitory);
            }
            char entry;
            std::cout << "Enter choice: ";
            std::cin >> entry;
            switch(entry){
                case 'q':
                case 'Q':{ //No need to function
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
                    if(home_house.interact_seed_totals(seed_types[seed_pick-1]) > 0){
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
                            if((seed_pick == 1) || (seed_pick == 2)){ //Needs work on generalising which field subclass is used.
                                crop_fields[y_coord-1][x_coord-1].plant_field(seed_types[seed_pick-1], plant_chars[seed_pick-1], small_plant_chars[seed_pick-1], base_yields[seed_pick-1]);
                                home_house.change_seed_totals(seed_types[seed_pick-1], -1);
                                crop_fields[y_coord-1][x_coord-1].begin(0, false, false);
                            }
                            if((seed_pick == 3) || (seed_pick == 4)){
                                orchard_fields[y_coord-1][x_coord-1].plant_field(seed_types[seed_pick-1], plant_chars[seed_pick-1], small_plant_chars[seed_pick-1], base_yields[seed_pick-1]);
                                home_house.change_seed_totals(seed_types[seed_pick-1], -1);
                                orchard_fields[y_coord-1][x_coord-1].begin(0, false);
                            }
                            if((seed_pick == 5) || (seed_pick == 6)){
                                multicrop_fields[y_coord-1][x_coord-1].plant_field(seed_types[seed_pick-1], plant_chars[seed_pick-1], small_plant_chars[seed_pick-1], base_yields[seed_pick-1]);
                                home_house.change_seed_totals(seed_types[seed_pick-1], -1);
                                multicrop_fields[y_coord-1][x_coord-1].begin(0, false);
                            }
                        }
                    }
                    else{
                        std::cout << "You don't have any " << seed_types[seed_pick-1] << " seeds left." << std::endl;
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
                            for(int i = 0; i < number_of_plants; i++){ //Be careful with the limit here.
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
                            for(int i = 0; i < number_of_plants; i++){ //Be careful with the limit here.
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
                            for(int i = 0; i < number_of_plants; i++){ //Be careful with the limit here.
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
                        harvest(seed_types[index], current_price[index], &storehouse, &ale_house, output, &money);
                        harvestable--;
                    }
                    system("pause");
                    break;
                }
                case 'b':
                case 'B':{ //Completely functioned
                    money = home_house.buy_menu(money, seed_prices);
                    system("pause");
                    break;
                }
                case 'c':
                case 'C':{ //Completely functioned
                    clear(crop_fields_point, orchard_fields_point, multicrop_fields_point, home_house, storehouse, ale_house, dormitory, size, &harvestable);
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
                            set_up_granary(crop_fields, orchard_fields, multicrop_fields, home_house, &storehouse, ale_house, dormitory, size, &money, &upkeep);
                        }
                        else{
                            std::cout << "You do not have enough money currently." << std::endl;
                        }
                    }
                    else{
                        storehouse.interact(seed_types, current_price, &money);
                    }
                    system("pause");
                    break;
                }
                case 'a':
                case 'A':{
                    if(ale_house.interact_is_working() == false){
                        std::cout << "It costs \x9C" << ale_house.interact_cost() << " to build a brewery." << std::endl;
                        if(money >= ale_house.interact_cost()){
                            set_up_brewery(crop_fields, orchard_fields, multicrop_fields, home_house, storehouse, &ale_house, dormitory, size, &money, &upkeep);
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
                                ale_house.barley_in(&storehouse);
                                break;
                            }
                            case 'o':
                            case 'O':{
                                ale_house.barley_out(&storehouse);
                                break;
                            }
                            case 'b':
                            case 'B':{
                                ale_house.brew();
                                break;
                            }
                            case 's':
                            case 'S':{
                                ale_house.sale(&money);
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
                            set_up_workhouse(crop_fields, orchard_fields, multicrop_fields, home_house, storehouse, ale_house, &dormitory, size, &money, &upkeep);
                        }
                        else{
                            std::cout << "You do not have enough money currently." << std::endl;
                        }
                    }
                    else{
                        bool in_dormitory = true;
                        while(in_dormitory == true){
                            system("cls");
                            main_ui(crop_fields, orchard_fields, multicrop_fields, size, month, money, upkeep, harvestable, home_house, storehouse, ale_house, dormitory);
                            std::cout << "You currently have " << dormitory.interact_workers() << " workers out of a maximum of " << dormitory.interact_max_workers() << "." << std::endl;
                            if(dormitory.interact_workers() > 0){
                                std::cout << "Of those, " << dormitory.interact_harvesters() << " workers are assigned to harvesting, " << dormitory.interact_fertilisers() << " workers are assigned to fertilising, with " << (dormitory.interact_workers() - dormitory.interact_harvesters() - dormitory.interact_fertilisers()) << " workers unassigned." << std::endl;
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
                                    dormitory.increase_workers(&money, &upkeep);
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
                case 'l':{
                    test(&money);
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
                        if(dormitory.interact_is_working() == true){
                            int to_fertilise = dormitory.interact_fertilisers();
                            int i = 0, k = 0;
                            while((to_fertilise > 0) && (i < 7) && (home_house.interact_fertiliser() > 0)){
                                if((crop_fields[i][k].interact_is_active() == true) && (crop_fields[i][k].interact_is_alive() == true) && (crop_fields[i][k].interact_is_fertilised() == false)){
                                    crop_fields[i][k].interact_is_fertilised(true);
                                    home_house.change_fertiliser(-1);
                                    to_fertilise--;
                                }
                                else if((orchard_fields[i][k].interact_is_active() == true) && (orchard_fields[i][k].interact_is_alive() == true) && (orchard_fields[i][k].interact_is_fertilised() == false)){
                                    orchard_fields[i][k].interact_is_fertilised(true);
                                    home_house.change_fertiliser(-1);
                                    to_fertilise--;
                                }
                                else if((multicrop_fields[i][k].interact_is_active() == true) && (multicrop_fields[i][k].interact_is_alive() == true) && (multicrop_fields[i][k].interact_is_fertilised() == false)){
                                    multicrop_fields[i][k].interact_is_fertilised(true);
                                    home_house.change_fertiliser(-1);
                                    to_fertilise--;
                                }
                                k++;
                                if(k > 6){
                                    k = 0, i++;
                                }
                            }
                            if((home_house.interact_fertiliser() == 0) && (dormitory.interact_fertilisers() > 0)){
                                std::cout << "You are out of fertiliser, so yor workers cannot fertilise the fields." << std::endl;
                                system("pause");
                            }
                        }
                    }
                    for(int i = 0; i < number_of_plants; i++){
                        current_price[i] = change_prices(current_price[i], base_price[i], price_variation[i]);
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