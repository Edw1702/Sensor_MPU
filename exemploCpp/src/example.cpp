#include "exemploCpp/exemplo.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace exemploCpp {

MPUSerialReader::MPUSerialReader(std::string porta) : porta_serial(porta) {}

bool MPUSerialReader::read_packet(uint8_t buffer_saida[14]) {
#ifdef _WIN32
    std::string caminho = "\\\\.\\" + porta_serial;
    HANDLE hSerial = CreateFileA(
        caminho.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr
    );

    if (hSerial == INVALID_HANDLE_VALUE) {
        return false;
    }

    DCB dcb = {0};
    dcb.DCBlength = sizeof(dcb);
    GetCommState(hSerial, &dcb);
    dcb.BaudRate = CBR_115200;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity   = NOPARITY;
    SetCommState(hSerial, &dcb);

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 1000;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);

    DWORD bytes_lidos = 0;
    BOOL sucesso = ReadFile(hSerial, buffer_saida, 14, &bytes_lidos, nullptr);
    CloseHandle(hSerial);

    return (sucesso && bytes_lidos == 14);
#else
    return false;
#endif
}

} // namespace exemploCpp
