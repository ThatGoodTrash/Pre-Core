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
include src/modules/helloworld/CMakeFiles/helloworld.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/modules/helloworld/CMakeFiles/helloworld.dir/compiler_depend.make

# Include the progress variables for this target.
include src/modules/helloworld/CMakeFiles/helloworld.dir/progress.make

# Include the compile flags for this target's objects.
include src/modules/helloworld/CMakeFiles/helloworld.dir/flags.make

src/modules/helloworld/CMakeFiles/helloworld.dir/helloworld.c.o: src/modules/helloworld/CMakeFiles/helloworld.dir/flags.make
src/modules/helloworld/CMakeFiles/helloworld.dir/helloworld.c.o: ../src/modules/helloworld/helloworld.c
src/modules/helloworld/CMakeFiles/helloworld.dir/helloworld.c.o: src/modules/helloworld/CMakeFiles/helloworld.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/Documents/students-2022/C/roadrunner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/modules/helloworld/CMakeFiles/helloworld.dir/helloworld.c.o"
	cd /home/vagrant/Documents/students-2022/C/roadrunner/build/src/modules/helloworld && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/modules/helloworld/CMakeFiles/helloworld.dir/helloworld.c.o -MF CMakeFiles/helloworld.dir/helloworld.c.o.d -o CMakeFiles/helloworld.dir/helloworld.c.o -c /home/vagrant/Documents/students-2022/C/roadrunner/src/modules/helloworld/helloworld.c

src/modules/helloworld/CMakeFiles/helloworld.dir/helloworld.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/helloworld.dir/helloworld.c.i"
	cd /home/vagrant/Documents/students-2022/C/roadrunner/build/src/modules/helloworld && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vagrant/Documents/students-2022/C/roadrunner/src/modules/helloworld/helloworld.c > CMakeFiles/helloworld.dir/helloworld.c.i

src/modules/helloworld/CMakeFiles/helloworld.dir/helloworld.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/helloworld.dir/helloworld.c.s"
	cd /home/vagrant/Documents/students-2022/C/roadrunner/build/src/modules/helloworld && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vagrant/Documents/students-2022/C/roadrunner/src/modules/helloworld/helloworld.c -o CMakeFiles/helloworld.dir/helloworld.c.s

# Object files for target helloworld
helloworld_OBJECTS = \
"CMakeFiles/helloworld.dir/helloworld.c.o"

# External object files for target helloworld
helloworld_EXTERNAL_OBJECTS =

src/modules/helloworld/libhelloworld.a: src/modules/helloworld/CMakeFiles/helloworld.dir/helloworld.c.o
src/modules/helloworld/libhelloworld.a: src/modules/helloworld/CMakeFiles/helloworld.dir/build.make
src/modules/helloworld/libhelloworld.a: src/modules/helloworld/CMakeFiles/helloworld.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vagrant/Documents/students-2022/C/roadrunner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libhelloworld.a"
	cd /home/vagrant/Documents/students-2022/C/roadrunner/build/src/modules/helloworld && $(CMAKE_COMMAND) -P CMakeFiles/helloworld.dir/cmake_clean_target.cmake
	cd /home/vagrant/Documents/students-2022/C/roadrunner/build/src/modules/helloworld && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/helloworld.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/modules/helloworld/CMakeFiles/helloworld.dir/build: src/modules/helloworld/libhelloworld.a
.PHONY : src/modules/helloworld/CMakeFiles/helloworld.dir/build

src/modules/helloworld/CMakeFiles/helloworld.dir/clean:
	cd /home/vagrant/Documents/students-2022/C/roadrunner/build/src/modules/helloworld && $(CMAKE_COMMAND) -P CMakeFiles/helloworld.dir/cmake_clean.cmake
.PHONY : src/modules/helloworld/CMakeFiles/helloworld.dir/clean

src/modules/helloworld/CMakeFiles/helloworld.dir/depend:
	cd /home/vagrant/Documents/students-2022/C/roadrunner/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/Documents/students-2022/C/roadrunner /home/vagrant/Documents/students-2022/C/roadrunner/src/modules/helloworld /home/vagrant/Documents/students-2022/C/roadrunner/build /home/vagrant/Documents/students-2022/C/roadrunner/build/src/modules/helloworld /home/vagrant/Documents/students-2022/C/roadrunner/build/src/modules/helloworld/CMakeFiles/helloworld.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/modules/helloworld/CMakeFiles/helloworld.dir/depend

