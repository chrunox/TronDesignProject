/************
  This contains all the functions to drive the robot forwards, turn
  as well as the functions of reading encoders
************/

void Turn(char dir) {
  reset_err();
  switch (dir) {
    case 'L':
      Serial.println("Turning Left");
      motorL.setSpeed(-200);
      motorR.setSpeed(200);
      break;
    case 'R':
      Serial.println("Turning Right");
      motorL.setSpeed(200);
      motorR.setSpeed(-200);
      break;
  }
}

void TurnByTime(char dir, int turn_time) {
  Turn(dir);
  delay(turn_time);
  motorR.setSpeed(0);
  delay(50);
  motorL.setSpeed(0);
  delay(stop_time);
}

void TurnByAngle(char dir, float target_yaw) {
  delay(200);
  float yaw_extra;
  if (dir == 'L') {
    read_tof(3);
    read_tof(4);
    //Serial.println(String(R1) + " " + String(R2));
    if (R1 && R2) {
      float R1sum, R2sum;
      float avg_cnt = 25.;
      for (int i = 0; i < avg_cnt; i++) {
        read_tof(3);
        read_tof(4);
        R1sum += R1;
        R2sum += R2;
      }
      yaw_extra = atan((R1sum / avg_cnt - R2sum / avg_cnt) / l);
      //Serial.println("wall on right ok. Extra yaw calculated");
    } else {
      //Serial.println("wall on right ng. No extra yaw calculated");
      yaw_extra = 0;
    }
  } else if (dir == 'R') {
    read_tof(1);
    read_tof(2);
    if (L1 && L2) {
      float L1sum, L2sum;
      float avg_cnt = 25.;
      for (int i = 0; i < avg_cnt; i++) {
        read_tof(1);
        read_tof(2);
        L1sum += L1;
        L2sum += L2;
      }
      yaw_extra = atan((L1sum / avg_cnt - L2sum / avg_cnt) / l);
    } else
      yaw_extra = 0;
  }
//  if (abs(yaw_extra) > 90) yaw_extra = 0;
  target_yaw -= (yaw_extra * 180. / PI);
  Serial.println("extra yaw = " + String((yaw_extra)));

  currYaw = 0;
  tSetpoint = target_yaw;  //PID setpoint is specified turn angle
  //  Turn(dir); //Turn motors on for turning
  PID_turn.reset();
  PID_turn.start();
  int dir_f;
  int counter = 0;
  while (counter < 500/*abs(currYaw) < tSetpoint*/) { //Keep turning while bot has not yet turned for target degrees
    time_old = time_curr;
    time_curr = millis();
    timeElapsed = time_curr - time_old;
    if (abs(read_mpu()) > 1) {
      currYaw += read_mpu() * timeElapsed / 1000;
      //      Serial.println(currYaw);
    }
    tInput = abs(currYaw); //input to PID is current turn angle
    PID_turn.compute();    //calculate PID output
    if (dir == 'L') dir_f = 1;
    else dir_f = -1;
    motorL.setSpeed(-dir_f * tOutput);
    motorR.setSpeed(dir_f * tOutput);
    if (abs(tOutput) < 30) {
      counter++;
    }
  }
  PID_turn.stop();
  stop_motor(stop_time);
  Serial.println("turning over");
}

void Forward() {
  //Serial.println("Moving Forward");
  motorL.setSpeed(100);
  motorR.setSpeed(145);
}

void Forward(int forward_time) {
  Forward();
  delay(forward_time);
  stop_motor(stop_time);
}

void Backward(int forward_time) {
  motorL.setSpeed(-100);
  motorR.setSpeed(-145);
  delay(forward_time);
  stop_motor(stop_time);
}

void ForwardTilWall(float num_cell) {
  read_tof(5);
  while (FW < num_cell * 190. + 65) {
    read_tof(5);
    Forward();
  }
  stop_motor(stop_time);
}

void Forward(String _cells) {
  //Convert string input to character array
  int fwd_len = _cells.length() + 1;
  char cells[fwd_len];
  _cells.toCharArray(cells, fwd_len);

  //prepare PID library functions
  PID_center.reset();
  PID_center.start();
  double A, B, delta_x, delta_m, ideal_x;  //variables for input calculations

  int index = 0; //variables for loop
  char curr_cell, next_cell;
  //Loop for moving forwards for each cell
  while (index < fwd_len - 1) {
    long old = millis();

    for (int i = 1; i <= 5; i++) read_tof(i);
    curr_cell = check_walls();          //Wall layout of current cell
    next_cell = cells[index];

    A = 2;
    B = 3;
    ideal_x = 85;
    float speed_factor = 1;

    if (L1 && L2) {           // if both left sensors detect wall, stay parallel and maintain distance to left wall
      delta_m = L1 - L2;
      delta_x = (L1 + L2) / (2 * sqrt(1 + pow((delta_m) / l, 2))); // refer to Phase B report for the math
      cSetpoint = A * ideal_x;
    } else if (R1 && R2) {    // if both right sensors detect wall, stay parallel and maintain distance to right wall
      delta_m = R2 - R1;
      delta_x = -(R1 + R2) / (2 * sqrt(1 + pow((delta_m) / l, 2)));
      cSetpoint = -A * ideal_x;
    } else {                  // drive forward and hope for the best 🙏 jk still wip
      delta_m = 0;
      delta_x = 0;
      cSetpoint = 0;
    }
    cInput = A * delta_x + B * delta_m;
    PID_center.compute();
    cOutput = map(cOutput, -512, 512, -45, 45);

    //Serial.print(delta_x);       Serial.print(" ");
    //Serial.print(cSetpoint);     Serial.print(" ");
    //Serial.print(cInput);        Serial.print(" ");
    //Serial.print(cOutput);       Serial.println(" ");

    /****uncomment this to enable forward pid****
        fInput = FW;
        fSetpoint = 50;
        PID_forward.compute();
        float speed_factor = fOutput / 255;
    ********************************************/

    if (cOutput < -5) {
      motorL.setSpeed(speed_factor * (100 - abs(cOutput)));
      motorR.setSpeed(speed_factor * 145);
    } else if (cOutput > 5)  {
      motorL.setSpeed(speed_factor * 100);
      motorR.setSpeed(speed_factor * (145 - abs(cOutput)));
    } else {
      motorL.setSpeed(speed_factor * 100);
      motorR.setSpeed(speed_factor * 145);
    }

    if (curr_cell == next_cell) {
      index++;
    }
    //Serial.println(millis() - old);
  }
  PID_center.stop();
  Forward();
  delay(500);
  stop_motor();
}

