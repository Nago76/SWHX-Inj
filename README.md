# SWHX [ SetWindowsHookex ]

The SetWindowsHookEx just an injector only work when u have signed dll, well this project is not mine and i got it from Discord
so the owner of this project delete his project so this is backup of his project well ik lmoooo

## How this work?

This only for Roblox

So this only work if u have signed your dll, yes it very shitty injector and no offsets require. So to implement this its very easy

1. you have to add this code below dllmain at ur api module

```cpp
// ADD THIS BELOW DLLMAIN!
extern "C" __declspec(dllexport) int NextHook(int nCode, WPARAM wParam, LPARAM lParam) { return CallNextHookEx(NULL, nCode, wParam, lParam); }

```

2. You have to change Roblox Version at Memory.h

```cpp
const std::wstring Vrs = L"version-fe20d41d8fec4770"; // change your roblox version if updated
```

3. Put your signed dll name at dllmain.cpp

```cpp
  if (!GetFullPathNameW(L"YOUR_DLL_NAME.dll", MAX_PATH, dllPath, nullptr)) // CHANGE YOUR DLL NAME
```

4. so that it! and build it and also test it if its work

## Issue

- Q. Why my module didn't not injected?
- A. Didn't you sign your dll first, If you didn't signed your dll. Download this file [DLL Signer](https://v3rm.net/threads/new-injection-method-reupload.22751/)

- Q. Why it show mismatch version?
- A. Did you change the version at step 2?

- Q. Why my game crash
- A. uhhh its your module fault lmaooo

## hm

I don't responsibility if u get banned, This project is for Experimental and Educational Purpose
