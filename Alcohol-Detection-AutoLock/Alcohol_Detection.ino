#define sensorAnalog A0
#define Motor 9
#define buzzer 8

void setup() {
    pinMode(Motor, OUTPUT);
    pinMode(buzzer, OUTPUT);
    Serial.begin(9600);

    delay(20000); // Warm-up time for sensor
}

void loop() {
    int alcoholLevel = analogRead(sensorAnalog);
    
    // Stabilizing noisy readings (Average over 5 samples)
    int avgAlcohol = 0;
    for (int i = 0; i < 5; i++) {
        avgAlcohol += analogRead(sensorAnalog);
        delay(10); // Small delay between readings
    }
    avgAlcohol /= 5;

    Serial.print("Alcohol Level: ");
    Serial.println(avgAlcohol);

    if (avgAlcohol > 700) {  // Adjust threshold based on real test values
        Serial.println("Accident Detected! Alcohol Level: " + String(avgAlcohol));
        digitalWrite(Motor, LOW);  // Lock motor
        digitalWrite(buzzer, HIGH); // Activate buzzer
    } else {
        digitalWrite(Motor, HIGH);  // Unlock motor
        digitalWrite(buzzer, LOW);  // Turn off buzzer
    }

    delay(1000); // Small delay for readability
}

