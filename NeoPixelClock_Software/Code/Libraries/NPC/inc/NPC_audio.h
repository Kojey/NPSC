/**
  ******************************************************************************
  * @file    NPC_audio.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    12-March-2017
  * @brief   This file contains all the configuration prototypes used by the
  * 			audio firmware
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPC_INC_NPC_AUDIO_H_
#define NPC_INC_NPC_AUDIO_H_

/* Includes ------------------------------------------------------------------*/
#include "NPC_utils.h"

/** @addtogroup NPC
  * @{
  */

/** @addtogroup Audio
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/**
 * @defgroup Constant
 * @brief Define audio frequency and DMA frequency
 * @{
 */
#define AUDIO_FREQUENCY 11000
#define DMA_FREQUENCY  (86000000/(2*AUDIO_FREQUENCY))
/**
 * @}
 */

/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Configuration **************************************************************/
void audio_disable(void);
void audio_init(uint16_t *, uint16_t);
/* Play audio ******************************************************************/
void audio_play(uint16_t * , uint16_t);

#endif /* NPC_INC_NPC_AUDIO_H_ */

/**
 * 	@}
 */

/**
 * @}
 */
