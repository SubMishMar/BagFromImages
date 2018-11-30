# BagFromImages

ROS package to generate a rosbag from a collection of images. Images are ordered alphabetically. The timestamp for each image is assigned according to the specified frequency. 

The bag will publish the images to topic `/camera/image_raw`.

Tested in ROS Kinetic running on Ubuntu 16.04.


## Usage:

    rosrun BagFromImages BagFromImages_node PATH_TO_IMAGES IMAGE_EXTENSION PATH_TO_OUPUT_BAG PATH_TO_TIMESTAMP_TEXT_FILE
  
 - `PATH_TO_IMAGES`: Path to the folder with the images
 - `IMAGE_EXTENSION`: .jpg, .png, etc. write the dot "."
 - `PATH_TO_OUTPUT_BAG`: Path to save the bag (including the filename e.g. directory/filename.bag)
 
 ## example
 
`rosrun BagFromImages BagFromImages_node /home/subodh/Downloads/dataset/sequences/00/image_0 "png" /home/subodh/kittibag.bag /home/subodh/Downloads/dataset/sequences/00/times.txt`
