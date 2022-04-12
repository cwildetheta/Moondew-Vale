#include "../include/crop.h"
#include "../include/orchard.h"
#include "../include/multicrop.h"
#include "../include/farmhouse.h"
#include "../include/granary.h"
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
        std::string seed_types[6] = {"Wheat", "Barley", "Apple", "Orange", "Courgette", "Tomato"};
        char plant_chars[6] = {'W', 'B', 'A', 'O', 'C', 'T'};
        char small_plant_chars[6] = {'w', 'b', 'a', 'o', 'c', 't'};
        int initial_seed_numbers[6] = {10, 10, 5, 5, 2, 2};
        int seed_prices[6] = {30, 45, 35, 35, 25, 20};
        int base_yields[6] = {15, 15, 5, 5, 5, 5};
        int base_price[6] = {5, 10, 6, 8, 3, 2}, current_price[6] = {5, 10, 6, 8, 3, 2};
        int initial_store[6] = {0, 0, 0, 0, 0, 0};
        farmhouse home_house(6, seed_types, initial_seed_numbers);
        granary storehouse(6, 200, 0, seed_types, initial_store);
        home_house.interact_is_working(true);
        home_house.interact_upkeep(0);
        home_house.interact_fertiliser(5);
        home_house.interact_x_location(4);
        home_house.interact_y_location(4);
        storehouse.interact_is_working(false);
        storehouse.interact_cost(150);
        storehouse.interact_upkeep(2);
        bool sim_loop = true;
        int money = 100;
        int month = 1;
        int harvestable = 0;
        while(sim_loop == true){
            system("cls");
            std::cout << "Current money: " << money << " pounds." << std::endl;
            std::cout << "The current month is " << months[month] << "." << std::endl;
            for(int i = 0; i < size; i++){
                for(int k = 0; k < size; k++){
                    std::cout << " ";
                    if(crop_fields[i][k].interact_is_active() == true){
                        if(crop_fields[i][k].interact_is_ripe() == true){
                            std::cout << crop_fields[i][k].interact_symbol();
                        }
                        else{
                            std::cout << crop_fields[i][k].interact_immature_symbol();
                        }
                    }
                    else if(orchard_fields[i][k].interact_is_active() == true){
                        if(orchard_fields[i][k].interact_age() > 18){
                            std::cout << orchard_fields[i][k].interact_symbol();
                        }
                        else{
                            std::cout << orchard_fields[i][k].interact_immature_symbol();
                        }
                    }
                    else if(multicrop_fields[i][k].interact_is_active() == true){
                        if(multicrop_fields[i][k].interact_is_producing() == true){
                            std::cout << multicrop_fields[i][k].interact_symbol();
                        }
                        else{
                            std::cout << multicrop_fields[i][k].interact_immature_symbol();
                        }
                    }
                    else if(((home_house.interact_x_location()-1) == k) && ((home_house.interact_y_location()-1) == i)){
                        std::cout << "F";
                    }
                    else if(((storehouse.interact_x_location()-1) == k) && ((storehouse.interact_y_location()-1) == i)){
                        std::cout << "S";
                    }
                    else{
                        std::cout << ":";
                    }
                    std::cout << " ";
                }
                if(i == 0){
                    std::cout << "          " << "Press p to plant a crop.";
                }
                if(i == 1){
                    std::cout << "          " << "Press h to harvest a crop.";
                }
                if(i == 2){
                    std::cout << "          " << "Press b to buy more seeds.";
                }
                if(i == 3){
                    std::cout << "          " << "Press c to clear a field.";
                }
                if(i == 4){
                    std::cout << "          " << "Press f to fertilise a field.";
                }
                if(i == 5){
                    if(storehouse.interact_is_working() == true){
                        std::cout << "          " << "Press s to view the storehouse.";
                    }
                    else{
                        std::cout << "          " << "Press s to build a storehouse.";
                    }
                }
                if(i == 6){
                    std::cout << "          " << "Press q to exit.";
                }
                if(i == 7){
                    std::cout << "          " << "Press any other key to move on to the next season.";
                }
                std::cout << std::endl;
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
                    else if((home_house.interact_x_location() == (x_coord-1)) && (home_house.interact_y_location() == (y_coord-1))){
                        std::cout << "This location is already occupied by the farmhouse, please try again." << std::endl;
                    }
                    else if((crop_fields[x_coord-1][y_coord-1].interact_is_active() == true) || (orchard_fields[x_coord-1][y_coord-1].interact_is_active() == true) || (multicrop_fields[x_coord-1][y_coord-1].interact_is_active() == true)){
                        std::cout << "This field is already in use. Clear it before planting something else." << std::endl;
                    }
                    else{
                        if(home_house.interact_seed_totals(seed_types[seed_pick-1]) > 0){
                            if((seed_pick == 1) || (seed_pick == 2)){ //Needs work on generalising which field subclass is used.
                                crop_fields[x_coord-1][y_coord-1].plant_field(seed_types[seed_pick-1], plant_chars[seed_pick-1], small_plant_chars[seed_pick-1]);
                                home_house.change_seed_totals(seed_types[seed_pick-1], -1);
                                crop_fields[x_coord-1][y_coord-1].interact_lifestage(0);
                                crop_fields[x_coord-1][y_coord-1].interact_is_ripe(false);
                                crop_fields[x_coord-1][y_coord-1].interact_is_overripe(false);
                                crop_fields[x_coord-1][y_coord-1].interact_yield(base_yields[seed_pick-1]);
                            }
                            if((seed_pick == 3) || (seed_pick == 4)){
                                orchard_fields[x_coord-1][y_coord-1].plant_field(seed_types[seed_pick-1], plant_chars[seed_pick-1], small_plant_chars[seed_pick-1]);
                                home_house.change_seed_totals(seed_types[seed_pick-1], -1);
                                orchard_fields[x_coord-1][y_coord-1].interact_age(0);
                                orchard_fields[x_coord-1][y_coord-1].interact_is_producing(false);
                                orchard_fields[x_coord-1][y_coord-1].interact_yield(base_yields[seed_pick-1]);
                            }
                            if((seed_pick == 5) || (seed_pick == 6)){
                                multicrop_fields[x_coord-1][y_coord-1].plant_field(seed_types[seed_pick-1], plant_chars[seed_pick-1], small_plant_chars[seed_pick-1]);
                                home_house.change_seed_totals(seed_types[seed_pick-1], -1);
                                multicrop_fields[x_coord-1][y_coord-1].interact_lifestage(0);
                                multicrop_fields[x_coord-1][y_coord-1].interact_is_producing(false);
                                multicrop_fields[x_coord-1][y_coord-1].interact_yield(base_yields[seed_pick-1]);
                            }
                        }
                    }
                    system("pause");
                    break;
                }
                case 'h':
                case 'H':{
                    std::cout << "Please enter x coordinate: ";
                    int x_coord, y_coord, type_harvested = -1;
                    std::cin >> x_coord;
                    std::cout << "Please enter y coordinate: ";
                    std::cin >> y_coord;
                    if((x_coord < 1) || (x_coord > size)){
                        std::cout << "x coordinate out of bounds, please try again." << std::endl;
                    }
                    else if((y_coord < 1) || (y_coord > size)){
                        std::cout << "y coordinate out of bounds, please try again." << std::endl;
                    }
                    if(crop_fields[x_coord-1][y_coord-1].interact_is_active() == true){
                        int output = crop_fields[x_coord-1][y_coord-1].harvest_field();
                        if(output != -1){
                            int index;
                            for(int i = 0; i < 6; i++){ //Be careful with the limit here, make sure to change it if it needs it.
                                if(seed_types[i] == crop_fields[x_coord-1][y_coord-1].interact_name()){
                                    index = i;
                                }
                            }
                            std::cout << "You have harvested " << output << " units of " << crop_fields[x_coord-1][y_coord-1].interact_name() << ". ";
                            std::cout << "The current price of " << crop_fields[x_coord-1][y_coord-1].interact_name() << " is " << current_price[index] << " pounds." << std::endl;
                            std::cout << "You have made " << output*current_price[index] << " pounds." << std::endl;
                            money = money + (output*current_price[index]);
                            harvestable--;
                            crop_fields[x_coord-1][y_coord-1].clear_field();
                        }
                    }
                    else if(orchard_fields[x_coord-1][y_coord-1].interact_is_active() == true){
                        int output = orchard_fields[x_coord-1][y_coord-1].harvest_field();
                        if(output != -1){
                            int index;
                            for(int i = 0; i < 6; i++){ //Be careful with the limit here, make sure to change it if it needs it.
                                if(seed_types[i] == orchard_fields[x_coord-1][y_coord-1].interact_name()){
                                    index = i;
                                }
                            }
                            std::cout << "You have harvested " << output << " units of " << orchard_fields[x_coord-1][y_coord-1].interact_name() << ". ";
                            std::cout << "The current price of " << orchard_fields[x_coord-1][y_coord-1].interact_name() << " is " << current_price[index] << " pounds." << std::endl;
                            std::cout << "You have made " << output*current_price[index] << " pounds." << std::endl;
                            money = money + (output*current_price[index]);
                            harvestable--;
                            orchard_fields[x_coord-1][y_coord-1].interact_is_producing(false);
                        }
                    }
                    else if(multicrop_fields[x_coord-1][y_coord-1].interact_is_active() == true){
                        int output = multicrop_fields[x_coord-1][y_coord-1].harvest_field();
                        if(output != -1){
                            int index;
                            for(int i = 0; i < 6; i++){ //Be careful with the limit here, make sure to change it if it needs it.
                                if(seed_types[i] == multicrop_fields[x_coord-1][y_coord-1].interact_name()){
                                    index = i;
                                }
                            }
                            std::cout << "You have harvested " << output << " units of " << multicrop_fields[x_coord-1][y_coord-1].interact_name() << ". ";
                            std::cout << "The current price of " << multicrop_fields[x_coord-1][y_coord-1].interact_name() << " is " << current_price[index] << " pounds." << std::endl;
                            std::cout << "You have made " << output*current_price[index] << " pounds." << std::endl;
                            money = money + (output*current_price[index]);
                            harvestable--;
                            multicrop_fields[x_coord-1][y_coord-1].interact_is_producing(false);
                        }
                    }
                    else if((home_house.interact_x_location() == (x_coord-1)) && (home_house.interact_y_location() == (y_coord-1))){
                        std::cout << "This is your farmhouse. you can't harvest a building." << std::endl;
                    }
                    else{
                        std::cout << "There is nothing in this field." << std::endl;
                    }
                    system("pause");
                    break;
                }
                case 'b':
                case 'B':{
                    std::cout << "Which type of seeds would you like to buy? Seeds are bought in packs of 5.    Current money: "<< money << " pounds." << std::endl; //Generalise this later, ie. seed_types[i]
                    std::cout << "0. Fertiliser  Current ammount: " << std::setw(4) << home_house.interact_fertiliser() << "     Cost: 10 pounds." << std::endl;
                    std::cout << "1. Wheat       Current seeds: " << std::setw(6) << home_house.interact_seed_totals(seed_types[0]) << "     Cost: " << seed_prices[0] << " pounds." << std::endl;
                    std::cout << "2. Barley      Current seeds: " << std::setw(6) << home_house.interact_seed_totals(seed_types[1]) << "     Cost: " << seed_prices[1] << " pounds." << std::endl;
                    std::cout << "3. Apple       Current seeds: " << std::setw(6) << home_house.interact_seed_totals(seed_types[2]) << "     Cost: " << seed_prices[2] << " pounds." << std::endl;
                    std::cout << "4. Orange      Current seeds: " << std::setw(6) << home_house.interact_seed_totals(seed_types[3]) << "     Cost: " << seed_prices[3] << " pounds." << std::endl;
                    std::cout << "5. Courgette   Current seeds: " << std::setw(6) << home_house.interact_seed_totals(seed_types[4]) << "     Cost: " << seed_prices[4] << " pounds." << std::endl;
                    std::cout << "6. Tomato      Current seeds: " << std::setw(6) << home_house.interact_seed_totals(seed_types[5]) << "     Cost: " << seed_prices[5] << " pounds." << std::endl << std::endl;
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
                    if(crop_fields[x_coord-1][y_coord-1].interact_is_active() == true){
                        crop_fields[x_coord-1][y_coord-1].clear_field();
                        std::cout << "Field at " << x_coord << "," << y_coord << " cleared." << std::endl;
                        if(crop_fields[x_coord-1][y_coord-1].interact_is_ripe() == true){
                            harvestable--;
                        }
                    }
                    else if(orchard_fields[x_coord-1][y_coord-1].interact_is_active() == true){
                        orchard_fields[x_coord-1][y_coord-1].clear_field();
                        std::cout << "Field at " << x_coord << "," << y_coord << " cleared." << std::endl;
                        if(crop_fields[x_coord-1][y_coord-1].interact_is_ripe() == true){
                            harvestable--;
                        }
                    }
                    else if(multicrop_fields[x_coord-1][y_coord-1].interact_is_active() == true){
                        multicrop_fields[x_coord-1][y_coord-1].clear_field();
                        std::cout << "Field at " << x_coord << "," << y_coord << " cleared." << std::endl;
                        if(crop_fields[x_coord-1][y_coord-1].interact_is_ripe() == true){
                            harvestable--;
                        }
                    }
                    else if((home_house.interact_x_location() == (x_coord-1)) && (home_house.interact_y_location() == (y_coord-1))){
                        std::cout << "This is your farmhouse. You can't remove that: you live there." << std::endl;
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
                        if(crop_fields[x_coord-1][y_coord-1].interact_is_active() == true){
                            if(crop_fields[x_coord-1][y_coord-1].interact_is_fertilised() == false){
                                crop_fields[x_coord-1][y_coord-1].interact_is_fertilised(true);
                                home_house.interact_fertiliser(home_house.interact_fertiliser()-1);
                                std::cout << "Field at " << x_coord << "," << y_coord << " fertilised." << std::endl;
                            }
                            else{
                                std::cout << "This field is already fertilised." << std::endl;
                            }
                        }
                        else if(orchard_fields[x_coord-1][y_coord-1].interact_is_active() == true){
                            if(orchard_fields[x_coord-1][y_coord-1].interact_is_fertilised() == false){
                                orchard_fields[x_coord-1][y_coord-1].interact_is_fertilised(true);
                                home_house.interact_fertiliser(home_house.interact_fertiliser()-1);
                                std::cout << "Field at " << x_coord << "," << y_coord << " fertilised." << std::endl;
                            }
                            else{
                                std::cout << "This field is already fertilised." << std::endl;
                            }
                        }
                        else if(multicrop_fields[x_coord-1][y_coord-1].interact_is_active() == true){
                            if(multicrop_fields[x_coord-1][y_coord-1].interact_is_fertilised() == false){
                                multicrop_fields[x_coord-1][y_coord-1].interact_is_fertilised(true);
                                home_house.interact_fertiliser(home_house.interact_fertiliser()-1);
                                std::cout << "Field at " << x_coord << "," << y_coord << " fertilised." << std::endl;
                            }
                            else{
                                std::cout << "This field is already fertilised." << std::endl;
                            }
                        }
                        else if((home_house.interact_x_location() == (x_coord-1)) && (home_house.interact_y_location() == (y_coord-1))){
                            std::cout << "This is your farmhouse. You can't fertilise it." << std::endl;
                        }
                    }
                    system("pause");
                    break;
                }
                case 's':
                case 'S':{
                    if(storehouse.interact_is_working() == false){
                        std::cout << "It costs " << storehouse.interact_cost() << " pounds to build a storehouse." << std::endl;
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
                                    else if(crop_fields[x_coord-1][y_coord-1].interact_is_active() == true || orchard_fields[x_coord-1][y_coord-1].interact_is_active() == true || multicrop_fields[x_coord-1][y_coord-1].interact_is_active() == true){
                                        std::cout << "There is a field planted here. You need to clear it before a storehouse can be built here." << std::endl;
                                    }
                                    else if((home_house.interact_x_location() == (x_coord-1)) && (home_house.interact_y_location() == (y_coord-1))){
                                        std::cout << "That's the farmhouse, you can't build a storehouse here." << std::endl;
                                    }
                                    else{
                                        storehouse.interact_is_working(true);
                                        storehouse.interact_x_location(x_coord);
                                        storehouse.interact_y_location(y_coord);
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
                                std::cout << "The current price of " << seed_types[store_pick-1] << " is " << current_price[store_pick-1] << " pounds. How much would you like to sell?: ";
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
                    break;
                }
            }
        }
    }
    system("pause");
    system("cls");
    return 0;
}