// NES serial communication example
// Sends an incrementing value every 0.5s to the NES
//
// @munshkr (munshkr@gmail.com) / 2014-05-30

                                // NES color pinout:
const uint8_t LATCH_PIN = 3;    //  orange
const uint8_t DATA_PIN  = 4;    //  yellow
const uint8_t CLOCK_PIN = 5;    //  red
                                //  brown = GND

uint8_t value;

void setup()
{
    noInterrupts();

    pinMode(LATCH_PIN, INPUT); 
    pinMode(CLOCK_PIN, INPUT); 
    pinMode(DATA_PIN, OUTPUT); 

    attachInterrupt(1, latchISR, FALLING);

    value = 0;

    interrupts();
}

void loop()
{
    value++; 
    delay(500);
}

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

    for (i = 0; i < 8; i++)  {
        // wait for falling edge (1 to 0)
        while (digitalRead(clockPin) == HIGH);

        if (bitOrder == LSBFIRST) {
            digitalWrite(dataPin, !!(val & (1 << i)));
        } else {
            digitalWrite(dataPin, !!(val & (1 << (7 - i))));
        }
    
        // wait for rising edge (0 to 1)
        while (digitalRead(clockPin) == LOW);
    }   
}
