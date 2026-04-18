#ifndef _DOSEGUARDIAN_H_
#define _DOSEGUARDIAN_H_
#include "types.h"


void DoseGuardian_Run(void);
void Edit_RTC(void);
void Edit_Med_Time(void);
char GetDigitKey(void);
u32 Get2DigitValue(char *, u32);

#endif
