# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.2.6\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.2.6\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\lorenzodentis\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\3 pacchetto\lab09\Es9_1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\lorenzodentis\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\3 pacchetto\lab09\Es9_1\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Es9_1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Es9_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Es9_1.dir/flags.make

CMakeFiles/Es9_1.dir/main.c.obj: CMakeFiles/Es9_1.dir/flags.make
CMakeFiles/Es9_1.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\lorenzodentis\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\3 pacchetto\lab09\Es9_1\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Es9_1.dir/main.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Es9_1.dir\main.c.obj   -c "C:\Users\lorenzodentis\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\3 pacchetto\lab09\Es9_1\main.c"

CMakeFiles/Es9_1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Es9_1.dir/main.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\lorenzodentis\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\3 pacchetto\lab09\Es9_1\main.c" > CMakeFiles\Es9_1.dir\main.c.i

CMakeFiles/Es9_1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Es9_1.dir/main.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\lorenzodentis\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\3 pacchetto\lab09\Es9_1\main.c" -o CMakeFiles\Es9_1.dir\main.c.s

# Object files for target Es9_1
Es9_1_OBJECTS = \
"CMakeFiles/Es9_1.dir/main.c.obj"

# External object files for target Es9_1
Es9_1_EXTERNAL_OBJECTS =

Es9_1.exe: CMakeFiles/Es9_1.dir/main.c.obj
Es9_1.exe: CMakeFiles/Es9_1.dir/build.make
Es9_1.exe: CMakeFiles/Es9_1.dir/linklibs.rsp
Es9_1.exe: CMakeFiles/Es9_1.dir/objects1.rsp
Es9_1.exe: CMakeFiles/Es9_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\lorenzodentis\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\3 pacchetto\lab09\Es9_1\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Es9_1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Es9_1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Es9_1.dir/build: Es9_1.exe

.PHONY : CMakeFiles/Es9_1.dir/build

CMakeFiles/Es9_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Es9_1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Es9_1.dir/clean

CMakeFiles/Es9_1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\lorenzodentis\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\3 pacchetto\lab09\Es9_1" "C:\Users\lorenzodentis\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\3 pacchetto\lab09\Es9_1" "C:\Users\lorenzodentis\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\3 pacchetto\lab09\Es9_1\cmake-build-debug" "C:\Users\lorenzodentis\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\3 pacchetto\lab09\Es9_1\cmake-build-debug" "C:\Users\lorenzodentis\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\3 pacchetto\lab09\Es9_1\cmake-build-debug\CMakeFiles\Es9_1.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Es9_1.dir/depend

