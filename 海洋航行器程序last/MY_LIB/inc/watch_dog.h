#ifndef __WATCH_DOG_H
#define __WATCH_DOG_H
#include "sys.h"

//���Ź������궨��  ��ʱ500ms
#define PRER1   3 
#define RLR1    625


void IWDG_Init(u8 prer,u16 rlr);
void Feed_WatchDog(void);
void WatchDog_Init(void);




#endif
