#include "TcpListener.cpp"


int main(){
    std::unique_ptr<Tcp::TcpListener> pTcpListener(new Tcp::TcpListener("192.168.1.1",8080));
    
    pTcpListener->Init();

    return 0;
}
