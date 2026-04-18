#ifndef DOSEGUARDIAN_IO_H
#define DOSEGUARDIAN_IO_H

#include <LPC21xx.h>
#include "types.h"

/* Pin definitions */
#define SW1     14
#define SW2     15
#define BUZZER  16
#define RED_LED 18

/* Function prototypes */
void IO_Init(void);
u8 Switch1_Pressed(void);
u8 Switch2_Pressed(void);
void Buzzer_ON(void);
void Buzzer_OFF(void);
void RedLED_ON(void);
void RedLED_OFF(void);

#endif
