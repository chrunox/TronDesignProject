/************
  This contains all the global variables used
************/

// encoder positions i.e. total pulses
volatile long int encoder1_pos = 0;
volatile long int encoder2_pos = 0;
volatile long int encoder3_pos = 0;
volatile long int encoder4_pos = 0;

// this holds the TOF measurement
VL53L0X_RangingMeasurementData_t measure_L1;
VL53L0X_RangingMeasurementData_t measure_L2;
VL53L0X_RangingMeasurementData_t measure_R1;
VL53L0X_RangingMeasurementData_t measure_R2;
VL53L0X_RangingMeasurementData_t measure_FW;
double L1, L2, R1, R2, FW;

// objects for the vl53l0x
Adafruit_VL53L0X LOX_L1 = Adafruit_VL53L0X();
Adafruit_VL53L0X LOX_L2 = Adafruit_VL53L0X();
Adafruit_VL53L0X LOX_R1 = Adafruit_VL53L0X();
Adafruit_VL53L0X LOX_R2 = Adafruit_VL53L0X();
Adafruit_VL53L0X LOX_FW = Adafruit_VL53L0X();

// objects for the motors
CytronMD motorL(PWM_DIR, 6, 7);  // PWM = Pin 5, DIR = Pin 4.
CytronMD motorR(PWM_DIR, 5, 4);  // PWM = Pin 6, DIR = Pin 7.

//PID Variables
//Centering PID
double cKp = 7.5, cKi = 0.05, cKd = 0.15; //PID turning for centering
double cSetpoint, cInput, cOutput;      //variables for centering
ArduPID PID_center;

//Forward distance PID
double fKp = 20, fKi = 0, fKd = 0.1; //PID turning for centering
double fSetpoint, fInput, fOutput;      //variables for centering
ArduPID PID_forward;

//Turning PID
double tKp = 10, tKi = 0.5, tKd = .1; //PID turning for centering
double tSetpoint, tInput, tOutput;      //variables for centering
ArduPID PID_turn;

double time_old , time_curr, timeElapsed;
double error_old, error_curr;
double sumError , rateError;
double ideal_dist_from_wall = 100; //need to figure this oot

//tof Variables
int L1_offset = -20, L2_offset = -60, R1_offset, R2_offset = 5, FW_offset;
double l = 68;

//stop time of motors after moving or turning
int stop_time = 75;
int turn90_time = 275; // obsolete

//variables and objects for servo
Servo servo;
int servoPos = 0;    // variable to store the servo position

//variables for mpu
double currYaw, prevYaw;
