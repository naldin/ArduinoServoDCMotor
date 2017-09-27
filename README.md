# ArduinoServoDCMotor
An Arduino servo motor with DC motor and potentiometer.

## Attention
Beware with correct position of wire motor (pin 5 and 6 of Arduino).
If they are changed, the motor will turn to the end travel of pot and can broke it.
Make a test with a low power (motorPWM variable) first.
If you want change the direction of motor, use something like this in Arduino loop:
runMotor(1023-val);

## Servo_DC_Motor_Pot
Using only proportionality for read/target value.

## Servo_DC_Motor_Pot_Prop
Using proportionality for read/target value and pwm.

Video [https://www.youtube.com/watch?v=m6xne2mSTUo](https://www.youtube.com/watch?v=m6xne2mSTUo)
