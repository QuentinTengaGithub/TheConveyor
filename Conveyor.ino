#include <M5Stack.h>
#include "wifi.h"
#include "rfid.h"
#include "service.h"
#include <ArduinoJson.h>
#include "servoMotor.h"
#include "GoPlus2.h"
#include "IRSensor.h"
#include <driver/rmt.h>
#include <math.h>
#include "GoPlus2Lib.h"
#include <Module_GRBL_13.2.h>
#include  "stepper.h"
 
const char *ssid     = "Wifeye";
const char *password = "abcd1234";

#define IR_RECV_PIN 36
#define IR_SEND_PIN 26

char *ref;


int getWarehouseAngle(String warehouse){
    if(warehouse == "1"){
      return 32;
    }
    else if (warehouse == "2"){
      return 44;
    }
    else if (warehouse == "3"){
      return 19;
    }
}


void setup() {
  
  M5.begin();
  M5.Power.begin();
  
  goPlus.begin();
  Serial.begin(9600);
  rx_channel_init();
  tx_channel_init();
 
  // Set text size
  M5.Lcd.setTextSize(3);
  
  // Connect wifi
  connectWifi(ssid, password);
  delay(1000);
  
  // init rfid
  Serial.println("Set up the RFID");
  rfidSetup();

  header("GoPlus 2", TFT_BLACK);
  attachInterrupt(digitalPinToInterrupt(38), doTask, RISING);

  stepper_setup();
  goPlus.Servo_write_angle(SERVO_NUM0, 25);
}
 
void loop() {
  if(WiFi.status() == WL_CONNECTED) {
      // Run the stepper Motor
      stepperRun();

      // Read the RFID Tag and get the ref 
      ref = rfidRead();
      // Display the ref
      M5.Lcd.println(ref);
      //Serial.println("Product reference : "+  ref);
    // if the ref exist and is not void
      if(ref && ref !=""){
        // Send a request to the API to get the product details using the ref
        JsonDocument product = getProductByRef(ref);
        Serial.println("The product from dolibar : ");
        //Serial.println(product);
        
        // Get the product warehouse ID and define the right angle for the servo motor to direct the products
        String warehouseId = product["fk_default_warehouse"];
        int angle = getWarehouseAngle(warehouseId);
        M5.Lcd.println("Angle du servo : "+ String(angle));
        Serial.println("Angle du servo : "+ String(angle));

        // Direct the servomotor to the right angle
        goPlus.Servo_write_angle(SERVO_NUM0, angle);
        Serial.println("Directed to the warehouse");
        delay(5000);
        goPlus.Servo_write_angle(SERVO_NUM0, 30);
        // Request to the API to move the product to the right warehouse
        addProductToWarehouse(product["id"], product["fk_default_warehouse"]);

        }
  }
}