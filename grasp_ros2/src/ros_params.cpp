// Copyright (c) 2018 Intel Corporation. All Rights Reserved
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

#include <string>
#include <vector>

#include "grasp_library/ros2/ros_params.hpp"

namespace grasp_ros2
{

void ROSParameters::getDetectionParams(
  rclcpp::Node * node,
  gpd::GraspDetector::GraspDetectionParameters & param)
{
  // Read hand geometry parameters.
  node->get_parameter_or("finger_width", param.hand_search_params.hand_geometry_.finger_width_, 0.005);
  node->get_parameter_or("hand_outer_diameter", param.hand_search_params.hand_geometry_.outer_diameter_,
    0.12);
  node->get_parameter_or("hand_depth", param.hand_search_params.hand_geometry_.depth_, 0.06);
  node->get_parameter_or("hand_height", param.hand_search_params.hand_geometry_.height_, 0.02);
  node->get_parameter_or("init_bite", param.hand_search_params.hand_geometry_.init_bite_, 0.01);

  // Read local hand search parameters.
  node->get_parameter_or("nn_radius", param.hand_search_params.nn_radius_frames_, 0.01);
  node->get_parameter_or("num_orientations", param.hand_search_params.num_orientations_, 8);
  node->get_parameter_or("num_samples", param.generator_params.num_samples_, 100);
  node->get_parameter_or("num_threads", param.hand_search_params.num_threads_, 4);
  // TODO
  node->get_parameter_or("rotation_axis", param.rotation_axis_, 2);

  // Read plotting parameters.
  node->get_parameter_or("plot_samples", param.plot_params.plot_samples_, false);
  node->get_parameter_or("plot_normals", param.plot_params.plot_normals_, false);
  //param.generator_params_params.plot_normals_ = param.plot_normals_;
  node->get_parameter_or("plot_filtered_grasps", param.plot_params.plot_filtered_grasps_, false);
  node->get_parameter_or("plot_valid_grasps", param.plot_params.plot_valid_grasps_, false);
  node->get_parameter_or("plot_clusters", param.plot_params.plot_clusters_, false);
  node->get_parameter_or("plot_selected_grasps", param.plot_params.plot_selected_grasps_, false);

  // Read preprocessing parameters.
  node->get_parameter_or("remove_outliers", param.generator_params.remove_statistical_outliers_,
    false);
  node->get_parameter_or("voxelize", param.generator_params.voxelize_, true);
  node->get_parameter_or("workspace", param.generator_params.workspace_,
    std::vector<double>(std::initializer_list<double>({-1.0, 1.0, -1.0, 1.0, -1.0, 1.0})));
  param.workspace_grasps_ = param.generator_params.workspace_;

  // Read classification parameters and create classifier.
  node->get_parameter_or("model_file", param.model_file_, std::string(""));
  node->get_parameter_or("trained_file", param.weights_file_, std::string(""));
  node->get_parameter_or("min_score_diff", param.min_score_diff_, 500.0);
  node->get_parameter_or("create_image_batches", param.create_image_batches_, false);
  node->get_parameter_or("device", param.device_, 0);

  // Read grasp image parameters.
  // node->get_parameter_or("image_outer_diameter", param.hand_search_params.hand_geometry.outer_diameter_,
  //   param.hand_search_params_params.hand_outer_diameter_);
  // node->get_parameter_or("image_depth", param.image_params.depth_,
  //   param.hand_search_params_params.hand_depth_);
  // node->get_parameter_or("image_height", param.image_params.height_,
  //   param.hand_search_params_params.hand_height_);
  // TODO
  node->get_parameter_or("image_size", param.image_params.size_, 60);
  node->get_parameter_or("image_num_channels", param.image_params.num_channels_, 15);

  // Read learning parameters.
  node->get_parameter_or("remove_plane_before_image_calculation", param.plot_params.remove_plane_, false);

  // Read grasp filtering parameters
  node->get_parameter_or("filter_grasps", param.filter_grasps_, false);
  node->get_parameter_or("filter_half_antipodal", param.filter_half_antipodal_, false);
  param.gripper_width_range_.push_back(0.03);
  param.gripper_width_range_.push_back(0.10);
  // node->get_parameter("gripper_width_range", param.gripper_width_range_);

  // Read clustering parameters
  node->get_parameter_or("min_inliers", param.min_inliers_, 1);

  // Read grasp selection parameters
  node->get_parameter_or("num_selected", param.num_selected_, 5);
}

void ROSParameters::getPlanningParams(
  rclcpp::Node * node,
  GraspPlanner::GraspPlanningParameters & param)
{
  node->get_parameter_or("grasp_service_timeout", param.grasp_service_timeout_, 0);
  node->get_parameter_or("grasp_score_threshold", param.grasp_score_threshold_, 200);
  node->get_parameter_or("grasp_frame_id", param.grasp_frame_id_, std::string("base"));
  std::vector<double> approach;
  node->get_parameter_or("grasp_approach", approach,
    std::vector<double>(std::initializer_list<double>({0.0, 0.0, -1.0})));
  param.grasp_approach_ = tf2::Vector3(approach[0], approach[1], approach[2]);
  node->get_parameter_or("grasp_approach_angle", param.grasp_approach_angle_, M_PI);
  node->get_parameter_or("grasp_offset", param.grasp_offset_,
    std::vector<double>(std::initializer_list<double>({0.0, 0.0, 0.0})));
  node->get_parameter_or("grasp_boundry", param.grasp_boundry_,
    std::vector<double>(std::initializer_list<double>({-1.0, 1.0, -1.0, 1.0, -1.0, 1.0})));
  node->get_parameter_or("eef_offset", param.eef_offset, 0.154);
  node->get_parameter_or("eef_yaw_offset", param.eef_yaw_offset, 0.0);
  node->get_parameter_or("grasp_min_distance", param.grasp_min_distance_, 0.06);
  node->get_parameter_or("grasp_desired_distance", param.grasp_desired_distance_, 0.1);

  // gripper parameters
  std::vector<double> finger_opens, finger_closes;
  node->get_parameter_or("finger_joint_names", param.finger_joint_names_,
    std::vector<std::string>(std::initializer_list<std::string>({std::string("panda_finger_joint1"),
      std::string("panda_finger_joint2")})));
  node->get_parameter_or("finger_positions_open", param.finger_points_open_.positions,
    std::vector<double>(std::initializer_list<double>({-0.01, 0.01})));
  node->get_parameter_or("finger_positions_close", param.finger_points_close_.positions,
    std::vector<double>(std::initializer_list<double>({-0.0, 0.0})));
}

}  // namespace grasp_ros2
