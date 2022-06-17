//構造体

#include <stdio.h>
#include <string.h>

// struct student{
//     int id;
//     char name[256];
//     int age;
// };

// typedef struct student student_data;

typedef struct{
    int id;
    char name[256];
    int age;
}student_data;

void setData(student_data*, int, char*, int);
void showData(student_data*);

void main(){

    // int i;
    // student_data data[] = {
    //     {1,"山田太郎",18},
    //     {2,"佐藤良子",19},
    //     {3,"太田涼",18},
    //     {4,"中田優子",18}
    // };

    // //データの内訳を表示
    // for(i=0; i<4; i++){
    //     printf("学生番号：%d 名前：%s 年齢：%d\n", data[i].id, data[i].name, data[i].age);
    // }

    student_data data[4];
    int i;
    int id[] = {1,2,3,4};
    char name[][256] = {"山田太郎", "佐藤良子", "太田流", "中田優子"};
    int age[] = {18,19,18,18};

    for(i=0;i<4;i++){
        setData(&data[i],id[i],name[i],age[i]);
    }

    for(i=0;i<4;i++){
        showData(&data[i]);
    }

 


}

void setData(student_data* data, int id, char* name, int age){
    //dataがポインタ型なのでアロー演算子
    data -> id = id;
    strcpy(data->name, name);
    data -> age = age;

}

void showData(student_data* data){
    printf("学生番号:%d 名前：%s 年齢：%d\n", data->id, data->name,data->age);
}