/************
  This contains all the functions to drive the robot forwards, turn
  as well as the functions of reading encoders
************/

void Left(int turn_time) {
  Serial.println("Turning Left");
  motor1.setSpeed(-255);
  motor2.setSpeed(255);
  delay(turn_time);
  stop_motor(500);
}

void Right(int turn_time) {
  Serial.println("Turning Right");
  motor1.setSpeed(255);
  motor2.setSpeed(-255);
  delay(turn_time);
  stop_motor(500);
}

void Forward(char cells[]) {
  //  int f_size = sizeof(cells) / sizeof(char);
  int index = 0;
  char curr_cell;
  char next_cell;
  while (index < strlen(cells)) {
    Serial.print("Driving forward... ");
    motor1.setSpeed(255);
    motor2.setSpeed(255);
    curr_cell = check_walls();
    next_cell = cells[index];
    Serial.println("current cell " + String(curr_cell) + " next cell: " + String(next_cell));
    if (curr_cell == next_cell) {
      index++;
    }
  }
  Serial.println("Driving forward done");
  delay(2000);
  stop_motor(500);
}

char check_walls() {
  bool l_wall;
  bool r_wall;
  char wall_layout;

  //read TOF sensor readings to determine if there is a wall on the left and/or right
  if (read_sensor(1) == -1) //check left wall
    l_wall = false;
  else
    l_wall = true;
  if (read_sensor(2) == -1) //check right wall
    r_wall = false;
  else
    r_wall = true;

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

void stop_motor(int stop_time) {
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  delay(stop_time);
}

//test function to see speed profile of both motors W.R.T. PWM
void measure_motor_speed() {
  float timeold;
  float timecurr;
  float pos1old;
  float pos1curr;
  float pos2old;
  float pos2curr;
  float timetemp;

  for (float i = 0; i < 255; i++) { //loop to measure the motor speed in pulses per sec
    timeold = timecurr;
    timecurr = millis();
    pos1old = pos1curr;
    pos1curr = encoder1_pos;
    pos2old = pos2curr;
    pos2curr = encoder3_pos;

    motor1.setSpeed(i);        // Run bad motor forward at full speed.
    motor2.setSpeed(i * 0.9);  // Run good motor forward at full speed. Tuned PWM by multiplying with 0.9 to try to match other motor's speed profile

    float motor1_speed = (pos1curr - pos1old) * 10 / (timecurr - timeold);
    float motor2_speed = (pos2curr - pos2old) * 10 / (timecurr - timeold);

    Serial.println(String(motor1_speed) + " " + String(motor2_speed));
    delay(50);
  }
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
