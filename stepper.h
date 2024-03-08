#include <Module_GRBL_13.2.h>
#include <Wire.h>

#define STEPMOTOR_I2C_ADDR 0x70
Module_GRBL _GRBL = Module_GRBL(STEPMOTOR_I2C_ADDR);


#define X_LOCAL 40
#define Y_LOCAL 30

#define X_OFFSET 160
#define Y_OFFSET 23
#define rrmt_item32_timemout_us 9500


void stepper_setup() {
  String message = "Running stepper motor....\n";
  Serial.println(message);
  M5.Lcd.println(message);

  Wire.begin(21, 22);

  _GRBL.Init(&Wire);
  _GRBL.setMode("distance");
}

void stepperRun() {
  _GRBL.sendGcode("G1 X5 F150");
  //Serial.println(".");
  //delay(1000);
}

void stepperStop() {
  _GRBL.unLock();
  _GRBL.Init(&Wire);
  _GRBL.setMode("distance");
}