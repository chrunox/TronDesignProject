/************
  This contains all the functions related to the TOFs
  such as initializing the TOFs and reading TOF measurements
************/

double read_tof (int sensorID) {
  int max_dist = 250;
  switch (sensorID) {
    case 1:
      LOX_L1.rangingTest(&measure_L1, false); // pass in 'true' to get debug data printout!
      if (measure_L1.RangeMilliMeter + L1_offset < max_dist)
        L1 = measure_L1.RangeMilliMeter + L1_offset;
      else L1 = 0;
//      Serial.println(L1);
      return L1;
    case 2:
      LOX_L2.rangingTest(&measure_L2, false);
      if (measure_L2.RangeMilliMeter + L2_offset < max_dist)
        L2 = measure_L2.RangeMilliMeter + L2_offset;
      else L2 = 0;
      return L2;
    case 3:
      LOX_R1.rangingTest(&measure_R1, false);
      if (measure_R1.RangeMilliMeter + R1_offset < max_dist)
        R1 = measure_R1.RangeMilliMeter + R1_offset;
      else R1 = 0;
      return R1;
    case 4:
      LOX_R2.rangingTest(&measure_R2, false);
      if (measure_R2.RangeMilliMeter + R2_offset < max_dist)
        R2 = measure_R2.RangeMilliMeter + R2_offset;
      else R2 = 0;
      return R2;
    case 5:
      LOX_FW.rangingTest(&measure_FW, false);
      FW = measure_FW.RangeMilliMeter + FW_offset;
      return FW;
      break;
  }
}

void tof_init() {
  //Prepare TOF sensors for initialization
  Serial.println(F("Shutdown pins inited..."));
  digitalWrite(sht_LOX_L1, LOW);
  digitalWrite(sht_LOX_L2, LOW);
  digitalWrite(sht_LOX_R1, LOW);
  digitalWrite(sht_LOX_R2, LOW);
  digitalWrite(sht_LOX_FW, LOW);
  Serial.println(F("All in reset mode...(pins are low)"));
  Serial.println(F("Starting..."));

  // all reset
  Serial.println("Resetting all sensors");
  digitalWrite(sht_LOX_L1, LOW);
  digitalWrite(sht_LOX_L2, LOW);
  digitalWrite(sht_LOX_R1, LOW);
  digitalWrite(sht_LOX_R2, LOW);
  digitalWrite(sht_LOX_FW, LOW);
  delay(10);

  // all unreset
  Serial.println("unresetting all sensors");
  digitalWrite(sht_LOX_L1, HIGH);
  digitalWrite(sht_LOX_L2, HIGH);
  digitalWrite(sht_LOX_R1, HIGH);
  digitalWrite(sht_LOX_R2, HIGH);
  digitalWrite(sht_LOX_FW, HIGH);
  delay(10);

  // activating LOX_L1 and resetting other TOFs
  Serial.println("activating loxl and resetting loxr");
  digitalWrite(sht_LOX_L1, HIGH);
  digitalWrite(sht_LOX_L2, LOW);
  digitalWrite(sht_LOX_R1, LOW);
  digitalWrite(sht_LOX_R2, LOW);
  digitalWrite(sht_LOX_FW, LOW);

  // initing LOX_L1
  Serial.println("initing loxL1");
  if (!LOX_L1.begin(LOX_L1_ADDRESS)) {
    Serial.println(F("Failed to boot front left TOF"));
    //    while (1);
  }
  delay(10);

  // activating LOX_L2
  digitalWrite(sht_LOX_L2, HIGH);
  delay(10);

  // initing LOX_L2
  Serial.println("initing loxL2");
  if (!LOX_L2.begin(LOX_L2_ADDRESS)) {
    Serial.println(F("Failed to boot back left VL53L0X"));
    //    while (1);
  }

  // activating LOX_R1
  digitalWrite(sht_LOX_R1, HIGH);
  delay(10);

  // initing LOX_R1
  Serial.println("initing loxR1");
  if (!LOX_R1.begin(LOX_R1_ADDRESS)) {
    Serial.println(F("Failed to boot front right VL53L0X"));
    //    while (1);
  }

  // activating LOX_R2
  digitalWrite(sht_LOX_R2, HIGH);
  delay(10);

  // initing LOX_R2
  Serial.println("initing loxR2");
  if (!LOX_R2.begin(LOX_R2_ADDRESS)) {
    Serial.println(F("Failed to boot back right VL53L0X"));
    //    while (1);
  }

  // activating LOX_FW
  digitalWrite(sht_LOX_FW, HIGH);
  delay(10);

  // initing LOX_FW
  Serial.println("initing loxFW");
  if (!LOX_FW.begin(LOX_FW_ADDRESS)) {
    Serial.println(F("Failed to boot forward VL53L0X"));
    //    while (1);
  }

  LOX_L1.startRangeContinuous();
  LOX_L2.startRangeContinuous();
  LOX_R1.startRangeContinuous();
  LOX_R2.startRangeContinuous();
  LOX_FW.startRangeContinuous();
  Serial.println("TOF setup done");
}
