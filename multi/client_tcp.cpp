#include <bits/stdc++.h>
#include "funcs.hpp"

using namespace std;

int main(int argc, char **argv){
    int sock; 

    if(argc != 3){
        cout << "~~Wrong arguments: ip, port" << endl;
        exit(1);
    }
    
    if(!(sock = create_tcp_socket())){
        exit(1);
    }

    if(!(bind(sock))){
        exit(1);
    }


    int port = atoi(argv[2]);
    char* hostinfo = argv[1];
    struct sockaddr_in addr;
    
    addr.sin_family = AF_INET; 
	addr.sin_port = htons(port); 
    //addr.sin_addr.s_addr = inet_addr(hostinfo);
    if(inet_aton(hostinfo, &addr.sin_addr) == 0){
        cerr << "Invalid IP address" << endl;
    }
	
	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){
		perror("~~Подключение");
		exit(2);
    }
    
    cout << "~~Подключение к серверу прошло успешно" << endl;

    char buffer[1024];
    cout << "\n~~Введите сообщение: ";
    cin >> buffer;

    send(sock, buffer, strlen(buffer), 0);

    close(sock);
}
