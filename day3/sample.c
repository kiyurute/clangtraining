#include <stdio.h>

/**
 *
 */
void dump(const char *msg, const void *buff, unsigned int length)
{
  char ascii[17];
  size_t i, j;

  printf("=== %s ===\n", msg);
  ascii[16] = '\0';
  for (i = 0; i < length; ++i) {
    if ((i % 16) == 0) {
      printf("%016llX| ", (unsigned long long)(buff + i));
    }
    printf("%02X ", ((unsigned char*)buff)[i]);
    if (((unsigned char*)buff)[i] >= ' ' && ((unsigned char*)buff)[i] <= '~') {
      ascii[i % 16] = ((unsigned char*)buff)[i];
    } else {
      ascii[i % 16] = '.';
    }
    if (((i + 1) % 8) == 0 || (i + 1) == length) {
      printf(" ");
      if (((i + 1) % 16) == 0) {
        printf("|  %s \n", ascii);
      } else if ((i + 1) == length) {
        ascii[(i + 1) % 16] = '\0';
        if (((i + 1) % 16) <= 8) {
          printf(" ");
        }
        for (j = (i + 1) % 16; j < 16; ++j) {
          printf("   ");
        }
        printf("|  %s \n", ascii);
      }
    }
  }
  printf("\n");
}

void sub(const char *arg)
{
  char x0[] = "xyz";
  unsigned int u0[] = { 1, 2, 3 };

  dump("sub: const char *arg length=10", &arg, 10);
  dump("sub: char x0[] = \"xyz\"; length=10", x0, 10);
  dump("sub: unsigned int u0[] = { 1, 2, 3 }; length=20", u0, 20);

  dump("sub: stack length=300", &arg, 300);
}

/**
 *
 */
int main(void)
{
  char a0[] = "ABCDEF";
  char a1[10] = "abcdef";
  char a2[] = { 'Z', 'Y', 'X', 'W', 'V', 'U' };
  char a3[10] = { 'z', 'y', 'x', 'w', 'v', 'u' };
  char a4[] = { '1', '2', '3', '4', '5', '6', '\0' };
  char a5[10] = { '1', '2', '3', '4', '5', '6', '\0' };
  int i0[] = { 101, 201, 301, 401 };
  int i1[10] = { 100, 200, 300, 400 };
  char *pa = a0;

  dump("main: char a0[] = \"ABCDEF\"; length=10", a0, 10);
  dump("main: char a1[10] = \"abcdef\"; length=10", a1, 10);
  dump("main: char a2[] = { 'Z', 'Y', 'X', 'W', 'V', 'U' }; length=10", a2, 10);
  dump("main: char a3[10] = { 'z', 'y', 'x', 'w', 'v', 'u' }; length=10", a3, 10);
  dump("main: char a4[] = { '1', '2', '3', '4', '5', '6', '\\0' }; length=10", a4, 10);
  dump("main: char a5[10] = { '1', '2', '3', '4', '5', '6', '\\0' }; length=10", a5, 10);
  dump("main: int i0[] = { 101, 201, 301, 401 }; length=40", i0, 40);
  dump("main: int i1[10] = { 100, 200, 300, 400 }; length=40", i1, 40);
  dump("main: char *pa = a0; length=10", &pa, 10);

  sub(a1);

  return 0;
}

/* vim: se nu ts=2 sw=2 si et : */