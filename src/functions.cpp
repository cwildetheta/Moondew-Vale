#include "../include/functions.h"
#include <iostream>

std::string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

void options(int lines_printed, granary storehouse, brewery ale_house, workhouse dormitory, int month, int money, int upkeep) //This function should only be called by the UI function.
{
    if(lines_printed == 0){
        std::cout << "          " << "Current month: " << months[month] << ".";
    }
    else if(lines_printed == 1){
        std::cout << "          " << "Current money: \x9C" << money << ".";
    }
    else if(lines_printed == 2){
        std::cout << "          " << "Current upkeep: \x9C" << upkeep << ".";
    }
    else if(lines_printed == 3){
        std::cout << "          ";
    }
    else if(lines_printed == 4){
        std::cout << "          " << "Press p to plant a crop.";
    }
    else if(lines_printed == 5){
        std::cout << "          " << "Press h to harvest a crop.";
    }
    else if(lines_printed == 6){
        std::cout << "          " << "Press c to clear a field.";
    }
    else if(lines_printed == 7){
        std::cout << "          " << "Press f to fertilise a field.";
    }
    else if(lines_printed == 8){
        std::cout << "          ";
    }
    else if(lines_printed == 9){
        std::cout << "          " << "Press b to buy more seeds.";
    }
    else if(lines_printed == 10){
        if(storehouse.interact_is_working() == true){
            std::cout << "          " << "Press s to view the storehouse.";
        }
        else{
            std::cout << "          " << "Press s to build a storehouse.";
        }
    }
    else if(lines_printed == 11){
        if(ale_house.interact_is_working() == true){
            std::cout << "          " << "Press a to view the brewery.";
        }
        else{
            std::cout << "          " << "Press a to build a brewery.";
        }
    }
    else if(lines_printed == 12){
        if(dormitory.interact_is_working() == true){
            std::cout << "          " << "Press d to view the dormitory.";
        }
        else{
            std::cout << "          " << "Press d to build a dormitory.";
        }
    }
    else if(lines_printed == 13){
        std::cout << "          ";
    }
    else if(lines_printed == 14){
        std::cout << "          " << "Press q to exit.";
    }
    else if(lines_printed == 15){
        std::cout << "          " << "Press any other key to move on to the next season.";
    }
}

