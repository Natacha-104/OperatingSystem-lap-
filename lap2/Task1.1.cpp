#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    printf("Parent Process ID: %lu\n", GetCurrentProcessId());
    printf("Parent Thread ID: %lu\n", GetCurrentThreadId());

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}

