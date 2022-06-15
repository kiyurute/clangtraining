#include <stdio.h>


int main(void)
{
  const char ipheader[] = "\x46\x00\x00\x28\x92\x66\x40\x00\x80\x06\x00\x00\xc0\xa8\xfe\xbc\x36\x96\x46\x2e";
  unsigned int header_length = ipheader[0] & 0x0F;
  header_length <<= 2;
  printf("header length = %u\n", header_length);
  return 0;
}

/* vim: se nu ts=2 sw=2 si et : */