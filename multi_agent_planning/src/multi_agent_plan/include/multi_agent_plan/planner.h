/* planner.h
 * Andres Torres Garcia (andrestoga@gmail.com)
 */
#ifndef PLANNER_H
#define PLANNER_H

#include "geometry_msgs/Pose2D.h"
#include "multi_agent_plan/GetPlan.h"
#include "multi_agent_plan/CurrPose.h"
#include "ros/ros.h"
#include "map.h"

namespace multi_agent_plan
{
	/**
	 * @brief      Pose in 2D
	 */
	struct Coord2D
	{
		float x_;
		float y_;
		float theta_;

		/**
		 * @brief      Constructor
		 *
		 * @param[in]  x      x coordinate
		 * @param[in]  y      y coordinate
		 * @param[in]  theta  theta angle
		 */
		Coord2D( float x, float y, float theta )
		: x_(x)
		, y_(y)
		, theta_(theta)
		{

		}
	};

	class Planner
	{
		bool is_curr_pose_ready_;
	    geometry_msgs::Pose2D start_pose_;
	    // std::map<geometry_msgs::Pose2D, std::map<geometry_msgs::Pose2D, std::vector<geometry_msgs::Pose2D>>> saved_paths_;
	    std::map<Coord2D, std::map<Coord2D, std::vector<geometry_msgs::Pose2D>>> saved_paths_;// Map used to store 

	    /**
	     * @brief      Calculates the path.
	     *
	     * @param      req   The request: serial id and the goal pose
	     * @param      res   The response: the path
	     *
	     * @return     Return true
	     */
	    bool computePath(multi_agent_plan::GetPlan::Request  &req,
         multi_agent_plan::GetPlan::Response &res);
	    /**
	     * @brief      Gets the agent pose.
	     *
	     * @param[in]  msg   The message containing the agent pose
	     */
	    void getAgentPose(const multi_agent_plan::CurrPose::ConstPtr& msg);
	    /**
	     * @brief      Plan for manhattan worlds with no obstacles. By using this algorithm all the paths will have L or | shape depending on the x and y coordinates.
	     *
	     * @param[in]  goal  The goal
	     *
	     * @return     the series of poses to move to reach the goal
	     */
	    std::vector<geometry_msgs::Pose2D> manhattanPlanning( geometry_msgs::Pose2D goal );


		// Access specifier 
		public:

	    // Data Members
	    Map grid_;

		ros::ServiceServer plan_service_;
		ros::Subscriber curr_pose_sub_;
		ros::NodeHandle nh_;
	  
	  	/**
	  	 * @brief      Constructs the object.
	  	 *
	  	 * @param[in]  nh    node handle
	  	 * @param[in]  grid  The grid
	  	 */
	    Planner(const ros::NodeHandle& nh, const Map& grid);

	};
}

#endif