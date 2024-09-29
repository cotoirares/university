

#include "UI.h"
#include <stdio.h>

void menu_option(){
    printf("(a) Add, delete or update an estate. An estate is uniquely identified by its address.\n");
    printf("(b) Display all estates whose address contains a given string (if the string is empty, all estates will be considered), sorted ascending by their price.\n");
    printf("(c) See all estates of a given type, having the surface greater than a user provided value.\n");
    printf("(d) Undo the Last Performed Operation.\n");
    printf("(e) Redo the Last Undone Operation.\n");
    printf("(p) Print all estates\n");
    printf("(x) Exit\n");
    printf("Choose an option: ");
}

void option_a_menu(){
    printf("1. Add estate\n");
    printf("2. Delete estate\n");
    printf("3. Update estate\n");
    printf("Choose an option: ");
}