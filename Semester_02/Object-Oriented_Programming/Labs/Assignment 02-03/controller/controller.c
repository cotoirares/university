

#include "../repository/memory_repo.h"
#include "../domain/domain.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

DynamicArray* init_estates_array(){
    DynamicArray* estates_array = init_repo();
    return estates_array;
}

void add_estate(DynamicArray* estates_array, char* type, char* address, int surface, int price){
    Estate* estate = create_estate(type, address, surface, price);
    add_estate_to_list(estates_array, estate);
}

void delete_estate(DynamicArray* estates_array, char* address){
    int index = -1;
    for(int i = 0; i < estates_array->size; i++){
        if(strcmp(get_address(&estates_array->data[i]), address) == 0){
            index = i;
            break;
        }
    }
    if(index == -1){
        return;
    }
    delete_estate_from_list(estates_array, index);
}

void update_estate(DynamicArray* estates_array, char* type, char* address, int surface, int price){
    int index = -1;
    for(int i = 0; i < estates_array->size; i++){
        if(strcmp(get_address(&estates_array->data[i]), address) == 0){
            index = i;
            break;
        }
    }
    if(index == -1){
        return;
    }
    Estate* new_estate = create_estate(type, address, surface, price);
    update_estate_in_list(estates_array, new_estate, index);
}

void print_all_estates(DynamicArray* estates_array){
    print_all(estates_array);
}


int compareByPrice(const void* a, const void* b) {
    Estate* estateA = (Estate*)a;
    Estate* estateB = (Estate*)b;
    return (estateA->price > estateB->price) - (estateA->price < estateB->price);
}


DynamicArray* get_searched_estates_sorted(DynamicArray* estates_list, const char* searchString) {
    DynamicArray* searchedEstates = (DynamicArray*)malloc(sizeof(DynamicArray));
    searchedEstates->size = 0;
    searchedEstates->capacity = estates_list->capacity;
    searchedEstates->data = (Estate*)malloc(sizeof(Estate) * searchedEstates->capacity);
    for (int i = 0; i < estates_list->size; i++) {
        if (strstr(get_address(&estates_list->data[i]), searchString) != NULL) {
            add_estate_to_list(searchedEstates, &estates_list->data[i]);
        }
    }
    qsort(searchedEstates->data, searchedEstates->size, sizeof(Estate), compareByPrice);
    return searchedEstates;
}

DynamicArray* get_estates_of_type_with_surface_greater_than(DynamicArray* estates_list, const char* type, int surface) {
    DynamicArray* searchedEstates = (DynamicArray*)malloc(sizeof(DynamicArray));
    searchedEstates->size = 0;
    searchedEstates->capacity = estates_list->capacity;
    searchedEstates->data = (Estate*)malloc(sizeof(Estate) * searchedEstates->capacity);
    for (int i = 0; i < estates_list->size; i++) {
        if (strcmp(get_type(&estates_list->data[i]), type) == 0 && get_surface(&estates_list->data[i]) > surface) {
            add_estate_to_list(searchedEstates, &estates_list->data[i]);
        }
    }
    return searchedEstates;
}