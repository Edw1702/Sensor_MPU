#include <cassert>
#include <cmath>
#include <iostream>
#include "exemploCpp/core.hpp"

int main() {
    uint8_t pacote_teste[14] = {
        0x00, 0x00, 
        0x00, 0x00, 
        0x40, 0x00, // Accel Z = 16384 (1.0 g)
        0x00, 0x00, 
        0x00, 0x83, // Gyro X = 131 (1.0 deg/s)
        0x00, 0x00, 
        0x00, 0x00  
    };

    auto resultado = exemploCpp::MPUParser::parse(pacote_teste);

    assert(std::fabs(resultado.accel_z - 1.0f) < 1e-4);
    assert(std::fabs(resultado.gyro_x - 1.0f) < 1e-4);
    assert(std::fabs(resultado.temp_c - 36.53f) < 1e-2);

    std::cout << "[SUCESSO] Todos os testes orientados a objetos passaram!\n";
    return 0;
}
