#pragma once
#include "Utils.h"
#include <Windows.h>
#include <ShlObj.h>
#include <filesystem>
#include <string>
#include <vector>
#include <optional>
#include <thread>
#include <random>
#include <chrono>
#include <TlHelp32.h>

namespace mem {

    inline bool IsRobloxVersionCorrect() {
        const std::wstring Vrs = L"version-fe20d41d8fec4770"; // Roblox version updated!
        const std::wstring playerExe = L"RobloxPlayerBeta.exe";

        wchar_t* localAppData = nullptr;
        if (FAILED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &localAppData))) {
            util::Log(L"Failed to get LocalAppData folder.", util::LogType::Error);
            return false;
        }

        std::filesystem::path versionsPath = std::filesystem::path(localAppData) / L"Roblox" / L"Versions";
        CoTaskMemFree(localAppData);

        if (!std::filesystem::exists(versionsPath) || !std::filesystem::is_directory(versionsPath)) {
            util::Log(L"Roblox Versions folder not found: " + versionsPath.wstring(), util::LogType::Error);
            return false;
        }

        for (auto& entry : std::filesystem::directory_iterator(versionsPath)) {
            if (entry.is_directory() && entry.path().filename() == Vrs) {
                std::filesystem::path exePath = entry.path() / playerExe;
                if (std::filesystem::exists(exePath)) {
                    util::Log(L"Found correct Roblox version at: " + exePath.wstring(), util::LogType::Success);
                    return true;
                }
            }
        }

        util::Log(L"Roblox version mismatch. Expected: " + Vrs + L". Waiting for update...", util::LogType::Warning);
        return false;
    }

    inline void RenameConsoleRandomly() {
        const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> charDist(0, static_cast<int>(charset.size() - 1));
        std::uniform_int_distribution<> lenDist(5, 15);

        while (true) {
            int titleLength = lenDist(gen);
            std::string randomTitle;
            for (int i = 0; i < titleLength; ++i)
                randomTitle += charset[charDist(gen)];

            SetConsoleTitleA(randomTitle.c_str());
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

    inline std::optional<DWORD> FindRobloxProcess() {
        PROCESSENTRY32 entry{};
        entry.dwSize = sizeof(PROCESSENTRY32);

        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snapshot == INVALID_HANDLE_VALUE) {
            util::Log(L"Failed to create process snapshot.", util::LogType::Error);
            return std::nullopt;
        }

        if (Process32First(snapshot, &entry)) {
            do {
                if (std::wstring(entry.szExeFile) == L"RobloxPlayerBeta.exe") {
                    CloseHandle(snapshot);
                    util::Log(L"Found Roblox process. PID: " + std::to_wstring(entry.th32ProcessID), util::LogType::Success);
                    return entry.th32ProcessID;
                }
            } while (Process32Next(snapshot, &entry));
        }

        CloseHandle(snapshot);
        util::Log(L"Roblox process not found.", util::LogType::Warning);
        return std::nullopt;
    }

}
