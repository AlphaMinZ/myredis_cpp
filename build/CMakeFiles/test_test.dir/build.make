# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mz/workspace/CPP/myredis_cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mz/workspace/CPP/myredis_cpp/build

# Include any dependencies generated for this target.
include CMakeFiles/test_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_test.dir/flags.make

CMakeFiles/test_test.dir/tests/test.cc.o: CMakeFiles/test_test.dir/flags.make
CMakeFiles/test_test.dir/tests/test.cc.o: ../tests/test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mz/workspace/CPP/myredis_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_test.dir/tests/test.cc.o"
	/opt/rh/devtoolset-8/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_test.dir/tests/test.cc.o -c /home/mz/workspace/CPP/myredis_cpp/tests/test.cc

CMakeFiles/test_test.dir/tests/test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_test.dir/tests/test.cc.i"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mz/workspace/CPP/myredis_cpp/tests/test.cc > CMakeFiles/test_test.dir/tests/test.cc.i

CMakeFiles/test_test.dir/tests/test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_test.dir/tests/test.cc.s"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mz/workspace/CPP/myredis_cpp/tests/test.cc -o CMakeFiles/test_test.dir/tests/test.cc.s

CMakeFiles/test_test.dir/tests/test.cc.o.requires:

.PHONY : CMakeFiles/test_test.dir/tests/test.cc.o.requires

CMakeFiles/test_test.dir/tests/test.cc.o.provides: CMakeFiles/test_test.dir/tests/test.cc.o.requires
	$(MAKE) -f CMakeFiles/test_test.dir/build.make CMakeFiles/test_test.dir/tests/test.cc.o.provides.build
.PHONY : CMakeFiles/test_test.dir/tests/test.cc.o.provides

CMakeFiles/test_test.dir/tests/test.cc.o.provides.build: CMakeFiles/test_test.dir/tests/test.cc.o


CMakeFiles/test_test.dir/myredis/database/executor.cc.o: CMakeFiles/test_test.dir/flags.make
CMakeFiles/test_test.dir/myredis/database/executor.cc.o: ../myredis/database/executor.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mz/workspace/CPP/myredis_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test_test.dir/myredis/database/executor.cc.o"
	/opt/rh/devtoolset-8/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_test.dir/myredis/database/executor.cc.o -c /home/mz/workspace/CPP/myredis_cpp/myredis/database/executor.cc

CMakeFiles/test_test.dir/myredis/database/executor.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_test.dir/myredis/database/executor.cc.i"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mz/workspace/CPP/myredis_cpp/myredis/database/executor.cc > CMakeFiles/test_test.dir/myredis/database/executor.cc.i

CMakeFiles/test_test.dir/myredis/database/executor.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_test.dir/myredis/database/executor.cc.s"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mz/workspace/CPP/myredis_cpp/myredis/database/executor.cc -o CMakeFiles/test_test.dir/myredis/database/executor.cc.s

CMakeFiles/test_test.dir/myredis/database/executor.cc.o.requires:

.PHONY : CMakeFiles/test_test.dir/myredis/database/executor.cc.o.requires

CMakeFiles/test_test.dir/myredis/database/executor.cc.o.provides: CMakeFiles/test_test.dir/myredis/database/executor.cc.o.requires
	$(MAKE) -f CMakeFiles/test_test.dir/build.make CMakeFiles/test_test.dir/myredis/database/executor.cc.o.provides.build
.PHONY : CMakeFiles/test_test.dir/myredis/database/executor.cc.o.provides

CMakeFiles/test_test.dir/myredis/database/executor.cc.o.provides.build: CMakeFiles/test_test.dir/myredis/database/executor.cc.o


CMakeFiles/test_test.dir/myredis/database/trigger.cc.o: CMakeFiles/test_test.dir/flags.make
CMakeFiles/test_test.dir/myredis/database/trigger.cc.o: ../myredis/database/trigger.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mz/workspace/CPP/myredis_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/test_test.dir/myredis/database/trigger.cc.o"
	/opt/rh/devtoolset-8/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_test.dir/myredis/database/trigger.cc.o -c /home/mz/workspace/CPP/myredis_cpp/myredis/database/trigger.cc

