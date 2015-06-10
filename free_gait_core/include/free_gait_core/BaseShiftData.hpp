/*
 * BaseShiftData.hpp
 *
 *  Created on: Mar 7, 2015
 *      Author: Péter Fankhauser
 *   Institute: ETH Zurich, Autonomous Systems Lab
 */

#pragma once

// STL
#include <string>
#include <iostream>
#include <memory>

// Free Gait
#include "free_gait_core/TypeDefs.hpp"
#include "free_gait_core/BaseShiftTrajectoryBase.hpp"

namespace free_gait {

class BaseShiftData
{
 public:
  BaseShiftData();
  virtual ~BaseShiftData();

  /*!
   * Copy-constructor.
   * @param other the swing data to be copied from.
   */
  BaseShiftData(const BaseShiftData& other);

  const std::string& getName() const;
  void setName(const std::string& name);

  std::shared_ptr<BaseShiftTrajectoryBase> getTrajectory();
  const BaseShiftTrajectoryBase& getTrajectory() const;
  void setTrajectory(const BaseShiftTrajectoryBase& trajectory);

  bool isUsingProfile() const;
  void setUseProfile(bool useProfile);

  friend std::ostream& operator << (std::ostream& out, const BaseShiftData& baseShiftData);

 protected:
  std::string name_;

  std::shared_ptr<BaseShiftTrajectoryBase> trajectory_;

 private:
  bool useProfile_;
};

} /* namespace */
