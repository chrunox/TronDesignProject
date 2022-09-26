void Left(int turn_time) {
  motor1.setSpeed(-255);
  motor2.setSpeed(255);
  delay(turn_time);
  stop(500);
}

void Right(int turn_time) {
  motor1.setSpeed(255);
  motor2.setSpeed(-255);
  delay(turn_time);
  stop_motor(500);
}

void Forward(char cells[]) {
  int f_size = sizeof(cells) / sizeof(char);
  int index = 0;
  char curr_cell = check_walls();
  while (index < f_size) {

    motor1.setSpeed(255);
    motor2.setSpeed(255);
  }
  stop_motor(500);
}

char check_walls() {
  
}

void stop_motor(int stop_time) {
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  delay(stop_time);
}
