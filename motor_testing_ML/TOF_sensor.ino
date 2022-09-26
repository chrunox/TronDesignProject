void setID() {
  // all reset
  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  delay(10);
  // all unreset
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  // activating LOX1 and resetting LOX2
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);

  // initing LOX1
  if (!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while (1);
  }
  delay(10);

  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  //initing LOX2
  if (!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while (1);
  }
}

int read_sensor (int sensorID) {
  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
  lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!
  switch (sensorID) {
    case 1:
      if (measure1.RangeMilliMeter < 200) {
        return measure1.RangeMilliMeter;
      } else {
        //Serial.println("Left sensor out of range");
        return -1;
      }
      break;
    case 2:
      if (measure2.RangeMilliMeter < 200) {
        return measure2.RangeMilliMeter;
      } else {
        //Serial.println("Right sensor out of range");
        return -1;
      }
      break;
  }
}
