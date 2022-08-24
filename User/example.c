//
// Created by Rule on 2022/8/25.
//

#include "main.h"
#include "example.h"
#include "rgb.h"

static void mode0(Item * pItem);
static void mode1(Item * pItem);

void exampleInit(void)
{
    rgbInit();
}

void exampleRunning(void)
{
    uint16_t i;
//    rgbDataChange(mode0);
//    rgbDataSend(false);
    rgbDataChange(mode1);
    for(i = 0; i < 300; i++)
    {
        rgbHandle.current = rgbHandle.current->last;
        rgbDataSend(false);
        HAL_Delay(30);
    }
    for(i = 0; i < 300; i++)
    {
        if((i/30)%2)
            rgbHandle.current = rgbHandle.current->next;
        else
            rgbHandle.current = rgbHandle.current->last;
        rgbDataSend(false);
        HAL_Delay(30);
    }
}

static void mode0(Item * pItem)
{
    pItem->R = 0;
    pItem->G = 0;
    pItem->B = 0;
}

static void mode1(Item * pItem)
{
    static uint8_t i = 0;

    switch (i%15) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            pItem->R=50;
            pItem->G=0;
            pItem->B=0;
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            pItem->R=0;
            pItem->G=50;
            pItem->B=0;
            break;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            pItem->R=0;
            pItem->G=0;
            pItem->B=50;
            break;
    }

    i++;
}