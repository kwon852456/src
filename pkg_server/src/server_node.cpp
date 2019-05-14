#include "ros/ros.h"
#include "pkg_server/stt.h"
#include "pkg_server/cmd.h"

bool response(pkg_server::cmd::Request &req, pkg_server::cmd::Response &res){

	res.res = 100;

	ROS_INFO("request: x = %1d"     , req.req);
	ROS_INFO("response: res = %1d"  , res.res);

	return true;

}




int main(int argc,char** argv){

	ros::init(argc, argv, "stt_publisher");
	ros::NodeHandle nh;

	ros::Publisher sttPub        = nh.advertise<pkg_server::stt>("stt", 100);
	ros::ServiceServer cmdServer = nh.advertiseService("cmd",response);

	ROS_INFO("cmd server is ready!");

	ros::Rate loop_rate(10);

	pkg_server::stt stt;
	int count = 0;

	while(ros::ok()){

		stt.x = count;
		ROS_INFO("send data = %1d", stt.x);

		sttPub.publish(stt);
		loop_rate.sleep();
		++count;

		ros::spinOnce();

	}

	return 0;

}
