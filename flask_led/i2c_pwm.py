import smbus

class I2C:
    def __init__(self, bus):
        self.bus = smbus.SMBus(bus)
        pass

    def write_number(self, i2c_slave_address, first_byte_address, value_for_send):
        bytes_for_send = self.int_to_bytes(value_for_send, 2)
        self.bus.write_block_data(i2c_slave_address, first_byte_address, bytes_for_send)

    def read_number(self, i2c_slave_address):
        # number = bus.read_byte(address)
        number = self.bus.read_byte_data(i2c_slave_address, 1)
        return number

    @staticmethod
    def bytes_to_int(byte_list):
        result = 0
        for b in byte_list:
            result = result * 256 + int(b)
        return result

    @staticmethod
    def int_to_bytes(value, length):
        result = []
        for i in range(0, length):
            result.append(value >> (i * 8) & 0xff)
        result.reverse()
        return result


class ServoMotor:
    def __init__(self, index, i2c, i2c_address):
        self.index = index
        self.i2c_address = i2c_address
        self.i2c = i2c

    def turn_to_angle(self, angle):
        self.i2c.write_number(self.i2c_address, self.index, angle)