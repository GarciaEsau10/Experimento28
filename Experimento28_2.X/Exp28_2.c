//Implementación Experimento28(Eslave)
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

char USARTReadChar() {
    while (!RCIF);       // Wait for data reception
    return RCREG;
}

void main(void) {
    OSCCON = 0x61;        // Set internal oscillator to 4MHz
    ANSEL = 0x00;
    ANSELH = 0x00;

    TRISBbits.TRISB7 = 0; // RB7 as output (LED)
    PORTBbits.RB7 = 0;    // Start with LED OFF

    // UART Setup
    SPBRG = 25;
    TXSTAbits.BRGH = 1;
    TXSTAbits.TXEN = 1;
    RCSTAbits.CREN = 1;   // Continuous receive
    RCSTAbits.SPEN = 1;

    while (1) {
        char data = USARTReadChar();
        PORTBbits.RB7 = (data & 0x80) ? 1 : 0; // Extract RB7 bit
        __delay_ms(100);
    }
}