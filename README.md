# Tempcheckbot Project
> Autonomous land robot for temperature reading
>> Built in Simulation with the TurtleBot3 model using ROS and IGN.


| Simulation Specs: ||
| ----------------- |:-------------|
| Platform          | ROS        |
| Platform Version  | ROS Noetic |
| Simulators        | ROS Gazebo, Ignition Gazebo |
| Simulator Version | For IGN Gazebo: Citadel |
| Robot Model       | TurtleBot3 Burger |
| Package Name      | tempcheckbot |
| Visualizer        | RViz |
---
## Running the Simulation
Copy the project to your catkin_ws/src workspace

Run `$ catkin build`

Then run `$ roslaunch tempcheckbot tempcheckbot_world.launch ` to launch the Gazebo world

After that, run `$ roslaunch tempcheckbot tempcheckbot.launch` to fire up the project

You can also run move into the `/ign_gazebo_version` folder and run `$ ign gazebo turtlebot3_empty_world_ign` to use the thermal camera on the turtlebot3 model