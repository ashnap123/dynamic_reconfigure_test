#include <ros/ros.h>
#include <ros/serialization.h>

#include <dynamic_reconfigure/server.h>
#include <dynamic_test/ExampleBrokenConfig.h>


const ros::Duration TIMEOUT_CLEARANCE_HEIGHT(10);
typedef dynamic_test::ExampleBrokenConfig Config;

void callback(Config &config, uint32_t level) {
    ROS_INFO("Reconfigure Request");
}


// Void height is used because this is easy for a human to measure and enter
// Most use cases will subtract the clearance height from the void height, giving the height from the chassis (base_link) to ceiling
// This "spray height" will be used by kinematics and transforms, as they all transform from the base_link (rather than the base_footprint)
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