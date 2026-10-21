#include "exemploCpp/core.hpp"

namespace exemploCpp {

int16_t MPUParser::combine_bytes(uint8_t high, uint8_t low) {
    return static_cast<int16_t>((static_cast<uint16_t>(high) << 8) | low);
}

MPUData MPUParser::parse(const uint8_t* raw_bytes) {
    MPUData data{};

    int16_t raw_ax   = combine_bytes(raw_bytes[0],  raw_bytes[1]);
    int16_t raw_ay   = combine_bytes(raw_bytes[2],  raw_bytes[3]);
    int16_t raw_az   = combine_bytes(raw_bytes[4],  raw_bytes[5]);
    int16_t raw_temp = combine_bytes(raw_bytes[6],  raw_bytes[7]);
    int16_t raw_gx   = combine_bytes(raw_bytes[8],  raw_bytes[9]);
    int16_t raw_gy   = combine_bytes(raw_bytes[10], raw_bytes[11]);
    int16_t raw_gz   = combine_bytes(raw_bytes[12], raw_bytes[13]);

    // Escalas padrão: +-2g (16384 LSB/g) e +-250 deg/s (131 LSB/deg/s)
    data.accel_x = raw_ax / 16384.0f;
    data.accel_y = raw_ay / 16384.0f;
    data.accel_z = raw_az / 16384.0f;
    data.temp_c  = (raw_temp / 340.0f) + 36.53f;
    data.gyro_x  = raw_gx / 131.0f;
    data.gyro_y  = raw_gy / 131.0f;
    data.gyro_z  = raw_gz / 131.0f;

    return data;
}

} // namespace exemploCpp