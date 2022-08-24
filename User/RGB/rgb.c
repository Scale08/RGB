//
// Created by Rule on 2022/8/24.
//

#include <stdlib.h>
#include <string.h>
#include "rgb.h"
#include "ws2812b.h"

CircleList rgbHandle;

bool rgbInit(void)
{
    Node * pNode;
    uint8_t i;

    memset(SendBuffer, 0, (LED*24)*sizeof(uint16_t));

    Node * pBlock = (Node *)malloc(LED*sizeof(Node));
    if (pBlock == NULL)
        return false;
    memset(pBlock, 0, LED*sizeof(Node));

    rgbHandle.current = pBlock;
    pNode = pBlock;

    for(i = 1; i < LED; i++)
    {
        pNode->next = pBlock + i;
        pNode->next->last = pNode;
        pNode = pNode->next;
    }

    rgbHandle.current->last = pNode;
    pNode->next = rgbHandle.current;
    rgbHandle.n = LED;

    return true;
}

void rgbDataChange(void (* pFunction)(Item * pItem))
{
    Node * pNode = rgbHandle.current;

    do{
        pFunction(&pNode->item);
        pNode = pNode->next;
    }while (pNode != rgbHandle.current);
}

void rgbDataSend(bool flag)
{
    Node * pNode = rgbHandle.current;
    uint8_t m = 0, n = 0;

    do
    {
        for(m = 0; m < 24; m++)
        {
            if(m<8)
                SendBuffer[n*24+m] = ((pNode->item.G<<(m%8))&0x80)==0x80?BIT1:BIT0;
            else if(m<16)
                SendBuffer[n*24+m] = ((pNode->item.R<<(m%8))&0x80)==0x80?BIT1:BIT0;
            else
                SendBuffer[n*24+m] = ((pNode->item.B<<(m%8))&0x80)==0x80?BIT1:BIT0;
        }

        if(flag == true)
        {
            pNode->item.R=0;
            pNode->item.B=0;
            pNode->item.G=0;
        }

        pNode = pNode->next;
        n++;
    }while (pNode != rgbHandle.current);

    ws2812b_sendBytes();
}
