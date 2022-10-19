//include libraries
#include "h_libraries.h"

//include header files for pins and global variables
#include "h_pins.h"
#include "h_global_vars.h"

void setup() {
  serial_init(115200);
  pins_init();
  TOF_init();
}

void loop() {
  //hard coded route for development. Implement into the NavMaze in phase B
  Forward2("D"); //MAZE 1 START
  Turn90('L');
  Forward2("AD");
  Turn90('L');
  Forward2("AC");
  Turn90('R');
  Forward2("AD");
  Turn90('L');
  Forward2("C");
  Turn90('R');
  Forward2("ACAC");
  Forward(50);
  Turn90('R');
  Forward(1000);
  Forward2("AC"); //start of ramp
  Forward(100);
  Turn90('R');
  Forward2("AC");
  Forward(10);
  Turn90('R');
  Forward2("AC");
  Turn90('R');
  Forward2("AC");
  Turn90('R');
  Forward2("ADAD");//start of maze 2
  Turn90('L');
  Forward2("AD");
  Turn90('L');
  Forward2("AD");
  Turn90('L');
  Forward2("AC");
  Turn90('R');
  Forward2("ADAD");
  Turn90('L');
  Forward2("A");

  while (1) {} //end of program


  //dev code for testing the left and right turning functions
  //Turn90('L');
  //delay(2000);
  //Turn90('L');
  //delay(2000);
  //Turn90('L');
  //delay(2000);
  //Turn90('L');
  //delay(2000);
  //Turn90('R');
  //delay(2000);
  //Turn90('R');
  //delay(2000);
  //Turn90('R');
  //delay(2000);
  //Turn90('R');
  //delay(2000);
}
