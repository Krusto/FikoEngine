//
// Created by Stoyanov, Krusto (K.S.) on 6/3/2022.
//
#pragma once

#include <cstdint>

#define s64 sint64_t  // No such thing as std::sint64_t, you probably meant a short int, which is std::int16_t

namespace FikoEngine
{
  using u64 = std::uint64_t;
  using i64 = std::int64_t;
  
  using u32 = std::uint32_t;
  using i32 = std::int32_t;
  
  using u16 = std::uint16_t; // IF you want a short int
  using i16 = std::int16_t;  // IF you want a short int
  
  using u8  = std::uint8_t;
  using i8  = std::int8_t;
}
