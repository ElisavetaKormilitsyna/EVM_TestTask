#ifndef INC_ADCDATAPROCESSING_H_
#define INC_ADCDATAPROCESSING_H_

#include "stdint.h"

void AdcDataProcessingTask(void *argument);

//---------------------------------------------------------------
uint16_t CalculateTemperature(uint16_t adcValue);

float GetVoltage(uint16_t adcValue);

float GetResistance(float voltage);

uint16_t GetTemperature(float resistance);

#endif /* INC_ADCDATAPROCESSING_H_ */
