#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <stdlib.h>
#include <thread>
#include <iostream>

void printError(const char* const &err)
{
    MessageBox(NULL, err, "Error", MB_OK);
    exit(0);
}

void SendMsg(SOCKET ClientSocket)
{
    char Msg[200];
    while(true)
    {
        gets(Msg);

        send(ClientSocket, Msg, strlen(Msg), 0);
    }
}

void RecvMsg(SOCKET ClientSocket)
{
    char Msg[200];
    unsigned int MsgSize = sizeof(Msg)/sizeof(Msg[0]);
    while(true)
    {
        int RecvMsgSize = 0;
        RecvMsgSize = recv(ClientSocket, Msg, MsgSize, 0);
        if(RecvMsgSize <= 0)
            continue;

        Msg[RecvMsgSize] = '\0';
        std::cout << "Client: " << Msg << '\n';
    }
}

int main()
{
    WSADATA wsaData;

    if(WSAStartup( MAKEWORD(2,2), &wsaData) != 0)
        printError("WSAStartup() failed.");

    SOCKET ServerSocket;

    ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(ServerSocket == INVALID_SOCKET)
        printError("Failed to create Server Socket.");

    sockaddr_in address = { 0 };
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_family = AF_INET;
    address.sin_port = htons(8055);

    if(bind(ServerSocket, (sockaddr*)&address, sizeof(address)) < 0)
        printError("Failed to bind Server Socket.");

    if(listen(ServerSocket,3) < 0)
        printError("Failed to listen.");

    int addrlen = sizeof(address);
    SOCKET ClientSocket = accept(ServerSocket, (sockaddr*)&address, &addrlen);

    if(ClientSocket == INVALID_SOCKET)
        printError("Failed to grab client focus.");

    std::thread SendThread(SendMsg,ClientSocket);
    std::thread RecvThread(RecvMsg,ClientSocket);

    SendThread.join();
    RecvThread.join();

    closesocket(ServerSocket);
    WSACleanup();
    return 0;
}
