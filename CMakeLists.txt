cmake_minimum_required(VERSION 3.20)
project(mocapviewer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(FetchContent)

# GLFW
# find_package(GLFW3 REQUIRED)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.3.8
)

FetchContent_MakeAvailable(glfw)

# OpenGL
find_package(OpenGL REQUIRED)

# Assimp
# find_package(assimp REQUIRED)

# FetchContent_Declare(
#   assimp
#   GIT_REPOSITORY https://github.com/assimp/assimp.git
#   GIT_TAG v5.2.5
# )

# FetchContent_MakeAvailable(assimp)

# ImGui
add_subdirectory(external/imgui)

target_include_directories(imgui PUBLIC ${glfw_SOURCE_DIR}/include)

# Source files
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h src/*.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${GLFW3_INCLUDE_DIR}
    ${ASSIMP_INCLUDE_DIR}
    ${GLM_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    glfw
    glad
    imgui
    OpenGL::GL
)

add_library(glad src/glad.c)
target_include_directories(glad PUBLIC include)
target_link_libraries(${PROJECT_NAME} glad)

# Cross platform support
if (WIN32)
    # Windows specific
elseif(UNIX)
    # Linux specific
    target_link_libraries(${PROJECT_NAME} pthread)
endif()