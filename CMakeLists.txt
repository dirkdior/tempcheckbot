cmake_minimum_required(VERSION 3.0.2)
project(tempcheckbot)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  turtlebot3_navigation
)

catkin_package(
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(talker_node src/moveturtlebot.cpp)
target_link_libraries(talker_node ${catkin_LIBRARIES})
add_dependencies(talker_node ${catkin_EXPORTED_TARGETS})