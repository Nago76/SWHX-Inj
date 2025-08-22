#include "Utils.h"
#include <thread>
#include <iostream>

namespace util {



    void Log(const std::wstring& msg, LogType type) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        WORD originalAttrs = 0;

        if (GetConsoleScreenBufferInfo(hConsole, &csbi))
            originalAttrs = csbi.wAttributes;

        std::wstring prefix = L"[ Sigma Injector ] ";

        switch (type) {
        case LogType::Info:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); /// Some colour
            prefix += L"[INFO] ";
            break;
        case LogType::Warning:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); /// yellow
            prefix += L"[WARN] ";
            break;
        case LogType::Error:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); /// bright red
            prefix += L"[ERROR] ";
            break;
        case LogType::Success:
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); /// bright green
            prefix += L"[SUCCESS] ";
            break;
        }

        std::wcout << prefix << msg << L"\n";

        SetConsoleTextAttribute(hConsole, originalAttrs);
    }


    void ShowMessage(const std::wstring& msg, const std::wstring& title, UINT type) {
        MessageBoxW(nullptr, msg.c_str(), title.c_str(), type);
    }

    bool WaitForWindow(const std::wstring& title, HWND& hwnd, int timeoutMs) {


    }
}
