#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>

// Configura tu red WiFi y los datos de Firebase
#define DATABASE_URL "xxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define API_KEY "xxxxxxxxxxxxxxxxxxxxxxx"
#define WIFI_SSID "xxxxxxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxxxxx"

/* Define el correo electrónico y la contraseña del usuario que ya se ha registrado en tu proyecto */
#define USER_EMAIL "xxxxxxxxxxxxxxx"
#define USER_PASSWORD "xxxxxxxxxxxxx"

/* Define la estructura de configuración de Firebase */
FirebaseConfig config;
FirebaseAuth auth;

// Firebase Data object
FirebaseData fbdo;

// Configura el lector RFID
#define SS_PIN 15  // Pin de seleccion SPI
#define RST_PIN 16 // Pin de reset

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }

  Serial.println("Conectado a WiFi");

//  /* Configura la estructura de configuración de Firebase */
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {
  Serial.println("Escanea RFID");
  // put your main code here, to run repeatedly:
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String cardUID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      cardUID += String(mfrc522.uid.uidByte[i], HEX);
    }

    Serial.println("UID de la tarjeta: " + cardUID);
        
    // Reemplace "asistencia" con el nombre de su coleccion en Firebase
    String path = "/prueba/" + cardUID;

    if (Firebase.setString(fbdo, path + "/IdUsuario", 1)) {
      Firebase.setString(fbdo, path + "/Nombre", "Juan");
      Firebase.setString(fbdo, path + "/Apellido", "Pérez");
      Firebase.setString(fbdo, path + "/CardUID", cardUID);
      Serial.println("Asistencia registrada en Firebase.");
    } else {
      Serial.println("Error al registrar la asistencia en Firebase: " + fbdo.errorReason());
    }

    delay(1000); // Evita múltiples registros en rápida sucesión
  }
}
