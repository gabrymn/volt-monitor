#include <WiFi.h>
#include <HTTPClient.h>
#include <config.h>

// 15 minutes would be 15 * 60 * 1000, since it's in ms
const unsigned long TIME_RANGE = 12 * 60 * 1000; 

unsigned long last_ping = 0;

void setup() {

	Serial.begin(115200);

	WiFi.begin(WIFI_SSID, WIFI_PASS);
	Serial.print("WiFi connection...");

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("\nWiFi connection ok");
	Serial.print("Local IP: ");
	Serial.println(WiFi.localIP());
}

void inviaPing() {

	HTTPClient http;

	Serial.print("ping: ");
	Serial.println(SERVER_URL);

	http.begin(SERVER_URL);

	int httpCode = http.GET();

	if (httpCode > 0) {
	
		Serial.print("Ping success, HTTP response code: ");
		Serial.println(httpCode);

	} else {
	
		Serial.print("Ping error, HTTP response code: ");
		Serial.println(http.errorToString(httpCode).c_str());
	}

	http.end(); 
}

void loop() {

	if (WiFi.status() != WL_CONNECTED) 
	{
		Serial.println("WiFi disconnected! Trying to reconnect...");
		WiFi.disconnect();
		WiFi.reconnect();
		delay(5000); 
		return;
	}

	if (millis() - last_ping >= TIME_RANGE || last_ping == 0) 
	{
		last_ping = millis();
		inviaPing();
	}
	
	delay(1000); // optimization
}








