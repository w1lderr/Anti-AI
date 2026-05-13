#include "HostsManager.h"
#include "Config.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void CleanHostsFile()
{
    ifstream fin(HOSTS_PATH);
    if (!fin) return;

    string line;
    ostringstream out;
    bool skipNext = false;

    // Read hosts file line by line and remove our custom block entries
    while (getline(fin, line))
    {
        if (line == "# AI Blocker") { skipNext = true; continue; }
        // Skip lines that have been redirected by us 
        if (skipNext && line.find("0.0.0.0") != string::npos) continue;

        skipNext = false;
        out << line << "\n";
    }
    fin.close();

    ofstream fout(HOSTS_PATH);
    if (fout) fout << out.str();
}

void PatchHostsFile()
{
    CleanHostsFile();

    // Append block rules directly to Windows hosts file
    ofstream fout(HOSTS_PATH, ios::app);
    if (fout)
    {
        fout << "\n# AI Blocker\n";
        for (const auto& d : domains)
            fout << "0.0.0.0 " << d << "\n";
        cout << "[HOSTS] Updated hosts file with blocklist" << endl;
    }
    else
    {
        cout << "[WARN]  Could not write hosts file. Ensure running as Administrator." << endl;
    }
}