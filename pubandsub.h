#include <iostream>
#include <vector>
#include <string>
#include <math.h>

#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/String.h"
#include "../include/stl.h"

#include "/home/jarvis/catkin_ws/devel/include/my_code/Robots_msg.h"  //Robots e' a msg

using std::vector;
using std::string;
using my_code::Robots_msg;
using namespace std;


class Landmark{
    public:
        Landmark(string name, double x, double y): name(name), x(x), y(y) {

        }
        string name;
        double x;
        double y;
};

class PublishAndSubscribe{
    private:
        ros::NodeHandle node_;
        ros::Publisher Robot_pub;
        ros::Subscriber odometry;
        ros::Publisher landmark_pub;
        vector<Landmark> landmarks_;

        Robots_msg FindClosest(double x, double y);
        void InitLandmarks();

    public:
        PublishAndSubscribe(){
            InitLandmarks();

            odometry = node_.subscribe("/odom", 10, &PublishAndSubscribe::Callback, this);
    
            Robot_pub = node_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 10);
            landmark_pub = node_.advertise<Robots_msg>("/closest_landmark", 10);
        }

        void Callback(const nav_msgs::Odometry::ConstPtr& msg){
            //subscreve valores de odometria
            double x =  msg->pose.pose.position.x;
            double y =  msg->pose.pose.position.y;
            double teta = msg->pose.pose.orientation.z;
            ROS_INFO("x: [%f], y: [%f], t: [%f]", x, y, teta);

            
            Robots_msg ld = FindClosest(x, y);
            landmark_pub.publish(ld);  //para o PUBLISHER

            //publica valores de velocidade
            geometry_msgs::Twist velocity;
            velocity.linear.x = 0.2;
            velocity.angular.z = 0.2;
            Robot_pub.publish(velocity);

        }

};
