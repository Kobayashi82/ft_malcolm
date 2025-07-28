sudo ./ft_malcolm 192.168.1.12 aa:bb:cc:dd:ee:ff 192.168.1.150 D8-43-AE-BA-D8-57
sudo ./ft_malcolm 192.168.1.12 08:00:27:d8:10:91 192.168.1.150 D8-43-AE-BA-D8-57

192.168.1.118		08:00:27:d8:10:91	(Linux)
192.168.1.150		D8-43-AE-BA-D8-57	(Windows)
192.168.1.12		96:f6:21:cc:7a:03	(Android)



## Windows

Limpiar tabla ARP				netsh interface ip delete arpcache
Ver tabla ARP					arp -a
Ping una vez					ping <ip> -n 1



## Linux

Ver info del adaptador de red	ifconfig			
Ver MAC propio					ip link
Ver trafico de red				sudo tcpdump -i <if_name>

Establecer modo promiscuo		sudo ip link set eth0 promisc on
Establecer modo promiscuo		sudo ifconfig eth0 promisc
Enable IP forwarding			echo 0 | sudo tee /proc/sys/net/ipv4/ip_forward
Disable IP forwarding			echo 1 | sudo tee /proc/sys/net/ipv4/ip_forward

Ping una vez					ping <ip> -c 1



## Dudas

IP Fowarding se encarga de enviar y devolver las respuestas?
Deberia hacer poison arp a la ip y al router?
Porque es necesario?	struct __attribute__((__packed__)) arp_packet
Se puede poner en modo promiscuo desde C?

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
| Enable IP forwarding | `echo 1 | sudo tee /proc/sys/net/ipv4/ip_forward` |
| Disable IP forwarding | `echo 0 | sudo tee /proc/sys/net/ipv4/ip_forward` |
| Ping una vez | `ping <ip> -c 1` |

## Dudas

| Pregunta | Respuesta |
|----------|-----------|
| ¿IP Forwarding se encarga de enviar y devolver las respuestas? | No. IP Forwarding solo reenvía paquetes entre interfaces de red diferentes. No genera respuestas, actúa como un router que toma paquetes de una interfaz y los envía por otra. |
| ¿Debería hacer poison ARP a la IP y al router? | Sí, debes hacer ARP poisoning a ambos extremos: a la víctima (diciéndole que tu MAC es la del router) y al router (diciéndole que tu MAC es la de la víctima). Así interceptas todo el tráfico bidireccional. |
| ¿Por qué es necesario `struct __attribute__((__packed__)) arp_packet`? | El atributo `__packed__` elimina el padding automático del compilador. En protocolos de red las estructuras deben coincidir exactamente con el formato del protocolo, sin espacios adicionales. |
| ¿Se puede poner en modo promiscuo desde C? | Sí, usando sockets raw con `setsockopt()` y opciones como `PACKET_ADD_MEMBERSHIP`. Requiere permisos de root. |