#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "domain/domain.h"
#include "repository/memory_repo.h"
#include "controller/controller.h"
#include "UI/UI.h"

int main(){
    DynamicArray* estates_array = init_estates_array();
    undo_stack* undo = init_undo_stack();
    redo_stack* redo = init_redo_stack();
    char option, bait_char;
    char type[20], address[50], searching_address[50];
    int surface, price;
    while(true){
        menu_option();
        scanf(" %c", &option);
        if(option == 'x'){
            for (int i = 0; i < estates_array->size; i++){
                destroy_estate(&estates_array->data[i]);
            }
            destroy_undo_stack(undo);
            destroy_redo_stack(redo);
            break;
        }
        if(option == 'a'){
            option_a_menu();
            scanf(" %c", &option);
            if(option == '1'){
                printf("Type: ");
                scanf(" %s", type);
                printf("Address: ");
                scanf("%c", &bait_char);
                fgets(address, 25, stdin);
                address[strlen(address) - 1] = '\0';
                printf("Surface: ");
                scanf(" %d", &surface);
                printf("Price: ");
                scanf(" %d", &price);
                add_estate(estates_array, type, address, surface, price);
                add_operation_to_undo_stack(undo, 1, create_estate(type, address, surface, price));
                printf("Estate added successfully!\n");
            }
            if(option == '2'){
                printf("Address: ");
                scanf("%c", &bait_char);
                fgets(address, 25, stdin);
                address[strlen(address) - 1] = '\0';
                Estate* estate = get_estate_by_address(estates_array, address);
                if(estate == NULL){
                    printf("No estate with this address\n");
                    continue;
                }
                else{
                    add_operation_to_undo_stack(undo, 2, create_estate(estate->type, estate->address, estate->surface, estate->price));
                    delete_estate(estates_array, address);
                    printf("Estate deleted successfully!\n");
                }
            }
            if(option == '3'){
                printf("Type: ");
                scanf(" %s", type);
                printf("Address: ");
                scanf("%c", &bait_char);
                fgets(address, 25, stdin);
                address[strlen(address) - 1] = '\0';
                printf("Surface: ");
                scanf(" %d", &surface);
                printf("Price: ");
                scanf(" %d", &price);
                Estate* searched_estate = get_estate_by_address(estates_array, address);
                if(searched_estate == NULL){
                    printf("No estate with this address\n");
                    continue;
                }
                else{
                    add_operation_to_undo_stack(undo, 3, searched_estate);
                    update_estate(estates_array, type, address, surface, price);
                    printf("Estate modified successfully!\n");
                }
            }
        }
        if(option == 'b'){
            printf("Search string: ");
            scanf("%c", &bait_char);
            fgets(searching_address, 25, stdin);
            searching_address[strlen(searching_address) - 1] = '\0';
            DynamicArray* searched_estates = get_searched_estates_sorted(estates_array, searching_address);
            print_all_estates(searched_estates);
        }
        if(option == 'p'){
            print_all_estates(estates_array);
        }
        if (option == 'c'){
            printf("Enter the matched type: ");
            scanf(" %s", type);
            printf("Enter the lowest surface: ");
            scanf(" %d", &surface);
            DynamicArray* estates_of_type = get_estates_of_type_with_surface_greater_than(estates_array, type, surface);
            print_all_estates(estates_of_type);
        }
        if (option == 'd') { //undo
            if (undo_lpo(estates_array, undo, redo) == 1){
                printf("Undone the Last Performed Operation successfully!\n");
            }
            else{
                printf("No more operations to undo!\n");
            }
        }
        if (option == 'e') { //redo
            if (redo_lpo(estates_array, undo, redo) == 1){
                printf("Redone the Last Performed Operation successfully!\n");
            }
            else{
                printf("No more operations to redo!\n");
            }
        }
    }
    return 0;

}