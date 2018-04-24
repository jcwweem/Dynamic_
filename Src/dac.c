/*
 * dac.c
 *
 *  Created on: Mar 29, 2018
 *      Author: Joep van de Weem
 */

#include "dac.h"

DAC_HandleTypeDef hdac1; //defines the ADC's config

void DAC_initialiseDAC(){

	DAC_ChannelConfTypeDef sConfig;

	hdac1.Instance = DAC1;
	if (HAL_DAC_Init(&hdac1) != HAL_OK)
	{
		while(1); //error
	}

	//DAC channel OUT1 config
	sConfig.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE;					//disables sampleandhold
	sConfig.DAC_Trigger = DAC_TRIGGER_NONE;									//disables external/internal triggers
	sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;						//enables the outputbuffer
	sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_DISABLE;
	sConfig.DAC_UserTrimming = DAC_TRIMMING_FACTORY;
	if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_1) != HAL_OK)
	{
		while(1); //error
	}

	HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);
}

void DAC_setDAC(uint32_t voltage){
	if(HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, (uint32_t) voltage) != HAL_OK) {
		while(1); //error
	}
}
