# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 4.0

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "F:\stacje radarowe\stacje_radarowe"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "F:\stacje radarowe\stacje_radarowe\build"

# Include any dependencies generated for this target.
include CMakeFiles/tests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/tests.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/tests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tests.dir/flags.make

tests_autogen/timestamp: F:/qt/6.9.0/mingw_64/bin/moc.exe
tests_autogen/timestamp: F:/qt/6.9.0/mingw_64/bin/uic.exe
tests_autogen/timestamp: CMakeFiles/tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir="F:\stacje radarowe\stacje_radarowe\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target tests"
	"C:\Program Files\CMake\bin\cmake.exe" -E cmake_autogen "F:/stacje radarowe/stacje_radarowe/build/CMakeFiles/tests_autogen.dir/AutogenInfo.json" ""
	"C:\Program Files\CMake\bin\cmake.exe" -E touch "F:/stacje radarowe/stacje_radarowe/build/tests_autogen/timestamp"

CMakeFiles/tests.dir/codegen:
.PHONY : CMakeFiles/tests.dir/codegen

CMakeFiles/tests.dir/tests_autogen/mocs_compilation.cpp.obj: CMakeFiles/tests.dir/flags.make
CMakeFiles/tests.dir/tests_autogen/mocs_compilation.cpp.obj: CMakeFiles/tests.dir/includes_CXX.rsp
CMakeFiles/tests.dir/tests_autogen/mocs_compilation.cpp.obj: tests_autogen/mocs_compilation.cpp
CMakeFiles/tests.dir/tests_autogen/mocs_compilation.cpp.obj: CMakeFiles/tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="F:\stacje radarowe\stacje_radarowe\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tests.dir/tests_autogen/mocs_compilation.cpp.obj"
	F:\qt\Tools\mingw1310_64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tests.dir/tests_autogen/mocs_compilation.cpp.obj -MF CMakeFiles\tests.dir\tests_autogen\mocs_compilation.cpp.obj.d -o CMakeFiles\tests.dir\tests_autogen\mocs_compilation.cpp.obj -c "F:\stacje radarowe\stacje_radarowe\build\tests_autogen\mocs_compilation.cpp"

CMakeFiles/tests.dir/tests_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tests.dir/tests_autogen/mocs_compilation.cpp.i"
	F:\qt\Tools\mingw1310_64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "F:\stacje radarowe\stacje_radarowe\build\tests_autogen\mocs_compilation.cpp" > CMakeFiles\tests.dir\tests_autogen\mocs_compilation.cpp.i

CMakeFiles/tests.dir/tests_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tests.dir/tests_autogen/mocs_compilation.cpp.s"
	F:\qt\Tools\mingw1310_64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "F:\stacje radarowe\stacje_radarowe\build\tests_autogen\mocs_compilation.cpp" -o CMakeFiles\tests.dir\tests_autogen\mocs_compilation.cpp.s

CMakeFiles/tests.dir/tests/test_main.cpp.obj: CMakeFiles/tests.dir/flags.make
CMakeFiles/tests.dir/tests/test_main.cpp.obj: CMakeFiles/tests.dir/includes_CXX.rsp
CMakeFiles/tests.dir/tests/test_main.cpp.obj: F:/stacje\ radarowe/stacje_radarowe/tests/test_main.cpp
CMakeFiles/tests.dir/tests/test_main.cpp.obj: CMakeFiles/tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="F:\stacje radarowe\stacje_radarowe\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/tests.dir/tests/test_main.cpp.obj"
	F:\qt\Tools\mingw1310_64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tests.dir/tests/test_main.cpp.obj -MF CMakeFiles\tests.dir\tests\test_main.cpp.obj.d -o CMakeFiles\tests.dir\tests\test_main.cpp.obj -c "F:\stacje radarowe\stacje_radarowe\tests\test_main.cpp"

CMakeFiles/tests.dir/tests/test_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/tests.dir/tests/test_main.cpp.i"
	F:\qt\Tools\mingw1310_64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "F:\stacje radarowe\stacje_radarowe\tests\test_main.cpp" > CMakeFiles\tests.dir\tests\test_main.cpp.i

CMakeFiles/tests.dir/tests/test_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/tests.dir/tests/test_main.cpp.s"
	F:\qt\Tools\mingw1310_64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "F:\stacje radarowe\stacje_radarowe\tests\test_main.cpp" -o CMakeFiles\tests.dir\tests\test_main.cpp.s

# Object files for target tests
tests_OBJECTS = \
"CMakeFiles/tests.dir/tests_autogen/mocs_compilation.cpp.obj" \
"CMakeFiles/tests.dir/tests/test_main.cpp.obj"

# External object files for target tests
tests_EXTERNAL_OBJECTS =

tests.exe: CMakeFiles/tests.dir/tests_autogen/mocs_compilation.cpp.obj
tests.exe: CMakeFiles/tests.dir/tests/test_main.cpp.obj
tests.exe: CMakeFiles/tests.dir/build.make
tests.exe: libmainwindow_lib.a
tests.exe: F:/qt/6.9.0/mingw_64/lib/libQt6Network.a
tests.exe: F:/qt/6.9.0/mingw_64/lib/libQt6Charts.a
tests.exe: F:/stacje\ radarowe/googletest/build/lib/libgtest.a
tests.exe: F:/stacje\ radarowe/googletest/build/lib/libgtest_main.a
tests.exe: F:/stacje\ radarowe/googletest/build/lib/libgmock.a
tests.exe: F:/stacje\ radarowe/googletest/build/lib/libgmock_main.a
tests.exe: F:/qt/6.9.0/mingw_64/lib/libQt6OpenGLWidgets.a
tests.exe: F:/qt/6.9.0/mingw_64/lib/libQt6Widgets.a
tests.exe: F:/qt/6.9.0/mingw_64/lib/libQt6OpenGL.a
tests.exe: F:/qt/6.9.0/mingw_64/lib/libQt6Gui.a
tests.exe: F:/qt/6.9.0/mingw_64/lib/libQt6Core.a
tests.exe: CMakeFiles/tests.dir/linkLibs.rsp
tests.exe: CMakeFiles/tests.dir/objects1.rsp
tests.exe: CMakeFiles/tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="F:\stacje radarowe\stacje_radarowe\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable tests.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\tests.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tests.dir/build: tests.exe
.PHONY : CMakeFiles/tests.dir/build

CMakeFiles/tests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\tests.dir\cmake_clean.cmake
.PHONY : CMakeFiles/tests.dir/clean

CMakeFiles/tests.dir/depend: tests_autogen/timestamp
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "F:\stacje radarowe\stacje_radarowe" "F:\stacje radarowe\stacje_radarowe" "F:\stacje radarowe\stacje_radarowe\build" "F:\stacje radarowe\stacje_radarowe\build" "F:\stacje radarowe\stacje_radarowe\build\CMakeFiles\tests.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/tests.dir/depend

