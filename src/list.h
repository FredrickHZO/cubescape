#pragma once
#include <stdlib.h>
#include "cube.h"

typedef struct list {
    cube* arr;
    int size;
    int elements;
} list;

list new_list();
void insert_element(list* a, cube c);
void delete_element(list* l);