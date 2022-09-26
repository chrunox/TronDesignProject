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
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }

  //set pins for encoders
  pinMode(ENCODER1, INPUT);
  pinMode(ENCODER2, INPUT);
  pinMode(ENCODER3, INPUT);
  pinMode(ENCODER4, INPUT);

  //set pins for TOF sensors
  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);

  //reset and initialize TOF sensors
  Serial.println(F("Shutdown pins inited..."));
  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  Serial.println(F("Both in reset mode...(pins are low)"));
  Serial.println(F("Starting..."));
  setID();

  attachInterrupt(digitalPinToInterrupt(ENCODER1), encoder1, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER2), encoder2, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER3), encoder3, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER4), encoder4, RISING);
}

void loop() {
  //  motor.setSpeed(128);  // Run forward at 50% speed.
  //  delay(2000);

  //    float timeold;
  //    float timecurr;
  //    float pos1old;
  //    float pos1curr;
  //    float pos2old;
  //    float pos2curr;
  //    float timetemp;
  //
  //  int turn_time = 1000;
  //
  //  Left(turn_time);
  //  Forward(1);
  //  Right(turn_time);
  //  Forward(2);
  //  Right(turn_time);
  //  Forward(3);
  //  Left(turn_time);
  //  Forward(4);
  char F1[] = "ACBDA";
  Forward(F1);
  Right(1000);
  Forward(F1);
  Left(1000);
  
}
