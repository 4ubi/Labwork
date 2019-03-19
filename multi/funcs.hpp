#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <fstream>
#include <ios>
#include <cmath>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

#define SIZE 1000

using namespace std;

int create_tcp_socket(){
    int sock;

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cerr << "\n~~Сокет не создался!" << endl;
        perror(NULL);
        return 0;
    }

    return sock;
}

int create_udp_socket(){
    int sock;

    if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        cerr << "\n~~Сокет не создался!" << endl;
        perror(NULL);
        return 0;
    }

    return sock;
}

int bind(int sock){
    struct sockaddr_in sock_addr;
    socklen_t sock_len = sizeof(sock_addr);

    bzero(&sock_addr, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(0);
    sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sock, (struct sockaddr*)&sock_addr, sock_len) < 0) {
        cerr << "\n~~bind не сработал!" << endl;
        perror(NULL);
        return 0;
    }

    if (getsockname(sock, (struct sockaddr *)&sock_addr, &sock_len) < 0){
        cerr << "\n~~getsockname wrong!" << endl;
        perror(NULL);
        return 0;
    }
    cout << "\n~~Используется порт: " << ntohs(sock_addr.sin_port) << endl;

    return ntohs(sock_addr.sin_port);
}

int bind(int t_sock, int u_sock){
    struct sockaddr_in sock_addr;
    socklen_t sock_len = sizeof(sock_addr);

    bzero(&sock_addr, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(0);
    sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(t_sock, (struct sockaddr*)&sock_addr, sock_len) < 0) {
        cerr << "\n~~bind не сработал!" << endl;
        perror(NULL);
        return 0;
    }

    if (getsockname(u_sock, (struct sockaddr *)&sock_addr, &sock_len) < 0){
        cerr << "\n~~getsockname wrong!" << endl;
        perror(NULL);
        return 0;
    }
    cout << "\n~~Используется порт: " << ntohs(sock_addr.sin_port) << endl;
/*
    struct sockaddr_in sock_addr_udp;
    bzero(&sock_addr_udp, sizeof(sock_addr_udp));
    sock_addr_udp.sin_family = AF_INET;
    sock_addr_udp.sin_port = sock_addr.sin_port;
    sock_addr_udp.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(u_sock, (struct sockaddr*)&sock_addr_udp, sock_len) < 0) {
        cerr << "bind не сработал!" << endl;
        perror(NULL);
        return 0;
    }
*/
    return 1;
}

struct sockaddr_in prepare_serv_addr(char* address, int port) {
    struct sockaddr_in serv_addr;

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if(inet_aton(address, &serv_addr.sin_addr) == 0){
        cerr << "\n~~Invalid IP address" << endl;
    }

    return serv_addr;
}

long long len(ifstream& ifs) {
	ifs.seekg (0, ifs.end);
    int length = ifs.tellg();
    ifs.seekg (0, ifs.beg);
    return length;
}
