#include "LayerStack.h"

namespace FikoEngine {
    std::unordered_map<std::string_view, Layer *> LayerStack::m_Layers = std::unordered_map<std::string_view, Layer *>();

    LayerStack LayerStack::layerStack = LayerStack();
}