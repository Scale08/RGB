//
// Created by Rule on 2022/8/24.
//

#ifndef RGB_WS2812B_H
#define RGB_WS2812B_H

#include <stdint.h>

#define BIT0 30
#define BIT1 60

extern uint16_t SendBuffer[];

void ws2812b_sendBytes(void);

#endif //RGB_WS2812B_H
