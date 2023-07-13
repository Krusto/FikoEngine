#include <FikoEngine.h>
#include "EditorLayer.h"
using namespace FikoEngine;

class Editor : public FikoEngine::Application
{
public:
    explicit Editor(const ApplicationSpec& spec){
        LayerStack::ConstructAndPushLayer<EditorLayer>(spec);
    }
    ~Editor()= default;
};

int main(){
    auto spec = FikoEngine::ApplicationSpec{"FikoEngine Editor",
                                            "./",
                                            FikoEngine::Version{1,0,0}};
    auto* editor = new Editor(spec);
    editor->Init(spec);
    editor->Run();

    editor->Destroy();

    delete editor;

    return 0;
}
