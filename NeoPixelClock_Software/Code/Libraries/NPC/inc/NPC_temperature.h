/**
  ******************************************************************************
  * @file    NPC_temperature.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    15-March-2017
  * @brief   This file contains all the configuration prototypes used by the
  * 			temperature firmware
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPC_INC_NPC_TEMPERATURE_H_
#define NPC_INC_NPC_TEMPERATURE_H_

/* Includes ------------------------------------------------------------------*/
#include "NPC_utils.h"

/** @addtogroup NPC
  * @{
  */

/** @addtogroup Temperature
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup Temparature_Const
 *  @{
 */
#define ADCx					ADC3
#define ADC_CHANNEL				ADC_Channel_7
#define ADC_DMA_CHANNEL 		DMA_Channel_0
#define ADC_DMA_STREAM			DMA2_Stream0
#define ADCx_DR_ADDRESS      	((uint32_t)0x4001224C)
/**
 * @}
 */
/* Exported variables --------------------------------------------------------*/
extern uint16_t adc_voltage = 0;
/* Exported macro ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void temperature_init(void);
int16_t temperature_read(void);

#endif /* NPC_INC_NPC_TEMPERATURE_H_ */

/**
 * 	@}
 */

/**
 * @}
 */
