#include "canDataProcessing.h"

CAN_TxHeaderTypeDef MakeCanHeader(uint32_t stdId)
{
	CAN_TxHeaderTypeDef txHeader = {0};
	txHeader.StdId = stdId;
	txHeader.ExtId = 0;
	txHeader.IDE = CAN_ID_STD;
	txHeader.RTR = CAN_RTR_DATA;
	txHeader.DLC = CAN_PAYLOAD_LENGTH;

	return txHeader;
}

HAL_StatusTypeDef SendCanMessage(uint32_t stdId, uint16_t data)
{
	uint32_t txMailbox = 0;
	uint8_t canBuffer[2] = {0};

	canBuffer[0] = (data >> 8) & 0xFF;
	canBuffer[1] = data & 0xFF;

	CAN_TxHeaderTypeDef header = MakeCanHeader(stdId);

	return HAL_CAN_AddTxMessage(&hcan1, &header, canBuffer, &txMailbox);
}

//--------------------------------------------------------------------------------------------------
void CanSendingTask(void *argument)
{
	HAL_CAN_Start(&hcan1);

	while (1)
	{
		CanData_t canData = {0};

		if(xQueueReceive(xCanDataQueue, &canData, portMAX_DELAY) == pdPASS)
		{
			if(HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) != 0)
			{
				//todo something if  status != OK
				HAL_StatusTypeDef msg0Status = SendCanMessage(CAN_THERMISTOR0_MSG_ID, canData.temperature0_celsius_x10);

				HAL_StatusTypeDef msg1Status = SendCanMessage(CAN_THERMISTOR1_MSG_ID, canData.temperature1_celsius_x10);
			}
		}
	}
}
