/************
  This contains all the global variables used
************/

// encoder positions i.e. total pulses
volatile long int encoder1_pos = 0;
volatile long int encoder2_pos = 0;
volatile long int encoder3_pos = 0;
volatile long int encoder4_pos = 0;

// this holds the TOF measurement
VL53L0X_RangingMeasurementData_t measure_L;
VL53L0X_RangingMeasurementData_t measure_R;

// variables and objects for PID control
float Kp, Ki, Kd;
double Setpoint, Input, PWMReduction;
int PWMred_cap;
ArduPID PID_centering;

// objects for the vl53l0x
Adafruit_VL53L0X LOX_L = Adafruit_VL53L0X();
Adafruit_VL53L0X LOX_R = Adafruit_VL53L0X();

// objects for the motors
CytronMD motorL(PWM_DIR, 6, 7);  // PWM = Pin 5, DIR = Pin 4.
CytronMD motorR(PWM_DIR, 5, 4);  // PWM = Pin 6, DIR = Pin 7.

//PID Variables - Fergal
double Ltof_old , Rtof_old;
double Ltof_curr, Rtof_curr;
double time_old , time_curr, timeElapsed;
double error_old, error_curr;
double cumError , rateError;
double ideal_dist_from_wall = 100; //need to figure this oot

//stop time of motors after moving or turning
int stop_time = 500;
int turn90_time = 275;

//variables and objects for servo
Servo servo;
int servoPos = 0;    // variable to store the servo position
