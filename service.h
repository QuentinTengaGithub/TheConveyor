#include <HTTPClient.h>
#include <ArduinoJson.h>

void getAllProducts() {
  // Initialisez l'objet HTTPClient
  HTTPClient http;
 
  // Spécifiez l'URL de l'API Dolibarr
  String apiUrl = "https://objective-bell.93-90-203-17.plesk.page/api/index.php/products";
 
  // Spécifiez la clé API dans le header
  String apiKey = "8bdff6564b53d94a13ec4bf0e581563d561b6790";
  
  // Spécifiez les données à envoyer au format JSON
  //String jsonData = "{\"votre_champ\":\"nouvelle_valeur\"}";  // Remplacez avec vos propres champs et valeurs
 
  // Définissez l'URL, la méthode et les en-têtes
  http.begin(apiUrl);
  //http.addHeader("Content-Type", "application/json");
  http.addHeader("DOLAPIKEY", apiKey);
 
  // Envoyez la requête PUT avec les données JSON
  int httpResponseCode = http.GET();
 
  // Affichez la réponse du serveur
  M5.Lcd.println("Code de réponse HTTP : ");
  M5.Lcd.println(httpResponseCode);
 
  // Si la requête a réussi, affichez la réponse du serveur
  if (httpResponseCode > 0) {
    String response = http.getString();
    M5.Lcd.println("Réponse du serveur : " + response);
  } else {
    M5.Lcd.println("Erreur lors de la requête GET");
  }
 
  // Libérez les ressources
  http.end();
}
 
JsonDocument getProductByRef(char *ref){
  // Initialisez l'objet HTTPClient
  HTTPClient http;
 
  // Spécifiez l'URL de l'API Dolibarr
  //String apiUrl = "https://objective-bell.93-90-203-17.plesk.page/api/index.php/products/ref/"+ref;
  // Spécifiez l'URL de l'API Dolibarr
  const char* apiUrlBase = "https://objective-bell.93-90-203-17.plesk.page/api/index.php/products/ref/";
  String apiUrl = String(apiUrlBase) + ref;
 
  // Spécifiez la clé API dans le header
  String apiKey = "8bdff6564b53d94a13ec4bf0e581563d561b6790";
 
  // Définissez l'URL, la méthode et les en-têtes
  http.begin(apiUrl);
  //http.addHeader("Content-Type", "application/json");
  http.addHeader("DOLAPIKEY", apiKey);
 
  // Envoyez la requête PUT avec les données JSON
  int httpResponseCode = http.GET();
 
  // Affichez la réponse du serveur
  M5.Lcd.println("Code de réponse HTTP : ");
  M5.Lcd.println(httpResponseCode);
 
  // Si la requête a réussi, affichez la réponse du serveur
  if (httpResponseCode > 0) {
    // Fetch the product
    String response = http.getString();
    // Get the warehouse ID
    JsonDocument doc;
    deserializeJson(doc, response);

    //M5.Lcd.println("Réponse du serveur : " + response)
    //Serial.print("Product infos : " + response);
    // Libérez les ressources
    http.end();
    return doc;
  } else {
    //M5.Lcd.println("Erreur lors de la requête GET");
    Serial.print("Erreur lors de la requête GET");
    // Libérez les ressources
    http.end();
  }
}

int addProductToWarehouse(int productId, int warehouseId, int qty = 1) {
  // Initialisez l'objet HTTPClient
  HTTPClient http;

  // Spécifiez l'URL de l'API Dolibarr
  const char* apiUrl = "https://objective-bell.93-90-203-17.plesk.page/api/index.php/stockmovements";
  // Spécifiez la clé API dans le header
  const char* apiKey = "8bdff6564b53d94a13ec4bf0e581563d561b6790";
  
  // Définissez l'URL, la méthode et les en-têtes
  http.begin(apiUrl);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("DOLAPIKEY", apiKey);

  // Construisez la chaîne JSON correctement
  String jsonData = "{\"product_id\":" + String(productId) + ",\"warehouse_id\":" + String(warehouseId) + ",\"qty\":" + String(qty) + "}";
  
  // Envoyez la requête POST avec les données JSON
  int httpResponseCode = http.POST(jsonData);

  // Libérez les ressources de l'objet HTTPClient
  http.end();

  return httpResponseCode;
}
