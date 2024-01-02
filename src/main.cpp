/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       noahl                                                     */
/*    Created:      11/28/2023, 10:23:11 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

const int PORT1 = 0;
const int PORT2 = 1;
const int PORT3 = 2;
const int PORT4 = 10;
const int PORT5 = 11;
const int PORT6 = 12;


vex::controller Controller();
vex::brain Brain();
vex::triport leftTriport(0);
vex::triport rightTriport(7);
vex::digital_out leftWing = digital_out(leftTriport);
vex::digital_out rightWing = digital_out(rightTriport);
vex::motor l1(PORT1);
vex::motor l2(PORT2);
vex::motor l3(PORT3);
vex::motor r1(PORT4);
vex::motor r2(PORT5);
vex::motor r3(PORT6);
vex::motor_group left(l1,l2,l3);
vex::motor_group right(r1,r2,r3);
vex::drivetrain Drivetrain(left, right);
competition Competition;

void pre_auton(void) {

}

void autonomous(void) {
  
}

// Controller callbacks

void move() {
  Drivetrain.drive(forward);
}

void turn() {
  Drivetrain.turn(right);
}

void wingsOpenClose() {
  if (leftWing.value() == true) {
    rightWing.set(false);
    leftWing.set(false);
  }
  else {
    rightWing.set(true);
    leftWing.set(true);
  }
}

void usercontrol(void) {
  while (1) {
    Controller.Axis2.changed(move);
    Controller.Axis1.changed(turn);
    Controller.ButtonX.pressed(wingsOpenClose);
    wait(20, msec);
  }
}

int main() {
  
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}
