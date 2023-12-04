
//client
#include<iostream>
#include<winsock2.h>
#include "lib/data_struct.hpp"
#include <string>

using namespace std;

Data user1 = {77, "ashik", "mahmud", "ashik@test.com", "2014-05-28 11:30:10", "2014-05-29 12:30:10", 12};

const int PORT = 2222;

void input_data(Data &user){
    cout<<endl<<"Enter User ID: ";
    cin>>user.user_id;
    cout<<endl<<"Enter First Name: ";
    cin>>user.first_name;
    cout<<endl<<"Enter Last Name: ";
    cin>>user.last_name;
    cout<<endl<<"Enter Email: ";
    cin>>user.email;
    cin.ignore();
    cout<<endl<<"Enter Subscription Time: ";
    cin.getline(user.subscription_time, 50);
    //cin>>user.subscription_time;
    cout<<endl<<"Enter Last Entry Time: ";
    cin.getline(user.last_entry_time, 50);
    cout<<endl<<"Enter View Time: ";
    cin>>user.view_time;
}

int main()
{

    try
    {
        cout<<"client socket"<<endl;

        //  SOCKET CREATION--------

        //wsadata init
        WSAData wsData;
        if(WSAStartup(MAKEWORD(2, 2), &wsData) != 0)
        {
            throw "wsa startup failed";
        }
        //socket
        int client_socket = socket(AF_INET, SOCK_DGRAM, 0);
        if(client_socket == SOCKET_ERROR)
        {
            WSACleanup();
            throw "socket creation failed";
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

        int testCase;
        cout<<"How Many Data Instance to Send: ";
        cin>>testCase;
        for(int i=0; i<testCase; i++){
                Data user;
                //take input
                input_data(user);

                //char buffer[sizeof(user1)];
                //memcpy(buffer, &user1, sizeof(user1));

                char buffer[sizeof(user)];
                memcpy(buffer, &user, sizeof(user));

                int bytes_sent = sendto(client_socket, buffer, sizeof(buffer), 0, (sockaddr*) &server_address, sizeof(server_address));

                if(bytes_sent == SOCKET_ERROR)
                {
                    closesocket(client_socket);
                    WSACleanup();
                    throw "socket error when sending data";
                }
                else
                {
                    cout<<"data sent to server"<<endl;
                }

            }


        closesocket(client_socket);
        WSACleanup();
    }
    catch(const char* errorMsg)
    {
        cout<<errorMsg<<endl;
    }

    return 0;
}
