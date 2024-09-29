
#include "memory_repo.h"
#include "../domain/domain.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void generate_initial_estates(DynamicArray* estates_array){
    Estate* estate_to_add = create_estate("house", "teodor mihali 50", 100, 1000);
    add_estate_to_list(estates_array, estate_to_add);
    estate_to_add = create_estate("apartment", "mihail kogalniceanu 10", 200, 2000);
    add_estate_to_list(estates_array, estate_to_add);
    estate_to_add = create_estate("penthouse", "aurel vlaicu 43", 300, 3000);
    add_estate_to_list(estates_array, estate_to_add);
    estate_to_add = create_estate("house", "teodor mihali 51", 100, 10001);
    add_estate_to_list(estates_array, estate_to_add);
    estate_to_add = create_estate("apartment", "mihail kogalniceanu 15", 200, 2050);
    add_estate_to_list(estates_array, estate_to_add);
    estate_to_add = create_estate("house", "teodor mihali 52", 120, 150);
    add_estate_to_list(estates_array, estate_to_add);
    estate_to_add = create_estate("penthouse", "mihail kogalniceanu 11", 200, 20040);
    add_estate_to_list(estates_array, estate_to_add);
    estate_to_add = create_estate("penthouse", "aurel vlaicu 5", 340, 3200);
    add_estate_to_list(estates_array, estate_to_add);
    estate_to_add = create_estate("penthouse", "teodor mihali 555", 110, 12001);
    add_estate_to_list(estates_array, estate_to_add);
    estate_to_add = create_estate("apartment", "mihail kogalniceanu 112", 200, 2050);
    add_estate_to_list(estates_array, estate_to_add);
}

DynamicArray* init_repo(){
    DynamicArray* estates_array = (DynamicArray*)malloc(sizeof(DynamicArray));
    estates_array->size = 0;
    estates_array->capacity = 10;
    estates_array->data = (Estate*)malloc(sizeof(Estate) * estates_array->capacity);
    generate_initial_estates(estates_array);
    return estates_array;
}

undo_stack* init_undo_stack(){
    undo_stack* undo = (undo_stack*)malloc(sizeof(undo_stack));
    undo->LPO = (int*)malloc(sizeof(int));
    undo->estate = (Estate*)malloc(sizeof(Estate));
    undo->size = 0;
    undo->capacity = 10;
    return undo;
}

redo_stack* init_redo_stack(){
    redo_stack* redo = (redo_stack*)malloc(sizeof(redo_stack));
    redo->LPO = (int*)malloc(sizeof(int));
    redo->estate = (Estate*)malloc(sizeof(Estate));
    redo->size = 0;
    redo->capacity = 10;
    return redo;
}

Estate* get_estate_by_address(DynamicArray* estates_array, char* address){
    for(int i = 0; i < estates_array->size; i++){
        if(strcmp(get_address(&estates_array->data[i]), address) == 0){
            return &estates_array->data[i];
        }
    }
    return NULL;
}

void add_estate_to_list(DynamicArray* estates_array, Estate* estate){
    if(estates_array->size == estates_array->capacity){
        estates_array->capacity *= 2;
        estates_array->data = (Estate*)realloc(estates_array->data, sizeof(Estate) * estates_array->capacity);
    }
    estates_array->data[estates_array->size++] = *estate;
}

void delete_estate_from_list(DynamicArray* estates_array, int index){
    for(int i = index; i < estates_array->size - 1; i++){
        estates_array->data[i] = estates_array->data[i + 1];
    }
    estates_array->size--;
}

void update_estate_in_list(DynamicArray* estates_array, Estate* new_estate, int index){
    estates_array->data[index].surface = new_estate->surface;
    estates_array->data[index].price = new_estate->price;
    strcpy(estates_array->data[index].type, new_estate->type);
}

void add_operation_to_undo_stack(undo_stack* undo, int LPO, Estate* estate){
    if(undo->size == undo->capacity){
        undo->capacity *= 2;
        undo->LPO = (int*)realloc(undo->LPO, sizeof(int) * undo->capacity);
        undo->estate = (Estate*)realloc(undo->estate, sizeof(Estate) * undo->capacity);
    }
    undo->LPO[undo->size] = LPO;
    undo->estate[undo->size++] = *estate;
}

