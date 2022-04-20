#include "../include/base_functions.h"
#include <iostream>
#include <limits>

int int_inputter(std::string request_output)
{
    bool in_int_loop = true;
    int int_input;
    while(in_int_loop == true){
        std::cout << request_output;
        std::cin >> int_input;
        if(std::cin.fail()){
            std::cout << "You did not enter an integer." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else{
            in_int_loop = false;
        }
    }
    return int_input;
}