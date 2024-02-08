void TestIRLED(void)  {
  // compute the time of the last blink event
  tslBlink = millis() - blinkTime;

  if (ledOn == 0){ //If LED is off
    if (tslBlink > ledOffDuration){ 
      digitalWrite(ledPin, HIGH);
      ledOn = 1;
      blinkTime = millis();
      Serial.println(F("The LED is on"));
    }
  }
  else{
    if (tslBlink > ledOnDuration){
      digitalWrite(ledPin, LOW);
      ledOn = 0;
      blinkTime = millis();
      Serial.println(F("The LED is off"));
    }
  }
}
