/************
  This contains all the I/O pins used by
  each peripheral
************/

// addresses assigned to the TOF sensors
#define LOX_L1_ADDRESS 0x30
#define LOX_L2_ADDRESS 0x31
#define LOX_R1_ADDRESS 0x32
#define LOX_R2_ADDRESS 0x33
#define LOX_FW_ADDRESS 0x34

// address of the MPU6050
#define MPU_addr 0x68

// set the pins to shutdown TOF
#define sht_LOX_L1 11
#define sht_LOX_L2 8
#define sht_LOX_R1 9
#define sht_LOX_R2 10
#define sht_LOX_FW 13

// define LED pins for left sensor and right sensor indicators
#define LED_L 37
#define LED_R 38

// define encoder pins for the motors
#define ENCODER1 18 //motor L - A
#define ENCODER2 19 //motor L - B
#define ENCODER3 2 //motor R - A
#define ENCODER4 3 //motor R - B
