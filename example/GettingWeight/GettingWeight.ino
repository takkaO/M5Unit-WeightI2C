#include <M5Unified.h>
#include <M5GFX.h>
#include "M5UnitWeightI2C.h"

M5GFX display;
M5Canvas canvas(&display);
M5UnitWeightI2C weight_i2c;

void setup() {
    M5.begin();
    display.begin();
    display.setEpdMode(epd_mode_t::epd_fastest);
    canvas.setColorDepth(8);
    canvas.setFont(&fonts::efontCN_12);
    canvas.createSprite(display.width(), display.height());
    canvas.setTextSize(2);
    while (!weight_i2c.begin(&Wire, M5.Ex_I2C.getSDA(), M5.Ex_I2C.getSCL(),
                             DEVICE_DEFAULT_ADDR, 100000U)) {
        Serial.println("weight i2c connect error");
        canvas.clear(BLACK);
        canvas.setTextColor(RED);
        canvas.drawCenterString("No i2c device", display.width() / 2,
                                display.height() / 2);
        canvas.pushSprite(0, 0);
        delay(100);
    }
}

void loop() {
    float weight = weight_i2c.getWeight();
    float gap    = weight_i2c.getGapValue();
    int adc      = weight_i2c.getRawADC();

    canvas.fillSprite(BLACK);
    canvas.setTextSize(2);
    canvas.drawString("Unit Scale Weight Getting", 10, 10);
    canvas.setTextColor(WHITE);
    canvas.setCursor(10, 50);
    canvas.setTextSize(2);
    canvas.printf("WEIGHT:");
    canvas.setTextColor(GREEN);
    canvas.setTextSize(3);
    canvas.printf("%.2fg", weight);
    canvas.setCursor(10, 100);
    canvas.setTextColor(WHITE);
    canvas.setTextSize(2);
    canvas.printf("ADC:");
    canvas.setTextColor(GREEN);
    canvas.setTextSize(3);
    canvas.printf("%d", adc);
    canvas.setTextColor(ORANGE);
    canvas.setTextSize(2);
    canvas.drawString("[Offset]", 110, 210);
    canvas.pushSprite(0, 0);

    M5.update();
    if (M5.BtnB.wasPressed()) {
        weight_i2c.setOffset();
    }
}