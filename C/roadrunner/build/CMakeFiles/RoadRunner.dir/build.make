# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vagrant/Documents/students-2022/C/roadrunner

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vagrant/Documents/students-2022/C/roadrunner/build

# Include any dependencies generated for this target.
include CMakeFiles/RoadRunner.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/RoadRunner.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/RoadRunner.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RoadRunner.dir/flags.make

CMakeFiles/RoadRunner.dir/src/roadrunner.c.o: CMakeFiles/RoadRunner.dir/flags.make
CMakeFiles/RoadRunner.dir/src/roadrunner.c.o: ../src/roadrunner.c
CMakeFiles/RoadRunner.dir/src/roadrunner.c.o: CMakeFiles/RoadRunner.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/Documents/students-2022/C/roadrunner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/RoadRunner.dir/src/roadrunner.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/RoadRunner.dir/src/roadrunner.c.o -MF CMakeFiles/RoadRunner.dir/src/roadrunner.c.o.d -o CMakeFiles/RoadRunner.dir/src/roadrunner.c.o -c /home/vagrant/Documents/students-2022/C/roadrunner/src/roadrunner.c

CMakeFiles/RoadRunner.dir/src/roadrunner.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RoadRunner.dir/src/roadrunner.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vagrant/Documents/students-2022/C/roadrunner/src/roadrunner.c > CMakeFiles/RoadRunner.dir/src/roadrunner.c.i

CMakeFiles/RoadRunner.dir/src/roadrunner.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RoadRunner.dir/src/roadrunner.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vagrant/Documents/students-2022/C/roadrunner/src/roadrunner.c -o CMakeFiles/RoadRunner.dir/src/roadrunner.c.s

# Object files for target RoadRunner
RoadRunner_OBJECTS = \
"CMakeFiles/RoadRunner.dir/src/roadrunner.c.o"

# External object files for target RoadRunner
RoadRunner_EXTERNAL_OBJECTS =

../bin/RoadRunner: CMakeFiles/RoadRunner.dir/src/roadrunner.c.o
../bin/RoadRunner: CMakeFiles/RoadRunner.dir/build.make
../bin/RoadRunner: src/modules/helloworld/libhelloworld.a
../bin/RoadRunner: src/modules/commands/libcommands.a
../bin/RoadRunner: src/modules/core/libcore.a
../bin/RoadRunner: src/modules/files/libfiles.a
../bin/RoadRunner: src/modules/sys/libsys.a
../bin/RoadRunner: src/modules/proxy/libproxy.a
../bin/RoadRunner: src/modules/commands/libcommands.a
../bin/RoadRunner: CMakeFiles/RoadRunner.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vagrant/Documents/students-2022/C/roadrunner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../bin/RoadRunner"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RoadRunner.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RoadRunner.dir/build: ../bin/RoadRunner
.PHONY : CMakeFiles/RoadRunner.dir/build

CMakeFiles/RoadRunner.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RoadRunner.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RoadRunner.dir/clean

CMakeFiles/RoadRunner.dir/depend:
	cd /home/vagrant/Documents/students-2022/C/roadrunner/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/Documents/students-2022/C/roadrunner /home/vagrant/Documents/students-2022/C/roadrunner /home/vagrant/Documents/students-2022/C/roadrunner/build /home/vagrant/Documents/students-2022/C/roadrunner/build /home/vagrant/Documents/students-2022/C/roadrunner/build/CMakeFiles/RoadRunner.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RoadRunner.dir/depend
