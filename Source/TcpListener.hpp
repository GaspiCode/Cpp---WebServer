#include <iostream>
#include <memory>
#include <WS2tcpip.h>
#include <string>
#include "Exception.cpp"
#define M_SOCKET_ERROR(code) SocketException(__FILE__,__LINE__).SocketError(code)

class TcpListener
{
public:
   class SocketException : public Exception
   {
        using Exception::Exception;
        public:
            std::string SocketError(int code) noexcept;
    };
    TcpListener(const char *ipAddress, int port);
    ~TcpListener();
    int Init();
    int Run();

private:
    
    void OnClientConnected(int clientSocket);
    void OnClientDisconnected(int clientSocket);
    void OnMessageReceived(int clientSocket, const char *msg, int length);
    void SendToClient(int clientSocket, const char *msg, int length);
    void BroadcastToClients(int sendingClient, const char *msg, int length);

private:
    const char * m_IpAddress;
    int m_Port;
    int m_Socket;
    fd_set m_Descriptor;
};
