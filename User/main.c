#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "beep.h"
#include "key.h"

double sound[12] = {
	1911.128
};

int idx[] = {
	0, 0, 7, 7, 9, 9, 7, -1,
	5, 5, 4, 4, 2, 2, 0, -1,
	7, 7, 5, 5, 4, 4, 2, -1,
	7, 7, 5, 5, 4, 4, 2, -1,
	0, 0, 7, 7, 9, 9, 7, -1,
	5, 5, 4, 4, 2, 2, 0,
};

int nk = sizeof(idx) / sizeof(idx[0]);

int nsound = sizeof(sound) / sizeof(sound[0]);

int main()
{
	u8 key;
	u8 cs = 0;
	u16 _;
	u32 t = 0;
	double tp = 1.05946309;
	int jp = 250000;
	
	for (_ = 1; _ < 12; _++) {
		sound[_] = sound[_ - 1] / tp;
	}
	
	SysTick_Init(72);
	LED_Init();
	BEEP_Init();
	KEY_Init();
	while (1) {
		while (cs < nk)
		{
			int i;
			switch (KEY_Scan(0)) {
				case KEY_UP_PRESS:
					cs = 0;
					break;
				case KEY0_PRESS:
					cs = nk - 1;
					t = jp;
					break;
			}
			i = idx[cs];
			if (i != -1) {
				double x = sound[i];
				BEEP = !BEEP;
				t += x;
				delay_us(x);
			} else {
				BEEP = 0;
				delay_us(jp);
				t += jp;
			}
			if (t >= jp) {
				t -= jp;
				cs++;
				BEEP = 0;
				delay_us(2000);
			}
		}
		BEEP = 0;
		while (1) {
			if (KEY_UP_PRESS == KEY_Scan(0)) {
				break;
			}
			delay_ms(100);
		}
		cs = 0;
	}
}
