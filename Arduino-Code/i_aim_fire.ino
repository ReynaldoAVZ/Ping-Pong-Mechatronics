void TestAimFire (void) {

  int prevButtonPressed = buttonPressed;
  ReadButtons();
  
  switch (buttonPressed) {

    case 3:
      
    case 1:
      
    case 4:
      
    case 2:

      switch(buttonPressed) {
        case 3:
        servoAngleIncrement = 5; 
        break;
        
        case 1:
        servoAngleIncrement = -5;
        break;

        case 4:
        servoAngleIncrement = -1;
        break;

        case 2:
        servoAngleIncrement = 1;
        break;  
      }
    tslIncrement = millis() - incrementTime;
    if ((prevButtonPressed != buttonPressed) || (tslIncrement > 250)) {
      incrementTime = millis();
      desiredServoAngle = desiredServoAngle + servoAngleIncrement;
      desiredServoAngle = constrain(desiredServoAngle,0,180);
      Serial.print(F("The desired servo angle = "));
      Serial.println(desiredServoAngle);
      }
    break;
    
    case 5:
      if (prevButtonPressed != buttonPressed) {
        if (state > 0) {
          Serial.println(F("aim/fire sequence is still in progress"));
        }
        else{
          state = 1;
          stateChangeTime = millis();
        }
      }
      break;
    case 0:
      //nothing
      break;
    default:
      //do nothing
      break;
  }

switch(state) {

  case 1:
    tslStateChange = millis() - stateChangeTime;
    if (tslStateChange > 0) {
      launcherServo.write(desiredServoAngle);
      Serial.print(F("Launcher servo commanded to "));
      Serial.println(desiredServoAngle);
      state = 2;
      stateChangeTime = millis();
    }
    break;

  case 2:
    tslStateChange = millis() - stateChangeTime;
    if (tslStateChange > 300) {
      digitalWrite(solenoidDirPin, HIGH);
      analogWrite(solenoidPowPin, solenoidPower);
      Serial.println(F("Firing !"));
      state = 3;
      stateChangeTime = millis();
    }
    break;

  case 3:
    tslStateChange = millis() - stateChangeTime;
    if (tslStateChange > solenoidActivationTime) {
      analogWrite(solenoidPowPin, 0);
      Serial.println(F("Done Firing :( "));
      state = 0;
    }
    break;
}

}
