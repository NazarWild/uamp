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
CMAKE_COMMAND = /Users/okolevatov/.brew/Cellar/cmake/3.18.2/bin/cmake

# The command to remove a file.
RM = /Users/okolevatov/.brew/Cellar/cmake/3.18.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/okolevatov/okolevatov/uamp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/okolevatov/okolevatov/uamp/build

# Utility rule file for uamp_autogen.

# Include the progress variables for this target.
include app/CMakeFiles/uamp_autogen.dir/progress.make

app/CMakeFiles/uamp_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/okolevatov/okolevatov/uamp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target uamp"
	cd /Users/okolevatov/okolevatov/uamp/build/app && /Users/okolevatov/.brew/Cellar/cmake/3.18.2/bin/cmake -E cmake_autogen /Users/okolevatov/okolevatov/uamp/build/app/CMakeFiles/uamp_autogen.dir/AutogenInfo.json ""

uamp_autogen: app/CMakeFiles/uamp_autogen
uamp_autogen: app/CMakeFiles/uamp_autogen.dir/build.make

.PHONY : uamp_autogen

# Rule to build all files generated by this target.
app/CMakeFiles/uamp_autogen.dir/build: uamp_autogen

.PHONY : app/CMakeFiles/uamp_autogen.dir/build

app/CMakeFiles/uamp_autogen.dir/clean:
	cd /Users/okolevatov/okolevatov/uamp/build/app && $(CMAKE_COMMAND) -P CMakeFiles/uamp_autogen.dir/cmake_clean.cmake
.PHONY : app/CMakeFiles/uamp_autogen.dir/clean

app/CMakeFiles/uamp_autogen.dir/depend:
	cd /Users/okolevatov/okolevatov/uamp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/okolevatov/okolevatov/uamp /Users/okolevatov/okolevatov/uamp/app /Users/okolevatov/okolevatov/uamp/build /Users/okolevatov/okolevatov/uamp/build/app /Users/okolevatov/okolevatov/uamp/build/app/CMakeFiles/uamp_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : app/CMakeFiles/uamp_autogen.dir/depend

