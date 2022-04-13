#ifndef WORKHOUSE_H_INCLUDED
#define WORKHOUSE_H_INCLUDED
#include "building.h"

class workhouse : public building{
    private:
        int workers, harvesters, fertilisers;

    public:
        workhouse(int);
        void increase_workers(int);
        void automate_harvest(int);
        void automate_fertilise(int);

        //VARIABLE INTERACTIONS//
        int interact_workers();
        void interact_workers(int);
        int interact_harvesters();
        void interact_harvesters(int);
        int interact_fertilisers();
        void interact_fertilisers(int);
};

#endif //WORKHOUSE_H_INCLUDED