void add_operation_to_redo_stack(redo_stack* redo, int LPO, Estate* estate){
    if(redo->size == redo->capacity){
        redo->capacity *= 2;
        redo->LPO = (int*)realloc(redo->LPO, sizeof(int) * redo->capacity);
        redo->estate = (Estate*)realloc(redo->estate, sizeof(Estate) * redo->capacity);
    }
    redo->LPO[redo->size] = LPO;
    redo->estate[redo->size++] = *estate;
}

void delete_operation_from_undo_stack(undo_stack* undo){
    undo->size--;
}

void delete_operation_from_redo_stack(redo_stack* redo){
    redo->size--;
}

bool undo_lpo(DynamicArray* estates_array, undo_stack* undo, redo_stack* redo){
    if(undo->size <= 0){
        return false;
    }
    int LPO = undo->LPO[undo->size - 1];
    Estate* estate = (Estate*)malloc(sizeof(Estate));
    estate->type = (char*)malloc(sizeof(char) * 100);
    estate->address = (char*)malloc(sizeof(char) * 100);
    estate->surface = undo->estate[undo->size - 1].surface;
    estate->price = undo->estate[undo->size - 1].price;
    strcpy(estate->type, undo->estate[undo->size - 1].type);
    strcpy(estate->address, undo->estate[undo->size - 1].address);
    if(LPO == 1){
        int index = -1;
        for(int i = 0; i < estates_array->size; i++){
            if(strcmp(get_address(&estates_array->data[i]), get_address(estate)) == 0){
                index = i;
                break;
            }
        }
        delete_estate_from_list(estates_array, index);
        add_operation_to_redo_stack(redo, 1, estate);
    }
    else if(LPO == 2){
        add_estate_to_list(estates_array, estate);
        add_operation_to_redo_stack(redo, 2, estate);
    }
    else if(LPO == 3){
        int index = -1;
        for(int i = 0; i < estates_array->size; i++){
            if(strcmp(get_address(&estates_array->data[i]), get_address(estate)) == 0){
                index = i;
                break;
            }
        }
        Estate* new_estate = create_estate(estate->type, estate->address, estate->surface, estate->price);
        update_estate_in_list(estates_array, new_estate, index);
        add_operation_to_redo_stack(redo, 3, estate);
    }
    delete_operation_from_undo_stack(undo);
    return true;
}

bool redo_lpo(DynamicArray* estates_array, undo_stack* undo, redo_stack* redo){
    if(redo->size <= 0){
        return false;
    }
    int LPO = redo->LPO[redo->size - 1];
    Estate* estate = (Estate*)malloc(sizeof(Estate));
    estate->type = (char*)malloc(sizeof(char) * 100);
    estate->address = (char*)malloc(sizeof(char) * 100);
    estate->surface = redo->estate[redo->size - 1].surface;
    estate->price = redo->estate[redo->size - 1].price;
    strcpy(estate->type, redo->estate[redo->size - 1].type);
    strcpy(estate->address, redo->estate[redo->size - 1].address);
    if(LPO == 1){
        add_estate_to_list(estates_array, estate);
        add_operation_to_undo_stack(undo, 1, estate);
    }
    else if(LPO == 2){
        int index = -1;
        for(int i = 0; i < estates_array->size; i++){
            if(strcmp(get_address(&estates_array->data[i]), get_address(estate)) == 0){
                index = i;
                break;
            }
        }
        delete_estate_from_list(estates_array, index);
        add_operation_to_undo_stack(undo, 2, estate);
    }
    else if(LPO == 3){
        int index = -1;
        for(int i = 0; i < estates_array->size; i++){
            if(strcmp(get_address(&estates_array->data[i]), get_address(estate)) == 0){
                index = i;
                break;
            }
        }
        Estate* new_estate = create_estate(estate->type, estate->address, estate->surface, estate->price);
        update_estate_in_list(estates_array, new_estate, index);
        add_operation_to_undo_stack(undo, 3, estate);
    }
    delete_operation_from_redo_stack(redo);
    return true;
}

void print_all(DynamicArray* estates_array){
    for(int i = 0; i < estates_array->size; i++){
        printf("Type: %s, Address: %s, Surface: %d, Price: %d\n", get_type(&estates_array->data[i]), get_address(&estates_array->data[i]), get_surface(&estates_array->data[i]), get_price(&estates_array->data[i]));
    }
}