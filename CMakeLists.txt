cmake_minimum_required(VERSION 3.14)
project(FikoEngine)


find_package(Vulkan REQUIRED)
find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})

add_definitions(-DVK_USE_PLATFORM_XLIB_KHR)

add_definitions(-D_LINUX)
add_definitions(-DGLFW_EXPOSE_NATIVE_X11)

add_definitions(-D_DEBUG)

IF (${CMAKE_SYSTEM_NAME} AND "Linux")

ELSE ()
ENDIF ()


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

set(CMAKE_CXX_STANDARD 17)
add_executable(FikoEngine FikoEngine/Application.cpp
        FikoEngine/Application.h
        FikoEngine/Window.cpp
        FikoEngine/Window.h
        FikoEngine/Renderer/Renderer.cpp
        FikoEngine/Renderer/Renderer.h
        FikoEngine/FikoEngine.h
        FikoEngine/EntryPoint.h
        Sandbox/src/Sandbox.cpp
        FikoEngine/Renderer/RendererAPI.cpp
        FikoEngine/Renderer/RendererAPI.h
        FikoEngine/Renderer/RenderCommand.h
        FikoEngine/Renderer/RenderCommand.cpp
        FikoEngine/Renderer/Platform/Vulkan/VulkanRendererAPI.cpp
        FikoEngine/Renderer/Platform/Vulkan/VulkanRendererAPI.h
        FikoEngine/Renderer/Platform/Vulkan/VulkanCore.cpp
        FikoEngine/Renderer/Platform/Vulkan/VulkanCore.h
        FikoEngine/Logger/lwlog/color.h
        FikoEngine/Logger/lwlog/core.h
        FikoEngine/Logger/lwlog/datetime.h
        FikoEngine/Logger/lwlog/details.h
        FikoEngine/Logger/lwlog/formatter.cpp
        FikoEngine/Logger/lwlog/formatter.h
        FikoEngine/Logger/lwlog/lwlog.cpp
        FikoEngine/Logger/lwlog/lwlog.h
        FikoEngine/Logger/lwlog/registry.cpp
        FikoEngine/Logger/lwlog/registry.h
        FikoEngine/Logger/lwlog/utilities.h
        FikoEngine/Logger/Logger.h
        FikoEngine/Renderer/Platform/Vulkan/VulkanCreateInfos.cpp
        FikoEngine/Renderer/Platform/Vulkan/VulkanCreateInfos.h
        FikoEngine/Renderer/Platform/Vulkan/AllocationManger.cpp
        FikoEngine/Renderer/Platform/Vulkan/AllocationManger.h
        FikoEngine/Renderer/Platform/Vulkan/VulkanUtilities.h)

target_link_libraries(FikoEngine glfw3)
target_link_libraries(FikoEngine dl)
target_link_libraries(FikoEngine X11)
target_link_libraries(FikoEngine pthread)
target_link_libraries(FikoEngine vulkan)
