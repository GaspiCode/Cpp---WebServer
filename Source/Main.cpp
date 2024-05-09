#include "TcpListener.cpp"

int main(){
    std::unique_ptr<TcpListener> pTcpListener(new TcpListener("0.0.0.0",8080));
    
    pTcpListener->Init();

    //pTcpListener->Run();



    return 0;
}
