#ifndef GRANARY_H_INCLUDED
#define GRANARY_H_INCLUDED
#include "building.h"
#include <string>

class granary : public building{
    private:
        int storage_space, current_total, store_totals[6], num_store_types;
        std::string store_types[6];

    public:
        granary(int, int, int, std::string[], int[]);
        void calculate_total();
        void increase_size(int);
        void add_to_store(std::string, int);
        int sell_from_store(std::string, int);
        int move_from_store(std::string, int);

        //VARIABLE INTERACTIONS//
        int interact_storage_space();
        void interact_storage_space(int);
        int interact_current_total();
        void interact_current_total(int);
        int interact_store_totals(std::string);
        void interact_store_totals(std::string, int);

};

#endif //GRANARY_H_INCLUDED