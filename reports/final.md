# Final Report

### D. Findrik (0808798), J. Hampl (0802690), L. Kamburov (0838290)


Abstract: TBD

# Introduction

### Task Description

The goal of this project was to build a robot that was supposed to move around in a lab environment searching for "resource sites". Resource sites were represented as black cardboard parallelograms taped to the floor. Two sides of the resource site had walls XXX centimetres high with a slight gap where they would meet. Here a switch was attached to a light diode that emitted a light pulsing at a specified frequency.

![picture of resource site]

The robot had five minutes to find as many as possible of these resource sites. When a resource site was found the robot was expected to trigger the switch and measure the frequency that was emitted by the light switch. Then one of the following victory dances should have been made based on the frequency of the light switch:

Frequency | Movement
----------|---------
0.5Hz     | Backwards, 360&deg; turn left
1Hz       | Backwards, 360&deg; turn right
2Hz       | Backwards, stop, backwards
4Hz       | Backwards, 180&deg; turn left
6Hz       | Backwards, 180&deg; turn right
8Hz       | Backwards, stop, forwards



---


# Method

## Hardware specification
Main Components of the robot :
          Hardware specification: 
          The main components of the robots are: 
				- Fit pc 
				- PowerBoard 
				- Interface Board(PhidgetInterfaceKit 8 digital outputs, 8 digital inputs and 8 analog input).
				- Sensors.
				- Standart lego kit
				- 2 x DC Motors and a Servo Motor
				- Cables - usb, digital and analog cabels.
	
	How to build such a robot: Design part probably.
	We have three main deattachable parts of our robot. The first part 
is the main frame. This is the part where batery, Dc motors and wheels are. 
We diceded to use chains for our robot.WHY ??? 
The second component is the where the middle frame is. 
It consists of interface board and power board. The last part is the front 
wheel - the servo motor. We are using the servo motors to the front so the robot could perform smoother turns.
Wheel spin measurement 12 cm.  
##Design##
Evolution of the robot:

## Measurements:

Greatest width | 23.5cm
---|---
Total length | 39cm
Length of whiskers | 14.5cm
Whiskers sticking out | 2cm
Height of front-facing IR | 5.9cm
end of whiskers are | 6.5cm away from front-facing IR
Height of Top light sensors |15.4cm
Top Light sensors are  | 5.1cm away from each other
Height of Top IR | 22cm (also the height of the robot)
whiskers are | 2.5cm away  
Wheelbase | 8.9cm
Rear wheels' axises are | 8cm away from the back
Distance between bottom light sensors | 8.4cm

TODO write about design

## Sensors

### Front-Facing IR

The primary task that our robot had to achieve in order to succeed in subsequent objectives was obstacle avoidance. The easiest and primary solution to this problem was given by the front-facing infrared sensor on our robot. This sensor measures the closeness of the objects in front of it and returns an integer. It should give the greatest value when the object is touching the sensor, however, due to the implementation of the sensor, the highest value is obtained when the obstacle in front of the robot is approximately 8 cms away. To have a greater understanding about the values returned by the sensor, we have carried out a test and measured the values obtained from the sensor between 0 and 17 centimeters with 0.5 cm increments and the result is shown in Figure x. The robot is programmed to obtain readings from the sensors continuously and retreats when the value from the sensor rises above a certain threshold, which represents a slightly greater distance than the length of the whiskers. In this case, the robot drives back and turns to avoid the obstacle.

### Whiskers

We have attached two whiskers to the robot that are pointing forwards and outwards from the robot - one on the left and one on the right. These sensors are triggered when the whisker touches the ring that surrounds it at its base and returns the value 1, otherwise 0 (see figure x). The purpose of the using the whisker sensors is to avoid obstacles that are invisible to the front-facing IR sensor and making sure that the robot does not attempt to enter a gap that is thinner than itself and this use of them was inspired by cats' whiskers which serve the same purpose. The whiskers are x cms long and sticking out x cms to the side. The robot's reactive behavior to the whiskers being triggered is shown in figure x (insert the picture of that behavior here). The problem with the whiskers is, however, that the input we obtain is noisy due to the oscillation of the whiskers. In our implementation we overlook this fact as the oscillation usually settles down by the time the reactive behavior is executed.
Both the front-facing IR sensor and the whiskers have been part of our robot since the first version.

