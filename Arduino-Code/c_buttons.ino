void TestButtons(void)  { 
  // Keep track of the previously pressed button
  int prevButtonPressed = buttonPressed;
    
  // Check what button is currently pressed
  ReadButtons();

  // If appropriate, print a new message
  tslPrint = millis() - printTime;
  if ((tslPrint > printInterval) || (buttonPressed != prevButtonPressed)) {
    printTime = millis();
    switch (buttonPressed) {
        
      case 3:
        Serial.println(F("UP Button Pressed"));
        break;

      case 1:
        Serial.println(F("DOWN Button Pressed"));
        break;

      case 4:
        Serial.println(F("LEFT Button Pressed"));
        break;

      case 2:
        Serial.println(F("RIGHT Button Pressed"));
        break;

      case 5:
        Serial.println(F("SELECT Button Pressed"));
        break;

      case 0:
        Serial.println(F("NO Button Pressed"));
        break;

      default:
        Serial.println(F("Something Went Wrong"));
        break;
        
    }
  }
}
