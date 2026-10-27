# Driver e Parser do Sensor IMU MPU-6050 (C++ / Python)

Repositório com a implementação em C++ e Python orientado a objetos para leitura serial, decodificação de pacotes de bytes e conversão física dos dados do sensor inercial MPU-6050(`ament_cmake`).

## Estrutura do Projeto

- `sensor_core` (`src/core` e `src/example`): Biblioteca C++ contendo a lógica de conversão de bytes (`MPUParser`) e a interface de comunicação serial (`MPUSerialReader`).
- `main_app` (`src/main/main.cpp`): Aplicação principal que inicializa a leitura serial (com fallback automático para pacote simulado de demonstração) e exibe as grandezas físicas processadas no terminal.
- `test_core` (`test/test_core.cpp`): Bateria de testes unitários integrada ao CTest para validação da conversão e integridade dos dados orientados a objetos.

## Especificações de Processamento e Conversão

- **Protocolo de leitura:** Pacote bruto de 14 bytes contínuos (`int16_t` *big-endian* para cada eixo).
- **Fatores de Escala e Conversão Física:**
  - Acelerômetro ($\pm 2\text{g}$): $\text{Valor Bruto} / 16384.0 \rightarrow \text{g}$
  - Giroscópio ($\pm 250^\circ/\text{s}$): $\text{Valor Bruto} / 131.0 \rightarrow \text{deg/s}$
  - Temperatura: $(\text{Valor Bruto} / 340.0) + 36.53 \rightarrow ^\circ\text{C}$

## Como Compilar e Executar

No seu workspace ROS 2 (`~/ros2_ws`):

```bash
cd ~/ros2_ws
colcon build --packages-select mpu_sensor
source install/local_setup.bash
ros2 run mpu_sensor main_app
