void TestReloader(void){
  int prevButtonPressed = buttonPressed;
  ReadButtons();
  switch(buttonPressed){
    case 5:
      if(prevButtonPressed != buttonPressed){
        if(state > 0){
          Serial.println(F("Reloading is still in progress."));
        }
        else{
          state = 1;
        }
      }
      break;
  }
  switch(state){
    case 1:
      reloaderServo.write(dispenseAngle);
      Serial.println(F("Dispensing..."));
      state = 2;
      stateChangeTime = millis();
      break;
    case 2:
      tslStateChange = millis() - stateChangeTime;
      if(tslStateChange > dispenseDuration){
        reloaderServo.write(holdAngle);
        Serial.println(F("Holding..."));
        state = 0;
      }
      break;
  }
}
