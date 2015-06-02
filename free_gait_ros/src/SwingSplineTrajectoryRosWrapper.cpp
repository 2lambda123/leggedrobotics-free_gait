/*
 * SwingSplineTrajectoryRosWrapper.cpp
 *
 *  Created on: Mar 6, 2015
 *      Author: Péter Fankhauser
 *   Institute: ETH Zurich, Autonomous Systems Lab
 */

#include <free_gait_ros/SwingSplineTrajectoryRosWrapper.hpp>
#include <ros/ros.h>

// STD
#include <string>

namespace free_gait {

SwingSplineTrajectoryRosWrapper::SwingSplineTrajectoryRosWrapper() :
    SwingSplineTrajectory(),
    curves::RosMultiDOFJointTrajectoryTranslationInterface()
{

}

SwingSplineTrajectoryRosWrapper::~SwingSplineTrajectoryRosWrapper()
{

}

bool SwingSplineTrajectoryRosWrapper::fromMessage(
    const trajectory_msgs::MultiDOFJointTrajectory& message, const std::string& jointName)
{
  setFrameId(message.header.frame_id);
  curves::RosMultiDOFJointTrajectoryTranslationInterface trajectory;
  if (!trajectory.fromMessage(message, jointName)) return false;
  trajectory_ = trajectory;
  return true;
}

} /* namespace */
