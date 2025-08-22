#include <Windows.h>
#include <ShlObj.h>
#include <filesystem>
#include <string>
#include <thread>
#include <chrono>
#include "Utils.h"
#include "Memory.h"
#include <iostream>

int wmain() {
    std::thread(&mem::RenameConsoleRandomly).detach();
    if (!mem::IsRobloxVersionCorrect()) {
        util::Log(L"Roblox version mismatch! Cannot inject.", util::LogType::Error);
        std::wcin.get();
        return 1;
    }

    util::Log(L"The Version Checked is legit Injecting...", util::LogType::Info);

    HWND hwnd = nullptr;
    for (int i = 0; i < 300; ++i) { 
        hwnd = FindWindowW(NULL, L"Roblox");
        if (hwnd) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if (!hwnd) {
        util::Log(L"Roblox window not found. Exiting.", util::LogType::Error);
        std::wcout << L"Press Enter to exit...";
        std::wcin.get();
        return 1;
    }

    DWORD pid = 0;
    DWORD tid = GetWindowThreadProcessId(hwnd, &pid);
    if (!pid || !tid) {
        util::Log(L"Failed to get Roblox PID/TID.", util::LogType::Error);
        std::wcout << L"Press Enter to exit...";
        std::wcin.get();
        return 1;
    }

    util::Log(L"Found Roblox! PID: " + std::to_wstring(pid) + L", TID: " + std::to_wstring(tid), util::LogType::Success);

    wchar_t dllPath[MAX_PATH];
    if (!GetFullPathNameW(L"Merdeka.dll", MAX_PATH, dllPath, nullptr)) {
        util::Log(L"Failed to resolve DLL path.", util::LogType::Error);
        return 1;
    }
    util::Log(L"Loading DLL: " + std::wstring(dllPath), util::LogType::Info);

    HMODULE dll = LoadLibraryExW(dllPath, nullptr, DONT_RESOLVE_DLL_REFERENCES);
    if (!dll) {
        util::Log(L"Failed to load DLL.", util::LogType::Error);
        return 1;
    }

    HOOKPROC addr = reinterpret_cast<HOOKPROC>(GetProcAddress(dll, "NextHook"));
    if (!addr) {
        util::Log(L"Failed to get NextHook address.", util::LogType::Error);
        FreeLibrary(dll);
        return 1;
    }

    HHOOK Inj = SetWindowsHookExW(WH_GETMESSAGE, addr, dll, tid);
    if (!Inj) {
        util::Log(L"Failed to set hook.", util::LogType::Error);
        FreeLibrary(dll);
        return 1;
    }

    PostThreadMessageW(tid, WM_NULL, 0, 0);
    util::Log(L"DLL injected successfully! Press Enter to unhook and exit...", util::LogType::Success);

    std::wcin.get();

    UnhookWindowsHookEx(Inj);
    FreeLibrary(dll);
    util::Log(L"Cleaned up and exiting.", util::LogType::Info);

    return 0;
}
