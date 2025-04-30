//Implementación Experimento28(Master)
//Garcia Cruz Esau Rafael
//Microcontroladores
//30/Abril/2025

#include <xc.h>
#define _XTAL_FREQ 4000000

// CONFIGURACIÓN DE BITS
#pragma config FOSC = INTRC_NOCLKOUT 
#pragma config WDTE = OFF            
#pragma config PWRTE = ON            
#pragma config MCLRE = ON            
#pragma config CP = OFF             
#pragma config CPD = OFF             
#pragma config BOREN = ON            
#pragma config IESO = OFF            
#pragma config FCMEN = OFF           
#pragma config LVP = OFF             

void USARTWriteChar(unsigned char c) {
    while (!TXIF);  // Wait for transmit buffer to be empty
    TXREG = c;      // Transmit character
}

void main(void) {
    OSCCON = 0x61;        // Set internal oscillator to 4MHz
    ANSEL = 0x00;         // All analog functions disabled (PORTA)
    ANSELH = 0x00;        // All analog functions disabled (PORTB-D)
    
    TRISBbits.TRISB7 = 1; // RB7 as input (push button)
    WPUBbits.WPUB7 = 1;   // Enable weak pull-up on RB7
    OPTION_REGbits.nRBPU = 0; // Enable PORTB pull-ups globally (activo en bajo)

    // UART Setup
    SPBRG = 25;           // Baud Rate = 9600 for Fosc=4MHz
    TXSTAbits.BRGH = 1;   // High speed baud rate
    TXSTAbits.TXEN = 1;   // Enable transmitter
    RCSTAbits.SPEN = 1;   // Enable serial port

    while (1) {
        unsigned char state = PORTBbits.RB7;
        USARTWriteChar(state << 7); // Send RB7 as MSB (0x00 or 0x80)
        __delay_ms(100);
    }
}