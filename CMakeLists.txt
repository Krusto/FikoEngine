cmake_minimum_required(VERSION 3.14)
project(FikoEngine)


find_package(Vulkan REQUIRED)
find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})

add_definitions(-DVK_USE_PLATFORM_XLIB_KHR)

add_definitions(-D_LINUX)
add_definitions(-DGLFW_EXPOSE_NATIVE_X11)

add_definitions(-D_DEBUG)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

set(CMAKE_CXX_STANDARD 17)


file(GLOB_RECURSE src ${PROJECT_SOURCE_DIR} *.cpp *.hpp)
add_executable(FikoEngine ${src})

target_link_libraries(FikoEngine glfw3)
target_link_libraries(FikoEngine dl)
target_link_libraries(FikoEngine X11)
target_link_libraries(FikoEngine pthread)
target_link_libraries(FikoEngine vulkan)
