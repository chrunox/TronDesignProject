void NavMaze() {
  //still WIP. Check void Forward2() instead
  //  Forward("AAD"); //start of top maze
  //  TurnByAngle('L', 90);
  //  Forward("AAD");
  //  TurnByAngle('L', 90);
  //  Forward("ADC");
  //  TurnByAngle('R', 90);
  //  Forward("ACAC"); //the 2nd A is to detect the pillars before the 2nd C
  //  //  Forward(250);
  //  TurnByAngle('R', 90);
  //  Forward("AC"); //Start of ramp, down
  //  TurnByAngle('R', 90);
  //  Forward("AAC");
  //  //  Forward(200);
  //  TurnByAngle('R', 90);
  //  Forward("AC");
  //  TurnByAngle('R', 90);
    Forward("AC");
    TurnByAngle('R', 90);
  Forward("AAD"); //start of bottom maze
  TurnByAngle('L', 90);
  Forward("AD");
  Backward(200);
  TurnByAngle('L', 90);
  Forward("C");
//  Forward();
//  delay(100);
//  stop_motor();
  TurnByAngle('R', 90);
  Forward("AB");
  TurnByAngle('L', 90);
  Forward("C");
  TurnByAngle('R', 90);
  Forward("AB");
  TurnByAngle('R', 90);
  Forward("D");
  TurnByAngle('L', 90);
  Forward("AB");
  TurnByAngle('R', 90);
  Forward("D");
  TurnByAngle('L', 90);
  Forward("AD");
  TurnByAngle('L', 90);
  Forward(1000); //scoop
  delay(1000);
  Backward(1000);
  TurnByAngle('L', 90); //start of bottom maze reverse
  Forward("AC");
  TurnByAngle('R', 90);
  Forward("D");
  TurnByAngle('L', 90);
  Forward("AB");
  TurnByAngle('R', 90);
  Forward("D");
  TurnByAngle('L', 90);
  Forward("AB");
  TurnByAngle('L', 90);
  Forward("C");
  TurnByAngle('R', 90);
  Forward("AB");
  TurnByAngle('L', 90);
  Forward("C");
  TurnByAngle('R', 90);
  Forward("AC");
  TurnByAngle('R', 90);
  Forward("AD");
  TurnByAngle('L', 90);
  Forward("AD");
  TurnByAngle('L', 90);
  Forward("AD"); //start of ramp, upwards
  TurnByAngle('L', 90);
  Forward("AD");
  TurnByAngle('L', 90);
  Forward("AD");
  TurnByAngle('L', 90);
  Forward("ACAC"); //start of top maze reverse
  TurnByAngle('L', 90);
  Forward("CAB");
  TurnByAngle('R', 90);
  Forward("AC");
  TurnByAngle('R', 90);
  Forward("ADADADADAD");
}

char check_walls() {
  bool l_wall, r_wall;
  char wall_layout;

  //read TOF sensor readings to determine if there is a wall on the left and/or right
  //check left wall
  if (L1) {
    l_wall = true;
  } else {
    l_wall = false;
  }
  //check right wall
  if (R1) {
    r_wall = true;
  } else {
    r_wall = false;
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
