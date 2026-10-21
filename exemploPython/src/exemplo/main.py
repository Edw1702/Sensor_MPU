import time
import serial
from exemplo import MPUData, parse_mpu6050


def ler_sensor_serial(porta: str = "COM3", baudrate: int = 115200):
    """Abre a porta Serial no Windows, le os 14 bytes do MPU6050 e interpreta."""
    try:
        with serial.Serial(porta, baudrate, timeout=1.0) as ser:
            print(f"Conectado na porta {porta} a {baudrate} bps.")
            while True:
                pacote = ser.read(14)
                if len(pacote) == 14:
                    dados = parse_mpu6050(pacote)
                    print(
                        f"Accel (g): X={dados.accel_x:.2f}, Y={dados.accel_y:.2f}, Z={dados.accel_z:.2f} | "
                        f"Gyro (deg/s): X={dados.gyro_x:.2f}, Y={dados.gyro_y:.2f}, Z={dados.gyro_z:.2f} | "
                        f"Temp: {dados.temp_c:.1f} C"
                    )
    except serial.SerialException as e:
        print(f"[Aviso] Nao foi possivel abrir a porta {porta}: {e}")
        print("A executar demonstracao com pacote de dados simulado...")
        pacote_simulado = bytes(
            [
                0x00,
                0x00,
                0x00,
                0x00,
                0x40,
                0x00,
                0x00,
                0x00,
                0x00,
                0x83,
                0x00,
                0x00,
                0x00,
                0x00,
            ]
        )
        dados = parse_mpu6050(pacote_simulado)
        print(f"Dados interpretados com sucesso: {dados}")


if __name__ == "__main__":
    ler_sensor_serial()
