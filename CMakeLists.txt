cmake_minimum_required(VERSION 3.14)
project(FikoEngine)

set(RENDERER_API "Vulkan")

if(RENDERER_API EQUAL "Vulkan")
    add_definitions(-DVK_USE_PLATFORM_XLIB_KHR)
    find_package(Vulkan REQUIRED)
elseif(RENDERER_API EQUAL "OpenGL")

endif()

find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})


add_definitions(-D_LINUX)
add_definitions(-DGLFW_EXPOSE_NATIVE_X11)

add_definitions(-D_DEBUG)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

set(CMAKE_CXX_STANDARD 17)


set(OPENGL_RENDERER_EXCLUDE_DIR "Platform/OpenGL")
set(VULKAN_RENDERER_EXCLUDE_DIR "Platform/Vulkan")

set(IMGUI_EXCLUDE_DIR "ImGUI/Platform")

list(APPEND Sources "")
list(APPEND Headers "")

file(GLOB_RECURSE Sources ./FikoEngine/*.cpp ./Sandbox/*.cpp)
file(GLOB_RECURSE Headers ./FikoEngine/*.h ./Sandbox/*.h)

foreach(TMP_PATH ${Sources})
    string(FIND ${TMP_PATH} ${VULKAN_RENDERER_EXCLUDE_DIR} EXCLUDE_VULKAN_RENDERER_DIR_FOUND)
    string(FIND ${TMP_PATH} ${OPENGL_RENDERER_EXCLUDE_DIR} EXCLUDE_OPENGL_RENDERER_DIR_FOUND)
    string(FIND ${TMP_PATH} ${IMGUI_EXCLUDE_DIR} IMGUI_EXCLUDE_DIR_FOUND)

    if(NOT ${EXCLUDE_VULKAN_RENDERER_DIR_FOUND} EQUAL -1)
        list(REMOVE_ITEM Sources ${TMP_PATH})
        list(REMOVE_ITEM Headers ${TMP_PATH})
    endif()
    if(NOT ${EXCLUDE_OPENGL_RENDERER_DIR_FOUND} EQUAL -1)
        list(REMOVE_ITEM Sources ${TMP_PATH})
        list(REMOVE_ITEM Headers ${TMP_PATH})
    endif()
    if(NOT ${IMGUI_EXCLUDE_DIR_FOUND} EQUAL -1)
        list(REMOVE_ITEM Sources ${TMP_PATH})
        list(REMOVE_ITEM Headers ${TMP_PATH})
    endif()
endforeach(TMP_PATH)

if(RENDERER_API EQUAL "Vulkan")

    file(GLOB_RECURSE sources2 ./FikoEngine/Renderer/Vulkan/*.cpp)
    file(GLOB_RECURSE headers2 ./FikoEngine/Renderer/Vulkan/*.h)
    file(GLOB_RECURSE ImGUI_Sources ./FikoEngine/Vendor/ImGUI/Platform/Vulkan/*.cpp)
    file(GLOB_RECURSE ImGUI_Headers ./FikoEngine/Vendor/ImGUI/Platform/Vulkan/*.h)

    list(APPEND Sources ${sources2})
    list(APPEND Sources ${ImGui_Sources})
    list(APPEND Headers ${headers2})
    list(APPEND Headers ${ImGui_Headers})

elseif(RENDERER_API EQUAL "OpenGL")

    file(GLOB_RECURSE sources2 ./FikoEngine/Renderer/OpenGL/*.cpp)
    file(GLOB_RECURSE headers2 ./FikoEngine/Renderer/OpenGL/*.h)
    file(GLOB_RECURSE ImGUI_Sources ./FikoEngine/Vendor/ImGUI/Platform/OpenGL/*.cpp)
    file(GLOB_RECURSE ImGUI_Headers ./FikoEngine/Vendor/ImGUI/Platform/OpenGL/*.h)

    list(APPEND Sources ${sources2})
    list(APPEND Sources ${ImGui_Sources})

    list(APPEND Headers ${headers2})
    list(APPEND Headers ${ImGui_Headers})

endif()

add_executable(FikoEngine ${Sources} ${Headers})

target_link_libraries(FikoEngine glfw3)
target_link_libraries(FikoEngine dl)
target_link_libraries(FikoEngine X11)
target_link_libraries(FikoEngine pthread)

if(RENDERER_API EQUAL "Vulkan")
target_link_libraries(FikoEngine vulkan)
elseif(RENDERER_API EQUAL "OpenGL")

endif()
