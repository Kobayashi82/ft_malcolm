<div align="center">

![Security](https://img.shields.io/badge/Security-brown?style=for-the-badge)
![Network Security](https://img.shields.io/badge/Network-Security-blue?style=for-the-badge)
![Protocol ARP](https://img.shields.io/badge/Protocol-ARP-green?style=for-the-badge)
![C Language](https://img.shields.io/badge/Language-C-red?style=for-the-badge)

*Una introducción práctica a los ataques Man in the Middle mediante ARP Spoofing*

</div>

# ft_malcolm

> Este proyecto es únicamente para fines educativos como parte del curriculum de 42 School. El código debe usarse solo en entornos controlados, como máquinas virtuales. Interceptar tráfico real sin autorización apropiada es ilegal y poco ético.

## 🎯 Descripción

**ft_malcolm** es una implementación educativa de ARP Spoofing (envenenamiento ARP), uno de los ataques Man in the Middle más básicos y fundamentales en seguridad de redes. Este proyecto forma parte de la rama de seguridad de red de 42 School.

### ¿Qué es ARP Spoofing?

El Address Resolution Protocol (ARP) es un protocolo de la capa 2 del modelo OSI que permite asociar direcciones IP con direcciones MAC en redes locales. Sin embargo, ARP tiene vulnerabilidades inherentes:

- **No tiene autenticación**: Cualquier dispositivo puede enviar respuestas ARP
- **Confía por defecto**: Las tablas ARP se actualizan automáticamente
- **Sin verificación**: No valida la legitimidad de las respuestas

### ¿Cómo funciona ft_malcolm?

1. **Escucha pasiva**: Monitorea la red esperando requests ARP broadcast del objetivo
2. **Detección**: Identifica cuando el target solicita la IP que queremos suplantar
3. **Respuesta maliciosa**: Envía una respuesta ARP falsa asociando nuestra MAC con la IP objetivo
4. **Envenenamiento exitoso**: La tabla ARP del target queda comprometida

```
[Target] ----ARP Request: "¿Quién tiene 192.168.1.1?"----- [Broadcast]
                                    |
[ft_malcolm] ----ARP Reply: "192.168.1.1 es aa:bb:cc:dd:ee:ff"----- [Target]
```

## 📚 Modelo OSI

### ¿Qué es?
Un modelo teórico de 1984 que explica cómo se comunican las computadoras dividiendo el proceso en 7 capas.

### Las 7 Capas (de arriba a abajo)

- **7. Aplicación** → Lo que ves (navegador, email, WhatsApp)
- **6. Presentación** → Cifrado y compresión de datos (TLS/SSL, SSH)
- **5. Sesión** → Inicia, mantiene y cierra conexiones
- **4. Transporte** → Divide y reordena los datos (TCP/UDP y puertos)
- **3. Red** → Encuentra el camino (direcciones IP y routers)
- **2. Enlace** → Se encarga de la entrega en la red local usando direcciones MAC (ARP y switches)
- **1. Física** → Hardware y señales eléctricas (cables, fibra óptica, ondas de radio)

## ¿Cómo funciona?

- Imagina enviar una carta:

#### 📤 Envío (de arriba hacia abajo)

| N | Capa                             | Analogía                                                        |
| - | -------------------------------- | --------------------------------------------------------------- |
| 7 | Aplicación                       | Escribes el mensaje                                             |
| 6 | Presentación, Sesión, Transporte | Cifras el mensaje, los divides en partes y lo metes en un sobre |
| 3 | Red                              | El cartero encuentra la dirección                               |
| 2 | Enlace                           | Se lleva al camión repartidor                                   |
| 1 | Física                           | Viaja por carreteras físicas                                    |

#### 📥 Recepción (de abajo hacia arriba)

| N | Capa                             | Analogía                                       |
| - | -------------------------------- | ---------------------------------------------- |
| 7 | Física                           | Llega por las carreteras                       |
| 6 | Enlace                           | El camión repartidor lo entrega                |
| 3 | Red                              | Se lee la dirección de destino                 |
| 2 | Transporte, Sesión, Presentación | Se abre el sobre, se reconstruye y se descifra |
| 1 | Aplicación                       | Se lee el mensaje                              |

### ¿Se usa hoy en día?

**En la teoría: SÍ** → Sigue siendo el estándar para entender y enseñar redes

**En la práctica: NO** → Internet usa TCP/IP (4 capas), no OSI

#### Lo que realmente usamos:
- **Internet funciona con TCP/IP** (más simple, 4 capas)
- **OSI es principalmente educativo** y para troubleshooting
- **Los conceptos siguen siendo válidos**, pero implementados de forma diferente

### ¿Para qué sirve hoy?
1. **Entender cómo funcionan las redes** de forma ordenada
2. **Resolver problemas**: "¿Es problema de cable, de IP, o de la aplicación?"
3. **Comunicarse entre técnicos** usando un lenguaje común
4. **Diseñar redes** separando responsabilidades

## 🔧 Compilación

```bash
git clone git@github.com:Kobayashi82/ft_malcolm.git
cd ft_malcolm
make
```

## 🖥️ Uso

### Sintaxis

```bash
sudo ./ft_malcolm <source_ip> <source_mac> <target_ip> <target_mac>
```

### Parámetros

| Parámetro | Descripción | Ejemplo |
|-----------|-------------|---------|
| `source_ip` | IP que queremos suplantar | `192.168.1.1` |
| `source_mac` | MAC falsa a asociar | `aa:bb:cc:dd:ee:ff` |
| `target_ip` | IP del dispositivo objetivo | `192.168.1.100` |
| `target_mac` | MAC real del objetivo | `00:11:22:33:44:55` |

### Ejemplo de Uso

```bash
sudo ./ft_malcolm 10.12.255.255 ff:bb:ff:ff:ee:ff 10.12.10.22 10:dd:b1:aa:bb:cc
```

**Salida esperada:**

```
Found available interface: eth0
An ARP request has been broadcast.
    mac address of request: 10:dd:b1:aa:bb:cc
    IP address of request: 10.12.12.07
Now sending an ARP reply to the target address with spoofed source, please wait...
Sent an ARP reply packet, you may now check the arp table on the target.
Exiting program...
```

### Verificación del Ataque

En el dispositivo objetivo, verifica la tabla ARP:

```bash
arp -a
```

Deberías ver la asociación falsa IP → MAC que configuraste.

### Comandos Útiles

|         Acción         |               Comando               |
| ---------------------- | ----------------------------------- |
| Ver info del adaptador | `ip link`                           |
| Ver tráfico de red     | `sudo tcpdump -i <if_name>`         |
| Limpiar tabla ARP      | `sudo arp -d <ip>`                  |
| Ver tabla ARP          | `arp -a`                            |
| Añadir ip              | `ip addr add <ip/24> dev <if_name>` |
| Eliminar ip            | `ip addr del <ip/24> dev <if_name>` |
| Ver ip                 | `ip addr show <if_name>`            |
|                                                              |

## 🛠️ Funcionalidades

### Parte Obligatoria

- ✅ Soporte IPv4 únicamente
- ✅ Validación de IPs y MACs
- ✅ Detección de ARP requests broadcast
- ✅ Envío de ARP reply único y salida
- ✅ Gestión de errores robusta
- ✅ Manejo de señales

### Funciones Usadas

| Categoría                     | Función            | Descripción                                                                                                             |
|-------------------------------|--------------------|-------------------------------------------------------------------------------------------------------------------------|
| Interfaces de Red             | `getifaddrs`       | Obtiene una lista completa de las interfaces de red disponibles y sus direcciones asociadas (por ejemplo, eth0, wlan0)  |
| Interfaces de Red             | `freeifaddrs`      | Libera la memoria utilizada por la estructura de datos devuelta por `getifaddrs`                                        |
| Interfaces de Red             | `if_nametoindex`   | Obtiene el índice numérico de una interfaz de red a partir de su nombre                                                 |
| Conversión de Direcciones IP  | `inet_pton`        | Convierte direcciones IP en formato texto a binario de red                                                              |
| Conversión de Direcciones IP  | `inet_ntop`        | Convierte direcciones IP binarias a formato texto                                                                       |
| Conversión de Orden de Bytes  | `htons`            | Convierte del orden de bytes del host al orden de bytes de red                                                          |
| Conversión de Orden de Bytes  | `ntohs`            | Convierte del orden de bytes de red al orden de bytes del host                                                          |
| Gestión de Sockets            | `socket`           | Crea un canal de comunicación para enviar y recibir datos                                                               |
| Envío y Recepción de Datos    | `sendto`           | Envía un paquete de datos a una dirección específica                                                                    |
| Envío y Recepción de Datos    | `recvfrom`         | Recibe datos de una dirección específica                                                                                |
| Manejo de Errores             | `strerror`         | Convierte códigos de error del sistema en mensajes descriptivos                                                         |
| Utilidades del Sistema        | `close`            | Cierra un descriptor de archivo o socket, liberando los recursos asociados                                              |
| Manejo de Señales             | `signal`           | Establece manejadores para señales de terminación (SIGINT, SIGQUIT, SIGTERM, SIGHUP)                                    |
| Salida Formateada             | `printf`           | Imprime texto formateado a la salida estándar (stdout)                                                                  |
| Salida Formateada             | `fprintf`          | Imprime texto formateado a un archivo específico o stream                                                               |
| Salida Formateada             | `sscanf`           | Lee datos de una cadena de texto y los convierte en los tipos de datos especificados                                    |

## 📊 Conceptos Técnicos

### Protocolo ARP (RFC 826)

ARP opera enviando broadcasts preguntando "¿Quién tiene esta IP?" y esperando respuestas con "Yo la tengo, mi MAC es X". El problema: cualquiera puede responder.

### Estructura del Paquete ARP

```c
typedef struct arp_header {
    uint16_t hardware_type;      // Tipo de hardware (Ethernet = 1)
    uint16_t protocol_type;      // Tipo de protocolo (IPv4 = 0x0800)
    uint8_t  hardware_len;       // Longitud MAC (6 bytes)
    uint8_t  protocol_len;       // Longitud IP (4 bytes)
    uint16_t operation;          // Operación (Request=1, Reply=2)
    uint8_t  sender_mac[6];      // MAC del emisor
    uint32_t sender_ip;          // IP del emisor
    uint8_t  target_mac[6];      // MAC del objetivo
    uint32_t target_ip;          // IP del objetivo
};
```

### Vulnerabilidades Explotadas

1. **Falta de autenticación**: ARP no verifica identidades
2. **Last-writer-wins**: La última respuesta ARP sobrescribe la tabla
3. **Confianza implícita**: Los dispositivos aceptan respuestas no solicitadas
4. **Broadcast nature**: Todos pueden escuchar y responder

## ⚠️ Consideraciones Éticas y Legales

Este software está diseñado **EXCLUSIVAMENTE** para:
- **Educación en seguridad de redes**
- **Entornos controlados**
- **Redes propias o con autorización explícita**
- **Investigación académica**

### Prohibido Terminantemente

❌ Uso en redes ajenas sin autorización  
❌ Interceptación de tráfico real  
❌ Actividades maliciosas  
❌ Violación de privacidad  
❌ Cualquier uso ilegal  

### Responsabilidad Legal

```
El uso indebido de esta herramienta puede constituir:
- Violación de leyes de ciberseguridad
- Acceso no autorizado a sistemas
- Interceptación ilegal de comunicaciones
- Daños a infraestructura de red

EL USUARIO ASUME TODA LA RESPONSABILIDAD LEGAL
```

## 🛡️ Contramedidas y Defensas

### Protecciones contra ARP Spoofing

1. **ARP estático**: Configurar entradas ARP permanentes
2. **Monitoreo de red**: Detectar cambios sospechosos en tablas ARP
3. **Segmentación**: VLANs y subredes aisladas
4. **Port Security**: Limitar MACs por puerto en switches
5. **ARP Inspection**: Validación dinámica en switches managed

### Detección de Ataques

```bash
# Monitorear cambios en tabla ARP
watch -n 1 'arp -a'

# Usar herramientas especializadas
arpwatch
arpon
```

## 📄 Licencia

Este proyecto está licenciado bajo la WTFPL – [Do What the Fuck You Want to Public License](http://www.wtfpl.net/about/).

---

<div align="center">

**🌐 Desarrollado como parte del curriculum de 42 School 🌐**

*"The best defense is understanding the attack"*

</div>
