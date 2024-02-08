void MoveLauncher(void){
 // DebugPrint("Calling Demo1 function; startMotion = ", startMotion);
  if (motorOn){
    Moving();
  }
  else{
    if(startMotion){
      PreparingToMove();
    }
    else{
      NotMoving();
    }
  }
}

void PreparingToMove(void){
  //set desired position
  if ( (userInput == 'k') || (userInput == 'v')){
    switch(headed){
      case 0:
        leftSwitchState = digitalRead(leftPin);
        if (leftSwitchState == 1){
          Serial.println(F("Already home..."));
          counts = 5;
          desiredPosition = 5;
          startMotion = 0;
          headed = 1;
        }
        else {
          Serial.println(F("Headed home..."));
          desiredPosition = -50;
        }
        break;
  
      case 1:
        desiredPosition = driveTo[target];
        break;
  
      case 2:
        desiredPosition = 100;
        break;
    }
  }
  
  // set motorRight
  if(desiredPosition > counts){
    motorRight = 1; //need to move right
  }
  else{
    motorRight = 0; //need to move left
  }
  // turn motor on
  if(counts != desiredPosition){
    TurnMotorOn();
    startMotion = 0;
  }
}

void Moving(void){
  //countstripes
  CountStripes();
  
  //stop at target
  if(counts == desiredPosition){
    TurnMotorOff(25);
    CountStripes();
    Serial.print(F("Launcher at stripe "));
    Serial.println(counts);
  }
  //read switches
  leftSwitchState = digitalRead(leftPin);
  rightSwitchState = digitalRead(rightPin);
  
  //stop at home (moving left - left switch tripped.)
  if((motorRight == false) && (leftSwitchState)){
    TurnMotorOff(25);
    CountStripes();
    counts = 5;
    Serial.println("Launcher at home - counts set to 5");
  }
  //stop at reloader (moving right - right switch tripped.)
    if((motorRight) && (rightSwitchState)){
    TurnMotorOff(25);
    CountStripes();
    counts = 43;
    Serial.println("Launcher at home - counts set to 43");
    }
}
