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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/p1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/p1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/p1.dir/flags.make

CMakeFiles/p1.dir/main.c.o: CMakeFiles/p1.dir/flags.make
CMakeFiles/p1.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/p1.dir/main.c.o"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/p1.dir/main.c.o   -c "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/main.c"

CMakeFiles/p1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/p1.dir/main.c.i"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/main.c" > CMakeFiles/p1.dir/main.c.i

CMakeFiles/p1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/p1.dir/main.c.s"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/main.c" -o CMakeFiles/p1.dir/main.c.s

CMakeFiles/p1.dir/read.c.o: CMakeFiles/p1.dir/flags.make
CMakeFiles/p1.dir/read.c.o: ../read.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/p1.dir/read.c.o"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/p1.dir/read.c.o   -c "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/read.c"

CMakeFiles/p1.dir/read.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/p1.dir/read.c.i"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/read.c" > CMakeFiles/p1.dir/read.c.i

CMakeFiles/p1.dir/read.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/p1.dir/read.c.s"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/read.c" -o CMakeFiles/p1.dir/read.c.s

CMakeFiles/p1.dir/parse.c.o: CMakeFiles/p1.dir/flags.make
CMakeFiles/p1.dir/parse.c.o: ../parse.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/p1.dir/parse.c.o"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/p1.dir/parse.c.o   -c "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/parse.c"

CMakeFiles/p1.dir/parse.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/p1.dir/parse.c.i"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/parse.c" > CMakeFiles/p1.dir/parse.c.i

CMakeFiles/p1.dir/parse.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/p1.dir/parse.c.s"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/parse.c" -o CMakeFiles/p1.dir/parse.c.s

CMakeFiles/p1.dir/execute.c.o: CMakeFiles/p1.dir/flags.make
CMakeFiles/p1.dir/execute.c.o: ../execute.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/p1.dir/execute.c.o"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/p1.dir/execute.c.o   -c "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/execute.c"

CMakeFiles/p1.dir/execute.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/p1.dir/execute.c.i"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/execute.c" > CMakeFiles/p1.dir/execute.c.i

CMakeFiles/p1.dir/execute.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/p1.dir/execute.c.s"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/execute.c" -o CMakeFiles/p1.dir/execute.c.s

CMakeFiles/p1.dir/redirect.c.o: CMakeFiles/p1.dir/flags.make
CMakeFiles/p1.dir/redirect.c.o: ../redirect.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/p1.dir/redirect.c.o"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/p1.dir/redirect.c.o   -c "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/redirect.c"

CMakeFiles/p1.dir/redirect.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/p1.dir/redirect.c.i"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/redirect.c" > CMakeFiles/p1.dir/redirect.c.i

CMakeFiles/p1.dir/redirect.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/p1.dir/redirect.c.s"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/redirect.c" -o CMakeFiles/p1.dir/redirect.c.s

# Object files for target p1
p1_OBJECTS = \
"CMakeFiles/p1.dir/main.c.o" \
"CMakeFiles/p1.dir/read.c.o" \
"CMakeFiles/p1.dir/parse.c.o" \
"CMakeFiles/p1.dir/execute.c.o" \
"CMakeFiles/p1.dir/redirect.c.o"

# External object files for target p1
p1_EXTERNAL_OBJECTS =

p1: CMakeFiles/p1.dir/main.c.o
p1: CMakeFiles/p1.dir/read.c.o
p1: CMakeFiles/p1.dir/parse.c.o
p1: CMakeFiles/p1.dir/execute.c.o
p1: CMakeFiles/p1.dir/redirect.c.o
p1: CMakeFiles/p1.dir/build.make
p1: CMakeFiles/p1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable p1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/p1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/p1.dir/build: p1

.PHONY : CMakeFiles/p1.dir/build

CMakeFiles/p1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/p1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/p1.dir/clean

CMakeFiles/p1.dir/depend:
	cd "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1" "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1" "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/cmake-build-debug" "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/cmake-build-debug" "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/cmake-build-debug/CMakeFiles/p1.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/p1.dir/depend

