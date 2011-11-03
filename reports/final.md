# Final Report

### D. Findrik (0808798), J. Hampl (0802690), L. Kamburov (0838290)


Abstract: TBD

# Introduction

### Task Description

The goal of this project was to build a robot that was supposed to move around a lab environment searching for "resource sites". Resource sites were represented as black cardboard parallelograms taped to the floor. Two sides of the resource site had walls XXX centimetres high with a slight gap where they would meet. Here a switch was attached to a light diode that emitted a light pulsing at a specified frequency.

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

One of our first design decisions was to try to create a purely reactive control architecture to solve the task assigned to us. This was partially successful in the sense that we managed to have the robot navigate around in this manner, without the need to use planning or active sensing. 

Our control algorithm is layered where bottom layers effect how the bottom layers react to sensory input. However each of these layers are directly dependent on sensory input (there is a bit of state retained in the robot, however there is so little that calling it a model would be exaggerated). 

A top level priority is finding out whether the robot is stuck somewhere. If not (or this hasn't been detected yet, see bellow for details), then we use light sensors on the bottom of the robot to detect dark flooring. When on the dark floor all movements tend to be smaller and less pronounced. Also the reaction to the whisker sensors becomes smaller to have a more wall hugging behaviour.

The lowest level are reactions to the whisker sensors and the front IR sensors. The remaining sensors are checked for values only when the other sensors mandate a possibility of them being useful.

### Strategies

Since creating reactive robots is all about using simple reactions to orchestrate more complex behaviours. 

#### Wall hugging

Inspired by Schank et al. (2006) we have used the two whisker sensors to avoid hitting a wall but intend the robot will back up a little in the direction that the whisker was triggered and then continue driving forwards presumably to hit the wall a couple of centimetres onwards. With this property we have tried to exploit two important properties of the environment. Our robots will have a high probability of ending up in corners (as discussed in Schank et al.; although they generate this behaviour by virtue of the robot's shape only, we considered that approach impractical with LEGO robots) and corners are where all of the light switches are. The second important property was that in a large number TBD of cases walls of the resource sites aim at walls of other resource sites. So when the robot follows such a wall when the wall ends it will continue straight and hit the wall in the next resource site and then it will follow that wall all the way to the switch.





---

# Results

# Disscusion

# References

1. Schank, J., Joshi, S., Tran, J., Taylor, R., May, C. J., & Scott, I.-E. (2006). Rat pups and random robots generate similar self‐organized and intentional behavior. *Complexity*.