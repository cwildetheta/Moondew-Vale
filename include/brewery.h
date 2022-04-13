#ifndef BREWERY_H_INCLUDED
#define BREWERY_H_INCLUDED
#include "building.h"
#include <string>

class brewery : public building{
    private:
        int storage_space, current_total, stored_barley, stored_beer, brewing_cap;

    public:
        brewery(int, int);
        void calculate_total();
        void make_beer(int);
        void sell_beer(int);
        void transfer_barley(int);

        //VARIABLE INTERACTIONS//
        int interact_storage_space();
        void interact_storage_space(int);
        int interact_current_total();
        void interact_current_total(int);
        int interact_stored_barley();
        void interact_stored_barley(int);
        int interact_stored_beer();
        void interact_stored_beer(int);
        int interact_brewing_cap();
        void interact_brewing_cap(int);

};

#endif //BREWERY_H_INCLUDED