CMakeFiles/test_test.dir/myredis/database/trigger.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_test.dir/myredis/database/trigger.cc.i"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mz/workspace/CPP/myredis_cpp/myredis/database/trigger.cc > CMakeFiles/test_test.dir/myredis/database/trigger.cc.i

CMakeFiles/test_test.dir/myredis/database/trigger.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_test.dir/myredis/database/trigger.cc.s"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mz/workspace/CPP/myredis_cpp/myredis/database/trigger.cc -o CMakeFiles/test_test.dir/myredis/database/trigger.cc.s

CMakeFiles/test_test.dir/myredis/database/trigger.cc.o.requires:

.PHONY : CMakeFiles/test_test.dir/myredis/database/trigger.cc.o.requires

CMakeFiles/test_test.dir/myredis/database/trigger.cc.o.provides: CMakeFiles/test_test.dir/myredis/database/trigger.cc.o.requires
	$(MAKE) -f CMakeFiles/test_test.dir/build.make CMakeFiles/test_test.dir/myredis/database/trigger.cc.o.provides.build
.PHONY : CMakeFiles/test_test.dir/myredis/database/trigger.cc.o.provides

CMakeFiles/test_test.dir/myredis/database/trigger.cc.o.provides.build: CMakeFiles/test_test.dir/myredis/database/trigger.cc.o


CMakeFiles/test_test.dir/myredis/datastore/expire.cc.o: CMakeFiles/test_test.dir/flags.make
CMakeFiles/test_test.dir/myredis/datastore/expire.cc.o: ../myredis/datastore/expire.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mz/workspace/CPP/myredis_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/test_test.dir/myredis/datastore/expire.cc.o"
	/opt/rh/devtoolset-8/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_test.dir/myredis/datastore/expire.cc.o -c /home/mz/workspace/CPP/myredis_cpp/myredis/datastore/expire.cc

CMakeFiles/test_test.dir/myredis/datastore/expire.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_test.dir/myredis/datastore/expire.cc.i"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mz/workspace/CPP/myredis_cpp/myredis/datastore/expire.cc > CMakeFiles/test_test.dir/myredis/datastore/expire.cc.i

CMakeFiles/test_test.dir/myredis/datastore/expire.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_test.dir/myredis/datastore/expire.cc.s"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mz/workspace/CPP/myredis_cpp/myredis/datastore/expire.cc -o CMakeFiles/test_test.dir/myredis/datastore/expire.cc.s

CMakeFiles/test_test.dir/myredis/datastore/expire.cc.o.requires:

.PHONY : CMakeFiles/test_test.dir/myredis/datastore/expire.cc.o.requires

CMakeFiles/test_test.dir/myredis/datastore/expire.cc.o.provides: CMakeFiles/test_test.dir/myredis/datastore/expire.cc.o.requires
	$(MAKE) -f CMakeFiles/test_test.dir/build.make CMakeFiles/test_test.dir/myredis/datastore/expire.cc.o.provides.build
.PHONY : CMakeFiles/test_test.dir/myredis/datastore/expire.cc.o.provides

CMakeFiles/test_test.dir/myredis/datastore/expire.cc.o.provides.build: CMakeFiles/test_test.dir/myredis/datastore/expire.cc.o


CMakeFiles/test_test.dir/myredis/datastore/hash.cc.o: CMakeFiles/test_test.dir/flags.make
CMakeFiles/test_test.dir/myredis/datastore/hash.cc.o: ../myredis/datastore/hash.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mz/workspace/CPP/myredis_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/test_test.dir/myredis/datastore/hash.cc.o"
	/opt/rh/devtoolset-8/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_test.dir/myredis/datastore/hash.cc.o -c /home/mz/workspace/CPP/myredis_cpp/myredis/datastore/hash.cc

