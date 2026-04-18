/******************************************************************************
 * File Name   : keypad.c
 * Project     : DoseGuardian - Intelligent Pill-Taking Assistant
 * Description : 4x4 Matrix Keypad driver implementation
 *               Handles key scanning and key detection.
 ******************************************************************************/

#include <LPC21XX.h>
#include "KeyPadDefines.h"
#include "delay.h"

/******************************************************************************
 * Function Name : WaitKeyRelease
 * Description   : Waits until all keys are released (debouncing)
 ******************************************************************************/
void WaitKeyRelease(void)
{
    // Wait until all column inputs are HIGH (no key pressed)
    while(((IOPIN1 >> C0) & 0x0F) != 0x0F);

    delay_ms(200);   // Debounce delay
}

/******************************************************************************
 * Function Name : KeyadInit  
 * Description   : Initializes keypad GPIO pins
 *                 Rows → Output
 *                 Columns → Input
 ******************************************************************************/
void KeyadInit(void)
{
    // Configure row pins as output (P1.16 to P1.19)
    IODIR1 |= ((1 << R0) | (1 << R1) | (1 << R2) | (1 << R3));
}

/******************************************************************************
 * Function Name : ColStat
 * Description   : Checks if any key is pressed
 * Returns       : 0 → Key pressed
 *                 1 → No key pressed
 ******************************************************************************/
int ColStat(void)
{
    if(((IOPIN1 >> C0) & 0x0F) == 0x0F)
        return 1;   // No key pressed
    else
        return 0;   // Key pressed
}

/******************************************************************************
 * Function Name : ReadKeyVal
 * Description   : Scans keypad to identify which key is pressed
 * Returns       : Character corresponding to pressed key
 ******************************************************************************/
char ReadKeyVal(void)
{
    char RowVal, ColVal;

    /* -------- Row 0 Scan -------- */
    IOCLR1 = 1 << R0;
    IOSET1 = (1 << R1) | (1 << R2) | (1 << R3);

    if(((IOPIN1 >> C0) & 0x0F) != 0x0F)
    {
        RowVal = 0;
        goto ColCheck;
    }

    /* -------- Row 1 Scan -------- */
    IOCLR1 = 1 << R1;
    IOSET1 = (1 << R0) | (1 << R2) | (1 << R3);

    if(((IOPIN1 >> C0) & 0x0F) != 0x0F)
    {
        RowVal = 1;
        goto ColCheck;
    }

    /* -------- Row 2 Scan -------- */
    IOCLR1 = 1 << R2;
    IOSET1 = (1 << R0) | (1 << R1) | (1 << R3);

    if(((IOPIN1 >> C0) & 0x0F) != 0x0F)
    {
        RowVal = 2;
        goto ColCheck;
    }

    /* -------- Row 3 Scan -------- */
    IOCLR1 = 1 << R3;
    IOSET1 = (1 << R0) | (1 << R1) | (1 << R2);

    if(((IOPIN1 >> C0) & 0x0F) != 0x0F)
    {
        RowVal = 3;
    }

ColCheck:

    /* Identify column */
    if(((IOPIN1 >> C0) & 1) == 0)
        ColVal = 0;
    else if(((IOPIN1 >> C1) & 1) == 0)
        ColVal = 1;
    else if(((IOPIN1 >> C2) & 1) == 0)
        ColVal = 2;
    else
        ColVal = 3;

    return LUT[RowVal][ColVal];   // Return mapped key
}

/******************************************************************************
 * Function Name : GetKey_Blocking
 * Description   : Waits until a key is pressed and returns it
 * Returns       : Pressed key value
 ******************************************************************************/
char GetKey_Blocking(void)
{
    char key;

    // Set all rows LOW
    IOCLR1 = 0x0F << R0;

    // Wait until a key is pressed
    while(ColStat());

    delay_ms(20);   // Debounce

    key = ReadKeyVal();  // Get key value

    WaitKeyRelease();    // Wait for release

    return key;
}