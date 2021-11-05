/*
 * File:   main.c
 * Author: Julia Filipchuk
 *
 * Created on October 29, 2021, 12:18 AM
 */

#include "PIC18F26K42_config.h"

#include <stdbool.h>

// This define is used internally by the delay functions.
//#define _XTAL_FREQ 16000000 // 16MHz
#define _XTAL_FREQ    32768 // 32.768KHz

// Forward Declarations
static void test_led_setup();
static void test_led(bool enable);


static void test_led_setup() {
    TRISB &= ~(1 << 3); // Clear Bit 3. Make RB3 output. Tristate Register.
    PORTB &= ~(1 << 3); // Clear Bit 3. Disable LED at start.
}

// test_led - connected to pin 24 (RB3).
static void test_led(bool enable) {
    static bool enabled = false;
    
    if (enable && !enabled) {
        PORTB |=  (1 << 3);  // Set Bit 3.
    } else if (!enable && enabled) {
        PORTB &= ~(1 << 3); // Clear Bit 3.
    }
}


void main(void) {
    int i;
    
    // reference: 10.2 PORTB Registers
    // TODO: These are too aggressive. Maybe don't clear everything.
    TRISB = 0x00; // Set bit 1 to make input. Set all PORTB as output.
    PORTB = 0x00; // Output of RB3 Low.
    
    
    for (i = 100; i; --i) {
        
        PORTB |=  (1 << 3); // Set bit. LED ON
        __delay_ms(500);
        PORTB &= ~(1 << 3); // Clear bit. LED OFF
        __delay_ms(500);
    }
    
    return;
}
