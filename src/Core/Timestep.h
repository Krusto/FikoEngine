#pragma once

#include "Definitions.h"

class Timestep {
public:
    Timestep() = default;
    Timestep(f32 time) : mTime(time) {}
    f32 toMillis() const { return mTime * (f32)1000; }
    f32 toMicros() const { return mTime * (f32)1000000; }
    f32 Time() const { return mTime; }
    Timestep operator-(Timestep& other) {
        return Timestep(this->Time() - other.Time());
    }
    void setTime(f32 time) {
        mTime = time;
    }
private:
    f32 mTime{};
};