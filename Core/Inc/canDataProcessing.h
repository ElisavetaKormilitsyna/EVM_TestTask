#ifndef INC_CANDATAPROCESSING_H_
#define INC_CANDATAPROCESSING_H_

#include "stdint.h"
#include "globals.h"

void CanSendingTask(void *argument);

//---------------------------------------------------------------
CAN_TxHeaderTypeDef MakeCanHeader(uint32_t stdId);

HAL_StatusTypeDef SendCanMessage(uint32_t stdId, uint16_t data);

#endif /* INC_CANDATAPROCESSING_H_ */
