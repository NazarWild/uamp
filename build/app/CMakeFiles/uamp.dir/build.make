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

# Include any dependencies generated for this target.
include app/CMakeFiles/uamp.dir/depend.make

# Include the progress variables for this target.
include app/CMakeFiles/uamp.dir/progress.make

# Include the compile flags for this target's objects.
include app/CMakeFiles/uamp.dir/flags.make

app/CMakeFiles/uamp.dir/uamp_autogen/mocs_compilation.cpp.o: app/CMakeFiles/uamp.dir/flags.make
app/CMakeFiles/uamp.dir/uamp_autogen/mocs_compilation.cpp.o: app/uamp_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/okolevatov/okolevatov/uamp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object app/CMakeFiles/uamp.dir/uamp_autogen/mocs_compilation.cpp.o"
	cd /Users/okolevatov/okolevatov/uamp/build/app && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/uamp.dir/uamp_autogen/mocs_compilation.cpp.o -c /Users/okolevatov/okolevatov/uamp/build/app/uamp_autogen/mocs_compilation.cpp

app/CMakeFiles/uamp.dir/uamp_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uamp.dir/uamp_autogen/mocs_compilation.cpp.i"
	cd /Users/okolevatov/okolevatov/uamp/build/app && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/okolevatov/okolevatov/uamp/build/app/uamp_autogen/mocs_compilation.cpp > CMakeFiles/uamp.dir/uamp_autogen/mocs_compilation.cpp.i

app/CMakeFiles/uamp.dir/uamp_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uamp.dir/uamp_autogen/mocs_compilation.cpp.s"
	cd /Users/okolevatov/okolevatov/uamp/build/app && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/okolevatov/okolevatov/uamp/build/app/uamp_autogen/mocs_compilation.cpp -o CMakeFiles/uamp.dir/uamp_autogen/mocs_compilation.cpp.s

app/CMakeFiles/uamp.dir/main.cpp.o: app/CMakeFiles/uamp.dir/flags.make
app/CMakeFiles/uamp.dir/main.cpp.o: ../app/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/okolevatov/okolevatov/uamp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object app/CMakeFiles/uamp.dir/main.cpp.o"
	cd /Users/okolevatov/okolevatov/uamp/build/app && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/uamp.dir/main.cpp.o -c /Users/okolevatov/okolevatov/uamp/app/main.cpp

app/CMakeFiles/uamp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uamp.dir/main.cpp.i"
	cd /Users/okolevatov/okolevatov/uamp/build/app && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/okolevatov/okolevatov/uamp/app/main.cpp > CMakeFiles/uamp.dir/main.cpp.i

app/CMakeFiles/uamp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uamp.dir/main.cpp.s"
	cd /Users/okolevatov/okolevatov/uamp/build/app && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/okolevatov/okolevatov/uamp/app/main.cpp -o CMakeFiles/uamp.dir/main.cpp.s

# Object files for target uamp
uamp_OBJECTS = \
"CMakeFiles/uamp.dir/uamp_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/uamp.dir/main.cpp.o"

# External object files for target uamp
uamp_EXTERNAL_OBJECTS =

../uamp: app/CMakeFiles/uamp.dir/uamp_autogen/mocs_compilation.cpp.o
../uamp: app/CMakeFiles/uamp.dir/main.cpp.o
../uamp: app/CMakeFiles/uamp.dir/build.make
../uamp: app/src/libliba.a
../uamp: 3dparty/taglib/taglib/libtag.a
../uamp: /Users/okolevatov/.brew/opt/qt/lib/QtWidgets.framework/QtWidgets
../uamp: /Users/okolevatov/.brew/opt/qt/lib/QtMultimedia.framework/QtMultimedia
../uamp: /Users/okolevatov/.brew/opt/qt/lib/QtGui.framework/QtGui
../uamp: /Users/okolevatov/.brew/opt/qt/lib/QtNetwork.framework/QtNetwork
../uamp: /Users/okolevatov/.brew/opt/qt/lib/QtDBus.framework/QtDBus
../uamp: /Users/okolevatov/.brew/opt/qt/lib/QtCore.framework/QtCore
../uamp: /Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/usr/lib/libz.tbd
../uamp: app/CMakeFiles/uamp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/okolevatov/okolevatov/uamp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../../uamp"
	cd /Users/okolevatov/okolevatov/uamp/build/app && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/uamp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
app/CMakeFiles/uamp.dir/build: ../uamp

.PHONY : app/CMakeFiles/uamp.dir/build

app/CMakeFiles/uamp.dir/clean:
	cd /Users/okolevatov/okolevatov/uamp/build/app && $(CMAKE_COMMAND) -P CMakeFiles/uamp.dir/cmake_clean.cmake
.PHONY : app/CMakeFiles/uamp.dir/clean

app/CMakeFiles/uamp.dir/depend:
	cd /Users/okolevatov/okolevatov/uamp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/okolevatov/okolevatov/uamp /Users/okolevatov/okolevatov/uamp/app /Users/okolevatov/okolevatov/uamp/build /Users/okolevatov/okolevatov/uamp/build/app /Users/okolevatov/okolevatov/uamp/build/app/CMakeFiles/uamp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : app/CMakeFiles/uamp.dir/depend
