#pragma once
#include <cstdint>

struct ViewportSize {
    u32 width{};
    u32 height{};

    ViewportSize& operator=(ViewportSize&) = default;
    ViewportSize& operator=(const ViewportSize&) = default;
    bool operator==(const ViewportSize& other) {
        return (other.width == width) && (other.height == height);
    }
    bool operator!=(const ViewportSize& other) {
        return !((*this) == other);
    }
};