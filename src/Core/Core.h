//
// Created by KSTOYAN2 on 6/8/2022.
//
#pragma once


#include "Definitions.h"
#include "Timestep.h"
#include "stdcpp.h"
#ifdef _WIN32
#include <Windows.h>
#endif
#include "Log.h"

#define VK_CHECK(x) assert(VK_SUCCESS == x)