CMakeFiles/test_test.dir/myredis/datastore/hash.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_test.dir/myredis/datastore/hash.cc.i"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mz/workspace/CPP/myredis_cpp/myredis/datastore/hash.cc > CMakeFiles/test_test.dir/myredis/datastore/hash.cc.i

CMakeFiles/test_test.dir/myredis/datastore/hash.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_test.dir/myredis/datastore/hash.cc.s"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mz/workspace/CPP/myredis_cpp/myredis/datastore/hash.cc -o CMakeFiles/test_test.dir/myredis/datastore/hash.cc.s

CMakeFiles/test_test.dir/myredis/datastore/hash.cc.o.requires:

.PHONY : CMakeFiles/test_test.dir/myredis/datastore/hash.cc.o.requires

CMakeFiles/test_test.dir/myredis/datastore/hash.cc.o.provides: CMakeFiles/test_test.dir/myredis/datastore/hash.cc.o.requires
	$(MAKE) -f CMakeFiles/test_test.dir/build.make CMakeFiles/test_test.dir/myredis/datastore/hash.cc.o.provides.build
.PHONY : CMakeFiles/test_test.dir/myredis/datastore/hash.cc.o.provides

CMakeFiles/test_test.dir/myredis/datastore/hash.cc.o.provides.build: CMakeFiles/test_test.dir/myredis/datastore/hash.cc.o


CMakeFiles/test_test.dir/myredis/datastore/list.cc.o: CMakeFiles/test_test.dir/flags.make
CMakeFiles/test_test.dir/myredis/datastore/list.cc.o: ../myredis/datastore/list.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mz/workspace/CPP/myredis_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/test_test.dir/myredis/datastore/list.cc.o"
	/opt/rh/devtoolset-8/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_test.dir/myredis/datastore/list.cc.o -c /home/mz/workspace/CPP/myredis_cpp/myredis/datastore/list.cc

CMakeFiles/test_test.dir/myredis/datastore/list.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_test.dir/myredis/datastore/list.cc.i"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mz/workspace/CPP/myredis_cpp/myredis/datastore/list.cc > CMakeFiles/test_test.dir/myredis/datastore/list.cc.i

CMakeFiles/test_test.dir/myredis/datastore/list.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_test.dir/myredis/datastore/list.cc.s"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mz/workspace/CPP/myredis_cpp/myredis/datastore/list.cc -o CMakeFiles/test_test.dir/myredis/datastore/list.cc.s

CMakeFiles/test_test.dir/myredis/datastore/list.cc.o.requires:

.PHONY : CMakeFiles/test_test.dir/myredis/datastore/list.cc.o.requires

CMakeFiles/test_test.dir/myredis/datastore/list.cc.o.provides: CMakeFiles/test_test.dir/myredis/datastore/list.cc.o.requires
	$(MAKE) -f CMakeFiles/test_test.dir/build.make CMakeFiles/test_test.dir/myredis/datastore/list.cc.o.provides.build
.PHONY : CMakeFiles/test_test.dir/myredis/datastore/list.cc.o.provides

CMakeFiles/test_test.dir/myredis/datastore/list.cc.o.provides.build: CMakeFiles/test_test.dir/myredis/datastore/list.cc.o


CMakeFiles/test_test.dir/myredis/datastore/set.cc.o: CMakeFiles/test_test.dir/flags.make
CMakeFiles/test_test.dir/myredis/datastore/set.cc.o: ../myredis/datastore/set.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mz/workspace/CPP/myredis_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/test_test.dir/myredis/datastore/set.cc.o"
	/opt/rh/devtoolset-8/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_test.dir/myredis/datastore/set.cc.o -c /home/mz/workspace/CPP/myredis_cpp/myredis/datastore/set.cc

CMakeFiles/test_test.dir/myredis/datastore/set.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_test.dir/myredis/datastore/set.cc.i"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mz/workspace/CPP/myredis_cpp/myredis/datastore/set.cc > CMakeFiles/test_test.dir/myredis/datastore/set.cc.i

