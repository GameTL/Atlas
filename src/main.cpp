#include <Arduino.h>

// Motor A

int dir1PinA = 2;
int dir2PinA = 3;
int speedPinA = 6; //   เพื่อให้ PWM สามารถควบคุมความเร็วมอเตอร์
// Motor B
int dir1PinB = 4;
int dir2PinB = 5;
int speedPinB = 7; // เพื่อให้ PWM สามารถควบคุมความเร็วมอเตอร์
bool foward = true;

void drive(int throttle = 0, int left = 0, int right = 0)
{
    /*
    Max number for throttle, left and right is 100 */
    if (left != 0)
    {
        // More power to the left
        // left = throttle
        // right =
        float rightPow = (((throttle - ((throttle * left) / (throttle + left))) * 255) / 100);
        pinMode(speedPinB, OUTPUT);
        analogWrite(speedPinB, rightPow); // PWM Speed control
    }
    else if (right != 0)
    {
        // More power to the left
        // left = throttle
        // right =
        float rightPow = (((throttle - ((throttle * right) / (throttle + right))) * 255) / 100);
        pinMode(speedPinB, OUTPUT);
        analogWrite(speedPinB, rightPow); // PWM Speed control
    }
    else
    {
        // More power to the left
        // left = throttle
        // right =
        float rightPow = (((throttle - ((throttle * left) / (throttle + left))) * 255) / 100);
        pinMode(speedPinB, OUTPUT);
        analogWrite(speedPinB, rightPow); // PWM Speed control
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
}

void loop()
{
    /* Direction are controlled by the PD of PinA 1&2 */
    if (foward)
    {
        analogWrite(speedPinA, 255); // PWM Speed control

        digitalWrite(dir1PinA, LOW);

        digitalWrite(dir2PinA, HIGH);
    }

    // Motor A

    analogWrite(speedPinA, 255); // PWM Speed control

    digitalWrite(dir1PinA, LOW);

    digitalWrite(dir2PinA, HIGH);

    // Motor B

    analogWrite(speedPinB, 255); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง

    digitalWrite(dir1PinB, LOW);

    digitalWrite(dir2PinB, HIGH);
}