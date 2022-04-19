#ifndef GRANARY_H_INCLUDED
#define GRANARY_H_INCLUDED
#include "building.h"
#include "crop.h"
#include "orchard.h"
#include "multicrop.h"
#include "farmhouse.h"
#include "brewery.h"
#include "workhouse.h"
#include <string>
#include <vector>

class granary : public building{
    private:
        int storage_space, current_total, store_totals[6], num_store_types;
        std::string store_types[6];

    public:
        granary(int, int, int, std::string[], int[], int, int, bool);
        int set_up(std::vector<std::vector<crop>>, std::vector<std::vector<orchard>>, std::vector<std::vector<multicrop>>, farmhouse, brewery, workhouse, int);
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