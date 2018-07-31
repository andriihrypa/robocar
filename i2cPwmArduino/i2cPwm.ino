#include <Servo.h>
#include <Wire.h>

#define MOTORS_NUMBER 6
#define SLAVE_ADDRESS 0x05
#define I2C_BUFFER_SIZE 50

Servo servoMotors[MOTORS_NUMBER];
int servoMotorsAngels[MOTORS_NUMBER];

// the setup function runs once when you press reset or power the board
void setup()
{
    Serial.begin(9600);

    servoMotors[0].attach(3);
    servoMotors[1].attach(5);
    servoMotors[2].attach(6);
    servoMotors[3].attach(9);
    servoMotors[4].attach(10);
    servoMotors[5].attach(11);

    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(i2cReceiveData);
}

// the loop function runs over and over again forever
void loop()
{
    delay(100);
}

//callback for received data via I2C
void i2cReceiveData(int byteCount)
{
    uint8_t receivedMessage[I2C_BUFFER_SIZE];
    int i = 0;
    while (Wire.available())
    {
        receivedMessage[i] = (uint8_t)Wire.read();
        Serial.print("receivedMessage[i]=");
        Serial.println(receivedMessage[i]);
        i++;
    }

    if (i < 4)
    {
        return;
    }

    int servoMotorIndex = receivedMessage[0];
    int turningAngle =  receivedMessage[2] * 256 + receivedMessage[3];
    Serial.print("servo motor index: ");
    Serial.println(servoMotorIndex);
    Serial.print("turning angle: ");
    Serial.println(turningAngle);
    servoMotors[servoMotorIndex].write(turningAngle);
}

// callback for sending data via I2C
void i2cSendData()
{
    Wire.write(42);
}