CMakeFiles/test_test.dir/myredis/datastore/set.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_test.dir/myredis/datastore/set.cc.s"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mz/workspace/CPP/myredis_cpp/myredis/datastore/set.cc -o CMakeFiles/test_test.dir/myredis/datastore/set.cc.s

CMakeFiles/test_test.dir/myredis/datastore/set.cc.o.requires:

.PHONY : CMakeFiles/test_test.dir/myredis/datastore/set.cc.o.requires

CMakeFiles/test_test.dir/myredis/datastore/set.cc.o.provides: CMakeFiles/test_test.dir/myredis/datastore/set.cc.o.requires
	$(MAKE) -f CMakeFiles/test_test.dir/build.make CMakeFiles/test_test.dir/myredis/datastore/set.cc.o.provides.build
.PHONY : CMakeFiles/test_test.dir/myredis/datastore/set.cc.o.provides

CMakeFiles/test_test.dir/myredis/datastore/set.cc.o.provides.build: CMakeFiles/test_test.dir/myredis/datastore/set.cc.o


CMakeFiles/test_test.dir/myredis/datastore/sorted_set.cc.o: CMakeFiles/test_test.dir/flags.make
CMakeFiles/test_test.dir/myredis/datastore/sorted_set.cc.o: ../myredis/datastore/sorted_set.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mz/workspace/CPP/myredis_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/test_test.dir/myredis/datastore/sorted_set.cc.o"
	/opt/rh/devtoolset-8/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_test.dir/myredis/datastore/sorted_set.cc.o -c /home/mz/workspace/CPP/myredis_cpp/myredis/datastore/sorted_set.cc

CMakeFiles/test_test.dir/myredis/datastore/sorted_set.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_test.dir/myredis/datastore/sorted_set.cc.i"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mz/workspace/CPP/myredis_cpp/myredis/datastore/sorted_set.cc > CMakeFiles/test_test.dir/myredis/datastore/sorted_set.cc.i

CMakeFiles/test_test.dir/myredis/datastore/sorted_set.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_test.dir/myredis/datastore/sorted_set.cc.s"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mz/workspace/CPP/myredis_cpp/myredis/datastore/sorted_set.cc -o CMakeFiles/test_test.dir/myredis/datastore/sorted_set.cc.s

CMakeFiles/test_test.dir/myredis/datastore/sorted_set.cc.o.requires:

.PHONY : CMakeFiles/test_test.dir/myredis/datastore/sorted_set.cc.o.requires

CMakeFiles/test_test.dir/myredis/datastore/sorted_set.cc.o.provides: CMakeFiles/test_test.dir/myredis/datastore/sorted_set.cc.o.requires
	$(MAKE) -f CMakeFiles/test_test.dir/build.make CMakeFiles/test_test.dir/myredis/datastore/sorted_set.cc.o.provides.build
.PHONY : CMakeFiles/test_test.dir/myredis/datastore/sorted_set.cc.o.provides

CMakeFiles/test_test.dir/myredis/datastore/sorted_set.cc.o.provides.build: CMakeFiles/test_test.dir/myredis/datastore/sorted_set.cc.o


CMakeFiles/test_test.dir/myredis/datastore/string.cc.o: CMakeFiles/test_test.dir/flags.make
CMakeFiles/test_test.dir/myredis/datastore/string.cc.o: ../myredis/datastore/string.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mz/workspace/CPP/myredis_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/test_test.dir/myredis/datastore/string.cc.o"
	/opt/rh/devtoolset-8/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_test.dir/myredis/datastore/string.cc.o -c /home/mz/workspace/CPP/myredis_cpp/myredis/datastore/string.cc

CMakeFiles/test_test.dir/myredis/datastore/string.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_test.dir/myredis/datastore/string.cc.i"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mz/workspace/CPP/myredis_cpp/myredis/datastore/string.cc > CMakeFiles/test_test.dir/myredis/datastore/string.cc.i

