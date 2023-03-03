#include "Window.h"
#ifdef _WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#define GLFW_INCLUDE_VULKAN

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

#include "Vulkan/Memory.h"
#include <vulkan/vulkan.h>

#ifdef _WIN32
#include <vulkan/vulkan_win32.h>
#endif

#include <Renderer/RendererAPI.h>

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
    if(severity!=GL_DEBUG_SEVERITY_NOTIFICATION)
        fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
                 ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
                 type, severity, message );
}


void ErrorCallback(int code, const char* err_str)
{
    if(std::string(err_str) != "Invalid window attribute 0x0002000D")
        std::cout << code <<" GLFW Error: " << err_str << std::endl;
}

namespace FikoEngine {
Window::Window(WindowSpec& spec) {
    this->spec = spec;

    if (!glfwInit()) {
        LOG_ERROR("GLFW CAN NOT INITIALIZE!!!");
        exit(-1);
    }

    switch(RendererAPI::s_api){
        case RendererAPI::API::OpenGL:
            glfwWindowHint(GLFW_CLIENT_API,GLFW_OPENGL_API);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
            break;
        case RendererAPI::API::Vulkan:
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);
            break;
        case RendererAPI::None:
            break;
    }

    int major,minor,rev;
    glfwGetVersion(&major,&minor,&rev);

    std::cout<<"GLFW VERSION:" << major<<"."<<minor<<"."<<rev<<'\n';

    s_Window = glfwCreateWindow(spec.width,spec.height,spec.title.c_str(),nullptr,nullptr);
    if (this->Good())
    {
        std::cout << "Failed to create GLFW window!\n";
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(s_Window);

    GraphicsContext::s_Context = Renderer::CreateGraphicsContext(s_Window);
    GraphicsContext::s_Context->Init();

    switch(RendererAPI::s_api){
        case RendererAPI::API::OpenGL:
            glEnable              ( GL_DEBUG_OUTPUT );
            glDebugMessageCallback( MessageCallback, 0 );
            break;
        default:
            break;
    }
    glfwSetErrorCallback(ErrorCallback);
    glfwSetWindowCloseCallback(this->s_Window,closeCallback);
    glfwSetWindowSizeCallback(this->s_Window,windowSizeCallback);
    glfwSetKeyCallback(this->s_Window,windowKeyCallback);
    glfwSetCursorPosCallback(this->s_Window, windowMouseMoveCallback);
//    glfwSetInputMode(this->s_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

VkSurfaceKHR Window::CreateSurface(VkInstance instance) {
    VkSurfaceKHR surface;
    #ifdef _WIN32
    VkWin32SurfaceCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.hwnd = glfwGetWin32Window(s_Window);
    createInfo.hinstance = GetModuleHandle(nullptr);
    vkCreateWin32SurfaceKHR(instance,&createInfo,nullptr,&surface);
    #endif
    return surface;
}

    void Window::Update() {
        GraphicsContext::s_Context->SwapBuffers();
        this->spec.width = s_ViewportSize.width;
        this->spec.height = s_ViewportSize.height;
    }

    void Window::Clear(float r, float g, float b, float a) {
        Renderer::ClearColor(glm::vec4{ r,g,b,a });
    }

    double Window::GetDeltaTime() const {
        return 1.0/m_Timestep;
    }

    void Window::SetDeltaTime(double value) {
        m_Timestep = value;
    }

    bool Window::Good() {
        return (s_Window == nullptr);
    }

    void Window::Close() {
        glfwSetWindowShouldClose(s_Window,GLFW_TRUE);
    }

    Window::operator bool() {
        return false;
    }
}