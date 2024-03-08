#include "MFRC522_I2C.h"
MFRC522 mfrc522(0x28);  // Create MFRC522 instance.  
 
void rfidSetup() {
    M5.Lcd.println("MFRC522 Configration...");
    Wire.begin();  // Wire init, adding the I2C bus.  Wire
    mfrc522.PCD_Init();  // Init MFRC522.
    M5.Lcd.println("Please put the card\n\nUID:");
}
char* rfidRead() {
  static char ref[16];  // Réservez un espace pour stocker la référence (assurez-vous que c'est suffisamment grand)
  
  M5.Lcd.setCursor(40, 47);
  if (!mfrc522.PICC_IsNewCardPresent() ||
      !mfrc522.PICC_ReadCardSerial()) {
      delay(200);
      return "";  // Aucune carte détectée, retourne une chaîne vide
  }

  for (byte i = 0; i < mfrc522.uid.size; i++) {
      M5.Lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      M5.Lcd.print(mfrc522.uid.uidByte[i], HEX);

      // Convertir chaque octet en caractère et ajouter à la chaîne ref
      sprintf(ref + i * 2, "%02X", mfrc522.uid.uidByte[i]);
  }
  ref[16] = '\0';  // Ajouter le caractère nul de fin de chaîne
  
  return ref;
}