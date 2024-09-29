//
// Created by Rares-Andrei Cotoi on 18.03.2024.
//

#pragma once

typedef struct Estate{
    char* type;
    char* address;
    int surface;
    int price;
}Estate;

typedef struct dynamic_array {
    Estate* data;
    int size;
    int capacity;
}DynamicArray;

typedef struct undo_stack{
    int* LPO; /// codes for LPO : 1 - add, 2 - delete, 3 - update
    Estate* estate;
    int size;
    int capacity;
}undo_stack;

typedef struct redo_stack{
    int* LPO; /// codes for LPO : 1 - add, 2 - delete, 3 - update
    Estate* estate;
    int size;
    int capacity;
}redo_stack;

Estate* create_estate(char* type, char* address, int surface, int price);
void destroy_estate(Estate* estate);
void destroy_undo_stack(undo_stack* undo);
void destroy_redo_stack(redo_stack* redo);
char* get_type(Estate* estate);
char* get_address(Estate* estate);
int get_surface(Estate* estate);
int get_price(Estate* estate);
