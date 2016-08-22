/*
  AcidBot Prototype gamma - Bluetooth car with autonomous mode
  Copyright (C) 2016 - Acidhub <contact@acidhub.click>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

  =======================================================================

*/

#include <Arduino.h>
#include <LedControl.h>     // Matrix MAX7219 lib

#define M1 12               // Right wheel
#define M2 13               // Left wheel
#define E1 3                // Right wheel speed control
#define E2 11               // Left wheel speed control

#define IRSensorLeft 5      // Left sensor input
#define IRSensorMiddle 4    // Middle sensor input
#define IRSensorRight 2     // Right sensor input

LedControl mx=LedControl(A2,A4,A3,1); // MAX7219 pinout

unsigned char IRSL;         // left sensor status
unsigned char IRSM;         // middle sensor status
unsigned char IRSR;         // right sensor status

int comm;                   // Serial input
int autoMode = 0;
double delay_;

void accControlConfig(void) {// Accessories config (Shield IO)
    pinMode(A0, OUTPUT);    // Left light
    pinMode(A1, OUTPUT);    // Right light
}

void motorControlConfig(void) { // Motor pinout config (Shield IO)
    pinMode(M1, OUTPUT);
    pinMode(M2, OUTPUT);
    pinMode(E1, OUTPUT);
    pinMode(E2, OUTPUT);
}

void sensorConfig(void) {   // Sensor pinout config (Shield IO)
    pinMode(IRSensorLeft,INPUT);
    pinMode(IRSensorMiddle,INPUT);
    pinMode(IRSensorRight,INPUT);
}

void mxConfig(void) {
    mx.shutdown(0,false);   // Wake up,
    mx.setIntensity(0,2);   // set led intensity and
    mx.clearDisplay(0);     // clear
}

void sensorScan(void) {     // Get sensors status
    IRSL = digitalRead(IRSensorLeft);
    IRSM = digitalRead(IRSensorMiddle);
    IRSR = digitalRead(IRSensorRight);
}

void forward(void) {        // Move forward
    digitalWrite(M1, LOW);  // Both left and right wheel move forward
    digitalWrite(M2, HIGH);
    analogWrite(E1, 255);
    analogWrite(E2, 255);
}

void backward(void) {       // Move backward
    digitalWrite(M1, HIGH); // Both left and right wheel move backward
    digitalWrite(M2, LOW);
    analogWrite(E1, 255);
    analogWrite(E2, 255);
}

void right(void) {          // Turn right
    digitalWrite(M1, HIGH); // Left wheel moves forward
    digitalWrite(M2, HIGH); // Right wheel moves backward
    analogWrite(E1, 255);
    analogWrite(E2, 150);
}

void left(void) {           // Turn left
    digitalWrite(M1, LOW);  // Left wheel moves backward
    digitalWrite(M2, LOW);  // Right wheel moves forward
    analogWrite(E1, 150);
    analogWrite(E2, 255);
}

void stop_(void) {          // Stop
    analogWrite(E1, 0);     // Useless set motor direction
    analogWrite(E2, 0);     // Both left and right wheel stop
}

void lightsOn(void) {
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
}

void lightsOff(void) {
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
}

void face(String where = "front") {
    mx.clearDisplay(0);

    byte eyes[3] = {B01100110, B11001100, B00110011};
    byte smile[2] = {B00111100, B01000010};

    mx.setColumn(0,1,smile[0]);
    mx.setColumn(0,2,smile[1]);
    if(where == "front") {
        mx.setColumn(0,5,eyes[0]);
        mx.setColumn(0,6,eyes[0]);
    } else if(where == "left") {
        mx.setColumn(0,5,eyes[1]);
        mx.setColumn(0,6,eyes[1]);
    } else if(where == "right") {
        mx.setColumn(0,5,eyes[2]);
        mx.setColumn(0,6,eyes[2]);
    } else if(where == "blink") {
        mx.setColumn(0,5,eyes[0]);
    }
}

void faceAnim(void) {
    delay_++;
    if(delay_ == 150000) face("blink");
    else if(delay_ == 160000) face();
    else if(delay_ == 220000) face("left");
    else if(delay_ == 230000) face("front");
    else if(delay_ == 232000) face("right");
    else if(delay_ == 242000) {
        face();
        delay_ = 0;
    }
}

void setup(void) {
    Serial.begin(9600);     // Ready for bluetooth data
    sensorConfig();         // Sensors init
    motorControlConfig();   // Motor init (Shield IO)
    accControlConfig();     // Accessories init (lights, horn, etc).
    mxConfig();             // Led matrix init
    stop_();
    face();
}

void loop(void) {
    comm = Serial.read();   // Get bluetooth/serial input
    if (comm != -1) {       // If not "nothing", echo received input
        Serial.print("\nReceived:\t");
        Serial.print(char(comm));
        Serial.print("\nAction:\t\t");
    }
    faceAnim();
    switch(comm) {
        case 'X':
            Serial.print("Entering autonomous mode");
            autoMode = 1;
            break;
        case 'x':
            Serial.print("Leaving autonomous mode");
            stop_();
            autoMode = 0;
            break;
    }
    if(autoMode == 1) {
        sensorScan();
        if(IRSL==1&&IRSM==1&&IRSR==1) {
            forward();
        }
        if((IRSL==0&&IRSM==0&&IRSR==1)||(IRSL==0&&IRSM==1&&IRSR==1)||(IRSL==1&&IRSM==0&&IRSR==1)) {
            right();
        }
        if((IRSL==0&&IRSM==0&&IRSR==0)||(IRSL==1&&IRSM==0&&IRSR==0)||(IRSL==1&&IRSM==1&&IRSR==0)) {
            left();
        }
    } else {
        switch (comm) {
            case 'F':
                Serial.print("Forward...");
                forward();
                face("front");
                break;
            case 'R':
                Serial.print("Right...");
                right();
                face("right");
                break;
            case 'L':
                Serial.print("Left...");
                left();
                face("left");
                break;
            case 'B':
                Serial.print("Backward...");
                backward();
                break;
            case 'S':
                Serial.print("Stop!");
                stop_();
                break;
            case 'W':
                Serial.print("Front lights ON");
                lightsOn();
                break;
            case 'w':
                Serial.print("Front lights OFF");
                lightsOff();
                break;
            case 'U':
            case 'u':
            case 'V':
            case 'v':
                Serial.println("Not implemented yet.");
                break;
        }
    }
}
