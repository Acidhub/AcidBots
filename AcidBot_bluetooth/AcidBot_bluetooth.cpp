/*
  AcidBot Prototype (Bluetooth car) - gamma platform
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

#define M1 12 // Right wheel
#define M2 13 // Left wheel
#define E1 3  // Right wheel speed control
#define E2 11 // Left wheel speed control

int comm;

void accControlConfig() {  // Accessories config (Shield IO)
    pinMode(A0, OUTPUT);     // Left light
    pinMode(A1, OUTPUT);     // Right light
}

void motorControlConfig(void) { // Motor pinout config (Shield IO)
    pinMode(M1, OUTPUT);
    pinMode(M2, OUTPUT);
    pinMode(E1, OUTPUT);
    pinMode(E2, OUTPUT);
}

void forward(void) {       // Move forward
    digitalWrite(M1, LOW);   // Both left and right wheel move forward
    digitalWrite(M2, HIGH);
    analogWrite(E1, 255);
    analogWrite(E2, 255);
}

void backward(void) {      // Move backward
    digitalWrite(M1, HIGH);  // Both left and right wheel move backward
    digitalWrite(M2, LOW);
    analogWrite(E1, 255);
    analogWrite(E2, 255);
}

void right(void) {         // Turn right
    digitalWrite(M1, HIGH);  // Left wheel moves forward
    digitalWrite(M2, HIGH);  // Right wheel moves backward
    analogWrite(E1, 255);
    analogWrite(E2, 150);
}

void left(void) {          // Turn left
    digitalWrite(M1, LOW);   // Left wheel moves backward
    digitalWrite(M2, LOW);   // Right wheel moves forward
    analogWrite(E1, 150);
    analogWrite(E2, 255);
}

void stop_(void) {         // Stop
    analogWrite(E1, 0);      // Useless set motor direction
    analogWrite(E2, 0);      // Both left and right wheel stop
}

void lightsOn(void) {
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
}

void lightsOff(void) {
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
}

void setup() {
    Serial.begin(9600);      // Ready for bluetooth data
    motorControlConfig();    // Motor init (Shield IO)
    accControlConfig();      // Accessories init (lights, horn, etc).
    stop_();
}

void loop() {
    comm = Serial.read();    // Get bluetooth/serial input
    if (comm != -1) {        // If not "nothing", echo received input
        Serial.print("\nReceived:\t");
        Serial.print(char(comm));
        Serial.print("\nAction:\t\t");
    }
    switch (comm) {
        case 'F':
            Serial.print("Forward...");
            forward();
            break;
        case 'R':
            Serial.print("Right...");
            right();
            break;
        case 'L':
            Serial.print("Left...");
            left();
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
        case 'X':
        case 'x':
            Serial.println("Not implemented yet.");
            break;
    }
}
