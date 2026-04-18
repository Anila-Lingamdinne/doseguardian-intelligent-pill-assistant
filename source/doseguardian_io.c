/******************************************************************************
 * File Name   : doseguardian_io.c
 * Project     : DoseGuardian - Intelligent Pill-Taking Assistant
 * Description : Handles all hardware I/O operations such as switches,
 *               buzzer, and LED control.
 ******************************************************************************/

#include "doseguardian_io.h"
#include "types.h"

/******************************************************************************
 * Function Name : IO_Init
 * Description   : Initializes GPIO pins for switches, buzzer, and LED.
 *                 - Switches are configured as input
 *                 - Buzzer and LED are configured as output
 ******************************************************************************/
void IO_Init(void)
{
    /* Configure switches as input */
    IODIR0 &= ~((1 << SW1) | (1 << SW2));

    /* Note:
       LPC2148 has internal pull-up resistors enabled by default */

    /* Configure buzzer and LED as output */
    IODIR0 |= (1 << BUZZER) | (1 << RED_LED);

    /* Turn OFF buzzer and LED initially */
    IOCLR0 = (1 << BUZZER) | (1 << RED_LED);
}

/******************************************************************************
 * Function Name : Switch1_Pressed
 * Description   : Checks if Switch 1 is pressed
 *                 (Active LOW: pressed = 0)
 * Returns       : 1 if pressed, 0 otherwise
 ******************************************************************************/
u8 Switch1_Pressed(void)
{
    if (!(IOPIN0 & (1 << SW1)))   // Check active-low condition
        return 1;

    return 0;
}

/******************************************************************************
 * Function Name : Switch2_Pressed
 * Description   : Checks if Switch 2 is pressed
 *                 (Active LOW: pressed = 0)
 * Returns       : 1 if pressed, 0 otherwise
 ******************************************************************************/
u8 Switch2_Pressed(void)
{
    if (!(IOPIN0 & (1 << SW2)))
        return 1;

    return 0;
}

/******************************************************************************
 * Function Name : Buzzer_ON
 * Description   : Turns ON the buzzer
 ******************************************************************************/
void Buzzer_ON(void)
{
    IOSET0 = (1 << BUZZER);
}

/******************************************************************************
 * Function Name : Buzzer_OFF
 * Description   : Turns OFF the buzzer
 ******************************************************************************/
void Buzzer_OFF(void)
{
    IOCLR0 = (1 << BUZZER);
}

/******************************************************************************
 * Function Name : RedLED_ON
 * Description   : Turns ON the Red LED
 ******************************************************************************/
void RedLED_ON(void)
{
    IOSET0 = (1 << RED_LED);
}

/******************************************************************************
 * Function Name : RedLED_OFF
 * Description   : Turns OFF the Red LED
 ******************************************************************************/
void RedLED_OFF(void)
{
    IOCLR0 = (1 << RED_LED);
}