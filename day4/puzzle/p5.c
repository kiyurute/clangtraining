#include <stdio.h>
#define f(a,b) a##b
#define g(a)   #a
#define h(a) g(a)
int main()
{
        printf("%s\n",h(f(1,2)));
        printf("%s\n",g(f(1,2)));
        return 0;
}


// このプログラムを見て、両方のprintfの出力は同じになると考える人がいるかもしれません。しかし、プログラムを走らせると、次の結果を取得します。
// bash$ ./a.out
// 12

// f(1,2)
// bash$

// なぜそうなるのでしょうか？