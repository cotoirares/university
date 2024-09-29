/// file containing the tests for all the non-UI functions

#include "domain/domain.h"
#include "repository/memory_repo.h"
#include "controller/controller.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void test_create_estate(){
    Estate* estate = create_estate("house", "Mihai Viteazu 1", 100, 100000);
    assert(strcmp(get_type(estate), "house") == 0);
    assert(strcmp(get_address(estate), "Mihai Viteazu 1") == 0);
    assert(get_surface(estate) == 100);
    assert(get_price(estate) == 100000);
    destroy_estate(estate);
}

///
void test_add_estate() {
    DynamicArray *estates_array = init_estates_array();
    add_estate(estates_array, "house", "Mihai Viteazu 1", 100, 100000);
    assert(estates_array->size == 1);
    assert(strcmp(get_type(&estates_array->data[0]), "house") == 0);
    assert(strcmp(get_address(&estates_array->data[0]), "Mihai Viteazu 1") == 0);
    assert(get_surface(&estates_array->data[0]) == 100);
    assert(get_price(&estates_array->data[0]) == 100000);
    destroy_estate(&estates_array->data[0]);
    free(estates_array->data);
    free(estates_array);
}

/// tests for A.2
void test_delete_estate() {
    DynamicArray *estates_array = init_estates_array();
    add_estate(estates_array, "house", "Mihai Viteazu 1", 100, 100000);
    add_estate(estates_array, "house", "Mihai Viteazu 2", 100, 100000);
    add_estate(estates_array, "house", "Mihai Viteazu 3", 100, 100000);
    delete_estate(estates_array, "Mihai Viteazu 2");
    assert(estates_array->size == 2);
    assert(strcmp(get_type(&estates_array->data[0]), "house") == 0);
    assert(strcmp(get_address(&estates_array->data[0]), "Mihai Viteazu 1") == 0);
    assert(get_surface(&estates_array->data[0]) == 100);
    assert(get_price(&estates_array->data[0]) == 100000);
    assert(strcmp(get_type(&estates_array->data[1]), "house") == 0);
    assert(strcmp(get_address(&estates_array->data[1]), "Mihai Viteazu 3") == 0);
    assert(get_surface(&estates_array->data[1]) == 100);
    assert(get_price(&estates_array->data[1]) == 100000);
    destroy_estate(&estates_array->data[0]);
    destroy_estate(&estates_array->data[1]);
    free(estates_array->data);
    free(estates_array);
}

/// tests for A.3
void test_update_estate() {
    DynamicArray *estates_array = init_estates_array();
    add_estate(estates_array, "house", "Mihai Viteazu 1", 100, 100000);
    add_estate(estates_array, "house", "Mihai Viteazu 2", 100, 100000);
    add_estate(estates_array, "house", "Mihai Viteazu 3", 100, 100000);
    update_estate(estates_array, "apartment", "Mihai Viteazu 2", 100, 100000);
    assert(estates_array->size == 3);
    assert(strcmp(get_type(&estates_array->data[0]), "house") == 0);
    assert(strcmp(get_address(&estates_array->data[0]), "Mihai Viteazu 1") == 0);
    assert(get_surface(&estates_array->data[0]) == 100);
    assert(get_price(&estates_array->data[0]) == 100000);
    assert(strcmp(get_type(&estates_array->data[1]), "apartment") == 0);
    assert(strcmp(get_address(&estates_array->data[1]), "Mihai Viteazu 2") == 0);
    assert(get_surface(&estates_array->data[1]) == 100);
    assert(get_price(&estates_array->data[1]) == 100000);
    assert(strcmp(get_type(&estates_array->data[2]), "house") == 0);
    assert(strcmp(get_address(&estates_array->data[2]), "Mihai Viteazu 3") == 0);
    assert(get_surface(&estates_array->data[2]) == 100);
    assert(get_price(&estates_array->data[2]) == 100000);
    destroy_estate(&estates_array->data[0]);
    destroy_estate(&estates_array->data[1]);
    destroy_estate(&estates_array->data[2]);
    free(estates_array->data);
    free(estates_array);
}

void test_compareByPrice() {
    Estate* estate1 = create_estate("house", "Mihai Viteazu 1", 100, 100000);
    Estate* estate2 = create_estate("house", "Mihai Viteazu 2", 100, 100000);
    assert(compareByPrice(estate1, estate2) == 0);
    destroy_estate(estate1);
    destroy_estate(estate2);
}

/// tests for functionality B
void test_get_searched_estates_sorted() {
    DynamicArray *estates_array = init_estates_array();
    add_estate(estates_array, "house", "Mihai Viteazu 1", 100, 100000);
    add_estate(estates_array, "house", "Mihai Viteazu 2", 100, 100000);
    add_estate(estates_array, "house", "Mihai Viteazu 3", 100, 100000);
    add_estate(estates_array, "apartment", "Mihai Viteazu 4", 100, 100000);
    add_estate(estates_array, "apartment", "Mihai Viteazu 5", 100, 100000);
    add_estate(estates_array, "apartment", "Mihai Viteazu 6", 100, 100000);
    DynamicArray* searched_estates = get_searched_estates_sorted(estates_array, "Mihai Viteazu 2");
    assert(searched_estates->size == 1);
    assert(strcmp(get_type(&searched_estates->data[0]), "house") == 0);
    assert(strcmp(get_address(&searched_estates->data[0]), "Mihai Viteazu 2") == 0);
    assert(get_surface(&searched_estates->data[0]) == 100);
    assert(get_price(&searched_estates->data[0]) == 100000);
    destroy_estate(&searched_estates->data[0]);
    free(searched_estates->data);
    free(searched_estates);
    destroy_estate(&estates_array->data[0]);
    destroy_estate(&estates_array->data[1]);
    destroy_estate(&estates_array->data[2]);
    destroy_estate(&estates_array->data[3]);
    destroy_estate(&estates_array->data[4]);
    destroy_estate(&estates_array->data[5]);
    free(estates_array->data);
    free(estates_array);
}

