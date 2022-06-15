#include <stdio.h>

/**
 *
 */
char *str_chr(const char *str, int c)
{
  while ((*str) != '\0') {
    if (c == (*str)) {
      return str;
    }
    str++;
  }
  return NULL;
}

/**
 *
 */
int main(void)
{
  char input_buff[256] = { 0 };
  char ch = 0;
  char *r = NULL;

  printf("検索する文字を入力してください: ");
  scanf("%c", &ch);
  printf("検索される文字列を入力してください: ");
  scanf("%s", input_buff);

  r = str_chr(input_buff, ch);

  printf("return value: %p\n", r);
  if (r != NULL) {
    printf("return value: %s\n", r);
  }

  return 0;
}

/* vim: se nu ts=2 sw=2 si et : */