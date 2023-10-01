#include "list.h"

list new_list() {
    list l = {
        .elements = 0,
        .size     = 10,
        .arr      = (struct cube*) malloc(sizeof(struct cube) * l.size)
    };
    return l;
}

void reset_list(list* l) {
    free(l->arr);
    l->elements = 0;
    l->size     = 10;
    l->arr      = (struct cube*) malloc(sizeof(struct cube) * l->size);
}

void list_double(list* l) {
    l->size *= 2;
    struct cube* tmp = (struct cube*) malloc(sizeof(struct cube) * l->size);
    for (int i = 0; i < l->elements; i++) {
       tmp[i] = l->arr[i];
    }
    free(l->arr);
    l->arr = tmp; 
}

void insert_element(list* l, struct cube c) {
    if (l->elements == l->size-1) {
        list_double(l);
    }
    l->arr[l->elements] = c;
    l->elements += 1;
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