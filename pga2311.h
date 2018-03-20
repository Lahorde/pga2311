/******************************************************************************
 * @file    pga2311.h
 * @author  Rémi Pincent - INRIA
 * @date    20/07/2017
 *
 * @brief Library for :
 * * TI PGA2311 Audio Volume Control  www.ti.com/lit/ds/symlink/pga2311.pdf
 * * CIRRUS Logic CS3310 https://www.cirrus.com/products/cs3310/
 * Project : pga2311
 * Contact:  Rémi Pincent - remi.pincent@inria.fr
 *
 * Revision History:
 * 
 * LICENSE :
 * pga2311 (c) by Rémi Pincent
 * pga2311 is licensed under a
 * Creative Commons Attribution-NonCommercial 3.0 Unported License.
 *
 * You should have received a copy of the license along with this
 * work.  If not, see <http://creativecommons.org/licenses/by-nc/3.0/>.
 *****************************************************************************/
#ifndef PGA2311_H
#define PGA2311_H
 
#ifdef __cplusplus
extern "C"
{
#endif
/**************************************************************************
 * Include Files
 **************************************************************************/
#include "stm32f0xx_hal.h"
#include <stdint.h>
/**************************************************************************
 * Manifest Constants
 **************************************************************************/
#define PGA2311_MIN_GAIN -95.5
#define PGA2311_MAX_GAIN  31.5

/**************************************************************************
 * Type Definitions
 **************************************************************************/
typedef struct
{
	SPI_HandleTypeDef* _ps_spi;
	uint8_t _u8_rChGain;
	uint8_t _u8_lChGain;
}TsPGA2311;
/**************************************************************************
 * Global variables
 **************************************************************************/

/**************************************************************************
 * Macros
 **************************************************************************/

/**************************************************************************
 * Global Functions Declarations
 **************************************************************************/

void PGA2311_init(TsPGA2311*);

/**
 * @brief Mute both channel left and right channels
 */
void PGA2311_muteAll(TsPGA2311*);

/**
 * @brief Unute both channel left and right channels.
 * Volume before mute restored
 */
void PGA2311_unmuteAll(TsPGA2311*);

/**
 * @brief mute right channel
 */
void PGA2311_muteRight(TsPGA2311*);

/**
 * @brief mute left channel
 */
void PGA2311_muteLeft(TsPGA2311*);


/**
 * @brief set left channel gain
 *
 * @param arg_f_lChGain, channel gain in db from +31.5 to -95.5dB
 */
void PGA2311_setLeftGain(TsPGA2311*, float arg_f_lChGain);

/**
 * @brief set right channel gain
 *
 * @param arg_f_lChGain, channel gain in db from +31.5 to -95.5dB
 */
void PGA2311_setRightGain(TsPGA2311*, float arg_f_rChGain);


/**
 * @brief set right and left channel gains
 *
 * @param arg_f_rChGain, channel gain in db from +31.5 to -95.5dB
 * @param arg_f_fChGain, channel gain in db from +31.5 to -95.5dB
 */
void PGA2311_setGain(TsPGA2311*, float arg_f_rChGain, float arg_f_lChGain);

#ifdef __cplusplus
}
#endif

#endif /* PGA2311_H */
