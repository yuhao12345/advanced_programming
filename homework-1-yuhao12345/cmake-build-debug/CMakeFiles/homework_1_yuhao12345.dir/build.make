# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /mnt/e/github/advanced_prog/homework-1-yuhao12345

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/e/github/advanced_prog/homework-1-yuhao12345/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/homework_1_yuhao12345.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/homework_1_yuhao12345.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/homework_1_yuhao12345.dir/flags.make

CMakeFiles/homework_1_yuhao12345.dir/test_list2.c.o: CMakeFiles/homework_1_yuhao12345.dir/flags.make
CMakeFiles/homework_1_yuhao12345.dir/test_list2.c.o: ../test_list2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/github/advanced_prog/homework-1-yuhao12345/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/homework_1_yuhao12345.dir/test_list2.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/homework_1_yuhao12345.dir/test_list2.c.o -c /mnt/e/github/advanced_prog/homework-1-yuhao12345/test_list2.c

CMakeFiles/homework_1_yuhao12345.dir/test_list2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/homework_1_yuhao12345.dir/test_list2.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/e/github/advanced_prog/homework-1-yuhao12345/test_list2.c > CMakeFiles/homework_1_yuhao12345.dir/test_list2.c.i

CMakeFiles/homework_1_yuhao12345.dir/test_list2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/homework_1_yuhao12345.dir/test_list2.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/e/github/advanced_prog/homework-1-yuhao12345/test_list2.c -o CMakeFiles/homework_1_yuhao12345.dir/test_list2.c.s

CMakeFiles/homework_1_yuhao12345.dir/list.c.o: CMakeFiles/homework_1_yuhao12345.dir/flags.make
CMakeFiles/homework_1_yuhao12345.dir/list.c.o: ../list.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/github/advanced_prog/homework-1-yuhao12345/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/homework_1_yuhao12345.dir/list.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/homework_1_yuhao12345.dir/list.c.o -c /mnt/e/github/advanced_prog/homework-1-yuhao12345/list.c

CMakeFiles/homework_1_yuhao12345.dir/list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/homework_1_yuhao12345.dir/list.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/e/github/advanced_prog/homework-1-yuhao12345/list.c > CMakeFiles/homework_1_yuhao12345.dir/list.c.i

CMakeFiles/homework_1_yuhao12345.dir/list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/homework_1_yuhao12345.dir/list.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/e/github/advanced_prog/homework-1-yuhao12345/list.c -o CMakeFiles/homework_1_yuhao12345.dir/list.c.s

# Object files for target homework_1_yuhao12345
homework_1_yuhao12345_OBJECTS = \
"CMakeFiles/homework_1_yuhao12345.dir/test_list2.c.o" \
"CMakeFiles/homework_1_yuhao12345.dir/list.c.o"

# External object files for target homework_1_yuhao12345
homework_1_yuhao12345_EXTERNAL_OBJECTS =

homework_1_yuhao12345: CMakeFiles/homework_1_yuhao12345.dir/test_list2.c.o
homework_1_yuhao12345: CMakeFiles/homework_1_yuhao12345.dir/list.c.o
homework_1_yuhao12345: CMakeFiles/homework_1_yuhao12345.dir/build.make
homework_1_yuhao12345: CMakeFiles/homework_1_yuhao12345.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/e/github/advanced_prog/homework-1-yuhao12345/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable homework_1_yuhao12345"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/homework_1_yuhao12345.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/homework_1_yuhao12345.dir/build: homework_1_yuhao12345

.PHONY : CMakeFiles/homework_1_yuhao12345.dir/build

CMakeFiles/homework_1_yuhao12345.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/homework_1_yuhao12345.dir/cmake_clean.cmake
.PHONY : CMakeFiles/homework_1_yuhao12345.dir/clean

CMakeFiles/homework_1_yuhao12345.dir/depend:
	cd /mnt/e/github/advanced_prog/homework-1-yuhao12345/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/e/github/advanced_prog/homework-1-yuhao12345 /mnt/e/github/advanced_prog/homework-1-yuhao12345 /mnt/e/github/advanced_prog/homework-1-yuhao12345/cmake-build-debug /mnt/e/github/advanced_prog/homework-1-yuhao12345/cmake-build-debug /mnt/e/github/advanced_prog/homework-1-yuhao12345/cmake-build-debug/CMakeFiles/homework_1_yuhao12345.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/homework_1_yuhao12345.dir/depend

