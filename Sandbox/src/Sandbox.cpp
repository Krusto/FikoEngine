#include "../../FikoEngine/FikoEngine.h"

class Sandbox : public FikoEngine::Application   {

public :
    Sandbox(){
    }
    ~Sandbox(){
    }
};

FikoEngine::Application* FikoEngine::CreateApplication() {
    return new Sandbox();
}