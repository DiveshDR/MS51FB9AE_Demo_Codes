#include "MS51_16K.H"

//change the display arrray to print
// Define segment pins
sbit SEG_A = P1^3;  // Segment A (P1.3)
sbit SEG_B = P0^0;  // Segment B (P0.0)
sbit SEG_C = P1^5;  // Segment C (P1.5, corrected from P0.15)
sbit SEG_D = P0^3;  // Segment D (P0.3)
sbit SEG_E = P0^1;  // Segment E (P0.1)
sbit SEG_F = P1^2;  // Segment F (P1.2)
sbit SEG_G = P1^7;  // Segment G (P1.7)
sbit SEG_DP = P0^4; // Decimal Point (P0.4)

// Define digit common pins
sbit DIGIT1 = P1^4; // Common Anode 1 (P1.4)
sbit DIGIT2 = P1^1; // Common Anode 2 (P1.1)
sbit DIGIT3 = P1^0; // Common Anode 3 (P1.0)

// Delay function (tuned for ~16MHz system clock)
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 160; j++); // Approx. 0.48ms per iteration
}

// Function to set segments based on a character
void set_segments(char c) {
    // Turn off all segments
    SEG_A = 1;
    SEG_B = 1;
    SEG_C = 1;
    SEG_D = 1;
    SEG_E = 1;
    SEG_F = 1;
    SEG_G = 1;
    SEG_DP = 1; // Decimal point always off

    // Set segment patterns based on the input character
    switch (c) {
        case '0':
            SEG_A = 0; SEG_B = 0; SEG_C = 0;
            SEG_D = 0; SEG_E = 0; SEG_F = 0;
            break;
        case '1':
            SEG_B = 0; SEG_C = 0;
            break;
        case '2':
            SEG_A = 0; SEG_B = 0; SEG_D = 0;
            SEG_E = 0; SEG_G = 0;
            break;
        case '3':
            SEG_A = 0; SEG_B = 0; SEG_C = 0;
            SEG_D = 0; SEG_G = 0;
            break;
        case '4':
            SEG_B = 0; SEG_C = 0; SEG_F = 0;
            SEG_G = 0;
            break;
        case '5':
            SEG_A = 0; SEG_C = 0; SEG_D = 0;
            SEG_F = 0; SEG_G = 0;
            break;
        case '6':
            SEG_A = 0; SEG_C = 0; SEG_D = 0;
            SEG_E = 0; SEG_F = 0; SEG_G = 0;
            break;
        case '7':
            SEG_A = 0; SEG_B = 0; SEG_C = 0;
            break;
        case '8':
            SEG_A = 0; SEG_B = 0; SEG_C = 0;
            SEG_D = 0; SEG_E = 0; SEG_F = 0;
            SEG_G = 0;
            break;
        case '9':
            SEG_A = 0; SEG_B = 0; SEG_C = 0;
            SEG_D = 0; SEG_F = 0; SEG_G = 0;
            break;
        case 'R':
        case 'r':
            SEG_A = 0; SEG_B = 0; SEG_C = 0;
            SEG_E = 0; SEG_F = 0;
            break;
        case 'D':
        case 'd':
            SEG_A = 0; SEG_B = 0; SEG_C = 0;
            SEG_D = 0; SEG_G = 0;
            break;
        case 'H':
        case 'h':
            SEG_A = 0; SEG_F = 0; SEG_G = 0;
            SEG_E = 0;
            break;
        default:
            // All segments off for unsupported characters
            break;
    }
}

void main(void) {
    // Declare display array at the start of main
    char display[3] = {'1', '2', '3'}; // Change to {'1', '2', '3'} or {'R', 'D', 'H'}

    // Configure Port 0 pins (P0.0, P0.1, P0.3, P0.4) as push-pull outputs
    P0M1 &= ~0x1B; // Clear bits 0, 1, 3, 4
    P0M2 |= 0x1B;  // Set bits 0, 1, 3, 4 as output

    // Configure Port 1 pins (P1.0, P1.1, P1.2, P1.3, P1.4, P1.5, P1.7) as push-pull outputs
    P1M1 &= ~0xBF; // Clear bits 0, 1, 2, 3, 4, 5, 7
    P1M2 |= 0xBF;  // Set bits 0, 1, 2, 3, 4, 5, 7 as output

    // Initialize all digits off
    DIGIT1 = 0;
    DIGIT2 = 0;
    DIGIT3 = 0;

    // Multiplexing loop
    while (1) {
        // Display first character on Digit 1
        set_segments(display[0]);
        DIGIT1 = 1;
        DIGIT2 = 0;
        DIGIT3 = 0;
        delay_ms(5);
        DIGIT1 = 0;

        // Display second character on Digit 2
        set_segments(display[1]);
        DIGIT2 = 1;
        DIGIT1 = 0;
        DIGIT3 = 0;
        delay_ms(5);
        DIGIT2 = 0;

        // Display third character on Digit 3
        set_segments(display[2]);
        DIGIT3 = 1;
        DIGIT1 = 0;
        DIGIT2 = 0;
        delay_ms(5);
        DIGIT3 = 0;
    }
}
