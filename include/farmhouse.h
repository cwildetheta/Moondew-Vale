#ifndef FARMHOUSE_H_INCLUDED
#define FARMHOUSE_H_INCLUDED
#include "building.h"
#include "base_functions.h"
#include <string>

class farmhouse : public building{
    private:
        int current_total, fertiliser, seed_totals[6], num_seed_types;
        std::string seed_types[6];

    public:
        farmhouse(int, std::string[], int[], int, int, int, int, bool);
        void change_seed_totals(std::string, int);
        int buy_menu(int, int[], int *);
        void change_fertiliser(int);

        //VARIABLE INTERACTIONS//
        int interact_current_total();
        void interact_current_total(int);
        int interact_fertiliser();
        void interact_fertiliser(int);
        int interact_seed_totals(std::string);
        void interact_seed_totals(std::string, int);
        std::string interact_seed_types();
        void interact_seed_types(std::string);
};

#endif //FARMHOUSE_H_INCLUDED