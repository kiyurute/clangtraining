  #include <stdio.h>
  #include <unistd.h>
  int main()
  {
          while(1)
          {
                  fprintf(stdout,"hello-out");
                  fprintf(stderr,"hello-err");
                  sleep(1);
          }
          return 0;
  }

  //fprintfはファイルへの書き込みだからファイルを読み込まないと実行されない？stderrはエラーメッセージだからコンソール出力される？