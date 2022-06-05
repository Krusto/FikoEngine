#pragma once
class Timestep {
public:
    Timestep() = default;
    Timestep(double time) : mTime(time) {}
    double toMillis() const { return mTime * (double)1000; }
    double toMicros() const { return mTime * (double)1000000; }
    double Time() const { return mTime; }
    Timestep operator-(Timestep& other) {
        return Timestep(this->Time() - other.Time());
    }
    void setTime(double time) {
        mTime = time;
    }
private:
    double mTime{};
};