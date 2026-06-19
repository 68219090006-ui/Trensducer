#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
	Serial.begin(9600);
	dht.begin();
	Serial.println("Start reading DHT11 sensor...");
}

void loop() {
	float humidity = dht.readHumidity();
	float temperature = dht.readTemperature();

	if (isnan(humidity) || isnan(temperature)) {
		Serial.println("Failed to read from DHT11 sensor");
	} else {
		Serial.print("Temperature: ");
		Serial.print(temperature);
		Serial.println(" C");

		Serial.print("Humidity: ");
		Serial.print(humidity);
		Serial.println(" %");

		Serial.println("--------------------");
	}

	delay(2000);
}
