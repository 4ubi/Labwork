#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>

int main() {
  int Sock, len, i, j, k, len1, fl = 0;
  struct sockaddr_in addr, addr1;
  char *p, buf2[100], buf[1024], c='z', ip[20], buf1[64], msg1[1024], m1[20], m2[20], m3[20];
  int bytes_read;
  Sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (Sock < 0) {
    perror("~~Сокет не был создан!");
    exit(0);
  }
  addr.sin_family = AF_INET;
  addr.sin_port = 0;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(Sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("~~Не удалось идентифицировать сокет!");
    close(Sock);
    exit(0);
  }
  len = sizeof(addr);
  if (getsockname(Sock, (struct sockaddr *)&addr, &len) < 0) {
    perror("~~Сервер не нашел свободный порт!");
    close(Sock);
    exit(0);
  }
  printf("~~Сервер нашел порт: - %d\n\n", ntohs(addr.sin_port));
  len1 = sizeof(addr1);
    while(1) {
    bytes_read = recvfrom(Sock, buf, 1024, 0,(struct sockaddr *)&addr1, &len1);
    buf[bytes_read] = '\0';
    printf("Сообщение от клиента: ");
    puts(buf);
    bytes_read = recvfrom(Sock, msg1, 1024, 0,(struct sockaddr *)&addr1, &len1);
    msg1[bytes_read] = '\0';
    for (i = 0; msg1[i] != ' '; i++)
      m1[i] = msg1[i];
    m1[i] = '\0';
    for (++i, j = 0; msg1[i] != ' '; i++, j++)
      m2[j] = msg1[i];
    m2[j] = '\0';
    for (++i, j = 0; msg1[i] != '\0'; i++, j++)
      m3[j] = msg1[i];
    m3[j] = '\0';
    p = strstr(buf,m1);
    if (p == NULL) {
      printf("~~Потерян 1-й пакет!!!\n");
      printf("~~Выполняется переотправка сообщения для получения недостающего пакета.\n");
      if (sendto(Sock, m1, sizeof(m1), 0, (struct sockaddr *)&addr1, sizeof(addr1))<0) {
          perror("~~Датаграмма не передана.");
          close(Sock);
          exit(0);
      }
      else
          printf("~~Датаграмма передана.\n");
      bytes_read = recvfrom(Sock, buf2, 100, 0,(struct sockaddr *)&addr1, &len1);
      buf2[bytes_read] = '\0';
      printf("Потерянный пакет: ");
      puts(buf2);
      printf("\n");
    }
    p = strstr(buf,m2);
    if (p == NULL) {
      printf("~~Потерян 2-й пакет!!!\n");
      printf("~~Выполняется переотправка сообщения для получения недостающего пакета.\n");
      if (sendto(Sock, m2, sizeof(m2), 0, (struct sockaddr *)&addr1, sizeof(addr1))<0) {
        perror("~~Датаграмма не передана");
        close(Sock);
        exit(0);
      }
      else
      printf("~~Датаграмма передана\n");
      bytes_read = recvfrom(Sock, buf2, 100, 0,(struct sockaddr *)&addr1, &len1);
      buf2[bytes_read] = '\0';
      printf("Потерянный пакет: ");
      puts(buf2);
      printf("\n");
    }
    p = strstr(buf,m3);
    if (p == NULL) {
      printf("~~Потерян 3-й пакет!!!\n");
      printf("~~Выполняется переотправка сообщения для получения недостающего пакета.\n");
      if (sendto(Sock, m3, sizeof(m3), 0, (struct sockaddr *)&addr1, sizeof(addr1))<0) {
        perror("~~Датаграмма не передана");
        close(Sock);
        exit(0);
      }
      else
        printf("~~Датаграмма передана\n");
      bytes_read = recvfrom(Sock, buf2, 100, 0,(struct sockaddr *)&addr1, &len1);
      buf2[bytes_read] = '\0';
      printf("Потерянный пакет: ");
      puts(buf2);
      printf("\n");
    }
    if (recvfrom(Sock, buf2, 100,0, (struct sockaddr *)&addr1, &len1) == 0) {
      printf("\n~~Соединение завершено. Клиент отключен.");
      break;
    }
  }
  close(Sock);
  return 0;
}
