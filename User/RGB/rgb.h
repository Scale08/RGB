//
// Created by Rule on 2022/8/24.
//

#ifndef RGB_RGB_H
#define RGB_RGB_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t R;
    uint8_t G;
    uint8_t B;
}Item;

typedef struct node {
    Item item;
    struct node * next;
    struct node * last;
}Node;

typedef struct {
    Node * current;
    uint8_t n;
}CircleList;

#define LED     30

extern CircleList rgbHandle;

bool rgbInit(void);
void rgbDataChange(void (* pFunction)(Item * pItem));
void rgbDataSend(bool flag);

#endif //RGB_RGB_H
