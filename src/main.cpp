#include <Arduino.h>

// TODO add servo library for the ackerman servo motor
//  Motor A
int dir1PinA = 2;
int dir2PinA = 3;
int speedPinA = 6; //   เพื่อให้ PWM สามารถควบคุมความเร็วมอเตอร์
// Motor B
int dir1PinB = 4;
int dir2PinB = 5;
int speedPinB = 7; // เพื่อให้ PWM สามารถควบคุมความเร็วมอเตอร์
bool foward = true;

// Functions
void speedControl(int throttle, int left, int right)
{
    if (left != 0)
    {
        // More power to the left
        // left = throttle
        float rightPow = (((throttle - ((throttle * left) / (throttle + left))) * 255) / 100);
        analogWrite(speedPinB, rightPow); // PWM Speed control
    }
    else if (right != 0)
    {
        // More power to the right
        float rightPow = (((throttle - ((throttle * right) / (throttle + right))) * 255) / 100);
        analogWrite(speedPinB, rightPow); // PWM Speed control
    }
    else
    {
        float rightPow = (((throttle - ((throttle * left) / (throttle + left))) * 255) / 100);
        analogWrite(speedPinB, rightPow); // PWM Speed control
    }
}

void drive(int throttle = 0, int left = 0, int right = 0)
{
    /*
    Max number for throttle, left and right is 100 */
    if (throttle > 0)
    {
        digitalWrite(dir1PinA, HIGH);
        digitalWrite(dir2PinA, LOW);
        speedControl(throttle, left, right);
    }
    else if (throttle < 0)
    {
        digitalWrite(dir1PinA, LOW);
        digitalWrite(dir2PinA, HIGH);
        speedControl(throttle, left, right);
    }
    else
    {
        digitalWrite(dir1PinA, LOW);
        digitalWrite(dir2PinA, LOW);
        speedControl(0, 0, 0);
    }
}

void setup()
{
    Serial.begin(9600);
    pinMode(dir1PinA, OUTPUT);
    pinMode(dir2PinA, OUTPUT);
    pinMode(speedPinA, OUTPUT);
    pinMode(dir1PinB, OUTPUT);
    pinMode(dir2PinB, OUTPUT);
    pinMode(speedPinB, OUTPUT);
    Serial.println("Setup done");
}

void loop()
{
    drive(0, 0, 0);
    drive(20, 0, 0);
    delay(2000);
    drive(-20, 0, 0);
    delay(2000);
    drive(20, 20, 0);
    delay(20000);
}

/* if (foward)
{
    analogWrite(speedPinA, 255); // PWM Speed control
    digitalWrite(dir1PinA, LOW);
    digitalWrite(dir2PinA, HIGH);
} */