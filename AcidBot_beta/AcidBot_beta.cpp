/*
  AcidBot Prototype beta - Ultra basic car robot build with a CD
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

#include <Arduino.h> //Now a PlatformIO project :)

// Motor pinout set (!= from gamma project)
#define MA1  5  // motor A-
#define MA2  6  // motor A+
#define MB1  10 // motor B-
#define MB2  11 // motor B+

int comm;

void motorControlConfig(void) { // Motor pinout config
    pinMode(MA1, OUTPUT);
    pinMode(MA2, OUTPUT);
    pinMode(MB1, OUTPUT);
    pinMode(MB2, OUTPUT);
}

void forward(void) {    // move forward
    digitalWrite(MA1, LOW);
    digitalWrite(MA2, HIGH);
    digitalWrite(MB1, LOW);
    digitalWrite(MB2, HIGH);
}

void backward(void) {    // move backward
    digitalWrite(MA1, HIGH);
    digitalWrite(MA2, LOW);
    digitalWrite(MB1, HIGH);
    digitalWrite(MB2, LOW);
}

void right(void) {       // turn right
    digitalWrite(MA1, HIGH);
    digitalWrite(MA2, LOW);
    digitalWrite(MB1, LOW);
    digitalWrite(MB2, HIGH);
}

void left(void) {        // turn left
    digitalWrite(MA1, LOW);
    digitalWrite(MA2, HIGH);
    digitalWrite(MB1, HIGH);
    digitalWrite(MB2, LOW);
}

void stop_(void) {       // stop
    digitalWrite(MA1, LOW);
    digitalWrite(MA2, LOW);
    digitalWrite(MB1, LOW);
    digitalWrite(MB2, LOW);
}

void setup() {
    Serial.begin(9600);     // Serial monitor (bluetooth compatible)
    motorControlConfig();   // Init motors
    stop_();
}

void loop() {
    comm = Serial.read();
    if (comm != -1) {
        Serial.print("\nReceived:\t");
        Serial.print(char(comm));
        Serial.print("\nAction:\t\t");
    }
    switch (comm) {
        case 'F':
            Serial.print("Forward...");
            forward();
            break;
        case 'B':
            Serial.print("Backward...");
            backward();
            break;
        case 'R':
            Serial.print("Right...");
            right();
            break;
        case 'L':
            Serial.print("Left...");
            left();
            break;
        case 'S':
            Serial.print("Stop!");
            stop_();
            break;
        case 'W': // Front lights
        case 'w':
        case 'U': // Back lights
        case 'u':
        case 'V': // Horn
        case 'v':
        case 'X': // Other
        case 'x':
            Serial.println("Not implemented in this robot.");
            break;
    }
}
