#include <stdio.h>
#include <string.h>
#include "main.h"
#include "linklist.h"

int main(int argc, char** argv) {
    bool   exit        = false;
	char   input       = 0;
	int    number      = 0;

    link_list_init();

	printf("Hello! This is a demo of linked list in a limited array.\n");
	while(!exit) {
       	if (input != '\n'){
           printf("\n[q: quit, a: add, r: remove, c: clear, d: dump, w: dump raw]\nCmd: ");
        }
		if(scanf("%c",&input) == 1) {
		    switch(input)
		    {
            case 'a':
                printf("Add a node\n");
                printf("Please input a number: ");
                if (scanf("%d", &number) == 1){
                    link_list_add(number);
                }
                break;
	        case 'r':
	            printf("Remove a node\n");
	            printf("Please input the number you want to remove: ");
	            if (scanf("%d", &number) == 1){
	                link_list_remove_number(number);
	            }
	            break;
	        case 'c':
	            printf("Clear all nodes\n");
	            link_list_clear();
	            break;
	        case 'd':
	            printf("Dump all nodes\n");
	            link_list_dump();
	            break;
	        case 'w':
	            printf("Dump raw\n");
	            link_list_dump_raw();
	            break;
            case 'q':
                printf("Quit\n");
                exit = true;
                break;
		    default:
		        if (input != '\n'){
		            printf("Unknown command...\n");
		        }
		        break;
		    }
		}
	}

	return 0;
}
