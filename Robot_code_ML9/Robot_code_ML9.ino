#include "h_libraries.h"    //include libraries
#include "h_pins.h"         //include header files for pins and global variables
#include "h_global_vars.h"

void setup() {
  serial_init(115200);
  pins_init();
  mpu_init();
  tof_init();
  pid_init();
}

void loop() {
  read_tof(1);
  read_tof(2);
  read_tof(3);
  read_tof(4);
  read_tof(5);

  Serial.print(L1); Serial.print(" ");
  Serial.print(L2); Serial.print(" ");
  Serial.print(R1); Serial.print(" ");
  Serial.print(R2); Serial.print(" ");
  //  Serial.print(FW); Serial.println();
  Serial.println(read_mpu());
//  Forward(250);
//  TurnByAngle('R', 90);
    NavMaze();
  //  Forward_ramp("ABAB");
  //    TurnByAngle('L', 90);
  //  while (1);
  //  long old = millis();
  //  Forward("DAD");
  //  TurnByAngle('L', 90);

  //  Forward("DAD");
  //  TurnByAngle('L',90);
  //  while(1);
  //  //put code here that you want to test the timing of
  //
  //  Serial.println(millis() - old);
  //


}

String read_liabas_mind() {
  return "I want to die";
}
