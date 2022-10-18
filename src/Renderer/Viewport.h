﻿#pragma once
#include <cstdint>

struct ViewportSize {
    uint32_t width{};
    uint32_t height{};

    bool operator==(const ViewportSize& other) {
        return (other.width == width) && (other.height == height);
    }
    bool operator!=(const ViewportSize& other) {
        return !((*this) == other);
    }
};