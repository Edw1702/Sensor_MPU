#pragma once
#include <cstdint>

namespace exemploCpp {

struct MPUData {
    float accel_x, accel_y, accel_z; // em g
    float temp_c;                    // em graus Celsius
    float gyro_x, gyro_y, gyro_z;    // em graus/s
};

class MPUParser {
private:
    static int16_t combine_bytes(uint8_t high, uint8_t low);

public:
    // Recebe os 14 bytes brutos e retorna a struct com os valores interpretados
    static MPUData parse(const uint8_t* raw_bytes);
};

} // namespace exemploCpp