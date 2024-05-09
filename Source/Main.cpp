#include "TcpListener.cpp"

int main(){
    std::unique_ptr<TcpListener> pTcpListener(new TcpListener("192.168.1.1",8080));
    
    pTcpListener->Init();



    return 0;
}
