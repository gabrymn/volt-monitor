#include <WiFi.h>
#include <HTTPClient.h>
#include <config.h>

// 12 minutes => 12 micro secondi * 60 * 1000000
#define TIME_TO_SLEEP  12 * 60 * 1000000 

void setup() {
	
	Serial.begin(115200);

	WiFi.begin(WIFI_SSID, WIFI_PASS);
	Serial.print("WiFi connection...");

	int tentativi = 0;

	while (WiFi.status() != WL_CONNECTED && tentativi < 20) 
	{
		delay(500);
		Serial.print(".");
		tentativi++;
	}

	if (WiFi.status() == WL_CONNECTED) 
	{
		Serial.println("\nWiFi OK");

		HTTPClient http;
		http.begin(SERVER_URL);
		int httpCode = http.GET();
		http.end();

		Serial.printf("Ping inviato, risposto: %d\n", httpCode);
	} 
	else 
	{
		Serial.println("\nImpossibile connettersi al WiFi");
	}

	Serial.println("12 minutes in deep sleep...");
	esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP);
	esp_deep_sleep_start();
}

void loop() {}
