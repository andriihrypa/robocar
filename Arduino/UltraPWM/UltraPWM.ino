// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
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
}
void demoOne()
{
    // turn on motor B
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // set speed to 200 out of possible range 0~255
    analogWrite(enB, 230);
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