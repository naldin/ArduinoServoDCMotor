/*
    Arduino Servo DC Motor v1.0
    Ronaldo Rezende Junior
    ronaldo.rrj at gmail
    09/2017
    https://github.com/naldin

    *** Attention ***
    Beware with correct position of wire motor (pin 5 and 6 of Arduino).
    If they are changed, the motor will turn to the end travel of pot 
    and can broke it.
    Make a test with a low power (motorPWM variable) first.
    If you want change the direction of motor, use something like 
    this in Arduino loop: runMotor(1023-val);
*/

//variables
short int valRead = 0;
short int motorPWM = 20; //amount of power motor (0-255) were 255 is max.

//constants
const short int wireMT_1 = 5; //for wire motor H bridge
const short int wireMT_2 = 6; //for wire motor H bridge
const short int potMT = A0; //motor potentiometer
const short int potIn = A3; //input potentiometer
const short int diff_error = 10; //max error to potentiometer motor
const short int minPot = 10;  //minimal position potentiometer motor (0-1023)
const short int maxPot = 1010; //max position potentiometer motor (0-1023)
const short int maxValIn = 1023; //max *input value. For this case 1023, the max of pot.
// *here can use something like degress, where max could be 180

//setup
void setup() {
  pinMode (wireMT_1, OUTPUT); //wire motor to H bridge
  pinMode (wireMT_2, OUTPUT); //wire motor to H bridge
  pinMode (potMT, INPUT); //motor potentiometer
  pinMode (potIn, INPUT); //input potentiometer
  digitalWrite (wireMT_1, LOW);
  digitalWrite (wireMT_2, LOW);
}

//run motor function
void runMotor(short int valTarget) {
  //proportionality between input and output value
  while (valRead <= valTarget && abs(valRead - valTarget) >  diff_error) {
    valRead = (((float)analogRead(potMT) - minPot) / (maxPot - minPot)) * maxValIn;
    //run motor
    analogWrite (wireMT_1, motorPWM);
    analogWrite (wireMT_2, 0);
  }
  analogWrite (wireMT_1, 0); //turn off motor
  
  //proportionality between input and output value
  while (valRead >= valTarget && abs(valRead - valTarget) >  diff_error) {
    valRead = (((float)analogRead(potMT) - minPot) / (maxPot - minPot)) * maxValIn;
    //run motor
    analogWrite (wireMT_2, motorPWM);
    analogWrite (wireMT_1, 0);
  }
  analogWrite (wireMT_2, 0); //turn off motor
}

//loop
void loop() {
  short int val = analogRead(potIn); //read input potentiometer
  runMotor(val); //run motor for target value
  //runMotor(1023-val); //use for invert direction motor
}
