

#pragma once

DynamicArray* init_estates_array();
void add_estate(DynamicArray* estates_array, char* type, char* address, int surface, int price);
void delete_estate(DynamicArray* estates_array, char* address);
void update_estate(DynamicArray* estates_array, char* type, char* address, int surface, int price);
void print_all_estates(DynamicArray* estates_array);
int compareByPrice(const void* a, const void* b);
DynamicArray* get_searched_estates_sorted(DynamicArray* estates_list, const char* searchString);
DynamicArray* get_estates_of_type_with_surface_greater_than(DynamicArray* estates_list, const char* type, int surface);
