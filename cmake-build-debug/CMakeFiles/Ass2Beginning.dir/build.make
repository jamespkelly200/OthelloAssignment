# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\James Kelly\CLionProjects\SoftwareEngineeringProject1\Ass2Beginning"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\James Kelly\CLionProjects\SoftwareEngineeringProject1\Ass2Beginning\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Ass2Beginning.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Ass2Beginning.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Ass2Beginning.dir/flags.make

CMakeFiles/Ass2Beginning.dir/main.c.obj: CMakeFiles/Ass2Beginning.dir/flags.make
CMakeFiles/Ass2Beginning.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\James Kelly\CLionProjects\SoftwareEngineeringProject1\Ass2Beginning\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Ass2Beginning.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Ass2Beginning.dir\main.c.obj   -c "C:\Users\James Kelly\CLionProjects\SoftwareEngineeringProject1\Ass2Beginning\main.c"

CMakeFiles/Ass2Beginning.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Ass2Beginning.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\James Kelly\CLionProjects\SoftwareEngineeringProject1\Ass2Beginning\main.c" > CMakeFiles\Ass2Beginning.dir\main.c.i

CMakeFiles/Ass2Beginning.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Ass2Beginning.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\James Kelly\CLionProjects\SoftwareEngineeringProject1\Ass2Beginning\main.c" -o CMakeFiles\Ass2Beginning.dir\main.c.s

# Object files for target Ass2Beginning
Ass2Beginning_OBJECTS = \
"CMakeFiles/Ass2Beginning.dir/main.c.obj"

# External object files for target Ass2Beginning
Ass2Beginning_EXTERNAL_OBJECTS =

Ass2Beginning.exe: CMakeFiles/Ass2Beginning.dir/main.c.obj
Ass2Beginning.exe: CMakeFiles/Ass2Beginning.dir/build.make
Ass2Beginning.exe: CMakeFiles/Ass2Beginning.dir/linklibs.rsp
Ass2Beginning.exe: CMakeFiles/Ass2Beginning.dir/objects1.rsp
Ass2Beginning.exe: CMakeFiles/Ass2Beginning.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\James Kelly\CLionProjects\SoftwareEngineeringProject1\Ass2Beginning\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Ass2Beginning.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Ass2Beginning.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Ass2Beginning.dir/build: Ass2Beginning.exe

.PHONY : CMakeFiles/Ass2Beginning.dir/build

CMakeFiles/Ass2Beginning.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Ass2Beginning.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Ass2Beginning.dir/clean

CMakeFiles/Ass2Beginning.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\James Kelly\CLionProjects\SoftwareEngineeringProject1\Ass2Beginning" "C:\Users\James Kelly\CLionProjects\SoftwareEngineeringProject1\Ass2Beginning" "C:\Users\James Kelly\CLionProjects\SoftwareEngineeringProject1\Ass2Beginning\cmake-build-debug" "C:\Users\James Kelly\CLionProjects\SoftwareEngineeringProject1\Ass2Beginning\cmake-build-debug" "C:\Users\James Kelly\CLionProjects\SoftwareEngineeringProject1\Ass2Beginning\cmake-build-debug\CMakeFiles\Ass2Beginning.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Ass2Beginning.dir/depend

