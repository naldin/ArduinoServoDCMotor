/*
    Arduino Servo DC Motor v1.0
    PWM proportional
    Ronaldo Rezende Junior
    ronaldo.rrj at gmail
    09/2017
    https://github.com/naldin
*/

//variables
short int valRead = 0;
short int motorPWM = 0;
short int error = 0; //difference between target value and input value

//constants
const short int kp = 3; //proportionality constant
const short int mp = 20; //minimal power (pwm) to motor
const short int wireMT_1 = 5; //for wire motor H bridge
const short int wireMT_2 = 6; //for wire motor H bridge
const short int potMT = A0; //motor potentiometer
const short int potIn = A3; //input potentiometer
const short int diff_error = 10; //max error to potentiometer motor
const short int minPot = 10;  //minimal input value
const short int maxPot = 1010; //max input value
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
    //pwm proportional
    error = valTarget - valRead;
    motorPWM = ((kp * error) / 100) + mp;
    //run motor
    analogWrite (wireMT_1, motorPWM);
    analogWrite (wireMT_2, 0);
  }
  analogWrite (wireMT_1, 0); //turn off motor
  
  //proportionality between input and output value
  while (valRead >= valTarget && abs(valRead - valTarget) >  diff_error) {
    valRead = (((float)analogRead(potMT) - minPot) / (maxPot - minPot)) * maxValIn;
    //pwm proportional
    error = valRead - valTarget;
    motorPWM = ((kp * error) / 100) + mp;
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
