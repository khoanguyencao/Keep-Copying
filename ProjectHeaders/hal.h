#ifndef _hal_h
#define _hal_h

#define PORT_A_SIZE 5

// Enumerated Types 
enum mode{INPUT = 1, OUTPUT = 0};       // Used for Pin Mode
enum value{HIGH = 1, LOW = 0};          // Used for Digital Write
enum port{PORT_A = 0, PORT_B = 1};       // Used for Ports

// Function Prototypes 
void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t value);
uint8_t digitalRead(uint8_t pin);

// Static Function Prototypes
static bool pinOutOfRange(uint8_t pin);
static void pinLocation(uint8_t pin, uint8_t* port_letter, uint32_t* bitmask);
static bool isInputPin(uint8_t port_letter, uint32_t bitmask);

#endif