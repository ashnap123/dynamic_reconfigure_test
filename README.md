#A Test Package For ROS Dynamic Reconfigure

When serialising parameter descriptions on arm release builds, and config message with multiple 
parameters of the same type is serialised to a much bigger size than required.

The example included in this package **ExampleBroken.cfg** parameter description message serialises to over 
600MB on ARM in release. The parameter object appears to behave in all other respects, but this is difficult 
to confirm as the issue on occours in ARM release builds.

|Language | Arch | Build | Serialised Bytes | Deserialised Message |
| ------ | ------ | ------ | ------ | ------ |
| C++ | X86 | Release | 335B | Valid |
| C++ | ARM | Release | 660MB | Valid |
| C++ | ARM | Debug | 355B | Valid |

### ExampleBroken.cfg
```
#!/usr/bin/env python
PACKAGE = "dynamic_test"

from dynamic_reconfigure.parameter_generator_catkin import *

gen = ParameterGenerator()

gen.add("double_1", double_t, 0, "Double 1", 0.5, 0.0, 2.0)
gen.add("double_2", double_t, 0, "Double 2", 0.5, 0.0, 2.0)

exit(gen.generate(PACKAGE, "ExampleBroken", "ExampleBroken"))

```

### Examples nodes provided

Must be built on ARM in release to recreate

`catkin_make -DCMAKE_BUILD_TYPE=Release dynamic_test`

```
rosrun dynamic_test dynamic_test_node
rosrun dynamic_test dynamic_test_broken_node
```

### Example Tests Are Provided
Must be built on ARM in release to recreate

`catkin_make run_tests -DCMAKE_BUILD_TYPE=Release dynamic_test`
```
TEST(ParameterDescriptionSerialsation, test_serialisation_multiple_parameters) {
    auto description = dynamic_test::ExampleBrokenConfig::__getDescriptionMessage__();
    auto serialisationLength = ros::serialization::serializationLength(description);
    EXPECT_LT(serialisationLength, 1024);
}
```