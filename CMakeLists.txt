cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/scripts/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/scripts/vcpkg/installed/x64-mingw-static/share")

project(FIKO_ENGINE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_GENERATOR_PLATFORM x64)
message("Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

message("${PROJECT_NAME}: Finding assimp...")
find_package(assimp REQUIRED)
message("${PROJECT_NAME}: Finding glfw3...")
find_package(glfw3 CONFIG REQUIRED)
message("${PROJECT_NAME}: Finding glm...")
find_package(glm CONFIG REQUIRED)
message("${PROJECT_NAME}: Adding yaml-cpp...")
add_subdirectory("${CMAKE_SOURCE_DIR}/Vendor/yaml-cpp")
message("${PROJECT_NAME}: Adding lwlog...")
add_subdirectory("${CMAKE_SOURCE_DIR}/Vendor/lwlog")
#message("${PROJECT_NAME}: Adding shaderc...")
#add_subdirectory("${CMAKE_SOURCE_DIR}/Vendor/shaderc")

message("${PROJECT_NAME}: Adding source files")
file(GLOB_RECURSE GLAD_SOURCE_FILES ./vendor/glad/src/*.c)
file(GLOB_RECURSE GLAD_HEADER_FILES ./vendor/glad/src/*.h)

file(GLOB_RECURSE IMGUI_SOURCE_FILES imgui_impl_vulkan.cpp imgui_impl_opengl3.cpp imgui_impl_glfw.cpp imgui.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp )
file(GLOB_RECURSE IMGUI_HEADER_FILES imgui_impl_vulkan.h   imgui_impl_opengl3.h imgui_impl_glfw.h   imgui.h imconfig.h imgui_internal.h imstb_rectpack.h imstb_textedit.h imstb_truetype.h)

file(GLOB_RECURSE SANDBOX_SOURCE_FILES ./Sandbox/src/*.cpp)
file(GLOB_RECURSE SANDBOX_HEADER_FILES ./Sandbox/src/*.h)

file(GLOB_RECURSE FIKO_ENGINE_EDITOR_SOURCE_FILES ./FikoEngineEditor/src/*.cpp)
file(GLOB_RECURSE FIKO_ENGINE_EDITOR_HEADER_FILES ./FikoEngineEditor/src/*.h)

file(GLOB_RECURSE FIKO_ENGINE_SOURCE_FILES ./FikoEngineLib/src/*.cpp)
file(GLOB_RECURSE FIKO_ENGINE_HEADER_FILES ./FikoEngineLib/src/*.h)

add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)

set(GLAD_INCLDUE_DIR           "./vendor/glad/include")
set(STB_INCLDUE_DIR            "./vendor/stb")
set(VULKAN_INCLUDE_DIR         "C:/VulkanSDK/1.3.216.0/Include")
set(IMGUI_INCLUDE_DIR          "./vendor/imgui")
set(IMGUI_BACKENDS_INCLUDE_DIR "./vendor/imgui/backends")
set(ENTT_INCLUDE_DIR           "./vendor/entt/single_include")
set(LWLOG_INCLUDE_DIR           "./vendor/lwlog/lwlog/src")

message("${PROJECT_NAME}: Creating imgui lib")
add_library(imgui STATIC ${IMGUI_SOURCE_FILES} ${IMGUI_HEADER_FILES})
message("${PROJECT_NAME}: Creating glad lib")
add_library(glad STATIC ${GLAD_SOURCE_FILES} ${GLAD_HEADER_FILES})

add_library(FikoEngineLib STATIC ${FIKO_ENGINE_SOURCE_FILES} ${FIKO_ENGINE_HEADER_FILES})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(FikoEngineLib PRIVATE -static-libstdc++)
#    target_compile_options(FikoEngineLib PRIVATE -Wall)
#    target_compile_options(FikoEngineLib PRIVATE -pedantic)
    target_compile_options(FikoEngineLib PRIVATE -Wno-volatile)
    target_compile_options(FikoEngineLib PRIVATE -Wno-delete-incomplete)
    target_compile_options(FikoEngineLib PRIVATE -Wno-int-to-pointer-cast)
endif()
target_compile_definitions(FikoEngineLib PRIVATE GLFW_EXPOSE_NATIVE_WIN32)

target_include_directories(glad PRIVATE ${GLAD_INCLDUE_DIR})

target_include_directories(imgui PRIVATE ${VULKAN_INCLUDE_DIR})
target_include_directories(imgui PRIVATE ${IMGUI_INCLUDE_DIR})
target_include_directories(imgui PRIVATE ${IMGUI_BACKENDS_INCLUDE_DIR})

target_include_directories(FikoEngineLib PRIVATE "./FikoEngineLib/src")
target_include_directories(FikoEngineLib PUBLIC ${GLAD_INCLDUE_DIR})
target_include_directories(FikoEngineLib SYSTEM PUBLIC ${STB_INCLDUE_DIR})
target_include_directories(FikoEngineLib PUBLIC ${VULKAN_INCLUDE_DIR})
target_include_directories(FikoEngineLib PUBLIC ${IMGUI_INCLUDE_DIR})
target_include_directories(FikoEngineLib PUBLIC ${IMGUI_BACKENDS_INCLUDE_DIR})
target_include_directories(FikoEngineLib PUBLIC ${ENTT_INCLUDE_DIR})
target_include_directories(FikoEngineLib PUBLIC ${CMAKE_SOURCE_DIR}/Vendor/yaml-cpp/include)
target_include_directories(FikoEngineLib PUBLIC ${LWLOG_INCLUDE_DIR})
add_library(FikoEngineInterfaceLibrary INTERFACE)

message("${PROJECT_NAME}: Linking libraries")

target_link_libraries(imgui PRIVATE glfw C:/VulkanSDK/1.3.216.0/Lib/vulkan-1.lib glad)

target_link_libraries(FikoEngineInterfaceLibrary INTERFACE
        glm::glm
        assimp::assimp
        glfw
        imgui
        glad
        C:/VulkanSDK/1.3.216.0/Lib/vulkan-1.lib
        yaml-cpp
        lwlog
        )
target_link_libraries(FikoEngineLib PUBLIC FikoEngineInterfaceLibrary)

add_executable(Sandbox ${SANDBOX_HEADER_FILES} ${SANDBOX_SOURCE_FILES})
target_include_directories(Sandbox PRIVATE "${CMAKE_SOURCE_DIR}/FikoEngineLib/src")
target_link_libraries(Sandbox FikoEngineLib)

add_executable(FikoEngineEditor ${FIKO_ENGINE_EDITOR_SOURCE_FILES} ${FIKO_ENGINE_EDITOR_HEADER_FILES})
target_include_directories(FikoEngineEditor PRIVATE "${CMAKE_SOURCE_DIR}/FikoEngineLib/src")
target_link_libraries(FikoEngineEditor FikoEngineLib)
