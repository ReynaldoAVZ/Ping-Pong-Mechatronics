/****************************************************************
  Author Name: Reynaldo Villarreal Zambrano, Edwin Prieto
  Date: 10.28.22
  Sketch Name: TestHardwareSketch
  Sketch Description: TestHardwareSketch contains all global variables/pins/ and setups.

  Button Usage: Up/Down    - 
              Left/Right - 
              Select     -

  Pin Usage:    Pin type/number     Hardware
              ----------------    ----------------
Digital output/13/BlinkIR         
Digital input/11/SwitchDemo
Digital input/12/SwitchDemo
Analog input /A7/ButtonDemo
Digital output/4/defg_motor
Digital output/5/defg_motor
Analog input /A5/PrintSensorValue
digitial output /9/ TestAimFire
Analog input/A6/ Solenoid Power
Digital output/7/ Solenoid Direction
Digital output/10/Test Reloader
*******************************************************************/

/****************************
 ** #defines and #includes **
 ****************************/
 //TestAimFire
#include <Servo.h>
/***********************
 ** Global Variables ***
 ***********************/
// *** Declare & Initialize Pins ***
//BlinkIRDemo
const int ledPin = 13; //Digital output

//switchDemo
const int leftPin = 11; //Digital input
const int rightPin = 12;//Digital input

//ButtonDemo
const int buttonPin = A7;

//defg_motor
const int motorDirection = 4;
const int motorPower = 5;

//PrintSensorValue
const int pinSensor = A5;

//Test aim fire
const int launcherServoPin = 9;
const int solenoidPowPin = 6;
const int solenoidDirPin = 7;

//Test Reloader
const int reloaderServoPin = 10;

//

// *** Create Servo Objects ***

//Test aim fire
Servo launcherServo;

//Test Reloader
Servo reloaderServo;

// *** Declare & Initialize Program Variables ***

//BlinkIRDemo
int ledOnDuration = 1000; //Time(ms) that LED stays on
int ledOffDuration = 2000; //Time(ms) that LED stays off
unsigned long blinkTime = 0; //Time(ms) that LED was last turned on or off
unsigned long tslBlink = 0; //Length of time(ms) that has elapsed since LED was on or off
bool ledOn = 0; // Variable that keeps track if LED is on or off

//switchDemo
int leftSwitchState = 0; // Stores the state 0 = open or 1 = close of left
int rightSwitchState = 0; // Stores the state 0 = open or 1 = close of right
unsigned long printTime = 0; // Time that the switch states where last printed to the serial monitor(ms)
unsigned long tslPrint = 0; // Lenght of time in (ms) that has elapsed since last message printed
int printInterval = 250; // Dersired length of time between printed messages when printstates are not changing

//switchDebounceDemo
unsigned long leftSwitchChangeTime = 0; // Time (ms) that the left switch last changed states
unsigned long rightSwitchChangeTime = 0; // Time (ms) that the right switch last changed states
unsigned long tslLeftSwitchChange = 0; // Length of time (ms) that has elapsed since left switch changed states
unsigned long tslRightSwitchChange = 0; // Length of time (ms) that has elapsed since right switch changed states
int switchDebounceInterval = 20; // Time (ms) to wait for switch to stop bouncing

//ButtonDemo
int buttonNumber = 0; //Stores the number of the button that corresponds to the 0-1023 value read from A7
unsigned long cibn = 0; // cibn stands for "Consecutive identiacal button numbers", this variable keeps track number how many times buttonNumber is the same
int buttonPressed = 0; //Stores number of button that was actually pressed.

char userInput = 'z';
bool newUserInput = 1; // 1 means user just entered a letter
// 0 means user did not enter a letter this time through

// debugPrint() function 
unsigned long debugPrintTime = 0;
unsigned long tslDebugPrint = 0;  // time since last debug print
int debugPrintInterval = 200;     // you can choose this time

