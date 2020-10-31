#include <stdint.h>
#include <xc.h>
#include <stdio.h> 
#include <stdbool.h>
#include "hal.h"

/* pinMode
 * -------------------------------------------------------------------------
 * pinMode accepts a pin number between 1 and 21 (inclusive) and a pin mode, 
 * which must be INPUT (1) or OUTPUT (0), and returns nothing. The function will set the
 * pin as either an input or output on the PIC32. pinMode will print an error
 * to console if the pin is out of range or the mode is not INPUT or OUTPUT.
 */
void pinMode(uint8_t pin, uint8_t mode) {
    // Check if pin is out of range
    if (pinOutOfRange(pin)){
        return;
    }
    // Check if mode is input or output
    if ((mode != INPUT) && (mode != OUTPUT)) {
        printf("Error: Mode is not INPUT or OUTPUT");
        return;
    }
    // Localise pin on port A/B and create bitmask
    uint8_t port_letter;
    uint32_t bitmask;
    pinLocation(pin, &port_letter, &bitmask);
    // Set direction of pin
    if (mode == INPUT) {
        if (port_letter == PORT_A) {
            TRISASET = bitmask;
        } else {
            TRISBSET = bitmask;
        }
    } else {
        if (port_letter == PORT_A) {
            TRISACLR = bitmask;
        } else {
            TRISBCLR = bitmask;
        }
    }
}

/* digitalWrite
 * -------------------------------------------------------------------------
 * digitalWrite accepts a output pin number between 1 and 21 (inclusive) and a pin
 * value, which must be HIGH or LOW, and returns nothing. The function will 
 * set the pin as either HIGH or LOW on the PIC32. digitalWrite will print
 * an error to console if the pin is out of range, the value is not HIGH or LOW, 
 * or the pin is not an output pin. 
 */
void digitalWrite(uint8_t pin, uint8_t value) {
    // Check if pin is out of range
    if (pinOutOfRange(pin)){
        return;
    }
    // Check if value is high or low 
    if ((value != HIGH) && (value != LOW)) {
        printf("Error: Value is not HIGH or LOW");
        return;
    }
    // Localise pin on port A/B and create bitmask
    uint8_t port_letter;
    uint32_t bitmask;
    pinLocation(pin, &port_letter, &bitmask);
    // Confirm pin is an output pin
    if (isInputPin(port_letter, bitmask)) {
        printf("Error: Writing to input pin");
        return;
    }
    // Write to pin
    if (port_letter == PORT_A) {
        if (value == HIGH) {
            LATASET = bitmask;
        } else {
            LATACLR = bitmask;
        }
    } else {
        if (value == HIGH) {
            LATBSET = bitmask;
        } else {
            LATBCLR = bitmask;
        }
    }
}
/* digitalRead
 * -------------------------------------------------------------------------
 * digitalRead accepts a pin number between 1 and 21 (inclusive). The function
 * reads the PORT register if the pin is an input and the LATCH register if the 
 * pin is an output. The function then returns the read value. If the pin 
 * is out of range, digitalRead will return 255.
 */
uint8_t digitalRead(uint8_t pin) {
    // Check if pin is out of range
    if (pinOutOfRange(pin)){
        return 255;
    }
    // Localise pin on port A/B and create bitmask
    uint8_t port_letter;
    uint32_t bitmask;
    pinLocation(pin, &port_letter, &bitmask);
    // Read pin and return value
    uint8_t pin_value;
    if(isInputPin(port_letter, bitmask)) {
        if (port_letter == PORT_A) {
            pin_value = (PORTA & bitmask) ? 1 : 0;
        } else {
            pin_value = (PORTB & bitmask) ? 1 : 0;
        }
    } else {
        if (port_letter == PORT_A) {
            pin_value = (LATA & bitmask) ? 1 : 0;
        } else {
            pin_value = (LATB & bitmask) ? 1 : 0;
        }
    }
    return pin_value;
}

/* Helper Functions
 */

/* pinOutOfRange
 * -------------------------------------------------------------------------
 * pinOutOfRange is a helper function that accepts a pin number and 
 * returns true if the pin is within the range 1-21 (inclusive) and 
 * false otherwise.
 */ 
static bool pinOutOfRange(uint8_t pin) {
    if ((pin < 1) || (pin > 21)) {
        printf("Error: Pin out of range");
        return true;
    } 
    return false;
}

/* pinLocation
 * -------------------------------------------------------------------------
 * pinLocation is a helper function that accepts a pin number and a pointer 
 * to a uint8_t representing the port letter (PORT A or B) and a bitmask. 
 * pinLocation will change by reference the port letter as either PORT_A 
 * or PORT_B and the bitmask for the pin. The function returns nothing.
 */
static void pinLocation(uint8_t pin, uint8_t* port_letter, uint32_t* bitmask) {
    uint8_t port_number;
    if (pin <= PORT_A_SIZE) {
        *port_letter = PORT_A;
        port_number = pin - 1;
    } else {
        *port_letter = PORT_B;
        port_number = pin - PORT_A_SIZE - 1;
    }
    *bitmask = (1 << port_number);
}
/* isInputPin
 * -------------------------------------------------------------------------
 * isInputPin is a helper function that accepts a port_letter (PORT_A or PORT_B)
 * and a bitmask. The function returns true if the pin is an input and false 
 * if the pin is an output pin. 
 */
static bool isInputPin(uint8_t port_letter, uint32_t bitmask) {
    if (port_letter == PORT_A) {
        return (TRISA & bitmask);
    } else {
        return (TRISB & bitmask);
    }
}