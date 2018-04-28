// библиотека для работы с аналоговым акселерометром
#include <TroykaAccelerometer.h>

// пины подключения осей акселерометра
#define PIN_X A1
#define PIN_Y A2
#define PIN_Z A0

// калибровочные значения одного из акселерометров
// для получения калибровочных значений воспользуйтесь скетчем «AcelerometerCalibration»
// и программой «AccelCalibration»
// подробности читайте в статье на вики:
// http://wiki.amperka.ru/продукты:troyka-analog-accelerometer

#define MIN_X   1.20
#define MAX_X   1.80
#define MIN_Y   1.20
#define MAX_Y   1.80
#define MIN_Z   1.25
#define MAX_Z   1.85

// создаём объект для работы с аналоговым акселерометром
TroykaAccelerometer accel(PIN_X, PIN_Y, PIN_Z);

void setup() {
  // открываем последовательный порт
  Serial.begin(9600);
  Serial.println("Serial begin is OK");
  // каждый акселерометр необходмо калибровать индивидуально
  // калибруем акселерометр по калибровочным значениям одного из партии
  accel.calibrate(MIN_X, MAX_X, MIN_Y, MAX_Y, MIN_Z, MAX_Z);
}

void loop() {
  // выводим направление и величины ускорения в единицах «g»
  Serial.print(accel.readGX());
  Serial.print("\t");
  Serial.print(accel.readGY());
  Serial.print("\t");
  Serial.print(accel.readGZ());
  Serial.print("\t");
  // выводим направление и величины ускорения в «м/с²»
  Serial.print(accel.readAX());
  Serial.print("\t");
  Serial.print(accel.readAY());
  Serial.print("\t");
  Serial.println(accel.readAZ());
  delay(100);
}
