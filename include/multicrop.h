#ifndef MULTICROP_H_INCLUDED
#define MULTICROP_H_INCLUDED
#include "field.h"
#include <string>

class multicrop : public field{
    private:
        int lifestage;
        bool is_producing;

    public:
        void grow();
        int harvest_field();
        void begin(int, bool);

        //VARIABLE INTERACTIONS//
        int interact_lifestage();
        void interact_lifestage(int);
        bool interact_is_producing();
        void interact_is_producing(bool);
};

#endif //MULTICROP_H_INCLUDED