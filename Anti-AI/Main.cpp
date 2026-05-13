#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <fwpmu.h>
#include <iostream>
#include <set>

#include "Config.h"
#include "WfpManager.h"
#include "HostsManager.h"

#pragma comment(lib, "fwpuclnt.lib")
#pragma comment(lib, "ws2_32.lib")

using namespace std;

HANDLE g_engine = NULL;

void Shutdown()
{
    if (g_engine)
    {
        // Restore access by closing dynamic WFP session (automatically removes filters)
        cout << "[*] Reverting changes and restoring access..." << endl;
        FwpmEngineClose0(g_engine);
        g_engine = NULL;
    }

    CleanHostsFile();
    system("ipconfig /flushdns > nul");
    cout << "[*] DNS cache flushed. Hosts cleaned." << endl;
}

BOOL WINAPI ConsoleHandler(DWORD signal)
{
    if (signal == CTRL_C_EVENT || signal == CTRL_CLOSE_EVENT ||
        signal == CTRL_BREAK_EVENT || signal == CTRL_LOGOFF_EVENT ||
        signal == CTRL_SHUTDOWN_EVENT)
    {
        Shutdown();
        return FALSE;
    }
    return FALSE;
}

int main(int argc, char* argv[])
{
    bool isUninstall = (argc > 1 && string(argv[1]) == "--uninstall");

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return 1;

    FWPM_SESSION0 session = {};
    session.flags = FWPM_SESSION_FLAG_DYNAMIC;
    HANDLE engine = NULL;

    DWORD result = FwpmEngineOpen0(NULL, RPC_C_AUTHN_WINNT, NULL, &session, &engine);
    if (result != ERROR_SUCCESS)
    {
        cout << "[ERROR] FwpmEngineOpen0 failed (Error code: " << result << ")! Run as Administrator." << endl;
        WSACleanup();
        return 1;
    }

    g_engine = engine;
    SetConsoleCtrlHandler(ConsoleHandler, TRUE);

    if (isUninstall)
    {
        cout << "[*] Uninstall mode chosen. Cleaning up..." << endl;
        Shutdown();
        WSACleanup();
        return 0;
    }

    if (!SetupWFPLayers(engine))
    {
        cout << "[ERROR] Failed to register WFP provider and sublayer." << endl;
        Shutdown();
        WSACleanup();
        return 1;
    }

    cout << "[*] WFP engine ready, resolving domains...\n\n";

    set<string> seen;
    int blocked = 0, failed = 0;

    for (const auto& domain : domains)
    {
        addrinfo hints = {};
        hints.ai_family = AF_INET;
        addrinfo* info = nullptr;

        if (getaddrinfo(domain.c_str(), NULL, &hints, &info) != 0)
        {
            cout << "[DNS FAIL] " << domain << endl;
            failed++;
            continue;
        }

        for (addrinfo* ptr = info; ptr; ptr = ptr->ai_next)
        {
            sockaddr_in* s4 = (sockaddr_in*)ptr->ai_addr;
            char buf[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &s4->sin_addr, buf, sizeof(buf));
            string ipText = buf;

            if (!seen.insert(ipText).second) continue;

            bool ok = AddIPv4Filter(engine, s4->sin_addr.S_un.S_addr,
                "AI Block: " + domain + " " + ipText);

            cout << (ok ? "[BLOCKED] " : "[FAILED]  ") << domain << " -> " << ipText << endl;
            ok ? blocked++ : failed++;
        }
        freeaddrinfo(info);
    }

    cout << "\n[INFO] WFP Filters added : " << blocked << "\n[INFO] Failures : " << failed << "\n\n";

    PatchHostsFile();
    // Flush to prevent caching mechanics from bypassing the local host resolution
    system("ipconfig /flushdns > nul");
    cout << "[*] System DNS cache flushed\n\n";

    cout << "=================================================\n"
        << "AI WEBSITES ARE NOW BLOCKED!\n"
        << "DO NOT CLOSE THIS WINDOW if you want to keep them blocked.\n\n"
        << "To restore access and exit, press any key "
        << "or close this window (X).\n"
        << "=================================================\n\n";

    system("pause");

    Shutdown();
    WSACleanup();
    return 0;
}