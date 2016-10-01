# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dsapandora/fuerte_workspace/sandbox/andreita

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dsapandora/fuerte_workspace/sandbox/andreita/build

# Include any dependencies generated for this target.
include CMakeFiles/colores.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/colores.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/colores.dir/flags.make

CMakeFiles/colores.dir/src/color_detection.o: CMakeFiles/colores.dir/flags.make
CMakeFiles/colores.dir/src/color_detection.o: ../src/color_detection.cpp
CMakeFiles/colores.dir/src/color_detection.o: ../manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/share/roslang/manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/share/roscpp/manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/share/geometry_msgs/manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/share/nav_msgs/manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/share/sensor_msgs/manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/stacks/bullet/manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/share/rosconsole/manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/stacks/geometry/angles/manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/share/rospy/manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/share/rostest/manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/share/roswtf/manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/share/message_filters/manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/stacks/geometry/tf/manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/stacks/vision_opencv/opencv2/manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/stacks/vision_opencv/cv_bridge/manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/share/std_msgs/manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/share/pcl/manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/share/ros/core/rosbuild/manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/share/roslib/manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/stacks/pluginlib/manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/stacks/image_common/image_transport/manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /home/dsapandora/fuerte_workspace/sandbox/amor-ros-pkg/Aria/manifest.xml
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/stacks/geometry/tf/msg_gen/generated
CMakeFiles/colores.dir/src/color_detection.o: /opt/ros/fuerte/stacks/geometry/tf/srv_gen/generated
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dsapandora/fuerte_workspace/sandbox/andreita/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/colores.dir/src/color_detection.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -DBT_USE_DOUBLE_PRECISION -DBT_EULER_DEFAULT_ZYX -fPIC -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -o CMakeFiles/colores.dir/src/color_detection.o -c /home/dsapandora/fuerte_workspace/sandbox/andreita/src/color_detection.cpp

CMakeFiles/colores.dir/src/color_detection.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/colores.dir/src/color_detection.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DBT_USE_DOUBLE_PRECISION -DBT_EULER_DEFAULT_ZYX -fPIC -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -E /home/dsapandora/fuerte_workspace/sandbox/andreita/src/color_detection.cpp > CMakeFiles/colores.dir/src/color_detection.i

CMakeFiles/colores.dir/src/color_detection.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/colores.dir/src/color_detection.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DBT_USE_DOUBLE_PRECISION -DBT_EULER_DEFAULT_ZYX -fPIC -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -S /home/dsapandora/fuerte_workspace/sandbox/andreita/src/color_detection.cpp -o CMakeFiles/colores.dir/src/color_detection.s

CMakeFiles/colores.dir/src/color_detection.o.requires:
.PHONY : CMakeFiles/colores.dir/src/color_detection.o.requires

CMakeFiles/colores.dir/src/color_detection.o.provides: CMakeFiles/colores.dir/src/color_detection.o.requires
	$(MAKE) -f CMakeFiles/colores.dir/build.make CMakeFiles/colores.dir/src/color_detection.o.provides.build
.PHONY : CMakeFiles/colores.dir/src/color_detection.o.provides

CMakeFiles/colores.dir/src/color_detection.o.provides.build: CMakeFiles/colores.dir/src/color_detection.o

# Object files for target colores
colores_OBJECTS = \
"CMakeFiles/colores.dir/src/color_detection.o"

# External object files for target colores
colores_EXTERNAL_OBJECTS =

../bin/colores: CMakeFiles/colores.dir/src/color_detection.o
../bin/colores: CMakeFiles/colores.dir/build.make
../bin/colores: CMakeFiles/colores.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/colores"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/colores.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/colores.dir/build: ../bin/colores
.PHONY : CMakeFiles/colores.dir/build

CMakeFiles/colores.dir/requires: CMakeFiles/colores.dir/src/color_detection.o.requires
.PHONY : CMakeFiles/colores.dir/requires

CMakeFiles/colores.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/colores.dir/cmake_clean.cmake
.PHONY : CMakeFiles/colores.dir/clean

CMakeFiles/colores.dir/depend:
	cd /home/dsapandora/fuerte_workspace/sandbox/andreita/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dsapandora/fuerte_workspace/sandbox/andreita /home/dsapandora/fuerte_workspace/sandbox/andreita /home/dsapandora/fuerte_workspace/sandbox/andreita/build /home/dsapandora/fuerte_workspace/sandbox/andreita/build /home/dsapandora/fuerte_workspace/sandbox/andreita/build/CMakeFiles/colores.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/colores.dir/depend

