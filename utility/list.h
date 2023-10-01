#pragma once
#include <stdlib.h>
#include <cube.h>

typedef struct list {
    struct cube* arr;
    int size;
    int elements;
} list;

list new_list();
void reset_list(list* l);
void insert_element(list* l, struct cube c);
void delete_element(list* l);
