# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /home/ahmednaggar19/Downloads/clion-2017.2.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/ahmednaggar19/Downloads/clion-2017.2.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ahmednaggar19/OS/MatrixMultiplication

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ahmednaggar19/OS/MatrixMultiplication/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MatrixMultiplication.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MatrixMultiplication.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MatrixMultiplication.dir/flags.make

CMakeFiles/MatrixMultiplication.dir/main.c.o: CMakeFiles/MatrixMultiplication.dir/flags.make
CMakeFiles/MatrixMultiplication.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ahmednaggar19/OS/MatrixMultiplication/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/MatrixMultiplication.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MatrixMultiplication.dir/main.c.o   -c /home/ahmednaggar19/OS/MatrixMultiplication/main.c

CMakeFiles/MatrixMultiplication.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MatrixMultiplication.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ahmednaggar19/OS/MatrixMultiplication/main.c > CMakeFiles/MatrixMultiplication.dir/main.c.i

CMakeFiles/MatrixMultiplication.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MatrixMultiplication.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ahmednaggar19/OS/MatrixMultiplication/main.c -o CMakeFiles/MatrixMultiplication.dir/main.c.s

CMakeFiles/MatrixMultiplication.dir/main.c.o.requires:

.PHONY : CMakeFiles/MatrixMultiplication.dir/main.c.o.requires

CMakeFiles/MatrixMultiplication.dir/main.c.o.provides: CMakeFiles/MatrixMultiplication.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/MatrixMultiplication.dir/build.make CMakeFiles/MatrixMultiplication.dir/main.c.o.provides.build
.PHONY : CMakeFiles/MatrixMultiplication.dir/main.c.o.provides

CMakeFiles/MatrixMultiplication.dir/main.c.o.provides.build: CMakeFiles/MatrixMultiplication.dir/main.c.o


CMakeFiles/MatrixMultiplication.dir/file_processing.c.o: CMakeFiles/MatrixMultiplication.dir/flags.make
CMakeFiles/MatrixMultiplication.dir/file_processing.c.o: ../file_processing.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ahmednaggar19/OS/MatrixMultiplication/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/MatrixMultiplication.dir/file_processing.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MatrixMultiplication.dir/file_processing.c.o   -c /home/ahmednaggar19/OS/MatrixMultiplication/file_processing.c

CMakeFiles/MatrixMultiplication.dir/file_processing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MatrixMultiplication.dir/file_processing.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ahmednaggar19/OS/MatrixMultiplication/file_processing.c > CMakeFiles/MatrixMultiplication.dir/file_processing.c.i

CMakeFiles/MatrixMultiplication.dir/file_processing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MatrixMultiplication.dir/file_processing.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ahmednaggar19/OS/MatrixMultiplication/file_processing.c -o CMakeFiles/MatrixMultiplication.dir/file_processing.c.s

CMakeFiles/MatrixMultiplication.dir/file_processing.c.o.requires:

.PHONY : CMakeFiles/MatrixMultiplication.dir/file_processing.c.o.requires

CMakeFiles/MatrixMultiplication.dir/file_processing.c.o.provides: CMakeFiles/MatrixMultiplication.dir/file_processing.c.o.requires
	$(MAKE) -f CMakeFiles/MatrixMultiplication.dir/build.make CMakeFiles/MatrixMultiplication.dir/file_processing.c.o.provides.build
.PHONY : CMakeFiles/MatrixMultiplication.dir/file_processing.c.o.provides

CMakeFiles/MatrixMultiplication.dir/file_processing.c.o.provides.build: CMakeFiles/MatrixMultiplication.dir/file_processing.c.o


CMakeFiles/MatrixMultiplication.dir/matrix_multiplication.c.o: CMakeFiles/MatrixMultiplication.dir/flags.make
CMakeFiles/MatrixMultiplication.dir/matrix_multiplication.c.o: ../matrix_multiplication.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ahmednaggar19/OS/MatrixMultiplication/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/MatrixMultiplication.dir/matrix_multiplication.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MatrixMultiplication.dir/matrix_multiplication.c.o   -c /home/ahmednaggar19/OS/MatrixMultiplication/matrix_multiplication.c

