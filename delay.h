#ifndef __DELAY_H
#define __DELAY_H

typedef void (*DELAY_CALLBACK)(int, void *);

void DELAY_Init();
int DELAY_Timeout(unsigned long us, DELAY_CALLBACK callback, void *param);
int DELAY_Interval(unsigned long us, DELAY_CALLBACK callback, void *param);

#endif