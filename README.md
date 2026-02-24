# Chat-application
## Description:
This project is a peer-to-peer command-based chat application that facilitates communication between multiple hosts in the same LAN.  

---

## Features
- Command-line interface (interactive)
- Built-in `help` command to display available commands and usage information
- Listen on a chosen port
- Connect to another host using IP + port
- Maintain multiple active connections
- Send messages to a specific connection (by connection id)
- List current connections
- Exit (Ctrl + C may cause error)

---

## Requirements
- Linux 
- C++ compiler (e.g., `g++`)
- `make`

---

## Build
Clone the repo and compile using `make`:

```bash
make
