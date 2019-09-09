//
// Created by krusto on 9/9/19.
//

#ifndef FIKOENGINE_LAYER_H
#define FIKOENGINE_LAYER_H

namespace FikoEngine {
    class Layer {
    public:
        Layer(){}
        virtual ~Layer() = default;

        virtual void Init(){}
        virtual void OnUpdate(){}
        virtual void OnAttach(){}
        virtual void OnDetach(){}
    private:
    };
}

#endif //FIKOENGINE_LAYER_H
