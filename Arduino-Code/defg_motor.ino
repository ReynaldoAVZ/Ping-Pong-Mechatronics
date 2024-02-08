// TestMotor function uses left/right buttons to move launcher right or left
void TestMotor(void){
  int prevButtonPressed = buttonPressed;
  ReadButtons();
  switch (buttonPressed) {

      // Up button = 3
      // currently doing nothing for left/right function 
      case 3:   
      // Down button = 1
      // currently doing nothing for left/right function 
      case 1:
      tslIncrement = millis() - incrementTime;
        if ((prevButtonPressed != buttonPressed) || (tslIncrement > 250)) {
          incrementTime = millis();
          if (buttonPressed == 3) {
            counts = counts + 1;
          }
          else if (buttonPressed == 1){ 
            counts = counts - 1;
          }
        Serial.print(F("The value of counts is "));
        Serial.println(counts);
        }
        break;

      // left button = 4
      case 4:
        motorRight = 0;
        TurnMotorOn();
        break;

      // right button = 2
      case 2:
        motorRight = 1;
        TurnMotorOn();
        break;

      // select button = 5
      // currently doing nothing for left/right function 
      case 5:
        if (counts != 24) {
          counts = 24;
          Serial.print(F("The counts variable is "));
          Serial.println(counts);
        }
        break;

      // No button pressed = 0
      case 0:
        TurnMotorOff(25);
         if (userInput == 'g') {
          CountStripes();
         }
        break;

      // default case = who the hell knows ??
      // currently doing nothing for left/right function 
      default:
        break; 
  }
      
      if (motorOn){
        switch(userInput){
        
        case 'd':
          PrintLeftRight();
          break;

        case 'e':
          PrintSensorValue();
          break;

        case 'f':
          PrintBlackWhite();
          break;

        case 'g':
          CountStripes();
          break;
      }
    }
}
// Update tslPrint 
void PrintLeftRight(void){
  tslPrint = millis() - printTime;
  if (tslPrint > printInterval)  {
    printTime = millis();
    Serial.println(F("Launcher is moving"));
    if (motorRight == true){
      Serial.println(F("Right"));
    }
    else{
      Serial.println(F("Left"));
    }
  }
}

void PrintSensorValue(void) {
  irSensorValue = analogRead(pinSensor);
  tslPrint = millis() - printTime;
  if (tslPrint > 50) {
    printTime = millis();
    Serial.print(F("The sensor value is "));
    Serial.println(irSensorValue);
  //Lowest High value = 372
  //Highest high value = 992
  
  }
}

void PrintBlackWhite(void) {
  bool prevBlack = black; //prevBlack local and black global
  black = GetEncoderBoolean();
  if (black != prevBlack) {
    if (black == 1) {
      Serial.println(F("Over black"));
    }
    else {
      Serial.println(F("Over white"));
    }
    }
  }
