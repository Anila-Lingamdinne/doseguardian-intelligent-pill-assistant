/******************************************************************************
 * File Name   : doseguardian.c
 * Project     : DoseGuardian - Intelligent Pill-Taking Assistant
 * Description : Core application logic for medication reminder system.
 *               Handles RTC display, menu navigation, medicine alerts,
 *               and user configuration.#ifndef RTC_H
 ******************************************************************************/

#include "lcd.h"
#include "doseguardian_io.h"
#include "doseguardian.h"
#include "rtc_defines.h"
#include "delay.h"
#include "types.h"
#include "KeyPad.h"
#include "rtc.h"

/* ===================== GLOBAL VARIABLES ===================== */

// Medicine schedule
u8 med_time_set = 0;   // Flag to indicate if medicine time is set
u8 med_hour = 9;       // Default hour (9 AM)
u8 med_min  = 30;      // Default minute

/* ===================== KEYPAD INPUT ===================== */

/******************************************************************************
 * Function Name : GetDigitKey
 * Description   : Waits for user to press a numeric key (0–9)
 * Returns       : Pressed digit character
 ******************************************************************************/
char GetDigitKey(void)
{
    char k;

    while(1)
    {
        k = GetKey_Blocking();   // Wait for key press

        if(k >= '0' && k <= '9') // Accept only digits
        {
            WaitKeyRelease();    // Avoid multiple reads
            return k;
        }
    }
}

/* ===================== MENU DISPLAY ===================== */

/******************************************************************************
 * Function Name : Show_Menu
 * Description   : Displays menu and allows user to select options
 ******************************************************************************/
void Show_Menu(void)
{
    char key;

    CmdLCD(0x01);
    StrLCD("1.RTC 2.MED");
    CmdLCD(0xC0);
    StrLCD("3.EXIT");

    while(1)
    {
        key = GetKey_Blocking();

        if(key == '1')
        {
            WaitKeyRelease();
            Edit_RTC();      // Edit RTC settings
            return;
        }
        else if(key == '2')
        {
            WaitKeyRelease();
            Edit_Med_Time(); // Edit medicine time
            return;
        }
        else if(key == '3')
        {
            CmdLCD(0x01);
            return;
        }
    }
}

/* ===================== MAIN APPLICATION ===================== */

/******************************************************************************
 * Function Name : DoseGuardian_Run
 * Description   : Main logic loop
 *                 - Displays time/date
 *                 - Checks for medicine alert
 *                 - Handles user interaction
 ******************************************************************************/
void DoseGuardian_Run(void)
{
    s32 hour, minute, second, date, month, year, day;
    u8 wait_time;

    static u8 alerted = 0;   // Prevent repeated alerts

    /* Get and display current time */
    GetRTCTimeInfo(&hour, &minute, &second);
    DisplayRTCTime(hour, minute, second);

    /* Get and display date */
    GetRTCDateInfo(&date, &month, &year);
    DisplayRTCDate(date, month, year);

    /* Get and display day */
    GetRTCDay(&day);
    DisplayRTCDay(day);

    /* Open menu if Switch1 is pressed */
    if(Switch1_Pressed())
    {
        Show_Menu();
        return;
    }

    /* Reset alert flag when time changes */
    if(hour != med_hour || minute != med_min)
    {
        alerted = 0;
        RedLED_OFF();
    }

    /* Medicine alert condition (trigger once per minute) */
    if(med_time_set && hour == med_hour && minute == med_min && !alerted)
    {
        alerted = 1;

        CmdLCD(0x01);
        StrLCD("TAKE MED NOW");

        Buzzer_ON();

        wait_time = 0;

        /* Wait up to 30 seconds for user response */
        while(wait_time < 30)
        {
            if(Switch2_Pressed())   // User confirms medicine taken
            {
                Buzzer_OFF();
                RedLED_OFF();

                CmdLCD(0x01);
                StrLCD("MED TAKEN");
                delay_ms(1000);
                CmdLCD(0x01);

                return;
            }

            delay_ms(1000);
            wait_time++;
        }

        /* If no response → medicine missed */
        Buzzer_OFF();
        RedLED_ON();

        CmdLCD(0x01);
        StrLCD("MED MISSED");
        delay_ms(500);
        CmdLCD(0x01);
    }
}

