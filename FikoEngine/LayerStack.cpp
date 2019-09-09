//
// Created by krusto on 9/9/19.
//

#include "LayerStack.h"

void FikoEngine::LayerStack::pushLayer(std::pair<std::string_view, Layer*> Layer) {
    mLayers.emplace(Layer);
    Layer.second->OnAttach();
}

void FikoEngine::LayerStack::popLayer(std::string_view name) {
    if(mLayers.find(name) != mLayers.end()){
        mLayers[name]->OnDetach();
        mLayers.erase(name);
    }
}

FikoEngine::LayerStack::~LayerStack() {
    for(auto i : mLayers){
        delete i.second;
    }
}
