cmake_minimum_required(VERSION 3.25)
include(FetchContent)

project(Snake)

set(CMAKE_CXX_STANDARD 17)

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    FIND_PACKAGE_ARGS NAMES glfw3
)
FetchContent_MakeAvailable(glfw)

# OpenGL
find_package(OpenGL REQUIRED)

# GLAD
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v2.0.8
)
FetchContent_MakeAvailable(glad)
add_subdirectory("${glad_SOURCE_DIR}/cmake" glad_cmake)
glad_add_library(glad REPRODUCIBLE EXCLUDE_FROM_ALL LOADER API gl:core=4.0)

# GLM
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
        FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(glm)

if (DEFINED glm_SOURCE_DIR)
include_directories("${glm_SOURCE_DIR}")
endif()

if (DEFINED glad_SOURCE_DIR)
include_directories("${glad_SOURCE_DIR}")
endif()

if (DEFINED glfw_SOURCE_DIR)
include_directories("${glfw_SOURCE_DIR}")
endif()

add_subdirectory(Snake)
