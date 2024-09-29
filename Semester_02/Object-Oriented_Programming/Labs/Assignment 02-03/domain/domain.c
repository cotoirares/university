//
// Created by Rares-Andrei Cotoi on 18.03.2024.
//

#include "domain.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Estate* create_estate(char* type, char* address, int surface, int price){
    Estate* estate = (Estate*)malloc(sizeof(Estate));
    estate->type = (char*)malloc(sizeof(char) * (strlen(type) + 1));
    estate->address = (char*)malloc(sizeof(char) * (strlen(address) + 1));
    strcpy(estate->type, type);
    strcpy(estate->address, address);
    estate->surface = surface;
    estate->price = price;
    return estate;
}

void destroy_estate(Estate* estate){
    free(estate->type);
    free(estate->address);
    free(estate);
}

void destroy_undo_stack(undo_stack* undo){
    free(undo->LPO);
    free(undo->estate);
    free(undo);
}

void destroy_redo_stack(redo_stack* redo){
    free(redo->LPO);
    free(redo->estate);
    free(redo);
}

char* get_type(Estate* estate){
    return estate->type;
}

char* get_address(Estate* estate){
    return estate->address;
}

int get_surface(Estate* estate){
    return estate->surface;
}

int get_price(Estate* estate){
    return estate->price;
}

