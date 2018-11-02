// SysTick.c
// Implements two busy-wait based delay routines.
#include <stdint.h>
// Initialize SysTick with busy wait running at bus clock.
#define NVIC_ST_CTRL_R      (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R    (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R   (*((volatile unsigned long *)0xE000E018))
#define reload 0x00FFFFFF
void SysTick_Init(void){
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = reload;
	NVIC_ST_CTRL_R = 0x00000005;
}
// The delay parameter is in units of the 80 MHz core clock. (12.5 ns)
void SysTick_Wait(unsigned long delay){					//cycles * 12.5e^-9 = delay time in sec 
	NVIC_ST_RELOAD_R = delay - 1;
	NVIC_ST_CURRENT_R = 0;
	while ((NVIC_ST_CTRL_R & 0x00010000)==0){ // bit 16 has 1 if Systick_wait has reached 0
	}																					// once it has reched zero, it stops looping
}

// Time delay using busy wait.
// waits for count*10ms
// 10000us equals 10ms
void SysTick_Wait10ms(uint32_t delay){
	uint32_t i;
	for (i = 0;i<delay;i++){
		SysTick_Wait(800000);			//12.5 ns times 800,000 = 10 ms
	}

}

