#ifndef FARMHOUSE_H_INCLUDED
#define FARMHOUSE_H_INCLUDED
#include "building.h"
#include "base_functions.h"
#include <string>

class farmhouse : public building{
    private:
        int fertiliser, seed_totals[6], num_seed_types;
        std::string seed_types[6];

    public:
        farmhouse(int, std::string[], int[], int, int, int, int, bool);
        int buy_menu(int, int[], int *);
        void change_seed_totals(std::string, int);
        void change_fertiliser(int);

        //VARIABLE INTERACTIONS//
        int interact_fertiliser();
        void interact_fertiliser(int);
        int interact_seed_totals(std::string);
        void interact_seed_totals(std::string, int);
        int interact_num_seed_types();
        void interact_num_seed_types(int);
        std::string interact_seed_types(int);
        void interact_seed_types(std::string, int);
};

#endif //FARMHOUSE_H_INCLUDED