<div align="center">

![Security](https://img.shields.io/badge/Security-brown?style=for-the-badge)
![Network Security](https://img.shields.io/badge/Network-Security-blue?style=for-the-badge)
![Protocol ARP](https://img.shields.io/badge/Protocol-ARP-green?style=for-the-badge)
![C Language](https://img.shields.io/badge/Language-C-red?style=for-the-badge)

*A practical introduction to Man-in-the-Middle attacks via ARP spoofing*

</div>

<div align="center">
  <img src="/ft_malcolm.png">
</div>

# ft_malcolm

[README en Español](README_es.md)

> This project is strictly for `educational` purposes as part of the `42 School` curriculum. The code must be used only in controlled environments, such as virtual machines. Intercepting real traffic without proper authorization is illegal and unethical.

`ft_malcolm` is an educational implementation of `ARP Spoofing` (ARP poisoning), one of the most basic and fundamental Man-in-the-Middle attacks in network security. This project is part of the `42 School` network security branch.

### What is ARP Spoofing?

The Address Resolution Protocol (ARP) is a layer 2 protocol in the OSI model that maps IP addresses to MAC addresses on local networks. However, ARP has inherent vulnerabilities:

- `No authentication`: Any device can send ARP replies
- `Default trust`: ARP tables update automatically
- `No verification`: It does not validate reply legitimacy

### How does ft_malcolm work?

1. `Passive listening`: Monitors the network waiting for ARP broadcast requests from the target
2. `Detection`: Identifies when the target requests the IP we want to spoof
3. `Malicious reply`: Sends a fake ARP reply associating our MAC with the target IP
4. `Successful poisoning`: The target's ARP table is compromised

```
[Target] ----ARP Request: "Who has 192.168.1.1?"----- [Broadcast]
                                    |
[ft_malcolm] ----ARP Reply: "192.168.1.1 is aa:bb:cc:dd:ee:ff"----- [Target]
```

## 📚 OSI Model

### What is it?
A theoretical model from 1984 that explains how computers communicate by dividing the process into 7 layers.

### The 7 layers (top to bottom)

- `7. Application` → What you see (browser, email, WhatsApp)
- `6. Presentation` → Encryption and compression (TLS/SSL, SSH)
- `5. Session` → Starts, maintains, and closes connections
- `4. Transport` → Splits and reorders data (TCP/UDP and ports)
- `3. Network` → Finds the path (IP addresses and routers)
- `2. Data Link` → Delivers on local network using MAC addresses (ARP and switches)
- `1. Physical` → Hardware and electrical signals (cables, fiber, radio waves)

## How does it work?

- Imagine sending a letter:

#### 📤 Sending (top to bottom)

| N | Layer                            | Analogy                                                |
|---|----------------------------------|--------------------------------------------------------|
| 7 | Application                      | You write the message                                  |
| 6 | Presentation, Session, Transport | You encrypt it, split it up, and put it in an envelope |
| 3 | Network                          | The mail carrier finds the address                     |
| 2 | Data Link                        | It goes to the delivery truck                          |
| 1 | Physical                         | It travels on physical roads                           |

#### 📥 Receiving (bottom to top)

| N | Layer                            | Analogy                                              |
|---|----------------------------------|------------------------------------------------------|
| 7 | Physical                         | It arrives via the roads                             |
| 6 | Data Link                        | The delivery truck hands it over                     |
| 3 | Network                          | The destination address is read                      |
| 2 | Transport, Session, Presentation | The envelope is opened, reconstructed, and decrypted |
| 1 | Application                      | The message is read                                  |

### Is it used today?

**In theory: YES** → Still the standard for understanding and teaching networks

**In practice: NO** → The Internet uses TCP/IP (4 layers), not OSI

#### What we actually use:
- `The Internet runs on TCP/IP` (simpler, 4 layers)
- `OSI is mainly educational` and for troubleshooting
- `The concepts remain valid`, but implemented differently

### What is it for today?
1. `Understand how networks work` in an organized way
2. `Troubleshoot`: "Is it a cable issue, IP issue, or application issue?"
3. `Communicate between technicians` using a common language
4. `Design networks` by separating responsibilities

## 🔧 Build

```bash
git clone git@github.com:Kobayashi82/ft_malcolm.git
cd ft_malcolm
make
```

## 🖥️ Usage

### Syntax

```bash
sudo ./ft_malcolm <source_ip> <source_mac> <target_ip> <target_mac>
```

### Parameters

| Parameter    | Description           | Example             |
|--------------|-----------------------|---------------------|
| `source_ip`  | IP we want to spoof   | `192.168.1.1`       |
| `source_mac` | Fake MAC to associate | `aa:bb:cc:dd:ee:ff` |
| `target_ip`  | Target device IP      | `192.168.1.100`     |
| `target_mac` | Real target MAC       | `00:11:22:33:44:55` |

### Usage example

```bash
sudo ./ft_malcolm 10.12.255.255 ff:bb:ff:ff:ee:ff 10.12.10.22 10:dd:b1:aa:bb:cc
```

**Expected output:**

```
Found available interface: eth0
An ARP request has been broadcast.
    mac address of request: 10:dd:b1:aa:bb:cc
    IP address of request: 10.12.12.07
Now sending an ARP reply to the target address with spoofed source, please wait...
Sent an ARP reply packet, you may now check the arp table on the target.
Exiting program...
```

### Attack verification

On the target device, check the ARP table:

```bash
arp -a
```

You should see the fake IP → MAC association you configured.

### Useful commands

| Action               | Command                             |
|----------------------|-------------------------------------|
| Show adapter info    | `ip link`                           |
| View network traffic | `sudo tcpdump -i <if_name>`         |
| Clear ARP table      | `sudo arp -d <ip>`                  |
| View ARP table       | `arp -a`                            |
| Add IP               | `ip addr add <ip/24> dev <if_name>` |
| Remove IP            | `ip addr del <ip/24> dev <if_name>` |
| Show IP              | `ip addr show <if_name>`            |

## 🛠️ Features

### Mandatory part

- ✅ IPv4-only support
- ✅ IP and MAC validation
- ✅ Detection of ARP broadcast requests
- ✅ Single ARP reply send and exit
- ✅ Robust error handling
- ✅ Signal handling

### Functions used

| Category              | Function         | Description                                                                                               |
|-----------------------|------------------|-----------------------------------------------------------------------------------------------------------|
| Network interfaces    | `getifaddrs`     | Retrieves a full list of available network interfaces and their associated addresses (e.g., eth0, wlan0)  |
| Network interfaces    | `freeifaddrs`    | Frees memory used by the structure returned by `getifaddrs`                                               |
| Network interfaces    | `if_nametoindex` | Gets the numeric index of a network interface from its name                                               |
| IP address conversion | `inet_pton`      | Converts IP addresses from text to network binary                                                         |
| IP address conversion | `inet_ntop`      | Converts binary IP addresses to text                                                                      |
| Byte order conversion | `htons`          | Converts from host byte order to network byte order                                                       |
| Byte order conversion | `ntohs`          | Converts from network byte order to host byte order                                                       |
| Socket management     | `socket`         | Creates a communication channel to send/receive data                                                      |
| Data send/receive     | `sendto`         | Sends a data packet to a specific address                                                                 |
| Data send/receive     | `recvfrom`       | Receives data from a specific address                                                                     |
| Error handling        | `strerror`       | Converts system error codes into descriptive messages                                                     |
| System utilities      | `close`          | Closes a file descriptor or socket, freeing associated resources                                          |
| Signal handling       | `signal`         | Sets handlers for termination signals (SIGINT, SIGQUIT, SIGTERM, SIGHUP)                                  |
| Formatted output      | `printf`         | Prints formatted text to standard output (stdout)                                                         |
| Formatted output      | `fprintf`        | Prints formatted text to a specific file or stream                                                        |
| Formatted output      | `sscanf`         | Reads data from a string and converts it to specified types                                               |

## 📊 Technical Concepts

### ARP Protocol (RFC 826)

ARP works by broadcasting "Who has this IP?" and waiting for replies with "I do, my MAC is X". The problem: anyone can respond.

### ARP Packet Structure

```c
typedef struct arp_header {
    uint16_t hardware_type;      // Hardware type (Ethernet = 1)
    uint16_t protocol_type;      // Protocol type (IPv4 = 0x0800)
    uint8_t  hardware_len;       // MAC length (6 bytes)
    uint8_t  protocol_len;       // IP length (4 bytes)
    uint16_t operation;          // Operation (Request=1, Reply=2)
    uint8_t  sender_mac[6];      // Sender MAC
    uint32_t sender_ip;          // Sender IP
    uint8_t  target_mac[6];      // Target MAC
    uint32_t target_ip;          // Target IP
};
```

### Exploited vulnerabilities

1. `Lack of authentication`: ARP does not verify identities
2. `Last-writer-wins`: The last ARP reply overwrites the table
3. `Implicit trust`: Devices accept unsolicited replies
4. `Broadcast nature`: Everyone can listen and respond

## ⚠️ Ethical and Legal Considerations

This software is designed **EXCLUSIVELY** for:
- `Network security education`
- `Controlled environments`
- `Your own networks or with explicit authorization`
- `Academic research`

### Strictly forbidden

❌ Use on networks you do not own without authorization  
❌ Interception of real traffic  
❌ Malicious activities  
❌ Privacy violations  
❌ Any illegal use  

### Legal responsibility

```
Misuse of this tool may constitute:
- Violations of cybersecurity laws
- Unauthorized access to systems
- Illegal interception of communications
- Damage to network infrastructure

THE USER ASSUMES ALL LEGAL RESPONSIBILITY
```

## 🛡️ Countermeasures and Defenses

### Protections against ARP spoofing

1. `Static ARP`: Configure permanent ARP entries
2. `Network monitoring`: Detect suspicious ARP table changes
3. `Segmentation`: VLANs and isolated subnets
4. `Port security`: Limit MACs per port on switches
5. `ARP inspection`: Dynamic validation on managed switches

### Attack detection

```bash
# Monitor ARP table changes
watch -n 1 'arp -a'

# Use specialized tools
arpwatch
arpon
```

## 📄 License

This project is licensed under the WTFPL – [Do What the Fuck You Want to Public License](http://www.wtfpl.net/about/).

---

<div align="center">

**🕵️ Developed as part of the 42 School curriculum 🕵️**

*"The best defense is understanding the attack"*

</div>