/* ===================== INPUT HELPER ===================== */

/******************************************************************************
 * Function Name : Get2DigitValue
 * Description   : Takes 2-digit input from keypad and validates range
 * Parameters    : msg → display message
 *                 max → maximum allowed value
 * Returns       : Valid numeric value
 ******************************************************************************/
u32 Get2DigitValue(char *msg, u32 max)
{
    char d1, d2;
    u32 val;

    while(1)
    {
        CmdLCD(0x01);
        StrLCD(msg);
        CmdLCD(0xC0);

        d1 = GetKey_Blocking();
        CharLCD(d1);

        d2 = GetKey_Blocking();
        CharLCD(d2);

        val = (d1 - '0') * 10 + (d2 - '0');

        if(val <= max)
            return val;

        CmdLCD(0x01);
        StrLCD("INVALID INPUT");
        delay_ms(1000);
    }
}

/* ===================== RTC EDIT ===================== */

/******************************************************************************
 * Function Name : Edit_RTC
 * Description   : Allows user to modify RTC parameters
 ******************************************************************************/
void Edit_RTC(void)
{
    char key;
    s32 hour, minute, second, day, date, month, year;

    GetRTCTimeInfo(&hour, &minute, &second);
    GetRTCDateInfo(&date, &month, &year);

    while(1)
    {
        CmdLCD(0x01);
        StrLCD("1.H 2.M 3.S 4.D");
        CmdLCD(0xC0);
        StrLCD("5.dt 6.m 7.y");

        key = GetKey_Blocking();

        switch(key)
        {
            case '1': hour   = Get2DigitValue("SET HOUR(00-23)", 23); break;
            case '2': minute = Get2DigitValue("SET MIN(00-59)", 59); break;
            case '3': second = Get2DigitValue("SET SEC(00-59)", 59); break;
            case '4': day    = Get2DigitValue("SET DAY(0-6)", 6); break;
            case '5': date   = Get2DigitValue("SET DATE(01-31)", 31); break;
            case '6': month  = Get2DigitValue("SET MON(01-12)", 12); break;
            case '7': year   = Get2DigitValue("SET YEAR(00-99)", 99) + 2000; break;

            case '#':   // SAVE
                SetRTCTimeInfo(hour, minute, second);
                SetRTCDateInfo(date, month, year);
                SetRTCDay(day);

                CmdLCD(0x01);
                StrLCD("RTC SAVED");
                delay_ms(1000);
                CmdLCD(0x01);
                return;

            case '*':   // EXIT
                CmdLCD(0x01);
                StrLCD("EXIT");
                delay_ms(500);
                return;
        }
    }
}

/* ===================== MEDICINE TIME EDIT ===================== */

/******************************************************************************
 * Function Name : Edit_Med_Time
 * Description   : Allows user to set medicine reminder time
 ******************************************************************************/
void Edit_Med_Time(void)
{
    char key;
    u8 temp_hour = med_hour;
    u8 temp_min  = med_min;

    while(1)
    {
        CmdLCD(0x01);
        StrLCD("1.H 2.M");
        CmdLCD(0xC0);
        StrLCD("3.SAVE 4.EXIT");

        key = GetKey_Blocking();

        switch(key)
        {
            case '1':
                temp_hour = Get2DigitValue("MED HOUR(00-23)", 23);
                break;

            case '2':
                temp_min = Get2DigitValue("MED MIN(00-59)", 59);
                break;

            case '3':   // SAVE
                med_hour = temp_hour;
                med_min  = temp_min;
                med_time_set = 1;  

                CmdLCD(0x01);
                StrLCD("MED TIME SAVED");
                delay_ms(1000);
                CmdLCD(0x01);
                return;

            case '4':   // EXIT
                CmdLCD(0x01);
                StrLCD("EXIT");
                delay_ms(500);
                return;
        }
    }
}