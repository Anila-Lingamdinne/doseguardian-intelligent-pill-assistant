/******************************************************************************
 * File Name   : keypad.h
 * Project     : DoseGuardian - Intelligent Pill-Taking Assistant
 * Description : Header file for 4x4 Matrix Keypad driver
 ******************************************************************************/

#ifndef _KEYPAD_H_
#define _KEYPAD_H_

/******************************************************************************
 * Function Name : Keypad_Init
 * Description   : Initializes keypad GPIO pins
 ******************************************************************************/
void Keypad_Init(void);

/******************************************************************************
 * Function Name : ColStat
 * Description   : Checks if any key is pressed
 * Returns       : 0 → Key pressed
 *                 1 → No key pressed
 ******************************************************************************/
int ColStat(void);

/******************************************************************************
 * Function Name : ReadKeyVal
 * Description   : Scans keypad and returns pressed key value
 ******************************************************************************/
char ReadKeyVal(void);

/******************************************************************************
 * Function Name : WaitKeyRelease
 * Description   : Waits until key is released (debouncing)
 ******************************************************************************/
void WaitKeyRelease(void);

/******************************************************************************
 * Function Name : GetKey_Blocking
 * Description   : Waits until a key is pressed and returns it
 ******************************************************************************/
char GetKey_Blocking(void);

/******************************************************************************
 * Function Name : Keypad_GetString
 * Description   : Reads a string input from keypad
 * Parameters    : str → buffer to store string
 * Returns       : Length of string
 ******************************************************************************/

#endif