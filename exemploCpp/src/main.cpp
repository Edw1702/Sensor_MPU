#include <iostream>
#include <iomanip>
#include "exemploCpp/core.hpp"
#include "exemploCpp/exemplo.h"

int main() {
    uint8_t pacote[14] = {0};
    exemploCpp::MPUSerialReader reader("COM3");

    if (reader.read_packet(pacote)) {
        std::cout << "Dados lidos com sucesso da porta COM3!\n";
    } else {
        std::cout << "[Aviso] Nao foi possivel abrir a porta COM3.\n";
        std::cout << "A executar demonstracao com pacote simulado...\n";
        
        // Simulação de dados (Accel Z = 1g, Gyro X = 1 deg/s)
        uint8_t simulado[14] = {
            0x00, 0x00, 0x00, 0x00, 0x40, 0x00,
            0x00, 0x00, 0x00, 0x83, 0x00, 0x00, 0x00, 0x00
        };
        for (int i = 0; i < 14; ++i) pacote[i] = simulado[i];
    }

    // Usa a classe MPUParser para interpretar os bytes
    exemploCpp::MPUData dados = exemploCpp::MPUParser::parse(pacote);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Resultado -> Accel(g): [X=" << dados.accel_x 
              << ", Y=" << dados.accel_y 
              << ", Z=" << dados.accel_z << "] | "
              << "Gyro(deg/s): [X=" << dados.gyro_x 
              << ", Y=" << dados.gyro_y 
              << ", Z=" << dados.gyro_z << "] | "
              << "Temp: " << dados.temp_c << " C\n";

    return 0;
}
