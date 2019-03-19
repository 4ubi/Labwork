#include <bits/stdc++.h>
#include "funcs.hpp"

using namespace std;


int main(int argc, char **argv){
    int sock;
    struct sockaddr_in serv_addr;

    if(argc != 3){
        cout << "Wrong arguments: ip, port" << endl;
        exit(1);
    }
    
    if(!(sock = create_udp_socket())){
        exit(1);
    }

    cout << "sock: " << sock << endl;

    if(!(bind(sock))){
        exit(1);
    }

    serv_addr = prepare_serv_addr(argv[1], atoi(argv[2]));

    char buffer[1024];
    cout << "Введите сообщение: ";
    cin >> buffer;
    
    int len = 
    sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    return 0;
}