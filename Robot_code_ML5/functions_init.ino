/************
  This contains all the functions for initialization
  that is called during void Setup()
************/

void pins_init() {
  //set pins for TOF sensors
  pinMode(sht_LOX_L, OUTPUT);
  pinMode(sht_LOX_R, OUTPUT);

  //set pins for encoders
  pinMode(ENCODER1, INPUT);
  pinMode(ENCODER2, INPUT);
  pinMode(ENCODER3, INPUT);
  pinMode(ENCODER4, INPUT);

  //set pins for LEDs
  pinMode(LED_L, OUTPUT);
  pinMode(LED_R, OUTPUT);

  //encoder interrupts
  attachInterrupt(digitalPinToInterrupt(ENCODER1), encoder1, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER2), encoder2, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER3), encoder3, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER4), encoder4, RISING);
}

void serial_init(long baud) {
  Serial.begin(baud);
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
}
