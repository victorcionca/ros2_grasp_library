// Copyright (c) 2019 Intel Corporation. All Rights Reserved
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef GRASP_LIBRARY__ROS2__GRASP_DETECTOR_BASE_HPP_
#define GRASP_LIBRARY__ROS2__GRASP_DETECTOR_BASE_HPP_

#include <grasp_msgs/msg/grasp_config_list.hpp>
#include <string>
#include "tf2/LinearMath/Vector3.h"
#include "gpd/grasp_detector.h"

namespace grasp_ros2
{

/** GraspCallback class
 *
 * \brief Abstract base class for grasp callback.
 *
 * A grasp planner inherits from this class get called back for grasp detection resutls.
 */
class GraspCallback
{
public:
  /**
   * \brief Callback for grasp detection results.
   *
   * \param msg Pointer to grasp detection results.
   */
  virtual void grasp_callback(const grasp_msgs::msg::GraspConfigList::SharedPtr msg) = 0;
};

/** GraspDetectorBase class
 *
 * \brief A base class for detecting grasp poses from visual input.
 *
 * This class defines uniform interface for grasp library, regardless whichever algorithm
 * is used for grasp detection.
 */
class GraspDetectorBase
{
  public:

  /**
   * \brief Constructor.
   */
  GraspDetectorBase()
  : object_name_(""), grasp_cb_(nullptr)
  {
  }

  /**
   * \brief Destructor.
   */
  ~GraspDetectorBase()
  {
  }

  /**
   * \brief Start grasp detection.
   * When this function is called, GraspDetector starts processing visual input.
   * \param name Name of the object for which to detect grasps
   */
  void start(std::string name = "")
  {
    started_ = true;
    object_name_ = name;
  }

  /**
   * \brief Stop grasp detection.
   * When this function is called, GraspDetector stops processing visual input.
   */
  void stop()
  {
    started_ = false;
  }

  /**
   * \brief Register grasp callback function.
   *
   * \param cb Callback function to be registered.
   */
  void add_callback(GraspCallback * cb)
  {
    grasp_cb_ = cb;
  }

protected:
  bool started_ = false;
  std::string object_name_;
  GraspCallback * grasp_cb_;
};

}  // namespace grasp_ros2

#endif  // GRASP_LIBRARY__ROS2__GRASP_DETECTOR_BASE_HPP_