CMakeFiles/MatrixMultiplication.dir/matrix_multiplication.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MatrixMultiplication.dir/matrix_multiplication.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ahmednaggar19/OS/MatrixMultiplication/matrix_multiplication.c > CMakeFiles/MatrixMultiplication.dir/matrix_multiplication.c.i

CMakeFiles/MatrixMultiplication.dir/matrix_multiplication.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MatrixMultiplication.dir/matrix_multiplication.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ahmednaggar19/OS/MatrixMultiplication/matrix_multiplication.c -o CMakeFiles/MatrixMultiplication.dir/matrix_multiplication.c.s

CMakeFiles/MatrixMultiplication.dir/matrix_multiplication.c.o.requires:

.PHONY : CMakeFiles/MatrixMultiplication.dir/matrix_multiplication.c.o.requires

CMakeFiles/MatrixMultiplication.dir/matrix_multiplication.c.o.provides: CMakeFiles/MatrixMultiplication.dir/matrix_multiplication.c.o.requires
	$(MAKE) -f CMakeFiles/MatrixMultiplication.dir/build.make CMakeFiles/MatrixMultiplication.dir/matrix_multiplication.c.o.provides.build
.PHONY : CMakeFiles/MatrixMultiplication.dir/matrix_multiplication.c.o.provides

CMakeFiles/MatrixMultiplication.dir/matrix_multiplication.c.o.provides.build: CMakeFiles/MatrixMultiplication.dir/matrix_multiplication.c.o


# Object files for target MatrixMultiplication
MatrixMultiplication_OBJECTS = \
"CMakeFiles/MatrixMultiplication.dir/main.c.o" \
"CMakeFiles/MatrixMultiplication.dir/file_processing.c.o" \
"CMakeFiles/MatrixMultiplication.dir/matrix_multiplication.c.o"

# External object files for target MatrixMultiplication
MatrixMultiplication_EXTERNAL_OBJECTS =

MatrixMultiplication: CMakeFiles/MatrixMultiplication.dir/main.c.o
MatrixMultiplication: CMakeFiles/MatrixMultiplication.dir/file_processing.c.o
MatrixMultiplication: CMakeFiles/MatrixMultiplication.dir/matrix_multiplication.c.o
MatrixMultiplication: CMakeFiles/MatrixMultiplication.dir/build.make
MatrixMultiplication: CMakeFiles/MatrixMultiplication.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ahmednaggar19/OS/MatrixMultiplication/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable MatrixMultiplication"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MatrixMultiplication.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MatrixMultiplication.dir/build: MatrixMultiplication

.PHONY : CMakeFiles/MatrixMultiplication.dir/build

CMakeFiles/MatrixMultiplication.dir/requires: CMakeFiles/MatrixMultiplication.dir/main.c.o.requires
CMakeFiles/MatrixMultiplication.dir/requires: CMakeFiles/MatrixMultiplication.dir/file_processing.c.o.requires
CMakeFiles/MatrixMultiplication.dir/requires: CMakeFiles/MatrixMultiplication.dir/matrix_multiplication.c.o.requires

.PHONY : CMakeFiles/MatrixMultiplication.dir/requires

CMakeFiles/MatrixMultiplication.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MatrixMultiplication.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MatrixMultiplication.dir/clean

CMakeFiles/MatrixMultiplication.dir/depend:
	cd /home/ahmednaggar19/OS/MatrixMultiplication/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ahmednaggar19/OS/MatrixMultiplication /home/ahmednaggar19/OS/MatrixMultiplication /home/ahmednaggar19/OS/MatrixMultiplication/cmake-build-debug /home/ahmednaggar19/OS/MatrixMultiplication/cmake-build-debug /home/ahmednaggar19/OS/MatrixMultiplication/cmake-build-debug/CMakeFiles/MatrixMultiplication.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MatrixMultiplication.dir/depend
