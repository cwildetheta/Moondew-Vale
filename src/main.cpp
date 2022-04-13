#include "../include/crop.h"
#include "../include/orchard.h"
#include "../include/multicrop.h"
#include "../include/farmhouse.h"
#include "../include/granary.h"
#include "../include/brewery.h"
#include "../include/workhouse.h"
#include "../include/simsystem.h"
#include <iostream>
#include <iomanip>

int main()
{
    system("cls");
    system("pause");
    std::string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    bool simulation = true;
    while(simulation == true){
        int size = 7;
        crop crop_fields[size][size];
        orchard orchard_fields[size][size];
        multicrop multicrop_fields[size][size];
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
        int base_price[number_of_plants] = {5, 10, 6, 8, 3, 2}, current_price[6] = {5, 10, 6, 8, 3, 2};
        int initial_store[number_of_plants] = {0, 0, 0, 0, 0, 0};
        farmhouse home_house(number_of_plants, seed_types, initial_seed_numbers);
        granary storehouse(number_of_plants, 200, 0, seed_types, initial_store);
        brewery ale_house(100, 10);
        workhouse dormitory(0);
        home_house.interact_is_working(true);
        home_house.interact_upkeep(0);
        home_house.interact_fertiliser(5);
        home_house.interact_x_location(4);
        home_house.interact_y_location(4);
        storehouse.interact_is_working(false);
        storehouse.interact_cost(150);
        storehouse.interact_upkeep(2);
        ale_house.interact_is_working(false);
        ale_house.interact_cost(200);
        ale_house.interact_upkeep(3);
        dormitory.interact_is_working(false);
        dormitory.interact_cost(200);
        dormitory.interact_upkeep(5);
        bool sim_loop = true;
        int money = 100;
        int month = 1;
        int harvestable = 0, upkeep = 0;
        while(sim_loop == true){
            system("cls");
            int lines_printed = 0;
            std::cout << "-------------------------------------------------------------------------------------" << std::endl;
            for(int i = 0; i < 3*size; i++){
                std::cout << "|";
                for(int k = 0; k < 3*size; k++){
                    //std::cout << " ";
                    if(crop_fields[i/3][k/3].interact_is_active() == true){
                        if(crop_fields[i/3][k/3].interact_is_fertilised() == false){
                            if(crop_fields[i/3][k/3].interact_is_ripe() == true){
                                std::cout << " " << crop_fields[i/3][k/3].interact_symbol() << " ";
                            }
                            else if(crop_fields[i/3][k/3].interact_lifestage() == 0){
                                std::cout << " ^ ";
                            }
                            else{
                                std::cout << " " << crop_fields[i/3][k/3].interact_immature_symbol() << " ";
                            }
                        }
                        else{
                            if((i%3 == 1) && (k%3 == 1)){
                                std::cout << " f ";
                            }
                            else{
                                if(crop_fields[i/3][k/3].interact_is_ripe() == true){
                                    std::cout << " " << crop_fields[i/3][k/3].interact_symbol() << " ";
                                }
                                else if(crop_fields[i/3][k/3].interact_lifestage() == 0){
                                    std::cout << " ^ ";
                                }
                                else{
                                    std::cout << " " << crop_fields[i/3][k/3].interact_immature_symbol() << " ";
                                }
                            }
                        }
                    }
                    else if(orchard_fields[i/3][k/3].interact_is_active() == true){
                        if(orchard_fields[i/3][k/3].interact_age() <= 18){
                            std::cout << " " << char(193) << " ";
                        }
                        else if((orchard_fields[i/3][k/3].interact_age() > 18) && (orchard_fields[i/3][k/3].interact_is_producing() == true)){
                            std::cout << " " << orchard_fields[i/3][k/3].interact_symbol() << " ";
                        }
                        else{
                            std::cout << " " << orchard_fields[i/3][k/3].interact_immature_symbol() << " ";
                        }
                    }
                    else if(multicrop_fields[i/3][k/3].interact_is_active() == true){
                        if(multicrop_fields[i/3][k/3].interact_is_producing() == true){
                            std::cout << " " << multicrop_fields[i/3][k/3].interact_symbol() << " ";
                        }
                        else if(multicrop_fields[i/3][k/3].interact_lifestage() == 0){
                            std::cout << " ^ ";
                        }
                        else{
                            std::cout << " " << multicrop_fields[i/3][k/3].interact_immature_symbol() << " ";
                        }
                    }
                    else if(((home_house.interact_x_location()-1) == k/3) && ((home_house.interact_y_location()-1) == i/3)){
                        if((i%3 == 0) && (k%3 == 0)){
                            std::cout << char(219) << char(223) << char(223);
                        }
                        else if((i%3 == 0) && (k%3 == 1)){
                            std::cout << char(223) << char(223) << char(223);
                        }
                        else if((i%3 == 0) && (k%3 == 2)){
                            std::cout << char(223) << char(223) << char(219);
                        }
                        else if((i%3 == 1) && (k%3 == 0)){
                            std::cout << char(219) << " H";
                        }
                        else if((i%3 == 1) && (k%3 == 1)){
                            std::cout << " H ";
                        }
                        else if((i%3 == 1) && (k%3 == 2)){
                            std::cout << "H " << char(219);
                        }
                        else if((i%3 == 2) && (k%3 == 0)){
                            std::cout << char(219) << char(220) << char(220);
                        }
                        else if((i%3 == 2) && (k%3 == 1)){
                            std::cout << char(220) << char(220) << char(220);
                        }
                        else if((i%3 == 2) && (k%3 == 2)){
                            std::cout << char(220) << char(220) << char(219);
                        }
                        //std::cout << " H ";
                    }
                    else if(((storehouse.interact_x_location()-1) == k/3) && ((storehouse.interact_y_location()-1) == i/3)){
                        if((i%3 == 0) && (k%3 == 0)){
                            std::cout << char(219) << char(223) << char(223);
                        }
                        else if((i%3 == 0) && (k%3 == 1)){
                            std::cout << char(223) << char(223) << char(223);
                        }
                        else if((i%3 == 0) && (k%3 == 2)){
                            std::cout << char(223) << char(223) << char(219);
                        }
                        else if((i%3 == 1) && (k%3 == 0)){
                            std::cout << char(219) << " S";
                        }
                        else if((i%3 == 1) && (k%3 == 1)){
                            std::cout << " S ";
                        }
                        else if((i%3 == 1) && (k%3 == 2)){
                            std::cout << "S " << char(219);
                        }
                        else if((i%3 == 2) && (k%3 == 0)){
                            std::cout << char(219) << char(220) << char(220);
                        }
                        else if((i%3 == 2) && (k%3 == 1)){
                            std::cout << char(220) << char(220) << char(220);
                        }
                        else if((i%3 == 2) && (k%3 == 2)){
                            std::cout << char(220) << char(220) << char(219);
                        }
                        //std::cout << " S ";
                    }
                    else{
                        std::cout << " ' ";
                    }
                    //std::cout << " ";
                    if((k+1)%3 == 0){
                        std::cout << "|";
                    }
                    else{
                        std::cout << " ";
                    }
                }
                if(lines_printed == 0){
                    std::cout << "          " << "Current month: " << months[month] << ".";
                }
                if(lines_printed == 1){
                    std::cout << "          " << "Current money: \x9C" << money << ".";
                }
                if(lines_printed == 2){
                    std::cout << "          " << "Current upkeep: \x9C" << upkeep << ".";
                }
                if(lines_printed == 3){
                    std::cout << "          ";
                }
                if(lines_printed == 4){
                    std::cout << "          " << "Press p to plant a crop.";
                }
                if(lines_printed == 5){
                    std::cout << "          " << "Press h to harvest a crop.";
                }
                if(lines_printed == 6){
                    std::cout << "          " << "Press b to buy more seeds.";
                }
                if(lines_printed == 7){
                    std::cout << "          " << "Press c to clear a field.";
                }
                if(lines_printed == 8){
                    std::cout << "          " << "Press f to fertilise a field.";
                }
                if(lines_printed == 9){
                    if(storehouse.interact_is_working() == true){
                        std::cout << "          " << "Press s to view the storehouse.";
                    }
                    else{
                        std::cout << "          " << "Press s to build a storehouse.";
                    }
                }
                if(lines_printed == 10){
                    std::cout << "          " << "Press q to exit.";
                }
                if(lines_printed == 11){
                    std::cout << "          " << "Press any other key to move on to the next season.";
                }
                std::cout << std::endl;
                lines_printed++;
                if((i+1)%3 == 0){
                    std::cout << "-------------------------------------------------------------------------------------";
                    if(lines_printed == 0){
                        std::cout << "          " << "Current month: " << months[month] << "." << std::endl;
                    }
                    else if(lines_printed == 1){
                        std::cout << "          " << "Current money: \x9C" << money << "." << std::endl;
                    }
                    else if(lines_printed == 2){
                        std::cout << "          " << "Current upkeep: \x9C" << upkeep << "." << std::endl;
                    }
                    else if(lines_printed == 3){
                        std::cout << "          " << std::endl;
                    }
                    else if(lines_printed == 4){
                        std::cout << "          " << "Press p to plant a crop." << std::endl;
                    }
                    else if(lines_printed == 5){
                        std::cout << "          " << "Press h to harvest a crop." << std::endl;
                    }
                    else if(lines_printed == 6){
                        std::cout << "          " << "Press b to buy more seeds." << std::endl;
                    }
                    else if(lines_printed == 7){
                        std::cout << "          " << "Press c to clear a field." << std::endl;
                    }
                    else if(lines_printed == 8){
                        std::cout << "          " << "Press f to fertilise a field." << std::endl;
                    }
                    else if(lines_printed == 9){
                        if(storehouse.interact_is_working() == true){
                            std::cout << "          " << "Press s to view the storehouse." << std::endl;
                        }
                        else{
                            std::cout << "          " << "Press s to build a storehouse." << std::endl;
                        }
                    }
                    else if(lines_printed == 10){
                        std::cout << "          " << "Press q to exit." << std::endl;
                    }
                    else if(lines_printed == 11){
                        std::cout << "          " << "Press any other key to move on to the next season." << std::endl;
                    }
                    else if(lines_printed == 12){
                        std::cout << "          " << "Upkeep this turn is " << upkeep << "." << std::endl;
                    }
                    else{
                        std::cout << std::endl;
                    }
                    lines_printed++;
                }
            }
            if(harvestable > 0){
                std::cout << "There are " << harvestable << " fields ready to be harvested." << std::endl;
            }
            std::cout << std::endl << std::endl;
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
                        if((storehouse.interact_is_working() == true) && ((storehouse.interact_storage_space()-storehouse.interact_current_total()) >= output)){
                            std::cout << ", or there is " << (storehouse.interact_storage_space()-storehouse.interact_current_total()) << " units of space available in the storehouse." << std::endl;
                            std::cout << "If you would like to store the harvest, press s, otherwise it will be sold: ";
                            char store_input;
                            std::cin >> store_input;
                            if(store_input == 's' || store_input == 'S'){
                                storehouse.add_to_store(seed_types[index], output);
                                std::cout << "The harvest has been stored." << std::endl;
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
                        }
                    }
                    else if(orchard_fields[y_coord-1][x_coord-1].interact_is_active() == true){
                        orchard_fields[y_coord-1][x_coord-1].clear_field();
                        std::cout << "Field at " << x_coord << "," << y_coord << " cleared." << std::endl;
                        if(crop_fields[y_coord-1][x_coord-1].interact_is_ripe() == true){
                            harvestable--;
                        }
                    }
                    else if(multicrop_fields[y_coord-1][x_coord-1].interact_is_active() == true){
                        multicrop_fields[y_coord-1][x_coord-1].clear_field();
                        std::cout << "Field at " << x_coord << "," << y_coord << " cleared." << std::endl;
                        if(crop_fields[y_coord-1][x_coord-1].interact_is_ripe() == true){
                            harvestable--;
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
                                    else{
                                        storehouse.interact_is_working(true);
                                        storehouse.interact_x_location(x_coord);
                                        storehouse.interact_y_location(y_coord);
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
                default:{
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