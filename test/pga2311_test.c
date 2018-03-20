/******************************************************************************
 * @file    pga2311_test.c
 * @author  Rémi Pincent - INRIA
 * @date    20/07/2017
 *
 * @brief Test for Library for TI PGA2311 Audio Volume Control  www.ti.com/lit/ds/symlink/pga2311.pdf
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
#include "pga2311_test.h"
#include "logger.h"
#include "pinout.h"

/**************************************************************************
 * Manifest Constants
 **************************************************************************/

/**************************************************************************
 * Type Definitions
 **************************************************************************/

/**************************************************************************
 * Local Functions Declarations
 **************************************************************************/

/**************************************************************************
 * Global Functions Definitions
 **************************************************************************/
void PGA2311_test_1(SPI_HandleTypeDef* arg_ps_spiHandle)
{
	TsPGA2311 loc_s_pga2311 = {
			._ps_spi = arg_ps_spiHandle,

	};

	TEST_USER_INFO(__func__, NULL, "start");
	PGA2311_init(&loc_s_pga2311);

	for(float loc_f_gain = PGA2311_MIN_GAIN; loc_f_gain <= PGA2311_MAX_GAIN; loc_f_gain++)
	{
		TEST_USER_INFO(__func__, NULL, "set gain to %f", loc_f_gain);
		HAL_Delay(50);
		PGA2311_setGain(&loc_s_pga2311, loc_f_gain, loc_f_gain);
	}
	TEST_USER_INFO(__func__, NULL, "end");
}

/**************************************************************************
 * Local Functions Definitions
 **************************************************************************/
