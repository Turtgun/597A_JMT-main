
#pragma once


#include "../Constants.hpp"
#include "../../include/pros/adi.hpp"


using namespace Constants;
using namespace pros;
using namespace adi;

//New wing will work with motors


struct Wing {
    private:
        Motor W1_mtr = Motor(W1_p);
        //Motor W2_mtr = Motor(W2_p);
        


        // Motor it2_mtr = Motor(it2_p);

        MotorGroup W_mtrGroup = MotorGroup({W1_p});
        PIDController pidController = PIDController(kP, kI, kD); 


    public:
        Wing() {
            W_mtrGroup.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        }



        void turnAngle(double TurnAngle){
            double direction = (TurnAngle < 0) ? 1: -1;
        
            TurnAngle = std::abs(TurnAngle);

            int ticks = (TurnAngle / 360.0) * WingEncoder_ticks_per_rev;

            //Reseting the position of the left and right group of motors
            W_mtrGroup.tare_position();

            //Setting the target ticks
            pidController.setTargetTicks(ticks);
        
            while (std::abs(W1_mtr.get_position()) < ticks) {
                double controlRPM = direction * pidController.compute(std::abs(TickAverage));

                W_mtrGroup.move_velocity(controlRPM);

                delay(20);
            }

            W_mtrGroup.move_velocity(0);
        
            pidController.reset();

            delay(delayMove);
        }


};

/*

OLD WING WHEN WE HAD PISTONS

struct Wing {
    private:
        DigitalOut piston1 = DigitalOut(Wing_p1);
        DigitalOut piston2 = DigitalOut(Wing_p2)

    public:
        Wing() {
        }


        void unClamp() {
            piston1.set_value(false);
            piston2.set_value(false);
        }


        void clamp() {
            piston1.set_value(true);
            piston2.set_value(true);
        }


        void changeClampState(bool newState) {
            piston1.set_value(newState);
            piston2.set_value(newState);
        }


};

*/