#include <stdio.h>
#include "studentDatabase.h"
#include "dataOutput.h"

void main(){
    int i;
    char names[][LENGTH] = {"碇シンジ", "綾波レイ", "式波アスカ", "巻波・マリ・イラストリアス"};
    int ids[] = {1,2,2,3};
    initDatabase();
    for(i=0; i<4; i++){          //データの登録
        add(ids[i], names[i]);
        printf("登録：%d %s\n", ids[i], names[i]);
        showError();
    }
    for (i = 0; i < 3; i++){      //データの登録
        showStudentData(get(i+1));
    }

}