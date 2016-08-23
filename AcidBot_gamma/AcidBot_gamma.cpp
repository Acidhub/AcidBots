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

#define IRSL 5              // Left sensor input
#define IRSM 4              // Middle sensor input
#define IRSR 2              // Right sensor input

#define mxClock A4          // MAX7219 pinout
#define mxCS A3
#define mxDin A2

char comm;                  // Serial input
unsigned char speed;
long delay_;                // Parallel delay
bool autoMode = 0;
LedControl mx=LedControl(mxDin,mxClock,mxCS,1);

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
    pinMode(IRSL,INPUT);
    pinMode(IRSM,INPUT);
    pinMode(IRSR,INPUT);
}

void mxConfig(void) {
    mx.shutdown(0,false);   // Wake up,
    mx.setIntensity(0,2);   // set led intensity and
    mx.clearDisplay(0);     // clear
}

void move(char direction, unsigned char speed) {
    analogWrite(E1, speed);
    analogWrite(E2, speed);

    switch(direction) {
        case 'F':
            digitalWrite(M1, LOW);  // Both left and right wheel move forward
            digitalWrite(M2, HIGH);
            break;
        case 'B':
            digitalWrite(M1, HIGH); // Both left and right wheel move backward
            digitalWrite(M2, LOW);
            break;
        case 'L':
            digitalWrite(M1, HIGH); // Left wheel moves forward
            digitalWrite(M2, HIGH); // Right wheel moves backward
            break;
        case 'R':
            digitalWrite(M1, LOW);  // Left wheel moves backward
            digitalWrite(M2, LOW);  // Right wheel moves forward
            break;
        case 'S':
            analogWrite(E1, 0);     // Useless set motor direction
            analogWrite(E2, 0);     // Both left and right wheel stop
            break;
    }
}

void lights(bool on) {
    if(on == 1) {
        digitalWrite(A0, HIGH);
        digitalWrite(A1, HIGH);
    } else {
        digitalWrite(A0, LOW);
        digitalWrite(A1, LOW);
    }
}

void face(const char what, const char where = 'N') {
    byte clear = B00000000;
    byte eyes[3] = {B01100110, B11001100, B00110011};
    byte mouth[4] = {B00111100, B01000010, // Smile
                     B00011000, B00100100};           // 'o'

    switch(what) {
        case 'M':
            switch(where) {
                case 'S':
                    mx.setColumn(0,0,clear);
                    mx.setColumn(0,1,mouth[0]);
                    mx.setColumn(0,2,mouth[1]);
                    mx.setColumn(0,3,mouth[1]);
                break;
                case 'O':
                    mx.setColumn(0,0,mouth[2]);
                    mx.setColumn(0,1,mouth[3]);
                    mx.setColumn(0,2,mouth[3]);
                    mx.setColumn(0,3,mouth[2]);
                break;
                case 'N':
                    mx.setColumn(0,0,clear);
                    mx.setColumn(0,1,mouth[0]);
                    mx.setColumn(0,2,mouth[1]);
                    mx.setColumn(0,3,clear);
                break;
            }
        break;
        case 'E':
            switch(where) {
                case 'N':
                    mx.setColumn(0,5,eyes[0]);
                    mx.setColumn(0,6,eyes[0]);
                break;
                case 'L':
                    mx.setColumn(0,5,eyes[1]);
                    mx.setColumn(0,6,eyes[1]);
                break;
                case 'R':
                    mx.setColumn(0,5,eyes[2]);
                    mx.setColumn(0,6,eyes[2]);
                break;
                case 'C':
                    mx.setColumn(0,5,eyes[0]);
                    mx.setColumn(0,6,clear);
                break;
            }
        break;
    }
}


void eyeAnim(void) {
    delay_++;

    if(delay_ == 150000) face('E', 'C');
    else if(delay_ == 160000) face('E');
    else if(delay_ == 170000) face('E', 'C');
    else if(delay_ == 180000) face('E');
    else if(delay_ == 280000) face('E', 'L');
    else if(delay_ == 320000) face('E');
    else if(delay_ == 340000) face('E', 'R');
    else if(delay_ == 380000) {
        face('E');
        delay_ = 0;
    }
}

void setup(void) {
    Serial.begin(9600);     // Ready for bluetooth data
    sensorConfig();         // Sensors init
    motorControlConfig();   // Motor init (Shield IO)
    accControlConfig();     // Accessories init (lights, horn, etc).
    mxConfig();             // Led matrix init
    face('M');              // Give a smile
}

void loop(void) {
    comm = Serial.read();   // Get bluetooth/serial input

    if(comm != -1) {       // If not "nothing", echo received input
        Serial.print("\nReceived:\t");
        Serial.print(comm);
        Serial.print("\nAction:\t\t");
    }

    switch(comm) {
        case 'X':
            Serial.print("Entering autonomous mode");
            autoMode = 1;
            break;
        case 'x':
            Serial.print("Leaving autonomous mode");
            move('S', 0);
            face('M');
            autoMode = 0;
            break;
    }

    if(autoMode == 1) {
        char IRL = digitalRead(IRSL);
        char IRM = digitalRead(IRSM);
        char IRR = digitalRead(IRSR);

        if((IRL==0&&IRM==0&&IRR==1) ||
           (IRL==0&&IRM==1&&IRR==1) ||
           (IRL==1&&IRM==0&&IRR==1)) {
            move('R', 150);
            face('E', 'R');
            face('M', 'O');
        } else if((IRL==0&&IRM==0&&IRR==0) ||
                  (IRL==1&&IRM==0&&IRR==0) ||
                  (IRL==1&&IRM==1&&IRR==0)) {
            move('L', 150);
            face('E', 'L');
            face('M', 'O');
        } else {
            move('F', 150);
            face('E', 'C');
            face('M', 'S');
        }
    } else {
        eyeAnim();
        switch(comm) {
            case 'F':
                Serial.print("Forward...");
                move('F', speed);
                break;
            case 'R':
                Serial.print("Right...");
                move('R', speed);
                break;
            case 'L':
                Serial.print("Left...");
                move('L', speed);
                break;
            case 'B':
                Serial.print("Backward...");
                move('B', speed);
                break;
            case 'S':
                Serial.print("Stop!");
                move('S', 0);
                break;
            case 'W':
                Serial.print("Front lights ON");
                lights(1);
                break;
            case 'w':
                Serial.print("Front lights OFF");
                lights(0);
                break;
            case 'U':
            case 'u':
            case 'V':
            case 'v':
                Serial.println("Not implemented yet.");
                break;
            case 'q':
                Serial.println("Full powahhhhhh!");
                speed = 255;
            default:
                if(isDigit(comm)) {
                    Serial.print("Speed: ");
                    speed = map((int)comm - 48, 0, 10, 100, 255);
                    Serial.println(speed);
                }
        }
    }
}
