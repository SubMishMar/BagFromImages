#include <iostream>
#include <fstream>
#include <string>
#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <sensor_msgs/Image.h>
#include <std_msgs/Time.h>
#include <std_msgs/Header.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

#include "../Thirdparty/DLib/FileFunctions.h"


using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "BagFromImages");

    if(argc!=5)
    {
        cerr << "Usage: rosrun BagFromImages BagFromImages <path to image directory> <image extension .ext> <frequency> <path to output bag>" << endl;
        return 0;
    }

    ros::start();

    // Vector of paths to image
    vector<string> filenames =
            DUtils::FileFunctions::Dir(argv[1], argv[2], true);

    cout << "Images: " << filenames.size() << endl;

    // Output bag
    rosbag::Bag bag_out(argv[3],rosbag::bagmode::Write);

    string time_file_name;
    time_file_name = argv[4];

    ifstream time_file;
    time_file.open(time_file_name.c_str());
    string line;
	if (time_file.is_open()) {
		size_t i=0;
	    while ( getline (time_file,line) )
	    {
	        if(!ros::ok())
	            break;
	        double time_stamp = stod(line);
	        if(i==0) {
	        	time_stamp = 0.000000001; 
	        } 
	        ros::Time t(time_stamp);
	        cv::Mat im = cv::imread(filenames[i],CV_LOAD_IMAGE_COLOR);
	        cv_bridge::CvImage cvImage;
	        cvImage.image = im;
	        cvImage.encoding = sensor_msgs::image_encodings::RGB8;
	        cvImage.header.stamp = t;
	        bag_out.write("/camera/image_raw",ros::Time(t),cvImage.toImageMsg());
	        cout << i << " / " << filenames.size() << endl;
	        i++;
	    }
	    time_file.close();
	}

    bag_out.close();

    ros::shutdown();

    return 0;
}