CMakeFiles/test_test.dir/myredis/datastore/string.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_test.dir/myredis/datastore/string.cc.s"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mz/workspace/CPP/myredis_cpp/myredis/datastore/string.cc -o CMakeFiles/test_test.dir/myredis/datastore/string.cc.s

CMakeFiles/test_test.dir/myredis/datastore/string.cc.o.requires:

.PHONY : CMakeFiles/test_test.dir/myredis/datastore/string.cc.o.requires

CMakeFiles/test_test.dir/myredis/datastore/string.cc.o.provides: CMakeFiles/test_test.dir/myredis/datastore/string.cc.o.requires
	$(MAKE) -f CMakeFiles/test_test.dir/build.make CMakeFiles/test_test.dir/myredis/datastore/string.cc.o.provides.build
.PHONY : CMakeFiles/test_test.dir/myredis/datastore/string.cc.o.provides

CMakeFiles/test_test.dir/myredis/datastore/string.cc.o.provides.build: CMakeFiles/test_test.dir/myredis/datastore/string.cc.o


CMakeFiles/test_test.dir/myredis/handler/handler.cc.o: CMakeFiles/test_test.dir/flags.make
CMakeFiles/test_test.dir/myredis/handler/handler.cc.o: ../myredis/handler/handler.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mz/workspace/CPP/myredis_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/test_test.dir/myredis/handler/handler.cc.o"
	/opt/rh/devtoolset-8/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_test.dir/myredis/handler/handler.cc.o -c /home/mz/workspace/CPP/myredis_cpp/myredis/handler/handler.cc

CMakeFiles/test_test.dir/myredis/handler/handler.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_test.dir/myredis/handler/handler.cc.i"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mz/workspace/CPP/myredis_cpp/myredis/handler/handler.cc > CMakeFiles/test_test.dir/myredis/handler/handler.cc.i

CMakeFiles/test_test.dir/myredis/handler/handler.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_test.dir/myredis/handler/handler.cc.s"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mz/workspace/CPP/myredis_cpp/myredis/handler/handler.cc -o CMakeFiles/test_test.dir/myredis/handler/handler.cc.s

CMakeFiles/test_test.dir/myredis/handler/handler.cc.o.requires:

.PHONY : CMakeFiles/test_test.dir/myredis/handler/handler.cc.o.requires

CMakeFiles/test_test.dir/myredis/handler/handler.cc.o.provides: CMakeFiles/test_test.dir/myredis/handler/handler.cc.o.requires
	$(MAKE) -f CMakeFiles/test_test.dir/build.make CMakeFiles/test_test.dir/myredis/handler/handler.cc.o.provides.build
.PHONY : CMakeFiles/test_test.dir/myredis/handler/handler.cc.o.provides

CMakeFiles/test_test.dir/myredis/handler/handler.cc.o.provides.build: CMakeFiles/test_test.dir/myredis/handler/handler.cc.o


CMakeFiles/test_test.dir/myredis/handler/reply.cc.o: CMakeFiles/test_test.dir/flags.make
CMakeFiles/test_test.dir/myredis/handler/reply.cc.o: ../myredis/handler/reply.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mz/workspace/CPP/myredis_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/test_test.dir/myredis/handler/reply.cc.o"
	/opt/rh/devtoolset-8/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_test.dir/myredis/handler/reply.cc.o -c /home/mz/workspace/CPP/myredis_cpp/myredis/handler/reply.cc

CMakeFiles/test_test.dir/myredis/handler/reply.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_test.dir/myredis/handler/reply.cc.i"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mz/workspace/CPP/myredis_cpp/myredis/handler/reply.cc > CMakeFiles/test_test.dir/myredis/handler/reply.cc.i

CMakeFiles/test_test.dir/myredis/handler/reply.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_test.dir/myredis/handler/reply.cc.s"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mz/workspace/CPP/myredis_cpp/myredis/handler/reply.cc -o CMakeFiles/test_test.dir/myredis/handler/reply.cc.s

