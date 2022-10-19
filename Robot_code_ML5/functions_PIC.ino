/************
  This contains functions for PID centering
  as well as the functions of reading encoders
************/

//Outdated PID for Phase A. Will return to this for Phase B
//Check void nudge() instead
void PID_center(char wall_layout) { 
  time_curr = millis();
  timeElapsed = time_curr - time_old;

  LOX_L.rangingTest(&measure_L, false); // pass in 'true' to get debug data printout!
  LOX_R.rangingTest(&measure_R, false); // pass in 'true' to get debug data printout!
  Ltof_curr = constrain(measure_L.RangeMilliMeter, 0, 300);
  Rtof_curr = constrain(measure_R.RangeMilliMeter, 0, 300);
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
  double Kd = 15;
  PWMred_cap = 20;
  //  Serial.println(input);
  error_curr = input - setPoint;
  cumError += error_curr;
  rateError = (error_curr - error_old) / timeElapsed;

  double K_sum = Kp * (error_curr) + Ki * (cumError) + Kd * (rateError);

  int PWMReduction = constrain(K_sum, -PWMred_cap, PWMred_cap);
  if (PWMReduction > 0) {
    motorL.setSpeed(100 - abs(PWMReduction));
    motorR.setSpeed(100);
  } else {
    motorL.setSpeed(100);
    motorR.setSpeed(100 - abs(PWMReduction));
  }
  time_old = time_curr;
  error_old = error_curr;
}


void reset_err() {
  error_old = 0;
  error_curr = 0;
  cumError = 0;
  rateError = 0;
}

void nudge(char wall_layout) {
  LOX_L.rangingTest(&measure_L, false); // pass in 'true' to get debug data printout!
  LOX_R.rangingTest(&measure_R, false); // pass in 'true' to get debug data printout!
  int Ltof_curr = constrain(measure_L.RangeMilliMeter, 0, 300);
  int Rtof_curr = constrain(measure_R.RangeMilliMeter, 0, 300);
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