### Bottom light sensors
For the task in Week 4, our robot had to distinguish dark floor from light floor, hence we needed sensors that give information about the floor to our system. Therefore we installed two light sensors to the bottom of the robot which measure the brightness of the object . To minimise the effect of the changes in light conditions, we have attached a lightbulb to the bottom of the robot between the two sensors. This provides a consistent source of light and minimises the variance between brightness values obtained from dark and light floor. We use thresholding based on the average of the first values obtained from the left and right sensors after starting our program, assuming our robot starts on light floor. We also use the position of the sensors to navigate into resource sites. (image of the bottom of the robot) // also add measurements: how far are the light sensors from each other and from the light

### Top light sensors
For Week 5 our robot had to recognise the frequencies with which the lights above the switches were flashing. In order to be able to do that, we have installed two light sensors to the front of the robot at the same height as the flashing LEDs are. These sensors are at the two sides of the robot and we take an average (?? have to check this) of the values to use for frequency detection (more about this in Functions/Frequency detection). The reasoning behind the placement of these sensors is that our robot might not be perfectly in front of the light when it triggers the switch, however, this way we can ensure that either of the sensors will reach the threshold required to determine the frequency. (picture of the front of the robot)

### Hall sensor
The Hall sensor can detect whether the wheels are moving by changing the output whenever the bar inside it makes a full turn. We use this sensor to identify the case when our robot is stuck even though none of the other sensors indicate that as they are not triggered. It can also be used to detect obstacles behind the robot by believing that the robot got stuck whilst driving backwards. The Hall sensor is attached to the top of the rear left wheel and is connected via a track to the axis of the wheel (see image). The reasoning behind placing it there is that whenever the robot is stuck the wheels stop moving (even powered wheels) and it was easier to install them then to place them on the front wheel.

### Top IR
We have attached an IR sensor, facing approximately 45˚ upwards, to the front of the robot to detect the gap at the resource site between the walls and help in guidance to the switch (see image of gap and IR sensor). This idea was implemented after seeing it working successfully on the robot of group A5. (all the others told us that we better mention them...)


## Robotic control

One of our first design decisions was to try to create a purely reactive control architecture to solve the task assigned to us. This was partially successful in the sense that we managed to have the robot navigate around in this manner, without the need to use planning or active sensing. 

Our control algorithm is layered where bottom layers effect how the bottom layers react to sensory input. However each of these layers are directly dependent on sensory input (there is a bit of state retained in the robot, however there is so little that calling it a model would be exaggerated). 

