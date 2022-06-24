#include <stdio.h>
#include <netdb.h>
#include <unistd.h>

/**
 *
 */
int connect_server(const char *host, const char *port)
{
  struct addrinfo hints = { 0 };
  struct addrinfo *res = NULL;
  int sock = -1;
  int err;

  hints.ai_socktype = SOCK_STREAM;
  err = getaddrinfo("127.0.0.1", "12345", &hints, &res);
  if (err != 0) {
    printf("getaddrinfo: failed: %s\n", gai_strerror(err));
    return -1;
  }

  sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (sock < 0) {
    perror("socket");
    return -1;
  }

  err = connect(sock, res->ai_addr, res->ai_addrlen);
  if (err != 0) {
    perror("connect");
    return -1;
  }

  freeaddrinfo(res);

  return sock;
}

/**
 *
 */
int main(int argc, char* argv[])
{
  char buff[1024] = { 0 };
  int sock = -1;
  int err;

  sock = connect_server("127.0.0.1", "12345");
  if (sock < 0) {
    return 1;
  }

  if (argc > 1) {
    err = sprintf(buff, "send buffer: %s", argv[1]);
  }
  else {
    err = sprintf(buff, "send buffer: no args");
  }
  err = send(sock, buff, err, 0);
  if (err < 0) {
    perror("send");
    return 1;
  }

  err = recv(sock, buff, sizeof(buff), 0);
  if (err < 0) {
    perror("recv");
    return 1;
  }
  printf("%.*s\n", err, buff);

  close(sock);

  return 0;
}

/* vim: se nu ts=2 sw=2 si et : */