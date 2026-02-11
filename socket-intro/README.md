# Socket Intro (TCP + UDP with Asio)

Small C++ socket examples using standalone Asio:
- `tcp_server` / `tcp_client`
- `udp_server` / `udp_client`

Asio is vendored in `third_party/asio-1.18.0`, so no extra Asio install is needed.

## Recommended on Windows (2026)

Use **WSL2 + Ubuntu** and build this as a Linux project. This is the easiest path and avoids Visual Studio IDE setup issues.

### Install WSL2 (one-time)

In **PowerShell as Administrator**:

```powershell
wsl --install -d Ubuntu
```

Then reboot if prompted, open the **Ubuntu** app, and create your Linux username/password.

After future reboots, get back into WSL by either:
- Launching **Ubuntu** from the Start menu, or
- Running `wsl` in PowerShell/Windows Terminal.

Inside Ubuntu, install build tools:

```bash
sudo apt update
sudo apt install -y build-essential cmake
```

## Build

```bash
cmake -S . -B build
cmake --build build -j
```

## Run

Open two terminals.

TCP:

```bash
./build/tcp_server
./build/tcp_client 127.0.0.1
```

UDP:

```bash
./build/udp_server
./build/udp_client 127.0.0.1
```

The server listens on port `3000` and echoes each byte as `value + 1`.
