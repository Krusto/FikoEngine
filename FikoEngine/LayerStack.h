//
// Created by krusto on 9/9/19.
//

#ifndef FIKOENGINE_LAYERSTACK_H
#define FIKOENGINE_LAYERSTACK_H

#include <utility>
#include <unordered_map>
#include <vector>
#include "Layer.h"



namespace FikoEngine {
    class LayerStack {
    public:
        static void pushLayer(std::pair<std::string_view,Layer*> Layer);
        static void popLayer(std::string_view name);

        static std::unordered_map<std::string_view ,Layer*>::iterator begin(){return mLayers.begin();}
        static std::unordered_map<std::string_view ,Layer*>::iterator end(){return mLayers.end();}

        ~LayerStack();
        static std::unordered_map<std::string_view,Layer*> mLayers;
    };

}

#endif //FIKOENGINE_LAYERSTACK_H
