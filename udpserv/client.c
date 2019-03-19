#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
  int SockClient, i, j, k, port, len1, bytes_read;
  char ip[20], buf[64], buf1[64], msg1[1024], arr[100], m1[256], m2[256], m3[256];
  struct sockaddr_in addr,addr1;
  if (argc < 3) {
	   perror("~~ <ip> <port>");
	    exit(0);
  }
  printf("Введите датаграмму которую нужно отправить серверу: ");
  gets(msg1);

  SockClient = socket(AF_INET, SOCK_DGRAM, 0);

  if (SockClient < 0) {
    perror("~~Сокет не был создан!");
    exit(0);
  }
  port = atoi(argv[2]);
  char* hostinfo = argv[1];
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(hostinfo);
  addr.sin_port = htons(port);
  printf("\n~~Соединение через порт: %d \n",port);
  for (i = 0; msg1[i] != ' '; i++)
    m1[i] = msg1[i];
  m1[i] = '\0';
  printf("Первый пакет: %s\n",m1);
  for (++i, j = 0; msg1[i] != ' '; i++, j++)
    m2[j] = msg1[i];
  m2[j] = '\0';
  printf("Второй пакет: %s\n",m2);
  for (++i, j = 0; msg1[i] != '\0'; i++, j++)
    m3[j] = msg1[i];
  m3[j] = '\0';
  printf("Третий пакет: %s\n",m3);
  srand(time(NULL));
  k = rand()%3+1;
  if (k == 1) {
    for (j = 0; m2[j] != '\0'; j++)
      arr[j] = m2[j];
    arr[j] = ' ';
    for (++j, i = 0; m3[i] != '\0'; i++, j++)
      arr[j] = m3[i];

    arr[j] = '\0';
  }
  if (k == 2) {
    for (j = 0; m1[j] != '\0'; j++)
      arr[j] = m1[j];
    arr[j] = ' ';
    for (++j, i = 0; m3[i] != '\0'; i++, j++)
      arr[j] = m3[i];
    arr[j] = '\0';
  }
  if (k == 3) {
    for (j = 0; m1[j] != '\0'; j++)
      arr[j] = m1[j];
    arr[j] = ' ';
    for (++j, i = 0; m2[i] != '\0'; i++, j++)
      arr[j] = m2[i];
    arr[j] = '\0';
  }
  sendto(SockClient, arr, sizeof(arr),0,(struct sockaddr *)&addr, sizeof(addr));
  sendto(SockClient, msg1, sizeof(msg1),0,(struct sockaddr *)&addr, sizeof(addr));
  bytes_read = recv(SockClient, buf1, 30, 0);
  buf1[bytes_read] = '\0';
  if (sendto(SockClient, buf1, sizeof(buf1),0,(struct sockaddr *)&addr, sizeof(addr))<0) {
    perror("~~Датаграмма не переотправлена!");
    close(SockClient);
    exit(0);
  }
  printf("~~Датаграмма переотправлена.\n");
  close(SockClient);
  return 0;
}
