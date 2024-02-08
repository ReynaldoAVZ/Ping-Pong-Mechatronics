void NotMoving(void) {
  
  //at home
  if (leftSwitchState){
    AtHome();
    //servo motor at home
  }
  else if (rightSwitchState){
    AtReloader();
    //servo motor at reloader
  }
  else if (desiredPosition == counts) {
    AtTarget();
    // servo motor at target
  }
  
}

void AtReloader(void) {

  switch(state) {

    case 1: // Dispense ball
      reloaderServo.write(dispenseAngle);
      Serial.println(F("Dispensing..."));
      state = 2;
      stateChangeTime = millis();     
      break;

    case 2:// delay and stop dispensing
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > dispenseDuration) {
        reloaderServo.write(holdAngle);
        Serial.println(F("Holding..."));
        state = 3;
        stateChangeTime = millis();
      }
      break;

    case 3://delay then set motion variables
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > 1) {
        startMotion = 1;
        headed = 1;
        target = target + 1;
        Serial.println(F("Ball reloaded - setting motion variables"));
        state = 1;      
      }
      break;
          
  }
}

void AtHome(void) {

  switch(state) {

    case 1: //LED ON
      digitalWrite(ledPin, HIGH);
      ledOn = 1;
      Serial.println(F("Triggering timer - LED on"));
      state = 2;
      stateChangeTime = millis();
      break;

    case 2: //delay then turn LED off
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > 1000) {
        digitalWrite(ledPin, LOW);
        ledOn = 0;
        Serial.println(F("Triggering timer - LED off"));
        state = 3;       
      }
      break;

    case 3: // set motion variables
      Serial.println(F("Setting motion variables"));
      if(target < 5){
        if( (target == 0) && (userInput == 'v')){
          Serial.println("Calling compute stuff");
          ComputeStuff();
        }
        startMotion = 1;
        headed = 1;
        state = 1;
      }
      else{
        target = 0;
        state = 0;
        Serial.println(F("All done :)"));
        if(userInput == 'v'){
          Serial.println("done");
        }
        userInput = 'x';
      }
      break;     
  }
}

void AtTarget(void) {
  switch (state){
    case 1: // command launcher servo to firing angle
      desiredServoAngle = writeToServo[target];
      launcherServo.write(desiredServoAngle);
      Serial.print(F("Commanding launcher servo to "));
      Serial.print(desiredServoAngle);
      Serial.print(F(" for target "));
      Serial.println(target);
      state = 2;
      stateChangeTime = millis();
      break;

    case 2: //delay then turn solenoid on
      tslStateChange = millis()- stateChangeTime;
      if(tslStateChange > 250){
        digitalWrite(solenoidDirPin, HIGH);
        analogWrite(solenoidPowPin, solenoidPower);
        Serial.println(F("Firing !"));
        state = 3;
        stateChangeTime = millis();
      }
      break;

    case 3: //delay then turn solenoid off
      tslStateChange = millis() - stateChangeTime;
      if(tslStateChange > solenoidActivationTime){
        digitalWrite(solenoidDirPin, LOW);
        analogWrite(solenoidPowPin, 0);
        Serial.println(F("Done firing..."));
        state = 4;
        stateChangeTime = millis();
      }
      break;

    case 4: // delay then command the launcher servo to the reload angle
      tslStateChange = millis() - stateChangeTime;
      if(tslStateChange > 1){
        desiredServoAngle = 60;
        launcherServo.write(desiredServoAngle);
        Serial.println(F("Commanding launcher servo to reload angle"));
        state = 5;
      }
      break;

    case 5: // set motion variables
      // set motion variables
      startMotion = 1;
      if (target < 5){
        headed = 2;
      }
      else{
        headed = 0;
      }
      Serial.println(F("Target actions complete - setting motion variables"));
      state = 1;
      break;
  }
}
