#include "../include/base_functions.h"
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
        int number_of_plants = 6, money = 1000, month = 1, harvestable = 0, upkeep = 0;
        std::string seed_types[number_of_plants] = {"Wheat", "Barley", "Apple", "Orange", "Courgette", "Tomato"};
        char plant_chars[number_of_plants] = {'W', 'B', 'A', 'O', 'C', 'T'}, small_plant_chars[number_of_plants] = {'w', 'b', 'a', 'o', 'c', 't'};
        int initial_seed_numbers[number_of_plants] = {10, 10, 5, 5, 2, 2};
        int seed_prices[number_of_plants] = {30, 45, 35, 35, 25, 20};
        int base_yields[number_of_plants] = {15, 15, 5, 5, 5, 5};
        int base_price[number_of_plants] = {5, 10, 6, 8, 3, 2}, current_price[number_of_plants] = {5, 10, 6, 8, 3, 2}, price_variation[number_of_plants] = {3, 8, 4, 5, 2, 1};
        int initial_store[number_of_plants] = {0, 0, 0, 0, 0, 0};
        int *current_price_point[number_of_plants];
        for(int i = 0; i < number_of_plants; i++){
            current_price_point[i] = &current_price[i];
        }
        farmhouse home_house(number_of_plants, seed_types, initial_seed_numbers, 0, 5, 4, 4, true);
        granary storehouse(number_of_plants, 200, 0, seed_types, initial_store, 150, 2, false);
        brewery ale_house(100, 10, 200, 3, false);
        workhouse dormitory(0, 10, 200, 5, false);
        bool sim_loop = true, first_run = false;
        while(sim_loop == true){
            system("cls");
            main_ui(crop_fields, orchard_fields, multicrop_fields, size, month, money, upkeep, harvestable, home_house, storehouse, ale_house, dormitory);
            if((harvestable > 0) && (dormitory.interact_is_working() == true) && (dormitory.interact_harvesters() > 0) && (first_run == true)){
                int auto_harvest[number_of_plants], to_harvest = dormitory.interact_harvesters();
                int *auto_harvest_point[number_of_plants];
                for(int i = 0; i < number_of_plants; i++){
                    auto_harvest[i] = 0, auto_harvest_point[i] = &auto_harvest[i];
                }
                harvest_auto(seed_types, crop_fields_point, orchard_fields_point, multicrop_fields_point, auto_harvest_point, number_of_plants, to_harvest, &harvestable);
                for(int l = 0; l < number_of_plants; l++){
                    if(auto_harvest[l] > 0){
                        harvest_manage(seed_types[l], current_price[l], &storehouse, &ale_house, auto_harvest[l], &money);
                    }
                }
                first_run = false;
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
                case 'P':{ //Completely functioned
                    plant(seed_types, crop_fields_point, orchard_fields_point, multicrop_fields_point, &home_house, storehouse, ale_house, dormitory, size, plant_chars, small_plant_chars, base_yields);
                    system("pause");
                    break;
                }
                case 'h':
                case 'H':{ //Completely functioned
                    int index = -1, output = 0;
                    harvest_manual(crop_fields_point, orchard_fields_point, multicrop_fields_point, home_house, storehouse, ale_house, dormitory, size, &index, &output, number_of_plants, seed_types);
                    if(index != -1){
                        harvest_manage(seed_types[index], current_price[index], &storehouse, &ale_house, output, &money);
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
                case 'F':{ //Completely functioned
                    fertilise(crop_fields_point, orchard_fields_point, multicrop_fields_point, &home_house, storehouse, ale_house, dormitory, size);
                    system("pause");
                    break;
                }
                case 's':
                case 'S':{ //Acceptably functioned
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
                case 'A':{ //Acceptably functioned
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
                case 'D':{ //Acceptably functioned
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
                default:{ //Completely functioned
                    end_turn(crop_fields_point, orchard_fields_point, multicrop_fields_point, &home_house, storehouse, &ale_house, dormitory, &harvestable, &month, &money, upkeep, size, number_of_plants, &sim_loop, &simulation, &first_run, current_price_point, base_price, price_variation);
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