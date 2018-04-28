/****************************************************************************/
//  Function:       Cpp file for TroykaAccelerometer
//  Hardware:       ADXL335
//  Arduino IDE:    Arduino-1.8.3
//  Author:         Igor Dementiev
//  Date:           Apr 25,2018
//  Version:        v1.0.0
//  by www.amperka.ru
/****************************************************************************/

#include "TroykaAccelerometer.h"

TroykaAccelerometer::TroykaAccelerometer(uint8_t pinX, uint8_t pinY, uint8_t pinZ) {
    _pinX = pinX;
    _pinY = pinY;
    _pinZ = pinZ;
    _modeAnalogReference = DEFAULT;
}

void TroykaAccelerometer::calibrate(float minVoltageX, float maxVoltageX, float minVoltageY, float maxVoltageY, float minVoltageZ, float maxVoltageZ) {
    _zeroVoltageX = (minVoltageX + maxVoltageX) / 2.0;
    _zeroVoltageY = (minVoltageY + maxVoltageY) / 2.0;
    _zeroVoltageZ = (minVoltageZ + maxVoltageZ) / 2.0;
    _sensitivityX = maxVoltageX - _zeroVoltageX;
    _sensitivityY = maxVoltageY - _zeroVoltageY;
    _sensitivityZ = maxVoltageZ - _zeroVoltageZ;
}

void TroykaAccelerometer::setAnalogReference(uint8_t modeAnalogReference) {
    _modeAnalogReference = modeAnalogReference;
    analogReference(_modeAnalogReference);
}

float TroykaAccelerometer::readVoltageX() {
    return readVoltage(_pinX);
}

float TroykaAccelerometer::readVoltageY() {
    return readVoltage(_pinY);
}

float TroykaAccelerometer::readVoltageZ() {
    return readVoltage(_pinZ);
}

float TroykaAccelerometer::readGX() {
    return (readVoltageX() - _zeroVoltageX) / _sensitivityX;
}

float TroykaAccelerometer::readGY() {
    return (readVoltageY() - _zeroVoltageY) / _sensitivityY;
}

float TroykaAccelerometer::readGZ() {
    return (readVoltageZ() - _zeroVoltageZ) / _sensitivityZ;
}

float TroykaAccelerometer::readAX() {
    return readGX() * G;
}

float TroykaAccelerometer::readAY() {
    return readGY() * G;
}

float TroykaAccelerometer::readAZ() {
    return readGZ() * G;
}

float TroykaAccelerometer::getPitch() {
    return atan2(readGX(), readGZ()) * 180 / M_PI;
}

float TroykaAccelerometer::getRoll() {
    return atan2(-readGY(), readGZ()) * 180 / M_PI;
}

float TroykaAccelerometer::readVoltage(uint8_t pin) {
    int sensorADC = 0;
    float sensorVoltage = 0;
    for (uint8_t i = 0; i < SAMPLE_TIMES; i++) {
        sensorADC += analogRead(pin);
    }
    sensorADC = sensorADC / SAMPLE_TIMES;
    if (_modeAnalogReference == DEFAULT) {
       sensorVoltage = sensorADC * OPERATING_VOLTAGE / ADC_VALUE_MAX; 
   } else {
        sensorVoltage = sensorADC * AREF / ADC_VALUE_MAX;
   }
   return sensorVoltage;
}

