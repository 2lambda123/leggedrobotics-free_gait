cmake_minimum_required(VERSION 2.8.3)
project(free_gait_core)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  loco
  curves
  grid_map_core
)

## System dependencies are found with CMake's conventions
find_package(Eigen3 REQUIRED)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
    INCLUDE_DIRS
      include
    LIBRARIES
      ${PROJECT_NAME}
    CATKIN_DEPENDS
      loco
      curves
      grid_map_core
    DEPENDS
      Eigen3
)

# Attempt to find catkinized kindr
find_package(kindr QUIET)
if(NOT kindr_FOUND)
  # Attempt to find package-based kindr
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(kindr kindr REQUIRED)
endif()

###########
## Build ##
###########

## Specify additional locations of header files
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
)

## Declare a cpp library
add_library(${PROJECT_NAME}
   src/BaseShiftData.cpp
   src/BaseShiftProfile.cpp
   src/BaseShiftSplineTrajectory.cpp
   src/BaseShiftTrajectoryBase.cpp
   src/Step.cpp
   src/StepCompleter.cpp
   src/StepQueue.cpp
   src/SwingData.cpp
   src/SwingProfile.cpp
   src/SwingSplineTrajectory.cpp
   src/SwingTrajectoryBase.cpp
   src/PoseOptimization.cpp
)

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

# This is required because loco's test don't work.
add_library(free_gait_to_test
  src/PoseOptimization.cpp
)

target_link_libraries(free_gait_to_test
  ${catkin_LIBRARIES}
)

#############
## Testing ##
#############

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
## Add gtest based cpp test target and link libraries
#catkin_add_gtest(${PROJECT_NAME}-test
#  test/test_free_gait_core.cpp
  #test/PoseOptimizationTest.cpp
#)
#if(TARGET ${PROJECT_NAME}-test)
#  target_link_libraries(${PROJECT_NAME}-test
#    ${PROJECT_NAME}
#  )
#endif()

# This is required because loco's test don't work.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
## Add gtest based cpp test target and link libraries
catkin_add_gtest(${PROJECT_NAME}-test
  test/test_free_gait_core.cpp
  test/PoseOptimizationTest.cpp
)
if(TARGET ${PROJECT_NAME}-test)
  target_link_libraries(${PROJECT_NAME}-test
    free_gait_to_test
  )
endif()