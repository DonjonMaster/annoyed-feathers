cmake_minimum_required(VERSION 3.24)

project(annoyed_feathers LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(RAYLIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build/external/raylib-master")
set(RAYLIB_SRC_DIR "${RAYLIB_DIR}/src")

if(NOT EXISTS "${RAYLIB_SRC_DIR}/raylib.h")
    message(FATAL_ERROR "Vendored raylib sources were not found in ${RAYLIB_SRC_DIR}")
endif()

add_library(raylib STATIC
    "${RAYLIB_SRC_DIR}/raudio.c"
    "${RAYLIB_SRC_DIR}/rcore.c"
    "${RAYLIB_SRC_DIR}/rglfw.c"
    "${RAYLIB_SRC_DIR}/rmodels.c"
    "${RAYLIB_SRC_DIR}/rshapes.c"
    "${RAYLIB_SRC_DIR}/rtext.c"
    "${RAYLIB_SRC_DIR}/rtextures.c"
)
target_include_directories(raylib
    PUBLIC "${RAYLIB_SRC_DIR}"
    PRIVATE "${RAYLIB_SRC_DIR}/external/glfw/include"
)
target_compile_definitions(raylib PUBLIC PLATFORM_DESKTOP GRAPHICS_API_OPENGL_33)

if(WIN32)
    target_link_libraries(raylib PUBLIC winmm gdi32 opengl32)
elseif(UNIX AND NOT APPLE)
    find_package(OpenGL REQUIRED)
    find_package(X11 REQUIRED)
    target_compile_definitions(raylib PRIVATE _GLFW_X11)
    target_link_libraries(raylib PUBLIC OpenGL::GL X11::X11 pthread m dl rt)
else()
    message(FATAL_ERROR "This CMake setup currently supports Windows and Linux only.")
endif()

file(GLOB_RECURSE CYCLONE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/Cyclone/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Cyclone/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Cyclone/include/*.hpp"
)
add_library(Cyclone STATIC ${CYCLONE_SOURCES})
target_include_directories(Cyclone PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/Cyclone/include"
)

file(GLOB_RECURSE SIEGELAB_CORE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/SiegeLabCore/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/SiegeLabCore/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/SiegeLabCore/*.hpp"
)
add_library(SiegeLabCore STATIC ${SIEGELAB_CORE_SOURCES})
target_include_directories(SiegeLabCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(SiegeLabCore PUBLIC Cyclone raylib)

add_executable(annoyed-feathers src/main.cpp)
target_include_directories(annoyed-feathers PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(annoyed-feathers PRIVATE SiegeLabCore raylib)

if(WIN32)
    target_sources(annoyed-feathers PRIVATE src/application.rc)
endif()

add_custom_command(TARGET annoyed-feathers POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/resources"
        "$<TARGET_FILE_DIR:annoyed-feathers>/resources"
)

include(CTest)
if(BUILD_TESTING)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
        GIT_SHALLOW TRUE
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_executable(SiegeLabTests SiegeLabTests/test.cpp)
    target_link_libraries(SiegeLabTests PRIVATE SiegeLabCore GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(SiegeLabTests)
endif()
