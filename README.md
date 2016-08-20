# AcidBots
##Project 1: AcidBot beta
Simple bluetooth or Serial controlled car.

#####TODO:
1. [ ] ~~Make turns more reliable (and merge on gamma)~~

####Used:
* [A DVD as platform/chassi](http://acidhub.click/imghp/Arduino/DVD.jpg) :dvd:
* [Arduino Nano with extension board](http://acidhub.click/imghp/Arduino/Nano_with_board.jpg)
* [2-way DC motor drive](http://acidhub.click/imghp/Arduino/Motor_drive.jpg)
* [2 DC motors with wheels](http://acidhub.click/imghp/Arduino/motor_wheel.jpg)
* [Mini breadboard](http://acidhub.click/imghp/Arduino/Breadboard_mini.jpg)
* [Bluetooth adapter](http://acidhub.click/imghp/Arduino/bluetooth.jpg)
* [Some few connections](http://acidhub.click/imghp/Arduino/complex-wiring.jpg)
* Glue :trollface:

NANO Pinout:
![Arduino Nano Pinout diagram](http://acidhub.click/imghp/Arduino/NANO_PINOUT.png)

##Project 2: Acidbot gamma (phases Bluetooth, Line and Obstacle)

Bluetooth or Serial controlled car.

* Complete bluetooth integration.
* Motor control (forward, backward, left, right)
* Lights ON/OFF (front)
* Autonomous mode (Obstacle avoidance with IR sensors)


#####TODO:
1. [X] Obstacle detection w/ 3 IR sensors.
2. [ ] Line tracking w/ 3 line sensors
3. [ ] Create car modes:
  1. [X] Remote mode
  2. [X] Autonomous mode (w/ obstacle detection)
  3. [ ] Autonomous mode (w/ obstacle detection and line tracking)
4. [X] Make a bluetooth command to switch between car modes


####Used:
* [KEYESTUDIO Car Kit (KS0159)](http://www.keyestudio.cc/nd.jsp?id=125&_sc=2)
  1. N20 metal gear motor * 4
  2. High quality tire * 4
  3. Motor holder * 4
  4. Car chassis * 2
  5. L298P motor driver shield * 1
  6. ARDUINO UNO328 board * 1  
  7. ARDUINO sensor shield * 1
  8. Infrared obstacle avoidance module * 3
  9. Line tracking module * 3
  10. HC-06 Bluetooth module * 1
  11. 14500 battery pack * 1
  12. 3PIN Dupont wires * 6
  13. 27MM Copper bush * 4
  14. 10MM Copper bush * 2
  15. 3MM screws and nuts

UNO R3 Pinout:
![Arduino Nano Pinout diagram](http://acidhub.click/imghp/Arduino/UNO-R3_PINOUT.png)
