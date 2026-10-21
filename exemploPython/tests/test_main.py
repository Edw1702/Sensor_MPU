import math
import pytest
from exemplo import parse_mpu6050


def test_parse_mpu6050_valores_corretos():
    # Simula o sensor pousado na mesa (Z = 1g -> 0x4000) e Gyro X = 1 deg/s (0x0083)
    pacote_teste = bytes(
        [
            0x00,
            0x00,  # Accel X = 0
            0x00,
            0x00,  # Accel Y = 0
            0x40,
            0x00,  # Accel Z = 16384 (1.0 g)
            0x00,
            0x00,  # Temp = 0 (36.53 C)
            0x00,
            0x83,  # Gyro X = 131 (1.0 deg/s)
            0x00,
            0x00,  # Gyro Y = 0
            0x00,
            0x00,  # Gyro Z = 0
        ]
    )

    resultado = parse_mpu6050(pacote_teste)

    assert math.isclose(resultado.accel_x, 0.0, abs_tol=1e-4)
    assert math.isclose(resultado.accel_z, 1.0, rel_tol=1e-4)
    assert math.isclose(resultado.gyro_x, 1.0, rel_tol=1e-4)
    assert math.isclose(resultado.temp_c, 36.53, rel_tol=1e-2)


def test_parse_mpu6050_tamanho_invalido():
    # Deve dar erro se receber menos de 14 bytes
    with pytest.raises(ValueError):
        parse_mpu6050(b"\x00\x01\x02")
