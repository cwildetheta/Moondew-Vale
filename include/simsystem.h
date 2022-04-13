#ifndef SIMSYSTEM_H_INCLUDED
#define SIMSYSTEM_H_INCLUDED
#include "../include/field.h"
#include "../include/crop.h"
#include "../include/orchard.h"
#include "../include/multicrop.h"
#include <string>

class simsystem{
    private:
        int size;
        crop crop_fields[1][1];
        orchard orchard_fields[1][1];
        multicrop multicrop_fields[1][1];
        field fields[7][7];

    public:
        simsystem(int);
        void set_up(int);
        void display_fields(int);

        //VARIABLE INTERACTIONS//
        int interact_size();
        void interact_size(int);

};

#endif //SIMSYSTEM_H_INCLUDED