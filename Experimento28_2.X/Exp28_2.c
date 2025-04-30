#include <xc.h>
#define _XTAL_FREQ 4000000

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

char USARTReadChr()
{
    while(PIR1bits.RCIF == 0);  // Esperar hasta recibir dato
    return RCREG;
}

void main(void)
{
    ADCON1 = 0b00000111; // Desactiva ADC
    TRISB = 0x00;         // PORTB como salida
    PORTB = 0x00;         // Apaga todo al inicio

    // Configurar UART
    SPBRG = 25;
    TXSTAbits.TXEN = 1;
    TXSTAbits.BRGH = 1;
    RCSTA = 0x90; // SPEN=1, CREN=1 (habilita recepción)

    char received;

    while(1)
    {
        received = USARTReadChr();

        if(received == 0x01) // Botón presionado
        {
            PORTBbits.RB7 = ~PORTBbits.RB7; // Hacer toggle del LED en RB7
        }

        __delay_ms(50); // Breve espera para evitar múltiples toggles por un solo pulso
    }
}
