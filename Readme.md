# ColonD CarRace

ColonD CarRace is a simple Top-Down Race simulation written in C++. [Box2D](http://box2d.org/) is used as the physics engine in this project which enables us to handle collisions and get the ray tracing feature used in the sensors on the car.

The main aim of this project is to drive in a race track autonomously. This game assumes that there are no noise in the sensory data and the car drives forward with constant velocity. The actions that can be done by the driver is to Steer Left, Steer Right or Drive Straight. Each simulated sensor also has a maximum range which is 8 units in this version of the project.

# Different Drivers

So far, the following drivers have been implemented in this project
 - SimpleDriver: This is just a simple minded driver which sums up the two left sensory data with the two right sensory data and tries to keep the ballance between these two summations by moving to the side with bigger summation.
 - ANNDriver: An Artificial Neural Network is trained using FANN 2 library and is used as an offline controller which accepts the sensor data values and generates an output based on them. This generates output is used to drive the car. The training data for this Network is obtained just by driving the car once in manually and collecing the sensor data values and the steering angle at each epoch.
 - QDriver (To be implemented soon): This is supposed to use Q-Learning algorithm to learn how to drive in the track. This will be implemented in the near future.

# Demo
You can see a demo of the Artificial Network Trained to drive the car from the following YouTube Video:

[![YouTube Video](http://img.youtube.com/vi/xTCJWMBy5rA/0.jpg)](https://www.youtube.com/watch?v=xTCJWMBy5rA)