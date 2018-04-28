/****************************************************************************/
//  Function:       Header file for TroykaAccelerometer
//  Hardware:       ADXL335
//  Arduino IDE:    Arduino-1.8.3
//  Author:         Igor Dementiev
//  Date:           Apr 25,2018
//  Version:        v1.0.0
//  by www.amperka.ru
/****************************************************************************/

#ifndef TROYKA_ACCELEROMETER_H_
#define TROYKA_ACCELEROMETER_H_

#include <Arduino.h>

#if defined(__AVR__)
#define OPERATING_VOLTAGE   5.0

#elif defined(__SAM3X8E__) || defined(__SAM3A8C__) || defined(__SAM3A4C__) || defined(__SAMD21G18A__) || defined(ARDUINO_ARCH_ESP8266) || defined(__arm__)
#define OPERATING_VOLTAGE   3.3
#endif

#define AREF                3.3

#define DEFAULT             1
#define EXTERNAL            0

#define G                   9.8
#define SAMPLE_TIMES        5
#define ADC_BIT             10
#define ADC_VALUE_MAX       pow(2, ADC_BIT)

class TroykaAccelerometer
{
public:
    TroykaAccelerometer(uint8_t pinX, uint8_t pinY, uint8_t pinZ);
    void calibrate(float minVoltageX = 1.20, float maxVoltageX = 1.80, float minVoltageY = 1.20, float maxVoltageY = 1.80, float minVoltageZ = 1.25, float maxVoltageZ = 1.85);
    void setAnalogReference(uint8_t modeAnalogReference);
    float readVoltageX();
    float readVoltageY();
    float readVoltageZ();
    float readGX();
    float readGY();
    float readGZ();
    float readAX();
    float readAY();
    float readAZ();
    float getPitch();
    float getRoll();
private:
    uint8_t _pinX;
    uint8_t _pinY;
    uint8_t _pinZ;
    uint8_t _modeAnalogReference;
    float _zeroVoltageX;
    float _zeroVoltageY;
    float _zeroVoltageZ;
    float _sensitivityX;
    float _sensitivityY;
    float _sensitivityZ;
    float readVoltage(uint8_t pin);
};
#endif  // TROYKA_ACCELEROMETER_H_
