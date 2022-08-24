//
// Created by Rule on 2022/8/24.
//

#include "main.h"
#include "rgb.h"

uint16_t SendBuffer[LED*24];

void ws2812b_sendBytes(void)
{
    HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_2, (uint32_t *)SendBuffer, LED*24);
    HAL_Delay(2);
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    if(htim == &htim2)
    {
                __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 0);
//       HAL_TIM_PWM_Stop_DMA(&htim2, TIM_CHANNEL_2);
    }
}
