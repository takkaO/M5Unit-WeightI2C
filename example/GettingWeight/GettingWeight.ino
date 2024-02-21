/**
 * @file GettingWeight.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief
 * @version 0.1
 * @date 2024-02-21
 *
 *
 * @Hardwares: M5Core + Unit Weight I2C
 * @Platform Version: Arduino M5Stack Board Manager v2.1.0
 * @Dependent Library:
 * M5UnitWeightI2C: https://github.com/m5stack/M5Unit-WeightI2C
 */

#include "M5UnitWeightI2C.h"

M5UnitWeightI2C weight_i2c;

void setup() {
    Serial.begin(115200);
    while (!weight_i2c.begin(&Wire, 21, 22, DEVICE_DEFAULT_ADDR, 100000U)) {
        Serial.println("weight i2c connect error");
        delay(100);
    }
    weight_i2c.setOffset();
}

void loop() {
    float weight = weight_i2c.getWeight();
    float gap    = weight_i2c.getGapValue();
    int adc      = weight_i2c.getRawADC();

    Serial.printf("WEIGHT:");
    Serial.printf("%.2fg\r\n", weight);
    Serial.printf("ADC:");
    Serial.printf("%d\r\n", adc);
    Serial.printf("GAP:");
    Serial.printf("%.2f\r\n", gap);
    delay(1000);
}
