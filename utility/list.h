#pragma once
#include <stdlib.h>
#include <cube.h>

typedef struct list {
    struct cube* arr;
    int size;
    int elements;
} list;

list new_list();
void insert_element(list* a, struct cube c);
void delete_element(list* l);
