# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.2.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\lory9\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\lab 4\ES 4_5"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\lory9\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\lab 4\ES 4_5\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/untitled.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/untitled.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/untitled.dir/flags.make

CMakeFiles/untitled.dir/main.c.obj: CMakeFiles/untitled.dir/flags.make
CMakeFiles/untitled.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\lory9\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\lab 4\ES 4_5\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/untitled.dir/main.c.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\untitled.dir\main.c.obj   -c "C:\Users\lory9\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\lab 4\ES 4_5\main.c"

CMakeFiles/untitled.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/untitled.dir/main.c.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\lory9\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\lab 4\ES 4_5\main.c" > CMakeFiles\untitled.dir\main.c.i

CMakeFiles/untitled.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/untitled.dir/main.c.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\lory9\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\lab 4\ES 4_5\main.c" -o CMakeFiles\untitled.dir\main.c.s

# Object files for target untitled
untitled_OBJECTS = \
"CMakeFiles/untitled.dir/main.c.obj"

# External object files for target untitled
untitled_EXTERNAL_OBJECTS =

untitled.exe: CMakeFiles/untitled.dir/main.c.obj
untitled.exe: CMakeFiles/untitled.dir/build.make
untitled.exe: CMakeFiles/untitled.dir/linklibs.rsp
untitled.exe: CMakeFiles/untitled.dir/objects1.rsp
untitled.exe: CMakeFiles/untitled.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\lory9\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\lab 4\ES 4_5\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable untitled.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\untitled.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/untitled.dir/build: untitled.exe

.PHONY : CMakeFiles/untitled.dir/build

CMakeFiles/untitled.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\untitled.dir\cmake_clean.cmake
.PHONY : CMakeFiles/untitled.dir/clean

CMakeFiles/untitled.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\lory9\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\lab 4\ES 4_5" "C:\Users\lory9\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\lab 4\ES 4_5" "C:\Users\lory9\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\lab 4\ES 4_5\cmake-build-debug" "C:\Users\lory9\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\lab 4\ES 4_5\cmake-build-debug" "C:\Users\lory9\OneDrive - Politecnico di Torino - IT\Attachments\scuola\algoritmi e programmazione\workspace\lab 4\ES 4_5\cmake-build-debug\CMakeFiles\untitled.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/untitled.dir/depend

