#include <Wire.h>

#define SERVO_ADDR 0x02

void Servo_write_us(uint8_t number, uint16_t us) {
    Wire.beginTransmission(SERVO_ADDR);
    Wire.write(0x00 | number);
    Wire.write(us & 0x00ff);
    Wire.write(us >> 8 & 0x00ff);
    Wire.endTransmission();
}

void Servo_write_angle(uint8_t number, uint8_t angle) {
    // Convert angle to pulse width (500 to 2500)
    uint16_t us = map(angle, 0, 180, 500, 2500);
    Servo_write_us(number, us);
}