/**************************************************************************************/
/**************************************nvic.c******************************************/
/**************************Created: 29/3/2024  10:00:00 AM*****************************/
/********************************Author: Amira Ismail**********************************/
/**************************************************************************************/

#include "nvic_reg.h"
#include "STD_TYPES.h"
#include "stdbool.h"
#include "bit_math.h"

void nvic_enableInterrupt(u8 intId)
{

    if (intId>=0 && intId<32)
    {
        NVIC_ISER0_REG = (1<<intId);
    }
    else if (intId>=32 && intId<64)
    {
        NVIC_ISER1_REG = (1<<(intId-32));
    }
    else
    {

    }
}

void nvic_disableInterrupt(u8 intId)
{
    if (intId>=0 && intId<32)
    {
        NVIC_ICER0_REG = (1<<intId);
    }
    else if (intId>=32 && intId<64)
    {
        NVIC_ICER1_REG = (1<<(intId-32));
    }
    else
    {

    }
}

void nvic_setPendingFlag(u8 intId)
{
    if (intId>=0 && intId<32)
    {
        NVIC_ISPR0_REG = (1<<intId);
    }
    else if (intId>=32 && intId<64)
    {
        NVIC_ISPR1_REG = (1<<(intId-32));
    }
    else
    {

    }
}

void nvic_clearPendingFlag(u8 intId)
{
    if (intId>=0 && intId<32)
    {
        NVIC_ICPR0_REG = (1<<intId);
    }
    else if (intId>=32 && intId<64)
    {
        NVIC_ICPR0_REG = (1<<(intId-32));
    }
    else
    {

    }
}

bool nvic_readActiveFlag(u8 intId)
{
    bool loc_result = FALSE;
    if (intId>=0 && intId<32)
    {
        loc_result = GET_BIT(NVIC_IABR0_REG,intId);
    }
    else if (intId>=32 && intId<64)
    {
        loc_result = GET_BIT(NVIC_IABR1_REG,(intId-32));
    }
    else
    {

    }
    return loc_result;
}

void nvic_setPriority(u8 line, u8 lvl)
{

    u8 reg_no = (line * 8) / 32;

    u8 byte_no = (line * 8) % 32;

    switch(reg_no)
    {
    case 0:
        NVIC_ICPR0_REG &= ~(0xff << byte_no*8);
        NVIC_ICPR0_REG |= lvl < (byte_no*8);

    case 1:
        NVIC_ICPR1_REG &= ~(0xff << byte_no*8);
        NVIC_ICPR1_REG |= lvl < (byte_no*8);
    }
}
