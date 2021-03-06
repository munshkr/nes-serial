// NES serial communication example
// Sends an incrementing value every 0.5s to the NES

#define DEBUG
#define MIDI_BRIDGE

#include <MIDI.h>

volatile uint8_t value;
volatile unsigned long latchTs;

uint8_t buttons[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };

void setup()
{
    noInterrupts();

    // Define outputs for DATA
    //         D11-D8
    DDRB |= B00001111;    // Low nibble of DDRB  => low nibble of DATA
    //      D7-D4
    DDRD |= B11110000;    // High nibble of DDRD => high nibble of DATA

    attachInterrupt(0, latchISR, RISING);

    latchTs = micros();
    setValue(0);    // send nothing

    interrupts();

    MIDI.begin();

    #ifdef MIDI_BRIDGE
      Serial.begin(115200);
    #endif

    MIDI.setHandleNoteOn(handleNoteOn);
}

void loop() {
    MIDI.read();
}

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
    value = buttons[pitch % 8];
}

// Sets value in bits using 8 output pins (D4-D11)
inline void setValue(uint8_t value)
{
    // NOTE The NES inverts all bits sent on DATA, so we invert them here too.
    PORTB = (PORTB & 0xf0) | (~value & 0x0f);
    PORTD = (PORTD & 0x0f) | (~value & 0xf0);
}

void latchISR()
{
    // The NES is trying to latch to the controller and read its values, so we
    // set a new value as fast as we can with setValue()

    // TODO Check how much time it takes the NES to poll the joystick
    // and adjust microseconds here.
    unsigned long nowTs = micros();
    if (nowTs - latchTs < 1000) return;

    setValue(value);

    latchTs = nowTs;
}
