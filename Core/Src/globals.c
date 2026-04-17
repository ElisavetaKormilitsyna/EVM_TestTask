#include "globals.h"

//--------------------------------------------------------
QueueHandle_t xCanDataQueue;
QueueHandle_t xAdcDataQueue;

//--------------------------------------------------------
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;

TIM_HandleTypeDef htim2;

//--------------------------------------------------------
uint16_t adcBuffer[ADC_CHANNEL_COUNT];