// debugBlink() function
const int debugLedPin = 13;   // onboard LED
unsigned long debugBlinkTime = 0;
unsigned long tslDebugBlink = 0;  // time since last debug blink
int debugLedHiLo = 0;

//defg_motor part a
const int motorPowerValue = 255; // supplies power to motor
bool motorOn = 0; //flag variable used to keep track of whether the motor is on or motor is off
bool motorRight = 0; // flag variable used to keep track of direction of motor. 1 is right, 0 is left.

//PrintSensorValue
int irSensorValue = 0; //Stores the 0 to 1023 value, representing the voltage read.

//Encoder Boolean
bool black = 1; // stores 1 if the IR reflectance is over a black stripe of a 0 if its over a white stripe

//CountStripes
unsigned long stripeChangeTime = 0; //A varaible to keep track of time at which IR reflectant sensor moves from white to black stripe(viseVersa).
unsigned long tslStripeChange = 0; // A varialbe to store time that has elapsed since the IR reflectant sensor moved from a black stripe to a white stripe.
int counts = 24; // Counter variable used to store the stripe number that the IR reflectant sesnor is over.

//Test Motor
unsigned long  incrementTime = 0; 
unsigned long tslIncrement = 0;
// These will control the speed of which a varaibles value is incremented by a button press.

// Move Launcher
bool startMotion = 0; // when true, flag variable indicates that the launcher should start moving somewhere. when motor on, launcher starts moving

//Test Move Launcher
int desiredPosition = 24;

//TestAimFire
int desiredServoAngle = 90;
int servoAngleIncrement = 5;
int state = 0; //Variable used to control what action is taken;
unsigned long stateChangeTime = 0; // Variable used to keep track of time that state changed value;
unsigned long tslStateChange = 0; // Variable used to store the time that has elapsed since state changed value;
int solenoidPower = 255;

//Robot 9
int solenoidActivationTime = 79; // milliseconds

// Test Reloader
int holdAngle = 60; // 30 is a guess for the reloader servo angle that will hold balls in place in the reloader
int dispenseAngle = 20; // 0 is a guess for the reloader servo angle that will drop one ball from the front
int dispenseDuration = 300; // milliseconds

//Demo 1 Motion Control
int target = 0; // keeps track of which target the robot is currently on
int headed = 0; // specifies where the launcher will move next
int driveTo[] = { 19, 35, 33, 31, 32, 34 }; // An array of stripe targets where targets are at
float xTargetVec[6] = {0.7, 0.8, 0.9, 1.0, 1.1, 1.2};
//Demo 1 At Target
int writeToServo[] = { 140, 110, 130, 90, 120, 80 }; // Array of servo angles for each target
float alpha = 38.4;
float beta = 0.015;
float thetaL0 = 11.77;
float kappa = 3.279;
float lambda = -0.0022; 

float slope = -0.01;
float intercept = 2;
/********************
 ** Setup Function **
 ********************/
void setup(void) {
  // PUT YOUR SETUP CODE HERE, TO RUN ONCE:

  // *** Configure Digital Pins & Attach Servos ***

  //BlinkIRDemo
  pinMode(ledPin, OUTPUT); //

  //switchDemo
  pinMode(leftPin,INPUT_PULLUP);
  pinMode(rightPin,INPUT_PULLUP);

  //defg_motor
  pinMode(motorDirection, OUTPUT);
  pinMode(motorPower, OUTPUT);

  //Test aim fire
  launcherServo.attach(launcherServoPin);
  pinMode(solenoidPowPin, OUTPUT);
  pinMode(solenoidDirPin, OUTPUT);

  //Test Reloader
  reloaderServo.attach(reloaderServoPin);
  
  // *** Initialize Serial Communication ***
  Serial.begin(9600);

  // *** Take Initial Readings ***

  GetEncoderBoolean();

  // *** Move Hardware to Desired Initial Positions ***

  //Test Reloader
  reloaderServo.write(holdAngle);
  
}// end setup() function
