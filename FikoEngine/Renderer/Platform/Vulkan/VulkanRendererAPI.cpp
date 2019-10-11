//
// Created by krusto on 30.08.19 г..
//

#include "VulkanRendererAPI.h"

void FikoEngine::VulkanRendererAPI::Init(FikoEngine::Window window) {
    mCore.Init(window);
}

void FikoEngine::VulkanRendererAPI::Clear() {

}

void FikoEngine::VulkanRendererAPI::Begin() {
    mCore.Begin();
}

void FikoEngine::VulkanRendererAPI::End() {
    mCore.End();
}
