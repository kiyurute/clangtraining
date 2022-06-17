#ifndef _STUDENT_DATABASE_H_
#define _STUDENT_DATABASE_H_

#define MAX_STUDENT 10

#define LENGTH 50

enum ERROR {
    MESSAGE_OK,
    MESSAGE_ERROR
};

//学生のデータ
typedef struct {
    int id;
    char name[LENGTH];
}student;

student student_database[MAX_STUDENT];

//データーベースの初期化
void initDatabase();
//データーベースへのデータ登録
int add(int, char*);
//学生データの取得
student* get(int);

#endif // _STUDENT_DATABASE_H_