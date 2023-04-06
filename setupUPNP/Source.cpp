#include <iostream>
#include <string>
#include <windows.h>
#include "MailSlots.h"

//my camera
//CameraModelK350

class CameraSelect
{
public:
    CameraSelect()
    {
        mailSlotRx = new Mailslot("\\\\.\\mailslot\\Global\\WFTPAIRING\\EVENT");
        mailSlotRx->OpenServer();
        mutex = CreateMutex(NULL, TRUE, L"CANON-EOSLIB-MAINSERVER-Shutdown");
        
        std::string str;

        std::string targetId = "{9F3E1EF9-F418-4FDB-B645-6D7585A28F72}";
        str = " /TARGETID " + targetId;

        std::wstring wstr = std::wstring(str.begin(), str.end());
        std::wstring service = L"/WFTSERVICE";
        UpnpServerStart(service + wstr);
    }

private:
    Mailslot* mailSlotRx;
    HANDLE mutex;


    void UpnpServerStart(std::wstring param)
    {
        STARTUPINFOW startupInfo;
        PROCESS_INFORMATION processInfo;

        ZeroMemory(&startupInfo, sizeof(startupInfo));
        startupInfo.cb = sizeof(startupInfo);
        startupInfo.dwFlags = STARTF_USESHOWWINDOW;
        startupInfo.wShowWindow = SW_HIDE;

        //std::wstring commandLine = L"C:\\Program Files (x86)\\Canon\\EOS Utility\\EOSUPNPSV.exe " + param;
        std::wstring commandLine = L"EOSUPNPSV.exe " + param;
        CreateProcessW(NULL, const_cast<LPWSTR>(commandLine.c_str()), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &startupInfo, &processInfo);

        WaitForSingleObject(processInfo.hProcess, INFINITE);

        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
    }
};

int main()
{
    CameraSelect camera;
    return 0;
}