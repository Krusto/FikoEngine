//
// Created by krusto on 9/16/19.
//

#ifndef FIKOENGINE_BUFFER_H
#define FIKOENGINE_BUFFER_H

#include <cstdint>

namespace FikoEngine {
    class Buffer {
    public:
        void CreateBuffer();
        void Submit();
    private:
        uint32_t mID;

    };
}

#endif //FIKOENGINE_BUFFER_H
