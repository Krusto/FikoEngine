cmake_minimum_required(VERSION 3.14)
project(Engine)


find_package(Vulkan REQUIRED)
find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})
add_definitions(-DVK_USE_PLATFORM_XLIB_KHR)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

set(CMAKE_CXX_STANDARD 17)
add_executable(Engine Engine/Application.cpp
        Engine/Application.h
        Engine/Window.cpp
        Engine/Window.h
        Engine/Renderer/Renderer.cpp
        Engine/Renderer/Renderer.h
        Engine/FikoEngine.h
        Engine/EntryPoint.h
                            Sandbox/src/Sandbox.cpp
        Engine/Renderer/RendererAPI.cpp
        Engine/Renderer/RendererAPI.h
        Engine/Renderer/RenderCommand.h
        Engine/Renderer/RenderCommand.cpp
        Engine/Renderer/Platform/Vulkan/VulkanRendererAPI.cpp
        Engine/Renderer/Platform/Vulkan/VulkanRendererAPI.h
        Engine/Renderer/Platform/Vulkan/VulkanCore.cpp
        Engine/Renderer/Platform/Vulkan/VulkanCore.h
        Engine/Logger/lwlog/color.h
        Engine/Logger/lwlog/core.h
        Engine/Logger/lwlog/datetime.h
        Engine/Logger/lwlog/details.h
        Engine/Logger/lwlog/formatter.cpp
        Engine/Logger/lwlog/formatter.h
        Engine/Logger/lwlog/lwlog.cpp
        Engine/Logger/lwlog/lwlog.h
        Engine/Logger/lwlog/registry.cpp
        Engine/Logger/lwlog/registry.h
        Engine/Logger/lwlog/utilities.h
        Engine/Logger/Logger.h
        Engine/Renderer/Platform/Vulkan/VulkanCreateInfos.cpp
        Engine/Renderer/Platform/Vulkan/VulkanCreateInfos.h
        Engine/Renderer/Platform/Vulkan/AllocationManger.cpp
        Engine/Renderer/Platform/Vulkan/AllocationManger.h
        Engine/Renderer/Platform/Vulkan/VulkanUtilities.h)

target_link_libraries(Engine glfw3)
target_link_libraries(Engine dl)
target_link_libraries(Engine X11)
target_link_libraries(Engine pthread)
target_link_libraries(Engine vulkan)
