#include "pubandsub.h"

//#include "mycode.h"
// #include "../include/my_code/mycode.h"


int main(int argc, char **argv){

    ros::init(argc, argv, "mycode");

    PublishAndSubscribe RoboObj;

    ros::spin();
    
    return 0;
}