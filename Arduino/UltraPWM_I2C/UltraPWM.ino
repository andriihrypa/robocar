#include <Wire.h>
#define SLAVE_ADDRESS 0x05
#define I2C_BUFFER_SIZE 50
// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
int speedFactor = 0;
int enB = 5;
int in3 = 7;
int in4 = 6;
// defines variables
long duration;
int distance;
void setup()
{
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    pinMode(enB, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    Serial.begin(9600); // Starts the serial communication
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(i2cReceiveData);
}
void demoOne()
{
    // turn on motor B
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // set speed to 200 out of possible range 0~255
    Serial.println("analogWrite(enB, speedFactor);");
    Serial.print("speedFactor: ");
    Serial.println(speedFactor);
    analogWrite(enB, speedFactor);
    delay(1000);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}
void loop() {
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);
    if (distance >= 15)
    {
        demoOne();
        delay(1000);
    }
    else
    {
        Serial.print("Too close: ");
        Serial.println(distance);
    }
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
    int speed = receivedMessage[2] * 256 + receivedMessage[3];
    Serial.print("servo motor index: ");
    Serial.println(servoMotorIndex);
    Serial.print("Speed: ");
    Serial.println(speed);
    speedFactor = speed;
}

// callback for sending data via I2C
void i2cSendData()
{
    Wire.write(42);
}