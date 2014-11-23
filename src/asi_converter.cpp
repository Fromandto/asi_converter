#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <sensor_msgs/fill_image.h>

int main(int argc , char ** argv)
{
	ros::init(argc , argv , "asi_converter");
	ros::NodeHandle nh_;
	image_transport::ImageTransport it_(nh_);
	image_transport::Publisher image_pub_ = it_.advertise("/asi_converter/output_video" , 1);
	ros::Rate loop_rate(30);
	cv::Mat frame;
	cv::VideoCapture capture;
	capture.open("/root/catkin_ws/test.avi");
	assert(capture.isOpened());
	//cv::namedWindow("Preview");
	while(ros::ok())
	{
		capture >> frame;
		//cv::imshow("Preview" , frame);
		//cv::waitKey(1);
		std_msgs::Header header;
		cv_bridge::CvImage cv_ptr(header , "bgr8" , frame);
		image_pub_.publish(cv_ptr.toImageMsg());
		loop_rate.sleep();
		ros::spinOnce();
	}
	return 0;
}
