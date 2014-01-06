/*

  using Alan Barr raspberry-gpio libraries
  https://github.com/alanbarr/RaspberryPi-GPIO 

  Here is where the magic happens, this TEST program communicates
  the rPI with an Arduino (does not matter which one, all of them are i2c
  enabled but the pin layout may change).

  The physic comunication is done trought a level shifter. Why? because
  the rPI works at 3v3  but the Ardu works at 5v so if you connect them 
  directly probably you will blow something. 
  Anyway seems like there is some people that doesn't use any level 
  shifter hardware and has no problems but my recomendation is to protect
  the rPi form overvoltage.
 
  For the sake of simplicity I'm using a Texas Instruments P82B96 but there is
  no problem at all making one by yourself, just a few resistors and MOSFETs 
  requiered.  
 
  ___________        ___________________________          __________
       3v3V3|-------|VCC                       |         |
         GND|-------|GND                    GND|---------|GND
         SDA|-------|Tx & Rx                 Sx|---------|SDA
         SCL|-------|Ty & Ry +10k pullup     Sy|---------|SCL
            |       |                          |         |
       rPi  |       |         P82B96           |         |   Ardu
  __________|       |__________________________|         |___________
 
  Also you may want to attach pullup resitors (depending the lenght of the bus but 
  10k is usually fine) to SDA and SCL in both sides of the level shifter. It is not
  mandatory but is nice to avoid headaches.
  -On the rPi side use a 10k 3v3 resistor to the SCL and another one to the SDA.
  -On the Ardu side use a 10k 5v resistor to the SCL and another one to the SDA.
  
  =================================================
  BEFORE POWER IT ON ALWAYS DOUBLE CHECK THE WIRING 
  BEFORE POWER IT ON ALWAYS DOUBLE CHECK THE WIRING 
  BEFORE POWER IT ON ALWAYS DOUBLE CHECK THE WIRING 
  =================================================
 
 */     

#include <stdio.h>
#include <unistd.h>
#include "rpiGpio.h"
#include "functions.h"

// rPi address
#define RASP_ADDR 0x40
// rPi address
#define ARDU_ADDR 0x12


int main(void)
{ 
    uint8_t dataOut;
    int counter;

    initialize();


    if (gpioI2cSet7BitSlave(ARDU_ADDR) != OK)
    {
        dbgPrint(DBG_INFO, "Failed setting the slave address\n");
        return 1;
    }

    if (gpioI2cWriteData(&dataOut[0], 2) != OK)
    {
        dbgPrint(DBG_INFO, "Fail sending data\n");
        return 1;
    }

    gpioI2cWriteData(&dataOut[2], 2);  

    for(counter = 15; counter >= 0; counter--)
    {
        
        dataOut[3] = (uint8_t)counter;
        sleep(1);
        printf("sending %d\n", counter);
        gpioI2cWriteData(&dataOut[2], 2);  
    
    }

    gpioI2cCleanup();
    gpioCleanup();
    
    return 0;
} 



