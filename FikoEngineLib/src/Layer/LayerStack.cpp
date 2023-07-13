#include "LayerStack.h"
#include <Renderer/Window.h>
namespace FikoEngine {
    void LayerStack::InitLayers(Ref<Window> window) {
        for (auto layer : m_Layers) {
            layer->Init(window);
        }
    }

}