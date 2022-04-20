#ifndef WORKHOUSE_H_INCLUDED
#define WORKHOUSE_H_INCLUDED
#include "building.h"
#include "base_functions.h"

class workhouse : public building{
    private:
        int workers, max_workers, harvesters, fertilisers;

    public:
        workhouse(int, int, int, int, bool);
        void increase_workers(int *, int *);
        void automate_harvest();
        void automate_fertilise();

        //VARIABLE INTERACTIONS//
        int interact_workers();
        void interact_workers(int);
        int interact_max_workers();
        void interact_max_workers(int);
        int interact_harvesters();
        void interact_harvesters(int);
        int interact_fertilisers();
        void interact_fertilisers(int);
};

#endif //WORKHOUSE_H_INCLUDED