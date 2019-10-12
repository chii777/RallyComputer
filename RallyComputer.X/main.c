/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16F18326
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "i2c_pp.h"

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

/* The TM6137 uses an I2C 'like' signalling method with two caveats:
 *  1. It does not use an I2C address so you can't have any other device on the bus.
 *  2. I2C sends data MSB first, the TM6137 expects data LSB first.
 *     Since this code uses the hardware MSSP module in the PIC, the data to be sent
 *     must be reversed before loading into the PICs MSSP buffer register. 
*/

#define WriteDispAddrAuto 0x02 //0100 0000
#define WriteDispAddrFix  0x22 //0100 0100
#define AddressZero       0x03 //1100 0000

// See TM1637 datasheet page 5
// Display control table        Data Byte   Reversed        
#define DisplayOn1        0x11 //10001000   00010001
#define DisplayOn2        0x91 //10001001   10010001
#define DisplayOn4        0x51 //10001010   01010001
#define DisplayOn10       0xD1 //10001011   11010001
#define DisplayOn11       0x31 //10001100   00110001
#define DisplayOn12       0xB1 //10001101   10110001
#define DisplayOn13       0x71 //10001110   01110001
#define DisplayOn14       0xF1 //10001111   11110001
#define DisplayOff        0x01 //10000000   00000001

// Segment data for digits 0 thru 9
uint8_t segdata[] = { 0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6 };

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

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    i2c1_init();
    
    struct 
    {
        uint8_t secsUnit;
        uint8_t secsTen;
        uint8_t minsUnit;
        uint8_t minsTen;
    } timer;
    
    timer.minsUnit = 0;
    timer.minsTen  = 0;   
    timer.secsUnit = 0;
    timer.secsTen  = 0;
    
    // TM6137 datasheet refers to the common anode connection of
    // each 7-segment display digit as GRIDn 
    // 4-digit display viewed from front[grid1 grid2 grid3 grid4]
    uint8_t grid1;
    uint8_t grid2;
    uint8_t grid3;
    uint8_t grid4;
    
    while (1)
    {
        
        grid4 = segdata[timer.secsUnit];
        grid3 = segdata[timer.secsTen];
        grid2 = segdata[timer.minsUnit];
        // Centre ':' is segment8 (DP) of grid2. Since we need to reverse the
        // data we send, inclusive-or bit 1 with segment data to turn it on.
        if(timer.secsUnit & 1) grid2 |= 1; // turn on centre ':'
        
        grid1 = segdata[timer.minsTen];
        
        // Send data to TM6137 module using the MSSP1 Synchronous Serial Port 
        // See TM1637 datasheet Page 4
        // Write SRAM data in address auto increment 1 mode.
        i2c1_start();
        i2c1_write(WriteDispAddrAuto);
        i2c1_stop();
        
        i2c1_start();
        i2c1_write(AddressZero);
        i2c1_write(grid1); 
        i2c1_write(grid2); 
        i2c1_write(grid3); 
        i2c1_write(grid4);     
        i2c1_stop();
   
        i2c1_start();
        i2c1_write(DisplayOn4);
        i2c1_stop();
        
        // For something to put on the display, count up like minutes : seconds
        // this is not an accurate timer, it's just to get some activity on the
        // the LED display.
        timer.secsUnit++;
        if(timer.secsUnit == 10)
        {
            timer.secsUnit = 0;
            timer.secsTen++;
        }
        
        if(timer.secsTen == 6)
        {
            timer.secsTen = 0;
            timer.minsUnit++;
        }
        
        if(timer.minsUnit == 10)
        {
            timer.minsUnit = 0;
            timer.minsTen++;
        }
        if(timer.minsTen == 6)
        {
            timer.minsTen = 0;
        }

        __delay_ms(1000);
        
    }
}
/**
 End of File
*/