/************
  In Trump's autotuned voice: I RAAAAAN. DOWN THE RAAAAAMP.
************/

void Ramp(char dir) {
  char turnDirection;
  String rampCells;
  switch (dir) {
    case 'U':
      turnDirection = 'L';
      rampCells = "AD";
      break;
    case 'D':
      turnDirection = 'R';
      rampCells = "AC";
      break;
  }

  // Ramp loop starting when robot is in the ramp section facing towards 1st ramp
  for (int x = 1; x <= 3; x++) {
    Forward(rampCells);
    Turn(turnDirection);
  }
}
