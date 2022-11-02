#pragma once
#include "Layer.h"
#include <unordered_map>
#include <Core/Ref.h>
namespace FikoEngine {
    class LayerStack {
    public:
        LayerStack() = default;

        static void PushLayer(Ref<Layer> layer) {
            LayerStack::m_Layers.try_emplace(layer->GetName(), layer);
            layer->OnAttach();
        }

        static void PopLayer(std::string name) {
            if (LayerStack::m_Layers.contains(name)) {
                LayerStack::m_Layers.at(name)->OnDetach();
                LayerStack::m_Layers.erase(name);
            }
        }

        static Layer *GetLayer(std::string name) { return LayerStack::m_Layers[name]; }

        static auto end() { return LayerStack::m_Layers.end(); }

        static auto begin() { return LayerStack::m_Layers.begin(); }

        static auto &data() { return LayerStack::m_Layers; }

    private:
        inline static std::unordered_map<std::string, Ref<Layer>> m_Layers{};
    };
 }