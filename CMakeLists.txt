cmake_minimum_required(VERSION 3.0.2)
project(dynamic_test)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
        dynamic_reconfigure
        roscpp
        rospy
        )

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

generate_dynamic_reconfigure_options(
        cfg/Example.cfg
        cfg/ExampleBroken.cfg
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
        #  INCLUDE_DIRS include
        LIBRARIES dynamic_test
        CATKIN_DEPENDS dynamic_reconfigure roscpp rospy
        DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(
        # include
        ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node src/node.cpp)
target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES})
add_dependencies(${PROJECT_NAME}_node ${PROJECT_NAME}_gencfg)

add_executable(${PROJECT_NAME}_broken_node src/nodeBroken.cpp)
target_link_libraries(${PROJECT_NAME}_broken_node ${catkin_LIBRARIES})
add_dependencies(${PROJECT_NAME}_broken_node ${PROJECT_NAME}_gencfg)

###########
## Tests ##
###########


catkin_add_gtest( ${PROJECT_NAME}_serialisation_test test/testParameterDescrptionSerialisation.cpp )
target_link_libraries(${PROJECT_NAME}_serialisation_test ${catkin_LIBRARIES})
add_dependencies(${PROJECT_NAME}_serialisation_test ${PROJECT_NAME}_gencfg)