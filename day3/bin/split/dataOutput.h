#ifndef _DATA_OUTPUT_H_
#define _DATA_OUTPUT_H_

#include "studentDatabase.h"

//学生データの表示
void showStudentData(student*);
//エラーの表示
void showError();

int Error;

//学生データの表示
void showStudentData(student* data){

    if(data != NULL) {
        printf("学生番号：%d 名前：%s\n", data->id, data->name);
    }
    else{
        printf("データが登録されていません \n");
    }

}

//エラーの表示
void showError(){
    switch (Error){
    case MESSAGE_OK:
        printf("OK!\n");
        break;
    case MESSAGE_ERROR:
        printf("ERROR!\n");
        break;
    }
}

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

//データーベースへの登録
int add(int id, char* name){

    if(get(id) == NULL && num < MAX_STUDENT){ //dbにidがなければ登録する。
        student_database[num].id = id;
        strcpy(student_database[num].name, name);
        num++;
        Error = MESSAGE_OK;
        return 1;
    }

    Error = MESSAGE_ERROR;

    return 0;
}

//学生データの取得
student* get(int id){
    int i;
    for(i = 0; i< num; i++){
        if(student_database[i].id == id){
            return &student_database[i]; //該当するidがあればstudent型を返す
        }
    }
    return NULL;
}


#endif