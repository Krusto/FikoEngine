#pragma once
#include <cstdint>
#include <functional>

namespace FikoEngine {
    class UUID {
    public:
        UUID();

        UUID(uint64_t uuid);

        UUID(const UUID &other);

        operator uint64_t() { return m_UUID; }

        operator const uint64_t() const { return m_UUID; }

        uint64_t GetID() { return m_UUID;}

        uint64_t GetID() const  { return m_UUID;}

    private:
        uint64_t m_UUID;
    };

    class UUID32 {
    public:
        UUID32();

        UUID32(u32 uuid);

        UUID32(const UUID32 &other);

        operator u32() { return m_UUID; }

        operator const u32() const { return m_UUID; }

        u32 GetID() { return m_UUID;}

        u32 GetID() const { return m_UUID;}
    private:
        u32 m_UUID;
    };


}
namespace std {

    template<> struct hash<FikoEngine::UUID> {
        std::size_t operator()(const FikoEngine::UUID &uuid) const {
            return hash<uint64_t>()((uint64_t) uuid.GetID());
        }
    };

    template<> struct hash<FikoEngine::UUID32> {
        std::size_t operator()(const FikoEngine::UUID32 &uuid) const {
            return hash<u32>()((u32) uuid.GetID());
        }
    };
}