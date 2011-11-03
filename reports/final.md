# Final Report

### D. Findrik (0808798), J. Hampl (0802690), L. Kamburov (0838290)


Abstract: TBD

# Introduction

### Task Description

The goal of this project was to build a robot that was supposed to move around a lab environment searching for "resource sites". Resource sites were represented as black cardboard parallelograms taped to the floor. Two sides of the resource site had walls XXX centimetres high with a slight gap where they would meet. Here a switch was attached to a light diode that emitted a light pulsing at a specified frequency.

![picture of resource site]

The robot had five minutes to find as many as possible of these resource sites. When a resource site was found the robot was expected to trigger the switch and measure the frequency that was emitted by the light switch.

---


###Structure of the robot###

##Design##
Evolution of the robot:
#Version1#
#Version2#
#Version3#
fail
#Version4#
TODO write about design

## Sensors

### Front-Facing IR

The primary task that our robot had to achieve in order to succeed in subsequent objectives was obstacle avoidance. The easiest and primary solution to this problem was given by the front-facing infrared sensor on our robot. This sensor measures the closeness of the objects in front of it and returns an integer. It should give the greatest value when the object is touching the sensor, however, due to the implementation of the sensor, the highest value is obtained when the obstacle in front of the robot is approximately 10 cms away (need to measure this and show a nice diagram of the change of the values with the threshold shown). The robot is programmed to obtain readings from the sensors continuously and retreats when the value from the sensor rises above a certain threshold, which represents a slightly greater distance than the length of the whiskers. In this case, the robot drives back and turns to avoid the obstacle.

### Whiskers

We have attached two whiskers to the robot that are pointing forwards and outwards from the robot - one on the left and one on the right. These sensors are triggered when the whisker touches the ring that surrounds it at its base and returns the value 1, otherwise 0 (see figure x). The purpose of the using the whisker sensors is to avoid obstacles that are invisible to the front-facing IR sensor and making sure that the robot does not attempt to enter a gap that is thinner than itself and this use of them was inspired by cats' whiskers which serve the same purpose. The whiskers are x cms long and sticking out x cms to the side. The robot's reactive behavior to the whiskers being triggered is shown in figure x (insert the picture of that behavior here). The problem with the whiskers is, however, that the input we obtain is noisy due to the oscillation of the whiskers. In our implementation we overlook this fact as the oscillation usually settles down by the time the reactive behavior is executed.
Both the front-facing IR sensor and the whiskers have been part of our robot since the first version.

#Bottom light sensors#


#Top light sensors#

#Hall sensor#

#Top IR#


## Robotic control

One of our first design decisions was to try to create a purely reactive control architecture to solve the task assigned to us. This was partially successful in the sense that 

##General structure##

##Functions##
#Stuck detection#


###Objectives###
## Week 1 ##
##Week 2##
##Week 3## etc

###Testing###