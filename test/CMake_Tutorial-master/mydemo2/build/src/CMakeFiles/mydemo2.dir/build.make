# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kim/CMake_Tutorial-master/mydemo2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kim/CMake_Tutorial-master/mydemo2/build

# Include any dependencies generated for this target.
include src/CMakeFiles/mydemo2.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/mydemo2.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/mydemo2.dir/flags.make

src/CMakeFiles/mydemo2.dir/main.cpp.o: src/CMakeFiles/mydemo2.dir/flags.make
src/CMakeFiles/mydemo2.dir/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kim/CMake_Tutorial-master/mydemo2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/mydemo2.dir/main.cpp.o"
	cd /home/kim/CMake_Tutorial-master/mydemo2/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mydemo2.dir/main.cpp.o -c /home/kim/CMake_Tutorial-master/mydemo2/src/main.cpp

src/CMakeFiles/mydemo2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mydemo2.dir/main.cpp.i"
	cd /home/kim/CMake_Tutorial-master/mydemo2/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kim/CMake_Tutorial-master/mydemo2/src/main.cpp > CMakeFiles/mydemo2.dir/main.cpp.i

src/CMakeFiles/mydemo2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mydemo2.dir/main.cpp.s"
	cd /home/kim/CMake_Tutorial-master/mydemo2/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kim/CMake_Tutorial-master/mydemo2/src/main.cpp -o CMakeFiles/mydemo2.dir/main.cpp.s

# Object files for target mydemo2
mydemo2_OBJECTS = \
"CMakeFiles/mydemo2.dir/main.cpp.o"

# External object files for target mydemo2
mydemo2_EXTERNAL_OBJECTS =

src/mydemo2: src/CMakeFiles/mydemo2.dir/main.cpp.o
src/mydemo2: src/CMakeFiles/mydemo2.dir/build.make
src/mydemo2: include/libMylib.a
src/mydemo2: src/CMakeFiles/mydemo2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kim/CMake_Tutorial-master/mydemo2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mydemo2"
	cd /home/kim/CMake_Tutorial-master/mydemo2/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mydemo2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/mydemo2.dir/build: src/mydemo2

.PHONY : src/CMakeFiles/mydemo2.dir/build

src/CMakeFiles/mydemo2.dir/clean:
	cd /home/kim/CMake_Tutorial-master/mydemo2/build/src && $(CMAKE_COMMAND) -P CMakeFiles/mydemo2.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/mydemo2.dir/clean

src/CMakeFiles/mydemo2.dir/depend:
	cd /home/kim/CMake_Tutorial-master/mydemo2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kim/CMake_Tutorial-master/mydemo2 /home/kim/CMake_Tutorial-master/mydemo2/src /home/kim/CMake_Tutorial-master/mydemo2/build /home/kim/CMake_Tutorial-master/mydemo2/build/src /home/kim/CMake_Tutorial-master/mydemo2/build/src/CMakeFiles/mydemo2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/mydemo2.dir/depend

