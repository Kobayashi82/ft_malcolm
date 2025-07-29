# ft_malcolm - Guía del Bonus Potente

## Resumen del Proyecto

**Objetivo**: Implementar un ARP spoofing/poisoning attack (Man-in-the-Middle) con funcionalidades avanzadas.

**Parte obligatoria**: Programa que espera una petición ARP, envía una respuesta falsa y termina.

**Tu bonus potente**: Herramienta completa de MITM con interfaz interactiva y redirección real.

## Funcionalidades Implementadas

### 1. **Modo Interactivo** (sin argumentos)
```bash
sudo ./ft_malcolm
```
- Lista interfaces disponibles
- Escanea la red automáticamente
- Permite seleccionar víctima y target
- Ofrece diferentes modos de operación

### 2. **Modo Clásico** (con argumentos)
```bash
sudo ./ft_malcolm <source_ip> <source_mac> <target_ip> <target_mac>
```
- Mantiene compatibilidad con requisitos originales
- Soporte para hostnames y IPs decimales
- Modo verbose opcional

### 3. **Modos de Operación**
- **Pasivo**: Espera petición ARP (requisito original)
- **Activo**: Envía ARP replies cada X segundos
- **MITM Completo**: Intercepta y reenvía tráfico real

## Arquitectura Técnica

### Funciones Permitidas (Obligatorias)
- `socket, sendto, recvfrom`
- `inet_pton, inet_ntop, inet_addr`
- `gethostbyname, getaddrinfo`
- `getifaddrs, freeifaddrs`
- `htons, ntohs`
- `sleep, signal, sigaction`

### Funciones Extra (Para Bonus Potente)
- **libpcap**: Captura de paquetes en modo promiscuo
- **ioctl**: Manipulación de interfaces de red
- **pthread/fork**: Manejo de múltiples conexiones
- **raw sockets**: Creación de paquetes personalizados

## Implementación del Bonus

### 1. **Detección de Red**
```c
// Usar getifaddrs() para listar interfaces
// Escanear red con ARP broadcast
// Detectar dispositivos activos
```

### 2. **Captura de Paquetes**
```c
// Usar pcap para capturar TODO el tráfico
pcap_t *handle = pcap_open_live("eth0", BUFSIZ, 1, 1000, errbuf);
pcap_loop(handle, -1, packet_handler, NULL);
```

### 3. **Redirección MITM**
```c
// Hilo 1: Capturar victim → target
// Hilo 2: Capturar target → victim
// Hilo 3: Reenviar con MAC modificada
// Hilo 4: Logging y estadísticas
```

### 4. **Interfaz Mejorada**
- Menús interactivos
- Logging detallado
- Estadísticas en tiempo real
- Manejo de errores robusto

## Permisos y Configuración

### Requisitos
- **Root obligatorio**: `sudo ./ft_malcolm`
- **IP forwarding**: `echo 1 > /proc/sys/net/ipv4/ip_forward`
- **Modo promiscuo**: Activado automáticamente

### Alternativa con Capabilities
```bash
sudo setcap cap_net_raw,cap_net_admin=eip ./ft_malcolm
```

## Estructura del Código

### Archivos Principales
```
ft_malcolm/
├── src/
│   ├── main.c              # Punto de entrada
│   ├── interactive.c       # Modo interactivo
│   ├── classic.c           # Modo clásico
│   ├── network_scan.c      # Detección de red
│   ├── packet_capture.c    # Captura con pcap
│   ├── mitm_engine.c       # Motor MITM
│   ├── arp_operations.c    # Operaciones ARP
│   └── utils.c             # Utilidades
├── include/
│   └── ft_malcolm.h        # Headers
├── libft/                  # Tu libft
└── Makefile
```

### Compilación
```makefile
# Makefile debe incluir:
LDFLAGS += -lpcap -lpthread
```

## Casos de Uso

### 1. **Pentesting Básico**
```bash
# Modo interactivo completo
sudo ./ft_malcolm

# Ataque específico
sudo ./ft_malcolm 192.168.1.1 aa:bb:cc:dd:ee:ff 192.168.1.105 11:22:33:44:55:66
```

### 2. **Monitoreo de Red**
```bash
# Modo verbose para debugging
sudo ./ft_malcolm -v router.local aa:bb:cc:dd:ee:ff laptop.local 11:22:33:44:55:66
```

### 3. **Educación/Demostración**
- Mostrar vulnerabilidades ARP
- Demostrar ataques MITM
- Analizar tráfico interceptado

## Defensa ante Evaluadores

### Argumentos Clave
1. **Cumple requisitos**: El modo clásico funciona exactamente como se pide
2. **Valor añadido**: Funcionalidades que hacen el programa realmente útil
3. **Aprendizaje**: Demuestra comprensión profunda de networking
4. **Innovación**: Va más allá de un simple "Hello World"

### Justificación Técnica
- "Implementé el core requirement y agregué funcionalidades que demuestran comprensión real del protocolo"
- "El modo interactivo hace la herramienta educativa y práctica"
- "La redirección MITM muestra el verdadero impacto del ataque"

## Consideraciones Éticas

### ⚠️ **IMPORTANTE**
- **Solo usar en redes propias**
- **Entorno de laboratorio/VM**
- **Fines educativos únicamente**
- **Nunca en redes de producción**

### Disclaimer
```
Este software es únicamente para propósitos educativos y de investigación.
El uso indebido puede violar leyes locales e internacionales.
El usuario es responsable del uso que haga de esta herramienta.
```

## Conclusión

**Resultado**: Una herramienta de ARP spoofing completa que:
- ✅ Cumple todos los requisitos obligatorios
- ✅ Añade funcionalidades reales y útiles
- ✅ Demuestra comprensión profunda de networking
- ✅ Impresiona a los evaluadores con funcionalidad real

**¡A por todas! 🔥**