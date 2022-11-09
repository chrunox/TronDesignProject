/************
  This contains all the functions related to the MPU6050
  such as initializing the MPU6050 and reading gyro measurements
************/

void mpu_init() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0); //wakes up the MPU6050
  Wire.endTransmission(true);
}

double read_mpu() {
  double gyroZ;
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x43); //change to 47 when need yaw
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 2, true); //request gyro registers 47 & 48
  while (Wire.available() < 2); //wait until all values obtained from the registers

  //Store last two bytes (i.e. gyro z reading)
  gyroZ = (Wire.read() << 8 | Wire.read()) / 131.0; 
  
  return gyroZ + 3.31; //recalculate 3.31 when switching to different direction
}

double calc_yaw(){
  double angularVel;
  angularVel = read_mpu();
  
}
