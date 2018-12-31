# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/dani/Soft/Window/Windows-CalcEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dani/Soft/Window/Windows-CalcEngine

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/local/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/local/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/local/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/local/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/local/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components

.PHONY : list_install_components/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/local/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/local/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/dani/Soft/Window/Windows-CalcEngine/CMakeFiles /home/dani/Soft/Window/Windows-CalcEngine/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/dani/Soft/Window/Windows-CalcEngine/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named FenestrationCommon

# Build rule for target.
FenestrationCommon: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 FenestrationCommon
.PHONY : FenestrationCommon

# fast build rule for target.
FenestrationCommon/fast:
	$(MAKE) -f src/Common/CMakeFiles/FenestrationCommon.dir/build.make src/Common/CMakeFiles/FenestrationCommon.dir/build
.PHONY : FenestrationCommon/fast

#=============================================================================
# Target rules for targets named Gases

# Build rule for target.
Gases: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Gases
.PHONY : Gases

# fast build rule for target.
Gases/fast:
	$(MAKE) -f src/Gases/CMakeFiles/Gases.dir/build.make src/Gases/CMakeFiles/Gases.dir/build
.PHONY : Gases/fast

#=============================================================================
# Target rules for targets named BPPGasLib

# Build rule for target.
BPPGasLib: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 BPPGasLib
.PHONY : BPPGasLib

# fast build rule for target.
BPPGasLib/fast:
	$(MAKE) -f src/Gases/CMakeFiles/BPPGasLib.dir/build.make src/Gases/CMakeFiles/BPPGasLib.dir/build
.PHONY : BPPGasLib/fast

#=============================================================================
# Target rules for targets named Tarcog

# Build rule for target.
Tarcog: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Tarcog
.PHONY : Tarcog

# fast build rule for target.
Tarcog/fast:
	$(MAKE) -f src/Tarcog/CMakeFiles/Tarcog.dir/build.make src/Tarcog/CMakeFiles/Tarcog.dir/build
.PHONY : Tarcog/fast

#=============================================================================
# Target rules for targets named SpectralAveraging

# Build rule for target.
SpectralAveraging: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 SpectralAveraging
.PHONY : SpectralAveraging

# fast build rule for target.
SpectralAveraging/fast:
	$(MAKE) -f src/SpectralAveraging/CMakeFiles/SpectralAveraging.dir/build.make src/SpectralAveraging/CMakeFiles/SpectralAveraging.dir/build
.PHONY : SpectralAveraging/fast

#=============================================================================
# Target rules for targets named Viewer

# Build rule for target.
Viewer: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Viewer
.PHONY : Viewer

# fast build rule for target.
Viewer/fast:
	$(MAKE) -f src/Viewer/CMakeFiles/Viewer.dir/build.make src/Viewer/CMakeFiles/Viewer.dir/build
.PHONY : Viewer/fast

#=============================================================================
# Target rules for targets named SingleLayerOptics

# Build rule for target.
SingleLayerOptics: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 SingleLayerOptics
.PHONY : SingleLayerOptics

# fast build rule for target.
SingleLayerOptics/fast:
	$(MAKE) -f src/SingleLayerOptics/CMakeFiles/SingleLayerOptics.dir/build.make src/SingleLayerOptics/CMakeFiles/SingleLayerOptics.dir/build
.PHONY : SingleLayerOptics/fast

#=============================================================================
# Target rules for targets named MultiLayerOptics

# Build rule for target.
MultiLayerOptics: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 MultiLayerOptics
.PHONY : MultiLayerOptics

# fast build rule for target.
MultiLayerOptics/fast:
	$(MAKE) -f src/MultiLayerOptics/CMakeFiles/MultiLayerOptics.dir/build.make src/MultiLayerOptics/CMakeFiles/MultiLayerOptics.dir/build
.PHONY : MultiLayerOptics/fast

#=============================================================================
# Target rules for targets named Chromogenics

# Build rule for target.
Chromogenics: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Chromogenics
.PHONY : Chromogenics

# fast build rule for target.
Chromogenics/fast:
	$(MAKE) -f src/Chromogenics/CMakeFiles/Chromogenics.dir/build.make src/Chromogenics/CMakeFiles/Chromogenics.dir/build
.PHONY : Chromogenics/fast

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... install/strip"
	@echo "... install/local"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... list_install_components"
	@echo "... install"
	@echo "... FenestrationCommon"
	@echo "... Gases"
	@echo "... BPPGasLib"
	@echo "... Tarcog"
	@echo "... SpectralAveraging"
	@echo "... Viewer"
	@echo "... SingleLayerOptics"
	@echo "... MultiLayerOptics"
	@echo "... Chromogenics"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
