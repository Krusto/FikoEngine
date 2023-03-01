//
// Created by Stoyanov, Krusto (K.S.) on 6/8/2022.
//
#pragma once


#include "Definitions.h"
#include "Extent2D.h"
#include "Timestep.h"
#include "stdcpp.h"
#ifdef _WIN32
#include <Windows.h>
#endif
#include "Log.h"
#include <vulkan/vulkan.h>

void VK_CHECK(auto x) {
    assert(VK_SUCCESS == x);
}