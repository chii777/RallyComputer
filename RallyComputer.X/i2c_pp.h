/* 
 * File:   i2c.h
 * Author: Pete
 *
 * Created on March 13, 2019, 9:36 PM
 */

#ifndef I2C_PP_H
#define	I2C_PP_H

#include <xc.h>
#include <stdint.h>

/* Modify these values for desired I2C clock frequency
 
   Fclock = Fosc /(SSP2ADD + 1)x4

   Fosc     Fcy     Fclock  BRG
   32MHz    8MHz    400KHz  0x13
   32MHz    8MHz    100KHz  0x4F
   16MHz    4MHz    400KHz  0x09
   16MHz    4MHz    100KHz  0x27
   4MHz     1MHz    100KHz  0x09
 */
#define I2C1_BRG 0x09

// 400Khz with Fosc = 16MHz


#define ACK 1
#define NACK 0
#define i2c1_read_ack i2c1_read(ACK)
#define i2c1_read_nack i2c1_read(NACK)

// I2C functions for MSSP1 module
void i2c1_check_idle(void);
void i2c1_start(void);
void i2c1_rep_start(void);
void i2c1_stop(void);
void i2c1_write(uint8_t i2c_data);
uint8_t i2c1_read(uint8_t ack);
void i2c1_init(void);




#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_PP_H */

