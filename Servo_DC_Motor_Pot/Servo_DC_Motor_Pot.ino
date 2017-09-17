/*
    Arduino Servo DC Motor
    Ronaldo Rezende Junior
    ronaldo.rrj at gmail
    09/2017
    https://github.com/naldin
*/

//variables
short int valPot = 0;
short int motorPWM = 20; //amount of power motor (0-255) were 255 is max.

//constants
const short int wireMT_1 = 5; //for wire motor H bridge
const short int wireMT_2 = 6; //for wire motor H bridge
const short int potMT = A0; //motor potentiometer
const short int potIn = A3; //input potentiometer
const short int diff_error = 20; //max error to potentiometer motor
const short int minPot = 10;  //minimal input value
const short int maxPot = 1010; //max input value
const short int maxValIn = 999; //max *potentiometer value
// *here can use something like degress, where max could be 180

//setup
void setup() {
  pinMode (wireMT_1, OUTPUT); //wire motor to H bridge
  pinMode (wireMT_2, OUTPUT); //wire motor to H bridge
  pinMode (potMT, INPUT); //motor potentiometer
  pinMode (potIn, INPUT); //input potentiometer
  digitalWrite (wireMT_1, LOW);
  digitalWrite (wireMT_2, LOW);
  valPot = analogRead(potMT);
}

//run motor function
void runMotor(short int valIn) {
  //proportionality between input and output value
  while (valPot <= valIn && abs(valPot - valIn) >  diff_error) {
    valPot = (((float)analogRead(potMT) - minPot) / (maxPot - minPot)) * maxValIn;
    //run motor
    analogWrite (wireMT_1, motorPWM);
    analogWrite (wireMT_2, 0);
  }
  analogWrite (wireMT_1, 0); //turn off motor
  
  //proportionality between input and output value
  while (valPot >= valIn && abs(valPot - valIn) >  diff_error) {
    valPot = (((float)analogRead(potMT) - minPot) / (maxPot - minPot)) * maxValIn;
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
}
