# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = E:\Projects\FikoEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\Projects\FikoEngine\build\minSizeRel

# Include any dependencies generated for this target.
include Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/compiler_depend.make

# Include the progress variables for this target.
include Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/progress.make

# Include the compile flags for this target's objects.
include Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/flags.make

Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.obj: Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/flags.make
Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.obj: Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/includes_CXX.rsp
Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.obj: ../../Vendor/yaml-cpp/util/sandbox.cpp
Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.obj: Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Projects\FikoEngine\build\minSizeRel\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.obj"
	cd /d E:\Projects\FikoEngine\build\minSizeRel\Vendor\yaml-cpp\util && D:\w64devkit\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.obj -MF CMakeFiles\yaml-cpp-sandbox.dir\sandbox.cpp.obj.d -o CMakeFiles\yaml-cpp-sandbox.dir\sandbox.cpp.obj -c E:\Projects\FikoEngine\Vendor\yaml-cpp\util\sandbox.cpp

Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.i"
	cd /d E:\Projects\FikoEngine\build\minSizeRel\Vendor\yaml-cpp\util && D:\w64devkit\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Projects\FikoEngine\Vendor\yaml-cpp\util\sandbox.cpp > CMakeFiles\yaml-cpp-sandbox.dir\sandbox.cpp.i

Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.s"
	cd /d E:\Projects\FikoEngine\build\minSizeRel\Vendor\yaml-cpp\util && D:\w64devkit\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Projects\FikoEngine\Vendor\yaml-cpp\util\sandbox.cpp -o CMakeFiles\yaml-cpp-sandbox.dir\sandbox.cpp.s

# Object files for target yaml-cpp-sandbox
yaml__cpp__sandbox_OBJECTS = \
"CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.obj"

# External object files for target yaml-cpp-sandbox
yaml__cpp__sandbox_EXTERNAL_OBJECTS =

Vendor/yaml-cpp/util/sandbox.exe: Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.obj
Vendor/yaml-cpp/util/sandbox.exe: Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/build.make
Vendor/yaml-cpp/util/sandbox.exe: Vendor/yaml-cpp/libyaml-cpp.a
Vendor/yaml-cpp/util/sandbox.exe: Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/linklibs.rsp
Vendor/yaml-cpp/util/sandbox.exe: Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/objects1.rsp
Vendor/yaml-cpp/util/sandbox.exe: Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\Projects\FikoEngine\build\minSizeRel\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sandbox.exe"
	cd /d E:\Projects\FikoEngine\build\minSizeRel\Vendor\yaml-cpp\util && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\yaml-cpp-sandbox.dir\link.txt --verbose=$(VERBOSE)
	cd /d E:\Projects\FikoEngine\build\minSizeRel\Vendor\yaml-cpp\util && C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe -noprofile -executionpolicy Bypass -file E:/Projects/FikoEngine/scripts/vcpkg-master/scripts/buildsystems/msbuild/applocal.ps1 -targetBinary E:/Projects/FikoEngine/build/minSizeRel/Vendor/yaml-cpp/util/sandbox.exe -installedDir E:/Projects/FikoEngine/scripts/vcpkg-master/installed/x64-windows/bin -OutVariable out

# Rule to build all files generated by this target.
Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/build: Vendor/yaml-cpp/util/sandbox.exe
.PHONY : Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/build

Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/clean:
	cd /d E:\Projects\FikoEngine\build\minSizeRel\Vendor\yaml-cpp\util && $(CMAKE_COMMAND) -P CMakeFiles\yaml-cpp-sandbox.dir\cmake_clean.cmake
.PHONY : Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/clean

Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Projects\FikoEngine E:\Projects\FikoEngine\Vendor\yaml-cpp\util E:\Projects\FikoEngine\build\minSizeRel E:\Projects\FikoEngine\build\minSizeRel\Vendor\yaml-cpp\util E:\Projects\FikoEngine\build\minSizeRel\Vendor\yaml-cpp\util\CMakeFiles\yaml-cpp-sandbox.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : Vendor/yaml-cpp/util/CMakeFiles/yaml-cpp-sandbox.dir/depend
