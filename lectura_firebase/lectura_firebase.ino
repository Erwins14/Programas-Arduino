#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>

// Configura tu red WiFi y los datos de Firebase
#define DATABASE_URL "esp8266-ceb36-default-rtdb.firebaseio.com"
#define API_KEY "AIzaSyAaApo7cviHp2gG-7YnhNCCz9vaUThu1x4"
#define WIFI_SSID "CLARO_rjNxKd"
#define WIFI_PASSWORD "C22DCDCC1D"

/* Define el correo electrónico y la contraseña del usuario que ya se ha registrado en tu proyecto */
#define USER_EMAIL "erwins1414@gmail.com"
#define USER_PASSWORD "UMG2023"

/* Define la estructura de configuración de Firebase */
FirebaseConfig config;
FirebaseAuth auth;

/* Define el objeto FirebaseData */
FirebaseData fbdo;

// Declarar variable global para almacenar valor
String val= "example";

/* Configura el lector RFID */
#define SS_PIN 15  // Pin de selección SPI
#define RST_PIN 16 // Pin de reset

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }

  Serial.println("Conectado a WiFi");

  /* 7. Configura la estructura de configuración de Firebase */
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  Firebase.begin(&config, &auth);

  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String cardUID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      cardUID += String(mfrc522.uid.uidByte[i], HEX);
    }

    Serial.println("UID de la tarjeta: " + cardUID);

    String path = "/usuarios/" + cardUID + "/cardUID";
    //String path = "/usuarios/";

    Serial.println(path);
    
    /* Realiza una consulta a Firebase para buscar al usuario por el UID */
    if (Firebase.getString(fbdo, path)) {
      if (fbdo.dataType() == "string") {
        Serial.println("Datos del usuario:");
        val = fbdo.stringData();
        Serial.println(val);
      } else {
        Serial.println("Error al obtener datos del usuario desde Firebase.");
      }
    } else {
      Serial.println("Usuario no encontrado en Firebase.");
    }

    delay(1000); // Evita múltiples consultas en rápida sucesión
  }
}
