#include <WiFi.h>
#include <HTTPClient.h>
#include <config.h>

// milliseconds
const unsigned long TIME_RANGE = 2 * 60 * 1000; 
unsigned long last_ping = 0;

String server_url;

void setup() {

	Serial.begin(115200);
	
	server_url = String("https://cronitor.link/p/") + USER_ID + "/" + MONITOR_KEY + "?msg=success";
	
	WiFi.begin(WIFI_SSID, WIFI_PASS);
	Serial.print("WiFi connection...");

	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.print("Connection failed... ");
	}

	Serial.println("\nWiFi connection ok");
	Serial.print("Local IP: ");
	Serial.println(WiFi.localIP());
}

void mping() {
	
	HTTPClient http;

	Serial.print("Ping: ");
	Serial.println(server_url);
	
	http.begin(server_url);

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
		mping();
	}
	
	delay(1000); // optimization
}








