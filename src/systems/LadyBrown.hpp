
#pragma once

#include "../Constants.hpp"
#include "pros/motors.hpp"
#include "pros/motor_group.hpp"
#include "../autonomous/PIDController.hpp"
#include <functional>

using namespace Constants;
using namespace pros;
using namespace adi;


//New wing will work with motors


struct LadyBrown {
    private:
        Motor LB_mtr = Motor(LB_p);
   
        MotorGroup LB_mtrGroup = MotorGroup({LB_p});
        PIDController pidController = PIDController(kP, kI, kD,0.1); 


    public:
        LadyBrown() {
            LB_mtrGroup.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        }



        void turnAngle(double TurnAngle){
            double direction = (TurnAngle < 0) ? -1 : 1;
        
            TurnAngle = std::abs(TurnAngle);

            int ticks = (TurnAngle / 360.0) * LB_ticks_per_rev;

            //Reseting the position of the left and right group of motors
            LB_mtrGroup.tare_position();

            //Setting the target ticks
            pidController.setTargetTicks(ticks);
        
            while (std::abs(W1_mtr.get_position()) < ticks) {
                double controlRPM = direction * pidController.compute(std::abs(LB_mtr.get_position()));

                LB_mtrGroup.move_velocity(controlRPM);

                delay(20);
            }

            LB_mtrGroup.move_velocity(0);
        
            pidController.reset();

            delay(delayMove);
        }


};
