//
// Created by q-bot on 03/09/18.
//

#include <gtest/gtest.h>

#include <ros/serialization.h>
#include <dynamic_test/ExampleBrokenConfig.h>
#include <dynamic_test/ExampleConfig.h>


TEST(ParameterDescriptionSerialsation, test_serialisation_multiple_parameters) {
    auto description = dynamic_test::ExampleBrokenConfig::__getDescriptionMessage__();
    auto serialisationLength = ros::serialization::serializationLength(description);
    EXPECT_LT(serialisationLength, 1024);
}

TEST(ParameterDescriptionSerialsation, test_serialisation_single_parameter) {
    auto description = dynamic_test::ExampleConfig::__getDescriptionMessage__();
    auto serialisationLength = ros::serialization::serializationLength(description);
    EXPECT_LT(serialisationLength, 1024);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}