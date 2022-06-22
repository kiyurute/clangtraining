#include <stdint.h>
#include <stdio.h>

struct memory_alignment {
  uint32_t first;  //4バイト
  uint16_t second; //2バイト
  uint64_t third;  //8バイト 
  uint8_t fourth;  //1バイト
  char text;       //<-文字挿入
  uint32_t fifth;  //4バイト
};

int main(){

    struct memory_alignment ma = {
            1,2,3,4,'a',5,
    };

    printf("size:%lu\n",sizeof(char));
    printf("address:%p val:%c size:%lu\n",(&ma.first),(char)ma.first,sizeof(ma.first));
    printf("address:%p val:%d size:%lu\n",(&ma.second),ma.second,sizeof(ma.second));
    printf("address:%p val:%d size:%lu\n",(&ma.third),ma.third,sizeof(ma.third));
    printf("address:%p val:%d size:%lu\n",(&ma.fourth),ma.fourth,sizeof(ma.fourth));
    printf("address:%p val:%c size:%lu\n",(&ma.text),ma.text,sizeof(ma.text));
    printf("address:%p val:%d size:%lu\n",(&ma.fifth),ma.fifth,sizeof(ma.fifth));
    
}