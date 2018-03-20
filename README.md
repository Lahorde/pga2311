# PGA2311
## Overview
C driver for :
 * [TI PGA2311 preamp](hhttp://www.ti.com/lit/ds/symlink/pga2311.pdf) 
 * [CIRRUS Logic CS3310](https://www.cirrus.com/products/cs3310/)

## Supported targets
STM32s with HAL

## Code snippet

	TsPGA2311 loc_s_pga2311 = {
			._ps_spi = arg_ps_spiHandle,

	};

	PGA2311_init(&loc_s_pga2311);

	for(float loc_f_gain = PGA2311_MIN_GAIN; loc_f_gain <= PGA2311_MAX_GAIN; loc_f_gain++)
	{
		printf("set gain to %f", loc_f_gain);
		HAL_Delay(50);
		PGA2311_setGain(&loc_s_pga2311, loc_f_gain, loc_f_gain);
	}