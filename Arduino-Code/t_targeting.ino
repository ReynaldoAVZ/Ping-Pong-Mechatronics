void ComputeStuff(void) {
  Serial.println(F("Performing target calculations"));
  float d1 = 0.0400;  // meters
  float d2 = 0.1583;  // meters
  float d3 = 0.0553;  // meters
  float d[] = {d1, d2, d3};
  float H[]= { 0.1301, 0.0960, 0.0880, 0.0465 };
  TargetServoAngles(d, kappa, lambda, H, alpha, beta, thetaL0, xTargetVec);
  AdjustedStripeNums();
  BestTargetAndAngleOrder();
  for (int k = 0; k < 6; ++k){
      Serial.print(F("To hit a target at "));
      Serial.print(xTargetVec[k]);
      Serial.print(F(" m, command the servo to "));
      Serial.print(writeToServo[k]);
      Serial.print(F(" deg, and drive to (adjusted!)"));
      Serial.println(driveTo[k]);
      
  }
}

void AdjustedStripeNums(void){
  for(int i = 0; i < 6;++i){
    float thetaS = writeToServo[i];
    //Serial.println(thetaS);
    float unroundedOffset = (slope * thetaS) + intercept;
    int offset = round(unroundedOffset);
    Serial.println(offset);
    driveTo[i] = driveTo[i] + offset;
  }
}
float Deg2Rad(float angle){
  float Radians = (angle * M_PI) / 180; //degree in radians
  return Radians;
}

float Quadratic(float a, float b, float c, int plusOrMinus) {
  float root = (-b + (plusOrMinus * sqrt(pow(b, 2) - (4 * a * c)))) / (2 * a);
  return root;
}

float LandingDistance(float d[],float k, float lambda, float theta) {
  float d1 = d[0];
  float d2 = d[1];
  float d3 = d[2];
  float Radians = Deg2Rad(theta);
  float x0 = d2 * cos(Radians) - d3 * sin(Radians);
  float y0 = d1 + d2 * sin(Radians) + d3 * cos(Radians);
  float v0 = k + lambda * theta;
  float v0x = v0 * cos(Radians);
  float v0y = v0 * sin(Radians);
  float g = 9.81;
  float a = (-1.0/2.0) * g;
  float b = v0y;
  float c = y0;
  float tLand = Quadratic(a, b, c, -1);
  float xLand = x0 + v0x * tLand;
  return xLand; 
}
float RangeAngle(float d[], float k, float lambda)  {
  float d1 = d[0];
  float d2 = d[1];
  float d3 = d[2];
  float thetaL = 0;
  float rangeAngle = 0;
  float xLand = 0;
  while (thetaL <= 90)  {
    float landingDistance = LandingDistance(d, k, lambda, thetaL);
    if (landingDistance >= xLand) {
      xLand = landingDistance;
      rangeAngle = thetaL;
    }
    thetaL = thetaL + 0.05;
    }
  return rangeAngle;
}
float LaunchAngle(float d[], float k, float lambda, float xTarget)  {
  float d1 = d[0];
  float d2 = d[1];
  float d3 = d[2];
  float thetaL = RangeAngle(d, k, lambda);
  float landingDistance = LandingDistance(d, k, lambda, thetaL);
  while (landingDistance >= xTarget)  {
    thetaL = thetaL + 0.05;
    landingDistance = LandingDistance(d, k, lambda, thetaL);
  }
  return thetaL;
}

float Rad2Deg(float Radians) {
  float Angle = (Radians * 180) / M_PI;
  return Angle;
}

float ThetaServo(float H[], float thetaL, float alpha, float beta, float thetaL0){
  float L1 = H[0];
  float L2 = H[1];
  float L3 = H[2];
  float L4 = H[3];
  float thetaLRad = Deg2Rad(thetaL);
  float alphaRad =  Deg2Rad(alpha);
  float thetaL0Rad = Deg2Rad(thetaL0);
  float K1 = L1 / L2;
  float K2 = L1 / L4;
  float K3 = ( pow(L1, 2) + pow(L2, 2) - pow(L3, 2) + pow(L4, 2) ) / (2 * L2 * L4 );
  float theta2Rad = thetaLRad - thetaL0Rad;
  float A = cos(theta2Rad) - K1 - K2 * cos(theta2Rad) + K3;
  float B = -2 * sin(theta2Rad);
  float C = K1 - (K2 + 1) * cos(theta2Rad) + K3;
  float quadraticVal = Quadratic(A, B, C, -1);
  float theta4Rad = 2 * atan(quadraticVal);
  float thetaSRad = (theta4Rad + alphaRad) / (1 - beta);
  float thetaSDegree = Rad2Deg(thetaSRad);
  return thetaSDegree;
}

void TargetServoAngles(float d[], float k, float lambda, float H[], float alpha, float beta, float thetaL0, float xTargetVec[]){
  float localLaunchVec[6];
  float localServoVec[6];
  int count;
  for(count = 0; count < 6; count++){
    Serial.print("Computing target ");
    Serial.println(count);
    localLaunchVec[count] = LaunchAngle(d, k, lambda, xTargetVec[count]);
    localServoVec[count] = ThetaServo(H, localLaunchVec[count], alpha, beta, thetaL0);
    int integerVariable = int(round(localServoVec[count]));
      writeToServo[count] = integerVariable;
  }
}
