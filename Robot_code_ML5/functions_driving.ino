/************
  This contains all the functions to drive the robot forwards, turn
  as well as the functions of reading encoders
************/

void NavMaze(String instructs){
  //still WIP. Check void Forward2() instead
}

void Turn(char dir) {
  reset_err();
  switch (dir) {
    case 'L':
      Serial.println("Turning Left");
      motorL.setSpeed(-100);
      motorR.setSpeed(115);
      break;
    case 'R':
      Serial.println("Turning Right");
      motorL.setSpeed(100);
      motorR.setSpeed(-115);
      break;
  }
}

void Turn(char dir, int turn_time) {
  Turn(dir);
  delay(turn_time);
  motorR.setSpeed(0);
  delay(50);
  motorL.setSpeed(0);
  delay(stop_time);
}

void Turn90(char dir) {
  Turn(dir); //Turn motors on for turning

  //init variables
  int turn_pulses = 525; //pulses for a perfect 90 degree turn
  bool stoppedL = false, stoppedR = false;
  int start_pulse_L = encoder1_pos;
  int start_pulse_R = encoder3_pos;
  int turn_dist_L, turn_dist_R;

  //Keep turning while bot has not yet turned for 90 degrees
  while (!(stoppedL && stoppedR)) {
    turn_dist_L = encoder1_pos - start_pulse_L;
    turn_dist_R = encoder3_pos - start_pulse_R;
    Serial.println(String(turn_dist_L) + " " + String(turn_dist_R));
    if (turn_dist_L >= turn_pulses) {
      motorL.setSpeed(0);
      stoppedL = true;
    }
    if (turn_dist_R + 95 >= turn_pulses) { //+95 is to counteract motor play after stopping
      motorR.setSpeed(0);
      stoppedR = true;
    }
  }
  delay(200);
}

void Forward() {
  Serial.println("Moving Forward");
  motorL.setSpeed(230);
  motorR.setSpeed(255);
}

void Forward(int forward_time) {
  Forward();
  delay(forward_time);
  stop_motor(stop_time);
}

void Backward() {
  motorL.setSpeed(-230);
  motorR.setSpeed(-255);
  delay(500);
  stop_motor(stop_time);
}

//outdated forward function for Phase A. Check Forward2() instead
void Forward(String _cells) {

  //Convert string input to character array
  int fwd_len = _cells.length() + 1;
  char cells[fwd_len];
  _cells.toCharArray(cells, fwd_len);

  Forward(); //Start motors for driving forward

  /****initialize and start PID calculation****
    Reminder: PID variables are Input, PWMReduction, Setpoint, Kp, Ki, Kd
  *********************************************/
  //  PID_init(20, 1, 0, 0);     //Initialize values for Kp, Ki, Kd and Setpoint
  //  PID_centering.start();

  int index = 0; //variables for loop
  char curr_cell, next_cell;
  int loop_start;
  //Loop for moving forwards for each cell
  while (index < fwd_len - 1) {
    //    loop_start = millis();              //for measuring execution time of the loop
    char curr_cell = check_walls();     //Wall layout of current cell
    //    Serial.println(curr_cell);
    next_cell = cells[index];


    //    Serial.print("current cell: " + String(curr_cell) + " next cell: " + String(next_cell));

    if (curr_cell == next_cell) {
      index++;
      reset_err(); //test whether to keep or reset error after every change of cell
    }
    //    PID_center(curr_cell);

    //    Serial.println("Loop time: " + String(millis() - loop_start));
  }
  Forward(150);//wally
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
  delay(400);
  stop_motor();
  Serial.println("Driving forward done");
}

char check_walls() {
  bool l_wall;
  bool r_wall;
  char wall_layout;
  LOX_L.rangingTest(&measure_L, false); // pass in 'true' to get debug data printout!
  LOX_R.rangingTest(&measure_R, false); // pass in 'true' to get debug data printout!
  int l_dist, r_dist;
  if (measure_L.RangeMilliMeter < 200) {
    l_dist = measure_L.RangeMilliMeter;
  } else {
    l_dist = -1;
    //Serial.println("Left sensor out of range");
  }
  if (measure_R.RangeMilliMeter < 200) {
    r_dist = measure_R.RangeMilliMeter;
  } else {
    r_dist = -1;
    //Serial.println("Right sensor out of range");
  }
  //read TOF sensor readings to determine if there is a wall on the left and/or right
  //check left wall
  if (l_dist == -1) {
    l_wall = false;
    digitalWrite(LED_L, LOW);
  } else {
    l_wall = true;
    digitalWrite(LED_L, HIGH);
  }
  //check right wall
  if (r_dist == -1) {
    r_wall = false;
    digitalWrite(LED_R, LOW);
  } else {
    r_wall = true;
    digitalWrite(LED_R, HIGH);
  }

  //Determine the wall layout configuration based on presence of either wall
  //A = both walls present, B = no walls, C = left wall, D = right wall
  if (r_wall && l_wall)
    wall_layout = 'A';
  else if (!r_wall && !l_wall)
    wall_layout = 'B';
  else if (!r_wall && l_wall)
    wall_layout = 'C';
  else if (r_wall && !l_wall)
    wall_layout = 'D';

  return wall_layout;
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
