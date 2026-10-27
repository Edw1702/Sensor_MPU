# Driver e Parser do Sensor IMU MPU-6050 (ROS 2)

Repositório com a implementação em C++ para leitura serial, decodificação de pacotes de bytes e publicação de dados inerciais do sensor MPU-6050 utilizando ROS 2 Humble.

## Estrutura do Projeto

- `sensor_core` (`src/core` e `src/example`): Biblioteca C++ orientada a objetos contendo o parser de pacotes de 14 bytes (`MPUParser`) e a interface de leitura serial (`MPUSerialReader`), com fallback automático para pacotes simulados.
- `main_app` (`src/main/main.cpp`): Executável do nó ROS 2 (`mpu_publisher_node`) responsável por amostrar o sensor periodicamente e publicar os dados na rede DDS.
- `test_core` (`test/test_core.cpp`): Bateria de testes unitários integrada ao CTest para validação da conversão e integridade dos dados orientados a objetos.

## Especificações de Publicação (Padrão REP-103)

- **Tópico de publicação:** `/imu/data_raw` (`sensor_msgs/msg/Imu`)
- **Frequência de amostragem:** 50 Hz (ciclo de 20 ms via `WallTimer`)
- **Frame de referência:** `imu_link`
- **Conversão de Unidades para o Sistema Internacional (SI):**
  - Aceleração Linear: $\text{g} \rightarrow \text{m/s}^2$ ($\times 9.80665$)
  - Velocidade Angular: $\text{deg/s} \rightarrow \text{rad/s}$ ($\times \frac{\pi}{180}$)
  - Orientação: `orientation_covariance[0] = -1.0` (indicando dados brutos sem estimativa de quaternion acoplada)

## Como Compilar e Executar

No seu workspace ROS 2 (`~/ros2_ws`):

```bash
cd ~/ros2_ws
colcon build --packages-select mpu_sensor
source install/local_setup.bash
ros2 run mpu_sensor main_app