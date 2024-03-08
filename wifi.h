#include <WiFi.h>
void connectWifi(const char *ssid,const char *password ) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        M5.Lcd.print(".");
    }
    M5.Lcd.println("\nWiFi connected");
}
