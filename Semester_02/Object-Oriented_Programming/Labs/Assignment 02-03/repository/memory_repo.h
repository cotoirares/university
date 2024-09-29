
#pragma once
#include "../domain/domain.h"
#include <stdbool.h>

DynamicArray* init_repo();
undo_stack* init_undo_stack();
redo_stack* init_redo_stack();
void add_estate_to_list(DynamicArray* estates_array, Estate* estate);
void delete_estate_from_list(DynamicArray* estates_array, int index);
void update_estate_in_list(DynamicArray* estates_array, Estate* new_estate, int index);
bool undo_lpo(DynamicArray* estates_array, undo_stack* undo, redo_stack* redo);
bool redo_lpo(DynamicArray* estates_array, undo_stack* undo, redo_stack* redo);
Estate* copy_estate(Estate* estate);
void add_operation_to_undo_stack(undo_stack* undo, int LPO, Estate* estate);
Estate* get_estate_by_address(DynamicArray* estates_array, char* address);
void add_operation_to_redo_stack(redo_stack* redo, int LPO, Estate* estate);
void delete_operation_from_undo_stack(undo_stack* undo);
void delete_operation_from_redo_stack(redo_stack* redo);
void print_all(DynamicArray* estates_array);
