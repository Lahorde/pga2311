/******************************************************************************
 * @file    pga2311.cpp
 * @author  Rémi Pincent - INRIA
 * @date    20/07/2017
 *
 * @brief Library for :
 * - TI PGA2311 Audio Volume Control  www.ti.com/lit/ds/symlink/pga2311.pdf
 * - CIRRUS Logic CS3310 https://www.cirrus.com/products/cs3310/
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

/**************************************************************************
 * Include Files
 **************************************************************************/
#include "pga2311.h"
#include "pinout.h"
#include "stm32f0xx_hal_gpio.h"
#include "logger.h"
#include <math.h>

/**************************************************************************
 * Manifest Constants
 **************************************************************************/

/**************************************************************************
 * Type Definitions
 **************************************************************************/

/**************************************************************************
 * Local Functions Declarations
 **************************************************************************/
void PGA2311_setIntGain(TsPGA2311*, uint8_t arg_u8_rChGain, uint8_t arg_u8_lChGain);

/**************************************************************************
 * Global Functions Definitions
 **************************************************************************/
void PGA2311_init(TsPGA2311* arg_ps_pga2311)
{
	ASSERT(arg_ps_pga2311 != NULL
			&& arg_ps_pga2311->_ps_spi != NULL);

	arg_ps_pga2311->_u8_rChGain = 0;
	arg_ps_pga2311->_u8_lChGain = 0;

	/** SPI, GPIOs already initialized and configured */
  /** SPI configuration :
   * MSB first - CPOL0 CPHA0 => mode 0
   * default configuration can be used
   * NSS output activated on GPIO PREAMP_CS_Pin */
  
  /** Disable mute */
	HAL_GPIO_WritePin(	PREAMP_MUTE_GPIO_Port, PREAMP_MUTE_Pin, GPIO_PIN_SET);
}

void PGA2311_muteAll(TsPGA2311* arg_ps_pga2311)
{
	ASSERT(arg_ps_pga2311 != NULL
				&& arg_ps_pga2311->_ps_spi != NULL);

  /** software mute */
	PGA2311_setIntGain(arg_ps_pga2311, (uint8_t)0, (uint8_t)0);
 
  /** TODO : test HW mute */
} 

void PGA2311_unmuteAll(TsPGA2311* arg_ps_pga2311)
{
	ASSERT(arg_ps_pga2311 != NULL
				&& arg_ps_pga2311->_ps_spi != NULL);

	PGA2311_setIntGain(arg_ps_pga2311, arg_ps_pga2311->_u8_rChGain, arg_ps_pga2311->_u8_lChGain);
} 


void PGA2311_PGA2311_muteRight(TsPGA2311* arg_ps_pga2311)
{
	ASSERT(arg_ps_pga2311 != NULL
				&& arg_ps_pga2311->_ps_spi != NULL);

	PGA2311_setIntGain(arg_ps_pga2311, (uint8_t)0, arg_ps_pga2311->_u8_lChGain);
} 

void PGA2311_muteLeft(TsPGA2311* arg_ps_pga2311)
{
	ASSERT(arg_ps_pga2311 != NULL
				&& arg_ps_pga2311->_ps_spi != NULL);

	PGA2311_setIntGain(arg_ps_pga2311, arg_ps_pga2311->_u8_lChGain, (uint8_t)0);
} 

void PGA2311_setLeftGain(TsPGA2311* arg_ps_pga2311, float arg_f_lChGain)
{
	ASSERT(arg_ps_pga2311 != NULL
				&& arg_ps_pga2311->_ps_spi != NULL);
  ASSERT(arg_f_lChGain >= PGA2311_MIN_GAIN && arg_f_lChGain <= PGA2311_MAX_GAIN);
   
  /** datasheet 7.3.2 */ 
  arg_ps_pga2311->_u8_lChGain = round((arg_f_lChGain - 31.5)*2 + 255);
  PGA2311_setIntGain(arg_ps_pga2311, arg_ps_pga2311->_u8_rChGain, arg_ps_pga2311->_u8_lChGain);
} 

void PGA2311_setRightGain(TsPGA2311* arg_ps_pga2311, float arg_f_rChGain)
{
	ASSERT(arg_ps_pga2311 != NULL
				&& arg_ps_pga2311->_ps_spi != NULL);
  ASSERT(arg_f_rChGain >= PGA2311_MIN_GAIN && arg_f_rChGain <= PGA2311_MAX_GAIN);
   
  /** datasheet 7.3.2 */ 
  arg_ps_pga2311->_u8_rChGain = round((arg_f_rChGain - 31.5)*2 + 255);
  PGA2311_setIntGain(arg_ps_pga2311, arg_ps_pga2311->_u8_rChGain, arg_ps_pga2311->_u8_lChGain);
} 


void PGA2311_setGain(TsPGA2311* arg_ps_pga2311, float arg_f_rChGain, float arg_f_lChGain)
{
	ASSERT(arg_ps_pga2311 != NULL
				&& arg_ps_pga2311->_ps_spi != NULL);
  ASSERT(arg_f_lChGain >= PGA2311_MIN_GAIN && arg_f_lChGain <= PGA2311_MAX_GAIN
      && arg_f_rChGain >= PGA2311_MIN_GAIN && arg_f_rChGain <= PGA2311_MAX_GAIN);
  
  /** datasheet 7.3.2 */ 
  arg_ps_pga2311->_u8_rChGain = round((arg_f_rChGain - 31.5)*2 + 255);
  arg_ps_pga2311->_u8_lChGain = round((arg_f_lChGain - 31.5)*2 + 255);
  PGA2311_setIntGain(arg_ps_pga2311, arg_ps_pga2311->_u8_rChGain, arg_ps_pga2311->_u8_lChGain);
}

/**************************************************************************
 * Local Functions Definitions
 **************************************************************************/
void PGA2311_setIntGain(TsPGA2311* arg_ps_pga2311, uint8_t arg_u8_rChGain, uint8_t arg_u8_lChGain)
{
	ASSERT(arg_ps_pga2311 != NULL
				&& arg_ps_pga2311->_ps_spi != NULL);

	uint8_t loc_au8_gains[2] = {arg_u8_rChGain, arg_u8_lChGain};

  LOG_INFO_LN("Set gain to %f %f", 31.5-0.5*(255.0 - arg_u8_rChGain), 31.5-0.5*(255 - arg_u8_rChGain)); 
  /** transmit gains in blocking mode, 16 bits transfers */
  HAL_SPI_Transmit(arg_ps_pga2311->_ps_spi, loc_au8_gains, 1, 20);
}
