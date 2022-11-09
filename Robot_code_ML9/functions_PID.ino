/************
  This contains functions for PID centering
  as well as the functions of reading encoders
************/


/************
  👇 Outdated PID for Phase A. Will return to this for Phase B
  Check void nudge() instead
  Currently WIP by Marc. Will change this into a single PID compute...
  ...function that can be called by other functions that require PID

void PID_centering(char wall_layout) {
  time_curr = millis();
  timeElapsed = time_curr - time_old;

  //  Serial.println(String(Ltof_curr));
  String message;
  double input;
  double setPoint;
  switch (wall_layout) {
    case 'A':
      input = Ltof_curr - Rtof_curr + 5;
      setPoint = 0;
      message = "Liaba is using PID 2 walls";
      break;
    case 'B':
      input = 0;
      setPoint = 0;
      message = "Liaba is using PID no walls";
      break;
    case 'C':
      input = Ltof_curr;
      setPoint = ideal_dist_from_wall;
      message = "Liaba is using PID left wall";
      break;
    case 'D':
      input = -(Rtof_curr);
      setPoint = -(ideal_dist_from_wall - 0);
      message = "Liaba is using PID right wall";
      break;
  }
  //  Serial.println(message);

  double Kp = 20; //tune this
  double Ki = 0.02;
  double Kd = 2;
  //  Serial.println(input);
  error_curr = input - setPoint;
  sumError += error_curr;
  rateError = (error_curr - error_old) / timeElapsed;

  double K_sum = Kp * (error_curr) + Ki * (sumError) + Kd * (rateError);

//  int PWMReduction = constrain(K_sum, -PWMred_cap, PWMred_cap);
//  if (PWMReduction > 0) {
//    motorL.setSpeed(100 - abs(PWMReduction));
//    motorR.setSpeed(100);
//  } else {
//    motorL.setSpeed(100);
//    motorR.setSpeed(100 - abs(PWMReduction));
//  }
//  time_old = time_curr;
//  error_old = error_curr;
}
************/

void reset_err() {
  error_old = 0;
  error_curr = 0;
  sumError = 0;
  rateError = 0;
}

void nudge(char wall_layout) {
  LOX_L1.rangingTest(&measure_L1, false); // pass in 'true' to get debug data printout!
  LOX_R1.rangingTest(&measure_R1, false); // pass in 'true' to get debug data printout!
  int Ltof_curr = constrain(measure_L1.RangeMilliMeter, 0, 300);
  int Rtof_curr = constrain(measure_R1.RangeMilliMeter, 0, 300);
  double input;
  double setPoint;
  String message;
  switch (wall_layout) {
    case 'A':
      input = Ltof_curr - Rtof_curr + 5;
      setPoint = 0;
      message = "Liaba is using PID 2 walls";
      break;
    case 'B':
      input = 0;
      setPoint = 0;
      message = "Liaba is using PID no walls";
      break;
    case 'C':
      input = Ltof_curr;
      setPoint = ideal_dist_from_wall;
      message = "Liaba is using PID left wall";
      break;
    case 'D':
      input = -(Rtof_curr);
      setPoint = -(ideal_dist_from_wall);
      message = "Liaba is using PID right wall";
      break;
  }
  int err = setPoint - input;
  Serial.println(err);
  int nudge_delay = 50;
  if (err > 1) {
    motorR.setSpeed(0); //nudge right
    //    motorL.setSpeed(150);
    delay(nudge_delay);
    Serial.println("nudging right");
  } else if (err < -1) {
    motorL.setSpeed(0); //nudge left
    //    motorR.setSpeed(150);
    delay(nudge_delay);
    Serial.println("nudging left");
  }
  //  Serial.println(wall_layout);
}


//void no_walls_forward() {
//  jesus_take_the_wheel();
//}
