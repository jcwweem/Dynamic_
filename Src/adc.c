/*
 * adc.c
 *
 *  Created on: Mar 29, 2018
 *      Author: Joep van de Weem
 */

#include "adc.h"

/*
 * This code is generated using STM32CUBEX
 */
void ADC_initialiseADC(){

	  ADC_ChannelConfTypeDef sConfig;

	    /**Common config
	    */
	  hadc1.Instance = ADC1;
	  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV2;					//sets the prescaler to 2, the ADC would present glitches if this wasn'tt applied
	  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;						//
	  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;					//
	  hadc1.Init.LowPowerAutoWait = DISABLE;
	  hadc1.Init.ContinuousConvMode = ENABLE;							//
	  hadc1.Init.NbrOfConversion = 3;
	  hadc1.Init.DiscontinuousConvMode = DISABLE;						//
	  hadc1.Init.NbrOfDiscConversion = 1;
	  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	  hadc1.Init.DMAContinuousRequests = DISABLE;
	  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
	  hadc1.Init.OversamplingMode = DISABLE;
	  if (HAL_ADC_Init(&hadc1) != HAL_OK)
	  {
	    while(1);
	  }

	    /**Configure Regular Channel
	    */
	  sConfig.Channel = ADC_CHANNEL_8;
	  sConfig.Rank = ADC_REGULAR_RANK_1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
	  sConfig.SingleDiff = ADC_SINGLE_ENDED;
	  sConfig.OffsetNumber = ADC_OFFSET_NONE;
	  sConfig.Offset = 0;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    while(1);
	  }

	    /**Configure Regular Channel
	    */
	  sConfig.Channel = ADC_CHANNEL_6;
	  sConfig.Rank = ADC_REGULAR_RANK_2;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    while(1);
	  }

	    /**Configure Regular Channel
	    */
	  sConfig.Channel = ADC_CHANNEL_5;
	  sConfig.Rank = ADC_REGULAR_RANK_3;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    while(1);
	  }



}

void ADC_getADC(uint32_t* channel1, uint32_t* channel2, uint32_t* channel3){
	HAL_ADC_Start(&hadc1);									//starts the ADC

	while(HAL_ADC_PollForConversion(&hadc1,0) != HAL_OK); 	//get the value from the first channel
	*channel1 = HAL_ADC_GetValue(&hadc1);

	while(HAL_ADC_PollForConversion(&hadc1,0) != HAL_OK); 	//get the value from the second channel
	*channel2 = HAL_ADC_GetValue(&hadc1);

	while(HAL_ADC_PollForConversion(&hadc1,0) != HAL_OK); 	//get the value from the third channel
	*channel3 = HAL_ADC_GetValue(&hadc1);

	HAL_ADC_Stop(&hadc1);									//stops the ADC
}
