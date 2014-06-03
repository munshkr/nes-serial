// NES serial communication example
// Sends an incrementing value every 0.5s to the NES
//
// @munshkr (munshkr@gmail.com) / 2014-05-30

                                // NES color pinout:
const uint8_t LATCH_PIN = 3;    //  orange
const uint8_t DATA_PIN  = 4;    //  yellow
const uint8_t CLOCK_PIN = 5;    //  red
                                //  brown = GND
const uint8_t LED_PIN = 13;

volatile uint8_t value;

void setup()
{
    pinMode(LATCH_PIN, INPUT_PULLUP);
    pinMode(CLOCK_PIN, INPUT_PULLUP);
    pinMode(DATA_PIN, OUTPUT);

    digitalWrite(DATA_PIN, LOW);

    // enable led, turn off
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    value = 0;

    attachInterrupt(1, latchISR, RISING);
}

void loop()
{
    value++;
    delay(1000);

    // flash led
    digitalWrite(LED_PIN, HIGH);
    delay(50);
    digitalWrite(LED_PIN, LOW);
}

// This ISR must be attached to the latch pin on a RISING edge.
// Check NES controller data flow for reference.
//
void latchISR()
{
    shiftOutWithClk(DATA_PIN, CLOCK_PIN, LSBFIRST, value);
}

// Same as shiftOut, but uses the clockPin as an external clock,
// and writes to dataPin after each rising edge of that clock.
//
void shiftOutWithClk(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
{
    uint8_t i;
    uint8_t vb;

    for (i = 0; i < 8; i++)  {
        if (bitOrder == LSBFIRST) {
            vb = !!(val & (1 << i));
        } else {
            vb = !!(val & (1 << (7 - i)));
        }

        // write the inverted value (NES inverts it)
        digitalWrite(dataPin, !vb);

        // wait for a full cycle of the clock
        while (digitalRead(clockPin) == HIGH);
        while (digitalRead(clockPin) == LOW);
    }

    digitalWrite(dataPin, LOW);
}
