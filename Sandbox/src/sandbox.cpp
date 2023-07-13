#include <FikoEngine.h>
#include "SandboxLayer.h"
using namespace FikoEngine;

class Sandbox : public FikoEngine::Application
{
public:
    explicit Sandbox(const ApplicationSpec& spec){
        LayerStack::ConstructAndPushLayer<SandboxLayer>(spec);
    }
    ~Sandbox()= default;
};

int main(){
    auto spec = FikoEngine::ApplicationSpec{"Sandbox",
                                            "./",
                                            FikoEngine::Version{1,0,0}};
    auto* sandbox = new Sandbox(spec);
    sandbox->Init(spec);
    sandbox->Run();

    sandbox->Destroy();

    delete sandbox;

    return 0;
}
