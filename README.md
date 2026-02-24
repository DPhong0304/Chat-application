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
```

## Usage
After building, run the executable with an optional port number (1024-65535). If no port is provided, you will be prompted to enter one.

```bash
./chatapp [port]
```

Enter your username when prompted. The application will start listening on the specified port.

Use the interactive command-line interface to manage connections and send messages.

## Commands
- `help`: Display available commands and usage.
- `myip`: Show your LAN IP address.
- `myport`: Show the port you are listening on.
- `connect <ip> <port>`: Connect to another host.
- `list`: List all active connections with IDs.
- `send <id> <message>`: Send a message to the connection with the specified ID.
- `terminate <id>`: Terminate the connection with the specified ID.
- `exit`: Quit the application.

## Examples
1. Start the app on port 8080:
   ```
   ./chatapp 8080
   Enter your username: Alice
   Alice@chatapp> connect 192.168.1.100 8081
   Alice@chatapp> send 1 Hello, Bob!
   Alice@chatapp> list
   ID      fd    hostname        IP              port      
   -------------------------------------------------------
   1       3     Bob             192.168.1.100   8081      
   Alice@chatapp> exit
   Exiting chat application...
   ```

2. Get help:
   ```
   Alice@chatapp> help
   ```
