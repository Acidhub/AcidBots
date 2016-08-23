# AcidBots


## Project 1: AcidBot beta
Simple bluetooth / serial controlled car with a DVD as chassi and an Arduino UNO.


#### TODO:
1. [ ] ~~Make turns more reliable (and merge on gamma)~~ (!= motor drivers)


NANO Pinout:
![Arduino Nano Pinout diagram](http://acidhub.click/imghp/Arduino/NANO_PINOUT.png)


## Project 2: Acidbot gamma (phases Bluetooth, Line and Obstacle)


Bluetooth / serial controlled car.


* Complete bluetooth integration.
* Motor control (forward, backward, left, right)
* Lights ON/OFF (front)
* Autonomous mode (Obstacle avoidance with 3 front IR sensors)
* Face with a 8x8 led matrix controled by a MAX7219 IC.


#### TODO:
1. [x] Obstacle detection w/ 3 IR sensors
2. [ ] Line tracking w/ 3 line sensors
3. [ ] Create car modes:
  * [x] Remote mode
  * [x] Autonomous mode (w/ obstacle detection)
  * [ ] Autonomous mode (w/ obstacle detection and line tracking)
4. [x] Make a bluetooth command to switch between car modes
5. [x] Make him smile :smile:


UNO R3 Pinout:
![Arduino Nano Pinout diagram](http://acidhub.click/imghp/Arduino/UNO-R3_PINOUT.png)
