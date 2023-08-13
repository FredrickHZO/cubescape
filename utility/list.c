#include "list.h"

list new_list() {
    list l = {
        .elements = 0,
        .size     = 10,
        .arr      = (cube*) malloc(sizeof(cube) * l.size)
    };
    return l;
}

void list_double(list* a) {
    cube* tmp;
    a->size *= 2;
    tmp = (cube*) malloc(sizeof(cube) * a->size);
    for (int i = 0; i < a->elements; i++) {
       tmp[i] = a->arr[i];
    }
    a->arr = tmp; 
}

void insert_element(list* a, cube c) {
    if (a->elements == a->size-1) {
        list_double(a);
    }
    a->arr[a->elements] = c;
    a->elements += 1;
 }

 void delete_element(list* l) {
    if (l->elements == 0) {
        return; 
    }
    for (int i = 0; i < l->elements; i++) {
        l->arr[i] = l->arr[i+1];
    }
    l->elements -= 1;
 }