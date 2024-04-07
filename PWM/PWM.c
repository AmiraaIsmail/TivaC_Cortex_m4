/**************************************************************************************/
/**************************************PWM.c*******************************************/
/**************************Created: 3/4/2024  10:00:00 PM******************************/
/********************************Author: Amira Ismail**********************************/
/**************************************************************************************/

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "PWM.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

void PWM_Init()
{
    // Configure PWM0 for DC motors
    SET_BIT(SYSCTL_RCGCPWM_R, 0);  // Enable PWM0 clock
    CLR_BIT(SYSCTL_RCC_R, 20);     // Clear divisor to run PWM clock at system clock speed

    // Configure GPIO pins for PWM0
    GPIO_PORTB_AFSEL_R |= 0xF0;    // Enable alternate function on PB4-PB7
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0x0000FFFF) | (0x44440000);  // Configure PB4-PB7 for PWM functionality
    GPIO_PORTB_DEN_R |= 0xF0;      // Enable digital functionality on PB4-PB7

    // Configure PWM0 Generator 0 for DC motors
    CLR_BIT(PWM0_0_CTL_R, 0);      // Disable PWM0 Generator 0
    PWM0_0_GENA_R = 0x8C;          // Set PWM0 Generator 0 control mode and output mode
    PWM0_0_LOAD_R = 8000 - 1;      // Set PWM0 Generator 0 load value for desired PWM frequency
    PWM0_0_CMPA_R = 8000 - 1;      // Set PWM0 Generator 0 compare A value for duty cycle
    SET_BIT(PWM0_0_CTL_R, 0);      // Enable PWM0 Generator 0

    // Configure PWM1 for servo motors
    SET_BIT(SYSCTL_RCGCPWM_R, 1);  // Enable PWM1 clock

    // Configure GPIO pins for PWM1
    GPIO_PORTF_AFSEL_R |= (1<<2);       // Enable alternate function on PF2 (for PWM)
    CLR_BIT(GPIO_PORTF_PCTL_R, 10);     // Clear PCTL register for PF2
    GPIO_PORTF_PCTL_R |= (5 << 10);     // Configure PF2 for PWM functionality
    SET_BIT(GPIO_PORTF_DEN_R, 2);       // Enable digital functionality on PF2

    // Configure PWM1 Generator 3 for servo motors
    CLR_BIT(PWM1_3_CTL_R, 0);      // Disable PWM1 Generator 3 counter
    CLR_BIT(PWM1_3_CTL_R, 1);      // Select down count mode of counter 3
    PWM1_3_GENA_R = 0x0000008C;    // Set PWM1 Generator 3 control mode and output mode
    PWM1_3_LOAD_R = 16000;         // Set load value for 1kHz PWM frequency
    PWM1_3_CMPA_R = 8000-1;        // Set duty cycle to 50%
    PWM1_3_CTL_R = 1;              // Enable PWM1 Generator 3 counter
}

void SetDutyCycle(u8 duty_cycle)
{
    // Calculate compare value based on duty cycle percentage
    u16 compare_value = (u16)((8000 * duty_cycle) / 100);

    // Set compare value for PWM0 Generator 0 (DC motors)
    PWM0_0_CMPA_R = compare_value;

    // Set compare value for PWM1 Generator 3 (servo motors)
    PWM1_3_CMPA_R = compare_value;
}
