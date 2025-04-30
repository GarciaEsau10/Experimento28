/***********************************************************************
* UART0_MASTER_PIC16F877A_XC8.c
* UART PIC TO PIC COMMUNICATION
* WHEN THE PUSH BUTTON AT THE RB7 OF MASTER PIC IS PRESSED, TOGGLE THE
* LED AT RB7 OF SLAVE PIC.
* AUTHOR: INNOCENT OKOLOKO
* DATE:   2015/11/17
***********************************************************************/

#include <xc.h>
#define _XTAL_FREQ 4000000 //Declare internal OSC Freq as 4MHz

#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

void USARTWriteChr(unsigned char c)
{
    while(PIR1bits.TXIF==0);
    TXREG=c;
}

void main(void)
{
    ADCON1 = 0b00000111;          //DISABLE ADC
    TRISB = 0xFF;                 //PORTB as Input
    nRBPU = 0;                    //Enables PORTB Internal Pull Up Resistors

    SPBRG=25;                     //25~= (Fosc/(16 x 9600)) - 1, BRGH=1,FOSC=4MHz
    TXSTAbits.TXEN=1;            //Transmit enable
    TXSTAbits.BRGH=1;            //High baud rate select
    RCSTAbits.SPEN=1;            //Serial port enable

    do

    {
        USARTWriteChr(PORTB);   //TRANSMIT PORTB BITS
        __delay_ms(150);
    }while(1);
   
    return;
}
