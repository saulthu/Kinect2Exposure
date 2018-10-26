#include "ReinterpretBytes.h"
#include <stdexcept>

std::array<uint8_t, 4> ub_land_value_to_bytes(float value)
{
  auto buf = reinterpret_cast<const uint8_t*>(&value);
  return std::array<uint8_t, 4>{buf[0], buf[1], buf[2], buf[3]};
}

std::array<uint8_t, 4> ub_land_value_to_bytes(uint32_t value)
{
  auto buf = reinterpret_cast<const uint8_t*>(&value);
  return std::array<uint8_t, 4>{buf[0], buf[1], buf[2], buf[3]};
}

uint32_t ub_land_bytes_to_int(const uint8_t* buf, int size)
{
  if (size < 4)
    throw std::invalid_argument("invalid size");
  return *reinterpret_cast<const uint32_t*>(buf);
}

float ub_land_bytes_to_float(const uint8_t* buf, int size)
{
  if (size < 4)
    throw std::invalid_argument("invalid size");
  return *reinterpret_cast<const float*>(buf);
}
