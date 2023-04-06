#include <iostream>
#include <fstream>
#include <string>
#include "MailSlots.h"

int main() {
    Mailslot* mailSlotRx;
    HANDLE mutex;

    mailSlotRx = new Mailslot("\\\\.\\mailslot\\Global\\WFTPAIRING\\OPERATION");
    mailSlotRx->OpenServer();

    std::string macaddress;
    std::ifstream infile("macaddress.txt");
    if (infile.good()) {
        getline(infile, macaddress);
        infile.close();
    }
    else {
        std::cerr << "Error: could not open macaddress.txt" << std::endl;
        return 1;
    }

    for (int x = 0; x < 50; x++) {
        mailSlotRx->Send("Connect," + macaddress);
        Sleep(1);
    }

    return 0;
}