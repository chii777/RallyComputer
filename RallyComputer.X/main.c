/* 
 * File:   main.c
 * Author: kuwano
 *
 * Created on 2019/09/25, 23:50
 */

// PIC16F18326 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FEXTOSC = OFF    // FEXTOSC External Oscillator mode Selection bits (Oscillator not enabled)
#pragma config RSTOSC = HFINT32 // Power-up default value for COSC bits (HFINTOSC with 2x PLL (32MHz))
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; I/O or oscillator function on OSC2)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config MCLRE = ON       // Master Clear Enable bit (MCLR/VPP pin function is MCLR; Weak pull-up enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config WDTE = ON        // Watchdog Timer Enable bits (WDT enabled, SWDTEN is ignored)
#pragma config LPBOREN = OFF    // Low-power BOR enable bit (ULPBOR disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bits (Brown-out Reset enabled, SBOREN bit ignored)
#pragma config BORV = LOW       // Brown-out Reset Voltage selection bit (Brown-out voltage (Vbor) set to 2.45V)
#pragma config PPS1WAY = ON     // PPSLOCK bit One-Way Set Enable bit (The PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable bit (Stack Overflow or Underflow will cause a Reset)
#pragma config DEBUG = OFF      // Debugger enable bit (Background debugger disabled)

// CONFIG3
#pragma config WRT = OFF        // User NVM self-write protection bits (Write protection off)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low Voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored.)

// CONFIG4
#pragma config CP = OFF         // User NVM Program Memory Code Protection bit (User NVM code protection disabled)
#pragma config CPD = OFF        // Data NVM Memory Code Protection bit (Data NVM code protection disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 8000000

/*
 * 
 */

void PICinit()
{
    OSCFRQbits.HFFRQ = 0b0011; //8MHz
    ANSELA  = 0b00000000; // AN?????
    TRISA   = 0b00000000; // set all of RA pins output
    TRISC   = 0b00000000; // set all of RC pins output
    PORTA   = 0b00000000; // All of RA pins set LOW
    PORTC   = 0b00000000; // All of RC pins set LOW
    return;
}

void printNumber(int num)
{
    if (num == 0)
    {// 1st_bit: RA1, 2nd_bit:RA0, A:RC1, B:RA5, C:RA4, D:RC4, E:RC5, F:RC2, G:RA2
        PORTA   = 0b00000100; // ? ? TRISA5 TRISA4 ? TRISA2 TRISA1 TRISA0
        PORTC   = 0b00000000; // ? ? ? TRISC5 TRISC4 TRISC3 TRISC2 TRISC1 TRISC0
    }
    else if (num == 1)
    {// 1st_bit: RA1, 2nd_bit:RA0, A:RC1, B:RA5, C:RA4, D:RC4, E:RC5, F:RC2, G:RA2
        PORTA   = 0b00000100; // ? ? TRISA5 TRISA4 ? TRISA2 TRISA1 TRISA0
        PORTC   = 0b00110110; // ? ? ? TRISC5 TRISC4 TRISC3 TRISC2 TRISC1 TRISC0
    }
    else if (num == 2)
    {// 1st_bit: RA1, 2nd_bit:RA0, A:RC1, B:RA5, C:RA4, D:RC4, E:RC5, F:RC2, G:RA2
        PORTA   = 0b00010000; // ? ? TRISA5 TRISA4 ? TRISA2 TRISA1 TRISA0
        PORTC   = 0b00000100; // ? ? ? TRISC5 TRISC4 TRISC3 TRISC2 TRISC1 TRISC0
    }
    else if (num == 3)
    {// 1st_bit: RA1, 2nd_bit:RA0, A:RC1, B:RA5, C:RA4, D:RC4, E:RC5, F:RC2, G:RA2
        PORTA   = 0b00000000; // ? ? TRISA5 TRISA4    ?   TRISA2 TRISA1 TRISA0
        PORTC   = 0b00100100; // ? ? TRISC5 TRISC4 TRISC3 TRISC2 TRISC1 TRISC0
    }
    else if (num == 4)
    {// 1st_bit: RA1, 2nd_bit:RA0, A:RC1, B:RA5, C:RA4, D:RC4, E:RC5, F:RC2, G:RA2
        PORTA   = 0b00000000; // ? ? TRISA5 TRISA4    ?   TRISA2 TRISA1 TRISA0
        PORTC   = 0b00110010; // ? ? TRISC5 TRISC4 TRISC3 TRISC2 TRISC1 TRISC0
    }
    else if (num == 5)
    {// 1st_bit: RA1, 2nd_bit:RA0, A:RC1, B:RA5, C:RA4, D:RC4, E:RC5, F:RC2, G:RA2
        PORTA   = 0b00100000; // ? ? TRISA5 TRISA4    ?   TRISA2 TRISA1 TRISA0
        PORTC   = 0b00100000; // ? ? TRISC5 TRISC4 TRISC3 TRISC2 TRISC1 TRISC0
    }
    else if (num == 6)
    {// 1st_bit: RA1, 2nd_bit:RA0, A:RC1, B:RA5, C:RA4, D:RC4, E:RC5, F:RC2, G:RA2
        PORTA   = 0b00100000; // ? ? TRISA5 TRISA4    ?   TRISA2 TRISA1 TRISA0
        PORTC   = 0b00000000; // ? ? TRISC5 TRISC4 TRISC3 TRISC2 TRISC1 TRISC0
    }
    else if (num == 7)
    {// 1st_bit: RA1, 2nd_bit:RA0, A:RC1, B:RA5, C:RA4, D:RC4, E:RC5, F:RC2, G:RA2
        PORTA   = 0b00000100; // ? ? TRISA5 TRISA4    ?   TRISA2 TRISA1 TRISA0
        PORTC   = 0b00110100; // ? ? TRISC5 TRISC4 TRISC3 TRISC2 TRISC1 TRISC0
    }
    else if (num == 8)
    {// 1st_bit: RA1, 2nd_bit:RA0, A:RC1, B:RA5, C:RA4, D:RC4, E:RC5, F:RC2, G:RA2
        PORTA   = 0b00000000; // ? ? TRISA5 TRISA4    ?   TRISA2 TRISA1 TRISA0
        PORTC   = 0b00000000; // ? ? TRISC5 TRISC4 TRISC3 TRISC2 TRISC1 TRISC0
    }
    else if (num == 9)
    {// 1st_bit: RA1, 2nd_bit:RA0, A:RC1, B:RA5, C:RA4, D:RC4, E:RC5, F:RC2, G:RA2
        PORTA   = 0b00000000; // ? ? TRISA5 TRISA4    ?   TRISA2 TRISA1 TRISA0
        PORTC   = 0b00100000; // ? ? TRISC5 TRISC4 TRISC3 TRISC2 TRISC1 TRISC0
    }
}

void setNum(int first, int second)
{
    printNumber(first);
    RA0=1;
    printNumber(second);
    RA1=1;
}

int main(int argc, char** argv) 
{
    PICinit();      //init PIC
    
    int i = 0;
    while(1)
    {
        for (int k=0; k<200; k++)
        {
            setNum(i/10%10, i%10);
        }
        i++;
    }
    setNum(0, 0);    

    return (EXIT_SUCCESS);
}

