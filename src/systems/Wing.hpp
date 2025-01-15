
#pragma once


#include "../Constants.hpp"
#include "../../include/pros/adi.hpp"


using namespace Constants;
using namespace pros;
using namespace adi;


struct Wing {
    private:
        DigitalOut piston = DigitalOut(Wing_p);

    public:
        Wing() {
        }


        void unClamp() {
            piston.set_value(false);
        }


        void clamp() {
            piston.set_value(true);
        }


        void changeClampState(bool newState) {
            piston.set_value(newState);
        }


};