# Information

## Windows

| Acción | Comando |
|--------|---------|
| Limpiar tabla ARP | `netsh interface ip delete arpcache` |
| Ver tabla ARP | `arp -a` |
| Ping una vez | `ping <ip> -n 1` |

## Linux

| Acción | Comando |
|--------|---------|
| Limpiar tabla ARP | `sudo arp -d <ip>` |
| Ver tabla ARP | `arp -a` |
| Ver info del adaptador de red | `ifconfig` |
| Ver MAC propio | `ip link` |
| Ver tráfico de red | `sudo tcpdump -i <if_name>` |
| Establecer modo promiscuo | `sudo ip link set eth0 promisc on` |
| Establecer modo promiscuo | `sudo ifconfig eth0 promisc` |
| Enable IP forwarding | `echo 1 \| sudo tee /proc/sys/net/ipv4/ip_forward` |
| Disable IP forwarding | `echo 0 \| sudo tee /proc/sys/net/ipv4/ip_forward` |
| Ping una vez | `ping <ip> -c 1` |

## Pruebas

- sudo ./ft_malcolm 192.168.1.12 08:00:27:d8:10:91 192.168.1.150 D8-43-AE-BA-D8-57

| IP | MAC | Device |
|----|-----|--------|
|192.168.1.118 | 08-00-27-D8-10-91 | (Linux) |
|192.168.1.150 | D8-43-AE-BA-D8-57 | (Windows) |
|192.168.1.12 | 96-F6-21-CC-7A-03 | (Android) |