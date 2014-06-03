// NES serial communication example
// Sends an incrementing value every 0.5s to the NES

const uint8_t LED_PIN = 13;
const uint8_t INPUT_PINS[8] = { 9, 8, 7, 6, 5, 4, 3, 2 };

uint8_t value;

void setup()
{
    // enable led, turn off
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    for (int i = 0; i < 8; i++) {
        pinMode(INPUT_PINS[i], OUTPUT);
        digitalWrite(INPUT_PINS[i], HIGH);
    }

    value = 0;

    Serial.begin(9600);
}

void loop()
{
    delay(100);

    value++;
    sendValue(value);
    Serial.println(value);

    // flash led
    digitalWrite(LED_PIN, HIGH);
    delay(50);
    digitalWrite(LED_PIN, LOW);
}

// Sends value in bits using the 8 output pins
void sendValue(uint8_t value)
{
    for (int i = 7; i >= 0; i--) {
        int res = value >> i;
        digitalWrite(INPUT_PINS[i], !(res & 1));
    }  
}
