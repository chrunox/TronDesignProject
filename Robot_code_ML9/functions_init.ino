/************
  This contains all the functions for initialization
  that is called during void Setup()
************/

void pins_init() {
  //set pins for TOF sensors
  pinMode(sht_LOX_L1, OUTPUT);
  pinMode(sht_LOX_L2, OUTPUT);
  pinMode(sht_LOX_R1, OUTPUT);
  pinMode(sht_LOX_R2, OUTPUT);
  pinMode(sht_LOX_FW, OUTPUT);

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

void pid_init() {
  PID_center.begin(&cInput, &cOutput, &cSetpoint, cKp, cKi, cKd);
  PID_center.setOutputLimits(-512, 512);
  PID_center.setWindUpLimits(-100, 100);

  PID_turn.begin(&tInput, &tOutput, &tSetpoint, tKp, tKi, tKd);
  PID_turn.setOutputLimits(-200, 200);
  PID_turn.setWindUpLimits(-10, 10);

  PID_forward.begin(&fInput, &fOutput, &fSetpoint, fKp, fKi, fKd);
  PID_forward.setOutputLimits(0, 510);
  fOutput = map(fOutput, 0, 510, -255, 255);
  PID_forward.setWindUpLimits(-10, 10);
}
