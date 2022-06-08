//
// Created by KSTOYAN2 on 6/7/2022.
//
#include "RendererAPI.h"
#include "Vulkan/Instance.h"
#include "Vulkan/PhysicalDevice.h"

#include "Vulkan/Device.h"
#include <vulkan/vulkan.h>
#include <lwlog.h>

namespace FikoEngine {

    void RendererAPI::Init(RendererSpecAPI rendererSpec, ApplicationSpec applicationSpec) {
        VkInstance instance = CreateInstance(applicationSpec);
        VkPhysicalDevice physicalDevice = SelectPhysicalDevice(instance);
        VkDevice device = CreateDevice(instance,physicalDevice,rendererSpec.extensions);

        auto console = std::make_shared<
                lwlog::logger<
                        lwlog::default_log_policy,
                        lwlog::default_storage_policy,
                        lwlog::single_threaded_policy,
                        lwlog::sinks::stdout_sink
                >
        >("CONSOLE");

        console->set_level_filter(lwlog::level::info | lwlog::level::debug | lwlog::level::critical);
        console->set_pattern(".br_red([%T] [%n]) .green([%l]): .br_cyan(%v) TEXT");

        {
            console->critical("First critical message");
        }


        vkDestroyDevice(device,nullptr);
        vkDestroyInstance(instance,nullptr);
    }
}