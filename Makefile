# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.25.0/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.25.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mcong/zpr-project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mcong/zpr-project

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target test
test:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running tests..."
	/opt/homebrew/Cellar/cmake/3.25.0/bin/ctest --force-new-ctest-process $(ARGS)
.PHONY : test

# Special rule for the target test
test/fast: test
.PHONY : test/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/opt/homebrew/Cellar/cmake/3.25.0/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/opt/homebrew/Cellar/cmake/3.25.0/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/mcong/zpr-project/CMakeFiles /Users/mcong/zpr-project//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/mcong/zpr-project/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named zpr_sync

# Build rule for target.
zpr_sync: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 zpr_sync
.PHONY : zpr_sync

# fast build rule for target.
zpr_sync/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zpr_sync.dir/build.make CMakeFiles/zpr_sync.dir/build
.PHONY : zpr_sync/fast

#=============================================================================
# Target rules for targets named runUnitTests

# Build rule for target.
runUnitTests: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 runUnitTests
.PHONY : runUnitTests

# fast build rule for target.
runUnitTests/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/runUnitTests.dir/build.make CMakeFiles/runUnitTests.dir/build
.PHONY : runUnitTests/fast

#=============================================================================
# Target rules for targets named docs

# Build rule for target.
docs: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 docs
.PHONY : docs

# fast build rule for target.
docs/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/docs.dir/build.make CMakeFiles/docs.dir/build
.PHONY : docs/fast

src/main.o: src/main.cc.o
.PHONY : src/main.o

# target to build an object file
src/main.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zpr_sync.dir/build.make CMakeFiles/zpr_sync.dir/src/main.cc.o
.PHONY : src/main.cc.o

src/main.i: src/main.cc.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zpr_sync.dir/build.make CMakeFiles/zpr_sync.dir/src/main.cc.i
.PHONY : src/main.cc.i

src/main.s: src/main.cc.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zpr_sync.dir/build.make CMakeFiles/zpr_sync.dir/src/main.cc.s
.PHONY : src/main.cc.s

src/zpr_sync/Connection.o: src/zpr_sync/Connection.cc.o
.PHONY : src/zpr_sync/Connection.o

# target to build an object file
src/zpr_sync/Connection.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zpr_sync.dir/build.make CMakeFiles/zpr_sync.dir/src/zpr_sync/Connection.cc.o
.PHONY : src/zpr_sync/Connection.cc.o

src/zpr_sync/Connection.i: src/zpr_sync/Connection.cc.i
.PHONY : src/zpr_sync/Connection.i

# target to preprocess a source file
src/zpr_sync/Connection.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zpr_sync.dir/build.make CMakeFiles/zpr_sync.dir/src/zpr_sync/Connection.cc.i
.PHONY : src/zpr_sync/Connection.cc.i

src/zpr_sync/Connection.s: src/zpr_sync/Connection.cc.s
.PHONY : src/zpr_sync/Connection.s

# target to generate assembly for a file
src/zpr_sync/Connection.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/zpr_sync.dir/build.make CMakeFiles/zpr_sync.dir/src/zpr_sync/Connection.cc.s
.PHONY : src/zpr_sync/Connection.cc.s

test/test-test.o: test/test-test.cc.o
.PHONY : test/test-test.o

# target to build an object file
test/test-test.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/runUnitTests.dir/build.make CMakeFiles/runUnitTests.dir/test/test-test.cc.o
.PHONY : test/test-test.cc.o

test/test-test.i: test/test-test.cc.i
.PHONY : test/test-test.i

# target to preprocess a source file
test/test-test.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/runUnitTests.dir/build.make CMakeFiles/runUnitTests.dir/test/test-test.cc.i
.PHONY : test/test-test.cc.i

test/test-test.s: test/test-test.cc.s
.PHONY : test/test-test.s

# target to generate assembly for a file
test/test-test.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/runUnitTests.dir/build.make CMakeFiles/runUnitTests.dir/test/test-test.cc.s
.PHONY : test/test-test.cc.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... test"
	@echo "... docs"
	@echo "... runUnitTests"
	@echo "... zpr_sync"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/zpr_sync/Connection.o"
	@echo "... src/zpr_sync/Connection.i"
	@echo "... src/zpr_sync/Connection.s"
	@echo "... test/test-test.o"
	@echo "... test/test-test.i"
	@echo "... test/test-test.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
