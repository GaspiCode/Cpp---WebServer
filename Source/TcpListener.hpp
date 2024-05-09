#include <iostream>
#include <memory>
#include <WS2tcpip.h>
#include <string>

class TcpListener
{
public:
    TcpListener(const char *ipAddress, int port);
    ~TcpListener();
    int Init();
    int Run();
    int Stop();

private:
    void OnClientConnected(int clientSocket);
    void OnClientDisconnected(int clientSocket);
    void OnMessageReceived(int clientSocket, const char *msg, int length);
    void SendToClient(int clientSocket, const char *msg, int length);
    void BroadcastToClients(int sendingClient, const char *msg, int length);

private:
    const char *m_IpAddress;
    int m_Port;
    int m_Socket;
    fd_set m_Descriptor;
};
