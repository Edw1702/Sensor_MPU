import struct
from dataclasses import dataclass


@dataclass
class MPUData:
    accel_x: float
    accel_y: float
    accel_z: float
    temp_c: float
    gyro_x: float
    gyro_y: float
    gyro_z: float


def parse_mpu6050(raw_bytes: bytes) -> MPUData:
    """Converte os 14 bytes brutos do MPU6050 em grandezas fisicas."""
    if len(raw_bytes) != 14:
        raise ValueError(
            f"Esperados 14 bytes, mas foram recebidos {len(raw_bytes)}"
        )

    # '>7h' desempacota 7 inteiros de 16 bits com sinal (Big-Endian)
    ax, ay, az, temp, gx, gy, gz = struct.unpack(">7h", raw_bytes)

    return MPUData(
        accel_x=ax / 16384.0,
        accel_y=ay / 16384.0,
        accel_z=az / 16384.0,
        temp_c=(temp / 340.0) + 36.53,
        gyro_x=gx / 131.0,
        gyro_y=gy / 131.0,
        gyro_z=gz / 131.0,
    )
