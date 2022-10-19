/************
  This contains all the functions related to the TOFs
  including initialization and reading TOF measurements
************/

void TOF_init() {
  //Prepare TOF sensors for initialization
  Serial.println(F("Shutdown pins inited..."));
  digitalWrite(sht_LOX_L, LOW);
  digitalWrite(sht_LOX_R, LOW);
  Serial.println(F("Both in reset mode...(pins are low)"));
  Serial.println(F("Starting..."));

  // all reset
  Serial.println("Resetting all sensors");
  digitalWrite(sht_LOX_L, LOW);
  digitalWrite(sht_LOX_R, LOW);
  delay(10);
  // all unreset
  Serial.println("unresetting all sensors");
  digitalWrite(sht_LOX_L, HIGH);
  digitalWrite(sht_LOX_R, HIGH);
  delay(10);

  // activating LOX_L and resetting LOX_R
  Serial.println("activating loxl and resetting loxr");
  digitalWrite(sht_LOX_L, HIGH);
  digitalWrite(sht_LOX_R, LOW);

  // initing LOX_L
  Serial.println("initing loxl");
  if (!LOX_L.begin(LOX_L_ADDRESS)) {
    Serial.println(F("Failed to boot first TOF"));
    while (1);
  }
  delay(10);

  // activating LOX_R
  digitalWrite(sht_LOX_R, HIGH);
  delay(10);

  //initing LOX_R
  Serial.println("initing loxr");
  if (!LOX_R.begin(LOX_R_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while (1);
  }
  Serial.println("SetID done");
}

int read_sensor (int sensorID) {
  LOX_L.rangingTest(&measure_L, false); // pass in 'true' to get debug data printout!
  LOX_R.rangingTest(&measure_R, false); // pass in 'true' to get debug data printout!
  switch (sensorID) {
    case 1:
      if (measure_L.RangeMilliMeter < 200) {
        return measure_L.RangeMilliMeter;
      } else {
        //Serial.println("Left sensor out of range");
        return -1;
      }
      break;
    case 2:
      if (measure_R.RangeMilliMeter < 200) {
        return measure_R.RangeMilliMeter;
      } else {
        //Serial.println("Right sensor out of range");
        return -1;
      }
      break;
  }
}
