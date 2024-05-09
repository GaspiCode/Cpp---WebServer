#include "TcpListener.hpp"


#pragma comment(lib, "ws2_32.lib")

TcpListener::TcpListener(const char *ipAddress, int port)
    : m_IpAddress(ipAddress),
      m_Port(port)
{
}

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
       throw M_SOCKET_ERROR(WSAGetLastError());
    }

    // Crear Socket:
    // AF_INET = ipv4,
    // SOCK_STREAM = socket para flujo full duplex
    // el protocolo tcp en realidad es 6, pero segun la interred el unico que soporta AF_INET es 0
    m_Socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_Socket == INVALID_SOCKET)
    {
        throw M_SOCKET_ERROR(WSAGetLastError());
    }

    // Struct para direccion de socket ipv4
    // htons: convierte datos en formatos de red
    sockaddr_in socketInstance;
    socketInstance.sin_family = AF_INET;
    socketInstance.sin_port = htons(m_Port);

    // inet_pton: convierte direcciones ip en binario
    // lo que estoy haciendo aca es convertir la string m_ipaddress en un valor lagible para la struct
    // sockaddr_in, necesito esta struct para bindear la direccion ip y el puerto al socket
    // muchos en stack overflow recomiendan usar INADDR_ANY para que el sistema operativo se encarge
    // de asignarme la ip, de esta manera en vez de usar inet_pton quedaria asi:
    //socketInstance.sin_addr.S_un.S_addr = INADDR_ANY

    // datazo: pton significa pointer to a string to number
    inet_pton(AF_INET, m_IpAddress, &socketInstance.sin_addr);

    // Intentar asociar socketInstance a Socket
    if (bind(m_Socket, (sockaddr *)&socketInstance, sizeof(socketInstance)) == SOCKET_ERROR)
    {
        throw M_SOCKET_ERROR(WSAGetLastError());
    }

    if (listen(m_Socket, SOMAXCONN) == SOCKET_ERROR)
    {
        throw M_SOCKET_ERROR(WSAGetLastError());
    }

    // Crear descriptor
    FD_ZERO(&m_Descriptor);

    // Agregar listening socket
    FD_SET(m_Socket, &m_Descriptor);

    return 0;
}

int TcpListener::Run()
{
    bool run = true;

    while (run)
    {
        // es necesario hacer una copia del descriptor:
        // select solo devuelve los sockets que estan interactuando en exactamente
        // ese momento con el server, si no los destruye
        fd_set copy = m_Descriptor;

        // MDSN: La función select se usa para determinar el estado de uno o varios sockets.
        int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

        for (int i = 0; i < socketCount; i++)
        {
            // itero el array de sockets activos
            SOCKET sock = copy.fd_array[i];
            // veo si el socket activo es el listener? osea aver si alguien se
            // esta comunicando con el server
            if (sock == m_Socket)
            {
                // acepto la conexion
                SOCKET client = accept(m_Socket, nullptr, nullptr);
                // agrego la conexion a la lista de clientes conectados
                FD_SET(client, &m_Descriptor);
                OnClientConnected(client);
            }
            // en caso de que no sea una solicitud de conexion es un mensaje entrante
            else
            {
                // me declaro un buffer y lo zereo todo (literal)
                char buffer[4096];
                ZeroMemory(buffer, 4096);

                // recibo el mensaje
                int bytesIn = recv(sock, buffer, 4096, 0);
                // si esta vacio lo desconecto
                if (bytesIn <= 0)
                {
                    OnClientDisconnected(sock);
                    closesocket(sock);
                    FD_CLR(sock, &m_Descriptor);
                }
                // si tiene contenido lo proceso
                else
                {
                    OnMessageReceived(sock, buffer, bytesIn);
                }
            }
        }
    }
    // remuevo el socket de listening del master descriptor y lo cierro
    FD_CLR(m_Socket, &m_Descriptor);
    closesocket(m_Socket);
    // hago lo mismo para los sockets de los clientes
    while (m_Descriptor.fd_count > 0)
    {

        SOCKET sock = m_Descriptor.fd_array[0];

        FD_CLR(sock, &m_Descriptor);
        closesocket(sock);
    }
    // libero el winsock
    WSACleanup();
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

std::string TcpListener::SocketException::SocketError(int code) noexcept
{
    std::string localErr = "Error al formatear el mensaje de error";
    LPWSTR buffer = nullptr;
    DWORD formatResult = FormatMessageW(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        code,
        MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
        reinterpret_cast<LPWSTR>(&buffer),
        0,
        nullptr);
    if (formatResult == 0)
    {
        ErrorMsg(localErr);
        return localErr;
    }
    std::wstring s = buffer;
    LocalFree(buffer);
    std::string out(s.begin(), s.end());
    ErrorMsg(out, code);
    return out;
}