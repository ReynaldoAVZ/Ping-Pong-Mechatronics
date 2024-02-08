void GetDataFromMATLAB(void) {
  Serial.println(F("ready for data"));
  for (target = 0; target < 6; ++target) {
    String dataString1 = Serial.readStringUntil('\n');
    String dataString2 = Serial.readStringUntil('\n');
    int stripeNum = dataString1.toInt();
    float xTargetm = dataString2.toFloat();
    xTargetVec[target] = xTargetm;
    driveTo[target] = stripeNum;
    Serial.print(F("For target "));
    Serial.print(target);
    Serial.print(F(" ,Drive to stripe "));
    //Serial.print(dataString1);
    Serial.print(stripeNum);
    Serial.print(F(" and aim for "));
    //Serial.print(dataString2);
    Serial.print(xTargetm, 3);
    Serial.println(F(" m."));
  }
  target = 0;
  // get linkage parameters from matlab
  String paramString = Serial.readStringUntil('\n');
  alpha = paramString.toFloat();
  paramString = Serial.readStringUntil('\n');
  beta = paramString.toFloat();
  paramString = Serial.readStringUntil('\n');
  thetaL0 = paramString.toFloat();
  Serial.print(F("alpha = "));
  Serial.print(alpha, 3);
  Serial.print(F("; beta = "));
  Serial.print(beta, 3);
  Serial.print(F("; thetaL0 = "));
  Serial.println(thetaL0, 3);

  // get optimal coefficients from matlab
  String coeffString = Serial.readStringUntil('\n');
  kappa = coeffString.toFloat();
  coeffString = Serial.readStringUntil('\n');
  lambda = coeffString.toFloat();
  Serial.print(F("kappa = "));
  Serial.print(kappa, 5);
  Serial.print(F("; lambda = "));
  Serial.println(lambda, 5);

  // get offset coefficients from matlab
  String offsetString = Serial.readStringUntil('\n');
  slope = offsetString.toFloat();
  offsetString = Serial.readStringUntil('\n');
  intercept = offsetString.toFloat();
  Serial.print(F("m = "));
  Serial.print(slope, 4);
  Serial.print(F("; b = "));
  Serial.println(intercept, 4);
}
