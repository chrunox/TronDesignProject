/************
  This contains all the I/O pins used by
  each peripheral
************/

// address we will assign if dual sensor is present
#define LOX_L_ADDRESS 0x30
#define LOX_R_ADDRESS 0x31

// set the pins to shutdown TOF
#define sht_LOX_L 8
#define sht_LOX_R 9

// define LED pins for left sensor and right sensor indicators
#define LED_L 12
#define LED_R 13

// define encoder pins for the motors
#define ENCODER1 18 //motor L - A
#define ENCODER2 19 //motor L - B
#define ENCODER3 2 //motor R - A
#define ENCODER4 3 //motor R - B
