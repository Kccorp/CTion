# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /home/kbod/cmake-3.21.1/bin/cmake

# The command to remove a file.
RM = /home/kbod/cmake-3.21.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/Keiss/CLionProjects/cTion

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Keiss/CLionProjects/cTion/cmake-build-wsl_profile

# Include any dependencies generated for this target.
include CMakeFiles/cTion.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cTion.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cTion.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cTion.dir/flags.make

CMakeFiles/cTion.dir/main.c.o: CMakeFiles/cTion.dir/flags.make
CMakeFiles/cTion.dir/main.c.o: ../main.c
CMakeFiles/cTion.dir/main.c.o: CMakeFiles/cTion.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Keiss/CLionProjects/cTion/cmake-build-wsl_profile/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cTion.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/cTion.dir/main.c.o -MF CMakeFiles/cTion.dir/main.c.o.d -o CMakeFiles/cTion.dir/main.c.o -c /mnt/c/Users/Keiss/CLionProjects/cTion/main.c

CMakeFiles/cTion.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cTion.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Keiss/CLionProjects/cTion/main.c > CMakeFiles/cTion.dir/main.c.i

CMakeFiles/cTion.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cTion.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Keiss/CLionProjects/cTion/main.c -o CMakeFiles/cTion.dir/main.c.s

# Object files for target cTion
cTion_OBJECTS = \
"CMakeFiles/cTion.dir/main.c.o"

# External object files for target cTion
cTion_EXTERNAL_OBJECTS =

cTion: CMakeFiles/cTion.dir/main.c.o
cTion: CMakeFiles/cTion.dir/build.make
cTion: /usr/lib/x86_64-linux-gnu/libcurl.so
cTion: CMakeFiles/cTion.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Keiss/CLionProjects/cTion/cmake-build-wsl_profile/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable cTion"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cTion.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cTion.dir/build: cTion
.PHONY : CMakeFiles/cTion.dir/build

CMakeFiles/cTion.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cTion.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cTion.dir/clean

CMakeFiles/cTion.dir/depend:
	cd /mnt/c/Users/Keiss/CLionProjects/cTion/cmake-build-wsl_profile && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Keiss/CLionProjects/cTion /mnt/c/Users/Keiss/CLionProjects/cTion /mnt/c/Users/Keiss/CLionProjects/cTion/cmake-build-wsl_profile /mnt/c/Users/Keiss/CLionProjects/cTion/cmake-build-wsl_profile /mnt/c/Users/Keiss/CLionProjects/cTion/cmake-build-wsl_profile/CMakeFiles/cTion.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cTion.dir/depend

