#pragma once
#include <Windows.h>
#include <string>

namespace util {

    enum class LogType {
        Info,
        Warning,
        Error,
        Success
    };

    void Log(const std::wstring& msg, LogType type);

    void ShowMessage(const std::wstring& msg, const std::wstring& title, UINT type);


}
