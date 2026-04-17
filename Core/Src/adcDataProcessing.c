#include "adcDataProcessing.h"
#include "globals.h"

float GetVoltage(uint16_t adcValue)
{
	return (((float)adcValue / ADC_MAX_VALUE) * V_REF);
}

float GetResistance(float voltage)
{
	return (R_CONST * voltage / (V_REF - voltage));
}

uint16_t GetTemperature(float resistance)
{
	float temperature_kelvin = 1.0f /
			(
				1.0f / (CELSIUS_TO_KELVIN(25)) +
				(1.0f / B) * logf(resistance/R_CONST)
			);

	uint16_t temperature_celsius_x10 = (int16_t)(KELVIN_TO_CELSIUS(temperature_kelvin) * 10.0f);

	return temperature_celsius_x10;
}


uint16_t CalculateTemperature(uint16_t adcValue)
{
	float voltage = GetVoltage(adcValue);

	float resistance = GetResistance(voltage);

	uint16_t temperature = GetTemperature(resistance);

	return temperature;
}

//-----------------------------------------------------------------------------------------------
void AdcDataProcessingTask(void *argument)
{
	AdcData_t adcData = {0};
	CanData_t canData = {0};

	while (1)
	{
		if(xQueueReceive(xAdcDataQueue, &adcData, portMAX_DELAY) == pdPASS)
		{
			canData.temperature0_celsius_x10 = CalculateTemperature(adcData.thermistor0);
			canData.temperature1_celsius_x10 = CalculateTemperature(adcData.thermistor1);

			xQueueSend(xCanDataQueue, &canData, 0);
		}
	}
}
