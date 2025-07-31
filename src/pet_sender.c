// simplified version of the petpix client.
// reads from stdin 1000 bytes at a time, and sends that to the pet.
// uses CA1/CB2 handshaking

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>

#define DIR                 40
#define OUTPUT_ENABLE_BAR   38
#define DATA0               36
#define DATA1               32
#define DATA2               28
#define DATA3               35
#define DATA4               33
#define DATA5               31
#define DATA6               29
#define DATA7               37
#define CA1                 16
#define CB2                 18

uint8_t data_pins[8] = {
    DATA0, DATA1, DATA2, DATA3, DATA4, DATA5, DATA6, DATA7
};

void output_byte(uint8_t val) {
    for (int i = 0; i < 8; i++) {
        digitalWrite(data_pins[i], (val >> i) & 1);
    }
}

void send_byte_sequence(uint8_t *buffer, size_t length, int delay_us) {
    for (size_t i = 0; i + 1 < length; i += 2) {
        uint8_t value1 = buffer[i];
        uint8_t value2 = buffer[i + 1];

        output_byte(value1);
        digitalWrite(CA1, LOW);
        delayMicroseconds(delay_us);
        digitalWrite(CA1, HIGH);
        while (digitalRead(CB2) != LOW);

        output_byte(value2);
        digitalWrite(CA1, LOW);
        delayMicroseconds(delay_us);
        digitalWrite(CA1, HIGH);
        while (digitalRead(CB2) != HIGH);
    }
}

int main() {
    wiringPiSetupPhys();

    pinMode(DIR, OUTPUT);
    pinMode(OUTPUT_ENABLE_BAR, OUTPUT);
    digitalWrite(DIR, LOW);
    digitalWrite(OUTPUT_ENABLE_BAR, LOW);

    for (int i = 0; i < 8; i++) {
        pinMode(data_pins[i], OUTPUT);
    }

    pinMode(CA1, OUTPUT);
    pinMode(CB2, INPUT);
    digitalWrite(CA1, HIGH);

    uint8_t buffer[1000];

    while (1) {
        size_t read_count = fread(buffer, 1, 1000, stdin);
        if (read_count == 0) break;
        send_byte_sequence(buffer, read_count, 5);
    }

    return 0;
}
