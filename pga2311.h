/******************************************************************************
 * @file    pga2311.h
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
#ifndef PGA2311_H
#define PGA2311_H
 
/**************************************************************************
 * Include Files
 **************************************************************************/
#include <stdint.h>
/**************************************************************************
 * Manifest Constants
 **************************************************************************/
#define PGA2311_MIN_GAIN -95.5
#define PGA2311_MAX_GAIN  31.5

/**************************************************************************
 * Type Definitions
 **************************************************************************/

/**************************************************************************
 * Global variables
 **************************************************************************/

/**************************************************************************
 * Macros
 **************************************************************************/

/**************************************************************************
 *  Class Declarations
 **************************************************************************/
class PGA2311 
{
  /** Public types */
  public :
    
  /** private members */  
  private :
  	uint8_t _u8_rChGain, _u8_lChGain;
    uint8_t _u8_spiCSPin, _u8_mutePin; 
    
  /** public methods */
	public :
    
    /** Default constructor, SPI will be used */ 
    PGA2311(uint8_t arg_u8_spiCSPin, uint8_t arg_u8_mutePin);
    
    void init(void);
    
    /**
     * @brief Mute both channel left and right channels
     */
    void muteAll(void);
    
    /**
     * @brief Unute both channel left and right channels.
     * Volume before mute restored
     */
    void unmuteAll(void);
    
    /**
     * @brief mute right channel 
     */
    void muteRight(void);
    
    /**
     * @brief mute left channel 
     */
    void muteLeft(void);
    
    
    /**
     * @brief set left channel gain
     *
     * @param arg_f_lChGain, channel gain in db from +31.5 to -95.5dB
     */
    void setLeftGain(float arg_f_lChGain);
    
    /**
     * @brief set right channel gain
     *
     * @param arg_f_lChGain, channel gain in db from +31.5 to -95.5dB
     */
    void setRightGain(float arg_f_rChGain);
    
    
    /**
     * @brief set right and left channel gains
     *
     * @param arg_f_rChGain, channel gain in db from +31.5 to -95.5dB
     * @param arg_f_fChGain, channel gain in db from +31.5 to -95.5dB
     */
    void setGain(float arg_f_rChGain, float arg_f_lChGain);
    
    /** Private methods */
  private :
    void setGain(uint8_t arg_u8_rChGain, uint8_t arg_u8_lChGain);
};

#endif /* PGA2311_H */
