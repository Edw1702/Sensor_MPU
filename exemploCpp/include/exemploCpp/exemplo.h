#pragma once
#include <cstdint>
#include <string>

namespace exemploCpp {

class MPUSerialReader {
private:
    std::string porta_serial;

public:
    explicit MPUSerialReader(std::string porta);
    
    // Tenta ler os 14 bytes da porta serial configurada
    bool read_packet(uint8_t buffer_saida[14]);
};

} // namespace exemploCpp