CMakeFiles/test_test.dir/myredis/handler/reply.cc.o.requires:

.PHONY : CMakeFiles/test_test.dir/myredis/handler/reply.cc.o.requires

CMakeFiles/test_test.dir/myredis/handler/reply.cc.o.provides: CMakeFiles/test_test.dir/myredis/handler/reply.cc.o.requires
	$(MAKE) -f CMakeFiles/test_test.dir/build.make CMakeFiles/test_test.dir/myredis/handler/reply.cc.o.provides.build
.PHONY : CMakeFiles/test_test.dir/myredis/handler/reply.cc.o.provides

CMakeFiles/test_test.dir/myredis/handler/reply.cc.o.provides.build: CMakeFiles/test_test.dir/myredis/handler/reply.cc.o


CMakeFiles/test_test.dir/myredis/persist/file_io.cc.o: CMakeFiles/test_test.dir/flags.make
CMakeFiles/test_test.dir/myredis/persist/file_io.cc.o: ../myredis/persist/file_io.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mz/workspace/CPP/myredis_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/test_test.dir/myredis/persist/file_io.cc.o"
	/opt/rh/devtoolset-8/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_test.dir/myredis/persist/file_io.cc.o -c /home/mz/workspace/CPP/myredis_cpp/myredis/persist/file_io.cc

CMakeFiles/test_test.dir/myredis/persist/file_io.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_test.dir/myredis/persist/file_io.cc.i"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mz/workspace/CPP/myredis_cpp/myredis/persist/file_io.cc > CMakeFiles/test_test.dir/myredis/persist/file_io.cc.i

CMakeFiles/test_test.dir/myredis/persist/file_io.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_test.dir/myredis/persist/file_io.cc.s"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mz/workspace/CPP/myredis_cpp/myredis/persist/file_io.cc -o CMakeFiles/test_test.dir/myredis/persist/file_io.cc.s

CMakeFiles/test_test.dir/myredis/persist/file_io.cc.o.requires:

.PHONY : CMakeFiles/test_test.dir/myredis/persist/file_io.cc.o.requires

CMakeFiles/test_test.dir/myredis/persist/file_io.cc.o.provides: CMakeFiles/test_test.dir/myredis/persist/file_io.cc.o.requires
	$(MAKE) -f CMakeFiles/test_test.dir/build.make CMakeFiles/test_test.dir/myredis/persist/file_io.cc.o.provides.build
.PHONY : CMakeFiles/test_test.dir/myredis/persist/file_io.cc.o.provides

CMakeFiles/test_test.dir/myredis/persist/file_io.cc.o.provides.build: CMakeFiles/test_test.dir/myredis/persist/file_io.cc.o


CMakeFiles/test_test.dir/myredis/protocol/parser.cc.o: CMakeFiles/test_test.dir/flags.make
CMakeFiles/test_test.dir/myredis/protocol/parser.cc.o: ../myredis/protocol/parser.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mz/workspace/CPP/myredis_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/test_test.dir/myredis/protocol/parser.cc.o"
	/opt/rh/devtoolset-8/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_test.dir/myredis/protocol/parser.cc.o -c /home/mz/workspace/CPP/myredis_cpp/myredis/protocol/parser.cc

CMakeFiles/test_test.dir/myredis/protocol/parser.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_test.dir/myredis/protocol/parser.cc.i"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mz/workspace/CPP/myredis_cpp/myredis/protocol/parser.cc > CMakeFiles/test_test.dir/myredis/protocol/parser.cc.i

CMakeFiles/test_test.dir/myredis/protocol/parser.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_test.dir/myredis/protocol/parser.cc.s"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mz/workspace/CPP/myredis_cpp/myredis/protocol/parser.cc -o CMakeFiles/test_test.dir/myredis/protocol/parser.cc.s

CMakeFiles/test_test.dir/myredis/protocol/parser.cc.o.requires:

