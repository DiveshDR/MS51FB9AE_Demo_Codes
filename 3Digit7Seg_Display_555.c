#include "MS51_16K.H"

// Define segment pins using sbit for clarity
sbit SEG_A = P1^3;  // Segment A (P1.3)
sbit SEG_B = P0^0;  // Segment B (P0.0)
sbit SEG_C = P1^5;  // Segment C (P1.5)
sbit SEG_D = P0^3;  // Segment D (P0.3)
sbit SEG_E = P0^1;  // Segment E (P0.1)
sbit SEG_F = P1^2;  // Segment F (P1.2)
sbit SEG_G = P1^7;  // Segment G (P1.7)
sbit SEG_DP = P0^4; // Decimal Point (P0.4)

// Define common anode pins for digits
sbit DIGIT1 = P1^0; // Common Anode 1 (P1.0)
sbit DIGIT2 = P1^1; // Common Anode 2 (P1.1)
sbit DIGIT3 = P1^4; // Common Anode 3 (P1.4)

// Delay function (tuned for ~16 MHz system clock, from reference code)
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 160; j++); // Approx. 0.48 ms per iteration
}

void main(void) {
    // Configure Port 0 pins (P0.0, P0.1, P0.3, P0.4) as push-pull outputs
    P0M1 &= ~0x1B; // Clear bits 0, 1, 3, 4 (00011011)
    P0M2 |= 0x1B;  // Set bits 0, 1, 3, 4 as push-pull

    // Configure Port 1 pins (P1.0, P1.1, P1.2, P1.3, P1.4, P1.5, P1.7) as push-pull outputs
    P1M1 &= ~0xBF; // Clear bits 0, 1, 2, 3, 4, 5, 7 (10111111)
    P1M2 |= 0xBF;  // Set bits 0, 1, 2, 3, 4, 5, 7 as push-pull

    // Initialize all digits off (common anode low)
    DIGIT1 = 0;
    DIGIT2 = 0;
    DIGIT3 = 0;

    // Set segment pattern for digit '5' (A, C, D, F, G on; B, E, DP off)
    // For common anode: 0 = on, 1 = off
    SEG_A = 0;  // On
    SEG_B = 1;  // Off
    SEG_C = 0;  // On
    SEG_D = 0;  // On
    SEG_E = 1;  // Off
    SEG_F = 0;  // On
    SEG_G = 0;  // On
    SEG_DP = 1; // Off

    // Multiplexing loop to display "555"
    while (1) {
        // Display Digit 1
        DIGIT1 = 1; // Turn on Digit 1
        DIGIT2 = 0;
        DIGIT3 = 0;
        delay_ms(5); // ~2.4 ms on-time
        DIGIT1 = 0;  // Turn off Digit 1

        // Display Digit 2
        DIGIT2 = 1; // Turn on Digit 2
        DIGIT1 = 0;
        DIGIT3 = 0;
        delay_ms(5);
        DIGIT2 = 0;  // Turn off Digit 2

        // Display Digit 3
        DIGIT3 = 1; // Turn on Digit 3
        DIGIT1 = 0;
        DIGIT2 = 0;
        delay_ms(5);
        DIGIT3 = 0;  // Turn off Digit 3
    }
}
