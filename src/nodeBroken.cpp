#include <ros/ros.h>

#include <dynamic_reconfigure/server.h>
#include <dynamic_test/ExampleBrokenConfig.h>


typedef dynamic_test::ExampleBrokenConfig Config;

void callback(Config &config, uint32_t level) {
    ROS_INFO("Reconfigure Request");
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "test_broken_node");

    dynamic_reconfigure::Server<Config> server;
    dynamic_reconfigure::Server<Config>::CallbackType reconfigureCallback;

    reconfigureCallback = boost::bind(&callback, _1, _2);
    server.setCallback(reconfigureCallback);

    ros::spin();
    return 0;
}