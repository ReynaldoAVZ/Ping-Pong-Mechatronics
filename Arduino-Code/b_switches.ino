void TestSwitches(void) {
  // Keep track of previous switch states for comparison
  int prevLeftSwitchState = leftSwitchState;
  int prevRightSwitchState = rightSwitchState;
  
  // Update the switch state variables
  int tempLeftSwitchState = digitalRead(leftPin);
  int tempRightSwitchState = digitalRead(rightPin);
  
  //Left switch debounce code
  if (tempLeftSwitchState != prevLeftSwitchState){
    tslLeftSwitchChange = millis() - leftSwitchChangeTime;
    if (tslLeftSwitchChange > switchDebounceInterval) {
      leftSwitchChangeTime = millis();
      leftSwitchState = tempLeftSwitchState;
    }
  }

  //Right switch debounce code

 if (tempRightSwitchState != prevRightSwitchState){
  tslRightSwitchChange = millis() - rightSwitchChangeTime;
  if (tslRightSwitchChange > switchDebounceInterval) {
    rightSwitchChangeTime = millis();
    rightSwitchState = tempRightSwitchState;
    }
  }
  // If appropriate, print a new message
  tslPrint = millis() - printTime;
  if ((leftSwitchState != prevLeftSwitchState) || (rightSwitchState != prevRightSwitchState) || (tslPrint > printInterval)) {
    printTime = millis();
    Serial.print(F("Left Switch State: "));
    Serial.print(leftSwitchState);
    Serial.print(F(" ... Right Switch State: "));
    Serial.println(rightSwitchState);
  }
}
