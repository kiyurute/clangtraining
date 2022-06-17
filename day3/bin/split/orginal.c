#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENT 10

#define LENGTH 50

#define MESSAGE_LENGTH 256

enum ERROR {
    MESSAGE_OK,
    MESSAGE_ERROR
};

typedef struct{
    int id;
    char name[LENGTH];
}student;

int num = 0;
student student_database[MAX_STUDENT];
int Error;
void initDatabase();
int add(int, char*);
student* get(int);
void showStudentData(student*);
void showError();

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







