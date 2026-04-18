/******************************************************************************
 * File Name   : main.c
 * Project     : DoseGuardian - Intelligent Pill-Taking Assistant
 * Description : Entry point of the application. Initializes all peripherals
 *               and continuously runs the main application logic.
 ******************************************************************************/

#include "lcd.h"              // LCD display driver
#include "rtc.h"              // Real Time Clock driver
#include "rtc_defines.h"      // RTC register definitions
#include "doseguardian.h"     // Core application logic
#include "doseguardian_io.h"  // I/O control (buzzer, LEDs, etc.)
#include "KeyPad.h"           // Keypad driver

int main(void)
{
    /**************************************************************************
     * GPIO Configuration
     * Set all pins as GPIO by clearing PINSEL registers
     **************************************************************************/
    PINSEL0 = 0x00000000;
    PINSEL1 = 0x00000000;
    PINSEL2 = 0x00000000;

    /**************************************************************************
     * Peripheral Initialization
     **************************************************************************/
    InitLCD();         
    RTC_Init();         
    KeyadInit();        
    IO_Init();     

    /**************************************************************************
     * Main Loop
     * Continuously executes the DoseGuardian application logic
     **************************************************************************/
    while (1)
    {
        DoseGuardian_Run();   // Handles scheduling, alerts, and user interaction
    }

    // This return will never be reached
    return 0;
}
