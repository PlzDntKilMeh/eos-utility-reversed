#pragma once
#include <Windows.h>
#include <string>

class Mailslot {
public:
    Mailslot(std::string name) : mailslotName(name) {
        securityAttribute.nLength = sizeof(securityAttribute);
        securityAttribute.bInheritHandle = FALSE;
        securityAttribute.lpSecurityDescriptor = NULL;
        BOOL result = ::InitializeSecurityDescriptor(&securityDescriptor, SECURITY_DESCRIPTOR_REVISION);
        if (result == TRUE) {
            result = ::SetSecurityDescriptorDacl(&securityDescriptor, TRUE, NULL, FALSE);
        }
        if (result == TRUE) {
            securityAttribute.lpSecurityDescriptor = &securityDescriptor;
        }
        else {
            securityAttribute.lpSecurityDescriptor = NULL;
        }
    }

    bool Send(std::string message) {
        return Send(reinterpret_cast<const BYTE*>(message.c_str()), static_cast<DWORD>(message.length()));
    }

    bool Send(const BYTE* data, DWORD dataSize) {
        std::wstring wMailslotName(mailslotName.begin(), mailslotName.end());
        HANDLE handle = ::CreateFile(wMailslotName.c_str(), GENERIC_WRITE, FILE_SHARE_READ, &securityAttribute, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (handle == INVALID_HANDLE_VALUE) {
            return false;
        }

        DWORD bytesWritten;
        BOOL result = ::WriteFile(handle, data, dataSize, &bytesWritten, NULL);
        ::CloseHandle(handle);

        return (result == TRUE && bytesWritten == dataSize);
    }

    bool OpenServer() {
        serverHandle = ::CreateMailslotA(mailslotName.c_str(), 0, MAILSLOT_WAIT_FOREVER, &securityAttribute);
        return (serverHandle != INVALID_HANDLE_VALUE);
    }

    void CloseServer() {
        if (serverHandle != INVALID_HANDLE_VALUE) {
            ::CloseHandle(serverHandle);
            serverHandle = INVALID_HANDLE_VALUE;
        }
    }

    std::string ReceiveString() {
        std::string result;
        BYTE* data = Receive();
        if (data != nullptr) {
            result.assign(reinterpret_cast<char*>(data), strlen(reinterpret_cast<char*>(data)));
            delete[] data;
        }
        return result;
    }

    BYTE* Receive() {
        DWORD bytesRead = 0;
        DWORD messages = 0;
        DWORD bytesLeft = 0;
        DWORD nextSize = 0;

        bool result = ::GetMailslotInfo(serverHandle, NULL, &nextSize, &messages, &bytesLeft);
        if (!result) {
            return nullptr;
        }

        if (nextSize == MAILSLOT_NO_MESSAGE) {
            return nullptr;
        }

        BYTE* data = new BYTE[nextSize];

        result = ::ReadFile(serverHandle, data, nextSize, &bytesRead, NULL);
        if (!result || bytesRead != nextSize) {
            delete[] data;
            return nullptr;
        }

        return data;
    }

    bool IsInvalidServer() const {
        return (serverHandle == INVALID_HANDLE_VALUE);
    }

private:
    std::string mailslotName;
    HANDLE serverHandle = INVALID_HANDLE_VALUE;
    SECURITY_DESCRIPTOR securityDescriptor;
    SECURITY_ATTRIBUTES securityAttribute;
};