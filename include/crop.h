#ifndef CROP_H_INCLUDED
#define CROP_H_INCLUDED
#include "field.h"
#include <string>

class crop : public field{
    private:
        int lifestage;
        bool is_ripe, is_overripe;

    public:
        void grow();
        int harvest_field();
        void begin(int, bool, bool);

        //VARIABLE INTERACTIONS//
        int interact_lifestage();
        void interact_lifestage(int);
        bool interact_is_ripe();
        void interact_is_ripe(bool);
        bool interact_is_overripe();
        void interact_is_overripe(bool);
};

#endif //CROP_H_INCLUDED