# Anti-AI

🛡️ **Anti-AI** is a Windows console app built for teamwork as the final exam project for **Object-Oriented Programming** at **ITSTEP (IT SCHOOL)**. The tool blocks access to popular AI services by combining Windows Filtering Platform (WFP) rules with hosts file overrides.

## 🧭 Overview
- Resolves a curated list of AI-related domains.
- Blocks outbound connections to the resolved IPs via WFP filters.
- Adds hosts file entries to prevent DNS-based bypass.
- Cleans up on exit or when run with `--uninstall`.

## 🧱 Project Architecture
- **Main.cpp** — app entry point, DNS resolution, WFP filter setup, lifecycle management.
- **Config.(h/cpp)** — provider/sublayer GUIDs, domain blocklist, hosts path.
- **WfpManager.(h/cpp)** — WFP provider/sublayer registration and IP filter creation.
- **HostsManager.(h/cpp)** — patching and cleanup of the Windows hosts file.

**Flow:** Resolve domains → add WFP block filters → patch hosts file → keep session alive until exit.

## ✨ Features
- 🔒 Blocks major AI providers (OpenAI, Anthropic, Google, xAI, etc.).
- 🧠 DNS resolution with unique IP de-duplication.
- 🧰 WFP dynamic session (auto-removes filters on close).
- 🧹 Hosts file cleanup and DNS cache flush.
- 🛠️ `--uninstall` mode to restore access quickly.

## 🧰 Technologies Used
- **C++20**
- **Windows API** (WFP, WinSock, DNS)
- **Visual Studio / MSVC** (toolset configured in the project)

## ▶️ How to run this project?
> ⚠️ **Administrator privileges required** (WFP + hosts file edits).

1. Open `Anti-AI.slnx` in **Visual Studio 2022**.
2. Build **Release | x64**.
3. Run the generated `.exe` **as Administrator**.
4. Keep the window open to keep blocking active.
5. To uninstall/cleanup:
   ```powershell
   Anti-AI.exe --uninstall
   ```

## 🤝 Contributing
Contributions are welcome!
- Open an issue for bugs or ideas.
- Fork the repo, create a feature branch, and open a PR.

## 📜 License
Licensed under the **GNU AGPLv3**. See [LICENSE.txt](LICENSE.txt) for details.
