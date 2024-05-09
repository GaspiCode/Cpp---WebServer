#include "TcpListener.hpp"
#include "Exception.cpp"

#pragma comment(lib, "ws2_32.lib")

TcpListener::TcpListener(const char *ipAddress, int port) 
    : 
    m_IpAddress(ipAddress),
    m_Port(port)
    {}

TcpListener::~TcpListener()
{
    closesocket(m_Socket);
    WSACleanup();
    exit(0);
}

int TcpListener::Init()
{

    // Inicializar variables de version de Windows Sockets
    WSADATA wsData;
    // makeword me estaria haciendo un binario de 16 bits, traduciendo cada argumento en cada octeto
    WORD version = MAKEWORD(2, 2);

    // Recuperar detalles de version de Windows Sockets, totalmente necesario en win antes de llamar a socket()
    int wsCheck = WSAStartup(version, &wsData);
    if (wsCheck != 0)
    {
        
        return wsCheck;
    }

    // Crear Socket:
    // AF_INET = ipv4,
    // SOCK_STREAM = socket para flujo full duplex
    // el protocolo tcp en realidad es 6, pero segun la interred el unico que soporta AF_INET es 0
    m_Socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_Socket == INVALID_SOCKET)
    {
        throw M_ERROR_COMMENT("Error de creacion del socket",WSAGetLastError());
    }

    // Struct para direccion de socket ipv4
    // htons: convierte datos en formatos de red
    sockaddr_in socketInstance;
    socketInstance.sin_family = AF_INET;
    socketInstance.sin_port = htons(m_Port);

    // inet_pton: convierte direcciones ip en binario
    inet_pton(AF_INET, m_IpAddress, &socketInstance.sin_addr);

    // Intentar asociar socketInstance a Socket
    if (bind(m_Socket, (sockaddr *)&socketInstance, sizeof(socketInstance)) == SOCKET_ERROR)
    {
        throw M_ERROR_COMMENT("Error al enlazar socketInstance con m_Socket",WSAGetLastError());
    }

    // Crear descriptor
    FD_ZERO(&m_Descriptor);

    // Agregar listening socket
    FD_SET(m_Socket, &m_Descriptor);

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
