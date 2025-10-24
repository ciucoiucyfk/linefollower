Readme for line follower robot :- 

The attached arduino .ino file contains the necessary arduino c++ code for a line follower bot that uses the L293D motor driver to drive two hobby gear motors. The bot takes input in the form of an array of either 1 or 0 , this input is taken directly from the 5 sensor array placed in the front of the bot and allows it to effectively navigate the line course.

The input from the sensor array allows the bot to get a guage on how deviated its center is from the direction of the line.
[0 0 1 0 0] :- Center > Action :- go Straight
[0 0 0 1 0] :- Slightly Right > Action :- Turn right 
[0 1 0 0 0] :- Slightly Left > Action :- Turn right 
[1 0 0 0 0] :- Extreme Left > Action  :- Turn hard left
[0 0 0 0 1] :- Extreme Right > Action :- Turn hard right

To control the hardness of the turn we use differential steering.

The bot always runs both wheels at a certain base speed and then differentially adjusts the rate of either wheel using a correction constant to cause the bot to turn in that direction at that rate.

We also use a PID controller to setup the harshness of the turn by taking readings of errors and change in error and then calculating PID correction value subsequently

We use potentiometers with a voltage divider setup to set Kp , Ki and Kd values for the PID controller.