/// tests for functionality C
void test_get_estates_of_type_with_surface_greater_than() {
    DynamicArray *estates_array = init_estates_array();
    add_estate(estates_array, "house", "Mihai Viteazu 1", 100, 100000);
    add_estate(estates_array, "house", "Mihai Viteazu 2", 100, 100000);
    add_estate(estates_array, "house", "Mihai Viteazu 3", 100, 100000);
    add_estate(estates_array, "apartment", "Mihai Viteazu 4", 100, 100000);
    add_estate(estates_array, "apartment", "Mihai Viteazu 5", 100, 100000);
    add_estate(estates_array, "apartment", "Mihai Viteazu 6", 100, 100000);
    DynamicArray *searched_estates = get_estates_of_type_with_surface_greater_than(estates_array, "house", 50);
    assert(searched_estates->size == 3);
    assert(strcmp(get_type(&searched_estates->data[0]), "house") == 0);
    assert(strcmp(get_address(&searched_estates->data[0]), "Mihai Viteazu 1") == 0);
    assert(get_surface(&searched_estates->data[0]) == 100);
    assert(get_price(&searched_estates->data[0]) == 100000);
    assert(strcmp(get_type(&searched_estates->data[1]), "house") == 0);
    assert(strcmp(get_address(&searched_estates->data[1]), "Mihai Viteazu 2") == 0);
    assert(get_surface(&searched_estates->data[1]) == 100);
    assert(get_price(&searched_estates->data[1]) == 100000);
    assert(strcmp(get_type(&searched_estates->data[2]), "house") == 0);
    assert(strcmp(get_address(&searched_estates->data[2]), "Mihai Viteazu 3") == 0);
    assert(get_surface(&searched_estates->data[2]) == 100);
    assert(get_price(&searched_estates->data[2]) == 100000);
    destroy_estate(&searched_estates->data[0]);
    destroy_estate(&searched_estates->data[1]);
    destroy_estate(&searched_estates->data[2]);
}

void test_undo_redo_lpo() {
    DynamicArray *estates_array = init_estates_array();
    add_estate(estates_array, "house", "Mihai Viteazu 1", 100, 100000);
    add_estate(estates_array, "house", "Mihai Viteazu 2", 100, 100000);
    add_estate(estates_array, "house", "Mihai Viteazu 3", 100, 100000);
    undo_stack *undo = (undo_stack *) malloc(sizeof(undo_stack));
    undo->size = 0;
    undo->capacity = 10;
    undo->LPO = (int *) malloc(sizeof(int) * undo->capacity);
    undo->estate = (Estate *) malloc(sizeof(Estate) * undo->capacity);
    redo_stack *redo = (redo_stack *) malloc(sizeof(redo_stack));
    redo->size = 0;
    redo->capacity = 10;
    redo->LPO = (int *) malloc(sizeof(int) * redo->capacity);
    redo->estate = (Estate *) malloc(sizeof(Estate) * redo->capacity);
    add_operation_to_undo_stack(undo, 2, &estates_array->data[1]);
    add_operation_to_undo_stack(undo, 3, &estates_array->data[1]);
    add_operation_to_undo_stack(undo, 1, &estates_array->data[1]);
    undo_lpo(estates_array, undo, redo);
    assert(estates_array->size == 2);
    assert(strcmp(get_type(&estates_array->data[0]), "house") == 0);
    assert(strcmp(get_address(&estates_array->data[0]), "Mihai Viteazu 1") == 0);
    assert(get_surface(&estates_array->data[0]) == 100);
    assert(get_price(&estates_array->data[0]) == 100000);
    assert(strcmp(get_type(&estates_array->data[1]), "house") == 0);
    assert(strcmp(get_address(&estates_array->data[1]), "Mihai Viteazu 3") == 0);
    assert(get_surface(&estates_array->data[1]) == 100);
    assert(get_price(&estates_array->data[1]) == 100000);
    destroy_estate(&estates_array->data[0]);
    destroy_estate(&estates_array->data[1]);
    free(estates_array->data);
    free(estates_array);
    free(undo->LPO);
    free(undo->estate);
    free(undo);
    free(redo->LPO);
    free(redo->estate);
    free(redo);
}

void run_all_tests(){
    test_create_estate();
    test_add_estate();
    test_delete_estate();
    test_update_estate();
    test_compareByPrice();
    test_get_searched_estates_sorted();
    test_get_estates_of_type_with_surface_greater_than();
    test_undo_redo_lpo();
}


