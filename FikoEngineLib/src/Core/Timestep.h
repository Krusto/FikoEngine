#pragma once

#include "Definitions.h"

class Timestep {
public:
    Timestep() = default;
    Timestep(float time) : mTime(time) {}
    float toMillis() const { return mTime * (float)1000; }
    float toMicros() const { return mTime * (float)1000000; }
    float Time() const { return mTime; }
    Timestep operator-(Timestep& other) {
        return Timestep(this->Time() - other.Time());
    }
    void setTime(float time) {
        mTime = time;
    }
private:
    float mTime{};
};