void main_ui(std::vector<std::vector<crop>> crop_fields, std::vector<std::vector<orchard>> orchard_fields, std::vector<std::vector<multicrop>> multicrop_fields, int size, int month, int money, int upkeep, int harvestable, farmhouse home_house, granary storehouse, brewery ale_house, workhouse dormitory)
{
    int lines_printed = 0;
    std::cout << "-------------------------------------------------------------------------------------" << std::endl;
    for(int i = 0; i < 3*size; i++){
        std::cout << "|";
        for(int k = 0; k < 3*size; k++){
            //std::cout << " ";
            if(crop_fields[i/3][k/3].interact_is_active() == true){
                if(crop_fields[i/3][k/3].interact_is_fertilised() == false){
                    if(crop_fields[i/3][k/3].interact_is_ripe() == true){
                        std::cout << crop_fields[i/3][k/3].interact_symbol() << crop_fields[i/3][k/3].interact_symbol() << crop_fields[i/3][k/3].interact_symbol();
                    }
                    else if(crop_fields[i/3][k/3].interact_lifestage() == 0){
                        std::cout << "^^^";
                    }
                    else{
                        std::cout << crop_fields[i/3][k/3].interact_immature_symbol() << crop_fields[i/3][k/3].interact_immature_symbol() << crop_fields[i/3][k/3].interact_immature_symbol();
                    }
                }
                else{
                    if((i%3 == 1) && (k%3 == 1)){
                        std::cout << " f ";
                    }
                    else{
                        if(crop_fields[i/3][k/3].interact_is_ripe() == true){
                            std::cout << crop_fields[i/3][k/3].interact_symbol() << crop_fields[i/3][k/3].interact_symbol() << crop_fields[i/3][k/3].interact_symbol();
                        }
                        else if(crop_fields[i/3][k/3].interact_lifestage() == 0){
                            std::cout << "^^^";
                        }
                        else{
                            std::cout << crop_fields[i/3][k/3].interact_immature_symbol() << crop_fields[i/3][k/3].interact_immature_symbol() << crop_fields[i/3][k/3].interact_immature_symbol();
                        }
                    }
                }
            }
            else if(orchard_fields[i/3][k/3].interact_is_active() == true){
                if(crop_fields[i/3][k/3].interact_is_fertilised() == false){
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
                else{
                    if((i%3 == 1) && (k%3 == 1)){
                        std::cout << " f ";
                    }
                    else{
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
                }
            }
            else if(multicrop_fields[i/3][k/3].interact_is_active() == true){
                if(crop_fields[i/3][k/3].interact_is_fertilised() == false){
                    if(multicrop_fields[i/3][k/3].interact_is_producing() == true){
                        std::cout << multicrop_fields[i/3][k/3].interact_symbol() << multicrop_fields[i/3][k/3].interact_symbol() << multicrop_fields[i/3][k/3].interact_symbol();
                    }
                    else if(multicrop_fields[i/3][k/3].interact_lifestage() == 0){
                        std::cout << "^^^";
                    }
                    else{
                        std::cout << multicrop_fields[i/3][k/3].interact_immature_symbol() << multicrop_fields[i/3][k/3].interact_immature_symbol() << multicrop_fields[i/3][k/3].interact_immature_symbol();
                    }
                }
                else{
                    if((i%3 == 1) && (k%3 == 1)){
                        std::cout << " f ";
                    }
                    else{
                        if(multicrop_fields[i/3][k/3].interact_is_producing() == true){
                            std::cout << multicrop_fields[i/3][k/3].interact_symbol() << multicrop_fields[i/3][k/3].interact_symbol() << multicrop_fields[i/3][k/3].interact_symbol();
                        }
                        else if(multicrop_fields[i/3][k/3].interact_lifestage() == 0){
                            std::cout << "^^^";
                        }
                        else{
                            std::cout << multicrop_fields[i/3][k/3].interact_immature_symbol() << multicrop_fields[i/3][k/3].interact_immature_symbol() << multicrop_fields[i/3][k/3].interact_immature_symbol();
                        }
                    }
                }
            }
            else if((home_house.interact_is_working() == true) && ((home_house.interact_x_location()-1) == k/3) && ((home_house.interact_y_location()-1) == i/3)){
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
            else if((storehouse.interact_is_working() == true) && ((storehouse.interact_x_location()-1) == k/3) && ((storehouse.interact_y_location()-1) == i/3)){
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
            else if((ale_house.interact_is_working() == true) && ((ale_house.interact_x_location()-1) == k/3) && ((ale_house.interact_y_location()-1) == i/3)){
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
                    std::cout << char(219) << "Br";
                }
                else if((i%3 == 1) && (k%3 == 1)){
                    std::cout << " Br";
                }
                else if((i%3 == 1) && (k%3 == 2)){
                    std::cout << "Br" << char(219);
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
            else if((dormitory.interact_is_working() == true) && ((dormitory.interact_x_location()-1) == k/3) && ((dormitory.interact_y_location()-1) == i/3)){
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
                    std::cout << char(219) << " D";
                }
                else if((i%3 == 1) && (k%3 == 1)){
                    std::cout << " D ";
                }
                else if((i%3 == 1) && (k%3 == 2)){
                    std::cout << "D " << char(219);
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
        options(lines_printed, storehouse, ale_house, dormitory, month, money, upkeep);
        std::cout << std::endl;
        lines_printed++;
        if((i+1)%3 == 0){
            std::cout << "-------------------------------------------------------------------------------------";
            options(lines_printed, storehouse, ale_house, dormitory, month, money, upkeep);
            std::cout << std::endl;
            lines_printed++;
        }
    }
    if(harvestable > 0){
        std::cout << "There are " << harvestable << " fields ready to be harvested." << std::endl;
    }
    std::cout << std::endl << std::endl;
}

int change_prices(int current_price, int base_price, int price_variation)
{
    srand(time(NULL));
    current_price = rand()%(2*price_variation) + (base_price - price_variation);

    return current_price;
}

void test_function(farmhouse *home_house)
{
    home_house->change_seed_totals("Wheat", 5);
    std::cout << "Upadating seed totals." << std::endl;
}