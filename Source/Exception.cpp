#include "Exception.hpp"

Exception::Exception(const char *file, int line) noexcept 
    : m_File(file),
    m_Line(line)
{
}

std::string Exception::ErrorMsg(std::string msg) noexcept
{
    std::ostringstream oss;
    oss << std::endl << GetOriginString() 
        << "[Message]: " << msg << std::endl;
    OutputMsg(oss.str());

    // Tecnicamente, este retorno iria a parar al try-catch, pero como no estoy seguro de tener ganas o querer llamar
    // siempre a try, las imprimo en el flujo estandar por las dudas

    return oss.str();
}

std::string Exception::ErrorMsg(int code) noexcept
{
    std::ostringstream oss;
    oss << std::endl << GetOriginString() 
        << "[Code]: " << code << std::endl;
    OutputMsg(oss.str());

    return oss.str();
}
std::string Exception::ErrorMsg(std::string msg, std::string realMsg) noexcept
{
    std::ostringstream oss;
    oss << std::endl << GetOriginString() 
        << "[Message]:" << realMsg << std::endl
        << "[Comment]: " << msg << std::endl;

    OutputMsg(oss.str());
    return oss.str();
}

std::string Exception::ErrorMsg(std::string msg, int code) noexcept
{
    std::ostringstream oss;
    oss << std::endl << GetOriginString() 
        << "[Code]: " << code << std::endl
        << "[Comment]: " << msg << std::endl;

    OutputMsg(oss.str());
    return oss.str();
}

std::string Exception::GetOriginString() noexcept
{
    std::ostringstream oss;
    oss << "[Line]: " << GetLine() << std::endl << "[File]: " << GetFile() << std::endl;
    return oss.str();
}

void Exception::OutputMsg(std::string msg) noexcept
{
    std::cerr << msg << std::endl;
}

const char *Exception::GetFile() noexcept
{
    return m_File;
}

int Exception::GetLine() noexcept
{
    return m_Line;
}