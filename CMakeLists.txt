cmake_minimum_required(VERSION 3.22)
project(FIKO_ENGINE)

add_subdirectory(Vendor/glfw)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_GENERATOR_PLATFORM x64)

file(GLOB_RECURSE SOURCE_FILES ./src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ./src/*.h)

message("Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

set (EXCLUDE_DIR "/Vendor/")
foreach (TMP_PATH ${SOURCE_FILES})
    string (FIND ${TMP_PATH} ${EXCLUDE_DIR} EXCLUDE_DIR_FOUND)
    if (NOT ${EXCLUDE_DIR_FOUND} EQUAL -1)
        list (REMOVE_ITEM SOURCE_FILES ${TMP_PATH})
    endif ()
endforeach(TMP_PATH)
foreach (TMP_PATH ${HEADER_FILES})
    string (FIND ${TMP_PATH} ${EXCLUDE_DIR} EXCLUDE_DIR_FOUND)
    if (NOT ${EXCLUDE_DIR_FOUND} EQUAL -1)
        list (REMOVE_ITEM HEADER_FILES ${TMP_PATH})
    endif ()
endforeach(TMP_PATH)

add_executable(FIKO_ENGINE ${SOURCE_FILES} ${HEADER_FILES})

include_directories(FIKO_ENGINE Vendor/glfw/include)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Debug!")
    target_link_libraries(FIKO_ENGINE ${CMAKE_SOURCE_DIR}/Vendor/glfw/src/Release/glfw3.lib)
endif()
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Release!")
    target_link_libraries(FIKO_ENGINE ${CMAKE_SOURCE_DIR}/Vendor/glfw/src/Release/glfw3.lib)
endif()
