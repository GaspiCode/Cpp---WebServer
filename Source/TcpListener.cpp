#include "TcpListener.hpp"

#pragma comment(lib, "ws2_32.lib")

namespace Tcp
{
    TcpListener::TcpListener(const char *ipAddress, int port) : IpAddress(ipAddress), Port(port) {}

    int TcpListener::Init()
    {

        // Inicializar variables de version de Windows Sockets
        WSADATA wsData;
        WORD version = MAKEWORD(2, 2);

        // Recuperar detalles de version de Windows Sockets
        int wsCheck = WSAStartup(version, &wsData);
        if (wsCheck != 0)
        {
            return wsCheck;
        }

        // Crear Socket:
        // AF_INET = ipv4,
        // SOCK_STREAM = socket para flujo de datos
        // 6 = protocolo tcp
        Socket = socket(AF_INET, SOCK_STREAM, 6);
        if (Socket == INVALID_SOCKET)
        {
            return WSAGetLastError();
        }

        // Struct para direccion de socket ipv4
        // htons: convierte datos en formatos de red
        sockaddr_in socketInstance;
        socketInstance.sin_family = AF_INET;
        socketInstance.sin_port = htons(Port);

        //inet_pton: convierte direcciones ip en binario
        inet_pton(AF_INET, IpAddress, &socketInstance.sin_addr);

        //Intentar asociar socketInstance a Socket
        if(bind(Socket,(sockaddr*)&socketInstance, sizeof(socketInstance)) == SOCKET_ERROR)
        {
            return WSAGetLastError();
        }

        //Crear descriptor
        FD_ZERO(&Descriptor);

        //Agregar listening socket
        FD_SET(Socket, &Descriptor);

        return 0;
    }

    int TcpListener::Run()
    {
          return 0;
    }
    int TcpListener::Stop()
    {
          return 0;
    }

    void TcpListener::OnClientConnected(int clientSocket)
    {
    }

    void TcpListener::OnClientDisconnected(int clientSocket)
    {
    }
    void TcpListener::OnMessageReceived(int clientSocket, const char *msg, int length)
    {
    }
    void TcpListener::SendToClient(int clientSocket, const char *msg, int length)
    {
    }
    void TcpListener::BroadcastToClients(int sendingClient, const char *msg, int length)
    {
    }

};