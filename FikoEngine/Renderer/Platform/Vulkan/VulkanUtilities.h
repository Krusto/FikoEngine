//
// Created by krusto on 1.09.19 г..
//

#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <experimental/filesystem>
#include <cstddef>

#include "../../../Logger/Logger.h"
#include "VulkanCreateInfos.h"

namespace FikoEngine::VulkanRenderer {
    static void VK_CHECK(VkResult result, std::string_view failMessage = "Runtime error") {
        if (result != VK_SUCCESS) {
            std::string error;
            error += failMessage;
            error += " | error code : ";
            error += std::to_string(result);
            error += "\n";
            std::transform(error.begin(), error.end(), error.begin(), ::toupper);

            FIKO_CORE_ERROR(error);
        }
    }
    static VulkanCreateInfos createInfo;

    static auto OpenFile(std::string_view FilePath){
        std::streampos fsize = 0;

        std::ifstream myfile (FilePath.data(), std::ios::in);  // File is of type const char*

        fsize = myfile.tellg();         // The file pointer is currently at the beginning
        myfile.seekg(0, std::ios::end);      // Place the file pointer at the end of file

        fsize = myfile.tellg() - fsize;;

       std::vector<uint8_t> buf = std::vector<uint8_t>(fsize);

        std::basic_ifstream<std::byte> ifs(FilePath.data(), std::ios::binary);
        ifs.read(reinterpret_cast<std::byte *>(buf.data()), fsize);

        return buf;
    }

}
