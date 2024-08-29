//Dual Axis Solar Panel

// include Servo library
#include <Servo.h>


// servo motor controlling the horizontal (West/East)
Servo horizontal;
int servoHor = 90;


int servoHorLimitHigh = 180;
int servoHorLimitLow = 65;


// servo motor controlling the vertical (North/South)
Servo vertical;
int servoVer = 90;


int servoVerLimitHigh = 120;
int servoVerLimitLow = 15;




// LDR pin connections
int ldrTR = 1; // LDR top right
int ldrTL = 3; // LDR top left
int ldrBR = 0; // LDR bottom right
int ldrBL = 2; // LDR bottom left




void setup() {
Serial.begin(9600);
// servo connections
horizontal.attach(9);
vertical.attach(10);
// move servos
horizontal.write(90);
vertical.write(0);
delay(3000);
}




void loop() {


int tr = analogRead(ldrTR); // top right
int tl = analogRead(ldrTL); // top left
int br = analogRead(ldrBR); // bottom right
int bl = analogRead(ldrBL); // bottom left


int dtime = 100; // change for debugging only
int tol = 50;


int aveTop = (tl + tr) / 2; // average value top
int aveBot = (bl + br) / 2; // average value bottom
int aveLeft = (tl + bl) / 2; // average value left
int aveRight = (tr + br) / 2; // average value right


int dvert = aveTop - aveBot; // check the difference of up and down
int dhoriz = aveLeft - aveRight; // check the difference of left and right


// send data to the serial monitor for debugging purposes
Serial.print("Top Left ");
Serial.println(tl);
Serial.print("Top Right ");
Serial.println(tr);
Serial.print("Bottom Left ");
Serial.println(bl);
Serial.print("Bottom Right ");
Serial.println(br);


// check if the difference is in the tolerance else change vertical angle
if (-1 * tol > dvert || dvert > tol) {
// if there is more light at the top
if (aveTop > aveBot) {
servoVer = ++servoVer;
// making sure to not exceed the limit
if (servoVer > servoVerLimitHigh) {
servoVer = servoVerLimitHigh;
}
}
// if there is more light at the bottom
else if (aveTop < aveBot) {
servoVer = --servoVer;
// making sure to not exceed the limit
if (servoVer < servoVerLimitLow) {
servoVer = servoVerLimitLow;
}
}
// give the servo motor the direction it needs to go
vertical.write(servoVer);
}


// check if the difference is in the tolerance else change horizontal angle
if (-1 * tol > dhoriz || dhoriz > tol) {
// if there is more light on the left
if (aveLeft > aveRight) {
servoHor = --servoHor;
// making sure to not exceed the limit
if (servoHor < servoHorLimitLow) {
servoHor = servoHorLimitLow;
}
}


// if there is more light on the right
else if (aveLeft < aveRight) {
servoHor = ++servoHor;
// making sure to not exceed the limit
if (servoHor > servoHorLimitHigh) {
servoHor = servoHorLimitHigh;
}
}
// give the servo motor the direction it needs to go
horizontal.write(servoHor);
}
delay(dtime);
}
