#ifndef GRANARY_H_INCLUDED
#define GRANARY_H_INCLUDED
#include "building.h"
#include "base_functions.h"
#include <string>
#include <vector>

class granary : public building{
    private:
        int storage_space, current_total, store_totals[6], num_store_types;
        std::string store_types[6];

    public:
        granary(int, int, int, std::string[], int[], int, int, bool);
        void interact(std::string[], int[], int *, int *);
        void calculate_total();
        void increase_size(int);
        void add_to_store(std::string, int);

        //VARIABLE INTERACTIONS//
        int interact_storage_space();
        void interact_storage_space(int);
        int interact_current_total();
        void interact_current_total(int);
        int interact_store_totals(std::string);
        void interact_store_totals(std::string, int);
        int interact_num_store_types();
        void interact_num_store_types(int);
        std::string interact_store_types(int);
        void interact_store_types(std::string, int);

};

#endif //GRANARY_H_INCLUDED