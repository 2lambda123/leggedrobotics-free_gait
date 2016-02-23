/*
 * BaseShiftTrajectoryBase.hpp
 *
 *  Created on: Mar 10, 2015
 *      Author: Péter Fankhauser
 *   Institute: ETH Zurich, Autonomous Systems Lab
 */

#pragma once

#include <free_gait_core/TypeDefs.hpp>
#include <free_gait_core/executor/State.hpp>
#include <free_gait_core/executor/AdapterBase.hpp>
#include <free_gait_core/step/Step.hpp>
#include <free_gait_core/step/StepQueue.hpp>

#include <string>
#include <memory>

namespace free_gait {

class State;
class AdapterBase;
class Step;
class StepQueue;

/*!
 * Base class for a generic base motions.
 */
class BaseMotionBase
{
 public:

  enum class Type
  {
    Auto,
    Target,
    Trajectory
  };

  /*!
   * Constructor.
   */
  BaseMotionBase(BaseMotionBase::Type type);

  /*!
   * Destructor.
   */
  virtual ~BaseMotionBase();

  virtual std::unique_ptr<BaseMotionBase> clone() const;

  /*!
   * Returns the type of the base motion.
   * @return the type of the base motion.
   */
  BaseMotionBase::Type getType() const;

  virtual const ControlSetup getControlSetup() const;
  virtual const std::string& getControllerType() const;

  /*!
   * Update the trajectory with the base start pose.
   * Do this to avoid jumps of the base.
   * @param startPose the start pose of the base in the frameId_ frame.
   * @return true if successful, false otherwise.
   */
  virtual void updateStartPose(const Pose& startPose);
  virtual void updateStartTwist(const Twist& startTwist);
  virtual void updateStartAcceleration(const Twist& startAcceleration);
  virtual void updateStartForceTorque(const Force& startForce, const Torque& startTorque);

  virtual bool compute(const State& state, const Step& step, const StepQueue& queue, const AdapterBase& adapter);
  virtual bool requiresMultiThreading() const;

  /*!
   * Returns the total duration of the motion.
   * @return the duration.
   */
  virtual double getDuration() const;

  /*!
   * Returns the frame id base motion.
   * @return the frame id.
   */
  virtual const std::string& getPoseFrameId() const;
  virtual const std::string& getTwistFrameId() const;
  virtual const std::string& getAccelerationFrameId() const;
  virtual const std::string& getForceTorqueFrameId() const;

  /*!
   * Evaluate the base motion at a given time.
   * @param time the time value.
   * @return the pose of the base.
   */
  virtual Pose evaluatePose(const double time) const;
  virtual Twist evaluateTwist(const double time) const;
  virtual Twist evaluateAcceleration(const double time) const;
  virtual Force evaluateForce(const double time) const;
  virtual Torque evaluateTorque(const double time) const;

  /*!
   * Print the contents to console for debugging.
   * @param out the output stream.
   * @param baseMotion the base motion to debug.
   * @return the resulting output stream.
   */
  friend std::ostream& operator<< (std::ostream& out, const BaseMotionBase& baseMotion);

 private:

  //! Type of the base motion.
  Type type_;
};

std::ostream& operator<<(std::ostream& out, const BaseMotionBase::Type& type);

} /* namespace */
