#pragma once
#include "Layer.h"
#include <unordered_map>
#include <Core/Ref.h>
class LayerStack {
public:
    LayerStack() = default;
    static void PushLayer(Ref<Layer> layer){m_Layers.try_emplace(layer->GetName(),layer.Raw());layer->OnAttach();}
    static void PopLayer(std::string_view name){
        if (m_Layers.contains(name)) {
            m_Layers.at(name)->OnDetach();
            m_Layers.erase(name);
        }
    }
    static Layer* GetLayer(std::string_view name){return m_Layers.at(name);}
    static auto end(){return m_Layers.end();}
    static auto begin(){return m_Layers.begin();}
    static auto& data(){return m_Layers;}
private:
    static std::unordered_map<std::string_view,Layer*> m_Layers;
    static LayerStack layerStack;
};