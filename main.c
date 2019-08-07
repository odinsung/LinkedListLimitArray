#include <stdio.h>
#include <string.h>

typedef unsigned char uchar;
typedef unsigned char bool;

#define true  1
#define false 0

typedef struct{
    uchar   UserIndex;
    uchar   Month;
    uchar   Day;
    uchar   Hour;
    uchar   Minute;
}Log_t;

#define LOG_NUM_MAX  10

typedef struct{
    int     Prev;   // 0xFF means 'NULL'
    int     Next;   // 0xFF means 'NULL'
    Log_t   Log;    
}LogLL_t; 


int LogHead = 0xFF;
int LogTail = 0xFF;
LogLL_t LogLL[LOG_NUM_MAX];


void log_ll_init(void){
    memset(LogLL, 0xFF, sizeof(LogLL_t) * LOG_NUM_MAX);
}

void log_dump(void){
    int num = 0;
    int current = 0xFF;
    printf("Head: %02d   Tail: %02d", LogHead, LogTail);
    if (LogHead == 0xFF){
        printf("\nNo Log");
    }else{
        current = LogHead;
        do{
            printf("\n%02d: %02d - %02d %02d %02d %02d", num++, LogLL[current].Log.UserIndex, \
                                                                LogLL[current].Log.Month, \
                                                                LogLL[current].Log.Day, \
                                                                LogLL[current].Log.Hour, \
                                                                LogLL[current].Log.Minute);
            current = LogLL[current].Next;                                                                
        }while(current != 0xFF);
    }
    printf("\n\n");
}

void log_add(uchar userIndex, uchar month, uchar day, uchar hour, uchar minute){
    int current = 0xFF;
    int newSlot = 0xFF;
    newSlot = log_find_empty();
    if (newSlot != 0xFF){ // Empty slot found.
        printf("slot %d\n", newSlot);
        if (LogHead == 0xFF && LogTail == 0xFF){
            LogHead = newSlot;
            LogTail = newSlot;
            LogLL[newSlot].Prev = 0xFF;
            LogLL[newSlot].Next = 0xFF;
        }else{
            LogLL[LogTail].Next = newSlot;
            LogLL[newSlot].Prev = LogTail;
            LogTail = newSlot; // New Tail
        }
    }else{ // Log Full!
        newSlot = LogHead;                  // newSlot = 0
        LogHead = LogLL[newSlot].Next;      // LogHead = 1
        LogLL[LogHead].Prev = 0xFF;         // LogLL[1].Prev = 0xFF
        LogLL[newSlot].Prev = LogTail;      // LogLL[0].Prev = 49
        LogLL[LogTail].Next = newSlot;      // LogLL[49].Next = 0
        LogLL[newSlot].Next = 0xFF;         // LogLL[0].Next = 0xFF
        LogTail = newSlot;                  // LogTail = 0        
    }
    LogLL[newSlot].Log.UserIndex    = userIndex;
    LogLL[newSlot].Log.Month        = month;
    LogLL[newSlot].Log.Day          = day;
    LogLL[newSlot].Log.Hour         = hour;
    LogLL[newSlot].Log.Minute       = minute;    
}

bool log_get(Log_t *log, int index){
    bool found = false;
    int current = LogHead;
    int i=0;
    if (LogHead != 0xFF && LogTail != 0xFF){ // Not empty
        for(i=0; i<=index; i++){
            if (i == index){
                found = true;
                break;
            }
            current = LogLL[current].Next;
            if (current == 0xFF){
                break;
            }
        }
        if (found){
            memcpy(log, &(LogLL[current].Log), sizeof(Log_t));
        }
    }
    return found;
}

bool log_remove_user_index(uchar userIndex){
    bool found = false;
    int current = LogHead;
    int tmp = 0;
    if (LogHead != 0xFF && LogTail != 0xFF){
        do{
            if (LogLL[current].Log.UserIndex == userIndex){
                found = true;
                if (current == LogHead){
                    LogHead = LogLL[current].Next; // New head = Next
                    if (LogHead != 0xFF){
                        LogLL[LogHead].Prev = 0xFF;
                        LogLL[current].Next = 0xFF;
                        current = LogHead; // Move to the new head.
                    }else{ // There is only 1 node, remove it and log is empty.
                        LogTail = 0xFF;
                        current = 0xFF; // Log is empty, search done.
                    }
                }else if (current == LogTail){
                    LogTail = LogLL[current].Prev; // New tail = Prev
                    LogLL[LogTail].Next = 0xFF;
                    LogLL[current].Prev = 0xFF;
                    current = 0xFF; // To the end, search done.
                }else{
                    LogLL[LogLL[current].Prev].Next = LogLL[current].Next;
                    LogLL[LogLL[current].Next].Prev = LogLL[current].Prev;
                    tmp = LogLL[current].Next;
                    LogLL[current].Prev = 0xFF;
                    LogLL[current].Next = 0xFF;
                    current = tmp;
                }
            }
        }while(current != 0xFF);
    }
    return found;
}

void log_clear(void){
    int i = 0;
    for(i=0; i<LOG_NUM_MAX; i++){
        LogLL[i].Prev = 0xFF;
        LogLL[i].Next = 0xFf;
    }
    LogHead = 0xFF;
    LogTail = 0xFF;
}

int log_find_empty(void){
    int i = 0;
    int index = 0xFF;
    if (LogHead == 0xFF && LogTail == 0xFF){ // Log is empty.
        index = 0;
    }else{
        for(i=0; i<LOG_NUM_MAX; i++){
            if (LogLL[i].Prev == 0xFF && LogLL[i].Next == 0xFF){ // Empty found!
                index = i;
                break;
            }
        }
    }
    return index;
}



int main(int argc, char** argv) {
    bool   exit        = false;
	char   input       = 0;
	int    userIndex   = 0;
	uchar  month       = 0;
	uchar  day         = 0;
	uchar  hour        = 0;
	uchar  minute      = 0;

    log_ll_init();

	printf("Hello! This is a Log with linked list demo.\n");
	printf("q: quit, a: add, r: remove, c: clear, d: dump\n");
	while(!exit) {
		if(scanf("%c",&input) == 1) {
		    
		    switch(input)
		    {
            case 'a':
                printf("Log Add\n");
                printf("User Index: ");
                if (scanf("%d", &userIndex) != 1){ printf("\nError!"); }
                printf("Month:      ");
                if (scanf("%d", &month)     != 1){ printf("\nError!"); }
                printf("Day:        ");
                if (scanf("%d", &day)       != 1){ printf("\nError!"); }
                printf("Hour:       ");
                if (scanf("%d", &hour)      != 1){ printf("\nError!"); }
                printf("Minute:     ");
                if (scanf("%d", &minute)    != 1){ printf("\nError!"); }
                log_add(userIndex, month, day, hour, minute);
                break;
	        case 'r':
	            printf("Log Remove\nPlease Input User Index: ");
	            if (scanf("%d", &userIndex) == 1){
	                if (log_remove_user_index(userIndex)){
	                    printf("Success\n");
	                }else{
	                    printf("Fail\n");
	                }
	            }
	            break;
	        case 'c':
	            printf("Log Clear\n");
	            log_clear();
	            break;
	        case 'd':
	            log_dump();
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
