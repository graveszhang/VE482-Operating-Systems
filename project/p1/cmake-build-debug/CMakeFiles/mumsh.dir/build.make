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
include CMakeFiles/mumsh.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mumsh.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mumsh.dir/flags.make

CMakeFiles/mumsh.dir/main.c.o: CMakeFiles/mumsh.dir/flags.make
CMakeFiles/mumsh.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/mumsh.dir/main.c.o"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mumsh.dir/main.c.o   -c "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/main.c"

CMakeFiles/mumsh.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mumsh.dir/main.c.i"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/main.c" > CMakeFiles/mumsh.dir/main.c.i

CMakeFiles/mumsh.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mumsh.dir/main.c.s"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/main.c" -o CMakeFiles/mumsh.dir/main.c.s

CMakeFiles/mumsh.dir/read.c.o: CMakeFiles/mumsh.dir/flags.make
CMakeFiles/mumsh.dir/read.c.o: ../read.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/mumsh.dir/read.c.o"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mumsh.dir/read.c.o   -c "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/read.c"

CMakeFiles/mumsh.dir/read.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mumsh.dir/read.c.i"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/read.c" > CMakeFiles/mumsh.dir/read.c.i

CMakeFiles/mumsh.dir/read.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mumsh.dir/read.c.s"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/read.c" -o CMakeFiles/mumsh.dir/read.c.s

CMakeFiles/mumsh.dir/parse.c.o: CMakeFiles/mumsh.dir/flags.make
CMakeFiles/mumsh.dir/parse.c.o: ../parse.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/mumsh.dir/parse.c.o"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mumsh.dir/parse.c.o   -c "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/parse.c"

CMakeFiles/mumsh.dir/parse.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mumsh.dir/parse.c.i"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/parse.c" > CMakeFiles/mumsh.dir/parse.c.i

CMakeFiles/mumsh.dir/parse.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mumsh.dir/parse.c.s"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/parse.c" -o CMakeFiles/mumsh.dir/parse.c.s

CMakeFiles/mumsh.dir/execute.c.o: CMakeFiles/mumsh.dir/flags.make
CMakeFiles/mumsh.dir/execute.c.o: ../execute.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/mumsh.dir/execute.c.o"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mumsh.dir/execute.c.o   -c "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/execute.c"

CMakeFiles/mumsh.dir/execute.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mumsh.dir/execute.c.i"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/execute.c" > CMakeFiles/mumsh.dir/execute.c.i

CMakeFiles/mumsh.dir/execute.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mumsh.dir/execute.c.s"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/execute.c" -o CMakeFiles/mumsh.dir/execute.c.s

CMakeFiles/mumsh.dir/redirect.c.o: CMakeFiles/mumsh.dir/flags.make
CMakeFiles/mumsh.dir/redirect.c.o: ../redirect.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/mumsh.dir/redirect.c.o"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mumsh.dir/redirect.c.o   -c "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/redirect.c"

CMakeFiles/mumsh.dir/redirect.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mumsh.dir/redirect.c.i"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/redirect.c" > CMakeFiles/mumsh.dir/redirect.c.i

CMakeFiles/mumsh.dir/redirect.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mumsh.dir/redirect.c.s"
	/Users/gravescn/opt/anaconda3/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/redirect.c" -o CMakeFiles/mumsh.dir/redirect.c.s

# Object files for target mumsh
mumsh_OBJECTS = \
"CMakeFiles/mumsh.dir/main.c.o" \
"CMakeFiles/mumsh.dir/read.c.o" \
"CMakeFiles/mumsh.dir/parse.c.o" \
"CMakeFiles/mumsh.dir/execute.c.o" \
"CMakeFiles/mumsh.dir/redirect.c.o"

# External object files for target mumsh
mumsh_EXTERNAL_OBJECTS =

mumsh: CMakeFiles/mumsh.dir/main.c.o
mumsh: CMakeFiles/mumsh.dir/read.c.o
mumsh: CMakeFiles/mumsh.dir/parse.c.o
mumsh: CMakeFiles/mumsh.dir/execute.c.o
mumsh: CMakeFiles/mumsh.dir/redirect.c.o
mumsh: CMakeFiles/mumsh.dir/build.make
mumsh: CMakeFiles/mumsh.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable mumsh"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mumsh.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mumsh.dir/build: mumsh

.PHONY : CMakeFiles/mumsh.dir/build

CMakeFiles/mumsh.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mumsh.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mumsh.dir/clean

CMakeFiles/mumsh.dir/depend:
	cd "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1" "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1" "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/cmake-build-debug" "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/cmake-build-debug" "/Users/gravescn/Desktop/GS/Coding Projects/VE482-Intro-to-Operating-Systems/project/p1/cmake-build-debug/CMakeFiles/mumsh.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/mumsh.dir/depend

