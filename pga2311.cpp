/******************************************************************************
 * @file    pga2311.cpp
 * @author  Rémi Pincent - INRIA
 * @date    20/07/2017
 *
 * @brief Library for TI PGA2311 Audio Volume Control  www.ti.com/lit/ds/symlink/pga2311.pdf
 * Project : peopeo_speaker
 * Contact:  Rémi Pincent - remi.pincent@inria.fr
 *
 * Revision History:
 * 
 * LICENSE :
 * peopeo_speaker (c) by Rémi Pincent
 * peopeo_speaker is licensed under a
 * Creative Commons Attribution-NonCommercial 3.0 Unported License.
 *
 * You should have received a copy of the license along with this
 * work.  If not, see <http://creativecommons.org/licenses/by-nc/3.0/>.
 *****************************************************************************/

/**************************************************************************
 * Include Files
 **************************************************************************/
#include "pga2311.h"

#include <SPI.h>
#include <logger_config.h>
#include <math.h>

/**************************************************************************
 * Manifest Constants
 **************************************************************************/

/**************************************************************************
 * Type Definitions
 **************************************************************************/

/**************************************************************************
 * Public Methods Definitions
 **************************************************************************/
PGA2311::PGA2311(uint8_t arg_u8_spiCSPin, uint8_t arg_u8_mutePin):
  /** mute */ 
  _u8_rChGain(0),
  _u8_lChGain(0),
  _u8_spiCSPin(arg_u8_spiCSPin),
  _u8_mutePin(arg_u8_mutePin)
{
}

void PGA2311::init(void)
{
  /** SPI configuration :
   * MSB first - CPOL0 CPHA0 => mode 0
   * default configuration can be used */
  SPI.begin();
  
  /** Do not select PGA2311 as SPI slave */ 
  pinMode(_u8_spiCSPin, OUTPUT);
  digitalWrite(_u8_spiCSPin, HIGH); 
  
  /** Disable mute */
  pinMode(_u8_mutePin, OUTPUT);
  digitalWrite(_u8_mutePin, HIGH); 
}

void PGA2311::muteAll(void)
{
  /** software mute */
  setGain((uint8_t)0, (uint8_t)0);
 
  /** TODO : test HW mute */
} 

void PGA2311::unmuteAll(void)
{
  setGain(_u8_rChGain, _u8_lChGain);
} 


void PGA2311::PGA2311::muteRight(void)
{
  setGain((uint8_t)0, _u8_lChGain);
} 

void PGA2311::muteLeft(void)
{
  setGain(_u8_lChGain, (uint8_t)0);
} 

void PGA2311::setLeftGain(float arg_f_lChGain)
{
  ASSERT(arg_f_lChGain >= PGA2311_MIN_GAIN && arg_f_lChGain <= PGA2311_MAX_GAIN);
   
  /** datasheet 7.3.2 */ 
  _u8_lChGain = round((arg_f_lChGain - 31.5)*2 + 255);
  setGain(_u8_rChGain, _u8_lChGain);
} 

void PGA2311::setRightGain(float arg_f_rChGain)
{
  ASSERT(arg_f_rChGain >= PGA2311_MIN_GAIN && arg_f_rChGain <= PGA2311_MAX_GAIN);
   
  /** datasheet 7.3.2 */ 
  _u8_rChGain = round((arg_f_rChGain - 31.5)*2 + 255);
  setGain(_u8_rChGain, _u8_lChGain);
} 


void PGA2311::setGain(float arg_f_rChGain, float arg_f_lChGain)
{
  ASSERT(arg_f_lChGain >= PGA2311_MIN_GAIN && arg_f_lChGain <= PGA2311_MAX_GAIN
      && arg_f_rChGain >= PGA2311_MIN_GAIN && arg_f_rChGain <= PGA2311_MAX_GAIN);
  
  /** datasheet 7.3.2 */ 
  _u8_rChGain = round((arg_f_rChGain - 31.5)*2 + 255);
  _u8_lChGain = round((arg_f_lChGain - 31.5)*2 + 255);
  setGain(_u8_rChGain, _u8_lChGain);
}

/**************************************************************************
* Private Methods Definitions
**************************************************************************/
void PGA2311::setGain(uint8_t arg_u8_rChGain, uint8_t arg_u8_lChGain)
{
  LOG_INFO_LN("Set gain to %f %f", 31.5-0.5*(255.0 - arg_u8_rChGain), 31.5-0.5*(255 - arg_u8_rChGain)); 
  /** select PGA2311 SPI slave */
  digitalWrite(_u8_spiCSPin, LOW); 
  SPI.transfer(arg_u8_rChGain); 
  SPI.transfer(arg_u8_lChGain); 
  digitalWrite(_u8_spiCSPin, HIGH); 
}