.PHONY : CMakeFiles/test_test.dir/myredis/protocol/parser.cc.o.requires

CMakeFiles/test_test.dir/myredis/protocol/parser.cc.o.provides: CMakeFiles/test_test.dir/myredis/protocol/parser.cc.o.requires
	$(MAKE) -f CMakeFiles/test_test.dir/build.make CMakeFiles/test_test.dir/myredis/protocol/parser.cc.o.provides.build
.PHONY : CMakeFiles/test_test.dir/myredis/protocol/parser.cc.o.provides

CMakeFiles/test_test.dir/myredis/protocol/parser.cc.o.provides.build: CMakeFiles/test_test.dir/myredis/protocol/parser.cc.o


CMakeFiles/test_test.dir/myredis/server/server.cc.o: CMakeFiles/test_test.dir/flags.make
CMakeFiles/test_test.dir/myredis/server/server.cc.o: ../myredis/server/server.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mz/workspace/CPP/myredis_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/test_test.dir/myredis/server/server.cc.o"
	/opt/rh/devtoolset-8/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_test.dir/myredis/server/server.cc.o -c /home/mz/workspace/CPP/myredis_cpp/myredis/server/server.cc

CMakeFiles/test_test.dir/myredis/server/server.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_test.dir/myredis/server/server.cc.i"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mz/workspace/CPP/myredis_cpp/myredis/server/server.cc > CMakeFiles/test_test.dir/myredis/server/server.cc.i

CMakeFiles/test_test.dir/myredis/server/server.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_test.dir/myredis/server/server.cc.s"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mz/workspace/CPP/myredis_cpp/myredis/server/server.cc -o CMakeFiles/test_test.dir/myredis/server/server.cc.s

CMakeFiles/test_test.dir/myredis/server/server.cc.o.requires:

.PHONY : CMakeFiles/test_test.dir/myredis/server/server.cc.o.requires

CMakeFiles/test_test.dir/myredis/server/server.cc.o.provides: CMakeFiles/test_test.dir/myredis/server/server.cc.o.requires
	$(MAKE) -f CMakeFiles/test_test.dir/build.make CMakeFiles/test_test.dir/myredis/server/server.cc.o.provides.build
.PHONY : CMakeFiles/test_test.dir/myredis/server/server.cc.o.provides

CMakeFiles/test_test.dir/myredis/server/server.cc.o.provides.build: CMakeFiles/test_test.dir/myredis/server/server.cc.o


# Object files for target test_test
test_test_OBJECTS = \
"CMakeFiles/test_test.dir/tests/test.cc.o" \
"CMakeFiles/test_test.dir/myredis/database/executor.cc.o" \
"CMakeFiles/test_test.dir/myredis/database/trigger.cc.o" \
"CMakeFiles/test_test.dir/myredis/datastore/expire.cc.o" \
"CMakeFiles/test_test.dir/myredis/datastore/hash.cc.o" \
"CMakeFiles/test_test.dir/myredis/datastore/list.cc.o" \
"CMakeFiles/test_test.dir/myredis/datastore/set.cc.o" \
"CMakeFiles/test_test.dir/myredis/datastore/sorted_set.cc.o" \
"CMakeFiles/test_test.dir/myredis/datastore/string.cc.o" \
"CMakeFiles/test_test.dir/myredis/handler/handler.cc.o" \
"CMakeFiles/test_test.dir/myredis/handler/reply.cc.o" \
"CMakeFiles/test_test.dir/myredis/persist/file_io.cc.o" \
"CMakeFiles/test_test.dir/myredis/protocol/parser.cc.o" \
"CMakeFiles/test_test.dir/myredis/server/server.cc.o"

# External object files for target test_test
test_test_EXTERNAL_OBJECTS =

