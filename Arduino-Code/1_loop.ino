/*******************
 ** Loop Function **
 *******************/
void loop(void) {
  //PUT YOUR MAIN CODE HERE, TO RUN REPEATEDLY
  //Serial.print(Serial.available());
  //Serial.println(" bytes available to read");

  if (Serial.available() >= 2)  {
    userInput = Serial.read();
    Serial.read();
    Serial.print(F("User entered "));
    Serial.println(userInput);
    newUserInput = 1;
  }

  switch (userInput)  {
    case 'a':
      // print instructions once
      if (newUserInput == 1)  {
        // CODE HERE (once code)
        Serial.println(F("Test a: Check that IR LED is blinking"));
        newUserInput = 0; // do NOT delete !!!
      }
      TestIRLED();
      break;

    case 'b':
      if (newUserInput == 1)  {
        Serial.println(F("Test b: Press the switches to test"));
        newUserInput = 0; // do NOT delete !!!
      }
      TestSwitches();
      break;

    case 'c':
      if (newUserInput == 1)  {
        Serial.println(F("Test c: Press the buttons to test"));
        newUserInput = 0; // do NOT delete !!!
      }
      TestButtons();
      break;

    case 'd':
      if (newUserInput == 1)  {
        Serial.println(F("Press the left and right buttons to test the motor."));
        newUserInput = 0; // do NOT delete !!!
      }
      TestMotor();
      break;

    case 'e':
      if (newUserInput == 1)  {
        Serial.println(F("Press the left and right buttons to test the motor and sensor."));
        newUserInput = 0; // do NOT delete !!!
      }
      TestMotor();
      break;

    case 'f':
      if (newUserInput == 1)  {
        Serial.println(F("Press the left and right buttons to test the motor and encoder."));
        newUserInput = 0; // do NOT delete !!!
      }
      TestMotor();
      break;
      
    case 'g':
      if (newUserInput == 1)  {
        Serial.println(F("Press the left and right buttons to count stripes"));
        Serial.println(F("Press the up and down buttons to increment counts"));
        Serial.println(F("Press the select button to set counts to 24"));
        newUserInput = 0; // do NOT delete !!!
      }
      TestMotor();
      break;
      
    case 'h':
      if (newUserInput == 1)  {
        startMotion = 0;
        Serial.println(F("Press the left and right buttons to increment desired position"));
        Serial.println(F("Press the up and down buttons to increment counts"));
        Serial.println(F("Press the select button to send the launcher to the desired position"));
        newUserInput = 0; // do NOT delete !!!
      }
      TestMoveLauncher();
      break;
    case 'i':
      if (newUserInput == 1)  {
        startMotion = 0;
        Serial.println(F("Press the up/down/left/right buttons to increment desired servo angle"));
        Serial.println(F("Press the select button to command the servo and fire the solenoid"));
        newUserInput = 0; // do NOT delete !!!
      }
      TestAimFire();
      break;
      
    case 'j':
      if (newUserInput == 1)  {
        startMotion = 0;
        Serial.println(F("Press the select button to reload a ball"));
        newUserInput = 0; // do NOT delete !!!
      }
      TestReloader();
      break;

    case 'k':
      if (newUserInput == 1)  {
        startMotion = 0;
        Serial.println(F("Press the left and right buttons to increment headed value"));
        Serial.println(F("Press the up and down buttons to increment target value"));
        Serial.println(F("Press the select button to start Demo1"));
        newUserInput = 0; // do NOT delete !!!
      }
      Demo1();
      break;
      
    case 'z':
      // do something once
      if (newUserInput == 1)  {
        PrintMenu();
        newUserInput = 0; // do not delete !
      }
      break;

    case 's': //GET DATA from matlab
      GetDataFromMATLAB();
      userInput = 'x';
      Serial.println(F("done"));
      break;

    case 't':
      GetDataFromMATLAB();
      ComputeStuff();
      userInput = 'x';
      Serial.println(F("done"));
      break;

    case 'v':
      if (newUserInput == 1)  {
        Serial.println(F("Running Demo 4 / competition code"));
        newUserInput = 0; // do NOT delete !!!
        GetDataFromMATLAB();
        startMotion = 1;
        state = 1;
      }
      Demo1();
      break;
    

    default:
      // do something once
      if (newUserInput == 1)  {
        Serial.println(F("Waiting for a valid user input"));
        Serial.println(F("Enter z to print menu"));
        newUserInput = 0; // do not delete !
        if(motorOn == 1){
          TurnMotorOff(25);
          Serial.println(F("Killing motion, wtf did you input :("));
        }
        startMotion = 0;
        headed = 0;
        target = 0;
      }
      break;
  }
} // end loop() function
