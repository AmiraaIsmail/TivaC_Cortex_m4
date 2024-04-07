/*
 * main.c
 */

#include "GPIO.h"
#include "STD_TYPES.h"

void main(void)
{
    u8 reading;

    GPIO_Init_Port(PF);

    GPIO_Set_Pin_Direction(PF, PIN1, OUT);
    GPIO_Set_Pin_Direction(PF, PIN0, INPUT);

    while(1)
    {
        reading = GPIO_Get_Pin_Value(PF, PIN0);
        if (reading == 0)
        {
            GPIO_Set_Pin_Value(PF, PIN1, HIGH);
        }
        else
        {
            GPIO_Set_Pin_Value(PF, PIN1, LOW);
        }
    }
}
