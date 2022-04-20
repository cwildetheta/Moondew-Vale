#include "../include/workhouse.h"
#include <iostream>

workhouse::workhouse(int int_input, int int_input_2, int cost_input, int upkeep_input, bool is_working_input)
{
    workers = int_input, max_workers = int_input_2;
    harvesters = 0, fertilisers = 0;
    interact_cost(cost_input);
    interact_upkeep(upkeep_input);
    interact_is_working(is_working_input);
}
void workhouse::increase_workers(int *money, int *upkeep)
{
    int int_input = 0;
    char reply;
    bool reply_loop = true;
    std::cout << "You currently have " << workers << " workers out of a potential maximum of " << max_workers << "." << std::endl;
    while(reply_loop == true){
        std::cout << "Would you like to hire new workers or fire current workers? h to hire or f to fire: ";
        std::cin >> reply;
        switch(reply){
            case 'h':
            case 'H':{
                if(workers != max_workers){
                    std::cout << "You have \x9C" << *money << ", and workers cost \x9C" << "25 to hire, with an upkeep of \x9C" << "2." << std::endl;
                    int_input = int_inputter("How many workers would you like to hire: ");
                    if((int_input >=0) && (int_input <= 10)){
                        if(int_input > (max_workers - workers)){
                            int_input = (max_workers - workers);
                        }
                        if((int_input*25) > *money){
                            std::cout << "You don't have enough money to afford that many workers." << std::endl;
                        }
                        else{
                            std::cout << "Hiring " << int_input << " new workers." << std::endl;
                            workers += int_input;
                            *money -= (25*int_input);
                            *upkeep += (2*int_input);
                        }
                    }
                    else{
                        std::cout << "Invalid input." << std::endl;
                    }
                }
                else{
                    std::cout << "You can't hire anymore workers." << std::endl;
                }
                reply_loop = false;
                break;
            }
            case 'f':
            case 'F':{
                if(workers != 0){
                    int_input = int_inputter("How many workers do you want to fire: ");
                    if(int_input > workers){
                        int_input = workers;
                    }
                    std::cout << "Firing " << int_input << " workers." << std::endl;
                    workers -= int_input;
                    *upkeep -= (2*int_input);
                    while((harvesters + fertilisers) > workers){
                        if(fertilisers > 0){
                            fertilisers--;
                        }
                        else{
                            harvesters--;
                        }
                    }
                }
                else{
                    std::cout << "You have no workers to fire." << std::endl;
                }
                reply_loop = false;
                break;
            }
            default:{
                break;
            }
        }
    }
}
void workhouse::automate_harvest()
{
    int int_input = int_inputter("How many workers do you want to assign to harvesting (negative to remove): ");
    if((int_input >= -10) && (int_input <= 10)){
        if(int_input > (workers - harvesters - fertilisers)){
            std::cout << "You don't have that many free workers." << std::endl;
        }
        else{
            harvesters += int_input;
        }
    }
    else{
        std::cout << "Invalid input." << std::endl;
    }
}
void workhouse::automate_fertilise()
{
    int int_input = int_inputter("How many workers do you want to assign to fertilising (negative to remove): ");
    if(int_input > (workers - harvesters - fertilisers)){
        std::cout << "You don't have that many free workers." << std::endl;
    }
    else{
        fertilisers += int_input;
    }
}

//INPUTS AND OUTPUTS//
int workhouse::interact_workers()
{
    return workers;
}
void workhouse::interact_workers(int int_input)
{
    workers = int_input;
}
int workhouse::interact_max_workers()
{
    return max_workers;
}
void workhouse::interact_max_workers(int int_input)
{
    max_workers = int_input;
}
int workhouse::interact_harvesters()
{
    return harvesters;
}
void workhouse::interact_harvesters(int int_input)
{
    harvesters = int_input;
}
int workhouse::interact_fertilisers()
{
    return fertilisers;
}
void workhouse::interact_fertilisers(int int_input)
{
    fertilisers = int_input;
}