void Forward_ramp(String _cells) {
  //Convert string input to character array
  int fwd_len = _cells.length() + 1;
  char cells[fwd_len];
  _cells.toCharArray(cells, fwd_len);

  //prepare PID library functions
  PID_center.reset();
  PID_center.start();
  double A, B, delta_x, delta_m, ideal_x;  //variables for input calculations

  int index = 0; //variables for loop
  char curr_cell, next_cell;
  //Loop for moving forwards for each cell
  while (index < fwd_len - 1) {
    long old = millis();

    for (int i = 1; i <= 5; i++) read_tof(i);
    curr_cell = check_walls();          //Wall layout of current cell
    next_cell = cells[index];

    A = 2;
    B = 3;
    ideal_x = 85;
    float speed_factor = 1;

    if (L1 && L2) {           // if both left sensors detect wall, stay parallel and maintain distance to left wall
      delta_m = L1 - L2;
      delta_x = (L1 + L2) / (2 * sqrt(1 + pow((delta_m) / l, 2))); // refer to Phase B report for the math
      cSetpoint = A * ideal_x;
    } else if (R1 && R2) {    // if both right sensors detect wall, stay parallel and maintain distance to right wall
      delta_m = R2 - R1;
      delta_x = -(R1 + R2) / (2 * sqrt(1 + pow((delta_m) / l, 2)));
      cSetpoint = -A * ideal_x;
    } else {                  // drive forward and hope for the best 🙏 jk still wip
      delta_m = 0;
      delta_x = 0;
      cSetpoint = 0;
    }
    cInput = A * delta_x + B * delta_m;
    PID_center.compute();
    cOutput = map(cOutput, -512, 512, -45, 45);

    Serial.print(delta_x);       Serial.print(" ");
    Serial.print(cSetpoint);     Serial.print(" ");
    Serial.print(cInput);        Serial.print(" ");
    Serial.print(cOutput);       Serial.println(" ");

    /****uncomment this to enable forward pid****
        fInput = FW;
        fSetpoint = 50;
        PID_forward.compute();
        float speed_factor = fOutput / 255;
    ********************************************/

    if (cOutput < 0) {
      motorL.setSpeed(speed_factor * (200 - abs(cOutput)));
      motorR.setSpeed(speed_factor * 245);
    } else {
      motorL.setSpeed(speed_factor * 200);
      motorR.setSpeed(speed_factor * (245 - abs(cOutput)));
    }

    if (curr_cell == next_cell) {
      index++;
    }
    Serial.println(millis() - old);
  }
  PID_center.stop();
  Forward();
  delay(500);
  stop_motor();
  Serial.println("Driving forward done");
}

void Forward2(String _cells) {

  //Convert string input to character array
  int fwd_len = _cells.length() + 1;
  char cells[fwd_len];
  _cells.toCharArray(cells, fwd_len);

  //  Forward(); //Start motors for driving forward
  motorL.setSpeed(100);
  motorR.setSpeed(100);
  int index = 0; //variables for loop
  char curr_cell, next_cell;
  int loop_start, loop_end;
  //Loop for moving forwards for each cell
  while (index < fwd_len - 1) {
    motorL.setSpeed(90);
    motorR.setSpeed(110);    //    loop_start = millis();              //for measuring execution time of the loop
    char curr_cell = check_walls();     //Wall layout of current cell
    //    loop_end = millis() - loop_start;
    //    Serial.println(curr_cell);
    next_cell = cells[index];

    if (curr_cell == next_cell) {
      index++;
    }
    nudge(curr_cell);
    //    Serial.println(loop_end);
    Serial.println(curr_cell);
  }
  Forward();
  delay(300);
  stop_motor();
  Serial.println("Driving forward done");
}



void stop_motor() {
  motorL.setSpeed(0);
  delay(20);
  motorR.setSpeed(0);
}

void stop_motor(int _stop_time) {
  stop_motor();
  delay(_stop_time);
}







/******
  Encoder interrupt functions
******/
void encoder1() {
  if (digitalRead(ENCODER1) == HIGH) {
    encoder1_pos++;
  } else {
    encoder1_pos--;
  }
}

void encoder2() {
  if (digitalRead(ENCODER2) == HIGH) {
    encoder2_pos++;
  } else {
    encoder2_pos--;
  }
}

void encoder3() {
  if (digitalRead(ENCODER3) == HIGH) {
    encoder3_pos++;
  } else {
    encoder3_pos--;
  }
}

void encoder4() {
  if (digitalRead(ENCODER4) == HIGH) {
    encoder4_pos++;
  } else {
    encoder4_pos--;
  }
}
