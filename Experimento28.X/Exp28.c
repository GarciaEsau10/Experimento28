#include <xc.h>
#define _XTAL_FREQ 4000000 // Frecuencia del oscilador

#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FCMEN = OFF
#pragma config LVP = OFF

void USARTWriteChr(unsigned char c)
{
    while(PIR1bits.TXIF == 0); // Espera hasta que el buffer esté vacío
    TXREG = c;                 // Envía el carácter
}

void main(void)
{
    ADCON1 = 0b00000111; // Desactiva ADC
    TRISB = 0xFF;         // PORTB como entrada
    nRBPU = 0;            // Activa resistencias pull-up internas

    // Configuración UART
    SPBRG = 25;
    TXSTAbits.TXEN = 1;
    TXSTAbits.BRGH = 1;
    RCSTAbits.SPEN = 1;

    unsigned char prevRB7 = PORTBbits.RB7;
    unsigned char currRB7;

    while(1)
    {
        currRB7 = PORTBbits.RB7;

        if (currRB7 != prevRB7)  // Detecta cambio de estado en RB7
        {
            USARTWriteChr(currRB7 ? 0x01 : 0x00); // Envía 0x01 si presionado, 0x00 si soltado
            prevRB7 = currRB7;
        }

        __delay_ms(50); // Pequeño retardo para evitar rebotes
    }
}
