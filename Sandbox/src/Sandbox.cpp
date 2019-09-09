#include "../../FikoEngine/FikoEngine.h"

class ExampleLayer : public FikoEngine::Layer{
public:
    ExampleLayer(){

    }
    void OnUpdate(){

    }
    void OnAttach(){

    }
    void OnDetach(){

    }
};
std::unordered_map<std::string_view,FikoEngine::Layer*> FikoEngine::LayerStack::mLayers = (std::unordered_map<std::string_view,FikoEngine::Layer*>)NULL;
class Sandbox : public FikoEngine::Application {

public :
    Sandbox() {
        FikoEngine::LayerStack::pushLayer(std::make_pair<std::string_view,FikoEngine::Layer*>("Example Layer",new ExampleLayer()));
    }

    ~Sandbox() {
    }
};

FikoEngine::Application *FikoEngine::CreateApplication() {
    return new Sandbox();
}