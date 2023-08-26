#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <locale>

using namespace std;

string get_Website(const char *url );

int main (int argc,char** argv)
{
    if(argc > 2)
        return -1;

    string url = "www.google.com";

    if(argc == 2)
        url = argv[1];

    cout << get_Website(url.c_str());

    return 0;
}

//***************************
string get_Website(const char *url )
{
    WSADATA wsaData;
    SOCKET Socket;
    SOCKADDR_IN SockAddr;


    int lineCount=0;
    int rowCount=0;

    string website_HTML;

    struct hostent *host;
    char *get_http= new char[256];

        memset(get_http,' ', sizeof(get_http) );
        strcpy(get_http,"GET / HTTP/1.1\r\nHost: ");
        strcat(get_http,url);
        strcat(get_http,"\r\nConnection: close\r\n\r\n");

        if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
        {
            cout << "WSAStartup failed.\n";
            system("pause");
            //return 1;
        }

        Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        host = gethostbyname(url);

        if(host == NULL)
            return "host resolution Failed";

        SockAddr.sin_port=htons(80);
        SockAddr.sin_family=AF_INET;
        SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

        cout << "Connecting to "<< url<<" ...\n";

        if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr)) != 0)
        {
            cout << "Could not connect";
            system("pause");
            //return 1;
        }

        cout << "Connected.\n";
        send(Socket,get_http, strlen(get_http),0 );

        char buffer[10000];

        int nDataLength;
            while ((nDataLength = recv(Socket,buffer,10000,0)) > 0)
            {
                int i = 0;

                while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r')
                {
                    website_HTML+=buffer[i];
                    i += 1;
                }
            }
        closesocket(Socket);
        WSACleanup();

            delete[] get_http;

    locale local;

    for (size_t i=0; i<website_HTML.length(); ++i)
    website_HTML[i]= tolower(website_HTML[i],local);

    return website_HTML + "\n\n";
}