A top level priority is finding out whether the robot is stuck somewhere. If not (or this hasn't been detected yet, see bellow for details), then we use light sensors on the bottom of the robot to detect dark flooring. When on the dark floor all movements tend to be smaller and less pronounced. Also the reaction to the whisker sensors becomes smaller to have a more wall hugging behaviour.

The lowest level are reactions to the whisker sensors and the front IR sensors. The remaining sensors are checked for values only when the other sensors mandate a possibility of them being useful.

### Strategies

Since creating reactive robots is all about using simple reactions to orchestrate more complex behaviours. 

#### Wall hugging

Inspired by Schank et al. (2006) we have used the two whisker sensors to avoid hitting a wall but intend the robot will back up a little in the direction that the whisker was triggered and then continue driving forwards presumably to hit the wall a couple of centimetres onwards. With this property we have tried to exploit two important properties of the environment. Our robots will have a high probability of ending up in corners (as discussed in Schank et al.; although they generate this behaviour by virtue of the robot's shape only, we considered that approach impractical with LEGO robots) and corners are where all of the light switches are. The second important property was that 6 out of the 10 walls of the resource sites aim at walls of other resource sites. So when the robot follows such a wall when the wall ends it will continue straight and hit the wall in the next resource site and then it will follow that wall all the way to the switch. The 8Hz resource site had the nice property that both of its walls led to another resource site, and this was in fact often exploited by the robot.

### Stuck Detection
In order to ensure that our robot does not get stuck for an extended period of time, we have installed the Hall sensor to recognise when the wheels are stationary. The input from the sensor changes parity when the magnet on the bar passes the sensor, i.e. makes a full turn. We exploit this behavior along with the fact that our main function, which defines every movement, is called every 50ms to determine the state "being stuck". The simplest approach was to count the number of loops when the input from the sensor has not changed. A single cycle of "being stuck" is defined by seven iterations of the main code called without change in the input. The robot considers itself being stuck after the third such cycle. If at any time the input changes, both the number of cycles and iterations are reset to zero. After the robot has realised that it is stuck, it makes the opposite movement that it was making previously, i.e. either go forward or back. This is done by storing the intended orientation when the robot starts to move in a given direction.

### Frequency recognition
TODO explain frequency recognition
We have carried out several tests to define the efficiency of the algorithm. In these experiments the robot was aligned facing the switch, the program was started and we let the robot find the switch, trigger it and readings of frequencies were recorded. For all lights that were available in the laboratory, we have measured the frequencies ten times and the result is shown by Figure x. We can see that the algorithm performs constantly well for lower frequencies with a standard deviation and mean of 0.0024 and 0.9835 for frequency 1 and 0.0097 and 1.9562 for frequency 2. For higher frequencies, the standard deviation has increased and thus we obtained 0.1208 with a mean of 3.9843 for frequency 4, 0.0862 with 5.9253 mean for frequency 6 and 0.1141 with 7.8632 mean for frequency 8. Even though the precision of the obtained values decreased as the frequencies became higher, the 0.3Hz wide area around the frequencies guarantee that the correct frequency is recognised.

## Experimental Design

Our main concern was the performance of the robot on its main task. We tested this in eight repeated 5 minute trials. We measured how many resource sites would the robot  reach, how many light switches would it manage to trigger and how many victory dances it performed correctly. The robot was always placed in the centre of the arena with a constant starting orientation facing one of the switches. The experimenters did not interfere with the operation of the robot.



---

# Results

### Main performance results

Run | Black areas reached | Lights triggered | Dances performed
----|---------------------|------------------|------------------
#1  | 3                   |                3 |                2
#2  | 2                   |                1 |                1
#3  | 1                   |                1 |                1
#4  | 4                   |                2 |                2
#5  | 2                   |                2 |                2
#6  | 3                   |                3 |                2
#7  | 1                   |                1 |                1
#8  | 3                   |                1 |                1
Mean |        2.625       |            1.625 |               1.5 
Standard Deviation |  0.916 |       0.744    | 0.535

### Corner oscillation 

An interesting side effect of our various behaviours interacting was when the robot got to a corner in the lab it tended to oscillate between driving out in one direction or the other. This is caused by the fact that the robot is basically designed to reach centres of corners (where we presume the light switches are). The robot didn't get stuck in the oscillatory pattern for ever, due to subtle differences in turning on both sides (caused by one wheel having additional friction caused by the Hall sensor) it would eventually manage to get out.

# Discussion

We started to build this robot with the aim of it being able to explore the arena, finding the resource sites and after triggering the light and recognising the frequency at which it flashes, making the correct movement. Our aim was also to implement this behavior in a robot that is robust enough to withstand small collisions and no parts would fall off it. As we have described in this report, we achieved a robust structure through centering most of the weight on the rear wheels and using several cross-bracing across the robot. However, the front wheel remained a weaker part of the robot due to the issues of attaching the front wheel adequately to the servo motor. To complete its weekly tasks, we have installed several sensors that proved to be useful in our reactive approach for the robot's behavior. As the experiments have shown, we expected our robot to perform one or two dances in the final competition due to the lack of a simple yet sophisticated search algorithm that could have helped our robot in finding resource sites. For this approach we could have used, for example, random search or spiral-like movement, however, we tried to keep our code and behavior as simple as possible. Another approach that we considered was the use of a sonar sensor to create a basic map of the arena, however, this approach was discarded after a small number of experiments with the sonar that showed that the values we obtain are non-linear and the relation to distance was not obvious. 

# Read this!!
Pictures of the robot https://picasaweb.google.com/107734719485006917029/ScrapbookPhotos?authuser=0&feat=directlink uploaded here. Will upload text later on.

# References

1. Schank, J., Joshi, S., Tran, J., Taylor, R., May, C. J., & Scott, I.-E. (2006). Rat pups and random robots generate similar self‐organized and intentional behavior. *Complexity*.

# Source code

The source code can be found at http://github.com/gampleman/Robot-IAR.