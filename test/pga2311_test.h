/******************************************************************************
 * @file    pga2311_test.h
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
#ifndef PGA2311_TEST_H
#define PGA2311_TEST_H

#ifdef __cplusplus
extern "C"
{
#endif
/**************************************************************************
 * Include Files
 **************************************************************************/
#include "pga2311.h"

/**************************************************************************
 * Manifest Constants
 **************************************************************************/

/**************************************************************************
 * Type Definitions
 **************************************************************************/

/**************************************************************
 * Global variables
 **************************************************************************/

/**************************************************************************
 * Macros
 **************************************************************************/

/**************************************************************************
 * Global Functions Declarations
 **************************************************************************/
void PGA2311_test_1(SPI_HandleTypeDef*);

#ifdef __cplusplus
}
#endif

#endif /* PGA2311_TEST_H */