../bin/test_test: CMakeFiles/test_test.dir/tests/test.cc.o
../bin/test_test: CMakeFiles/test_test.dir/myredis/database/executor.cc.o
../bin/test_test: CMakeFiles/test_test.dir/myredis/database/trigger.cc.o
../bin/test_test: CMakeFiles/test_test.dir/myredis/datastore/expire.cc.o
../bin/test_test: CMakeFiles/test_test.dir/myredis/datastore/hash.cc.o
../bin/test_test: CMakeFiles/test_test.dir/myredis/datastore/list.cc.o
../bin/test_test: CMakeFiles/test_test.dir/myredis/datastore/set.cc.o
../bin/test_test: CMakeFiles/test_test.dir/myredis/datastore/sorted_set.cc.o
../bin/test_test: CMakeFiles/test_test.dir/myredis/datastore/string.cc.o
../bin/test_test: CMakeFiles/test_test.dir/myredis/handler/handler.cc.o
../bin/test_test: CMakeFiles/test_test.dir/myredis/handler/reply.cc.o
../bin/test_test: CMakeFiles/test_test.dir/myredis/persist/file_io.cc.o
../bin/test_test: CMakeFiles/test_test.dir/myredis/protocol/parser.cc.o
../bin/test_test: CMakeFiles/test_test.dir/myredis/server/server.cc.o
../bin/test_test: CMakeFiles/test_test.dir/build.make
../bin/test_test: /usr/lib64/libz.so
../bin/test_test: /usr/lib64/libssl.so
../bin/test_test: /usr/lib64/libcrypto.so
../bin/test_test: CMakeFiles/test_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mz/workspace/CPP/myredis_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Linking CXX executable ../bin/test_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_test.dir/build: ../bin/test_test

.PHONY : CMakeFiles/test_test.dir/build

CMakeFiles/test_test.dir/requires: CMakeFiles/test_test.dir/tests/test.cc.o.requires
CMakeFiles/test_test.dir/requires: CMakeFiles/test_test.dir/myredis/database/executor.cc.o.requires
CMakeFiles/test_test.dir/requires: CMakeFiles/test_test.dir/myredis/database/trigger.cc.o.requires
CMakeFiles/test_test.dir/requires: CMakeFiles/test_test.dir/myredis/datastore/expire.cc.o.requires
CMakeFiles/test_test.dir/requires: CMakeFiles/test_test.dir/myredis/datastore/hash.cc.o.requires
CMakeFiles/test_test.dir/requires: CMakeFiles/test_test.dir/myredis/datastore/list.cc.o.requires
CMakeFiles/test_test.dir/requires: CMakeFiles/test_test.dir/myredis/datastore/set.cc.o.requires
CMakeFiles/test_test.dir/requires: CMakeFiles/test_test.dir/myredis/datastore/sorted_set.cc.o.requires
CMakeFiles/test_test.dir/requires: CMakeFiles/test_test.dir/myredis/datastore/string.cc.o.requires
CMakeFiles/test_test.dir/requires: CMakeFiles/test_test.dir/myredis/handler/handler.cc.o.requires
CMakeFiles/test_test.dir/requires: CMakeFiles/test_test.dir/myredis/handler/reply.cc.o.requires
CMakeFiles/test_test.dir/requires: CMakeFiles/test_test.dir/myredis/persist/file_io.cc.o.requires
CMakeFiles/test_test.dir/requires: CMakeFiles/test_test.dir/myredis/protocol/parser.cc.o.requires
CMakeFiles/test_test.dir/requires: CMakeFiles/test_test.dir/myredis/server/server.cc.o.requires

.PHONY : CMakeFiles/test_test.dir/requires

CMakeFiles/test_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_test.dir/clean

CMakeFiles/test_test.dir/depend:
	cd /home/mz/workspace/CPP/myredis_cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mz/workspace/CPP/myredis_cpp /home/mz/workspace/CPP/myredis_cpp /home/mz/workspace/CPP/myredis_cpp/build /home/mz/workspace/CPP/myredis_cpp/build /home/mz/workspace/CPP/myredis_cpp/build/CMakeFiles/test_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_test.dir/depend

