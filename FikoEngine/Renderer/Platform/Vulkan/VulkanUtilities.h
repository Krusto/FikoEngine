//
// Created by krusto on 1.09.19 г..
//

#ifndef FIKOENGINE_VULKANUTILITIES_H
#define FIKOENGINE_VULKANUTILITIES_H

#include <vulkan/vulkan.h>
#include <string>
#include <assert.h>
#include "../../../Logger/Logger.h"

namespace FikoEngine::VulkanRenderer{
    void VK_CHECK(VkResult result,std::string_view failMessage = "fail"){
        if(result != VK_SUCCESS){
            std::string error;
            error += failMessage;
            error += "| error code : ";
            error += std::to_string(result);
            error += "\n";

            FIKO_CORE_ERROR(error);
                assert(false);
        }
    }

}

#endif //FIKOENGINE_VULKANUTILITIES_H
