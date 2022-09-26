#include "CytronMotorDriver.h"
#include "Adafruit_VL53L0X.h"

// address we will assign if dual sensor is present
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31

// set the pins to shutdown TOF
#define SHT_LOX1 9
#define SHT_LOX2 8

#define ENCODER1 18 //motor 1
#define ENCODER2 19 //motor 1
#define ENCODER3 2 //motor  2
#define ENCODER4 3 //motor 2

volatile long int encoder1_pos = 0;
volatile long int encoder2_pos = 0;
volatile long int encoder3_pos = 0;
volatile long int encoder4_pos = 0;

// objects for the vl53l0x
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
// objects for the motors
CytronMD motor1(PWM_DIR, 5, 4);  // PWM = Pin 5, DIR = Pin 4.
CytronMD motor2(PWM_DIR, 6, 7);  // PWM = Pin 6, DIR = Pin 7.

// this holds the TOF measurement
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;

void setup() {
  pinMode(ENCODER1, INPUT);
  pinMode(ENCODER2, INPUT);
  pinMode(ENCODER3, INPUT);
  pinMode(ENCODER4, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCODER1), encoder1, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER2), encoder2, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER3), encoder3, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER4), encoder4, RISING);
  Serial.begin(9600);
}

void loop() {
  //  motor.setSpeed(128);  // Run forward at 50% speed.
  //  delay(2000);

  //  float timeold;
  //  float timecurr;
  //  float pos1old;
  //  float pos1curr;
  //  float pos2old;
  //  float pos2curr;
  //  float timetemp;
  //
  //  for (float i = 0; i < 255; i++) { //loop to measure the motor speed in pulses per sec
  //    timeold = timecurr;
  //    timecurr = millis();
  //    pos1old = pos1curr;
  //    pos1curr = encoder1_pos;
  //    pos2old = pos2curr;
  //    pos2curr = encoder3_pos;
  //
  //    motor1.setSpeed(i);        // Run bad motor forward at full speed.
  //    motor2.setSpeed(i * 0.9);  // Run good motor forward at full speed. Tuned PWM by multiplying with 0.9 to try to match other motor's speed profile
  //
  //    float motor1_speed = (pos1curr - pos1old) * 10 / (timecurr - timeold);
  //    float motor2_speed = (pos2curr - pos2old) * 10 / (timecurr - timeold);
  //
  //    Serial.println(String(motor1_speed) + " " + String(motor2_speed));
  //    delay(50);
  //  }
  int turn_time = 1000;

  Left(turn_time);
  Forward(1);
  Right(turn_time);
  Forward(2);
  Right(turn_time);
  Forward(3);
  Left(turn_time);
  Forward(4);
}







void encoder1() {
  if (digitalRead(ENCODER1) == HIGH) {
    encoder1_pos++;
  } else {
    encoder1_pos--;
  }
}

void encoder2() {
  if (digitalRead(ENCODER2) == HIGH) {
    encoder2_pos++;
  } else {
    encoder2_pos--;
  }
}

void encoder3() {
  if (digitalRead(ENCODER3) == HIGH) {
    encoder3_pos++;
  } else {
    encoder3_pos--;
  }
}

void encoder4() {
  if (digitalRead(ENCODER4) == HIGH) {
    encoder4_pos++;
  } else {
    encoder4_pos--;
  }
}
