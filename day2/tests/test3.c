#include <stdio.h>

unsigned int hexToUInt(const char*);

int main(){
    char ipheader[] = "\x45\x00\x00\x28\x92\x66\x40\x00\x80\x06\x00\x00\xc0\xa8\xfe\xbc\x36\x96\x46\x2e";
    int bin = hexToUInt(ipheader);
    printf("%d",bin);


}

unsigned int hexToUInt(const char *ptr)
{
    printf("%c",*ptr);
    unsigned int val = 0;
    unsigned int v;
    char ch;
    while( (ch = *ptr++) != '\0' ) {
        printf("%c",ch);
        if( ch >= '0' && ch <= '9' )
            v = ch - '0';
        else if( ch >= 'A' && ch <= 'F' )
            v = ch - 'A' + 10;
        else if( ch >= 'a' && ch <= 'f' )
            v = ch - 'a' + 10;
        else
            continue;    // 16進数文字ではない場合
        val = val * 16 + v;
        printf("%c",ch);
    }
    return val;
}