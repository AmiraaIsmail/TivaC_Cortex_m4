/**************************************************************************************/
/**************************************nvic.h******************************************/
/**************************Created: 29/3/2024  10:00:00 AM*****************************/
/********************************Author: Amira Ismail**********************************/
/**************************************************************************************/

#ifndef NVIC_H_
#define NVIC_H_

#include "STD_TYPES.h"
#include "stdbool.h"

void nvic_enableInterrupt(u8 intId);
void nvic_disableInterrupt(u8 intId);

void nvic_setPendingFlag(u8 intId);
void nvic_clearPendingFlag(u8 intId);

bool nvic_readActiveFlag(u8 intId);
void nvic_setPriority(u8 line, u8 lvl);


#endif /* NVIC_H_ */
