#include <iostream>
#include <Windows.h>

int main()
{
    const char* dllName = "C:\\Users\\whitetea\\Desktop\\RE\\My Games\\3 Fundamentals\\3.3 Internal\\code\\Internal_Ammo\\Debug\\Internal_Ammo.dll";
    
    HWND window  = 0;
    DWORD procId = 0;

    while (!window) {
        window = FindWindow(0, L"AssaultCube");
        Sleep(50);
    }
    
    GetWindowThreadProcessId(window, &procId);

    // Open Process
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);

    // Inj: alloc, load dll, start thread
    void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    WriteProcessMemory(hProc, loc, dllName, strlen(dllName) + 1, 0);
    HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);

    // Clean
    CloseHandle(hProc);
    CloseHandle(hThread);
}

