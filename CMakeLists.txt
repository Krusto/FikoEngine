cmake_minimum_required(VERSION 3.21)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/scripts/vcpkg-master/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/scripts/vcpkg-master/installed/x64-windows/share")

project(FIKO_ENGINE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_GENERATOR_PLATFORM x64)
message("Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

message("Finding assimp...")
find_package(assimp REQUIRED)
message("Finding glfw3...")
find_package(glfw3 CONFIG REQUIRED)

file(GLOB_RECURSE GLAD_SOURCE_FILES ./vendor/glad/src/*.c)
file(GLOB_RECURSE GLAD_HEADER_FILES ./vendor/glad/src/*.h)

file(GLOB_RECURSE IMGUI_SOURCE_FILES imgui_impl_vulkan.cpp imgui_impl_opengl3.cpp imgui_impl_glfw.cpp imgui.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp )
file(GLOB_RECURSE IMGUI_HEADER_FILES imgui_impl_vulkan.h   imgui_impl_opengl3.h imgui_impl_glfw.h   imgui.h imconfig.h imgui_internal.h imstb_rectpack.h imstb_textedit.h imstb_truetype.h)

file(GLOB_RECURSE SOURCE_FILES ./src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ./src/*.h)

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


add_compile_definitions(GLFW_EXPOSE_NATIVE_WIN32)
add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)

set(GLAD_INCLDUE_DIR           "./vendor/glad/include")
set(VULKAN_INCLUDE_DIR         "C:/VulkanSDK/1.3.216.0/Include")
set(GLM_INCLUDE_DIR            "./vendor/glm")
set(IMGUI_INCLUDE_DIR          "./vendor/imgui")
set(IMGUI_BACKENDS_INCLUDE_DIR "./vendor/imgui/backends")
set(ENTT_INCLUDE_DIR           "./vendor/entt/single_include")

file(GLOB_RECURSE GLM_SOURCES ${GLM_INCLUDE_DIR}/glm/*.cpp)
file(GLOB_RECURSE GLM_HEADER ${GLM_INCLUDE_DIR}/glm/*.cpp)
file(GLOB_RECURSE GLM_INLINE ${GLM_INCLUDE_DIR}/glm/*.cpp)

add_library(imgui STATIC ${IMGUI_SOURCE_FILES} ${IMGUI_HEADER_FILES})
add_library(glad SHARED ${GLAD_SOURCE_FILES} ${GLAD_HEADER_FILES})
add_library(glm SHARED ${GLM_SOURCES} ${GLM_HEADER} ${GLM_INLINE})

add_executable(FikoEngine ${SOURCE_FILES} ${HEADER_FILES})

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(FikoEngine PRIVATE -static-libstdc++)
    target_compile_options(FikoEngine PRIVATE -Wno-volatile)
    target_compile_options(FikoEngine PRIVATE -Wno-delete-incomplete)
    target_compile_options(FikoEngine PRIVATE -Wno-int-to-pointer-cast)
endif()

target_include_directories(glm PRIVATE ${GLM_INCLUDE_DIR})

target_include_directories(glad PRIVATE ${GLAD_INCLDUE_DIR})

target_include_directories(imgui PRIVATE ${VULKAN_INCLUDE_DIR})
target_include_directories(imgui PRIVATE ${IMGUI_INCLUDE_DIR})
target_include_directories(imgui PRIVATE ${IMGUI_BACKENDS_INCLUDE_DIR})
target_include_directories(imgui PRIVATE ${GLFW_INCLUDE_DIR})

target_include_directories(FikoEngine PRIVATE "./src")
target_include_directories(FikoEngine PRIVATE ${GLAD_INCLDUE_DIR})
target_include_directories(FikoEngine PRIVATE ${VULKAN_INCLUDE_DIR})
target_include_directories(FikoEngine PRIVATE ${GLM_INCLUDE_DIR})
target_include_directories(FikoEngine PRIVATE ${IMGUI_INCLUDE_DIR})
target_include_directories(FikoEngine PRIVATE ${IMGUI_BACKENDS_INCLUDE_DIR})
target_include_directories(FikoEngine PRIVATE ${ENTT_INCLUDE_DIR})

target_link_libraries(imgui PRIVATE C:/VulkanSDK/1.3.216.0/Lib/vulkan-1.lib)
target_link_libraries(imgui PRIVATE glfw)
target_link_libraries(imgui PRIVATE glad)

target_link_libraries(FikoEngine PRIVATE C:/VulkanSDK/1.3.216.0/Lib/vulkan-1.lib)
target_link_libraries(FikoEngine PRIVATE glm)
target_link_libraries(FikoEngine PRIVATE glfw)
target_link_libraries(FikoEngine PRIVATE assimp::assimp)
target_link_libraries(FikoEngine PRIVATE imgui)
target_link_libraries(FikoEngine PRIVATE glad)

target_precompile_headers(FikoEngine PRIVATE ${CMAKE_SOURCE_DIR}/src/Core/pch.hpp)