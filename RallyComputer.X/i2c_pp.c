/**
  Generated Pin Manager File

  Company:
    Picprojects

  File Name:
    i2c.c

  Summary:
    I2C for PIC16F18345 

  Description:
    I2C functions for PIC16F18345 
    * Functions are blocking
    * No error recovery
 
    Generation Information :
        Device            :  PIC16F18345
    Tested against the following:
        Compiler          :  XC8 2.05 (free)
        MPLAB             :  MPLAB X 5.10

    2019 Picprojects.org
*/
#include "i2c_pp.h"

void i2c1_wait_until_idle(void){
    while((SSP1CON2 & 0x1F) || (SSP1STAT & 0x04) );
}

void i2c1_start(void){
    i2c1_wait_until_idle();
    SSP1CON2bits.SEN = 1;
}

void i2c1_rep_start(void){
    i2c1_wait_until_idle();
    SSP1CON2bits.RSEN = 1;
}

void i2c1_stop(void){
    i2c1_wait_until_idle();
    SSP1CON2bits.PEN = 1;
}

void i2c1_write(uint8_t i2c_data){
    i2c1_wait_until_idle();
    SSP1BUF = i2c_data;
    while(SSP1STATbits.BF != 0);
    while(SSP1CON2bits.ACKSTAT != 0);
}

uint8_t i2c1_read(uint8_t ack){
    uint8_t receive = 0;
    i2c1_wait_until_idle();
    SSP1CON2bits.RCEN = 1;
    while(SSP1STATbits.BF != 1);
    receive = SSP1BUF;
    SSP1CON2bits.ACKEN = ack;
    return receive;
}


void i2c1_init(void){
    TRISCbits.TRISC0 = 1;
    TRISCbits.TRISC1 = 1;
    RC0PPS = 0x18;      //RC0->MSSP1:SCL1;    
    SSP1CLKPPS = 0x10;  //RC0->MSSP1:SCL1;    
    RC1PPS = 0x19;      //RC1->MSSP1:SDA1;    
    SSP1DATPPS = 0x11;  //RC1->MSSP1:SDA1;    
    SSP1STATbits.SMP = 0;  // Slew rate control enabled 
    SSP1STATbits.CKE = 0;  // Disable SMBus specific inputs
    SSP1CON1bits.SSPM = 0x08;
    SSP1CON3bits.SDAHT = 0; // hold time on SDA after falling edge SCL
    SSP1ADD = I2C1_BRG;    // I2C baud rate. See i2c_pp.h 
    SSP1CON1bits.SSPEN = 1;
}




