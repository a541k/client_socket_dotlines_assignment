
//client
#include<iostream>
#include<winsock2.h>
#include "lib/data_struct.hpp"

using namespace std;

Data user1 = {77, "ashik", "mahmud", "ashik@test.com", "2014-05-28 11:30:10", "2014-05-29 12:30:10", 12};

const int PORT = 2222;

int main(){
    cout<<"client socket"<<endl;

    //  SOCKET CREATION--------

    //wsadata init
    WSAData wsData;
    if(WSAStartup(MAKEWORD(2, 2), &wsData) != 0){
        cout<<"wsa startup failed"<<endl;
        return 0;
    }
    //socket
    int client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(client_socket == SOCKET_ERROR){
        cout<<"socket creation failed"<<endl;
        WSACleanup();
        return 0;
    }
    cout<<"clent socket created"<<endl;


    //where to send data
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");//localhost

    //if(bind(client_socket, (sockaddr_in*)&client_address, sizeof(client_address)))
    //no need to bind in udp client socket, os assigns a random port


    //char msg[] = "hello there..";
    char buffer[sizeof(user1)];
    memcpy(buffer, &user1, sizeof(user1));

    int bytes_sent = sendto(client_socket, buffer, sizeof(buffer), 0, (sockaddr*) &server_address, sizeof(server_address));

    if(bytes_sent == SOCKET_ERROR){
        cout<<"error sending data"<<endl;
        closesocket(client_socket);
        WSACleanup();
        return 0;
    }
    else{
        cout<<"data sent to server successfully"<<endl;
    }


    closesocket(client_socket);
    WSACleanup();
    return 0;
}
