# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.10

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.1.6\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.1.6\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\vlad\CLionProjects\Second_middle_temperature

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\vlad\CLionProjects\Second_middle_temperature\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Second_middle_temperature.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Second_middle_temperature.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Second_middle_temperature.dir/flags.make

CMakeFiles/Second_middle_temperature.dir/main.cpp.obj: CMakeFiles/Second_middle_temperature.dir/flags.make
CMakeFiles/Second_middle_temperature.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\vlad\CLionProjects\Second_middle_temperature\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Second_middle_temperature.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Second_middle_temperature.dir\main.cpp.obj -c C:\Users\vlad\CLionProjects\Second_middle_temperature\main.cpp

CMakeFiles/Second_middle_temperature.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Second_middle_temperature.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\vlad\CLionProjects\Second_middle_temperature\main.cpp > CMakeFiles\Second_middle_temperature.dir\main.cpp.i

CMakeFiles/Second_middle_temperature.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Second_middle_temperature.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\vlad\CLionProjects\Second_middle_temperature\main.cpp -o CMakeFiles\Second_middle_temperature.dir\main.cpp.s

CMakeFiles/Second_middle_temperature.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/Second_middle_temperature.dir/main.cpp.obj.requires

CMakeFiles/Second_middle_temperature.dir/main.cpp.obj.provides: CMakeFiles/Second_middle_temperature.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\Second_middle_temperature.dir\build.make CMakeFiles/Second_middle_temperature.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/Second_middle_temperature.dir/main.cpp.obj.provides

CMakeFiles/Second_middle_temperature.dir/main.cpp.obj.provides.build: CMakeFiles/Second_middle_temperature.dir/main.cpp.obj


# Object files for target Second_middle_temperature
Second_middle_temperature_OBJECTS = \
"CMakeFiles/Second_middle_temperature.dir/main.cpp.obj"

# External object files for target Second_middle_temperature
Second_middle_temperature_EXTERNAL_OBJECTS =

Second_middle_temperature.exe: CMakeFiles/Second_middle_temperature.dir/main.cpp.obj
Second_middle_temperature.exe: CMakeFiles/Second_middle_temperature.dir/build.make
Second_middle_temperature.exe: CMakeFiles/Second_middle_temperature.dir/linklibs.rsp
Second_middle_temperature.exe: CMakeFiles/Second_middle_temperature.dir/objects1.rsp
Second_middle_temperature.exe: CMakeFiles/Second_middle_temperature.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\vlad\CLionProjects\Second_middle_temperature\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Second_middle_temperature.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Second_middle_temperature.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Second_middle_temperature.dir/build: Second_middle_temperature.exe

.PHONY : CMakeFiles/Second_middle_temperature.dir/build

CMakeFiles/Second_middle_temperature.dir/requires: CMakeFiles/Second_middle_temperature.dir/main.cpp.obj.requires

.PHONY : CMakeFiles/Second_middle_temperature.dir/requires

CMakeFiles/Second_middle_temperature.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Second_middle_temperature.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Second_middle_temperature.dir/clean

CMakeFiles/Second_middle_temperature.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\vlad\CLionProjects\Second_middle_temperature C:\Users\vlad\CLionProjects\Second_middle_temperature C:\Users\vlad\CLionProjects\Second_middle_temperature\cmake-build-debug C:\Users\vlad\CLionProjects\Second_middle_temperature\cmake-build-debug C:\Users\vlad\CLionProjects\Second_middle_temperature\cmake-build-debug\CMakeFiles\Second_middle_temperature.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Second_middle_temperature.dir/depend

