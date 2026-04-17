#ifndef INC_GLOBALS_H_
#define INC_GLOBALS_H_

#include "FreeRTOS.h"
#include "queue.h"
#include "main.h"

//Constants ADC ----------------------------------------------------
#define ADC_CHANNEL_COUNT 2

//Constants CAN ----------------------------------------------------
#define CAN_PAYLOAD_LENGTH 		2
#define CAN_THERMISTOR0_MSG_ID	0x100
#define CAN_THERMISTOR1_MSG_ID	0x101

//Temperature calculation data -------------------------------------
#define R_CONST 10000.0f
#define ADC_MAX_VALUE 4095.0f //2^12 - 1
#define V_REF 3.3f
#define B 3950.0f

#define CELSIUS_TO_KELVIN(c) ((c) + 273.15f)
#define KELVIN_TO_CELSIUS(k) ((k) - 273.15f)

//Queues ----------------------------------------------------------
extern QueueHandle_t xCanDataQueue;
extern QueueHandle_t xAdcDataQueue;

//Periphery handlers-----------------------------------------------
extern ADC_HandleTypeDef hadc1;
//extern DMA_HandleTypeDef hdma_adc1;

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

extern TIM_HandleTypeDef htim2;

//Data Buffers ---------------------------------------------------
extern uint16_t adcBuffer[ADC_CHANNEL_COUNT];

//Structures -----------------------------------------------------
typedef struct
{
	uint16_t thermistor0;
	uint16_t thermistor1;
} AdcData_t;

typedef struct
{
	int16_t temperature0_celsius_x10;
	int16_t temperature1_celsius_x10;
} CanData_t;

#endif /* INC_GLOBALS_H_ */
