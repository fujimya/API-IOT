#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

char terima[3];
String hasil;
String suhu = "";
String kelembapan = "";
ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);
  WiFiMulti.addAP("gin", "qwerty.123");
  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print("Menyambungkan.");
    delay(100);
    Serial.print(".");
    delay(100);
    Serial.print(".");
    delay(100);
    Serial.print(".");
    delay(100);
    Serial.print(".");
    delay(100);
    Serial.println(".");
    delay(100);

  }
  Serial.println("Terhubung");
}
void loop() {
  while (Serial.available() > 0)
  {
    terima[3] = Serial.read();
    //Serial.println(terima[3]);
    if (terima[3] == '*') {
      suhu = hasil;
//      Serial.println(suhu);
      Serial.println(hasil);
      hasil = "";
      terima[3] = ' ';
    }
    if (terima[3] == '#') {
      kelembapan = hasil;
      Serial.println(hasil);
      hasil = "";
      terima[3] = ' ';
    }
    if (terima[3] != ' ') {
      hasil += terima[3];
    }

    if (suhu != "" && kelembapan != "") {
      Serial.println(suhu);
      Serial.println(kelembapan);
      setData(suhu, kelembapan);
      suhu = "";
      kelembapan = "";
    }
    //Serial.println(hasil);
  }



  delay(200);

}
void setData(String suhu, String kelembapan)
{
  String ref = "http://rumo.web.id/Simpan/Store/";
  if ((WiFiMulti.run() == WL_CONNECTED)) {


    ref += suhu;
    ref += "/";
    ref += kelembapan;
    HTTPClient http;
    http.begin(ref);
    int httpCode = http.GET();
    Serial.println(ref);

    if (httpCode > 0) {
      Serial.print("Data terkirim");
      Serial.println(ref);
      if (httpCode == HTTP_CODE_OK)
      {
        digitalWrite(2, HIGH);
        delay(300);
        digitalWrite(2, LOW);
        delay(300);
      }
    }
    else {
      digitalWrite(2, HIGH);
      delay(2000);

      digitalWrite(2, LOW);
      delay(200);
      digitalWrite(2, HIGH);
      delay(100);
      digitalWrite(2, LOW);
    }
    http.end();

  }
}
