
///* Includes */
#include "application.h"
#include "framework.h"
#include "systemTest.h"
#include "unitTest.h"
//#include "neopixel.h"
//#include "bluetooth.h"

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
	framework_init();
	application_init();
	STM_EVAL_LEDInit(LED6);
//	neopixel_setBrightness(50);
//	neopixel_setAllPixelRGB(255,0,255);
	while(1)
	{
		alarm_synchronize();
		nextion_instructionUpdate();
		instruction_execute();
		visual_update(true);

	}
}

/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
2 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
