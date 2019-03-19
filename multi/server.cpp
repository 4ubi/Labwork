#include <bits/stdc++.h>
#include "funcs.hpp"

using namespace std;

int main() {

    int t_sock = create_tcp_socket();
    int u_sock = create_udp_socket();

    int port = bind(t_sock);

    struct sockaddr_in addr_udp;
    addr_udp.sin_family = AF_INET;
    addr_udp.sin_port =  htons(port);
    addr_udp.sin_addr.s_addr = htonl(INADDR_ANY);
        
    if (bind(u_sock, (struct sockaddr*)&addr_udp, sizeof(addr_udp)) < 0) {
        cout << "~~error!" << endl;
        close(u_sock);
        close(t_sock);
        return -1;
    }

    listen(t_sock,1);

    int c_sock;

    fd_set rfds, temp_rfds;

    int nfds = max(t_sock, u_sock) + 1;
    FD_ZERO(&rfds);

    FD_SET(t_sock,&rfds);
    FD_SET(u_sock,&rfds);

    for(;;) {
        temp_rfds = rfds;
        select(nfds,&temp_rfds,NULL,NULL,NULL);

        if(FD_ISSET(t_sock,&temp_rfds)) {
            c_sock = accept(t_sock,0,0);
            FD_SET(c_sock, &rfds);
            if(nfds <= c_sock)
                nfds = c_sock + 1;
        }

        if(FD_ISSET(u_sock,&temp_rfds)) {
            char buffer[1024];
            recvfrom(u_sock,buffer,1024,0,0,0);
            cout <<"UDP: "<< buffer << endl;
        }

        for(int fd=0; fd < nfds; fd++) {
            if(fd != u_sock && fd != t_sock && FD_ISSET(fd,&temp_rfds)) {
                char buffer[1024];
                int check = recv(fd, buffer, 1024, 0);
                if(check <= 0) {
                    FD_CLR(fd, &rfds);
                    continue;
                }
                cout <<"TCP: "<< buffer << endl;
            }
        }
    }

}
