#include <iostream>
#include <string>
#include <sstream>

#define M_ERROR(msg) Exception(__FILE__,__LINE__).ErrorMsg(msg)
#define M_ERROR_COMMENT(firstMsg, secMsg) Exception(__FILE__,__LINE__).Exception::ErrorMsg(firstMsg, secMsg)

class Exception
{
    public:
        Exception(const char * file, int line) noexcept;
        std::string ErrorMsg(int code) noexcept;
        std::string ErrorMsg(std::string msg) noexcept;
        std::string ErrorMsg(std::string msg, std::string realMsg) noexcept;
        std::string ErrorMsg(std::string msg, int code) noexcept;
    private:
        std::string GetOriginString() noexcept;
        const char * GetFile() noexcept;
        int GetLine() noexcept;
        void OutputMsg(std::string msg) noexcept;
    private:
        const char * m_File;
        int m_Line;
};
