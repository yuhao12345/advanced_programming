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
CMAKE_SOURCE_DIR = /mnt/e/github/advanced_prog/final

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/e/github/advanced_prog/final

# Include any dependencies generated for this target.
include CMakeFiles/final.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/final.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/final.dir/flags.make

CMakeFiles/final.dir/main.c.o: CMakeFiles/final.dir/flags.make
CMakeFiles/final.dir/main.c.o: main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/github/advanced_prog/final/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/final.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/final.dir/main.c.o -c /mnt/e/github/advanced_prog/final/main.c

CMakeFiles/final.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/final.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/e/github/advanced_prog/final/main.c > CMakeFiles/final.dir/main.c.i

CMakeFiles/final.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/final.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/e/github/advanced_prog/final/main.c -o CMakeFiles/final.dir/main.c.s

CMakeFiles/final.dir/heap.c.o: CMakeFiles/final.dir/flags.make
CMakeFiles/final.dir/heap.c.o: heap.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/github/advanced_prog/final/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/final.dir/heap.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/final.dir/heap.c.o -c /mnt/e/github/advanced_prog/final/heap.c

CMakeFiles/final.dir/heap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/final.dir/heap.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/e/github/advanced_prog/final/heap.c > CMakeFiles/final.dir/heap.c.i

CMakeFiles/final.dir/heap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/final.dir/heap.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/e/github/advanced_prog/final/heap.c -o CMakeFiles/final.dir/heap.c.s

CMakeFiles/final.dir/encode_decode.c.o: CMakeFiles/final.dir/flags.make
CMakeFiles/final.dir/encode_decode.c.o: encode_decode.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/github/advanced_prog/final/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/final.dir/encode_decode.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/final.dir/encode_decode.c.o -c /mnt/e/github/advanced_prog/final/encode_decode.c

CMakeFiles/final.dir/encode_decode.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/final.dir/encode_decode.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/e/github/advanced_prog/final/encode_decode.c > CMakeFiles/final.dir/encode_decode.c.i

CMakeFiles/final.dir/encode_decode.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/final.dir/encode_decode.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/e/github/advanced_prog/final/encode_decode.c -o CMakeFiles/final.dir/encode_decode.c.s

# Object files for target final
final_OBJECTS = \
"CMakeFiles/final.dir/main.c.o" \
"CMakeFiles/final.dir/heap.c.o" \
"CMakeFiles/final.dir/encode_decode.c.o"

# External object files for target final
final_EXTERNAL_OBJECTS =

final: CMakeFiles/final.dir/main.c.o
final: CMakeFiles/final.dir/heap.c.o
final: CMakeFiles/final.dir/encode_decode.c.o
final: CMakeFiles/final.dir/build.make
final: CMakeFiles/final.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/e/github/advanced_prog/final/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable final"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/final.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/final.dir/build: final

.PHONY : CMakeFiles/final.dir/build

CMakeFiles/final.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/final.dir/cmake_clean.cmake
.PHONY : CMakeFiles/final.dir/clean

CMakeFiles/final.dir/depend:
	cd /mnt/e/github/advanced_prog/final && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/e/github/advanced_prog/final /mnt/e/github/advanced_prog/final /mnt/e/github/advanced_prog/final /mnt/e/github/advanced_prog/final /mnt/e/github/advanced_prog/final/CMakeFiles/final.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/final.dir/depend

