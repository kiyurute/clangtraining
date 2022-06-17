//以下の構造体とその構造体の配列を使って、各教科の平均値を出力する関数を作成して。

#include <stdio.h>

typedef struct grades {
  int no;       /* 出席番号 */
  unsigned int japanese; /* 国語 */
  unsigned int math;     /* 数学 */
  unsigned int science;  /* 理科 */
  unsigned int social;   /* 社会 */
} grades_t;

void calc_average(const grades_t *data)
{
  /* ここに処理を書いてね */
  int i;

    //教科ごとの平均
    float js=0, ms=0, scs=0, sos=0;
    float ja, ma, sca, soa;

    //人ごとの平均
    int is[][2] = {};

    while (data[i].no != -1){
        printf("no:%d j:%d m:%d sc:%d so:%d\n", data[i].no, data[i].japanese, data[i].math, data[i].science, data[i].social);

        //人ごとの平均
        //is[i][0] = (float)data[i].no;
        // is[i][1] = (data[i].japanese + data[i].math + data[i].science + data[i].social) / 4;
        // printf("is:%f\n", "is:%f\n", is[i][0], is[i][1]);

        //教科ごとの和
        js += data[i].japanese;
        ms += data[i].math;
        scs += data[i].science;
        sos += data[i].social;

        printf("ms:%f\n", ms);

        i++;
    }

    ja = js / i;
    ma = ms / i;
    sca = scs / i;
    soa = sos / i;

    //教科ごとの平均
    printf("j:%f m:%f sc:%f so:%f\n", 
              ja,  ma,  sca,   soa);

    //人ごとの平均
    

  
}

int main(void)
{
  grades_t myclass[] = {
    { 1001, 85, 74, 63, 90 },
    { 1002, 78, 65, 70, 62 },
    { 1003, 89, 92, 88, 76 },
    { 1004, 32, 48, 66, 25 },
    { 1005, 92, 76, 81, 98 },
    {   -1,  0,  0,  0,  0 },
  };

  calc_average(myclass);

  return 0;
}