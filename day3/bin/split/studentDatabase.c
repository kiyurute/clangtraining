#include "studentDatabase.h"
#include <string.h>

#define MESSAGE_LENGTH 256

int num = 0;

student student_database[MAX_STUDENT];

int Error = MESSAGE_OK;

//データーベースの初期化
void initDatabase(){
    int i;
    for(i = 0; i < MAX_STUDENT; i++){
        student_database[i].id = -1;
        strcpy(student_database[i].name, "");
    }

    Error = MESSAGE_OK;
    num = 0;
}

