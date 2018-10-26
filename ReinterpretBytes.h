#pragma once
#include <cstdint>
#include <array>

// Need to perform some unsafe, Undefined Behaviour-inducing type punning
// to be able to call the C API of NuiSensor. So ...
// ... do it in a separate translation unit to reduce possibility of the
// optimizer inlining the functions and causing UB-related optimizations.

std::array<uint8_t, 4> ub_land_value_to_bytes(float value);
std::array<uint8_t, 4> ub_land_value_to_bytes(uint32_t value);
uint32_t ub_land_bytes_to_int(const uint8_t* buf, int size);
float ub_land_bytes_to_float(const uint8_t* buf, int size);

