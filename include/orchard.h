#ifndef ORCHARD_H_INCLUDED
#define ORCHARD_H_INCLUDED
#include "field.h"
#include <string>

class orchard : public field{
    private:
        //int age;
        bool is_producing;

    public:
        //void grow();
        int harvest_field();
        void begin(int, bool);

        //VARIABLE INTERACTIONS//
        //int interact_age();
        //void interact_age(int);
        bool interact_is_producing();
        void interact_is_producing(bool);
};

#endif //ORCHARD_H_INCLUDED