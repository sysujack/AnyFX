#-------------------------------------------------------------------------------
# anyfx
#-------------------------------------------------------------------------------
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(ANYFX_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})

IF(NOT DEFINED ANYFX_FOLDER)
	SET(ANYFX_FOLDER "anyfx")
ENDIF()

SET(ANYFX_VULKAN_EXTERNAL ON)

SET(ANYFX_GLEW_EXTERNAL ON)
IF(NOT DEFINED ANYFX_GLEW_FOLDER)
	SET(ANYFX_GLEW_FOLDER ${ANYFX_SOURCE_DIR}/exts/glew)
	SET(ANYFX_GLEW_EXTERNAL OFF)
ENDIF()

INCLUDE(macros.cmake)
PROJECT(AnyFX)

IF (WIN32)
	SET(OPENGL_LIBS glu32.lib opengl32.lib)
ELSEIF(APPLE)
	LINK_DIRECTORIES(/System/Library/Frameworks /usr/X11R6/lib /opt/local/lib)
	INCLUDE_DIRECTORIES(/System/Library/Frameworks /usr/X11R6/include /opt/local/include)
	FIND_PACKAGE(OpenGL REQUIRED)
	INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
	SET(OPENGL_LIBS ${OPENGL_LIBRARIES} X11)
ELSEIF(UNIX)
	SET(OPENGL_LIBS GL X11)
ENDIF()

# set compiler definitions
IF(WIN32)
	ADD_DEFINITIONS(-D__WIN32__)
ELSEIF(APPLE)
	ADD_DEFINITIONS(-D__APPLE__)
ELSEIF(UNIX)
	ADD_DEFINITIONS(-D__UNIX__)
ENDIF()

IF(MSVC)
	ADD_DEFINITIONS(-D__MSVC__)
ELSEIF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	ADD_DEFINITIONS(-D__GNUCXX__)
ENDIF()

OPTION(ANYFX_BUILD_DEMO "Build AnyFX Demo" OFF)
OPTION(ANYFX_BUILD_COMPILER_LIBRARY "Build AnyFX Compiler as a library" ON)
OPTION(ANYFX_TRANSPOSE_MATRICES "Builds AnyFX with automatic matrix transposing for variables")
ADD_SUBDIRECTORY(compiler)
ADD_SUBDIRECTORY(api)
ADD_SUBDIRECTORY(util)
ADD_SUBDIRECTORY(exts/eastl)
ADD_SUBDIRECTORY(exts/glslang)

IF (NOT ANYFX_VULKAN_EXTERNAL)
	INCLUDE_DIRECTORIES(exts/vulkan/src/vulkan)
	SET_TARGET_PROPERTIES(vulkan PROPERTIES FOLDER ${ANYFX_FOLDER}/exts)
ENDIF()
IF (NOT ANYFX_GLEW_EXTERNAL)
	ADD_SUBDIRECTORY(exts/glew)
	SET_TARGET_PROPERTIES(glew PROPERTIES FOLDER ${ANYFX_FOLDER}/exts)
ENDIF()

# set target subdirs
SET_TARGET_PROPERTIES(compiler PROPERTIES FOLDER ${ANYFX_FOLDER})
SET_TARGET_PROPERTIES(mcpp PROPERTIES FOLDER ${ANYFX_FOLDER})
SET_TARGET_PROPERTIES(antlr PROPERTIES FOLDER ${ANYFX_FOLDER})
SET_TARGET_PROPERTIES(api PROPERTIES FOLDER ${ANYFX_FOLDER})
SET_TARGET_PROPERTIES(util PROPERTIES FOLDER ${ANYFX_FOLDER})
SET_TARGET_PROPERTIES(EASTL PROPERTIES FOLDER ${ANYFX_FOLDER})

# set khronos compiler folders
SET_TARGET_PROPERTIES(glslang PROPERTIES FOLDER ${ANYFX_FOLDER}/khronos)
SET_TARGET_PROPERTIES(glslangValidator PROPERTIES FOLDER ${ANYFX_FOLDER}/khronos)
SET_TARGET_PROPERTIES(OGLCompiler PROPERTIES FOLDER ${ANYFX_FOLDER}/khronos)
SET_TARGET_PROPERTIES(OSDependent PROPERTIES FOLDER ${ANYFX_FOLDER}/khronos)
SET_TARGET_PROPERTIES(SPIRV PROPERTIES FOLDER ${ANYFX_FOLDER}/khronos)
SET_TARGET_PROPERTIES(spirv-remap PROPERTIES FOLDER ${ANYFX_FOLDER}/khronos)

IF(ANYFX_TRANSPOSE_MATRICES)
	ADD_DEFINITIONS(-D__ANYFX_TRANSPOSE_MATRIX__)
ENDIF()

IF(ANYFX_BUILD_DEMO)
	ADD_SUBDIRECTORY(demo)
	SET_TARGET_PROPERTIES(demo PROPERTIES FOLDER ${ANYFX_FOLDER})
ENDIF()

